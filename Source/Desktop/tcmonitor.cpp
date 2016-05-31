// TCMONITOR.CPP : Telecommand Procedures Monitor Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the telecommand
// procedures monitor related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2007/04/03 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static UINT BASED_CODE nTCProceduresMonitorStatusBarIndicators[] =
{
	ID_TCPROCEDURESMONITOR_STATUSBAR_MESSAGEPANE,
	ID_TCPROCEDURESMONITOR_STATUSBAR_UPLINKPANE,
	ID_TCPROCEDURESMONITOR_STATUSBAR_PEVPANE,
	ID_TCPROCEDURESMONITOR_STATUSBAR_CEVPANE,
	ID_TCPROCEDURESMONITOR_STATUSBAR_STATEPANE,
};



/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItem

CTCProceduresMonitorItem::CTCProceduresMonitorItem() : CDatabaseTCProcedure()
{
	m_nID = -1;
	m_nFlags = 0;
	m_tTriggerTime[0] = 0;
	m_tTriggerTime[1] = 0;
	m_tTriggerTime[2] = 0;
	m_tTriggerInterval = 0;
	m_tDailyTriggerTime = 0;
	m_nTriggerCount = 0;
	m_nExecutionCount = 0;
	m_tExecutionTime[0] = 0;
	m_tExecutionTime[1] = 0;
	m_bManualExecution = TRUE;
	m_bExecutionBreaks = TRUE;
	m_bTriggerEvent = FALSE;
	m_nTriggerType = TCPROCEDURESMONITORITEM_TRIGGERTYPE_NONE;
	m_nExecutionMode = TCPROCEDURESMONITORITEM_EXECUTIONMODE_NONE;
	m_nRunningState = TCPROCEDURESMONITORITEM_RUNNINGSTATE_NOTRUNNING;
	m_bAcknowledgmentFlag[TCPROCEDURESMONITORITEM_ALERTTYPE_INFORMATIONAL] = FALSE;
	m_bAcknowledgmentFlag[TCPROCEDURESMONITORITEM_ALERTTYPE_WARNING] = FALSE;
	m_bAcknowledgmentFlag[TCPROCEDURESMONITORITEM_ALERTTYPE_ERROR] = TRUE;
	m_bAcknowledgmentFlag[TCPROCEDURESMONITORITEM_ALERTTYPE_ALERT] = TRUE;
	m_bAcknowledgmentFlag[TCPROCEDURESMONITORITEM_ALERTTYPE_AUTHORIZATION] = TRUE;
	m_nAcknowledgmentColor[TCPROCEDURESMONITORITEM_ALERTTYPE_INFORMATIONAL] = GetSysColor(COLOR_WINDOWTEXT);
	m_nAcknowledgmentColor[TCPROCEDURESMONITORITEM_ALERTTYPE_WARNING] = GetSysColor(COLOR_WINDOWTEXT);
	m_nAcknowledgmentColor[TCPROCEDURESMONITORITEM_ALERTTYPE_ERROR] = VGA_COLOR_LTRED;
	m_nAcknowledgmentColor[TCPROCEDURESMONITORITEM_ALERTTYPE_ALERT] = VGA_COLOR_LTRED;
	m_nAcknowledgmentColor[TCPROCEDURESMONITORITEM_ALERTTYPE_AUTHORIZATION] = VGA_COLOR_LTRED;
	m_bAuditionBlinkFlag[TCPROCEDURESMONITORITEM_ALERTTYPE_INFORMATIONAL] = FALSE;
	m_bAuditionBlinkFlag[TCPROCEDURESMONITORITEM_ALERTTYPE_WARNING] = FALSE;
	m_bAuditionBlinkFlag[TCPROCEDURESMONITORITEM_ALERTTYPE_ERROR] = FALSE;
	m_bAuditionBlinkFlag[TCPROCEDURESMONITORITEM_ALERTTYPE_ALERT] = FALSE;
	m_bAuditionBlinkFlag[TCPROCEDURESMONITORITEM_ALERTTYPE_AUTHORIZATION] = FALSE;
	m_nAuditionColor[TCPROCEDURESMONITORITEM_ALERTTYPE_INFORMATIONAL] = m_nAcknowledgmentColor[TCPROCEDURESMONITORITEM_ALERTTYPE_INFORMATIONAL];
	m_nAuditionColor[TCPROCEDURESMONITORITEM_ALERTTYPE_WARNING] = m_nAcknowledgmentColor[TCPROCEDURESMONITORITEM_ALERTTYPE_WARNING];
	m_nAuditionColor[TCPROCEDURESMONITORITEM_ALERTTYPE_ERROR] = m_nAcknowledgmentColor[TCPROCEDURESMONITORITEM_ALERTTYPE_ERROR];
	m_nAuditionColor[TCPROCEDURESMONITORITEM_ALERTTYPE_ALERT] = m_nAcknowledgmentColor[TCPROCEDURESMONITORITEM_ALERTTYPE_ALERT];
	m_nAuditionColor[TCPROCEDURESMONITORITEM_ALERTTYPE_AUTHORIZATION] = m_nAcknowledgmentColor[TCPROCEDURESMONITORITEM_ALERTTYPE_AUTHORIZATION];
	m_bAlerted = FALSE;
	m_bEnabled = TRUE;
}

VOID CTCProceduresMonitorItem::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CTCProceduresMonitorItem::GetName() CONST
{
	return m_szName;
}

VOID CTCProceduresMonitorItem::SetID(INT nID)
{
	m_nID = nID;
}

INT CTCProceduresMonitorItem::GetID() CONST
{
	return m_nID;
}

VOID CTCProceduresMonitorItem::SetFlags(UINT nFlags)
{
	m_nFlags = nFlags;
}

UINT CTCProceduresMonitorItem::GetFlags() CONST
{
	return m_nFlags;
}

VOID CTCProceduresMonitorItem::SetArguments(CONST CDatabaseTCProcedureArguments &pArguments)
{
	m_pArguments.Copy(&pArguments);
}

INT CTCProceduresMonitorItem::GetArguments(CDatabaseTCProcedureArguments &pArguments) CONST
{
	pArguments.Copy(&m_pArguments);
	return((INT)pArguments.GetSize());
}

VOID CTCProceduresMonitorItem::SetTriggerType(UINT nType)
{
	if ((m_nTriggerType = nType) == TCPROCEDURESMONITORITEM_TRIGGERTYPE_AUTOMATIC)
	{
		m_tTriggerTime[0] = 0;
		m_tTriggerTime[1] = 0;
		m_tTriggerTime[2] = 0;
		m_tDailyTriggerTime = 0;
		m_tTriggerInterval = 0;
		m_nTriggerCount = 0;
		m_szTriggerEvent.Empty();
		m_bTriggerEvent = FALSE;
	}
}

UINT CTCProceduresMonitorItem::GetTriggerType() CONST
{
	return m_nTriggerType;
}

VOID CTCProceduresMonitorItem::SetTriggerTime(CONST CTimeKey &tTime)
{
	m_tTriggerTime[0] = tTime;
}

CTimeKey CTCProceduresMonitorItem::GetTriggerTime() CONST
{
	return m_tTriggerTime[0];
}

VOID CTCProceduresMonitorItem::SetDailyTriggerTime(CONST CTimeSpan &tTime)
{
	m_tDailyTriggerTime = tTime;
}

CTimeSpan CTCProceduresMonitorItem::GetDailyTriggerTime() CONST
{
	return m_tDailyTriggerTime;
}

VOID CTCProceduresMonitorItem::SetTriggerInterval(CONST CTimeKey &tStartTime, CONST CTimeSpan &tInterval)
{
	m_tTriggerTime[1] = tStartTime;
	m_tTriggerTime[2] = 0;
	m_tTriggerInterval = tInterval;
	m_nTriggerCount = 0;
}
VOID CTCProceduresMonitorItem::SetTriggerInterval(CONST CTimeKey &tStartTime, CONST CTimeSpan &tInterval, UINT nCount)
{
	m_tTriggerTime[1] = tStartTime;
	m_tTriggerTime[2] = 0;
	m_tTriggerInterval = tInterval;
	m_nTriggerCount = nCount;
}
VOID CTCProceduresMonitorItem::SetTriggerInterval(CONST CTimeKey &tStartTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime)
{
	m_tTriggerTime[1] = tStartTime;
	m_tTriggerTime[2] = tStopTime;
	m_tTriggerInterval = tInterval;
	m_nTriggerCount = 0;
}

BOOL CTCProceduresMonitorItem::GetTriggerInterval(CTimeKey &tStartTime, CTimeSpan &tInterval) CONST
{
	tStartTime = m_tTriggerTime[1];
	tInterval = m_tTriggerInterval;
	return((tStartTime > 0 && !m_tTriggerTime[2].GetTime() && !m_nTriggerCount) ? TRUE : FALSE);
}
BOOL CTCProceduresMonitorItem::GetTriggerInterval(CTimeKey &tStartTime, CTimeSpan &tInterval, UINT &nCount) CONST
{
	tStartTime = m_tTriggerTime[1];
	tInterval = m_tTriggerInterval;
	nCount = m_nTriggerCount;
	return((tStartTime > 0 && nCount > 0) ? TRUE : FALSE);
}
BOOL CTCProceduresMonitorItem::GetTriggerInterval(CTimeKey &tStartTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST
{
	tStartTime = m_tTriggerTime[1];
	tStopTime = m_tTriggerTime[2];
	tInterval = m_tTriggerInterval;
	return((tStartTime > 0 && tStopTime > 0 && tStartTime <= tStopTime) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorItem::SetTriggerEvent(LPCTSTR pszEvent)
{
	m_szTriggerEvent = pszEvent;
}

CString CTCProceduresMonitorItem::GetTriggerEvent() CONST
{
	return m_szTriggerEvent;
}

VOID CTCProceduresMonitorItem::EnableTriggerEvent(BOOL bEnable)
{
	m_bTriggerEvent = bEnable;
}

BOOL CTCProceduresMonitorItem::IsTriggerEventEnabled() CONST
{
	return m_bTriggerEvent;
}

VOID CTCProceduresMonitorItem::SetExecutionMode(UINT nMode)
{
	m_nExecutionMode = nMode;
}

UINT CTCProceduresMonitorItem::GetExecutionMode() CONST
{
	return m_nExecutionMode;
}

VOID CTCProceduresMonitorItem::SetExecutionStartTime(CONST CTimeKey &tTime)
{
	m_tExecutionTime[0] = tTime;
}

CTimeKey CTCProceduresMonitorItem::GetExecutionStartTime() CONST
{
	return m_tExecutionTime[0];
}

VOID CTCProceduresMonitorItem::SetExecutionEndTime(CONST CTimeKey &tTime)
{
	m_tExecutionTime[1] = tTime;
}

CTimeKey CTCProceduresMonitorItem::GetExecutionEndTime() CONST
{
	return m_tExecutionTime[1];
}

VOID CTCProceduresMonitorItem::SetExecutionCount(UINT nCount)
{
	m_nExecutionCount = nCount;
}

UINT CTCProceduresMonitorItem::GetExecutionCount() CONST
{
	return m_nExecutionCount;
}

VOID CTCProceduresMonitorItem::AllowManualExecution(BOOL bAllow)
{
	m_bManualExecution = bAllow;
}

BOOL CTCProceduresMonitorItem::IsManualExecutionAllowed() CONST
{
	return m_bManualExecution;
}

VOID CTCProceduresMonitorItem::AllowExecutionBreaks(BOOL bAllow)
{
	m_bExecutionBreaks = bAllow;
}

BOOL CTCProceduresMonitorItem::AreExecutionBreaksAllowed() CONST
{
	return m_bExecutionBreaks;
}

BOOL CTCProceduresMonitorItem::SetReleaseConstraints(CONST CStringArray &szItems)
{
	INT  nItem;
	INT  nItems;
	INT  nStep;
	INT  nSteps;
	INT  nEntry;
	INT  nEntries;
	INT  nThread;
	INT  nThreads;
	CString  szItem;
	CPtrArray  pSteps;
	CStringTools  cStringTools;
	CDatabaseTCPacket  cPacket;
	CDatabaseTCFunction  cFunction;
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pStep;
	CDatabaseTCProcedureThread  *pThread;
	CTCProcedureDocumentSendTCFunctionItem  *pSendTCFunctionStep;
	CTCProcedureDocumentSendTCSequenceItem  *pSendTCSequenceStep;

	for (nThread = 0, nThreads = (szItems.GetSize() > 0) ? (INT)GetSize() : 0, m_szReleaseItems.Copy(szItems); nThread < nThreads; nThread++)
	{
		if ((pThread = GetAt(nThread)) != (CDatabaseTCProcedureThread *)NULL)
		{
			if ((pDocument = new CTCProcedureDocument) != (CTCProcedureDocument *)NULL)
			{
				if (pDocument->Unmap(pThread) && pDocument->EnumSteps(pSteps, FALSE, TRUE) >= 0)
				{
					for (nItem = 0, nItems = (INT)m_szReleaseItems.GetSize(); nItem < nItems; nItem++)
					{
						if (m_szReleaseItems.GetAt(nItem).Left(pThread->GetName().GetLength() + 1) == pThread->GetName() + TAB)
						{
							for (nStep = 0, nSteps = (INT)pSteps.GetSize(); nStep < nSteps; nStep++)
							{
								if ((pStep = (CTCProcedureDocumentItem *)pSteps.GetAt(nStep)))
								{
									if (pStep->GetType() == TCPROCEDURETHREADSTEP_ACTIONOBJECT_SENDTCFUNCTION)
									{
										if ((pSendTCFunctionStep = (CTCProcedureDocumentSendTCFunctionItem *)pStep) && pSendTCFunctionStep->GetFunction(&cFunction, &cPacket))
										{
											szItem = pThread->GetName() + TAB + pStep->GetName() + TAB + cStringTools.ConvertIntToString(-1) + TAB + cFunction.GetName() + TAB;
											if (m_szReleaseItems.GetAt(nItem).Left(szItem.GetLength()) == szItem) break;
										}
									}
									if (pStep->GetType() == TCPROCEDURETHREADSTEP_ACTIONOBJECT_SENDTCSEQUENCE)
									{
										if ((pSendTCSequenceStep = (CTCProcedureDocumentSendTCSequenceItem *)pStep))
										{
											for (nEntry = 0, nEntries = pSendTCSequenceStep->GetSize(); nEntry < nEntries; nEntry++)
											{
												if ((pSendTCFunctionStep = pSendTCSequenceStep->GetAt(nEntry)) && pSendTCFunctionStep->GetFunction(&cFunction, &cPacket))
												{
													szItem = pThread->GetName() + TAB + pStep->GetName() + TAB + cStringTools.ConvertIntToString(nEntry + 1) + TAB + cFunction.GetName() + TAB;
													if (m_szReleaseItems.GetAt(nItem).Left(szItem.GetLength()) == szItem) break;
												}
											}
											if (nEntry < nEntries) break;
										}
									}
								}
							}
							if (nStep == nSteps)
							{
								m_szReleaseItems.RemoveAt(nItem);
								nItems--;
								nItem--;
							}
						}
					}
					delete pDocument;
					continue;
				}
				delete pDocument;
			}
		}
		break;
	}
	return((nThread == nThreads) ? TRUE : FALSE);
}
BOOL CTCProceduresMonitorItem::SetReleaseConstraints(LPCTSTR pszThread, LPCTSTR pszStep, LPCTSTR pszFunction, INT nEntry, LPCTSTR pszInterlock, CONST CTimeSpan &tTimeWindow)
{
	INT  nItem;
	INT  nItems;
	CString  szItem;
	CStringTools  cStringTools;
	CStringArray  szReleaseItems;

	for (nItem = 0, nItems = (INT)m_szReleaseItems.GetSize(), szReleaseItems.Copy(m_szReleaseItems), szItem = CString(pszThread) + TAB + CString(pszStep) + TAB + cStringTools.ConvertIntToString(nEntry) + TAB + CString(pszFunction) + TAB; nItem < nItems; nItem++)
	{
		if (!szReleaseItems.GetAt(nItem).Left(szItem.GetLength()).Compare(szItem))
		{
			if (lstrlen(pszInterlock) > 0 || tTimeWindow.GetTotalSeconds() > 0)
			{
				szReleaseItems.SetAt(nItem, szItem + pszInterlock + TAB + cStringTools.ConvertLongIntToString(tTimeWindow.GetTotalSeconds()));
				break;
			}
			szReleaseItems.RemoveAt(nItem);
			break;
		}
	}
	if (nItem == nItems)
	{
		if (lstrlen(pszInterlock) > 0 || tTimeWindow > 0)
		{
			szReleaseItems.Add(szItem + pszInterlock + TAB + cStringTools.ConvertLongIntToString(tTimeWindow.GetTotalSeconds()));
			return SetReleaseConstraints(szReleaseItems);
		}
		return FALSE;
	}
	return SetReleaseConstraints(szReleaseItems);
}

INT CTCProceduresMonitorItem::GetReleaseConstraints(CStringArray &szItems) CONST
{
	szItems.Copy(m_szReleaseItems);
	return((INT)szItems.GetSize());
}
BOOL CTCProceduresMonitorItem::GetReleaseConstraints(LPCTSTR pszThread, LPCTSTR pszStep, LPCTSTR pszFunction, INT nEntry, CString &szInterlock, CTimeSpan &tTimeWindow) CONST
{
	INT  nPos;
	INT  nItem;
	INT  nItems;
	CString  szItem;
	CStringTools  cStringTools;

	for (nItem = 0, nItems = (INT)m_szReleaseItems.GetSize(), szItem = CString(pszThread) + TAB + CString(pszStep) + TAB + cStringTools.ConvertIntToString(nEntry) + TAB + CString(pszFunction) + TAB, szInterlock.Empty(), tTimeWindow = 0; nItem < nItems; nItem++)
	{
		if (m_szReleaseItems.GetAt(nItem).Left(szItem.GetLength()) == szItem)
		{
			szItem = m_szReleaseItems.GetAt(nItem).Mid(szItem.GetLength());
			if ((nPos = szItem.Find(TAB)) >= 0)
			{
				szInterlock = szItem.Left(nPos);
				tTimeWindow = _ttoi64(szItem.Mid(nPos + 1));
				break;
			}
		}
	}
	return((nItem < nItems) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorItem::SetAudition(UINT nType, LPCTSTR pszAudition)
{
	m_szAudition[nType] = pszAudition;
}

CString CTCProceduresMonitorItem::GetAudition(UINT nType) CONST
{
	return m_szAudition[nType];
}

VOID CTCProceduresMonitorItem::EnableAuditionBlinking(UINT nType, BOOL bEnable)
{
	m_bAuditionBlinkFlag[nType] = bEnable;
}

BOOL CTCProceduresMonitorItem::IsAuditionBlinkingEnabled(UINT nType) CONST
{
	return m_bAuditionBlinkFlag[nType];
}

VOID CTCProceduresMonitorItem::SetAuditionColor(UINT nType, COLORREF nColor)
{
	m_nAuditionColor[nType] = nColor;
}

COLORREF CTCProceduresMonitorItem::GetAuditionColor(UINT nType) CONST
{
	return m_nAuditionColor[nType];
}

VOID CTCProceduresMonitorItem::SetNotifications(UINT nType, CONST CStringArray &szNotifications)
{
	m_szNotifications[nType].Copy(szNotifications);
}

INT CTCProceduresMonitorItem::GetNotifications(UINT nType, CStringArray &szNotifications) CONST
{
	szNotifications.Copy(m_szNotifications[nType]);
	return((INT)szNotifications.GetSize());
}

VOID CTCProceduresMonitorItem::EnableAcknowledgment(UINT nType, BOOL bEnable)
{
	m_bAcknowledgmentFlag[nType] = bEnable;
}

BOOL CTCProceduresMonitorItem::IsAcknowledgmentEnabled(UINT nType) CONST
{
	return m_bAcknowledgmentFlag[nType];
}

VOID CTCProceduresMonitorItem::SetAcknowledgmentColor(UINT nType, COLORREF nColor)
{
	m_nAcknowledgmentColor[nType] = nColor;
}

COLORREF CTCProceduresMonitorItem::GetAcknowledgmentColor(UINT nType) CONST
{
	return m_nAcknowledgmentColor[nType];
}

BOOL CTCProceduresMonitorItem::AddAuthorizableTelecommand(CONST CTCItem *pTCItem)
{
	CTCItem  *pItem;

	if ((pItem = new CTCItem))
	{
		if (pItem->Copy(pTCItem))
		{
			m_pAuthorizableTCItems.InsertAt(m_pAuthorizableTCItems.GetSize(), pItem, 1);
			return TRUE;
		}
		delete pItem;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItem::EnumAuthorizableTelecommands(CTCItems &pTCItems) CONST
{
	return((pTCItems.Copy(&m_pAuthorizableTCItems) && pTCItems.GetSize() > 0) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorItem::HasAuthorizableTelecommands() CONST
{
	return((m_pAuthorizableTCItems.GetSize() > 0) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorItem::AuthorizeTelecommands(CONST CTCItems &pTCItems)
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	CTCItem  *pTCItem[2];

	for (nItem = 0, nItems = (INT)pTCItems.GetSize(); nItem < nItems; nItem++)
	{
		if ((pTCItem[0] = pTCItems.GetAt(nItem)) && pTCItem[0]->GetAuthorizationStatus() != TCITEM_AUTHORIZATIONSTATUS_NONE)
		{
			if ((pTCItem[1] = m_pAuthorizableTCItems.GetAt((nIndex = m_pAuthorizableTCItems.Find(pTCItem[0])))))
			{
				m_pAuthorizableTCItems.RemoveAt(nIndex);
				delete pTCItem[1];
				continue;
			}
			break;
		}
		nItem = nItems - 1;
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

INT CTCProceduresMonitorItem::AddAlertMessage(LPCTSTR pszAlert)
{
	return AddAlertMessage(TCPROCEDURESMONITORITEM_ALERTTYPE_INFORMATIONAL, pszAlert);
}
INT CTCProceduresMonitorItem::AddAlertMessage(UINT nType, LPCTSTR pszAlert)
{
	CTimeTag  tAlert;

	return AddAlertMessage(nType, pszAlert, tAlert);
}
INT CTCProceduresMonitorItem::AddAlertMessage(UINT nType, LPCTSTR pszAlert, CONST CTimeTag &tAlert)
{
	INT  nIndex;

	for (nIndex = (INT)(m_nAlertMessageTypes.GetSize() - 1); nIndex >= 0; nIndex--)
	{
		if (m_nAlertMessageTypes.GetAt(nIndex) != TCPROCEDURESMONITORITEM_ALERTTYPE_AUTHORIZATION) break;
		continue;
	}
	m_nAlertMessageTypes.InsertAt(nIndex + 1, nType);
	m_szAlertMessages.InsertAt(nIndex + 1, pszAlert);
	m_tAlertMessages.InsertAt(nIndex + 1, tAlert);
	return TRUE;
}

CString CTCProceduresMonitorItem::GetAlertMessage() CONST
{
	UINT  nType;
	CString  szAlert;
	CTimeTag  tAlert;

	return((GetAlertMessage(nType, szAlert, tAlert)) ? szAlert : EMPTYSTRING);
}
BOOL CTCProceduresMonitorItem::GetAlertMessage(UINT &nType, CString &szAlert) CONST
{
	CTimeTag  tAlert;

	return GetAlertMessage(nType, szAlert, tAlert);
}
BOOL CTCProceduresMonitorItem::GetAlertMessage(UINT &nType, CString &szAlert, CTimeTag &tAlert) CONST
{
	if (m_nAlertMessageTypes.GetSize() > 0 && m_szAlertMessages.GetSize() > 0 && m_tAlertMessages.GetSize() > 0)
	{
		nType = m_nAlertMessageTypes.GetAt((INT)m_nAlertMessageTypes.GetUpperBound());
		szAlert = m_szAlertMessages.GetAt((INT)m_szAlertMessages.GetUpperBound());
		tAlert = m_tAlertMessages.GetAt((INT)m_tAlertMessages.GetUpperBound());
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItem::RemoveAlertMessage()
{
	if (m_nAlertMessageTypes.GetSize() > 0 && m_szAlertMessages.GetSize() > 0 && m_tAlertMessages.GetSize() > 0)
	{
		m_nAlertMessageTypes.RemoveAt((INT)m_nAlertMessageTypes.GetUpperBound());
		m_szAlertMessages.RemoveAt((INT)m_szAlertMessages.GetUpperBound());
		m_tAlertMessages.RemoveAt((INT)m_tAlertMessages.GetUpperBound());
		return TRUE;
	}
	return FALSE;
}

VOID CTCProceduresMonitorItem::RemoveAllAlertMessages()
{
	m_nAlertMessageTypes.RemoveAll();
	m_szAlertMessages.RemoveAll();
	m_tAlertMessages.RemoveAll();
}

VOID CTCProceduresMonitorItem::Alert(BOOL bEnable)
{
	m_bAlerted = bEnable;
}

BOOL CTCProceduresMonitorItem::IsAlerted() CONST
{
	return m_bAlerted;
}

VOID CTCProceduresMonitorItem::Enable(BOOL bEnable)
{
	m_bEnabled = bEnable;
}

BOOL CTCProceduresMonitorItem::IsEnabled() CONST
{
	return m_bEnabled;
}

VOID CTCProceduresMonitorItem::SetRunningState(UINT nState)
{
	m_nRunningState = nState;
}

UINT CTCProceduresMonitorItem::GetRunningState() CONST
{
	return m_nRunningState;
}

BOOL CTCProceduresMonitorItem::Copy(CONST CTCProceduresMonitorItem *pItem, BOOL bAll)
{
	INT  nAlertType;
	INT  nAlertTypes;

	for (nAlertType = 0, nAlertTypes = TCPROCEDURESMONITORITEM_ALERTTYPES, m_szName = pItem->m_szName, m_nID = pItem->m_nID, m_nFlags = pItem->m_nFlags, m_nTriggerType = pItem->m_nTriggerType, m_tTriggerTime[0] = pItem->m_tTriggerTime[0], m_tTriggerTime[1] = pItem->m_tTriggerTime[1], m_tTriggerTime[2] = pItem->m_tTriggerTime[2], m_tDailyTriggerTime = pItem->m_tDailyTriggerTime, m_tTriggerInterval = pItem->m_tTriggerInterval, m_szTriggerEvent = pItem->m_szTriggerEvent, m_nTriggerCount = pItem->m_nTriggerCount, m_nExecutionMode = pItem->m_nExecutionMode, m_bManualExecution = pItem->m_bManualExecution, m_bExecutionBreaks = pItem->m_bExecutionBreaks, m_szReleaseItems.Copy(pItem->m_szReleaseItems), m_pArguments.Copy(&pItem->m_pArguments), m_bEnabled = pItem->m_bEnabled; nAlertType < nAlertTypes; nAlertType++)
	{
		m_szAudition[nAlertType] = pItem->m_szAudition[nAlertType];
		m_nAuditionColor[nAlertType] = pItem->m_nAuditionColor[nAlertType];
		m_bAuditionBlinkFlag[nAlertType] = pItem->m_bAuditionBlinkFlag[nAlertType];
		m_szNotifications[nAlertType].Copy(pItem->m_szNotifications[nAlertType]);
		m_bAcknowledgmentFlag[nAlertType] = pItem->m_bAcknowledgmentFlag[nAlertType];
		m_nAcknowledgmentColor[nAlertType] = pItem->m_nAcknowledgmentColor[nAlertType];
	}
	if (bAll)
	{
		m_nRunningState = pItem->m_nRunningState;
		m_bTriggerEvent = pItem->m_bTriggerEvent;
		m_nExecutionCount = pItem->m_nExecutionCount;
		m_tExecutionTime[0] = pItem->m_tExecutionTime[0];
		m_tExecutionTime[1] = pItem->m_tExecutionTime[1];
		m_pAuthorizableTCItems.Copy(&pItem->m_pAuthorizableTCItems);
		m_nAlertMessageTypes.Copy(pItem->m_nAlertMessageTypes);
		m_szAlertMessages.Copy(pItem->m_szAlertMessages);
		m_tAlertMessages.Copy(pItem->m_tAlertMessages);
		m_bAlerted = pItem->m_bAlerted;
	}
	return CDatabaseTCProcedure::Copy(pItem);
}

BOOL CTCProceduresMonitorItem::Compare(CONST CTCProceduresMonitorItem *pItem, BOOL bAll) CONST
{
	INT  nAlertType;
	INT  nAlertTypes;
	INT  nAlertMessage;
	INT  nAlertMessages;
	INT  nReleaseItem[2];
	INT  nReleaseItems[2];
	INT  nNotification[2];
	INT  nNotifications[2];

	for (nAlertType = 0, nAlertTypes = (pItem->m_szName == m_szName && pItem->m_nID == m_nID && pItem->m_nFlags == m_nFlags && pItem->m_nTriggerType == m_nTriggerType && (pItem->m_nTriggerType != TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATTIME || pItem->m_tTriggerTime[0] == m_tTriggerTime[0]) && (pItem->m_nTriggerType != TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATINTERVAL || (pItem->m_tTriggerTime[1] == m_tTriggerTime[1] && pItem->m_tTriggerTime[2] == m_tTriggerTime[2] && pItem->m_tTriggerInterval == m_tTriggerInterval && pItem->m_nTriggerCount == m_nTriggerCount)) && (pItem->m_nTriggerType != TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATDAILYTIME || pItem->m_tDailyTriggerTime == m_tDailyTriggerTime) && (pItem->m_nTriggerType != TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATEVENT || (pItem->m_szTriggerEvent == m_szTriggerEvent && (!bAll || pItem->m_bTriggerEvent == m_bTriggerEvent))) && pItem->m_nExecutionMode == m_nExecutionMode && (!bAll || (pItem->m_tExecutionTime[0] == m_tExecutionTime[0] && pItem->m_tExecutionTime[1] == m_tExecutionTime[1] && pItem->m_nExecutionCount == m_nExecutionCount)) && pItem->m_bManualExecution == m_bManualExecution && pItem->m_bExecutionBreaks == m_bExecutionBreaks && pItem->m_pArguments.Compare(&m_pArguments) && (!bAll || pItem->m_pAuthorizableTCItems.Compare(&m_pAuthorizableTCItems)) && (!bAll || pItem->m_nRunningState == m_nRunningState) && pItem->m_bEnabled == m_bEnabled) ? TCPROCEDURESMONITORITEM_ALERTTYPES : -1; nAlertType < nAlertTypes; nAlertType++)
	{
		for (nReleaseItem[0] = 0, nReleaseItems[0] = (pItem->m_szReleaseItems.GetSize() == m_szReleaseItems.GetSize()) ? (INT)m_szReleaseItems.GetSize() : -1; nReleaseItem[0] < nReleaseItems[0]; nReleaseItem[0]++)
		{
			for (nReleaseItem[1] = 0, nReleaseItems[1] = nReleaseItems[0]; nReleaseItem[1] < nReleaseItems[1]; nReleaseItem[1]++)
			{
				if (pItem->m_szReleaseItems.GetAt(nReleaseItem[0]) == m_szReleaseItems.GetAt(nReleaseItem[1])) break;
				continue;
			}
			if (nReleaseItem[1] == nReleaseItems[1]) break;
		}
		for (nNotification[0] = 0, nNotifications[0] = (pItem->m_szAudition[nAlertType] == m_szAudition[nAlertType] && pItem->m_bAuditionBlinkFlag[nAlertType] == m_bAuditionBlinkFlag[nAlertType] && pItem->m_nAuditionColor[nAlertType] == m_nAuditionColor[nAlertType] && pItem->m_szNotifications[nAlertType].GetSize() == m_szNotifications[nAlertType].GetSize() && pItem->m_bAcknowledgmentFlag[nAlertType] == m_bAcknowledgmentFlag[nAlertType] && pItem->m_nAcknowledgmentColor[nAlertType] == m_nAcknowledgmentColor[nAlertType]) ? (INT)m_szNotifications[nAlertType].GetSize() : -1; nNotification[0] < nNotifications[0]; nNotification[0]++)
		{
			for (nNotification[1] = 0, nNotifications[1] = nNotifications[0]; nNotification[1] < nNotifications[1]; nNotification[1]++)
			{
				if (pItem->m_szNotifications[nAlertType].GetAt(nNotification[0]) == m_szNotifications[nAlertType].GetAt(nNotification[1]))
				{
					if (nNotification[0] != nNotification[1]) break;
					continue;
				}
			}
			if (nNotification[1] == nNotifications[1]) break;
		}
		if (nReleaseItem[0] < nReleaseItems[0] || nReleaseItems[0] < 0 || nNotification[0] < nNotifications[0] || nNotifications[0] < 0) break;
	}
	for (nAlertMessage = 0, nAlertMessages = (bAll) ? ((nAlertType == nAlertTypes && pItem->m_nAlertMessageTypes.GetSize() == m_nAlertMessageTypes.GetSize() && pItem->m_szAlertMessages.GetSize() == m_szAlertMessages.GetSize() && pItem->m_tAlertMessages.GetSize() == m_tAlertMessages.GetSize() && pItem->m_bAlerted == m_bAlerted) ? (INT)m_szAlertMessages.GetSize() : -1) : 0; nAlertMessage < nAlertMessages; nAlertMessage++)
	{
		if (pItem->m_nAlertMessageTypes.GetAt(nAlertMessage) != m_nAlertMessageTypes.GetAt(nAlertMessage) || pItem->m_szAlertMessages.GetAt(nAlertMessage) != m_szAlertMessages.GetAt(nAlertMessage) || pItem->m_tAlertMessages.GetAt(nAlertMessage) != m_tAlertMessages.GetAt(nAlertMessage)) break;
		continue;
	}
	return((nAlertType == nAlertTypes  &&  nAlertMessage == nAlertMessages) ? CDatabaseTCProcedure::Compare(pItem) : FALSE);
}

BOOL CTCProceduresMonitorItem::Map(CByteArray &nInfo) CONST
{
	DATA  sData;
	INT  cbData;
	INT  nAlertType;
	INT  nAlertTypes;
	INT  nReleaseItem;
	INT  nReleaseItems;
	INT  nNotification;
	INT  nNotifications;
	CByteArray  nArgumentsData;
	CByteArray  nReleaseItemsData;
	CByteArray  nNotificationsData[TCPROCEDURESMONITORITEM_ALERTTYPES];

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbTriggerEvent = (m_szTriggerEvent.GetLength() + 1)*sizeof(TCHAR);
	for (nReleaseItem = 0, nReleaseItems = (INT)m_szReleaseItems.GetSize(); nReleaseItem < nReleaseItems; nReleaseItem++)
	{
		nReleaseItemsData.SetSize((cbData = (INT)nReleaseItemsData.GetSize()) + (m_szReleaseItems.GetAt(nReleaseItem).GetLength() + 1)*sizeof(TCHAR));
		CopyMemory(nReleaseItemsData.GetData() + cbData, (LPCTSTR)m_szReleaseItems.GetAt(nReleaseItem), (m_szReleaseItems.GetAt(nReleaseItem).GetLength() + 1)*sizeof(TCHAR));
	}
	for (nAlertType = 0, nAlertTypes = TCPROCEDURESMONITORITEM_ALERTTYPES, sData.cbReleaseItems = (INT)(nReleaseItemsData.GetSize()*sizeof(BYTE)), sData.cbArguments = (m_pArguments.Map(nArgumentsData)) ? (INT)nArgumentsData.GetSize() : -1, sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbTriggerEvent + sData.cbReleaseItems + max(sData.cbArguments, 0); nAlertType < nAlertTypes; nAlertType++)
	{
		for (nNotification = 0, nNotifications = (INT)m_szNotifications[nAlertType].GetSize(), sData.cbAudition[nAlertType] = (m_szAudition[nAlertType].GetLength() + 1)*sizeof(TCHAR), sData.bAuditionBlinkFlag[nAlertType] = m_bAuditionBlinkFlag[nAlertType], sData.nAuditionColor[nAlertType] = m_nAuditionColor[nAlertType], sData.bAcknowledgmentFlag[nAlertType] = m_bAcknowledgmentFlag[nAlertType], sData.nAcknowledgmentColor[nAlertType] = m_nAcknowledgmentColor[nAlertType]; nNotification < nNotifications; nNotification++)
		{
			nNotificationsData[nAlertType].SetSize((cbData = (INT)nNotificationsData[nAlertType].GetSize()) + (m_szNotifications[nAlertType].GetAt(nNotification).GetLength() + 1)*sizeof(TCHAR));
			CopyMemory(nNotificationsData[nAlertType].GetData() + cbData, (LPCTSTR)m_szNotifications[nAlertType].GetAt(nNotification), (m_szNotifications[nAlertType].GetAt(nNotification).GetLength() + 1)*sizeof(TCHAR));
		}
		sData.cbSize += sData.cbAudition[nAlertType];
		sData.cbSize += sData.cbNotifications[nAlertType] = (INT)nNotificationsData[nAlertType].GetSize();
	}
	for (nInfo.SetSize(sData.cbSize), sData.nFlags = m_nFlags, sData.nTriggerType = m_nTriggerType, sData.nTriggerCount = m_nTriggerCount, sData.tTriggerTime[0] = m_tTriggerTime[0].GetTime(), sData.tTriggerTime[1] = m_tTriggerTime[1].GetTime(), sData.tTriggerTime[2] = m_tTriggerTime[2].GetTime(), sData.tDailyTriggerTime = m_tDailyTriggerTime.GetTotalSeconds(), sData.tTriggerInterval = m_tTriggerInterval.GetTotalSeconds(), sData.nExecutionMode = m_nExecutionMode, sData.tExecutionTime[0] = m_tExecutionTime[0].GetTime(), sData.tExecutionTime[1] = m_tExecutionTime[1].GetTime(), sData.nExecutionCount = m_nExecutionCount, sData.bManualExecution = m_bManualExecution, sData.bExecutionBreaks = m_bExecutionBreaks, sData.bEnabled = m_bEnabled; nInfo.GetSize() == sData.cbSize && sData.cbArguments >= 0; )
	{
		for (nAlertType = 0, CopyMemory(nInfo.GetData(), &sData, sizeof(DATA)), CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName), CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szTriggerEvent, sData.cbTriggerEvent), CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbTriggerEvent), nReleaseItemsData.GetData(), sData.cbReleaseItems), CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbReleaseItems), nArgumentsData.GetData(), sData.cbArguments); nAlertType < nAlertTypes; nAlertType++)
		{
			CopyMemory(nInfo.GetData() + (cbData = (nAlertType > 0) ? (cbData + sData.cbNotifications[nAlertType - 1]) : (cbData + sData.cbArguments)), (LPCTSTR)m_szAudition[nAlertType], sData.cbAudition[nAlertType]);
			CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbAudition[nAlertType]), nNotificationsData[nAlertType].GetData(), sData.cbNotifications[nAlertType]);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItem::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;
	INT  cbData;
	INT  nAlertType;
	INT  nAlertTypes;
	INT  cbReleaseItem;
	INT  cbReleaseItems;
	INT  cbNotification;
	INT  cbNotifications;
	CByteArray  nArgumentsData;
	CByteArray  nReleaseItemsData;
	CByteArray  nNotificationsData[TCPROCEDURESMONITORITEM_ALERTTYPES];

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize >= (INT) sizeof(DATA) + sData.cbName + sData.cbTriggerEvent + sData.cbReleaseItems + sData.cbArguments && sData.cbName > 0 && sData.cbTriggerEvent > 0 && sData.cbReleaseItems >= 0 && sData.cbArguments >= 0; )
	{
		for (nReleaseItemsData.SetSize(sData.cbReleaseItems), nArgumentsData.SetSize(sData.cbArguments), CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName)), CopyMemory(m_szTriggerEvent.GetBufferSetLength(STRINGCHARS(sData.cbTriggerEvent)), nInfo.GetData() + (cbData = cbData + sData.cbName), STRINGBYTES(sData.cbTriggerEvent)), CopyMemory(nReleaseItemsData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbTriggerEvent), sData.cbReleaseItems), CopyMemory(nArgumentsData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbReleaseItems), sData.cbArguments), m_szName.ReleaseBuffer(), m_szTriggerEvent.ReleaseBuffer(), m_szReleaseItems.RemoveAll(), cbReleaseItems = 0; cbReleaseItems < nReleaseItemsData.GetSize(); cbReleaseItems += cbReleaseItem)
		{
			m_szReleaseItems.Add((LPCTSTR)(nReleaseItemsData.GetData() + cbReleaseItems));
			cbReleaseItem = (m_szReleaseItems.GetAt(m_szReleaseItems.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR);
		}
		for (nAlertType = 0, nAlertTypes = TCPROCEDURESMONITORITEM_ALERTTYPES; nAlertType < nAlertTypes && (nAlertType > 0 || m_pArguments.Unmap(nArgumentsData)) && sData.cbAudition[nAlertType] > 0 && sData.cbNotifications[nAlertType] >= 0; nAlertType++)
		{
			for (nNotificationsData[nAlertType].SetSize(sData.cbNotifications[nAlertType]), CopyMemory(m_szAudition[nAlertType].GetBufferSetLength(STRINGCHARS(sData.cbAudition[nAlertType])), nInfo.GetData() + (cbData = (nAlertType > 0) ? (cbData + sData.cbNotifications[nAlertType - 1]) : (cbData + sData.cbArguments)), STRINGBYTES(sData.cbAudition[nAlertType])), m_bAuditionBlinkFlag[nAlertType] = sData.bAuditionBlinkFlag[nAlertType], m_nAuditionColor[nAlertType] = sData.nAuditionColor[nAlertType], CopyMemory(nNotificationsData[nAlertType].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbAudition[nAlertType]), sData.cbNotifications[nAlertType]), m_bAcknowledgmentFlag[nAlertType] = sData.bAcknowledgmentFlag[nAlertType], m_nAcknowledgmentColor[nAlertType] = sData.nAcknowledgmentColor[nAlertType], m_szAudition[nAlertType].ReleaseBuffer(), cbNotifications = 0, m_szNotifications[nAlertType].RemoveAll(); cbNotifications < nNotificationsData[nAlertType].GetSize(); cbNotifications += cbNotification)
			{
				m_szNotifications[nAlertType].Add((LPCTSTR)(nNotificationsData[nAlertType].GetData() + cbNotifications));
				cbNotification = (m_szNotifications[nAlertType].GetAt(m_szNotifications[nAlertType].GetUpperBound()).GetLength() + 1)*sizeof(TCHAR);
			}
		}
		m_nFlags = sData.nFlags;
		m_bEnabled = sData.bEnabled;
		m_nTriggerType = sData.nTriggerType;
		m_tTriggerTime[0] = sData.tTriggerTime[0];
		m_tTriggerTime[1] = sData.tTriggerTime[1];
		m_tTriggerTime[2] = sData.tTriggerTime[2];
		m_tDailyTriggerTime = sData.tDailyTriggerTime;
		m_tTriggerInterval = sData.tTriggerInterval;
		m_nTriggerCount = sData.nTriggerCount;
		m_nExecutionMode = sData.nExecutionMode;
		m_tExecutionTime[0] = sData.tExecutionTime[0];
		m_tExecutionTime[1] = sData.tExecutionTime[1];
		m_nExecutionCount = sData.nExecutionCount;
		m_bManualExecution = sData.bManualExecution;
		m_bExecutionBreaks = sData.bExecutionBreaks;
		return((nAlertType == nAlertTypes) ? TRUE : FALSE);
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItems

CTCProceduresMonitorItems::CTCProceduresMonitorItems() : CPtrArray()
{
	return;
}

CTCProceduresMonitorItems::~CTCProceduresMonitorItems()
{
	RemoveAll();
}

INT CTCProceduresMonitorItems::Add(CTCProceduresMonitorItem *pItem)
{
	return((INT)CPtrArray::Add(pItem));
}

CTCProceduresMonitorItem *CTCProceduresMonitorItems::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCProceduresMonitorItem *)CPtrArray::GetAt(nIndex) : (CTCProceduresMonitorItem *)NULL);
}

CTCProceduresMonitorItem *CTCProceduresMonitorItems::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCProceduresMonitorItem *)CPtrArray::GetAt(nIndex) : (CTCProceduresMonitorItem *)NULL);
}

VOID CTCProceduresMonitorItems::RemoveAll()
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

BOOL CTCProceduresMonitorItems::Copy(CONST CTCProceduresMonitorItems *pItems)
{
	INT  nItem;
	INT  nItems;
	CTCProceduresMonitorItem  *pItem;

	for (nItem = 0, nItems = (INT)pItems->GetSize(), RemoveAll(); nItem < nItems; nItem++)
	{
		if ((pItem = new CTCProceduresMonitorItem))
		{
			pItem->Copy(pItems->GetAt(nItem));
			InsertAt(nItem, pItem, 1);
			continue;
		}
		break;
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorItems::Compare(CONST CTCProceduresMonitorItems *pItems) CONST
{
	INT  nItem[2];
	INT  nItems[2];

	for (nItem[0] = 0, nItems[0] = (INT)GetSize(), nItems[1] = (INT)pItems->GetSize(); nItem[0] < nItems[0]; nItem[0]++)
	{
		for (nItem[1] = (nItems[0] != nItems[1]) ? nItems[1] : 0; nItem[1] < nItems[1]; nItem[1]++)
		{
			if (pItems->GetAt(nItem[0])->Compare(GetAt(nItem[1]))) break;
			continue;
		}
		if (nItem[1] == nItems[1]) break;
	}
	return((nItem[0] == nItems[0] && nItems[0] == nItems[1]) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorItems::Map(CByteArray &nInfo) CONST
{
	INT  nItem;
	INT  nItems;
	CByteArray  nItemData;
	CTCProceduresMonitorItem  *pItem;

	for (nItem = 0, nItems = (INT)GetSize(), nInfo.RemoveAll(); nItem < nItems; nItem++)
	{
		if ((pItem = GetAt(nItem)) && pItem->Map(nItemData) && nInfo.Append(nItemData) >= 0) continue;
		break;
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorItems::Unmap(CONST CByteArray &nInfo)
{
	INT  cbItem;
	INT  cbItems;
	CByteArray  nItemData;
	CTCProceduresMonitorItem  *pItem;

	for (cbItems = 0, RemoveAll(); cbItems < nInfo.GetSize(); cbItems += cbItem)
	{
		for (CopyMemory(&cbItem, nInfo.GetData() + cbItems, sizeof(cbItem)), nItemData.SetSize(max(min(cbItem, nInfo.GetSize() - cbItems), 0)); nItemData.GetSize() >= 0; )
		{
			CopyMemory(nItemData.GetData(), nInfo.GetData() + cbItems, nItemData.GetSize());
			break;
		}
		if ((pItem = new CTCProceduresMonitorItem))
		{
			if (pItem->Unmap(nItemData) && Add(pItem) >= 0) continue;
			delete pItem;
		}
		break;
	}
	return((cbItems == nInfo.GetSize()) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemThread

IMPLEMENT_DYNAMIC(CTCProceduresMonitorItemThread, CThread)

CTCProceduresMonitorItemThread::CTCProceduresMonitorItemThread(CONST CTCProceduresMonitorItem *pItem) : CThread()
{
	m_nTCProcedureID = -1;
	m_nTCProcedureStepID = -1;
	m_bTCProcedureStepInto = FALSE;
	m_bTCProcedureStepOver = FALSE;
	m_bTCProcedureStepOut = FALSE;
	m_bTCProcedureStepBreak = FALSE;
	m_bTCProcedureLineBreak = FALSE;
	m_bTCProcedureBreak = FALSE;
	m_bTCProcedureDirty = FALSE;
	m_bTCProcedureExit = FALSE;
	m_szTCProcedureStep.Empty();
	m_hTCProcedureCode = (HINSTANCE)NULL;
	m_pTCProceduresMonitorWnd = (CTCProceduresMonitorWnd *)NULL;
	m_pTCProcessEngine = (CTCProcessEngine *)NULL;
	m_pTCEnvironment = (CTCEnvironment *)NULL;
	m_cItem[0].Copy(pItem);
	m_bStartup = TRUE;
}

CTCProceduresMonitorItemThread::~CTCProceduresMonitorItemThread()
{
	Stop();
}

BOOL CTCProceduresMonitorItemThread::Start(CTCProceduresMonitorWnd *pTCProceduresMonitorWnd, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, BOOL bStartup)
{
	for (m_pTCProceduresMonitorWnd = pTCProceduresMonitorWnd, m_pTCProcessEngine = pTCProcessEngine, m_pTCEnvironment = pTCEnvironment, m_hTCProcedureEvents.RemoveAll(), m_bStartup = bStartup; m_cItem[0].GetID() >= 0; )
	{
		m_hTCProcedureEvents.Add((HANDLE)m_bAbort);
		m_bUpdate.ResetEvent();
		m_bAbort.ResetEvent();
		return CreateThread((LPVOID)NULL, THREAD_PRIORITY_ABOVE_NORMAL);
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemThread::Stop(BOOL bWait)
{
	return(((!bWait  &&  SetEvent(m_hObject)) || (bWait  &&  DestroyThread() >= 0)) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorItemThread::Update(CONST CTCProceduresMonitorItem *pItem)
{
	INT  nThread;
	INT  nThreads;
	CDatabaseTCProcedureThread  *pThread;
	CDatabaseTCProcedureThreadBreakpoints  pBreakpoints;
	CDisplayLock  cLock(this);

	for (nThread = 0, nThreads = (IsProcedureRunning()) ? (INT)pItem->GetSize() : 0; nThread < nThreads; nThread++)
	{
		if ((pThread = pItem->GetAt(nThread)) && pThread->GetBreakpoints(pBreakpoints) >= 0)
		{
			UpdateThreadBreakpoints(pThread->GetName(), pBreakpoints);
			continue;
		}
	}
	return((pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_MANUAL) ? ((!IsProcedureRunning() && m_cItem[1].Copy(&m_cItem[0]) && m_cItem[0].Copy(pItem) && m_bUpdate.SetEvent()) || (IsProcedureRunning() && m_cItem[0].Copy(pItem))) : (m_cItem[0].Copy(pItem) && m_bUpdate.SetEvent()));
}
BOOL CTCProceduresMonitorItemThread::Update(CONST CTMEnvironment *pTMEnvironment)
{
	CString  szProcedure;
	BOOL(__cdecl *pUpdate)(INT nID, CONST CTMEnvironment *pTMEnvironment);
	CDisplayLock  cLock(this);

	if (IsProcedureRunning())
	{
#ifndef UNICODE
		szProcedure = STRING(IDS_EXPORTINTERFACE_UPDATETCPROCEDURE);
#else
		WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_UPDATETCPROCEDURE), -1, (LPSTR)szProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_UPDATETCPROCEDURE))), lstrlen(STRING(IDS_EXPORTINTERFACE_UPDATETCPROCEDURE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
		szProcedure.ReleaseBuffer();
#endif
		return(((pUpdate = (BOOL(__cdecl *)(INT nID, CONST CTMEnvironment *pTMEnvironment)) GetProcAddress(m_hTCProcedureCode, (LPCSTR)(LPCTSTR)szProcedure))) ? (*pUpdate)(m_nTCProcedureID, pTMEnvironment) : FALSE);
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemThread::Refresh()
{
	CDisplayLock  cLock(this);

	return UpdateProcedure(&m_cItem[2]);
}

BOOL CTCProceduresMonitorItemThread::Suspend()
{
	CDisplayLock  cLock(this);

	return SuspendProcedure(&m_cItem[2]);
}

BOOL CTCProceduresMonitorItemThread::Resume(BOOL bAuto)
{
	CDisplayLock  cLock(this);

	return ResumeProcedure(&m_cItem[2], bAuto);
}

BOOL CTCProceduresMonitorItemThread::Abort()
{
	return m_bAbort.SetEvent();
}

BOOL CTCProceduresMonitorItemThread::Reset()
{
	INT  nThread;
	INT  nThreads;
	CUIntArray  nStates;
	CStringArray  szSteps;
	CDisplayLock  cLock(this);

	for (nThread = 0, nThreads = (INT)m_cItem[2].GetSize(), m_bTCProcedureDirty = FALSE; nThread < nThreads; nThread++)
	{
		m_pTCProceduresMonitorWnd->UpdateProcedure(m_cItem[2].GetID(), m_cItem[2].GetTriggerType(), TCPROCEDURE_RUNNINGSTATE_NOTRUNNING, nThread, 0, szSteps, nStates, 0);
		continue;
	}
	return TRUE;
}

BOOL CTCProceduresMonitorItemThread::CanReset() CONST
{
	return m_bTCProcedureDirty;
}

BOOL CTCProceduresMonitorItemThread::CheckExecution(INT nProcedureID) CONST
{
	CDisplayLock  cLock(this);

	return((IsProcedureRunning()) ? (m_nTCProcedureID == nProcedureID || nProcedureID == -1) : FALSE);
}
BOOL CTCProceduresMonitorItemThread::CheckExecution(INT nProcedureID, CString &szSubRoutine) CONST
{
	INT  nProcedure;
	INT  nProcedures;
	CPtrArray  hProcedures;
	CUIntArray  nProcedureIDs;
	CStringArray  szProcedureNames;
	CDisplayLock  cLock(this);

	if (IsProcedureRunning())
	{
		for (nProcedure = 0, nProcedures = (!CheckExecution(nProcedureID)) ? m_pTCEnvironment->EnumTCProcedures(szProcedureNames, nProcedureIDs, hProcedures) : -1, szSubRoutine.Empty(); nProcedure < nProcedures; nProcedure++)
		{
			if (nProcedureIDs.GetAt(nProcedure) == nProcedureID)
			{
				szSubRoutine = szProcedureNames.GetAt(nProcedure);
				break;
			}
		}
		return((nProcedure < nProcedures || nProcedures < 0) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemThread::StepIntoExecutionBlock(INT nThreadID)
{
	UINT  nLine;
	UINT  nState;
	CUIntArray  nStates;
	CStringArray  szSteps;
	CDatabaseTCProcedureThread  *pThread;
	CDisplayLock  cLock(this);

	if ((pThread = (m_bTCProcedureStepBreak) ? m_cItem[2].GetAt(nThreadID) : (CDatabaseTCProcedureThread *)NULL) && CheckThreadState(pThread->GetName(), nState, szSteps, nStates, nLine))
	{
		m_szTCProcedureStep = (szSteps.GetSize() > 0) ? szSteps.GetAt(szSteps.GetUpperBound()) : EMPTYSTRING;
		m_nTCProcedureStepID = nThreadID;
		m_bTCProcedureStepInto = TRUE;
		m_bTCProcedureStepOver = FALSE;
		m_bTCProcedureStepOut = FALSE;
		Resume();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemThread::CanStepIntoExecutionBlock(INT nThreadID) CONST
{
	INT  nStep;
	INT  nSteps;
	UINT  nLine;
	UINT  nState;
	CPtrArray  pSteps;
	CUIntArray  nStates;
	CStringArray  szSteps;
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pStep;
	CDatabaseTCProcedureThread  *pThread;
	CDisplayLock  cLock(this);

	if (IsProcedureRunning() && IsProcedureSuspended())
	{
		if ((pDocument = ((pThread = (m_bTCProcedureStepBreak) ? m_cItem[2].GetAt(nThreadID) : (CDatabaseTCProcedureThread *)NULL) && CheckThreadState(pThread->GetName(), nState, szSteps, nStates, nLine)) ? new CTCProcedureDocument : (CTCProcedureDocument *)NULL))
		{
			for (nStep = 0, nSteps = (pDocument->Unmap(pThread)) ? pDocument->EnumSteps(pSteps, FALSE, TRUE) : 0; nStep < nSteps; nStep++)
			{
				if ((pStep = (CTCProcedureDocumentItem *)pSteps.GetAt(nStep)) && pStep->GetName() == szSteps.GetAt(szSteps.GetUpperBound()))
				{
					nStep = (!pStep->GetSubSteps()->GetStepCount()) ? nSteps : nStep;
					break;
				}
			}
			delete pDocument;
			return((nStep < nSteps) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemThread::StepOverExecutionBlock(INT nThreadID)
{
	UINT  nLine;
	UINT  nState;
	CUIntArray  nStates;
	CStringArray  szSteps;
	CDatabaseTCProcedureThread  *pThread;
	CDisplayLock  cLock(this);

	if ((pThread = (m_bTCProcedureStepBreak) ? m_cItem[2].GetAt(nThreadID) : (CDatabaseTCProcedureThread *)NULL) && CheckThreadState(pThread->GetName(), nState, szSteps, nStates, nLine))
	{
		m_szTCProcedureStep = (szSteps.GetSize() > 0) ? szSteps.GetAt(szSteps.GetUpperBound()) : EMPTYSTRING;
		m_nTCProcedureStepID = nThreadID;
		m_bTCProcedureStepInto = FALSE;
		m_bTCProcedureStepOver = TRUE;
		m_bTCProcedureStepOut = FALSE;
		Resume();
		return TRUE;
	}
	if (m_bTCProcedureLineBreak)
	{
		m_bTCProcedureStepInto = FALSE;
		m_bTCProcedureStepOver = TRUE;
		m_bTCProcedureStepOut = FALSE;
		Resume();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemThread::CanStepOverExecutionBlock(INT nThreadID) CONST
{
	INT  nStep;
	INT  nSteps;
	UINT  nLine;
	UINT  nState;
	CPtrArray  pSteps;
	CUIntArray  nStates;
	CStringArray  szSteps;
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pStep;
	CDatabaseTCProcedureThread  *pThread;
	CDisplayLock  cLock(this);

	if (IsProcedureRunning() && IsProcedureSuspended())
	{
		if ((pDocument = ((pThread = (m_bTCProcedureStepBreak) ? m_cItem[2].GetAt(nThreadID) : (CDatabaseTCProcedureThread *)NULL) && CheckThreadState(pThread->GetName(), nState, szSteps, nStates, nLine)) ? new CTCProcedureDocument : (CTCProcedureDocument *)NULL))
		{
			for (nStep = 0, nSteps = (pDocument->Unmap(pThread)) ? pDocument->EnumSteps(pSteps, FALSE, TRUE) : 0; nStep < nSteps; nStep++)
			{
				if ((pStep = (CTCProcedureDocumentItem *)pSteps.GetAt(nStep)) && pStep->GetName() == szSteps.GetAt(szSteps.GetUpperBound()))
				{
					nStep = (!pDocument->GetNextStep(pStep)) ? nSteps : nStep;
					break;
				}
			}
			delete pDocument;
			return((nStep < nSteps) ? TRUE : FALSE);
		}
		return m_bTCProcedureLineBreak;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemThread::StepOutExecutionBlock(INT nThreadID)
{
	UINT  nLine;
	UINT  nState;
	CUIntArray  nStates;
	CStringArray  szSteps;
	CDatabaseTCProcedureThread  *pThread;
	CDisplayLock  cLock(this);

	if ((pThread = (m_bTCProcedureStepBreak) ? m_cItem[2].GetAt(nThreadID) : (CDatabaseTCProcedureThread *)NULL) && CheckThreadState(pThread->GetName(), nState, szSteps, nStates, nLine))
	{
		m_szTCProcedureStep = (szSteps.GetSize() > 0) ? szSteps.GetAt(szSteps.GetUpperBound()) : EMPTYSTRING;
		m_nTCProcedureStepID = nThreadID;
		m_bTCProcedureStepInto = FALSE;
		m_bTCProcedureStepOver = FALSE;
		m_bTCProcedureStepOut = TRUE;
		Resume();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemThread::CanStepOutExecutionBlock(INT nThreadID) CONST
{
	INT  nStep;
	INT  nSteps;
	UINT  nLine;
	UINT  nState;
	CPtrArray  pSteps;
	CUIntArray  nStates;
	CStringArray  szSteps;
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pStep;
	CDatabaseTCProcedureThread  *pThread;
	CDisplayLock  cLock(this);

	if (IsProcedureRunning() && IsProcedureSuspended())
	{
		if ((pDocument = ((pThread = (m_bTCProcedureStepBreak) ? m_cItem[2].GetAt(nThreadID) : (CDatabaseTCProcedureThread *)NULL) && CheckThreadState(pThread->GetName(), nState, szSteps, nStates, nLine)) ? new CTCProcedureDocument : (CTCProcedureDocument *)NULL))
		{
			for (nStep = 0, nSteps = (pDocument->Unmap(pThread)) ? pDocument->EnumSteps(pSteps, FALSE, TRUE) : 0; nStep < nSteps; nStep++)
			{
				if ((pStep = (CTCProcedureDocumentItem *)pSteps.GetAt(nStep)) && pStep->GetName() == szSteps.GetAt(szSteps.GetUpperBound()))
				{
					nStep = (pDocument->FindStep(pStep, FALSE)) ? nSteps : nStep;
					break;
				}
			}
			delete pDocument;
			return((nStep < nSteps) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemThread::IsRunning() CONST
{
	CDisplayLock  cLock(this);

	return IsProcedureRunning();
}

BOOL CTCProceduresMonitorItemThread::IsSuspended() CONST
{
	CDisplayLock  cLock(this);

	return IsProcedureSuspended();
}

int CTCProceduresMonitorItemThread::Run()
{
	INT  nID[2];
	INT  nThread;
	INT  nThreads;
	INT  nIdentifier;
	INT  nIdentifiers;
	UINT  nThreadLine;
	UINT  nCycleCount;
	UINT  nTriggerType;
	BOOL  bTermination;
	DWORD  dwWaitCode;
	DWORD  dwTimeout;
	CString  szItem;
	CString  szMessage;
	CString  szFailure;
	CString  szMessageType;
	CString  szProcedure[5];
	CTimeKey  tTime[4];
	CPtrArray  hEvents;
	CTimeSpan  tInterval;
	HINSTANCE  hInstance;
	CPtrArray  pIdentifiers;
	CUIntArray  nThreadStepStates;
	CUIntArray  nIdentifierTypes;
	CStringArray  szThreadStepNames;
	CStringArray  szErrorParameters;
	CStringArray  szIdentifiers;
	CTMParameter  *pTMParameter;
	CTMParameters  pTMParameters;
	CLongUIntArray  nIdentifierAttributes;
	CDatabaseTMParameter  *pParameter;
	CDatabaseTCProcedureThread  *pThread;
	CDatabaseTCProcedureArguments  pArguments;
	CDatabaseTCProcedureThreadBreakpoints  pBreakpoints;
	BOOL(__cdecl *pInitialize)(CONST CDatabaseEngine *pDatabase, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, LPCTSTR pszName, INT nProcedureID, INT nID, UINT nExecutionMode, BOOL bSynchronized, CONST CPtrArray &hEvents, CStringArray &szErrorParameters);
	BOOL(__cdecl *pInitializeParameters)(INT nID, CONST CTMParameters &pTMParameters, double fTotalTMBandwidth, double fAvailableTMBandwidth, double fMaxDiagnosticTMBandwidth, double fAvailableDiagnosticTMBandwidth, CONST CTimeTag &tTMBandwidth);
	INT(__cdecl *pEnumIdentifiers)(INT nID, CStringArray &szIdentifiers, CUIntArray &nIdentifierTypes, CLongUIntArray &nIdentifierAttributes, CPtrArray &pIdentifiers);
	BOOL(__cdecl *pStart)(INT nID, CONST CDatabaseTCProcedureArguments &pArguments, UINT nExecutionMode);
	BOOL(__cdecl *pCheckSourceCodeVersion)(LPCTSTR pszSourceCode);

	do
	{
		for (dwTimeout = INFINITE; Lock(); )
		{
			if (!m_cItem[2].Copy(&m_cItem[0]))
			{
				m_cItem[2].SetID(-1);
				Unlock();
				break;
			}
			for (tTime[0] = CTime::GetCurrentTime().GetTime(), tTime[1] = m_cItem[2].GetExecutionStartTime(); tTime[1] < 0; )
			{
				tTime[1] = -tTime[1].GetTime();
				break;
			}
			m_cItem[0].EnableTriggerEvent(FALSE);
			Unlock();
			break;
		}
		if (m_cItem[2].GetID() >= 0)
		{
			if (m_cItem[2].GetTriggerType() != TCPROCEDURESMONITORITEM_TRIGGERTYPE_NONE  &&  m_cItem[2].IsEnabled())
			{
				if (((m_cItem[2].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_IMMEDIATELY || m_cItem[2].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_AUTOMATIC) && m_cItem[2].GetExecutionStartTime() == 0) || (m_cItem[2].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATSTARTUP  &&  m_bStartup) || (m_cItem[2].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_MANUAL  &&  !m_bStartup) || (m_cItem[2].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATTIME  &&  m_cItem[2].GetTriggerTime() > tTime[1] && m_cItem[2].GetTriggerTime() <= tTime[0]) || (m_cItem[2].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATDAILYTIME  &&  tTime[0].GetTime() / SECONDSPERDAY > tTime[1].GetTime() / SECONDSPERDAY  &&  m_cItem[2].GetDailyTriggerTime().GetTotalSeconds() % SECONDSPERDAY <= tTime[0].GetTime() % SECONDSPERDAY) || (m_cItem[2].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATINTERVAL && ((m_cItem[2].GetTriggerInterval(tTime[2], tInterval) && tTime[0] >= tTime[2] && (tTime[1].GetTime() - tTime[2].GetTime()) / tInterval.GetTotalSeconds() < (tTime[0].GetTime() - tTime[2].GetTime()) / tInterval.GetTotalSeconds()) || (m_cItem[2].GetTriggerInterval(tTime[2], tInterval, nCycleCount) && tTime[0] >= tTime[2] && (tTime[0].GetTime() - tTime[2].GetTime()) / tInterval.GetTotalSeconds() < nCycleCount && (tTime[1].GetTime() - tTime[2].GetTime()) / tInterval.GetTotalSeconds() < (tTime[0].GetTime() - tTime[2].GetTime()) / tInterval.GetTotalSeconds()) || (m_cItem[2].GetTriggerInterval(tTime[2], tInterval, tTime[3]) && tTime[0] >= tTime[2] && tTime[2].GetTime() + tInterval.GetTotalSeconds()*((tTime[0].GetTime() - tTime[2].GetTime()) / tInterval.GetTotalSeconds()) <= tTime[3].GetTime() && (tTime[1].GetTime() - tTime[2].GetTime()) / tInterval.GetTotalSeconds() < (tTime[0].GetTime() - tTime[2].GetTime()) / tInterval.GetTotalSeconds()))) || (m_cItem[2].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATEVENT  &&  m_cItem[2].IsTriggerEventEnabled()))
				{
					if ((nID[0] = m_pTCEnvironment->LoadTCProcedure(GetDatabase(), m_cItem[2].GetName(), FALSE, hInstance, hEvents)) >= 0)
					{
						for (nThread = 0, nThreads = (INT)m_cItem[2].GetSize(), m_nTCProcedureID = nID[0], m_szTCProcedureStep.Empty(), m_nTCProcedureStepID = -1, m_bTCProcedureStepInto = m_bTCProcedureStepOver = m_bTCProcedureStepOut = FALSE, m_bTCProcedureStepBreak = m_bTCProcedureLineBreak = FALSE, m_bTCProcedureBreak = FALSE, m_bTCProcedureDirty = FALSE, m_bTCProcedureExit = FALSE, m_hTCProcedureCode = hInstance, m_hTCProcedureEvents.InsertAt(TCPROCEDURESMONITORITEMTHREAD_EVENT_UPDATE, hEvents.GetAt(hEvents.GetSize() - TCPROCEDUREPROCESS_EVENTTYPES + TCPROCEDUREPROCESS_EVENTTYPE_UPDATE)), m_hTCProcedureEvents.InsertAt(TCPROCEDURESMONITORITEMTHREAD_EVENT_EXIT, hEvents.GetAt(hEvents.GetSize() - TCPROCEDUREPROCESS_EVENTTYPES + TCPROCEDUREPROCESS_EVENTTYPE_EXIT)), m_nTCProcedureLines.RemoveAll(), m_nTCProcedureLines.SetSize(nThreads), m_cItem[2].GetArguments(pArguments), szThreadStepNames.RemoveAll(), nThreadStepStates.RemoveAll(), nThreadLine = 0; nThread < nThreads; nThread++)
						{
							m_pTCProceduresMonitorWnd->UpdateProcedure(m_cItem[2].GetID(), m_cItem[2].GetTriggerType(), TCPROCEDURE_RUNNINGSTATE_NOTRUNNING, nThread, 0, szThreadStepNames, nThreadStepStates, nThreadLine);
							continue;
						}
#ifndef UNICODE
						szProcedure[0] = STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDURE);
						szProcedure[1] = STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDUREPARAMETERS);
						szProcedure[2] = STRING(IDS_EXPORTINTERFACE_STARTTCPROCEDURE);
						szProcedure[3] = STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDURESOURCECODEVERSION);
						szProcedure[4] = STRING(IDS_EXPORTINTERFACE_ENUMTCPROCEDUREIDENTIFIERS);
#else
						WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDURE), -1, (LPSTR)szProcedure[0].GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDURE))), lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDURE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
						WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDUREPARAMETERS), -1, (LPSTR)szProcedure[1].GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDUREPARAMETERS))), lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDUREPARAMETERS)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
						WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_STARTTCPROCEDURE), -1, (LPSTR)szProcedure[2].GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_STARTTCPROCEDURE))), lstrlen(STRING(IDS_EXPORTINTERFACE_STARTTCPROCEDURE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
						WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDURESOURCECODEVERSION), -1, (LPSTR)szProcedure[3].GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDURESOURCECODEVERSION))), lstrlen(STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDURESOURCECODEVERSION)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
						WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_ENUMTCPROCEDUREIDENTIFIERS), -1, (LPSTR)szProcedure[4].GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_ENUMTCPROCEDUREIDENTIFIERS))), lstrlen(STRING(IDS_EXPORTINTERFACE_ENUMTCPROCEDUREIDENTIFIERS)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
						szProcedure[0].ReleaseBuffer();
						szProcedure[1].ReleaseBuffer();
						szProcedure[2].ReleaseBuffer();
						szProcedure[3].ReleaseBuffer();
						szProcedure[4].ReleaseBuffer();
#endif
						if ((pCheckSourceCodeVersion = (BOOL(__cdecl *)(LPCTSTR pszSourceCode)) GetProcAddress(hInstance, (LPCSTR)(LPCTSTR)szProcedure[3])) && (*pCheckSourceCodeVersion)(m_cItem[2].GetPrecompiledCode()))
						{
							if ((pInitialize = (BOOL(__cdecl *)(CONST CDatabaseEngine *pDatabase, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, LPCTSTR pszName, INT nProcedureID, INT nID, UINT nExecutionMode, BOOL bSynchronized, CONST CPtrArray &hEvents, CStringArray &szErrorParameters)) GetProcAddress(hInstance, (LPCSTR)(LPCTSTR)szProcedure[0])) && (*pInitialize)(GetDatabase(), m_pTCProcessEngine, m_pTCEnvironment, m_cItem[2].GetName(), -1, nID[0], -1, TRUE, hEvents, szErrorParameters))
							{
								if ((pEnumIdentifiers = (INT(__cdecl *)(INT nID, CStringArray &szIdentifiers, CUIntArray &nIdentifierTypes, CLongUIntArray &nIdentifierAttributes, CPtrArray &pIdentifiers)) GetProcAddress(hInstance, (LPCSTR)(LPCTSTR)szProcedure[4])) && (*pEnumIdentifiers)(nID[0], szIdentifiers, nIdentifierTypes, nIdentifierAttributes, pIdentifiers) >= 0)
								{
									for (nIdentifier = 0, nIdentifiers = (INT)szIdentifiers.GetSize(), pTMParameters.RemoveAll(); nIdentifier < nIdentifiers; nIdentifier++)
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
									if ((pInitializeParameters = (nIdentifier == nIdentifiers  &&  InitializeTMData(pTMParameters)) ? (BOOL(__cdecl *)(INT nID, CONST CTMParameters &pTMParameters, double fTotalTMBandwidth, double fAvailableTMBandwidth, double fMaxDiagnosticTMBandwidth, double fAvailableDiagnosticTMBandwidth, CONST CTimeTag &tTMBandwidth)) GetProcAddress(hInstance, (LPCSTR)(LPCTSTR)szProcedure[1]) : (BOOL(__cdecl *)(INT nID, CONST CTMParameters &pTMParameters, double fTotalTMBandwidth, double fAvailableTMBandwidth, double fMaxDiagnosticTMBandwidth, double fAvailableDiagnosticTMBandwidth, CONST CTimeTag &tTMBandwidth)) NULL) && (*pInitializeParameters)(nID[0], pTMParameters, GetTMService()->GetTotalTMBandwidth(), GetTMService()->GetAvailableTMBandwidth(), GetTMService()->GetMaxDiagnosticTMBandwidth(), GetTMService()->GetAvailableDiagnosticTMBandwidth(), GetTMService()->GetLastTMBandwidthMeasurementTime()))
									{
										for (nThread = 0, nThreads = (INT)m_cItem[2].GetSize(); nThread < nThreads; nThread++)
										{
											if ((pThread = m_cItem[2].GetAt(nThread)) && pThread->GetBreakpoints(pBreakpoints) >= 0)
											{
												UpdateThreadBreakpoints(pThread->GetName(), pBreakpoints);
												continue;
											}
										}
										if ((pStart = (BOOL(__cdecl *)(INT nID, CONST CDatabaseTCProcedureArguments &pArguments, UINT nExecutionMode)) GetProcAddress(hInstance, (LPCSTR)(LPCTSTR)szProcedure[2])) != (BOOL(__cdecl *)(INT nID, CONST CDatabaseTCProcedureArguments &pArguments, UINT nExecutionMode)) NULL && (*pStart)(nID[0], pArguments, m_cItem[2].GetExecutionMode()))
										{
											for (m_cItem[2].SetExecutionStartTime(CTime::GetCurrentTime().GetTime()), m_cItem[2].SetExecutionEndTime(0), m_cItem[2].SetExecutionCount(m_cItem[2].GetExecutionCount() + 1), m_pTCProceduresMonitorWnd->UpdateProcedure(m_cItem[2].GetID(), m_cItem[2].GetTriggerType(), TCPROCEDURE_RUNNINGSTATE_RUNNING, m_cItem[2].GetExecutionStartTime(), m_cItem[2].GetExecutionEndTime(), m_cItem[2].GetExecutionCount()); (dwWaitCode = Wait((LPHANDLE)m_hTCProcedureEvents.GetData(), (DWORD)m_hTCProcedureEvents.GetSize(), FALSE)) != WAIT_OBJECT_0 && dwWaitCode != WAIT_FAILED; )
											{
												if (dwWaitCode == WAIT_OBJECT_0 + TCPROCEDURESMONITORITEMTHREAD_EVENT_UPDATE + 1)
												{
													UpdateProcedure(&m_cItem[2]);
													continue;
												}
												if (dwWaitCode == WAIT_OBJECT_0 + TCPROCEDURESMONITORITEMTHREAD_EVENT_EXIT + 1)
												{
													for (UpdateProcedure(&m_cItem[2]), bTermination = TerminateProcedure(&m_cItem[2]); !bTermination; )
													{
														UpdateProcedure(&m_cItem[2]);
														break;
													}
													if (!bTermination) continue;
													break;
												}
												AbortProcedure(&m_cItem[2]);
												break;
											}
											for (Lock(), m_hTCProcedureEvents.RemoveAt(0, TCPROCEDURESMONITORITEMTHREAD_EVENTS), m_bStartup = FALSE; m_cItem[2].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_MANUAL; )
											{
												m_cItem[0].Copy(&m_cItem[1]);
												m_cItem[1].SetID(-1);
												break;
											}
											for (nID[1] = m_cItem[0].GetID(), nTriggerType = m_cItem[0].GetTriggerType(), m_cItem[0].SetExecutionStartTime((tTime[0] = m_cItem[2].GetExecutionStartTime())), m_cItem[0].SetExecutionEndTime((tTime[1] = CTime::GetCurrentTime().GetTime())), m_cItem[0].SetExecutionCount((nCycleCount = m_cItem[2].GetExecutionCount())), Unlock(); TRUE; )
											{
												m_pTCProceduresMonitorWnd->UpdateProcedure(nID[1], nTriggerType, TCPROCEDURE_RUNNINGSTATE_NOTRUNNING, tTime[0], tTime[1], nCycleCount);
												break;
											}
											m_nTCProcedureID = -1;
											m_hTCProcedureCode = (HINSTANCE)NULL;
											m_bUpdate.SetEvent();
											continue;
										}
									}
								}
							}
							szFailure = STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGE_STARTFAILURE);
							m_hTCProcedureEvents.RemoveAt(0, TCPROCEDURESMONITORITEMTHREAD_EVENTS);
						}
						else  szFailure = STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGE_VERSIONFAILURE);
					}
					else  szFailure = STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGE_LOADFAILURE);
					for (m_pTCProceduresMonitorWnd->AlertProcedure(m_cItem[2].GetID(), TCPROCEDURESMONITORITEM_ALERTTYPE_ERROR, szFailure), Lock(), m_bStartup = FALSE; m_cItem[2].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_MANUAL; )
					{
						m_cItem[0].Copy(&m_cItem[1]);
						m_cItem[1].SetID(-1);
						break;
					}
					if (nID[0] >= 0)
					{
						m_pTCEnvironment->FreeTCProcedure(nID[0]);
						m_hTCProcedureCode = (HINSTANCE)NULL;
						m_nTCProcedureID = -1;
					}
					dwTimeout = INFINITE;
					Unlock();
					continue;
				}
				if (m_cItem[2].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATTIME  &&  m_cItem[2].GetTriggerTime() > tTime[1]) dwTimeout = (tTime[0] < m_cItem[2].GetTriggerTime()) ? (DWORD)(1000 * min(m_cItem[2].GetTriggerTime().GetTime() - tTime[0].GetTime(), SECONDSPERDAY)) : 0;
				if (m_cItem[2].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATDAILYTIME) dwTimeout = (tTime[0].GetTime() % SECONDSPERDAY <= m_cItem[2].GetDailyTriggerTime().GetTotalSeconds() % SECONDSPERDAY) ? (DWORD)(1000 * (m_cItem[2].GetDailyTriggerTime().GetTotalSeconds() % SECONDSPERDAY - tTime[0].GetTime() % SECONDSPERDAY)) : (DWORD)(1000 * (SECONDSPERDAY - tTime[0].GetTime() % SECONDSPERDAY + m_cItem[2].GetDailyTriggerTime().GetTotalSeconds() % SECONDSPERDAY));
				if (m_cItem[2].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATINTERVAL && (m_cItem[2].GetTriggerInterval(tTime[2], tInterval) || (m_cItem[2].GetTriggerInterval(tTime[2], tInterval, nCycleCount) && (tTime[0] <= tTime[2] || (tTime[0].GetTime() - tTime[2].GetTime()) / tInterval.GetTotalSeconds() < nCycleCount - 1)) || (m_cItem[2].GetTriggerInterval(tTime[2], tInterval, tTime[3]) && (tTime[0] <= tTime[2] || tTime[2].GetTime() + tInterval.GetTotalSeconds()*((tTime[0].GetTime() - tTime[2].GetTime()) / tInterval.GetTotalSeconds() + 1) <= tTime[3].GetTime())))) dwTimeout = ((tTime[3] = (tTime[0] > tTime[2]) ? (tTime[2].GetTime() + tInterval.GetTotalSeconds()*((tTime[0].GetTime() - tTime[2].GetTime()) / tInterval.GetTotalSeconds() + 1)) : tTime[2].GetTime()) > tTime[0]) ? (DWORD)(1000 * min(tTime[3].GetTime() - tTime[0].GetTime(), SECONDSPERDAY)) : 0;
			}
		}
		for (Lock(), m_bStartup = FALSE; m_cItem[2].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_MANUAL; )
		{
			m_cItem[0].Copy(&m_cItem[1]);
			m_cItem[1].SetID(-1);
			break;
		}
		Unlock();
	} while ((dwWaitCode = Wait(m_bUpdate, FALSE, dwTimeout)) == WAIT_OBJECT_0 + 1 || dwWaitCode == WAIT_TIMEOUT);
	return 0;
}

BOOL CTCProceduresMonitorItemThread::SuspendProcedure(CONST CTCProceduresMonitorItem *pItem)
{
	CString  szProcedure;
	BOOL(__cdecl *pSuspend)(INT nID);

	if (IsProcedureRunning())
	{
		if (!HasProcedureDialogs(pItem))
		{
#ifndef UNICODE
			szProcedure = STRING(IDS_EXPORTINTERFACE_SUSPENDTCPROCEDURE);
#else
			WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_SUSPENDTCPROCEDURE), -1, (LPSTR)szProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_SUSPENDTCPROCEDURE))), lstrlen(STRING(IDS_EXPORTINTERFACE_SUSPENDTCPROCEDURE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
			szProcedure.ReleaseBuffer();
#endif
			if ((pSuspend = (BOOL(__cdecl *)(INT nID)) GetProcAddress(m_hTCProcedureCode, (LPCSTR)(LPCTSTR)szProcedure)) && (*pSuspend)(-(INT)m_nTCProcedureID))
			{
				m_bTCProcedureBreak = TRUE;
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemThread::UpdateProcedure(CONST CTCProceduresMonitorItem *pItem)
{
	INT  nStep;
	INT  nSteps;
	INT  nThread;
	INT  nThreads;
	INT  nTrigger;
	INT  nTriggers;
	INT  nBreakpoint;
	INT  nBreakpoints;
	BOOL  bSuspend[3];
	UINT  nThreadLine;
	UINT  nThreadState;
	UINT  nSubThreadID[2];
	CString  szProcedure[2];
	CPtrArray  pThreadSteps;
	CUIntArray  nThreadTriggers;
	CUIntArray  nThreadStepStates;
	CStringArray  szThreadTriggers;
	CStringArray  szThreadStepNames;
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pStep;
	CDatabaseTCProcedureThread  *pThread;
	CDatabaseTCProcedureThreadBreakpoint  *pBreakpoint;
	CDatabaseTCProcedureThreadBreakpoints  pBreakpoints;
	INT(__cdecl *pCheckThreadExecutionState)(INT nID, LPCTSTR pszThread, UINT &nState, CStringArray &szStepNames, CUIntArray &nStepStates, UINT &nLine);
	BOOL(__cdecl *pAcknowledgeThreadExecutionState)(INT nID, LPCTSTR pszThread);

	if (IsProcedureRunning())
	{
		if (!IsProcedureStopping())
		{
#ifndef UNICODE
			szProcedure[0] = STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDURETHREADEXECUTIONSTATE);
			szProcedure[1] = STRING(IDS_EXPORTINTERFACE_ACKNOWLEDGETCPROCEDURETHREADEXECUTIONSTATE);
#else
			WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDURETHREADEXECUTIONSTATE), -1, (LPSTR)szProcedure[0].GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDURETHREADEXECUTIONSTATE))), lstrlen(STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDURETHREADEXECUTIONSTATE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
			WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_ACKNOWLEDGETCPROCEDURETHREADEXECUTIONSTATE), -1, (LPSTR)szProcedure[1].GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_ACKNOWLEDGETCPROCEDURETHREADEXECUTIONSTATE))), lstrlen(STRING(IDS_EXPORTINTERFACE_ACKNOWLEDGETCPROCEDURETHREADEXECUTIONSTATE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
			szProcedure[0].ReleaseBuffer();
			szProcedure[1].ReleaseBuffer();
#endif
			if ((pCheckThreadExecutionState = (INT(__cdecl *)(INT nID, LPCTSTR pszThread, UINT &nState, CStringArray &szStepNames, CUIntArray &nStepStates, UINT &nLine)) GetProcAddress(m_hTCProcedureCode, (LPCSTR)(LPCTSTR)szProcedure[0])))
			{
				if ((pAcknowledgeThreadExecutionState = (BOOL(__cdecl *)(INT nID, LPCTSTR pszThread)) GetProcAddress(m_hTCProcedureCode, (LPCSTR)(LPCTSTR)szProcedure[1])))
				{
					for (nThread = 0, nThreads = (INT)pItem->GetSize(), bSuspend[0] = FALSE, bSuspend[1] = TRUE, bSuspend[2] = FALSE; nThread < nThreads; nThread++)
					{
						if ((pThread = (CDatabaseTCProcedureThread *)pItem->GetAt(nThread)) != (CDatabaseTCProcedureThread *)NULL)
						{
							if ((*pCheckThreadExecutionState)(m_nTCProcedureID, pThread->GetName(), nThreadState, szThreadStepNames, nThreadStepStates, nThreadLine) >= 0)
							{
								for (m_pTCProceduresMonitorWnd->UpdateProcedure(pItem->GetID(), nThread, nThreadState, szThreadStepNames, nThreadStepStates, nThreadLine); (pDocument = (((m_nTCProcedureStepID == nThread && szThreadStepNames.GetSize() > 0 && szThreadStepNames.GetAt(szThreadStepNames.GetUpperBound()) != m_szTCProcedureStep && m_bTCProcedureStepBreak) || (m_nTCProcedureLines.GetAt(nThread) != nThreadLine && m_bTCProcedureLineBreak)) && (nThreadState & TCPROCEDURETHREAD_RUNNINGSTATE_RUNNING)) ? new CTCProcedureDocument : (CTCProcedureDocument *)NULL); )
								{
									for (nStep = 0, nSteps = (!m_szTCProcedureStep.IsEmpty() && szThreadStepNames.GetSize() > 0 && pDocument->Unmap(pThread)) ? pDocument->EnumSteps(pThreadSteps, FALSE, TRUE) : 0, nSubThreadID[0] = nSubThreadID[1] = (UINT)-1; nStep < nSteps; nStep++)
									{
										if ((pStep = (CTCProcedureDocumentItem *)pThreadSteps.GetAt(nStep)))
										{
											if (pStep->GetName() == m_szTCProcedureStep)
											{
												nSubThreadID[0] = pStep->GetSubThreadID();
												if (nSubThreadID[1] != (UINT)-1) break;
												continue;
											}
											if (pStep->GetName() == szThreadStepNames.GetAt(szThreadStepNames.GetUpperBound()))
											{
												nSubThreadID[1] = pStep->GetSubThreadID();
												if (nSubThreadID[0] != (UINT)-1) break;
												continue;
											}
										}
									}
									if ((m_bTCProcedureStepInto  &&  nSubThreadID[0] < nSubThreadID[1]) || (m_bTCProcedureStepOver  &&  nSubThreadID[0] == nSubThreadID[1]) || (m_bTCProcedureStepOut  &&  nSubThreadID[0] > nSubThreadID[1]))
									{
										if ((m_bTCProcedureLineBreak  &&  m_nTCProcedureLines.GetAt(nThread) != nThreadLine) || (m_bTCProcedureStepBreak  &&  nSubThreadID[0] != (UINT)-1 && nSubThreadID[1] != (UINT)-1))
										{
											m_bTCProcedureStepInto = FALSE;
											m_bTCProcedureStepOver = FALSE;
											m_bTCProcedureStepOut = FALSE;
											m_szTCProcedureStep.Empty();
											m_nTCProcedureStepID = -1;
											bSuspend[0] = TRUE;
										}
									}
									delete pDocument;
									break;
								}
								for (bSuspend[1] = (nThreadState & TCPROCEDURETHREAD_RUNNINGSTATE_RUNNING) ? FALSE : bSuspend[1], bSuspend[2] = (nThreadState & TCPROCEDURETHREAD_RUNNINGSTATE_STOPPED) ? TRUE : bSuspend[2]; szThreadStepNames.GetSize() > 0 && (nThreadStepStates.GetAt(nThreadStepStates.GetUpperBound()) & TCPROCEDURETHREADSTEP_STATE_TRIGGER_RUNNING); )
								{
									szThreadTriggers.Add(szThreadStepNames.GetAt(szThreadStepNames.GetUpperBound()));
									nThreadTriggers.Add(nThread);
									break;
								}
								for (m_nTCProcedureLines.SetAt(nThread, nThreadLine), m_bTCProcedureDirty = TRUE; !bSuspend[0]; )
								{
									(*pAcknowledgeThreadExecutionState)(m_nTCProcedureID, pThread->GetName());
									break;
								}
							}
						}
					}
					for (m_pTCProceduresMonitorWnd->UpdateProcedure(pItem->GetID(), pItem->GetTriggerType(), (bSuspend[0] || (bSuspend[1] && bSuspend[2])) ? TCPROCEDURE_RUNNINGSTATE_STOPPED : TCPROCEDURE_RUNNINGSTATE_RUNNING); bSuspend[0]; )
					{
						SuspendProcedure(pItem);
						break;
					}
					if (bSuspend[0] || (bSuspend[1] && bSuspend[2]))
					{
						for (nThread = 0; nThread < nThreads; nThread++)
						{
							if ((pThread = pItem->GetAt(nThread)) && pThread->GetBreakpoints(pBreakpoints) > 0)
							{
								for (nBreakpoint = 0, nBreakpoints = (INT)pBreakpoints.GetSize(); nBreakpoint < nBreakpoints; nBreakpoint++)
								{
									if ((pBreakpoint = pBreakpoints.GetAt(nBreakpoint)) && !pBreakpoint->GetLocation().IsEmpty())
									{
										for (nTrigger = 0, nTriggers = (INT)nThreadTriggers.GetSize(); nTrigger < nTriggers; nTrigger++)
										{
											if (nThreadTriggers.GetAt(nTrigger) == nThread) break;
											continue;
										}
										if (nTrigger < nTriggers  &&  pBreakpoint->GetLocation() == szThreadTriggers.GetAt(nTrigger)) break;
									}
								}
								if (nBreakpoint < nBreakpoints) break;
							}
						}
						if ((!m_bTCProcedureStepBreak  &&  !m_bTCProcedureLineBreak) || nThread < nThreads)
						{
							m_bTCProcedureStepBreak = (nThread < nThreads) ? TRUE : FALSE;
							m_bTCProcedureLineBreak = !m_bTCProcedureStepBreak;
						}
						m_bTCProcedureBreak = TRUE;
						return TRUE;
					}
					m_bTCProcedureBreak = FALSE;
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemThread::ResumeProcedure(CONST CTCProceduresMonitorItem *pItem, BOOL bAuto)
{
	CString  szProcedure;
	BOOL(__cdecl *pResume)(INT nID, BOOL bAuto);

	if (IsProcedureRunning())
	{
#ifndef UNICODE
		szProcedure = STRING(IDS_EXPORTINTERFACE_RESUMETCPROCEDURE);
#else
		WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_RESUMETCPROCEDURE), -1, (LPSTR)szProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_RESUMETCPROCEDURE))), lstrlen(STRING(IDS_EXPORTINTERFACE_RESUMETCPROCEDURE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
		szProcedure.ReleaseBuffer();
#endif
		if ((pResume = (BOOL(__cdecl *)(INT nID, BOOL bAuto)) GetProcAddress(m_hTCProcedureCode, (LPCSTR)(LPCTSTR)szProcedure)) && (*pResume)(-(INT)m_nTCProcedureID, bAuto))
		{
			m_bTCProcedureBreak = FALSE;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemThread::TerminateProcedure(CONST CTCProceduresMonitorItem *pItem)
{
	INT  nThread;
	INT  nThreads;
	HANDLE  hEvent[2];
	CString  szProcedure;
	CUIntArray  nThreadStepStates;
	CStringArray  szThreadStepNames;
	BOOL(__cdecl *pTerminate)(INT nID, BOOL bAuto);

	if (IsProcedureRunning())
	{
		if (!IsProcedureStopping())
		{
#ifndef UNICODE
			szProcedure = STRING(IDS_EXPORTINTERFACE_TERMINATETCPROCEDURE);
			m_bTCProcedureExit = TRUE;
#else
			WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_TERMINATETCPROCEDURE), -1, (LPSTR)szProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_TERMINATETCPROCEDURE))), lstrlen(STRING(IDS_EXPORTINTERFACE_TERMINATETCPROCEDURE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
			szProcedure.ReleaseBuffer();
			m_bTCProcedureExit = TRUE;
#endif
			if ((pTerminate = (BOOL(__cdecl *)(INT nID, BOOL bAuto)) GetProcAddress(m_hTCProcedureCode, (LPCSTR)(LPCTSTR)szProcedure)) && (*pTerminate)(m_nTCProcedureID, FALSE))
			{
				for (hEvent[0] = m_pTCEnvironment->SignalTCFunctionQueue(TRUE), hEvent[1] = m_pTCEnvironment->SignalMessageQueue(TRUE); Wait(0) == WAIT_TIMEOUT; )
				{
					if (WaitForMultipleObjects(sizeof(hEvent) / sizeof(HANDLE), hEvent, TRUE, 0) != WAIT_TIMEOUT) break;
					continue;
				}
				for (nThread = 0, nThreads = (INT)pItem->GetSize(); nThread < nThreads; nThread++)
				{
					m_pTCProceduresMonitorWnd->UpdateProcedure(pItem->GetID(), pItem->GetTriggerType(), TCPROCEDURE_RUNNINGSTATE_NOTRUNNING, nThread, TCPROCEDURETHREAD_RUNNINGSTATE_NOTRUNNING, szThreadStepNames, nThreadStepStates, -1);
					continue;
				}
				if (m_pTCEnvironment->FreeTCProcedure(m_nTCProcedureID))
				{
					m_hTCProcedureCode = (HINSTANCE)NULL;
					m_bTCProcedureExit = FALSE;
					m_nTCProcedureID = -1;
					return TRUE;
				}
			}
			m_bTCProcedureExit = FALSE;
		}
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemThread::AbortProcedure(CONST CTCProceduresMonitorItem *pItem)
{
	INT  nThread;
	INT  nThreads;
	HANDLE  hEvent[2];
	CString  szProcedure;
	CUIntArray  nThreadStepStates;
	CStringArray  szThreadStepNames;
	BOOL(__cdecl *pAbort)(INT nID);

	if (IsProcedureRunning())
	{
		if (!IsProcedureStopping())
		{
#ifndef UNICODE
			szProcedure = STRING(IDS_EXPORTINTERFACE_ABORTTCPROCEDURE);
			m_bTCProcedureExit = TRUE;
#else
			WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_ABORTTCPROCEDURE), -1, (LPSTR)szProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_ABORTTCPROCEDURE))), lstrlen(STRING(IDS_EXPORTINTERFACE_ABORTTCPROCEDURE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
			szProcedure.ReleaseBuffer();
			m_bTCProcedureExit = TRUE;
#endif
			if ((pAbort = (BOOL(__cdecl *)(INT nID)) GetProcAddress(m_hTCProcedureCode, (LPCSTR)(LPCTSTR)szProcedure)) && (*pAbort)(m_nTCProcedureID))
			{
				for (hEvent[0] = m_pTCEnvironment->SignalTCFunctionQueue(TRUE), hEvent[1] = m_pTCEnvironment->SignalMessageQueue(TRUE); Wait(0) == WAIT_TIMEOUT; )
				{
					if (WaitForMultipleObjects(sizeof(hEvent) / sizeof(HANDLE), hEvent, TRUE, 0) != WAIT_TIMEOUT) break;
					continue;
				}
				for (nThread = 0, nThreads = (INT)pItem->GetSize(); nThread < nThreads; nThread++)
				{
					m_pTCProceduresMonitorWnd->UpdateProcedure(pItem->GetID(), pItem->GetTriggerType(), TCPROCEDURE_RUNNINGSTATE_NOTRUNNING, nThread, TCPROCEDURETHREAD_RUNNINGSTATE_NOTRUNNING | TCPROCEDURETHREAD_ACTIONSTATE_ABORT, szThreadStepNames, nThreadStepStates, -1);
					continue;
				}
				if (m_pTCEnvironment->FreeTCProcedure(m_nTCProcedureID))
				{
					m_hTCProcedureCode = (HINSTANCE)NULL;
					m_bTCProcedureExit = FALSE;
					m_nTCProcedureID = -1;
					return TRUE;
				}
			}
			m_bTCProcedureExit = FALSE;
		}
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemThread::HasProcedureDialogs(CONST CTCProceduresMonitorItem *pItem) CONST
{
	INT  nThread;
	INT  nThreads;
	CString  szProcedure;
	CDatabaseTCProcedureThread  *pThread;
	BOOL(__cdecl *pHasThreadOpenDialogs)(INT nID, LPCTSTR pszThread);

	if (IsProcedureRunning())
	{
#ifndef UNICODE
		szProcedure = STRING(IDS_EXPORTINTERFACE_HASTCPROCEDURETHREADOPENDIALOGS);
#else
		WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_HASTCPROCEDURETHREADOPENDIALOGS), -1, (LPSTR)szProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_HASTCPROCEDURETHREADOPENDIALOGS))), lstrlen(STRING(IDS_EXPORTINTERFACE_HASTCPROCEDURETHREADOPENDIALOGS)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
		szProcedure.ReleaseBuffer();
#endif
		if ((pHasThreadOpenDialogs = (BOOL(__cdecl *)(INT nID, LPCTSTR pszThread)) GetProcAddress(m_hTCProcedureCode, (LPCSTR)(LPCTSTR)szProcedure)))
		{
			for (nThread = 0, nThreads = (INT)pItem->GetSize(); nThread < nThreads; nThread++)
			{
				if ((pThread = pItem->GetAt(nThread)) != (CDatabaseTCProcedureThread *)NULL)
				{
					if ((*pHasThreadOpenDialogs)(m_nTCProcedureID, pThread->GetName())) break;
					continue;
				}
			}
			return((nThread < nThreads) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemThread::IsProcedureRunning() CONST
{
	return((m_nTCProcedureID >= 0) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorItemThread::IsProcedureSuspended() CONST
{
	CString  szProcedure;
	BOOL(__cdecl *pIsSuspended)(INT nID);

	if (!m_bTCProcedureBreak)
	{
#ifndef UNICODE
		szProcedure = STRING(IDS_EXPORTINTERFACE_ISSUSPENDEDTCPROCEDURE);
#else
		WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_ISSUSPENDEDTCPROCEDURE), -1, (LPSTR)szProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_ISSUSPENDEDTCPROCEDURE))), lstrlen(STRING(IDS_EXPORTINTERFACE_ISSUSPENDEDTCPROCEDURE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
		szProcedure.ReleaseBuffer();
#endif
		if ((pIsSuspended = (BOOL(__cdecl *)(INT nID)) GetProcAddress(m_hTCProcedureCode, (LPCSTR)(LPCTSTR)szProcedure))) return((*pIsSuspended)(-(INT)m_nTCProcedureID));
		return FALSE;
	}
	return TRUE;
}

BOOL CTCProceduresMonitorItemThread::IsProcedureStopping() CONST
{
	return m_bTCProcedureExit;
}

BOOL CTCProceduresMonitorItemThread::UpdateThreadBreakpoints(LPCTSTR pszThread, CONST CDatabaseTCProcedureThreadBreakpoints &pBreakpoints)
{
	CString  szProcedure;
	BOOL(__cdecl *pUpdateBreakpoints)(INT nID, LPCTSTR pszThread, CONST CDatabaseTCProcedureThreadBreakpoints &pBreakpoints);

	if (IsProcedureRunning())
	{
#ifndef UNICODE
		szProcedure = STRING(IDS_EXPORTINTERFACE_UPDATETCPROCEDURETHREADBREAKPOINTS);
#else
		WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_UPDATETCPROCEDURETHREADBREAKPOINTS), -1, (LPSTR)szProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_UPDATETCPROCEDURETHREADBREAKPOINTS))), lstrlen(STRING(IDS_EXPORTINTERFACE_UPDATETCPROCEDURETHREADBREAKPOINTS)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
		szProcedure.ReleaseBuffer();
#endif
		if ((pUpdateBreakpoints = (BOOL(__cdecl *)(INT nID, LPCTSTR pszThread, CONST CDatabaseTCProcedureThreadBreakpoints &pBreakpoints)) GetProcAddress(m_hTCProcedureCode, (LPCSTR)(LPCTSTR)szProcedure)) && (*pUpdateBreakpoints)(m_nTCProcedureID, pszThread, pBreakpoints)) return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemThread::CheckThreadState(LPCTSTR pszThread, UINT &nState, CStringArray &szSteps, CUIntArray &nStepStates, UINT &nLine) CONST
{
	CString  szProcedure;
	INT(__cdecl *pCheckThreadExecutionState)(INT nID, LPCTSTR pszThread, UINT &nState, CStringArray &szSteps, CUIntArray &nStepStates, UINT &nLine);

	if (IsProcedureRunning())
	{
#ifndef UNICODE
		szProcedure = STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDURETHREADEXECUTIONSTATE);
#else
		WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDURETHREADEXECUTIONSTATE), -1, (LPSTR)szProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDURETHREADEXECUTIONSTATE))), lstrlen(STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDURETHREADEXECUTIONSTATE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
		szProcedure.ReleaseBuffer();
#endif
		if ((pCheckThreadExecutionState = (INT(__cdecl *)(INT nID, LPCTSTR pszThread, UINT &nState, CStringArray &szSteps, CUIntArray &nStepStates, UINT &nLine)) GetProcAddress(m_hTCProcedureCode, (LPCSTR)(LPCTSTR)szProcedure)) && (*pCheckThreadExecutionState)(m_nTCProcedureID, pszThread, nState, szSteps, nStepStates, nLine) >= 0) return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemThread::Lock()
{
	return((m_pTCProceduresMonitorWnd->Lock() && CThread::Lock()) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorItemThread::Unlock()
{
	return((CThread::Unlock() && m_pTCProceduresMonitorWnd->Unlock()) ? TRUE : FALSE);
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorItemThread, CThread)
	//{{AFX_MSG_MAP(CTCProceduresMonitorItemThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorPrintJobInfo

CTCProceduresMonitorPrintJobInfo::CTCProceduresMonitorPrintJobInfo() : CObject()
{
	m_nPrintMode = 0;
	m_nPrintScale = 0;
}

VOID CTCProceduresMonitorPrintJobInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CTCProceduresMonitorPrintJobInfo::GetName() CONST
{
	return m_szName;
}

VOID CTCProceduresMonitorPrintJobInfo::SetProfile(LPCTSTR pszProfile)
{
	m_szProfile = pszProfile;
}

CString CTCProceduresMonitorPrintJobInfo::GetProfile() CONST
{
	return m_szProfile;
}

VOID CTCProceduresMonitorPrintJobInfo::SetComments(LPCTSTR pszComments)
{
	m_szComments = pszComments;
}

CString CTCProceduresMonitorPrintJobInfo::GetComments() CONST
{
	return m_szComments;
}

BOOL CTCProceduresMonitorPrintJobInfo::SetPrintMode(UINT nMode)
{
	m_nPrintMode = nMode;
	return TRUE;
}

UINT CTCProceduresMonitorPrintJobInfo::GetPrintMode() CONST
{
	return m_nPrintMode;
}

BOOL CTCProceduresMonitorPrintJobInfo::SetPrintScale(UINT nScale)
{
	if (m_nPrintMode & TCPROCEDURESMONITOR_PRINT_FIXEDSCALE)
	{
		m_nPrintScale = nScale;
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorPrintJobInfo::GetPrintScale(UINT &nScale) CONST
{
	if (m_nPrintMode & TCPROCEDURESMONITOR_PRINT_FIXEDSCALE)
	{
		nScale = m_nPrintScale;
		return TRUE;
	}
	return FALSE;
}

VOID CTCProceduresMonitorPrintJobInfo::Copy(CONST CTCProceduresMonitorPrintJobInfo *pJobInfo)
{
	m_szName = pJobInfo->m_szName;
	m_szProfile = pJobInfo->m_szProfile;
	m_szComments = pJobInfo->m_szComments;
	m_nPrintMode = pJobInfo->m_nPrintMode;
	m_nPrintScale = pJobInfo->m_nPrintScale;
}

BOOL CTCProceduresMonitorPrintJobInfo::Compare(CONST CTCProceduresMonitorPrintJobInfo *pJobInfo) CONST
{
	return((pJobInfo->m_szName == m_szName  &&  pJobInfo->m_szProfile == m_szProfile  &&  pJobInfo->m_szComments == m_szComments  &&  pJobInfo->m_nPrintMode == m_nPrintMode && (!(m_nPrintMode & TCPROCEDURESMONITOR_PRINT_FIXEDSCALE) || pJobInfo->m_nPrintScale == m_nPrintScale)) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorPrintJobInfo::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbProfile = (m_szProfile.GetLength() + 1)*sizeof(TCHAR);
	sData.cbComments = (m_szComments.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbProfile + sData.cbComments)), sData.nPrintMode = m_nPrintMode, sData.nPrintScale = m_nPrintScale; nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szProfile, sData.cbProfile);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbProfile), (LPCTSTR)m_szComments, sData.cbComments);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorPrintJobInfo::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbProfile + sData.cbComments && sData.cbName > 0 && sData.cbProfile > 0 && sData.cbComments > 0; )
	{
		CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName));
		CopyMemory(m_szProfile.GetBufferSetLength(STRINGCHARS(sData.cbProfile)), nInfo.GetData() + (cbData = cbData + sData.cbName), STRINGBYTES(sData.cbProfile));
		CopyMemory(m_szComments.GetBufferSetLength(STRINGCHARS(sData.cbComments)), nInfo.GetData() + (cbData = cbData + sData.cbProfile), STRINGBYTES(sData.cbComments));
		m_nPrintMode = sData.nPrintMode;
		m_nPrintScale = sData.nPrintScale;
		m_szName.ReleaseBuffer();
		m_szProfile.ReleaseBuffer();
		m_szComments.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorPrintJobs

CTCProceduresMonitorPrintJobs::CTCProceduresMonitorPrintJobs() : CPtrArray()
{
	return;
}

CTCProceduresMonitorPrintJobs::~CTCProceduresMonitorPrintJobs()
{
	RemoveAll();
}

INT CTCProceduresMonitorPrintJobs::Add(CTCProceduresMonitorPrintJobInfo *pJobInfo)
{
	return((INT)CPtrArray::Add(pJobInfo));
}

INT CTCProceduresMonitorPrintJobs::Find(LPCTSTR pszName) CONST
{
	INT  nJob;
	INT  nJobs;
	CTCProceduresMonitorPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = GetAt(nJob)) && pJobInfo->GetName() == pszName) break;
		continue;
	}
	return((nJob < nJobs) ? nJob : -1);
}

CTCProceduresMonitorPrintJobInfo *CTCProceduresMonitorPrintJobs::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCProceduresMonitorPrintJobInfo *)CPtrArray::GetAt(nIndex) : (CTCProceduresMonitorPrintJobInfo *)NULL);
}

CTCProceduresMonitorPrintJobInfo *CTCProceduresMonitorPrintJobs::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCProceduresMonitorPrintJobInfo *)CPtrArray::GetAt(nIndex) : (CTCProceduresMonitorPrintJobInfo *)NULL);
}

VOID CTCProceduresMonitorPrintJobs::RemoveAll()
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

BOOL CTCProceduresMonitorPrintJobs::Copy(CONST CTCProceduresMonitorPrintJobs *pPrintJobs)
{
	INT  nJob;
	INT  nJobs;
	CTCProceduresMonitorPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)pPrintJobs->GetSize(), RemoveAll(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = new CTCProceduresMonitorPrintJobInfo))
		{
			pJobInfo->Copy(pPrintJobs->GetAt(nJob));
			InsertAt(nJob, pJobInfo, 1);
			continue;
		}
		break;
	}
	return((nJob == nJobs) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorPrintJobs::Compare(CONST CTCProceduresMonitorPrintJobs *pPrintJobs) CONST
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

BOOL CTCProceduresMonitorPrintJobs::Map(CByteArray &nInfo) CONST
{
	INT  nJob;
	INT  nJobs;
	CByteArray  nJobData;
	CTCProceduresMonitorPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)GetSize(), nInfo.RemoveAll(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = GetAt(nJob)) && pJobInfo->Map(nJobData) && nInfo.Append(nJobData) >= 0) continue;
		break;
	}
	return((nJob == nJobs) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorPrintJobs::Unmap(CONST CByteArray &nInfo)
{
	INT  cbJob;
	INT  cbJobs;
	CByteArray  nJobData;
	CTCProceduresMonitorPrintJobInfo  *pJobInfo;

	for (cbJobs = 0, RemoveAll(); cbJobs < nInfo.GetSize(); cbJobs += cbJob)
	{
		for (CopyMemory(&cbJob, nInfo.GetData() + cbJobs, sizeof(cbJob)), nJobData.SetSize(max(min(cbJob, nInfo.GetSize() - cbJobs), 0)); nJobData.GetSize() >= 0; )
		{
			CopyMemory(nJobData.GetData(), nInfo.GetData() + cbJobs, nJobData.GetSize());
			break;
		}
		if ((pJobInfo = new CTCProceduresMonitorPrintJobInfo))
		{
			if (pJobInfo->Unmap(nJobData) && Add(pJobInfo) >= 0) continue;
			delete pJobInfo;
		}
		break;
	}
	if ((pJobInfo = (!GetSize()) ? new CTCProceduresMonitorPrintJobInfo : (CTCProceduresMonitorPrintJobInfo *)NULL))
	{
		for (pJobInfo->SetName(STRING(IDS_PRINTJOB_DEFAULTNAME)), pJobInfo->SetProfile(STRING(IDS_PRINTPROFILE_DEFAULTNAME)), pJobInfo->SetPrintMode(TCPROCEDURESMONITOR_PRINT_LIST); Add(pJobInfo) >= 0; ) return TRUE;
		delete pJobInfo;
		return FALSE;
	}
	return((cbJobs == nInfo.GetSize()) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorSettingsLayoutPage property page

IMPLEMENT_DYNCREATE(CTCProceduresMonitorSettingsLayoutPage, CLocalePropertyPage)

CTCProceduresMonitorSettingsLayoutPage::CTCProceduresMonitorSettingsLayoutPage() : CLocalePropertyPage(CTCProceduresMonitorSettingsLayoutPage::IDD)
{
	//{{AFX_DATA_INIT(CTCProceduresMonitorSettingsLayoutPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCProceduresMonitorSettingsLayoutPage::Initialize()
{
	if (GetParentDisplay()->GetLayout(m_nColumns[0]) && GetParentDisplay()->GetListTitleFont(&m_fntListTitle[0]) && GetParentDisplay()->GetListItemsFont(&m_fntListItems[0]) && GetParentDisplay()->GetItemSourceCodeFont(&m_fntSourceCode[0]) && GetParentDisplay()->GetItemFlowchartLabelsFont(&m_fntFlowchartLabels[0]) && GetParentDisplay()->GetItemFlowchartLabelsColor(m_nFlowchartLabelsColor[0]) && GetParentDisplay()->GetItemFlowchartBackgroundColor(m_nFlowchartBackgroundColor[0]))
	{
		CopyMemory(&m_fntListTitle[1], &m_fntListTitle[0], sizeof(LOGFONT));
		CopyMemory(&m_fntListItems[1], &m_fntListItems[0], sizeof(LOGFONT));
		CopyMemory(&m_fntSourceCode[1], &m_fntSourceCode[0], sizeof(LOGFONT));
		CopyMemory(&m_fntFlowchartLabels[1], &m_fntFlowchartLabels[0], sizeof(LOGFONT));
		m_bToolTips[0] = m_bToolTips[1] = GetParentDisplay()->IsToolTipModeEnabled();
		m_nFlowchartBackgroundColor[1] = m_nFlowchartBackgroundColor[0];
		m_nFlowchartLabelsColor[1] = m_nFlowchartLabelsColor[0];
		m_nColumns[1].Copy(m_nColumns[0]);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorSettingsLayoutPage::GetColumns(CUIntArray &nColumns) CONST
{
	nColumns.Copy(m_nColumns[0]);
	return((nColumns.GetSize() > 0) ? Check(FALSE) : FALSE);
}

BOOL CTCProceduresMonitorSettingsLayoutPage::GetTitleFont(LPLOGFONT pTitleFont) CONST
{
	CopyMemory(pTitleFont, &m_fntListTitle[0], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL CTCProceduresMonitorSettingsLayoutPage::GetItemsFont(LPLOGFONT pItemsFont) CONST
{
	CopyMemory(pItemsFont, &m_fntListItems[0], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL CTCProceduresMonitorSettingsLayoutPage::GetSourceCodeFont(LPLOGFONT pCodeFont) CONST
{
	CopyMemory(pCodeFont, &m_fntSourceCode[0], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL CTCProceduresMonitorSettingsLayoutPage::GetFlowchartLabelsFont(LPLOGFONT pLabelsFont) CONST
{
	CopyMemory(pLabelsFont, &m_fntFlowchartLabels[0], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL CTCProceduresMonitorSettingsLayoutPage::GetFlowchartLabelsColor(COLORREF &nColor) CONST
{
	nColor = m_nFlowchartLabelsColor[0];
	return Check(FALSE);
}

BOOL CTCProceduresMonitorSettingsLayoutPage::GetFlowchartBackgroundColor(COLORREF &nColor) CONST
{
	nColor = m_nFlowchartBackgroundColor[0];
	return Check(FALSE);
}

BOOL CTCProceduresMonitorSettingsLayoutPage::GetToolTipMode(BOOL &bEnable) CONST
{
	bEnable = m_bToolTips[0];
	return Check(FALSE);
}

CTCProceduresMonitorSettingsDialog *CTCProceduresMonitorSettingsLayoutPage::GetParentDialog() CONST
{
	return((CTCProceduresMonitorSettingsDialog *)CLocalePropertyPage::GetParent());
}

CTCProceduresMonitorWnd *CTCProceduresMonitorSettingsLayoutPage::GetParentDisplay() CONST
{
	return((CTCProceduresMonitorWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL CTCProceduresMonitorSettingsLayoutPage::EnumLayoutColumns()
{
	INT  nColumn;
	INT  nColumns;
	CStringArray  szColumns;

	szColumns.Add(LookupColumnName(TCPROCEDURESMONITOR_TITLEITEM_NAME));
	szColumns.Add(LookupColumnName(TCPROCEDURESMONITOR_TITLEITEM_DESCRIPTION));
	szColumns.Add(LookupColumnName(TCPROCEDURESMONITOR_TITLEITEM_COMMENTS));
	szColumns.Add(LookupColumnName(TCPROCEDURESMONITOR_TITLEITEM_AUTHOR));
	szColumns.Add(LookupColumnName(TCPROCEDURESMONITOR_TITLEITEM_CREATIONTIME));
	szColumns.Add(LookupColumnName(TCPROCEDURESMONITOR_TITLEITEM_MODIFICATIONTIME));
	szColumns.Add(LookupColumnName(TCPROCEDURESMONITOR_TITLEITEM_VERIFICATIONSTATUS));
	szColumns.Add(LookupColumnName(TCPROCEDURESMONITOR_TITLEITEM_NUMBEROFTHREADS));
	szColumns.Add(LookupColumnName(TCPROCEDURESMONITOR_TITLEITEM_ARGUMENTS));
	szColumns.Add(LookupColumnName(TCPROCEDURESMONITOR_TITLEITEM_TRIGGERTYPE));
	szColumns.Add(LookupColumnName(TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONMODE));
	szColumns.Add(LookupColumnName(TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONCOUNT));
	szColumns.Add(LookupColumnName(TCPROCEDURESMONITOR_TITLEITEM_RUNNINGSTATE));
	szColumns.Add(LookupColumnName(TCPROCEDURESMONITOR_TITLEITEM_ACKNOWLEDGEREQUEST));
	szColumns.Add(LookupColumnName(TCPROCEDURESMONITOR_TITLEITEM_ACKREQUESTTIME));
	szColumns.Add(LookupColumnName(TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS));
	szColumns.Add(LookupColumnName(TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS));
	szColumns.Add(LookupColumnName(TCPROCEDURESMONITOR_TITLEITEM_STARTTIME));
	szColumns.Add(LookupColumnName(TCPROCEDURESMONITOR_TITLEITEM_ENDTIME));
	for (nColumn = 0, nColumns = (INT)szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szColumns.GetAt(nColumn));
		continue;
	}
	SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_NAME, CB_SETCURSEL);
	return((nColumn == nColumns) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorSettingsLayoutPage::ShowLayoutColumns()
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_nColumns[0].GetSize(), SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_VIEW, LVM_DELETEALLITEMS), m_nColumnIndex = 0; nColumn < nColumns; nColumn++)
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
		if ((!nColumn  &&  !Listview_InsertText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_VIEW), 0, EMPTYSTRING)) || (nColumn > 0 && !Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_VIEW), 0, nColumn, EMPTYSTRING))) break;
		continue;
	}
	return((nColumn == nColumns) ? SetCurLayoutColumn() : FALSE);
}

VOID CTCProceduresMonitorSettingsLayoutPage::ShowLayoutFontDetails()
{
	INT  nSize;
	INT  nSizes;
	INT  nStyle;
	INT  nStyles;
	BOOL  bUnderlined;
	CStringArray  szSizes;
	CStringArray  szStyles;
	CFontTools  cFontTools;

	for (SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_RESETCONTENT), SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_RESETCONTENT), SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)) ? m_fntListTitle[0].lfFaceName : ((IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS)) ? m_fntListItems[0].lfFaceName : ((IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_SOURCECODE)) ? m_fntSourceCode[0].lfFaceName : m_fntFlowchartLabels[0].lfFaceName))))); (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE) && cFontTools.EnumerateFont(m_fntListTitle[0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS) && cFontTools.EnumerateFont(m_fntListItems[0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_SOURCECODE) && cFontTools.EnumerateFont(m_fntSourceCode[0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELS) && cFontTools.EnumerateFont(m_fntFlowchartLabels[0].lfFaceName, szStyles, szSizes, bUnderlined)); )
	{
		for (nStyle = 0, nStyles = (INT)szStyles.GetSize(); nStyle < nStyles; nStyle++) SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szStyles.GetAt(nStyle));
		for (nSize = 0, nSizes = (INT)szSizes.GetSize(); nSize < nSizes; nSize++) SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szSizes.GetAt(nSize));
		break;
	}
	if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELSCOLOR, CB_SETCURSEL, (WPARAM)-1);
		SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntListTitle[0])), 0));
		SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntListTitle[0])), max(SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntListTitle[1])), 0)));
	}
	if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELSCOLOR, CB_SETCURSEL, (WPARAM)-1);
		SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntListItems[0])), 0));
		SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntListItems[0])), max(SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntListItems[1])), 0)));
	}
	if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_SOURCECODE))
	{
		SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELSCOLOR, CB_SETCURSEL, (WPARAM)-1);
		SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntSourceCode[0])), 0));
		SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntSourceCode[0])), max(SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntSourceCode[1])), 0)));
	}
	if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELS))
	{
		SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELSCOLOR, CCB_SELECTCOLOR, (WPARAM)-1, (m_nFlowchartLabelsColor[0] != GetSysColor(COLOR_WINDOWTEXT)) ? (LPARAM)m_nFlowchartLabelsColor[0] : VGA_COLOR_BLACK);
		SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntFlowchartLabels[0])), 0));
		SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntFlowchartLabels[0])), max(SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntFlowchartLabels[1])), 0)));
	}
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELSCOLOR)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELS));
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SAMPLE)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorSettingsLayoutPage::ShowLayoutFontSample()
{
	CRect  rSampleText;

	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText);
	ScreenToClient(rSampleText);
	InvalidateRect(rSampleText);
	UpdateWindow();
}

BOOL CTCProceduresMonitorSettingsLayoutPage::InsertLayoutColumn(INT nIndex, LPCTSTR pszColumn)
{
	m_szColumns.InsertAt(nIndex, pszColumn);
	m_nColumnIndex = (nIndex <= m_nColumnIndex) ? (INT)min(m_nColumnIndex + 1, m_szColumns.GetSize() - 1) : m_nColumnIndex;
	return Listview_InsertColumn(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex, m_szColumns.GetAt(nIndex), CalcColumnWidth(pszColumn));
}

BOOL CTCProceduresMonitorSettingsLayoutPage::ModifyLayoutColumn(INT nIndex, LPCTSTR pszColumn)
{
	m_szColumns.SetAt(nIndex, pszColumn);
	return Listview_SetColumn(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex, m_szColumns.GetAt(nIndex), CalcColumnWidth(pszColumn));
}

BOOL CTCProceduresMonitorSettingsLayoutPage::RemoveLayoutColumn(INT nIndex)
{
	if (Listview_DeleteColumn(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex))
	{
		m_nColumnIndex = (nIndex >= m_nColumnIndex) ? ((nIndex > m_nColumnIndex) ? m_nColumnIndex : 0) : max(m_nColumnIndex - 1, 0);
		m_szColumns.RemoveAt(nIndex);
		return SetCurLayoutColumn(m_nColumnIndex);
	}
	return FALSE;
}

BOOL CTCProceduresMonitorSettingsLayoutPage::SetCurLayoutColumn(INT nIndex)
{
	if (nIndex < m_nColumns[0].GetSize())
	{
		for (m_szColumns.SetAt(m_nColumnIndex, (m_szColumns.GetAt(m_nColumnIndex).Right(lstrlen(STRING(IDS_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_COLUMNMARKER))) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_COLUMNMARKER)) ? (m_szColumns.GetAt(m_nColumnIndex).Left(m_szColumns.GetAt(m_nColumnIndex).GetLength() - lstrlen(STRING(IDS_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_COLUMNMARKER)))) : m_szColumns.GetAt(m_nColumnIndex)), m_szColumns.SetAt(nIndex, m_szColumns.GetAt(nIndex) + STRING(IDS_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_COLUMNMARKER)); TRUE; )
		{
			Listview_SetColumn(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_VIEW), m_nColumnIndex, m_szColumns.GetAt(m_nColumnIndex), CalcColumnWidth(m_szColumns.GetAt(m_nColumnIndex)));
			Listview_SetColumn(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex, m_szColumns.GetAt(nIndex), CalcColumnWidth(m_szColumns.GetAt((m_nColumnIndex = nIndex))));
			break;
		}
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE)->EnableWindow((m_nColumnIndex > 0) ? (CheckLayoutColumn() && (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE))) : FALSE);
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER)->EnableWindow((m_nColumnIndex >= 0) ? (CheckLayoutColumn() && (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE))) : FALSE);
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_REMOVE)->EnableWindow((m_nColumnIndex > 0) ? (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)) : FALSE);
		return TRUE;
	}
	return FALSE;
}

INT CTCProceduresMonitorSettingsLayoutPage::GetCurLayoutColumn() CONST
{
	return m_nColumnIndex;
}

BOOL CTCProceduresMonitorSettingsLayoutPage::CheckLayoutColumn() CONST
{
	INT  nColumn;
	INT  nColumns;
	CString  szColumn;

	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_NAME)->GetWindowText(szColumn);
	for (nColumn = 0, nColumns = (INT)m_nColumns[0].GetSize(); nColumn < nColumns; nColumn++)
	{
		if (LookupColumnName(m_nColumns[0].GetAt(nColumn)) == szColumn) break;
		continue;
	}
	return((nColumn == nColumns) ? TRUE : FALSE);
}

CString CTCProceduresMonitorSettingsLayoutPage::LookupColumnName(UINT nColumn) CONST
{
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_NAME) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NAME);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_DESCRIPTION) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_DESCRIPTION);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_COMMENTS) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_COMMENTS);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_AUTHOR) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_AUTHOR);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_CREATIONTIME) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_CREATIONTIME);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_MODIFICATIONTIME) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_MODIFICATIONTIME);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_VERIFICATIONSTATUS) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_VERIFICATIONSTATUS);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_NUMBEROFTHREADS) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NUMBEROFTHREADS);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_ARGUMENTS) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ARGUMENTS);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_TRIGGERTYPE) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_TRIGGERTYPE);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONMODE) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONMODE);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONCOUNT) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONCOUNT);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_RUNNINGSTATE) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_RUNNINGSTATE);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_ACKNOWLEDGEREQUEST) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ACKNOWLEDGEREQUEST);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_ACKREQUESTTIME) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ACKREQUESTTIME);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_STARTTIME) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_STARTTIME);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_ENDTIME) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ENDTIME);
	return EMPTYSTRING;
}
UINT CTCProceduresMonitorSettingsLayoutPage::LookupColumnName(LPCTSTR pszColumn) CONST
{
	if (!_tcsncmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NAME), lstrlen(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NAME)))) return TCPROCEDURESMONITOR_TITLEITEM_NAME;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_DESCRIPTION), lstrlen(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_DESCRIPTION)))) return TCPROCEDURESMONITOR_TITLEITEM_DESCRIPTION;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_COMMENTS), lstrlen(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_COMMENTS)))) return TCPROCEDURESMONITOR_TITLEITEM_COMMENTS;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_AUTHOR), lstrlen(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_AUTHOR)))) return TCPROCEDURESMONITOR_TITLEITEM_AUTHOR;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_CREATIONTIME), lstrlen(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_CREATIONTIME)))) return TCPROCEDURESMONITOR_TITLEITEM_CREATIONTIME;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_MODIFICATIONTIME), lstrlen(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_MODIFICATIONTIME)))) return TCPROCEDURESMONITOR_TITLEITEM_MODIFICATIONTIME;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_VERIFICATIONSTATUS), lstrlen(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_VERIFICATIONSTATUS)))) return TCPROCEDURESMONITOR_TITLEITEM_VERIFICATIONSTATUS;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NUMBEROFTHREADS), lstrlen(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NUMBEROFTHREADS)))) return TCPROCEDURESMONITOR_TITLEITEM_NUMBEROFTHREADS;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ARGUMENTS), lstrlen(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ARGUMENTS)))) return TCPROCEDURESMONITOR_TITLEITEM_ARGUMENTS;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_TRIGGERTYPE), lstrlen(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_TRIGGERTYPE)))) return TCPROCEDURESMONITOR_TITLEITEM_TRIGGERTYPE;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONMODE), lstrlen(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONMODE)))) return TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONMODE;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONCOUNT), lstrlen(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONCOUNT)))) return TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONCOUNT;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_RUNNINGSTATE), lstrlen(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_RUNNINGSTATE)))) return TCPROCEDURESMONITOR_TITLEITEM_RUNNINGSTATE;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ACKNOWLEDGEREQUEST), lstrlen(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ACKNOWLEDGEREQUEST)))) return TCPROCEDURESMONITOR_TITLEITEM_ACKNOWLEDGEREQUEST;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ACKREQUESTTIME), lstrlen(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ACKREQUESTTIME)))) return TCPROCEDURESMONITOR_TITLEITEM_ACKREQUESTTIME;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS), lstrlen(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS)))) return TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS), lstrlen(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS)))) return TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_STARTTIME), lstrlen(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_STARTTIME)))) return TCPROCEDURESMONITOR_TITLEITEM_STARTTIME;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ENDTIME), lstrlen(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ENDTIME)))) return TCPROCEDURESMONITOR_TITLEITEM_ENDTIME;
	return 0;
}

INT CTCProceduresMonitorSettingsLayoutPage::CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths)
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

INT CTCProceduresMonitorSettingsLayoutPage::CalcColumnWidth(LPCTSTR pszColumn)
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
				nWidth = ((nColumn = LookupColumnName(pszColumn)) == TCPROCEDURESMONITOR_TITLEITEM_NAME) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCProceduresMonitorNameColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : 0;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_DESCRIPTION) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCProceduresMonitorDescriptionColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_COMMENTS) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCProceduresMonitorCommentsColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_AUTHOR) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCProceduresMonitorAuthorColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_CREATIONTIME) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCProceduresMonitorCreationTimeColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_MODIFICATIONTIME) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCProceduresMonitorModificationTimeColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_VERIFICATIONSTATUS) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCProceduresMonitorVerificationStatusColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_NUMBEROFTHREADS) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCProceduresMonitorNumberOfThreadsColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_ARGUMENTS) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCProceduresMonitorArgumentsColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_TRIGGERTYPE) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCProceduresMonitorTriggerTypeColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONMODE) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCProceduresMonitorExecutionModeColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONCOUNT) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCProceduresMonitorExecutionCountColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_RUNNINGSTATE) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCProceduresMonitorRunningStateColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_ACKNOWLEDGEREQUEST) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCProceduresMonitorAcknowledgeRequestColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_ACKREQUESTTIME) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCProceduresMonitorAckRequestTimeColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCProceduresMonitorPEVChecksColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCProceduresMonitorCEVChecksColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_STARTTIME) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCProceduresMonitorStartTimeColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_ENDTIME) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCProceduresMonitorEndTimeColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
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

INT CTCProceduresMonitorSettingsLayoutPage::CalcColumnIndent() CONST
{
	return 3 * GetSystemMetrics(SM_CXEDGE);
}

VOID CTCProceduresMonitorSettingsLayoutPage::AdjustToPrivileges()
{
	BOOL  bCheck;

	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_NAME, (bCheck = CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)));
	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_FLOWCHART_BACKGROUNDCOLOR, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_FLOWCHART_TOOLTIPS, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELSCOLOR, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_NAMES, bCheck, TRUE, FALSE);
	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE, bCheck);
}

BOOL CTCProceduresMonitorSettingsLayoutPage::IsModified(BOOL bAll) CONST
{
	INT  nColumn;
	INT  nColumns;
	CFontTools  cFontTools;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		for (nColumn = 0, nColumns = (m_nColumns[0].GetSize() == m_nColumns[1].GetSize() && !lstrcmp(m_fntListTitle[0].lfFaceName, m_fntListTitle[1].lfFaceName) && (m_fntListTitle[0].lfHeight == m_fntListTitle[1].lfHeight || cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntListTitle[0])) == cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntListTitle[1]))) && m_fntListTitle[0].lfWeight == m_fntListTitle[1].lfWeight && m_fntListTitle[0].lfItalic == m_fntListTitle[1].lfItalic && !lstrcmp(m_fntListItems[0].lfFaceName, m_fntListItems[1].lfFaceName) && (m_fntListItems[0].lfHeight == m_fntListItems[1].lfHeight || cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntListItems[0])) == cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntListItems[1]))) && m_fntListItems[0].lfWeight == m_fntListItems[1].lfWeight && m_fntListItems[0].lfItalic == m_fntListItems[1].lfItalic && !lstrcmp(m_fntSourceCode[0].lfFaceName, m_fntSourceCode[1].lfFaceName) && (m_fntSourceCode[0].lfHeight == m_fntSourceCode[1].lfHeight || cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntSourceCode[0])) == cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntSourceCode[1]))) && m_fntSourceCode[0].lfWeight == m_fntSourceCode[1].lfWeight && m_fntSourceCode[0].lfItalic == m_fntSourceCode[1].lfItalic && !lstrcmp(m_fntFlowchartLabels[0].lfFaceName, m_fntFlowchartLabels[1].lfFaceName) && (m_fntFlowchartLabels[0].lfHeight == m_fntFlowchartLabels[1].lfHeight || cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntFlowchartLabels[0])) == cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntFlowchartLabels[1]))) && m_fntFlowchartLabels[0].lfWeight == m_fntFlowchartLabels[1].lfWeight && m_fntFlowchartLabels[0].lfItalic == m_fntFlowchartLabels[1].lfItalic && m_fntFlowchartLabels[0].lfUnderline == m_fntFlowchartLabels[1].lfUnderline && m_nFlowchartLabelsColor[0] == m_nFlowchartLabelsColor[1] && m_nFlowchartBackgroundColor[0] == m_nFlowchartBackgroundColor[1] && m_bToolTips[0] == m_bToolTips[1]) ? (INT)m_nColumns[0].GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			if (m_nColumns[0].GetAt(nColumn) != m_nColumns[1].GetAt(nColumn)) break;
			continue;
		}
		return((nColumn != nColumns) ? TRUE : FALSE);
	}
	return((bAll) ? CLocalePropertyPage::IsModified() : FALSE);
}

BOOL CTCProceduresMonitorSettingsLayoutPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (m_nColumns[0].GetSize() > 0 && m_nColumns[0].GetAt(0) == TCPROCEDURESMONITOR_TITLEITEM_NAME  &&  GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_NAMES)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowTextLength() > 0 && (!IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELS) || GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELSCOLOR)->SendMessage(CB_GETCURSEL) >= 0) && GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_FLOWCHART_BACKGROUNDCOLOR)->SendMessage(CB_GETCURSEL) >= 0) : CLocalePropertyPage::Check()) : TRUE);
}

void CTCProceduresMonitorSettingsLayoutPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProceduresMonitorSettingsLayoutPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCProceduresMonitorSettingsLayoutPage::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_nColumns[0].RemoveAll();
	m_nColumns[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorSettingsLayoutPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CTCProceduresMonitorSettingsLayoutPage)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE, OnInsertColumnBefore)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER, OnInsertColumnAfter)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_REMOVE, OnRemoveColumn)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_FLOWCHART_TOOLTIPS, OnToolTips)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, OnTitleFont)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS, OnItemsFont)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_SOURCECODE, OnSourceCodeFont)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELS, OnFlowchartLabelsFont)
	ON_CBN_EDITCHANGE(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_NAMES, OnEditchangeFontName)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_NAME, OnSelchangeColumnName)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_NAMES, OnSelchangeFontName)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE, OnSelchangeFontStyle)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE, OnSelchangeFontSize)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELSCOLOR, OnSelchangeFontColor)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_FLOWCHART_BACKGROUNDCOLOR, OnSelchangeBackgroundColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorSettingsLayoutPage message handlers

BOOL CTCProceduresMonitorSettingsLayoutPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	CheckRadioButton(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELS, IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_FLOWCHART_TOOLTIPS, m_bToolTips[0]);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowText(m_szFontSampleText);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_NAME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_VIEW)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_FLOWCHART_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_FLOWCHART_BACKGROUNDCOLOR)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_FLOWCHART_TOOLTIPS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_SOURCECODE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_CHARACTERISTICS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_NAMES)->EnableWindow();
	SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_NAMES, FCB_DIR, CF_EFFECTS | CF_SCREENFONTS);
	SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_fntListTitle[0].lfFaceName));
	SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_FLOWCHART_BACKGROUNDCOLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nFlowchartBackgroundColor[0]);
	EnumLayoutColumns();
	ShowLayoutColumns();
	ShowLayoutFontDetails();
	AdjustToPrivileges();
	return TRUE;
}

void CTCProceduresMonitorSettingsLayoutPage::OnPaint()
{
	INT  nBkMode;
	CFont  cFont;
	CFont  *pOldFont;
	CRect  rSampleText;
	COLORREF  nOldColor;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText), ScreenToClient(rSampleText); cFont.CreateFontIndirect((IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)) ? &m_fntListTitle[0] : ((IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS)) ? &m_fntListItems[0] : ((IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_SOURCECODE)) ? &m_fntSourceCode[0] : &m_fntFlowchartLabels[0]))); )
	{
		if ((pOldFont = cDC.SelectObject(&cFont)))
		{
			nBkMode = cDC.SetBkMode(TRANSPARENT);
			nOldColor = cDC.SetTextColor((!IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELS)) ? ((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? GetSysColor(COLOR_WINDOWTEXT) : GetSysColor(COLOR_GRAYTEXT)) : m_nFlowchartLabelsColor[0]);
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

BOOL CTCProceduresMonitorSettingsLayoutPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMLISTVIEW  *pNotifyInfo = (NMLISTVIEW *)lParam;

	if (pNotifyInfo->hdr.idFrom == IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_VIEW)
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

void CTCProceduresMonitorSettingsLayoutPage::OnInsertColumnBefore()
{
	INT  nIndex;
	CString  szColumn;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_NAME)->GetWindowText(szColumn); InsertLayoutColumn((nIndex = m_nColumnIndex), szColumn); )
	{
		m_nColumns[0].InsertAt(nIndex, LookupColumnName(szColumn));
		SetCurLayoutColumn(nIndex);
		break;
	}
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsLayoutPage::OnInsertColumnAfter()
{
	INT  nIndex;
	CString  szColumn;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_NAME)->GetWindowText(szColumn); InsertLayoutColumn((nIndex = m_nColumnIndex + 1), szColumn); )
	{
		m_nColumns[0].InsertAt(nIndex, LookupColumnName(szColumn));
		SetCurLayoutColumn(nIndex);
		break;
	}
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsLayoutPage::OnRemoveColumn()
{
	INT  nIndex;
	CHourglassCursor  cCursor;

	if (RemoveLayoutColumn((nIndex = m_nColumnIndex)))
	{
		m_nColumns[0].RemoveAt(nIndex);
		SetCurLayoutColumn();
	}
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsLayoutPage::OnToolTips()
{
	m_bToolTips[0] = IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_FLOWCHART_TOOLTIPS);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsLayoutPage::OnTitleFont()
{
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_SOURCECODE, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELS, FALSE);
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CTCProceduresMonitorSettingsLayoutPage::OnItemsFont()
{
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_SOURCECODE, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELS, FALSE);
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CTCProceduresMonitorSettingsLayoutPage::OnSourceCodeFont()
{
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_SOURCECODE, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELS, FALSE);
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CTCProceduresMonitorSettingsLayoutPage::OnFlowchartLabelsFont()
{
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_SOURCECODE, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELS, TRUE);
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CTCProceduresMonitorSettingsLayoutPage::OnEditchangeFontName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsLayoutPage::OnSelchangeColumnName()
{
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE)->EnableWindow((m_nColumnIndex > 0) ? (CheckLayoutColumn() && (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE))) : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER)->EnableWindow((m_nColumnIndex >= 0) ? (CheckLayoutColumn() && (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE))) : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_REMOVE)->EnableWindow((m_nColumnIndex > 0) ? (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)) : FALSE);
}

void CTCProceduresMonitorSettingsLayoutPage::OnSelchangeFontName()
{
	CString  szSize;
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		_tcscpy_s(m_fntListTitle[0].lfFaceName, sizeof(m_fntListTitle[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		_tcscpy_s(m_fntListItems[0].lfFaceName, sizeof(m_fntListItems[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_SOURCECODE))
	{
		_tcscpy_s(m_fntSourceCode[0].lfFaceName, sizeof(m_fntSourceCode[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELS))
	{
		_tcscpy_s(m_fntFlowchartLabels[0].lfFaceName, sizeof(m_fntFlowchartLabels[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntListTitle[0].lfWeight, m_fntListTitle[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntListTitle[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntListTitle[0]);
	}
	if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntListItems[0].lfWeight, m_fntListItems[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntListItems[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntListItems[0]);
	}
	if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_SOURCECODE))
	{
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntSourceCode[0].lfWeight, m_fntSourceCode[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntSourceCode[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntSourceCode[0]);
	}
	if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELS))
	{
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntFlowchartLabels[0].lfWeight, m_fntFlowchartLabels[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntFlowchartLabels[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntFlowchartLabels[0]);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsLayoutPage::OnSelchangeFontStyle()
{
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntListTitle[0].lfWeight, m_fntListTitle[0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntListItems[0].lfWeight, m_fntListItems[0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_SOURCECODE))
	{
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntSourceCode[0].lfWeight, m_fntSourceCode[0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELS))
	{
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntFlowchartLabels[0].lfWeight, m_fntFlowchartLabels[0].lfItalic);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsLayoutPage::OnSelchangeFontSize()
{
	CString  szSize;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntListTitle[0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntListItems[0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_SOURCECODE))
	{
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntSourceCode[0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELS))
	{
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntFlowchartLabels[0].lfHeight);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsLayoutPage::OnSelchangeFontColor()
{
	COLORREF  nColor;

	if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELS))
	{
		nColor = (SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELSCOLOR, CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nFlowchartLabelsColor[1]) != SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELSCOLOR, CB_GETCURSEL)) ? (COLORREF)SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELSCOLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELSCOLOR, CB_GETCURSEL)) : m_nFlowchartLabelsColor[1];
		m_nFlowchartLabelsColor[0] = nColor;
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsLayoutPage::OnSelchangeBackgroundColor()
{
	m_nFlowchartBackgroundColor[0] = (COLORREF)SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_FLOWCHART_BACKGROUNDCOLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_FLOWCHART_BACKGROUNDCOLOR, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorSettingsContentsPage property page

IMPLEMENT_DYNCREATE(CTCProceduresMonitorSettingsContentsPage, CLocalePropertyPage)

CTCProceduresMonitorSettingsContentsPage::CTCProceduresMonitorSettingsContentsPage() : CLocalePropertyPage(CTCProceduresMonitorSettingsContentsPage::IDD)
{
	//{{AFX_DATA_INIT(CTCProceduresMonitorSettingsContentsPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCProceduresMonitorSettingsContentsPage::Initialize()
{
	if (GetParentDisplay()->GetProcedures(m_pItems[0]))
	{
		m_bModes[0] = m_bModes[1] = GetParentDisplay()->IsTelecommandingReleaseWaitModeEnabled();
		m_bStateFlags[0] = m_bStateFlags[1] = (GetParentDisplay()->GetTelecommandingState() & TCPROCEDURESMONITOR_STATE_DISABLED) ? TRUE : FALSE;
		m_nCheckFlags[0] = m_nCheckFlags[1] = GetParentDisplay()->GetTelecommandingChecks();
		return m_pItems[1].Copy(&m_pItems[0]);
	}
	return FALSE;
}

INT CTCProceduresMonitorSettingsContentsPage::GetContents(CTCProceduresMonitorItems &pItems) CONST
{
	pItems.Copy(&m_pItems[0]);
	return((Check(FALSE)) ? (INT)pItems.GetSize() : 0);
}

BOOL CTCProceduresMonitorSettingsContentsPage::GetCheckOptions(UINT &nFlags) CONST
{
	nFlags = m_nCheckFlags[0];
	return Check(FALSE);
}

BOOL CTCProceduresMonitorSettingsContentsPage::GetReleaseWaitModeFlag(BOOL &bEnabled) CONST
{
	bEnabled = m_bModes[0];
	return Check(FALSE);
}

BOOL CTCProceduresMonitorSettingsContentsPage::GetDisabledStateFlag(BOOL &bFlag) CONST
{
	bFlag = m_bStateFlags[0];
	return Check(FALSE);
}

CTCProceduresMonitorSettingsDialog *CTCProceduresMonitorSettingsContentsPage::GetParentDialog() CONST
{
	return((CTCProceduresMonitorSettingsDialog *)CLocalePropertyPage::GetParent());
}

CTCProceduresMonitorWnd *CTCProceduresMonitorSettingsContentsPage::GetParentDisplay() CONST
{
	return((CTCProceduresMonitorWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL CTCProceduresMonitorSettingsContentsPage::EnumProcedures()
{
	INT  nColumn;
	INT  nColumns;
	INT  nArgument;
	INT  nArguments;
	INT  nProcedure;
	INT  nProcedures;
	UINT  nCount;
	CString  szItem;
	CString  szArgument;
	CString  szProcedure;
	CTimeKey  tStopTime;
	CTimeKey  tStartTime;
	CTimeSpan  tInterval;
	CStringTools  cStringTools;
	CDatabaseTCProcedure  *pProcedure;
	CDatabaseTCProcedureArgument  *pArgument;
	CDatabaseTCProcedureArguments  pArguments;
	CTCProceduresMonitorItem  *pItem;

	for (nProcedure = 0, nProcedures = (INT)GetDatabase()->GetTCProcedures()->GetSize(); nProcedure < nProcedures; nProcedure++)
	{
		if ((pProcedure = GetDatabase()->GetTCProcedures()->GetAt(nProcedure)) != (CDatabaseTCProcedure *)NULL)
		{
			szProcedure.Format(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_LISTFORMAT), (LPCTSTR)pProcedure->GetName(), (LPCTSTR)pProcedure->GetDescription());
			SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_LIST, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)((pProcedure->GetDescription().IsEmpty()) ? (LPCTSTR)pProcedure->GetName() : (LPCTSTR)szProcedure));
		}
	}
	for (nProcedure = 0, nProcedures = (INT)m_pItems[0].GetSize(); nProcedure < nProcedures; nProcedure++)
	{
		if ((pItem = m_pItems[0].GetAt(nProcedure)) != (CTCProceduresMonitorItem *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TITLEITEM_NAME); )
				{
					szItem = pItem->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TITLEITEM_DESCRIPTION); )
				{
					szItem = pItem->GetDescription();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TITLEITEM_ARGUMENTS); )
				{
					for (nArgument = 0, nArguments = pItem->GetArguments(pArguments), szItem.Empty(); nArgument < nArguments; nArgument++)
					{
						if ((pArgument = pArguments.GetAt(nArgument)) != (CDatabaseTCProcedureArgument *)NULL)
						{
							szArgument.Format(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ARGUMENTSFORMAT), (LPCTSTR)pArgument->GetTag(), (LPCTSTR)pArgument->GetConstValueAsText());
							szItem += (!szItem.IsEmpty()) ? (STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ARGUMENTSSEPARATOR) + szArgument) : szArgument;
						}
					}
					if (!nArguments)
					{
						szArgument = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_NOARGUMENTS);
						szItem = szArgument;
					}
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TITLEITEM_TRIGGERTYPE); )
				{
					if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_NONE)
					{
						szItem = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERTYPE_NONE);
						szItem += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
						break;
					}
					if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_IMMEDIATELY)
					{
						szItem = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERTYPE_IMMEDIATELY);
						szItem += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
						break;
					}
					if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATSTARTUP)
					{
						szItem = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERTYPE_ATSTARTUP);
						szItem += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
						break;
					}
					if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATTIME)
					{
						szItem.Format(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERTYPE_ATTIME), (LPCTSTR)pItem->GetTriggerTime().FormatGmt());
						szItem += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
						break;
					}
					if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATDAILYTIME)
					{
						szItem.Format(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERTYPE_ATDAILYTIME), (LPCTSTR)CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + pItem->GetDailyTriggerTime().GetTotalSeconds()).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT)));
						szItem += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
						break;
					}
					if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATINTERVAL)
					{
						if (pItem->GetTriggerInterval(tStartTime, tInterval) || pItem->GetTriggerInterval(tStartTime, tInterval, tStopTime) || pItem->GetTriggerInterval(tStartTime, tInterval, nCount))
						{
							szItem.Format(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERTYPE_ATINTERVAL), (LPCTSTR)cStringTools.ConvertLongIntToStructuredString(tInterval.GetTotalSeconds()), (LPCTSTR)tStartTime.FormatGmt());
							szItem += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
							break;
						}
					}
					if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATEVENT)
					{
						szItem.Format(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERTYPE_ATEVENT), (LPCTSTR)pItem->GetTriggerEvent());
						szItem += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
						break;
					}
					szItem.Empty();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TITLEITEM_EXECUTIONMODE); )
				{
					if (pItem->GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_AUTOMATIC)
					{
						szItem = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_EXECUTIONMODE_AUTOMATIC);
						break;
					}
					if (pItem->GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_SINGLESTEP)
					{
						szItem = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_EXECUTIONMODE_SINGLESTEP);
						break;
					}
					if (pItem->GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_EXTERNALACTIONS)
					{
						szItem = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_EXECUTIONMODE_EXTERNALACTIONS);
						break;
					}
					if (pItem->GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_COMMANDS)
					{
						szItem = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_EXECUTIONMODE_COMMANDS);
						break;
					}
					szItem.Empty();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST), nProcedure, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST), nProcedure, nColumn, szItem);
			}
		}
	}
	SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_LIST, CB_SETCURSEL);
	Listview_SetCurText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST), 0);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_LIST, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_LIST)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_LIST, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_LIST, CB_GETCOUNT) == nProcedures  &&  SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST, LVM_GETITEMCOUNT) == m_pItems[0].GetSize()) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorSettingsContentsPage::ShowProperties()
{
	CTCProceduresMonitorItem  *pItem;
	CDatabaseTCProcedureArguments  pArguments;

	if ((pItem = FindProcedure()))
	{
		if (!IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_COMMANDSOURCE))
		{
			CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_OVERRIDEPEV, (pItem->GetFlags() & TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDEPEV) ? TRUE : FALSE);
			CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLEPEV, (pItem->GetFlags() & TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLEPEV) ? TRUE : FALSE);
			CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_OVERRIDECEV, (pItem->GetFlags() & TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDECEV) ? TRUE : FALSE);
			CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLECEV, (pItem->GetFlags() & TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLECEV) ? TRUE : FALSE);
			CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_RELEASEWAITMODE, FALSE);
			CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLED, FALSE);
			GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_RELEASEWAITMODE)->EnableWindow(FALSE);
			GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLED)->EnableWindow(FALSE);
			GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_ARGUMENTS)->EnableWindow((pItem->GetArguments(pArguments) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_EXECUTION)->EnableWindow();
			GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_COMMANDS)->EnableWindow();
			GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_ALERTS)->EnableWindow();
			GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ADD)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_LIST, CB_GETCOUNT) > 0) ? CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE) : FALSE);
			GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow(CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE));
			GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow(CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE));
			return;
		}
	}
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_COMMANDSOURCE, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_OVERRIDEPEV, (m_nCheckFlags[0] & TCPROCEDURESMONITOR_CHECKS_PEV_OVERRIDE) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLEPEV, (m_nCheckFlags[0] & TCPROCEDURESMONITOR_CHECKS_PEV_DISABLE) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_OVERRIDECEV, (m_nCheckFlags[0] & TCPROCEDURESMONITOR_CHECKS_CEV_OVERRIDE) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLECEV, (m_nCheckFlags[0] & TCPROCEDURESMONITOR_CHECKS_CEV_DISABLE) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_RELEASEWAITMODE, m_bModes[0]);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLED, m_bStateFlags[0]);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_RELEASEWAITMODE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLED)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_ARGUMENTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_EXECUTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_COMMANDS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_ALERTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ADD)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_LIST, CB_GETCOUNT) > 0) ? CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE) : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST)) >= 0) ? CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE) : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST, LVM_GETITEMCOUNT) > 0) ? CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE) : FALSE);
}

CTCProceduresMonitorItem *CTCProceduresMonitorSettingsContentsPage::FindProcedure() CONST
{
	return m_pItems[0].GetAt(Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST)));
}

INT CTCProceduresMonitorSettingsContentsPage::FindColumnIndex(LPCTSTR pszColumn) CONST
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == pszColumn) break;
		continue;
	}
	return((nColumn < nColumns) ? nColumn : -1);
}

VOID CTCProceduresMonitorSettingsContentsPage::AdjustToPrivileges()
{
	BOOL  bCheck;

	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_LIST, (bCheck = CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)));
	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_OVERRIDEPEV, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLEPEV, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_OVERRIDECEV, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLECEV, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_RELEASEWAITMODE, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLED, bCheck);
}

BOOL CTCProceduresMonitorSettingsContentsPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (m_bModes[0] != m_bModes[1] || m_bStateFlags[0] != m_bStateFlags[1] || m_nCheckFlags[0] != m_nCheckFlags[1] || !m_pItems[0].Compare(&m_pItems[1])) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CTCProceduresMonitorSettingsContentsPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? TRUE : CLocalePropertyPage::Check()) : TRUE);
}

void CTCProceduresMonitorSettingsContentsPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProceduresMonitorSettingsContentsPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCProceduresMonitorSettingsContentsPage::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pItems[0].RemoveAll();
	m_pItems[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorSettingsContentsPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CTCProceduresMonitorSettingsContentsPage)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ADD, OnAddProcedure)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_REMOVE, OnRemoveProcedure)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_REMOVEALL, OnRemoveAllProcedures)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_COMMANDSOURCE, OnOperationsCommandSource)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_OVERRIDEPEV, OnOperationsOverridePEV)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLEPEV, OnOperationsDisablePEV)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_OVERRIDECEV, OnOperationsOverrideCEV)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLECEV, OnOperationsDisableCEV)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_RELEASEWAITMODE, OnOperationsReleaseWaitMode)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLED, OnOperationsDisabled)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_ARGUMENTS, OnProcedureArguments)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_EXECUTION, OnProcedureExecution)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_COMMANDS, OnProcedureCommands)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_ALERTS, OnProcedureAlerts)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorSettingsContentsPage message handlers

BOOL CTCProceduresMonitorSettingsContentsPage::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TITLEITEM_DESCRIPTION));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TITLEITEM_ARGUMENTS));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TITLEITEM_TRIGGERTYPE));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TITLEITEM_EXECUTIONMODE));
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST)->GetClientRect(rColumns);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TITLEITEM_NAME)) ? (rColumns.Width() / 4) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TITLEITEM_DESCRIPTION)) ? ((3 * rColumns.Width()) / 8) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TITLEITEM_ARGUMENTS)) ? (rColumns.Width() / 2) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TITLEITEM_TRIGGERTYPE)) ? (rColumns.Width() / 3) : (rColumns.Width() / 4)))));
		continue;
	}
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_COMMANDSOURCE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_OVERRIDEPEV)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLEPEV)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_OVERRIDECEV)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLECEV)->EnableWindow();
	EnumProcedures();
	ShowProperties();
	AdjustToPrivileges();
	return TRUE;
}

BOOL CTCProceduresMonitorSettingsContentsPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED)) ShowProperties();
	}
	return CLocalePropertyPage::OnNotify(wParam, lParam, pResult);
}

void CTCProceduresMonitorSettingsContentsPage::OnAddProcedure()
{
	INT  nPos;
	INT  nIndex;
	INT  nColumn;
	INT  nColumns;
	INT  nArgument;
	INT  nArguments;
	INT  nThread;
	INT  nThreads;
	INT  nEntry;
	INT  nEntries;
	INT  nStep;
	INT  nSteps;
	UINT  nCount;
	CString  szItem;
	CString  szName;
	CString  szFormat;
	CString  szArgument;
	CString  szInterlock;
	CTimeKey  tStopTime;
	CTimeKey  tStartTime;
	CTimeSpan  tInterval;
	CPtrArray  pSteps;
	CTimeSpan  tTimeWindow;
	CTCInterlock  *pInterlock;
	CStringTools  cStringTools;
	CComputerToken  cComputerToken;
	CDatabaseTCFunction  *pFunction;
	CDatabaseTCSequence  *pSequence;
	CDatabaseTCProcedure  *pProcedure;
	CDatabaseTCSequenceEntry  *pSequenceEntry;
	CDatabaseTCProcedureThread  *pThread;
	CDatabaseTCProcedureArgument  *pArgument;
	CDatabaseTCProcedureArguments  pArguments;
	CTCProcedureDocumentSendTCSequenceItem  *pSendTCSequenceItem;
	CTCProceduresMonitorItem  *pItem;
	CTCProcedureDocumentItem  *pStep;
	CTCProcedureDocument  *pDocument;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_LIST)->GetWindowText(szName), szFormat.Format(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_LISTFORMAT), EMPTYSTRING, EMPTYSTRING); (pProcedure = GetDatabase()->GetTCProcedures()->GetAt(GetDatabase()->GetTCProcedures()->Find((szName = ((nPos = szName.Find(szFormat.GetAt(0))) >= 0) ? szName.Left(nPos) : szName)))); )
	{
		if ((pItem = new CTCProceduresMonitorItem))
		{
			pItem->SetName(pProcedure->GetName());
			pItem->SetTriggerType(TCPROCEDURESMONITORITEM_TRIGGERTYPE_NONE);
			pItem->SetExecutionMode(TCPROCEDURESMONITORITEM_EXECUTIONMODE_AUTOMATIC);
			pItem->SetFlags(((IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_OVERRIDEPEV)) ? TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDEPEV : 0) | ((IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLEPEV)) ? TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLEPEV : 0) | ((IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_OVERRIDECEV)) ? TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDECEV : 0) | ((IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLECEV)) ? TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLECEV : 0));
			for (pItem->CDatabaseTCProcedure::Copy(pProcedure); pProcedure->GetArguments(pArguments) > 0; )
			{
				pItem->SetArguments(pArguments);
				break;
			}
			if ((nIndex = m_pItems[0].Add(pItem)) >= 0)
			{
				for (nThread = 0, nThreads = (INT)pProcedure->GetSize(); nThread < nThreads; nThread++)
				{
					if ((pThread = pProcedure->GetAt(nThread)))
					{
						if ((pDocument = new CTCProcedureDocument))
						{
							if (pDocument->Unmap(pThread) && pDocument->EnumSteps(pSteps, FALSE, TRUE) >= 0)
							{
								for (nStep = 0, nSteps = (INT)pSteps.GetSize(); nStep < nSteps; nStep++)
								{
									if ((pStep = (CTCProcedureDocumentItem *)pSteps.GetAt(nStep)))
									{
										if (pStep->GetType() == TCPROCEDURETHREADSTEP_ACTIONOBJECT_SENDTCSEQUENCE)
										{
											if ((pSendTCSequenceItem = (CTCProcedureDocumentSendTCSequenceItem *)pStep))
											{
												if ((pSequence = GetDatabase()->GetTCSequences()->GetAt(GetDatabase()->GetTCSequences()->Find(pSendTCSequenceItem->GetSequence()))))
												{
													for (nEntry = 0, nEntries = (INT)pSequence->GetSize(); nEntry < nEntries; nEntry++)
													{
														if ((pSequenceEntry = pSequence->GetAt(nEntry)))
														{
															if (pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_TYPE_FUNCTION)
															{
																if ((pFunction = GetDatabase()->GetTCFunctions()->GetAt(GetDatabase()->GetTCFunctions()->Find(pSequenceEntry->GetName()))))
																{
																	if ((pInterlock = ((pSequenceEntry->GetAttributes() & (TCSEQUENCEENTRY_ILSCOPE_GLOBAL | TCSEQUENCEENTRY_ILSCOPE_LOCAL | TCSEQUENCEENTRY_ILSCOPE_LOCALNOWAIT | TCSEQUENCEENTRY_ILSCOPE_GLOBALSUBSYSTEM | TCSEQUENCEENTRY_ILSCOPE_LOCALSUBSYSTEM | TCSEQUENCEENTRY_ILSCOPE_LOCALSUBSYSTEMNOWAIT)) || (pFunction->GetAttributes() & (TCFUNCTION_ILSCOPE_GLOBAL | TCFUNCTION_ILSCOPE_LOCAL | TCFUNCTION_ILSCOPE_GLOBALSUBSYSTEM | TCFUNCTION_ILSCOPE_LOCALSUBSYSTEM))) ? new CTCInterlock : (CTCInterlock *)NULL))
																	{
																		for (pInterlock->SetSourceType(TCINTERLOCK_SOURCETYPE_PROCEDURESMONITOR), pInterlock->SetScope(((pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_ILSCOPE_GLOBAL) || (pFunction->GetAttributes() & TCFUNCTION_ILSCOPE_GLOBAL)) ? TCINTERLOCK_SCOPE_GLOBAL : (((pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_ILSCOPE_LOCAL) || (pFunction->GetAttributes() & TCFUNCTION_ILSCOPE_LOCAL)) ? TCINTERLOCK_SCOPE_LOCAL : ((pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_ILSCOPE_LOCALNOWAIT) ? TCINTERLOCK_SCOPE_LOCALNOWAIT : (((pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_ILSCOPE_GLOBALSUBSYSTEM) || (pFunction->GetAttributes() & TCFUNCTION_ILSCOPE_GLOBALSUBSYSTEM)) ? TCINTERLOCK_SCOPE_GLOBALSUBSYSTEM : (((pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_ILSCOPE_LOCALSUBSYSTEM) || (pFunction->GetAttributes() & TCFUNCTION_ILSCOPE_LOCALSUBSYSTEM)) ? TCINTERLOCK_SCOPE_LOCALSUBSYSTEM : ((pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_ILSCOPE_LOCALSUBSYSTEMNOWAIT) ? TCINTERLOCK_SCOPE_LOCALSUBSYSTEMNOWAIT : TCINTERLOCK_SCOPE_NONE)))))), pInterlock->SetStage(((pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_ILSTAGE_RECEPTION) || (pFunction->GetAttributes() & TCFUNCTION_ILSTAGE_RECEPTION)) ? TCINTERLOCK_STAGE_RECEPTION : (((pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_ILSTAGE_UPLINK) || (pFunction->GetAttributes() & TCFUNCTION_ILSTAGE_UPLINK)) ? TCINTERLOCK_STAGE_TRANSMISSION : (((pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_ILSTAGE_ONBOARD) || (pFunction->GetAttributes() & TCFUNCTION_ILSTAGE_ONBOARD)) ? TCINTERLOCK_STAGE_ACCEPTANCE : (((pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_ILSTAGE_ACCEPTANCE) || (pFunction->GetAttributes() & TCFUNCTION_ILSTAGE_ACCEPTANCE)) ? TCINTERLOCK_STAGE_START : (((pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_ILSTAGE_COMPLETION) || (pFunction->GetAttributes() & TCFUNCTION_ILSTAGE_COMPLETION)) ? TCINTERLOCK_STAGE_COMPLETION : TCINTERLOCK_STAGE_NONE))))), pInterlock->SetState(TCINTERLOCK_STATE_IDLE); pItem->GetReleaseConstraints(pThread->GetName(), pStep->GetName(), pFunction->GetName(), nEntry + 1, szInterlock, tTimeWindow) >= 0; )
																		{
																			pItem->SetReleaseConstraints(pThread->GetName(), pStep->GetName(), pFunction->GetName(), nEntry + 1, pInterlock->GetName(), (tTimeWindow > 0 || GetTCService()->GetCommandHandlerDefaultReleaseTimeWindow(tTimeWindow)) ? tTimeWindow : tTimeWindow);
																			break;
																		}
																		delete pInterlock;
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
							delete pDocument;
						}
					}
				}
				for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
				{
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TITLEITEM_NAME); )
					{
						szItem = pItem->GetName();
						break;
					}
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TITLEITEM_DESCRIPTION); )
					{
						szItem = pItem->GetDescription();
						break;
					}
					if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TITLEITEM_ARGUMENTS))
					{
						for (nArgument = 0, nArguments = (INT)pArguments.GetSize(), szItem.Empty(); nArgument < nArguments; nArgument++)
						{
							if ((pArgument = pArguments.GetAt(nArgument)) != (CDatabaseTCProcedureArgument *)NULL)
							{
								szArgument.Format(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ARGUMENTSFORMAT), (LPCTSTR)pArgument->GetTag(), (LPCTSTR)pArgument->GetConstValueAsText());
								szItem += (!szItem.IsEmpty()) ? (STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ARGUMENTSSEPARATOR) + szArgument) : szArgument;
							}
						}
						if (!nArguments)
						{
							szArgument = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_NOARGUMENTS);
							szItem = szArgument;
						}
					}
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TITLEITEM_TRIGGERTYPE); )
					{
						if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_NONE)
						{
							szItem = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERTYPE_NONE);
							szItem += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
							break;
						}
						if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATSTARTUP)
						{
							szItem = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERTYPE_ATSTARTUP);
							szItem += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
							break;
						}
						if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATTIME)
						{
							szItem.Format(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERTYPE_ATTIME), (LPCTSTR)pItem->GetTriggerTime().FormatGmt());
							szItem += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
							break;
						}
						if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATDAILYTIME)
						{
							szItem.Format(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERTYPE_ATDAILYTIME), (LPCTSTR)CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + pItem->GetDailyTriggerTime().GetTotalSeconds()).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT)));
							szItem += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
							break;
						}
						if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATINTERVAL)
						{
							if (pItem->GetTriggerInterval(tStartTime, tInterval) || pItem->GetTriggerInterval(tStartTime, tInterval, tStopTime) || pItem->GetTriggerInterval(tStartTime, tInterval, nCount))
							{
								szItem.Format(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERTYPE_ATINTERVAL), (LPCTSTR)cStringTools.ConvertLongIntToStructuredString(tInterval.GetTotalSeconds()), (LPCTSTR)tStartTime.FormatGmt());
								szItem += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
								break;
							}
						}
						if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATEVENT)
						{
							szItem.Format(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERTYPE_ATEVENT), (LPCTSTR)pItem->GetTriggerEvent());
							szItem += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
							break;
						}
						szItem.Empty();
						break;
					}
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TITLEITEM_EXECUTIONMODE); )
					{
						if (pItem->GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_AUTOMATIC)
						{
							szItem = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_EXECUTIONMODE_AUTOMATIC);
							break;
						}
						if (pItem->GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_SINGLESTEP)
						{
							szItem = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_EXECUTIONMODE_SINGLESTEP);
							break;
						}
						if (pItem->GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_EXTERNALACTIONS)
						{
							szItem = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_EXECUTIONMODE_EXTERNALACTIONS);
							break;
						}
						if (pItem->GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_COMMANDS)
						{
							szItem = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_EXECUTIONMODE_COMMANDS);
							break;
						}
						szItem.Empty();
						break;
					}
					if (!nColumn)
					{
						Listview_InsertText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST), nIndex, szItem);
						continue;
					}
					Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST), nIndex, nColumn, szItem);
				}
				Listview_SetCurText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST), nIndex);
				GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ADD)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_LIST, CB_GETCOUNT) > 0) ? CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE) : FALSE);
				GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST)) >= 0) ? CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE) : FALSE);
				GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST, LVM_GETITEMCOUNT) > 0) ? CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE) : FALSE);
				GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
				GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_ARGUMENTS)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST)) >= 0 && pArguments.GetSize() > 0) ? TRUE : FALSE);
				GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_EXECUTION)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST)) >= 0) ? TRUE : FALSE);
				GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_COMMANDS)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST)) >= 0) ? TRUE : FALSE);
				GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_ALERTS)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST)) >= 0) ? TRUE : FALSE);
				break;
			}
			delete pItem;
		}
		break;
	}
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_LIST)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsContentsPage::OnRemoveProcedure()
{
	INT  nIndex;
	CTCProceduresMonitorItem  *pItem[2];
	CDatabaseTCProcedureArguments  pArguments;
	CHourglassCursor  cCursor;

	if ((pItem[0] = FindProcedure()))
	{
		Listview_DeleteText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST), (nIndex = Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST))));
		Listview_SetCurText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST), (SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST, LVM_GETITEMCOUNT) > 0) ? 0 : -1);
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ADD)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_LIST, CB_GETCOUNT) > 0) ? CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE) : FALSE);
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST)) >= 0) ? CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE) : FALSE);
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST, LVM_GETITEMCOUNT) > 0) ? CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE) : FALSE);
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_ARGUMENTS)->EnableWindow(((pItem[1] = (Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST)) >= 0) ? FindProcedure() : (CTCProceduresMonitorItem *)NULL) && pItem[1]->GetArguments(pArguments) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_EXECUTION)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST)) >= 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_COMMANDS)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST)) >= 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_ALERTS)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST)) >= 0) ? TRUE : FALSE);
		m_pItems[0].RemoveAt(nIndex);
		delete pItem[0];
	}
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_LIST)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsContentsPage::OnRemoveAllProcedures()
{
	CHourglassCursor  cCursor;

	m_pItems[0].RemoveAll();
	SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ADD)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_LIST, CB_GETCOUNT) > 0) ? CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE) : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_ARGUMENTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_EXECUTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_COMMANDS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_ALERTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_LIST)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsContentsPage::OnOperationsCommandSource()
{
	ShowProperties();
}

void CTCProceduresMonitorSettingsContentsPage::OnOperationsOverridePEV()
{
	CTCProceduresMonitorItem  *pItem;

	for (; IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_COMMANDSOURCE); )
	{
		m_nCheckFlags[0] = (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_OVERRIDEPEV)) ? ((m_nCheckFlags[0] & ~TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLEPEV) | TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDEPEV) : (m_nCheckFlags[0] & ~TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDEPEV);
		break;
	}
	for (CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLEPEV, FALSE); (pItem = (!IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_COMMANDSOURCE)) ? FindProcedure() : (CTCProceduresMonitorItem *)NULL); )
	{
		pItem->SetFlags((IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_OVERRIDEPEV)) ? ((pItem->GetFlags() & ~TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLEPEV) | TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDEPEV) : (pItem->GetFlags() & ~TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDEPEV));
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsContentsPage::OnOperationsDisablePEV()
{
	CTCProceduresMonitorItem  *pItem;

	for (; IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_COMMANDSOURCE); )
	{
		m_nCheckFlags[0] = (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLEPEV)) ? ((m_nCheckFlags[0] & ~TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDEPEV) | TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLEPEV) : (m_nCheckFlags[0] & ~TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLEPEV);
		break;
	}
	for (CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_OVERRIDEPEV, FALSE); (pItem = (!IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_COMMANDSOURCE)) ? FindProcedure() : (CTCProceduresMonitorItem *)NULL); )
	{
		pItem->SetFlags((IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLEPEV)) ? ((pItem->GetFlags() & ~TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDEPEV) | TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLEPEV) : (pItem->GetFlags() & ~TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLEPEV));
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsContentsPage::OnOperationsOverrideCEV()
{
	CTCProceduresMonitorItem  *pItem;

	for (; IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_COMMANDSOURCE); )
	{
		m_nCheckFlags[0] = (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_OVERRIDECEV)) ? ((m_nCheckFlags[0] & ~TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLECEV) | TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDECEV) : (m_nCheckFlags[0] & ~TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDECEV);
		break;
	}
	for (CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLECEV, FALSE); (pItem = (!IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_COMMANDSOURCE)) ? FindProcedure() : (CTCProceduresMonitorItem *)NULL); )
	{
		pItem->SetFlags((IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_OVERRIDECEV)) ? ((pItem->GetFlags() & ~TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLECEV) | TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDECEV) : (pItem->GetFlags() & ~TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDECEV));
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsContentsPage::OnOperationsDisableCEV()
{
	CTCProceduresMonitorItem  *pItem;

	for (; IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_COMMANDSOURCE); )
	{
		m_nCheckFlags[0] = (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLECEV)) ? ((m_nCheckFlags[0] & ~TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDECEV) | TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLECEV) : (m_nCheckFlags[0] & ~TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLECEV);
		break;
	}
	for (CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_OVERRIDECEV, FALSE); (pItem = (!IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_COMMANDSOURCE)) ? FindProcedure() : (CTCProceduresMonitorItem *)NULL); )
	{
		pItem->SetFlags((IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLECEV)) ? ((pItem->GetFlags() & ~TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDECEV) | TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLECEV) : (pItem->GetFlags() & ~TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLECEV));
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsContentsPage::OnOperationsReleaseWaitMode()
{
	m_bModes[0] = IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_RELEASEWAITMODE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsContentsPage::OnOperationsDisabled()
{
	m_bStateFlags[0] = IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLED);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsContentsPage::OnProcedureArguments()
{
	INT  nArgument;
	INT  nArguments;
	CString  szArgument;
	CString  szArguments;
	CTCProceduresMonitorItem  *pItem;
	CDatabaseTCProcedureArgument  *pArgument;
	CDatabaseTCProcedureArguments  pArguments;
	CTCProceduresMonitorArgumentValuesDialog  cArgumentValuesDialog;

	if ((pItem = FindProcedure()))
	{
		if (cArgumentValuesDialog.Create(this, pItem) == IDOK)
		{
			for (nArgument = 0, nArguments = pItem->GetArguments(pArguments); nArgument < nArguments; nArgument++)
			{
				if ((pArgument = pArguments.GetAt(nArgument)) != (CDatabaseTCProcedureArgument *)NULL)
				{
					szArgument.Format(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ARGUMENTSFORMAT), (LPCTSTR)pArgument->GetTag(), (LPCTSTR)pArgument->GetConstValueAsText());
					szArguments += (!szArguments.IsEmpty()) ? (STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ARGUMENTSSEPARATOR) + szArgument) : szArgument;
				}
			}
			if (!nArguments)
			{
				szArgument = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_NOARGUMENTS);
				szArguments = szArgument;
			}
			Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TITLEITEM_ARGUMENTS)), szArguments);
		}
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsContentsPage::OnProcedureExecution()
{
	UINT  nCount;
	CString  szMode;
	CString  szTrigger;
	CTimeKey  tStopTime;
	CTimeKey  tStartTime;
	CTimeSpan  tInterval;
	CStringTools  cStringTools;
	CTCProceduresMonitorItem  *pItem;
	CTCProceduresMonitorExecutionOptionsDialog  cExecutionOptionsDialog;

	if ((pItem = FindProcedure()))
	{
		if (cExecutionOptionsDialog.Create(this, pItem) == IDOK)
		{
			if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_NONE)
			{
				szTrigger = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERTYPE_NONE);
				szTrigger += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
			}
			if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_IMMEDIATELY)
			{
				szTrigger = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERTYPE_IMMEDIATELY);
				szTrigger += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
			}
			if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATSTARTUP)
			{
				szTrigger = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERTYPE_ATSTARTUP);
				szTrigger += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
			}
			if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATTIME)
			{
				szTrigger.Format(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERTYPE_ATTIME), (LPCTSTR)pItem->GetTriggerTime().FormatGmt());
				szTrigger += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
			}
			if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATDAILYTIME)
			{
				szTrigger.Format(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERTYPE_ATDAILYTIME), (LPCTSTR)CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + pItem->GetDailyTriggerTime().GetTotalSeconds()).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT)));
				szTrigger += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
			}
			if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATINTERVAL)
			{
				if (pItem->GetTriggerInterval(tStartTime, tInterval) || pItem->GetTriggerInterval(tStartTime, tInterval, tStopTime) || pItem->GetTriggerInterval(tStartTime, tInterval, nCount))
				{
					szTrigger.Format(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERTYPE_ATINTERVAL), (LPCTSTR)cStringTools.ConvertLongIntToStructuredString(tInterval.GetTotalSeconds()), (LPCTSTR)tStartTime.FormatGmt());
					szTrigger += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
				}
			}
			if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATEVENT)
			{
				szTrigger.Format(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERTYPE_ATEVENT), (LPCTSTR)pItem->GetTriggerEvent());
				szTrigger += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
			}
			for (; pItem->GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_AUTOMATIC; )
			{
				szMode = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_EXECUTIONMODE_AUTOMATIC);
				break;
			}
			for (; pItem->GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_SINGLESTEP; )
			{
				szMode = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_EXECUTIONMODE_SINGLESTEP);
				break;
			}
			for (; pItem->GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_EXTERNALACTIONS; )
			{
				szMode = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_EXECUTIONMODE_EXTERNALACTIONS);
				break;
			}
			for (; pItem->GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_COMMANDS; )
			{
				szMode = STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_EXECUTIONMODE_COMMANDS);
				break;
			}
			Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TITLEITEM_TRIGGERTYPE)), szTrigger);
			Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_TITLEITEM_EXECUTIONMODE)), szMode);
		}
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsContentsPage::OnProcedureCommands()
{
	INT  nItem;
	INT  nItems;
	CStringArray  szCommandOptions;
	CTCProceduresMonitorItem  *pItem[2];
	CTCProceduresMonitorCommandOptionsDialog  cCommandOptionsDialog;

	if ((pItem[0] = FindProcedure()))
	{
		for (nItem = 0, nItems = (cCommandOptionsDialog.Create(this, pItem[0]) == IDOK) ? (INT)m_pItems[0].GetSize() : 0, pItem[0]->GetReleaseConstraints(szCommandOptions); nItem < nItems; nItem++)
		{
			if ((pItem[1] = m_pItems[0].GetAt(nItem)) && pItem[0]->GetName() == pItem[1]->GetName())
			{
				pItem[1]->SetReleaseConstraints(szCommandOptions);
				continue;
			}
		}
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsContentsPage::OnProcedureAlerts()
{
	INT  nItem;
	INT  nItems;
	UINT  nAlertType;
	UINT  nAlertTypes;
	CString  szAudition;
	CStringArray  szNotifications;
	CTCProceduresMonitorItem  *pItem[2];
	CTCProceduresMonitorAlertOptionsDialog  cAlertOptionsDialog;

	if ((pItem[0] = FindProcedure()))
	{
		for (nItem = 0, nItems = (cAlertOptionsDialog.Create(this, pItem[0]) == IDOK) ? (INT)m_pItems[0].GetSize() : 0; nItem < nItems; nItem++)
		{
			if ((pItem[1] = m_pItems[0].GetAt(nItem)) != (CTCProceduresMonitorItem *)NULL  &&  pItem[0]->GetName() == pItem[1]->GetName())
			{
				for (nAlertType = 0, nAlertTypes = TCPROCEDURESMONITORITEM_ALERTTYPES; nAlertType < nAlertTypes; nAlertType++)
				{
					szAudition = pItem[0]->GetAudition(nAlertType);
					pItem[0]->GetNotifications(nAlertType, szNotifications);
					pItem[1]->SetAudition(nAlertType, szAudition);
					pItem[1]->SetAuditionColor(nAlertType, pItem[0]->GetAuditionColor(nAlertType));
					pItem[1]->EnableAuditionBlinking(nAlertType, pItem[0]->IsAuditionBlinkingEnabled(nAlertType));
					pItem[1]->EnableAcknowledgment(nAlertType, pItem[0]->IsAcknowledgmentEnabled(nAlertType));
					pItem[1]->SetAcknowledgmentColor(nAlertType, pItem[0]->GetAcknowledgmentColor(nAlertType));
					pItem[1]->SetNotifications(nAlertType, szNotifications);
				}
			}
		}
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorSettingsLoggingPage property page

IMPLEMENT_DYNCREATE(CTCProceduresMonitorSettingsLoggingPage, CLocalePropertyPage)

CTCProceduresMonitorSettingsLoggingPage::CTCProceduresMonitorSettingsLoggingPage() : CLocalePropertyPage(CTCProceduresMonitorSettingsLoggingPage::IDD)
{
	//{{AFX_DATA_INIT(CTCProceduresMonitorSettingsLoggingPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCProceduresMonitorSettingsLoggingPage::Initialize()
{
	if (GetParentDisplay()->GetLoggingOptions(m_nArchivalPolicy[0], m_szArchivalFileName[0], m_dwArchivalRetention[0], m_tArchivalRetention[0], m_szRetrievalFileName[0], m_nRetrievalReloadCount[0], m_bShowAsEvent[0]))
	{
		m_nArchivalPolicy[1] = m_nArchivalPolicy[0] = m_nArchivalPolicy[0] & ~LOGFILE_POLICY_RESET;
		m_szArchivalFileName[1] = m_szArchivalFileName[0];
		m_dwArchivalRetention[1] = m_dwArchivalRetention[0];
		m_tArchivalRetention[1] = m_tArchivalRetention[0];
		m_szRetrievalFileName[1] = m_szRetrievalFileName[0];
		m_nRetrievalReloadCount[1] = m_nRetrievalReloadCount[0];
		m_bShowAsEvent[1] = m_bShowAsEvent[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorSettingsLoggingPage::GetOptions(UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST
{
	nArchivalPolicy = m_nArchivalPolicy[0];
	szArchivalFileName = m_szArchivalFileName[0];
	dwArchivalRetention = m_dwArchivalRetention[0];
	tArchivalRetention = m_tArchivalRetention[0];
	szRetrievalFileName = m_szRetrievalFileName[0];
	nRetrievalReloadCount = m_nRetrievalReloadCount[0];
	bShowAsEvent = m_bShowAsEvent[0];
	return Check(FALSE);
}

CTCProceduresMonitorSettingsDialog *CTCProceduresMonitorSettingsLoggingPage::GetParentDialog() CONST
{
	return((CTCProceduresMonitorSettingsDialog *)CLocalePropertyPage::GetParent());
}

CTCProceduresMonitorWnd *CTCProceduresMonitorSettingsLoggingPage::GetParentDisplay() CONST
{
	return((CTCProceduresMonitorWnd *)GetParentDialog()->GetParentDisplay());
}

VOID CTCProceduresMonitorSettingsLoggingPage::ShowLoggingDetails()
{
	for (Spinbox_SetRange(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD_COUNT), TCPROCEDURESMONITORSETTINGSLOGGINGPAGE_MINIMUMRELOADCOUNT, TCPROCEDURESMONITORSETTINGSLOGGINGPAGE_MAXIMUMRELOADCOUNT), Spinbox_SetRange(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT), TCPROCEDURESMONITORSETTINGSLOGGINGPAGE_MINIMUMRETRIEVALSTOPCOUNT, TCPROCEDURESMONITORSETTINGSLOGGINGPAGE_MAXIMUMRETRIEVALSTOPCOUNT), CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_REALTIME, TRUE), CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL, FALSE), CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_SHOWASEVENT, m_bShowAsEvent[0]); m_nRetrievalReloadCount[0] > 0; )
	{
		Spinbox_SetPos(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD_COUNT), m_nRetrievalReloadCount[0]);
		CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD, TRUE);
		break;
	}
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD_COUNT)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD));
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD_COUNT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD));
	SetTimer(TCPROCEDURESMONITORSETTINGSLOGGINGPAGE_TIMERID, TCPROCEDURESMONITORSETTINGSLOGGINGPAGE_TIMEOUT, NULL);
	RetrieveLogEntries();
}

VOID CTCProceduresMonitorSettingsLoggingPage::ShowLogEntries(CONST CTCLogEntries &pEntries)
{
	INT  nEntry;
	INT  nEntries;
	CTCLogEntry  *pEntry;

	for (nEntry = 0, nEntries = (INT)pEntries.GetSize(); nEntry < nEntries; nEntry++)
	{
		if ((pEntry = pEntries.GetAt(nEntry)))
		{
			ShowLogEntry(pEntry, nEntry);
			continue;
		}
	}
	while (nEntries < SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_LIST, LVM_GETITEMCOUNT))
	{
		Listview_DeleteText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_LIST), nEntries);
		continue;
	}
	Listview_SetCurText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_LIST), 0);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_LIST)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorSettingsLoggingPage::ShowLogEntry(CONST CTCLogEntry *pEntry, INT nIndex)
{
	INT  nColumn;
	INT  nColumns;
	CString  szEntry;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_TITLEITEM_NAME); )
		{
			szEntry = pEntry->GetName();
			break;
		}
		for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_TITLEITEM_DESCRIPTION); )
		{
			szEntry = pEntry->GetDescription();
			break;
		}
		for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_TITLEITEM_ACTIVITY); )
		{
			szEntry = pEntry->GetActivity();
			break;
		}
		for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_TITLEITEM_TIME); )
		{
			szEntry = pEntry->GetTime().FormatGmt();
			break;
		}
		for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_TITLEITEM_USER); )
		{
			szEntry = pEntry->GetUser();
			break;
		}
		if ((nIndex >= SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_LIST, LVM_GETITEMCOUNT) || nIndex < 0) && !nColumn)
		{
			Listview_InsertText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_LIST), (nIndex < 0) ? (INT)SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_LIST, LVM_GETITEMCOUNT) : nIndex, szEntry);
			continue;
		}
		Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_LIST), (nIndex < 0) ? (INT)(SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_LIST, LVM_GETITEMCOUNT) - 1) : nIndex, nColumn, szEntry);
	}
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_LIST)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorSettingsLoggingPage::RetrieveLogEntries()
{
	CTCLogEntries  pEntries;

	if (RetrieveLogEntries(pEntries))
	{
		ShowLogEntries(pEntries);
		return TRUE;
	}
	return FALSE;
}
BOOL CTCProceduresMonitorSettingsLoggingPage::RetrieveLogEntries(CTCLogEntries &pEntries)
{
	INT  nCount;
	INT  nEntry;
	INT  nEntries;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeKey  tLogTime;
	CByteArray  nLogData;
	CTCLogEntry  *pEntry;

	for (pEntries.RemoveAll(); IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_REALTIME); )
	{
		if ((nCount = (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD)) ? (INT)Spinbox_GetPos(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD_COUNT)) : 0) > 0)
		{
			if (m_cRetrievalFile.Open(m_szRetrievalFileName[0], GetAccountSpacecraftName(), STRING(IDS_LOGFILETYPE_TCLOG), CFile::modeRead))
			{
				if (m_cRetrievalFile.SeekFromEnd(nCount))
				{
					do
					{
						if (m_cRetrievalFile.Read(tLogTime, nLogData))
						{
							if ((pEntry = new CTCLogEntry) != (CTCLogEntry *)NULL)
							{
								if (pEntry->Unmap(nLogData) && pEntries.Add(pEntry) >= 0) continue;
								delete pEntry;
							}
						}
						break;
					} while (TRUE);
					for (nEntry = 0, nEntries = (INT)(pEntries.GetSize() - nCount); nEntry < nEntries; nEntry++)
					{
						if ((pEntry = pEntries.GetAt(nEntry)))
						{
							pEntries.RemoveAt(nEntry);
							delete pEntry;
							nEntries--;
							nEntry--;
						}
					}
					m_cRetrievalFile.Close();
					return TRUE;
				}
				if (m_cRetrievalFile.IsEmpty())
				{
					m_cRetrievalFile.Close();
					return TRUE;
				}
				m_cRetrievalFile.Close();
			}
			return FALSE;
		}
		return TRUE;
	}
	if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL))
	{
		if (m_cRetrievalFile.Open(m_szRetrievalFileName[0], GetAccountSpacecraftName(), STRING(IDS_LOGFILETYPE_TCLOG), CFile::modeRead))
		{
			for (tStartTime = Timespinbox_GetTime(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STARTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPTIME)), nCount = (INT)Spinbox_GetPos(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT)); m_cRetrievalFile.SeekTo(tStartTime); )
			{
				do
				{
					if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATTIME))
					{
						if (m_cRetrievalFile.Read(tLogTime, nLogData) && tLogTime <= tStopTime)
						{
							if ((pEntry = new CTCLogEntry))
							{
								if (tLogTime < tStartTime)
								{
									delete pEntry;
									continue;
								}
								if (pEntry->Unmap(nLogData) && pEntries.Add(pEntry) >= 0) continue;
								delete pEntry;
							}
						}
						break;
					}
					if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATLIMIT))
					{
						if (m_cRetrievalFile.Read(tLogTime, nLogData) && nCount > pEntries.GetSize())
						{
							if ((pEntry = new CTCLogEntry))
							{
								if (tLogTime < tStartTime)
								{
									delete pEntry;
									continue;
								}
								if (pEntry->Unmap(nLogData) && pEntries.Add(pEntry) >= 0) continue;
								delete pEntry;
							}
						}
						break;
					}
					if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_NOLIMIT))
					{
						if (m_cRetrievalFile.Read(tLogTime, nLogData))
						{
							if ((pEntry = new CTCLogEntry))
							{
								if (tLogTime < tStartTime)
								{
									delete pEntry;
									continue;
								}
								if (pEntry->Unmap(nLogData) && pEntries.Add(pEntry) >= 0) continue;
								delete pEntry;
							}
						}
					}
					break;
				} while (TRUE);
				m_cRetrievalFile.Close();
				return TRUE;
			}
			if (m_cRetrievalFile.IsEmpty())
			{
				m_cRetrievalFile.Close();
				return TRUE;
			}
			m_cRetrievalFile.Close();
		}
	}
	return FALSE;
}

VOID CTCProceduresMonitorSettingsLoggingPage::AdjustToPrivileges()
{
	BOOL  bCheck;

	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_REALTIME, (bCheck = CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)));
	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD_COUNT, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STARTTIME, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATTIME, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPTIME, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATLIMIT, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_NOLIMIT, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_SHOWASEVENT, bCheck);
}

BOOL CTCProceduresMonitorSettingsLoggingPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (m_nArchivalPolicy[0] != m_nArchivalPolicy[1] || m_szArchivalFileName[0].CompareNoCase(m_szArchivalFileName[1]) || m_dwArchivalRetention[0] != m_dwArchivalRetention[1] || m_tArchivalRetention[0] != m_tArchivalRetention[1] || m_szRetrievalFileName[0].CompareNoCase(m_szRetrievalFileName[1]) || m_nRetrievalReloadCount[0] != m_nRetrievalReloadCount[1] || m_bShowAsEvent[0] != m_bShowAsEvent[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CTCProceduresMonitorSettingsLoggingPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? TRUE : CLocalePropertyPage::Check()) : TRUE);
}

void CTCProceduresMonitorSettingsLoggingPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProceduresMonitorSettingsLoggingPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCProceduresMonitorSettingsLoggingPage::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorSettingsLoggingPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CTCProceduresMonitorSettingsLoggingPage)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_REALTIME, OnRealtime)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL, OnHistorical)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD, OnReloadCount)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_OPTIONS, OnOptions)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATTIME, OnStopAtTime)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATLIMIT, OnStopAtLimit)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_NOLIMIT, OnStopAtEnd)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_RETRIEVE, OnRetrieve)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_SHOWASEVENT, OnShowAsEvent)
	ON_CONTROL(SBXN_CHANGE, IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD_COUNT, OnSpinchangeReloadCount)
	ON_CONTROL(TSBXN_CHANGE, IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STARTTIME, OnSpinchangeStartTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPTIME, OnSpinchangeStopTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorSettingsLoggingPage message handlers

BOOL CTCProceduresMonitorSettingsLoggingPage::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_TITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_TITLEITEM_DESCRIPTION));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_TITLEITEM_ACTIVITY));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_TITLEITEM_TIME));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_TITLEITEM_USER));
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_LIST)->GetClientRect(rColumns);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_LIST), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_TITLEITEM_NAME)) ? (rColumns.Width() / 3) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_TITLEITEM_DESCRIPTION) || m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_TITLEITEM_ACTIVITY)) ? (rColumns.Width() / 2) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_TITLEITEM_TIME)) ? (rColumns.Width() / 4) : (rColumns.Width() / 5))));
		continue;
	}
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_OPTIONS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_MODE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_REALTIME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_SHOWASEVENT)->EnableWindow();
	ShowLoggingDetails();
	AdjustToPrivileges();
	return TRUE;
}

void CTCProceduresMonitorSettingsLoggingPage::OnRealtime()
{
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_REALTIME, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATTIME, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATLIMIT, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_NOLIMIT, FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STARTTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STARTTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATLIMIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_NOLIMIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_RETRIEVE)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD));
}

void CTCProceduresMonitorSettingsLoggingPage::OnHistorical()
{
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_REALTIME, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATTIME, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATLIMIT, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_NOLIMIT, TRUE);
	Timespinbox_SetTime(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STARTTIME), CTimeKey(CTime::GetCurrentTime().GetTime() - SECONDSPERHOUR));
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD_COUNT)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD_COUNT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STARTTIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STARTTIME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATTIME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATLIMIT)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_NOLIMIT)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_RETRIEVE)->EnableWindow();
}

void CTCProceduresMonitorSettingsLoggingPage::OnReloadCount()
{
	m_nRetrievalReloadCount[0] = (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD)) ? TCPROCEDURESMONITORSETTINGSLOGGINGPAGE_DEFAULTRELOADCOUNT : 0;
	Spinbox_SetPos(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD_COUNT), TCPROCEDURESMONITORSETTINGSLOGGINGPAGE_DEFAULTRELOADCOUNT);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD_COUNT)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD));
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD_COUNT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD));
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_RETRIEVE)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD));
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD_COUNT)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsLoggingPage::OnStopAtTime()
{
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATTIME, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATLIMIT, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_NOLIMIT, FALSE);
	Timespinbox_SetTime(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPTIME), CTimeKey(CTime::GetCurrentTime().GetTime()));
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPTIME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPTIME)->SetFocus();
}

void CTCProceduresMonitorSettingsLoggingPage::OnStopAtLimit()
{
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATTIME, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATLIMIT, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_NOLIMIT, FALSE);
	Spinbox_SetPos(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT), TCPROCEDURESMONITORSETTINGSLOGGINGPAGE_DEFAULTRETRIEVALSTOPCOUNT);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT)->SetFocus();
}

void CTCProceduresMonitorSettingsLoggingPage::OnStopAtEnd()
{
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATTIME, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATLIMIT, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_NOLIMIT, TRUE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT_STATIC)->EnableWindow(FALSE);
}

void CTCProceduresMonitorSettingsLoggingPage::OnOptions()
{
	CTCProceduresMonitorLoggingOptionsDialog  cLoggingOptionsDialog;

	for (cLoggingOptionsDialog.Create(this, m_szArchivalFileName[0], m_nArchivalPolicy[0], m_dwArchivalRetention[0], m_tArchivalRetention[0], m_szRetrievalFileName[0]); m_nArchivalPolicy[0] & LOGFILE_POLICY_RESET; )
	{
		if (m_cRetrievalFile.Open(m_szRetrievalFileName[0], GetAccountSpacecraftName(), STRING(IDS_LOGFILETYPE_TCLOG), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite))
		{
			m_cRetrievalFile.Reset();
			m_cRetrievalFile.Close();
			RetrieveLogEntries();
		}
		m_nArchivalPolicy[0] &= ~LOGFILE_POLICY_RESET;
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsLoggingPage::OnRetrieve()
{
	CHourglassCursor  cCursor;

	RetrieveLogEntries();
}

void CTCProceduresMonitorSettingsLoggingPage::OnShowAsEvent()
{
	m_bShowAsEvent[0] = IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_SHOWASEVENT);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsLoggingPage::OnSpinchangeReloadCount()
{
	m_nRetrievalReloadCount[0] = (UINT)Spinbox_GetPos(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD_COUNT));
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_RETRIEVE)->EnableWindow();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsLoggingPage::OnSpinchangeStartTime()
{
	CTimeKey  tTime[2];

	for (tTime[0] = Timespinbox_GetTime(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STARTTIME)), tTime[1] = Timespinbox_GetTime(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPTIME)); tTime[0] > tTime[1]; )
	{
		Timespinbox_SetTime(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPTIME), tTime[0]);
		break;
	}
}

void CTCProceduresMonitorSettingsLoggingPage::OnSpinchangeStopTime()
{
	CTimeKey  tTime[2];

	for (tTime[0] = Timespinbox_GetTime(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STARTTIME)), tTime[1] = Timespinbox_GetTime(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPTIME)); tTime[0] > tTime[1]; )
	{
		Timespinbox_SetTime(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STARTTIME), tTime[1]);
		break;
	}
}

void CTCProceduresMonitorSettingsLoggingPage::OnTimer(UINT_PTR nEventID)
{
	CByteArray  nLogData;
	CTCLogEntry  *pEntry;

	if (nEventID == TCPROCEDURESMONITORSETTINGSLOGGINGPAGE_TIMERID)
	{
		if (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_REALTIME))
		{
			if (m_cRetrievalFile.Open(m_szRetrievalFileName[0], GetAccountSpacecraftName(), STRING(IDS_LOGFILETYPE_TCLOG), CFile::modeRead))
			{
				if (m_cRetrievalFile.IsWatched() || m_cRetrievalFile.BeginWatch())
				{
					if (m_cRetrievalFile.Watch(nLogData))
					{
						do
						{
							if ((pEntry = new CTCLogEntry))
							{
								if (pEntry->Unmap(nLogData)) ShowLogEntry(pEntry);
								delete pEntry;
							}
						} while (m_cRetrievalFile.Watch(nLogData));
					}
				}
				m_cRetrievalFile.Close();
			}
		}
	}
	CLocalePropertyPage::OnTimer(nEventID);
}

void CTCProceduresMonitorSettingsLoggingPage::OnDestroy()
{
	if (m_cRetrievalFile.Open(m_szRetrievalFileName[0], GetAccountSpacecraftName(), STRING(IDS_LOGFILETYPE_TCLOG), CFile::modeRead))
	{
		m_cRetrievalFile.EndWatch();
		m_cRetrievalFile.Close();
	}
	KillTimer(TCPROCEDURESMONITORSETTINGSLOGGINGPAGE_TIMERID);
	CLocalePropertyPage::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorSettingsPrintingComments

IMPLEMENT_DYNCREATE(CTCProceduresMonitorSettingsPrintingComments, CEdit)

BEGIN_MESSAGE_MAP(CTCProceduresMonitorSettingsPrintingComments, CEdit)
	//{{AFX_MSG_MAP(CTCProceduresMonitorSettingsPrintingComments)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorSettingsPrintingComments message handlers

void CTCProceduresMonitorSettingsPrintingComments::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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
// CTCProceduresMonitorSettingsPrintingPage property page

IMPLEMENT_DYNCREATE(CTCProceduresMonitorSettingsPrintingPage, CLocalePropertyPage)

CTCProceduresMonitorSettingsPrintingPage::CTCProceduresMonitorSettingsPrintingPage() : CLocalePropertyPage(CTCProceduresMonitorSettingsPrintingPage::IDD)
{
	//{{AFX_DATA_INIT(CTCProceduresMonitorSettingsPrintingPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCProceduresMonitorSettingsPrintingPage::Initialize()
{
	return((GetParentDisplay()->GetPrintJobs(m_pJobs[0])) ? m_pJobs[1].Copy(&m_pJobs[0]) : FALSE);
}

BOOL CTCProceduresMonitorSettingsPrintingPage::GetJobs(CTCProceduresMonitorPrintJobs &pJobs) CONST
{
	return((pJobs.Copy(&m_pJobs[0])) ? Check(FALSE) : FALSE);
}

CTCProceduresMonitorSettingsDialog *CTCProceduresMonitorSettingsPrintingPage::GetParentDialog() CONST
{
	return((CTCProceduresMonitorSettingsDialog *)CLocalePropertyPage::GetParent());
}

CTCProceduresMonitorWnd *CTCProceduresMonitorSettingsPrintingPage::GetParentDisplay() CONST
{
	return((CTCProceduresMonitorWnd *)GetParentDialog()->GetParentDisplay());
}

VOID CTCProceduresMonitorSettingsPrintingPage::ShowJobInfo()
{
	UINT  nMode;
	UINT  nScale;
	CTCProceduresMonitorPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLIST, ((nMode = pJobInfo->GetPrintMode()) & TCPROCEDURESMONITOR_PRINT_LIST) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTONEONLY, (nMode & TCPROCEDURESMONITOR_PRINT_ONEONLY) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTFLOWCHART, (nMode & TCPROCEDURESMONITOR_PRINT_FLOWCHART) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_AUTOSCALE, (nMode & TCPROCEDURESMONITOR_PRINT_AUTOSCALE) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE, (nMode & TCPROCEDURESMONITOR_PRINT_FIXEDSCALE) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_CLEARCOMMENTS, (nMode & TCPROCEDURESMONITOR_PRINT_CLEARCOMMENTS) ? TRUE : FALSE);
		SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PROFILE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetProfile()));
		Spinbox_SetPos(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE_NUMBER), ((nMode & TCPROCEDURESMONITOR_PRINT_FIXEDSCALE) && pJobInfo->GetPrintScale(nScale)) ? nScale : 0);
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_COMMENTSTEXT)->SetWindowText(pJobInfo->GetComments());
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PROFILE_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PROFILE)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_OPTIONS)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLIST)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTONEONLY)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTFLOWCHART)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTONEONLY));
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTFLOWCHART));
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_AUTOSCALE)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTFLOWCHART));
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTFLOWCHART));
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTFLOWCHART) && IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE));
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTFLOWCHART) && IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE));
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_COMMENTS)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_COMMENTSTEXT_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_COMMENTSTEXT)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_CLEARCOMMENTS)->EnableWindow(!pJobInfo->GetComments().IsEmpty());
		return;
	}
	SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PROFILE, CB_SETCURSEL, (WPARAM)-1);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLIST, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTONEONLY, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTFLOWCHART, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_AUTOSCALE, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_CLEARCOMMENTS, FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_COMMENTSTEXT)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_DETAILS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PROFILE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PROFILE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_OPTIONS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTONEONLY)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTFLOWCHART)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_AUTOSCALE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_COMMENTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_COMMENTSTEXT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_COMMENTSTEXT)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_CLEARCOMMENTS)->EnableWindow(FALSE);
}

CTCProceduresMonitorPrintJobInfo *CTCProceduresMonitorSettingsPrintingPage::FindJobInfo() CONST
{
	return m_pJobs[0].GetAt(m_pJobs[0].Find(STRING(IDS_PRINTJOB_DEFAULTNAME)));
}

BOOL CTCProceduresMonitorSettingsPrintingPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_pJobs[0].Compare(&m_pJobs[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CTCProceduresMonitorSettingsPrintingPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PROFILE)->SendMessage(CB_GETCURSEL) >= 0 && (!IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTONEONLY) || IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLIST) || IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTFLOWCHART))) : CLocalePropertyPage::Check()) : TRUE);
}

void CTCProceduresMonitorSettingsPrintingPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProceduresMonitorSettingsPrintingPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCProceduresMonitorSettingsPrintingPage::PostNcDestroy()
{
	m_pJobs[0].RemoveAll();
	m_pJobs[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorSettingsPrintingPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CTCProceduresMonitorSettingsPrintingPage)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLIST, OnPrintList)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTFLOWCHART, OnPrintFlowchart)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTONEONLY, OnPrintOneOnly)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_AUTOSCALE, OnPrintAutomaticScale)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE, OnPrintFixedScale)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_CLEARCOMMENTS, OnResetComments)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PROFILE, OnSelchangeProfile)
	ON_EN_CHANGE(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_COMMENTSTEXT, OnEditchangeComments)
	ON_CONTROL(SBXN_CHANGE, IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE_NUMBER, OnSpinchangePrintFixedScale)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorSettingsPrintingPage message handlers

BOOL CTCProceduresMonitorSettingsPrintingPage::OnInitDialog()
{
	INT  nProfile;
	INT  nProfiles;
	CStringArray  szProfiles;
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	for (nProfile = 0, nProfiles = (EnumPrintProfiles(szProfiles)) ? (INT)szProfiles.GetSize() : 0, Spinbox_SetRange(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE_NUMBER), TCPROCEDURESMONITORSETTINGSPRINTINGPAGE_MINIMUMSCALE, TCPROCEDURESMONITORSETTINGSPRINTINGPAGE_MAXIMUMSCALE), m_wndComments.SubclassWindow(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_COMMENTSTEXT)->GetSafeHwnd()); nProfile < nProfiles; nProfile++)
	{
		SendDlgItemMessage(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PROFILE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szProfiles.GetAt(nProfile));
		continue;
	}
	ShowJobInfo();
	return TRUE;
}

void CTCProceduresMonitorSettingsPrintingPage::OnSelchangeProfile()
{
	CString  szProfile;
	CTCProceduresMonitorPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PROFILE)->GetWindowText(szProfile);
		pJobInfo->SetProfile(szProfile);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsPrintingPage::OnPrintList()
{
	UINT  nMode;
	CTCProceduresMonitorPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLIST)) ? (pJobInfo->GetPrintMode() | TCPROCEDURESMONITOR_PRINT_LIST) : (pJobInfo->GetPrintMode() & ~TCPROCEDURESMONITOR_PRINT_LIST);
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsPrintingPage::OnPrintFlowchart()
{
	CTCProceduresMonitorPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		pJobInfo->SetPrintMode((IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTFLOWCHART)) ? (pJobInfo->GetPrintMode() | TCPROCEDURESMONITOR_PRINT_FLOWCHART | TCPROCEDURESMONITOR_PRINT_FIXEDSCALE) : (pJobInfo->GetPrintMode() & ~(TCPROCEDURESMONITOR_PRINT_FLOWCHART | TCPROCEDURESMONITOR_PRINT_AUTOSCALE | TCPROCEDURESMONITOR_PRINT_FIXEDSCALE)));
		pJobInfo->SetPrintScale(TCPROCEDURESMONITORSETTINGSPRINTINGPAGE_DEFAULTSCALE);
	}
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_AUTOSCALE, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE, IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTFLOWCHART));
	Spinbox_SetPos(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE_NUMBER), TCPROCEDURESMONITORSETTINGSPRINTINGPAGE_DEFAULTSCALE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTFLOWCHART));
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_AUTOSCALE)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTFLOWCHART));
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTFLOWCHART));
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTFLOWCHART));
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTFLOWCHART));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsPrintingPage::OnPrintOneOnly()
{
	UINT  nMode;
	CTCProceduresMonitorPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTONEONLY)) ? (pJobInfo->GetPrintMode() | TCPROCEDURESMONITOR_PRINT_ONEONLY) : (pJobInfo->GetPrintMode() & ~(TCPROCEDURESMONITOR_PRINT_ONEONLY | TCPROCEDURESMONITOR_PRINT_FLOWCHART | TCPROCEDURESMONITOR_PRINT_AUTOSCALE | TCPROCEDURESMONITOR_PRINT_FIXEDSCALE));
		pJobInfo->SetPrintMode(nMode);
		pJobInfo->SetPrintScale(0);
	}
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTFLOWCHART, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_AUTOSCALE, FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTFLOWCHART)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTONEONLY));
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTFLOWCHART));
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_AUTOSCALE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsPrintingPage::OnPrintAutomaticScale()
{
	CTCProceduresMonitorPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo())) pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | TCPROCEDURESMONITOR_PRINT_AUTOSCALE) & ~TCPROCEDURESMONITOR_PRINT_FIXEDSCALE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsPrintingPage::OnPrintFixedScale()
{
	CTCProceduresMonitorPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | TCPROCEDURESMONITOR_PRINT_FIXEDSCALE) & ~TCPROCEDURESMONITOR_PRINT_AUTOSCALE);
		pJobInfo->SetPrintScale(TCPROCEDURESMONITORSETTINGSPRINTINGPAGE_DEFAULTSCALE);
	}
	Spinbox_SetPos(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE_NUMBER), TCPROCEDURESMONITORSETTINGSPRINTINGPAGE_DEFAULTSCALE);
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE_NUMBER)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsPrintingPage::OnSpinchangePrintFixedScale()
{
	CTCProceduresMonitorPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo())) pJobInfo->SetPrintScale((UINT)Spinbox_GetPos(GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE_NUMBER)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsPrintingPage::OnEditchangeComments()
{
	CString  szComments;
	CTCProceduresMonitorPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_COMMENTSTEXT)->GetWindowText(szComments);
		GetDlgItem(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_CLEARCOMMENTS)->EnableWindow(!szComments.IsEmpty());
		CheckDlgButton(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_CLEARCOMMENTS, (!szComments.IsEmpty()) ? IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_CLEARCOMMENTS) : FALSE);
		pJobInfo->SetPrintMode((IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_CLEARCOMMENTS)) ? (pJobInfo->GetPrintMode() | TCPROCEDURESMONITOR_PRINT_CLEARCOMMENTS) : (pJobInfo->GetPrintMode() & ~TCPROCEDURESMONITOR_PRINT_CLEARCOMMENTS));
		pJobInfo->SetComments(szComments);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorSettingsPrintingPage::OnResetComments()
{
	UINT  nMode;
	CTCProceduresMonitorPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (IsDlgButtonChecked(IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_CLEARCOMMENTS)) ? (pJobInfo->GetPrintMode() | TCPROCEDURESMONITOR_PRINT_CLEARCOMMENTS) : (pJobInfo->GetPrintMode() & ~TCPROCEDURESMONITOR_PRINT_CLEARCOMMENTS);
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorSettingsTabCtrl

IMPLEMENT_DYNCREATE(CTCProceduresMonitorSettingsTabCtrl, CTabCtrl)

BEGIN_MESSAGE_MAP(CTCProceduresMonitorSettingsTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CTCProceduresMonitorSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorSettingsTabCtrl message handlers


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorSettingsDialog

IMPLEMENT_DYNCREATE(CTCProceduresMonitorSettingsDialog, CDisplayPropertySheetDialog)

CTCProceduresMonitorSettingsDialog::CTCProceduresMonitorSettingsDialog() : CDisplayPropertySheetDialog()
{
	AddPage(&m_pageLayout);
	AddPage(&m_pageContents);
	AddPage(&m_pageLogging);
	AddPage(&m_pagePrinting);
}

BOOL CTCProceduresMonitorSettingsDialog::GetColumns(CUIntArray &nColumns) CONST
{
	return m_pageLayout.GetColumns(nColumns);
}

BOOL CTCProceduresMonitorSettingsDialog::GetTitleFont(LPLOGFONT pTitleFont) CONST
{
	return m_pageLayout.GetTitleFont(pTitleFont);
}

BOOL CTCProceduresMonitorSettingsDialog::GetItemsFont(LPLOGFONT pItemsFont) CONST
{
	return m_pageLayout.GetItemsFont(pItemsFont);
}

BOOL CTCProceduresMonitorSettingsDialog::GetSourceCodeFont(LPLOGFONT pCodeFont) CONST
{
	return m_pageLayout.GetSourceCodeFont(pCodeFont);
}

BOOL CTCProceduresMonitorSettingsDialog::GetFlowchartLabelsFont(LPLOGFONT pLabelsFont) CONST
{
	return m_pageLayout.GetFlowchartLabelsFont(pLabelsFont);
}

BOOL CTCProceduresMonitorSettingsDialog::GetFlowchartLabelsColor(COLORREF &nColor) CONST
{
	return m_pageLayout.GetFlowchartLabelsColor(nColor);
}

BOOL CTCProceduresMonitorSettingsDialog::GetFlowchartBackgroundColor(COLORREF &nColor) CONST
{
	return m_pageLayout.GetFlowchartBackgroundColor(nColor);
}

BOOL CTCProceduresMonitorSettingsDialog::GetToolTipMode(BOOL &bEnable) CONST
{
	return m_pageLayout.GetToolTipMode(bEnable);
}

BOOL CTCProceduresMonitorSettingsDialog::IsLayoutModified() CONST
{
	return m_pageLayout.IsModified();
}

BOOL CTCProceduresMonitorSettingsDialog::GetContents(CTCProceduresMonitorItems &pItems) CONST
{
	return m_pageContents.GetContents(pItems);
}

BOOL CTCProceduresMonitorSettingsDialog::GetCheckOptions(UINT &nFlags) CONST
{
	return m_pageContents.GetCheckOptions(nFlags);
}

BOOL CTCProceduresMonitorSettingsDialog::GetReleaseWaitModeFlag(BOOL &bEnabled) CONST
{
	return m_pageContents.GetReleaseWaitModeFlag(bEnabled);
}

BOOL CTCProceduresMonitorSettingsDialog::GetDisabledStateFlag(BOOL &bFlag) CONST
{
	return m_pageContents.GetDisabledStateFlag(bFlag);
}

BOOL CTCProceduresMonitorSettingsDialog::IsContentsModified() CONST
{
	return m_pageContents.IsModified();
}

BOOL CTCProceduresMonitorSettingsDialog::GetLoggingOptions(UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST
{
	return m_pageLogging.GetOptions(nArchivalPolicy, szArchivalFileName, dwArchivalRetention, tArchivalRetention, szRetrievalFileName, nRetrievalReloadCount, bShowAsEvent);
}

BOOL CTCProceduresMonitorSettingsDialog::IsLoggingModified() CONST
{
	return m_pageLogging.IsModified();
}

BOOL CTCProceduresMonitorSettingsDialog::GetPrintJobs(CTCProceduresMonitorPrintJobs &pPrintJobs) CONST
{
	return m_pagePrinting.GetJobs(pPrintJobs);
}

BOOL CTCProceduresMonitorSettingsDialog::IsPrintingModified() CONST
{
	return m_pagePrinting.IsModified();
}

CTCProceduresMonitorWnd *CTCProceduresMonitorSettingsDialog::GetParentDisplay() CONST
{
	return((CTCProceduresMonitorWnd *)CDisplayPropertySheetDialog::GetParentDisplay());
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorSettingsDialog, CDisplayPropertySheetDialog)
	//{{AFX_MSG_MAP(CTCProceduresMonitorSettingsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorSettingsDialog message handlers

BOOL CTCProceduresMonitorSettingsDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayPropertySheetDialog::OnInitDialog();
	SetTitle(STRING(IDS_TCPROCEDURESMONITORSETTINGSDIALOG_TITLE));
	if (m_wndTabCtrl.SubclassWindow(GetTabControl()->GetSafeHwnd()))
	{
		m_wndTabCtrl.SetFocus();
		return FALSE;
	}
	return TRUE;
}

void CTCProceduresMonitorSettingsDialog::OnOK()
{
	CHourglassCursor  cCursor;

	ReportEvent((!GetParentDisplay()->OnCloseSettingsDialog(IDOK)) ? SYSTEM_WARNING_TCPROCEDURESMONITOR_SETUP_FAILURE : SYSTEM_NOERROR);
	CDisplayPropertySheetDialog::OnOK();
}

void CTCProceduresMonitorSettingsDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	GetParentDisplay()->OnCloseSettingsDialog(IDCANCEL);
	CDisplayPropertySheetDialog::OnCancel();
}

BOOL CTCProceduresMonitorSettingsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORSETTINGSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCProceduresMonitorSettingsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORSETTINGSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorArgumentParametersCalibrationPage property page

IMPLEMENT_DYNCREATE(CTCProceduresMonitorArgumentParametersCalibrationPage, CLocalePropertyPage)

CTCProceduresMonitorArgumentParametersCalibrationPage::CTCProceduresMonitorArgumentParametersCalibrationPage() : CLocalePropertyPage(CTCProceduresMonitorArgumentParametersCalibrationPage::IDD)
{
	//{{AFX_DATA_INIT(CTCProceduresMonitorArgumentParametersCalibrationPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CTCProceduresMonitorArgumentParametersCalibrationPage::ShowParameterInfo(CONST CDatabaseTCParameter *pTCParameter)
{
	INT  nIndex;
	CString  szName;
	CDatabaseTCNumCalTable  *pTCNumCalTable;
	CDatabaseTCTxtCalTable  *pTCTxtCalTable;

	for (SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_NAME, CB_RESETCONTENT), m_nCalTableIDs.RemoveAll(); pTCParameter; )
	{
		if ((m_nCalTableType = (pTCParameter->GetAttributes() & (TCPARAMETER_CALIBRATION_NUMERICAL | TCPARAMETER_CALIBRATION_STATUS))) == TCPARAMETER_CALIBRATION_NUMERICAL)
		{
			if ((pTCNumCalTable = GetDatabase()->GetTCNumCalTables()->GetAt((nIndex = pTCParameter->GetCalTableRef()))) != (CDatabaseTCNumCalTable *)NULL)
			{
				for (szName.Format(STRING(IDS_TCPROCEDURESMONITORARGUMENTPARAMETERS_CALIBRATIONPAGE_TABLE_FORMAT), (LPCTSTR)pTCNumCalTable->GetDescription(), (LPCTSTR)pTCNumCalTable->GetName()); pTCNumCalTable->GetDescription().IsEmpty(); )
				{
					szName = pTCNumCalTable->GetName();
					break;
				}
				SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szName);
				m_nCalTableIDs.Add(nIndex);
			}
		}
		if (pTCParameter->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS)
		{
			if ((pTCTxtCalTable = GetDatabase()->GetTCTxtCalTables()->GetAt((nIndex = pTCParameter->GetCalTableRef()))))
			{
				for (szName.Format(STRING(IDS_TCPROCEDURESMONITORARGUMENTPARAMETERS_CALIBRATIONPAGE_TABLE_FORMAT), (LPCTSTR)pTCTxtCalTable->GetDescription(), (LPCTSTR)pTCTxtCalTable->GetName()); pTCTxtCalTable->GetDescription().IsEmpty(); )
				{
					szName = pTCTxtCalTable->GetName();
					break;
				}
				SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szName);
				m_nCalTableIDs.Add(nIndex);
			}
		}
		break;
	}
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_NAME, CB_SETCURSEL);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_NAME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_NAME)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	ShowCalibrationInfo();
}

VOID CTCProceduresMonitorArgumentParametersCalibrationPage::ShowCalibrationInfo()
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
	CDatabaseTCNumCalTable  *pTCNumCalTable;
	CDatabaseTCNumCalPoint  *pTCNumCalPoint;
	CDatabaseTCTxtCalTable  *pTCTxtCalTable;
	CDatabaseTCTxtCalPoint  *pTCTxtCalPoint;

	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_DELETEALLITEMS);
	if ((nIndex = (INT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCURSEL)) >= 0)
	{
		if ((pTCNumCalTable = (m_nCalTableType == TCPARAMETER_CALIBRATION_NUMERICAL) ? GetDatabase()->GetTCNumCalTables()->GetAt(m_nCalTableIDs.GetAt(nIndex)) : (CDatabaseTCNumCalTable *)NULL))
		{
			for (nItem = 0, nItems = (INT)pTCNumCalTable->GetSize(); nItem < nItems; nItem++)
			{
				if ((pTCNumCalPoint = pTCNumCalTable->GetAt(nItem)))
				{
					for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
					{
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORARGUMENTPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER); )
						{
							szItem = cStringTools.ConvertIntToString(nItem + 1);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORARGUMENTPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X); )
						{
							szItem = cStringTools.ConvertFloatToTruncatedString(pTCNumCalPoint->GetX());
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORARGUMENTPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y); )
						{
							szItem = cStringTools.ConvertFloatToString(pTCNumCalPoint->GetY());
							break;
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS), nItem, szItem);
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS), nItem, nColumn, szItem);
					}
				}
			}
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(pTCNumCalTable->GetName());
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(STRING(IDS_TCPROCEDURESMONITORARGUMENTPARAMETERS_CALIBRATIONPAGE_TYPE_NUMERICAL));
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow((GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow((GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow();
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow();
			return;
		}
		if ((pTCTxtCalTable = (m_nCalTableType == TCPARAMETER_CALIBRATION_STATUS) ? GetDatabase()->GetTCTxtCalTables()->GetAt(m_nCalTableIDs.GetAt(nIndex)) : (CDatabaseTCTxtCalTable *)NULL))
		{
			for (nItem = 0, nItems = (INT)pTCTxtCalTable->GetSize(); nItem < nItems; nItem++)
			{
				if ((pTCTxtCalPoint = pTCTxtCalTable->GetAt(nItem)))
				{
					for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
					{
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORARGUMENTPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER); )
						{
							szItem = cStringTools.ConvertIntToString(nItem + 1);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORARGUMENTPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X); )
						{
							if (pTCTxtCalPoint->GetRange(fCalPtX, fCalPtY, szCalText) || pTCTxtCalPoint->GetPoint(fCalPtX, szCalText))
							{
								for (szCalPtX = szItem = cStringTools.ConvertFloatToTruncatedString(fCalPtX, -1), szCalPtY = cStringTools.ConvertFloatToTruncatedString(fCalPtY, -1); fCalPtX != fCalPtY; )
								{
									szItem.Format(STRING(IDS_TCPROCEDURESMONITORARGUMENTPARAMETERS_CALIBRATIONPAGE_POINT_RANGE), (LPCTSTR)szCalPtX, (LPCTSTR)szCalPtY);
									break;
								}
								break;
							}
							szItem.Empty();
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORARGUMENTPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y); )
						{
							szItem = (pTCTxtCalPoint->GetPoint(fCalPtX, szCalText) || pTCTxtCalPoint->GetRange(fCalPtX, fCalPtY, szCalText)) ? (LPCTSTR)szCalText : EMPTYSTRING;
							break;
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS), nItem, szItem);
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS), nItem, nColumn, szItem);
					}
				}
			}
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(pTCTxtCalTable->GetName());
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(STRING(IDS_TCPROCEDURESMONITORARGUMENTPARAMETERS_CALIBRATIONPAGE_TYPE_STATUS));
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow((GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow((GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow();
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow();
			return;
		}
	}
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow(FALSE);
}

BOOL CTCProceduresMonitorArgumentParametersCalibrationPage::GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST
{
	szX = Listview_GetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS)), FindColumnIndex(STRING(IDS_TCPROCEDURESMONITORARGUMENTPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X)));
	szY = Listview_GetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS)), FindColumnIndex(STRING(IDS_TCPROCEDURESMONITORARGUMENTPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y)));
	return((!szX.IsEmpty() && !szY.IsEmpty()) ? TRUE : FALSE);
}

CTCProceduresMonitorArgumentParametersFolder *CTCProceduresMonitorArgumentParametersCalibrationPage::GetParent() CONST
{
	return((CTCProceduresMonitorArgumentParametersFolder *)CLocalePropertyPage::GetParent());
}

INT CTCProceduresMonitorArgumentParametersCalibrationPage::FindColumnIndex(LPCTSTR pszColumn) CONST
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == pszColumn) break;
		continue;
	}
	return((nColumn < nColumns) ? nColumn : -1);
}

void CTCProceduresMonitorArgumentParametersCalibrationPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProceduresMonitorArgumentParametersCalibrationPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCProceduresMonitorArgumentParametersCalibrationPage::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_nCalTableIDs.RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorArgumentParametersCalibrationPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CTCProceduresMonitorArgumentParametersCalibrationPage)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_NAME, OnSelchangeName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorArgumentParametersCalibrationPage message handlers

BOOL CTCProceduresMonitorArgumentParametersCalibrationPage::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORARGUMENTPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORARGUMENTPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORARGUMENTPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS)->GetClientRect(rColumns);
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = (rColumns.Width() - GetSystemMetrics(SM_CXVSCROLL)) / 5; nColumn < nColumns; nWidth = (++nColumn > 0) ? (2 * (rColumns.Width() - GetSystemMetrics(SM_CXVSCROLL)) / 5) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	return TRUE;
}

BOOL CTCProceduresMonitorArgumentParametersCalibrationPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CString  szX;
	CString  szY;
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK)
		{
			if (GetSelectedCalibrationPoint(szX, szY))
			{
				GetParent()->GetParent()->SetSelectedCalibrationPoint(szX, szY);
				GetParent()->GetParent()->EndDialog(IDOK);
				return TRUE;
			}
		}
	}
	return CLocalePropertyPage::OnNotify(wParam, lParam, pResult);
}

void CTCProceduresMonitorArgumentParametersCalibrationPage::OnSelchangeName()
{
	ShowCalibrationInfo();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorArgumentParametersFolderTabCtrl

IMPLEMENT_DYNCREATE(CTCProceduresMonitorArgumentParametersFolderTabCtrl, CTabCtrl)

CTCProceduresMonitorArgumentParametersFolder *CTCProceduresMonitorArgumentParametersFolderTabCtrl::GetParent() CONST
{
	return((CTCProceduresMonitorArgumentParametersFolder *)CTabCtrl::GetParent());
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorArgumentParametersFolderTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CTCProceduresMonitorArgumentParametersFolderTabCtrl)
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorArgumentParametersFolderTabCtrl message handlers

UINT CTCProceduresMonitorArgumentParametersFolderTabCtrl::OnGetDlgCode()
{
	return CTabCtrl::OnGetDlgCode() | DLGC_WANTTAB;
}

void CTCProceduresMonitorArgumentParametersFolderTabCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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
// CTCProceduresMonitorArgumentParametersFolder

IMPLEMENT_DYNCREATE(CTCProceduresMonitorArgumentParametersFolder, CLocalePropertySheetDialog)

CTCProceduresMonitorArgumentParametersFolder::CTCProceduresMonitorArgumentParametersFolder() : CLocalePropertySheetDialog()
{
	AddPage(&m_pageCalibration);
}

BOOL CTCProceduresMonitorArgumentParametersFolder::Create(CWnd *pParentWnd, CONST RECT &rect)
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

VOID CTCProceduresMonitorArgumentParametersFolder::ShowParameterInfo(CONST CDatabaseTCParameter *pTCParameter)
{
	m_pageCalibration.ShowParameterInfo(pTCParameter);
}

BOOL CTCProceduresMonitorArgumentParametersFolder::GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST
{
	return m_pageCalibration.GetSelectedCalibrationPoint(szX, szY);
}

CTCProceduresMonitorArgumentParametersDialog *CTCProceduresMonitorArgumentParametersFolder::GetParent() CONST
{
	return((CTCProceduresMonitorArgumentParametersDialog *)CLocalePropertySheetDialog::GetParent());
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorArgumentParametersFolder, CLocalePropertySheetDialog)
	//{{AFX_MSG_MAP(CTCProceduresMonitorArgumentParametersFolder)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorArgumentParametersFolder message handlers

void CTCProceduresMonitorArgumentParametersFolder::OnSetFocus(CWnd *pOldWnd)
{
	if (IsWindow(m_wndTabCtrl.GetSafeHwnd()))
	{
		m_wndTabCtrl.SetFocus();
		return;
	}
	CLocalePropertySheetDialog::OnSetFocus(pOldWnd);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorArgumentParametersDialog dialog

IMPLEMENT_DYNCREATE(CTCProceduresMonitorArgumentParametersDialog, CDisplayDialog)

CTCProceduresMonitorArgumentParametersDialog::CTCProceduresMonitorArgumentParametersDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCProceduresMonitorArgumentParametersDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCProceduresMonitorArgumentParametersDialog::Create(CWnd *pParentWnd, LPCTSTR pszParameter, CString &szValue)
{
	CString  szX;
	CString  szY;
	INT  nResult;

	for (m_szParameter = pszParameter, szValue.Empty(); (nResult = CDisplayDialog::Create(pParentWnd, CTCProceduresMonitorArgumentParametersDialog::IDD)) == IDOK; )
	{
		szValue = (GetSelectedCalibrationPoint(szX, szY)) ? szY : EMPTYSTRING;
		break;
	}
	return nResult;
}

VOID CTCProceduresMonitorArgumentParametersDialog::SetSelectedCalibrationPoint(LPCTSTR pszX, LPCTSTR pszY)
{
	m_szX = pszX;
	m_szY = pszY;
}

BOOL CTCProceduresMonitorArgumentParametersDialog::GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST
{
	szX = m_szX;
	szY = m_szY;
	return((!szX.IsEmpty() && !szY.IsEmpty()) ? TRUE : FALSE);
}

CTCProceduresMonitorArgumentValuesDialog *CTCProceduresMonitorArgumentParametersDialog::GetParent() CONST
{
	return((CTCProceduresMonitorArgumentValuesDialog *)CDisplayDialog::GetParent());
}

BOOL CTCProceduresMonitorArgumentParametersDialog::EnumParameters()
{
	CString  szParameter;
	CDatabaseTCParameter  *pParameter;

	if ((pParameter = GetDatabase()->GetTCParameters()->GetAt(GetDatabase()->GetTCParameters()->Find(m_szParameter))))
	{
		if (pParameter->GetAttributes() & (TCPARAMETER_CALIBRATION_NUMERICAL | TCPARAMETER_CALIBRATION_STATUS))
		{
			szParameter.Format(STRING(IDS_TCPROCEDURESMONITORARGUMENTPARAMETERSDIALOG_FORMAT), (LPCTSTR)pParameter->GetTag(), (LPCTSTR)pParameter->GetDescription());
			SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_ITEM, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szParameter);
		}
	}
	szParameter.Format(STRING(IDS_TCPROCEDURESMONITORARGUMENTPARAMETERSDIALOG_FORMAT), (LPCTSTR)m_szParameter, EMPTYSTRING);
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_ITEM, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_ITEM, CB_FINDSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter), 0));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_DETAILS)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_ITEM_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_ITEM)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	m_wndFolderCtrl.EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorArgumentParametersDialog::ShowParameterInfo()
{
	CString  szParameter[2];
	CDatabaseTCParameter  *pParameter;

	for (GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_ITEM)->GetWindowText(szParameter[0]), szParameter[1].Format(STRING(IDS_TCPROCEDURESMONITORARGUMENTPARAMETERSDIALOG_FORMAT), EMPTYSTRING, EMPTYSTRING), szParameter[0] = (szParameter[0].Find(szParameter[1]) >= 0) ? szParameter[0].Left(szParameter[0].Find(szParameter[1])) : szParameter[0]; (pParameter = GetDatabase()->GetTCParameters()->GetAt(GetDatabase()->GetTCParameters()->Find(szParameter[0]))); )
	{
		m_wndFolderCtrl.ShowParameterInfo(pParameter);
		return;
	}
	m_wndFolderCtrl.ShowParameterInfo();
}

CRect CTCProceduresMonitorArgumentParametersDialog::CalcFolderSize() CONST
{
	CRect  rFolder;

	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_FOLDER)->GetWindowRect(rFolder);
	ScreenToClient(rFolder);
	return rFolder;
}

void CTCProceduresMonitorArgumentParametersDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProceduresMonitorArgumentParametersDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorArgumentParametersDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCProceduresMonitorArgumentParametersDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_ITEM, OnSelchangeParameter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorArgumentParametersDialog message handlers

BOOL CTCProceduresMonitorArgumentParametersDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	for (CDisplayDialog::OnInitDialog(); m_wndFolderCtrl.Create(this, CalcFolderSize()) && SetChildSheet(&m_wndFolderCtrl, GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_FOLDER - 1)); )
	{
		if (EnumParameters()) ShowParameterInfo();
		break;
	}
	return TRUE;
}

void CTCProceduresMonitorArgumentParametersDialog::OnSelchangeParameter()
{
	ShowParameterInfo();
}

void CTCProceduresMonitorArgumentParametersDialog::OnOK()
{
	CHourglassCursor  cCursor;

	m_wndFolderCtrl.GetSelectedCalibrationPoint(m_szX, m_szY);
	CDisplayDialog::OnOK();
}

BOOL CTCProceduresMonitorArgumentParametersDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORPARAMETERARGUMENTSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCProceduresMonitorArgumentParametersDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORPARAMETERARGUMENTSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorArgumentValuesDialog dialog

IMPLEMENT_DYNCREATE(CTCProceduresMonitorArgumentValuesDialog, CDisplayDialog)

CTCProceduresMonitorArgumentValuesDialog::CTCProceduresMonitorArgumentValuesDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCProceduresMonitorArgumentValuesDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCProceduresMonitorArgumentValuesDialog::Create(CWnd *pParentWnd, CTCProceduresMonitorItem *pItem)
{
	INT  nResult;

	return(((nResult = (m_cItem[0].Copy(pItem) && m_cItem[1].Copy(pItem)) ? CDisplayDialog::Create(pParentWnd, CTCProceduresMonitorArgumentValuesDialog::IDD) : -1) == IDOK  &&  pItem->Copy(&m_cItem[0])) ? IDOK : nResult);
}

CTCProceduresMonitorSettingsContentsPage *CTCProceduresMonitorArgumentValuesDialog::GetParentDialog() CONST
{
	return((CTCProceduresMonitorSettingsContentsPage *)CDisplayDialog::GetParent());
}

CTCProceduresMonitorWnd *CTCProceduresMonitorArgumentValuesDialog::GetParentDisplay() CONST
{
	return((CTCProceduresMonitorWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CTCProceduresMonitorArgumentValuesDialog::EnumArguments()
{
	INT  nColumn;
	INT  nColumns;
	INT  nArgument;
	INT  nArguments;
	UINT  nOolStatus;
	CString  szItem;
	CDatabaseTCProcedureArgument  *pArgument;
	CDatabaseTCProcedureArguments  pArguments;

	for (nArgument = 0, nArguments = m_cItem[0].GetArguments(pArguments); nArgument < nArguments; nArgument++)
	{
		if ((pArgument = pArguments.GetAt(nArgument)) != (CDatabaseTCProcedureArgument *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_NAME); )
				{
					szItem = pArgument->GetTag();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_DESCRIPTION); )
				{
					szItem = pArgument->GetDescription();
					break;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_TYPE))
				{
					szItem = (pArgument->GetAttributes() & TCPARAMETER_CALIBRATION_NONE) ? STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TYPE_RAW) : EMPTYSTRING;
					szItem = (pArgument->GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL) ? STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TYPE_NUMERICAL) : szItem;
					szItem = (pArgument->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) ? STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TYPE_STATUS) : szItem;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_CODING))
				{
					szItem = (pArgument->GetAttributes() & TCPARAMETER_CODING_BITPATTERN) ? STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_CODING_BITPATTERN) : EMPTYSTRING;
					szItem = (pArgument->GetAttributes() & TCPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_CODING_SIGNEDINTEGER) : szItem;
					szItem = (pArgument->GetAttributes() & TCPARAMETER_CODING_UNSIGNEDINTEGER) ? STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_CODING_UNSIGNEDINTEGER) : szItem;
					szItem = (pArgument->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT) ? STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_CODING_FLOATINGPOINT) : szItem;
					szItem = (pArgument->GetAttributes() & TCPARAMETER_CODING_TIME) ? STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_CODING_DATETIME) : szItem;
					szItem = (pArgument->GetAttributes() & TCPARAMETER_CODING_TEXTSTRING) ? STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_CODING_STRING) : szItem;
					szItem = ((pArgument->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME | TCPARAMETER_CODING_TEXTSTRING)) == 0) ? ((pArgument->GetAttributes() & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_DECIMAL | TCPARAMETER_RADIX_HEXADECIMAL)) ? ((pArgument->GetAttributes() & TCPARAMETER_RADIX_DECIMAL) ? STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_CODING_UNSIGNEDINTEGER) : STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_CODING_BITPATTERN)) : STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_CODING_STRING)) : szItem;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_RADIX))
				{
					szItem = (pArgument->GetAttributes() & TCPARAMETER_RADIX_BINARY) ? STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_RADIX_BINARY) : EMPTYSTRING;
					szItem = (pArgument->GetAttributes() & TCPARAMETER_RADIX_OCTAL) ? STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_RADIX_OCTAL) : szItem;
					szItem = (pArgument->GetAttributes() & TCPARAMETER_RADIX_DECIMAL) ? STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_RADIX_DECIMAL) : szItem;
					szItem = (pArgument->GetAttributes() & TCPARAMETER_RADIX_HEXADECIMAL) ? STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_RADIX_HEXADECIMAL) : szItem;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_MINIMUMVALUE); )
				{
					szItem = pArgument->GetMinValueAsText();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_MAXIMUMVALUE); )
				{
					szItem = pArgument->GetMaxValueAsText();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_VALUE); )
				{
					szItem = pArgument->GetConstValueAsText();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_LIMITCHECK); )
				{
					if (GetTCService()->CheckTCProcedureArgumentOolStatus(pArgument, nOolStatus))
					{
						if (nOolStatus == TCPARAMETER_STATUS_NOLIMIT)
						{
							szItem = STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_LIMITCHECK_NOLIMIT);
							break;
						}
						if (nOolStatus == TCPARAMETER_STATUS_SOFTLIMIT)
						{
							szItem = STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_LIMITCHECK_SOFTLIMIT);
							break;
						}
						if (nOolStatus == TCPARAMETER_STATUS_HARDLIMIT)
						{
							szItem = STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_LIMITCHECK_HARDLIMIT);
							break;
						}
						if (nOolStatus == TCPARAMETER_STATUS_DELTALIMIT)
						{
							szItem = STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_LIMITCHECK_DELTALIMIT);
							break;
						}
						if (nOolStatus == TCPARAMETER_STATUS_VALUELIMIT)
						{
							szItem = STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_LIMITCHECK_VALUELIMIT);
							break;
						}
						if (nOolStatus == TCPARAMETER_STATUS_TIMELIMIT)
						{
							szItem = STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_LIMITCHECK_TIMELIMIT);
							break;
						}
						szItem = (!pArgument->GetConstValueAsText().IsEmpty()) ? STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_LIMITCHECK_NONE) : EMPTYSTRING;
						break;
					}
					szItem = STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_LIMITCHECK_FAILURE);
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST), nArgument, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST), nArgument, nColumn, szItem);
			}
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST), 0);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST, LVM_GETITEMCOUNT) == nArguments) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorArgumentValuesDialog::ShowArgumentValues()
{
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE, CB_RESETCONTENT);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_REMARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_REMARK)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE_SET)->EnableWindow(FALSE);
}
VOID CTCProceduresMonitorArgumentValuesDialog::ShowArgumentValues(CONST CDatabaseTCProcedureArgument *pArgument)
{
	INT  nPoint;
	INT  nPoints;
	double  fX[2];
	CString  szY;
	CString  szValue;
	CDatabaseTCTxtCalTable  *pTCTxtCalTable;
	CDatabaseTCTxtCalPoint  *pTCTxtCalPoint;

	for (SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE, CB_RESETCONTENT); pArgument->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS; )
	{
		if ((pTCTxtCalTable = GetDatabase()->GetTCTxtCalTables()->GetAt(GetDatabase()->GetTCTxtCalTables()->Find(pArgument->GetCalTable()))))
		{
			for (nPoint = 0, nPoints = (INT)pTCTxtCalTable->GetSize(); nPoint < nPoints; nPoint++)
			{
				if ((pTCTxtCalPoint = pTCTxtCalTable->GetAt(nPoint)))
				{
					if (pTCTxtCalPoint->GetPoint(fX[0], szY))
					{
						szValue.Format(STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_POINTVALUE_FORMAT), (LPCTSTR)szY, (LONGLONG)fX[0]);
						SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szValue);
						continue;
					}
					if (pTCTxtCalPoint->GetRange(fX[0], fX[1], szY))
					{
						szValue.Format(STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_RANGEVALUE_FORMAT), (LPCTSTR)szY, (LONGLONG)fX[0], (LONGLONG)fX[1]);
						SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szValue);
						continue;
					}
				}
			}
		}
		break;
	}
	if (pArgument->GetAttributes() & (TCPARAMETER_CALIBRATION_NUMERICAL | TCPARAMETER_CALIBRATION_STATUS))
	{
		GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_REMARK)->EnableWindow(TRUE);
		GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_REMARK)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_REMARK)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_REMARK)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE)->SetWindowText(pArgument->GetConstValueAsText());
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE_SET)->EnableWindow(FALSE);
}

INT CTCProceduresMonitorArgumentValuesDialog::FindColumnIndex(LPCTSTR pszColumn) CONST
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == pszColumn) break;
		continue;
	}
	return((nColumn < nColumns) ? nColumn : -1);
}

VOID CTCProceduresMonitorArgumentValuesDialog::AdjustToPrivileges()
{
	AccessControl(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE, CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE));
}

BOOL CTCProceduresMonitorArgumentValuesDialog::Check(BOOL bModified) CONST
{
	INT  nArgument;
	INT  nArguments;
	CDatabaseTCProcedureArgument  *pArgument;
	CDatabaseTCProcedureArguments  pArguments;

	for (nArgument = 0, nArguments = m_cItem[0].GetArguments(pArguments); nArgument < nArguments; nArgument++)
	{
		if ((pArgument = pArguments.GetAt(nArgument)) && pArgument->GetConstValueAsText().IsEmpty())
		{
			if (pArgument->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME | TCPARAMETER_CODING_TEXTSTRING)) break;
			continue;
		}
	}
	return((nArgument == nArguments) ? TRUE : FALSE);
}

void CTCProceduresMonitorArgumentValuesDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProceduresMonitorArgumentValuesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCProceduresMonitorArgumentValuesDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorArgumentValuesDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCProceduresMonitorArgumentValuesDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE_SET, OnSetValue)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE, OnEditchangeValue)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE, OnSelchangeValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorArgumentValuesDialog message handlers

BOOL CTCProceduresMonitorArgumentValuesDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_DESCRIPTION));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_TYPE));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_CODING));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_RADIX));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_MINIMUMVALUE));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_MAXIMUMVALUE));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_VALUE));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_LIMITCHECK));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_NAME) ? (rColumns.Width() / 5) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_DESCRIPTION) ? ((2 * rColumns.Width()) / 5) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_TYPE) ? (rColumns.Width() / 7) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_CODING)) ? (rColumns.Width() / 4) : (((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_RADIX) || m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_LIMITCHECK)) ? (rColumns.Width() / 5) : ((9 * rColumns.Width()) / 35))))))))));
		continue;
	}
	EnumArguments();
	AdjustToPrivileges();
	return TRUE;
}

BOOL CTCProceduresMonitorArgumentValuesDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CString  szValue;
	CDatabaseTCProcedureArgument  *pArgument;
	CDatabaseTCProcedureArguments  pArguments;
	CTCProceduresMonitorArgumentParametersDialog  cArgumentsDialog;
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		for (; pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED); )
		{
			if (pNotifyListView->iItem < m_cItem[0].GetArguments(pArguments))
			{
				if ((pArgument = pArguments.GetAt(pNotifyListView->iItem)))
				{
					ShowArgumentValues(pArgument);
					break;
				}
			}
			ShowArgumentValues();
			break;
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK)
		{
			if ((pArgument = (pNotifyListView->iItem < m_cItem[0].GetArguments(pArguments)) ? pArguments.GetAt(pNotifyListView->iItem) : (CDatabaseTCProcedureArgument *)NULL) && (pArgument->GetAttributes() & (TCPARAMETER_CALIBRATION_NUMERICAL | TCPARAMETER_CALIBRATION_STATUS)))
			{
				if (cArgumentsDialog.Create(this, pArgument->GetTag(), szValue) == IDOK  &&  !szValue.IsEmpty() && (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)))
				{
					GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE_SET)->EnableWindow((szValue != Listview_GetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_VALUE)))) ? (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)) : FALSE);
					GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE)->SetWindowText(szValue);
					SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE, EM_SETSEL, 0, -1);
					GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE)->SetFocus();
				}
			}
		}
	}
	return CDisplayDialog::OnNotify(wParam, lParam, pResult);
}

void CTCProceduresMonitorArgumentValuesDialog::OnSetValue()
{
	double  fX[2];
	UINT  nOolStatus;
	CString  szValue;
	CDatabaseTCTxtCalTable  *pTCTxtCalTable;
	CDatabaseTCTxtCalPoint  *pTCTxtCalPoint;
	CDatabaseTCProcedureArgument  *pArgument;
	CDatabaseTCProcedureArguments  pArguments;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE)->GetWindowText(szValue); (pArgument = (m_cItem[0].GetArguments(pArguments) > 0) ? pArguments.GetAt(Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST))) : (CDatabaseTCProcedureArgument *)NULL); )
	{
		for (; (pTCTxtCalTable = (pArgument->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) ? GetDatabase()->GetTCTxtCalTables()->GetAt(GetDatabase()->GetTCTxtCalTables()->Find(pArgument->GetCalTable())) : (CDatabaseTCTxtCalTable *)NULL); )
		{
			if ((pTCTxtCalPoint = pTCTxtCalTable->GetAt((INT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szValue))))
			{
				if (pTCTxtCalPoint->GetPoint(fX[0], szValue)) break;
				if (pTCTxtCalPoint->GetRange(fX[0], fX[1], szValue)) break;
			}
			break;
		}
		pArgument->SetConstValueAsText(szValue);
		Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_VALUE)), szValue);
		Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_LIMITCHECK)), (GetTCService()->CheckTCProcedureArgumentOolStatus(pArgument, nOolStatus)) ? ((nOolStatus == TCPARAMETER_STATUS_NOLIMIT) ? STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_LIMITCHECK_NOLIMIT) : ((nOolStatus == TCPARAMETER_STATUS_SOFTLIMIT) ? STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_LIMITCHECK_SOFTLIMIT) : ((nOolStatus == TCPARAMETER_STATUS_HARDLIMIT) ? STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_LIMITCHECK_HARDLIMIT) : ((nOolStatus == TCPARAMETER_STATUS_DELTALIMIT) ? STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_LIMITCHECK_DELTALIMIT) : ((nOolStatus == TCPARAMETER_STATUS_VALUELIMIT) ? STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_LIMITCHECK_VALUELIMIT) : ((nOolStatus == TCPARAMETER_STATUS_TIMELIMIT) ? STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_LIMITCHECK_TIMELIMIT) : ((!szValue.IsEmpty()) ? STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_LIMITCHECK_NONE) : EMPTYSTRING))))))) : STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_LIMITCHECK_FAILURE));
		m_cItem[0].SetArguments(pArguments);
		break;
	}
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE_SET)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorArgumentValuesDialog::OnEditchangeValue()
{
	INT  nPoint;
	INT  nPoints;
	double  fX[2];
	CString  szValue[2];
	CDatabaseTCTxtCalTable  *pTCTxtCalTable;
	CDatabaseTCTxtCalPoint  *pTCTxtCalPoint;
	CDatabaseTCProcedureArgument  *pArgument;
	CDatabaseTCProcedureArguments  pArguments;

	for (GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE)->GetWindowText(szValue[0]); (pArgument = (m_cItem[0].GetArguments(pArguments) > 0) ? pArguments.GetAt(Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST))) : (CDatabaseTCProcedureArgument *)NULL); )
	{
		if ((pTCTxtCalTable = (pArgument->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) ? GetDatabase()->GetTCTxtCalTables()->GetAt(GetDatabase()->GetTCTxtCalTables()->Find(pArgument->GetCalTable())) : (CDatabaseTCTxtCalTable *)NULL))
		{
			for (nPoint = 0, nPoints = (INT)pTCTxtCalTable->GetSize(); nPoint < nPoints; nPoint++)
			{
				if ((pTCTxtCalPoint = pTCTxtCalTable->GetAt(nPoint)))
				{
					if (pTCTxtCalPoint->GetPoint(fX[0], szValue[1]) && szValue[0] == szValue[1]) break;
					if (pTCTxtCalPoint->GetRange(fX[0], fX[1], szValue[1]) && szValue[0] == szValue[1]) break;
				}
			}
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE_SET)->EnableWindow((nPoint < nPoints) ? (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)) : FALSE);
			return;
		}
		GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE_SET)->EnableWindow((GetDatabase()->CheckTCParameterConstValue(pArgument->GetAttributes(), szValue[0]) && ((pArgument->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME | TCPARAMETER_CODING_TEXTSTRING)) == 0 || !szValue[0].IsEmpty())) ? (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)) : FALSE);
		return;
	}
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE_SET)->EnableWindow(FALSE);
}

void CTCProceduresMonitorArgumentValuesDialog::OnSelchangeValue()
{
	double  fX[2];
	CString  szValue;
	CDatabaseTCTxtCalTable  *pTCTxtCalTable;
	CDatabaseTCTxtCalPoint  *pTCTxtCalPoint;
	CDatabaseTCProcedureArgument  *pArgument;
	CDatabaseTCProcedureArguments  pArguments;

	for (szValue = Combobox_GetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE), (INT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE, CB_GETCURSEL)); (pArgument = (m_cItem[0].GetArguments(pArguments) > 0) ? pArguments.GetAt(Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST))) : (CDatabaseTCProcedureArgument *)NULL); )
	{
		for (; (pTCTxtCalTable = (pArgument->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) ? GetDatabase()->GetTCTxtCalTables()->GetAt(GetDatabase()->GetTCTxtCalTables()->Find(pArgument->GetCalTable())) : (CDatabaseTCTxtCalTable *)NULL); )
		{
			if ((pTCTxtCalPoint = pTCTxtCalTable->GetAt((INT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE, CB_GETCURSEL))))
			{
				if (pTCTxtCalPoint->GetPoint(fX[0], szValue)) break;
				if (pTCTxtCalPoint->GetRange(fX[0], fX[1], szValue)) break;
			}
			break;
		}
		GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE_SET)->EnableWindow((szValue != Listview_GetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TITLEITEM_VALUE)))) ? (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)) : FALSE);
		return;
	}
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE_SET)->EnableWindow(FALSE);
}

void CTCProceduresMonitorArgumentValuesDialog::OnOK()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnOK();
}

BOOL CTCProceduresMonitorArgumentValuesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCProceduresMonitorArgumentValuesDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORARGUMENTVALUESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorExecutionOptionsDialog dialog

IMPLEMENT_DYNCREATE(CTCProceduresMonitorExecutionOptionsDialog, CDisplayDialog)

CTCProceduresMonitorExecutionOptionsDialog::CTCProceduresMonitorExecutionOptionsDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCProceduresMonitorExecutionOptionsDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCProceduresMonitorExecutionOptionsDialog::Create(CWnd *pParentWnd, CTCProceduresMonitorItem *pItem)
{
	INT  nResult;

	return(((nResult = (m_cItem[0].Copy(pItem) && m_cItem[1].Copy(pItem)) ? CDisplayDialog::Create(pParentWnd, CTCProceduresMonitorExecutionOptionsDialog::IDD) : -1) == IDOK  &&  pItem->Copy(&m_cItem[0])) ? IDOK : nResult);
}

CTCProceduresMonitorSettingsContentsPage *CTCProceduresMonitorExecutionOptionsDialog::GetParentDialog() CONST
{
	return((CTCProceduresMonitorSettingsContentsPage *)CDisplayDialog::GetParent());
}

CTCProceduresMonitorWnd *CTCProceduresMonitorExecutionOptionsDialog::GetParentDisplay() CONST
{
	return((CTCProceduresMonitorWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CTCProceduresMonitorExecutionOptionsDialog::EnumTriggerEvents()
{
	INT  nEvent;
	INT  nEvents;
	CTelemetryEvents  pEvents;
	CTelemetryEventInfo  *pEventInfo;

	for (nEvent = 0, nEvents = (GetTelemetryEvents(pEvents)) ? (INT)pEvents.GetSize() : 0; nEvent < nEvents; nEvent++)
	{
		if ((pEventInfo = pEvents.GetAt(nEvent))) SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pEventInfo->GetName());
		continue;
	}
	return((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT_NAME, CB_GETCOUNT) >= 0) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorExecutionOptionsDialog::ShowExecutionDetails()
{
	UINT  nCount;
	CTimeKey  tStopTime;
	CTimeKey  tStartTime;
	CTimeSpan  tInterval;

	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_DISABLED, !m_cItem[0].IsEnabled());
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_MANUAL, m_cItem[0].IsManualExecutionAllowed());
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_IMMEDIATELY, (m_cItem[0].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_IMMEDIATELY) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATSTARTUP, (m_cItem[0].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATSTARTUP) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATDAILYTIME, (m_cItem[0].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATDAILYTIME) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATTIME, (m_cItem[0].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATTIME) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL, (m_cItem[0].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATINTERVAL) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT, (m_cItem[0].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATINTERVAL  &&  m_cItem[0].GetTriggerInterval(tStartTime, tInterval, nCount)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPTIME, (m_cItem[0].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATINTERVAL  &&  m_cItem[0].GetTriggerInterval(tStartTime, tInterval, tStopTime)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT, (m_cItem[0].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATEVENT) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_AUTOMATIC, (m_cItem[0].GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_AUTOMATIC) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_SINGLESTEP, (m_cItem[0].GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_SINGLESTEP) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_EXTERNALACTIONS, (m_cItem[0].GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_EXTERNALACTIONS) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_COMMANDS, (m_cItem[0].GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_COMMANDS) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_BREAKS, (m_cItem[0].AreExecutionBreaksAllowed()) ? TRUE : FALSE);
	Timespinbox_SetTime(GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATDAILYTIME_TIME), (m_cItem[0].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATDAILYTIME) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + m_cItem[0].GetDailyTriggerTime().GetTotalSeconds()) : CTime::GetCurrentTime().GetTime());
	Timespinbox_SetTime(GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATTIME_TIME), (m_cItem[0].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATTIME) ? m_cItem[0].GetTriggerTime() : CTime::GetCurrentTime().GetTime());
	Timespinbox_SetTime(GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STARTTIME), (m_cItem[0].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATINTERVAL && (m_cItem[0].GetTriggerInterval(tStartTime, tInterval) || m_cItem[0].GetTriggerInterval(tStartTime, tInterval, tStopTime) || m_cItem[0].GetTriggerInterval(tStartTime, tInterval, nCount))) ? tStartTime : CTime::GetCurrentTime().GetTime());
	Timespinbox_SetTime(GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPTIME_TIME), (m_cItem[0].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATINTERVAL  &&  m_cItem[0].GetTriggerInterval(tStartTime, tInterval, tStopTime)) ? tStopTime : CTime::GetCurrentTime().GetTime());
	Spinbox_SetPos(GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_INTERVAL), (m_cItem[0].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATINTERVAL && (m_cItem[0].GetTriggerInterval(tStartTime, tInterval) || m_cItem[0].GetTriggerInterval(tStartTime, tInterval, tStopTime) || m_cItem[0].GetTriggerInterval(tStartTime, tInterval, nCount))) ? tInterval.GetTotalSeconds() : 0);
	Spinbox_SetPos(GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT_NUMBER), (m_cItem[0].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATINTERVAL  &&  m_cItem[0].GetTriggerInterval(tStartTime, tInterval, nCount)) ? nCount : 0);
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT_NAME, CB_SETCURSEL, (WPARAM)((m_cItem[0].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATEVENT) ? SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)m_cItem[0].GetTriggerEvent()) : -1));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATDAILYTIME_TIME)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATDAILYTIME));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATTIME_TIME)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATTIME));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STARTTIME)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STARTTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_INTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_INTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT_NUMBER_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPTIME_TIME)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPTIME));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT_NAME)->EnableWindow((IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT) && SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorExecutionOptionsDialog::AdjustToPrivileges()
{
	BOOL  bCheck;

	AccessControl(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_IMMEDIATELY, (bCheck = CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)));
	AccessControl(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATSTARTUP, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATDAILYTIME, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATDAILYTIME_TIME, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATTIME, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATTIME_TIME, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STARTTIME, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_INTERVAL, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT_NUMBER, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPTIME, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPTIME_TIME, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT_NAME, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_DISABLED, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_MANUAL, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_AUTOMATIC, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_SINGLESTEP, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_EXTERNALACTIONS, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_COMMANDS, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_BREAKS, bCheck);
}

BOOL CTCProceduresMonitorExecutionOptionsDialog::IsModified() CONST
{
	return !m_cItem[0].Compare(&m_cItem[1]);
}

BOOL CTCProceduresMonitorExecutionOptionsDialog::Check(BOOL bModified) CONST
{
	return((!IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT) || GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT_NAME)->SendMessage(CB_GETCURSEL) >= 0) ? (!bModified || IsModified()) : FALSE);
}

void CTCProceduresMonitorExecutionOptionsDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProceduresMonitorExecutionOptionsDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorExecutionOptionsDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCProceduresMonitorExecutionOptionsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_IMMEDIATELY, OnTriggerImmediately)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATSTARTUP, OnTriggerAlwaysAfterStartup)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATDAILYTIME, OnTriggerAtDailyTime)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATTIME, OnTriggerAtTime)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL, OnTriggerAtInterval)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT, OnTriggerStopAtCount)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPTIME, OnTriggerStopAtTime)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT, OnTriggerAtEvent)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_DISABLED, OnTriggerDisabled)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_MANUAL, OnAllowManualExecution)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_AUTOMATIC, OnModeAutomatic)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_SINGLESTEP, OnModeSingleStep)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_EXTERNALACTIONS, OnModeExternalActions)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_COMMANDS, OnModeCommands)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_BREAKS, OnModeExecutionBreaks)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT_NAME, OnSelchangeTriggerEvent)
	ON_CONTROL(TSBXN_CHANGE, IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATDAILYTIME_TIME, OnSpinchangeTriggerDailyTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATTIME_TIME, OnSpinchangeTriggerTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STARTTIME, OnSpinchangeTriggerIntervalStartTime)
	ON_CONTROL(SBXN_CHANGE, IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_INTERVAL, OnSpinchangeTriggerInterval)
	ON_CONTROL(SBXN_CHANGE, IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT_NUMBER, OnSpinchangeTriggerIntervalStopCount)
	ON_CONTROL(TSBXN_CHANGE, IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPTIME_TIME, OnSpinchangeTriggerIntervalStopTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorExecutionOptionsDialog message handlers

BOOL CTCProceduresMonitorExecutionOptionsDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	Spinbox_SetRange(GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_INTERVAL), TCPROCEDURESMONITOREXECUTIONOPTIONSDIALOG_MINIMUMTRIGGERINTERVAL, TCPROCEDURESMONITOREXECUTIONOPTIONSDIALOG_MAXIMUMTRIGGERINTERVAL);
	Spinbox_SetRange(GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT_NUMBER), TCPROCEDURESMONITOREXECUTIONOPTIONSDIALOG_MINIMUMTRIGGERCOUNT, TCPROCEDURESMONITOREXECUTIONOPTIONSDIALOG_MAXIMUMTRIGGERCOUNT);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_IMMEDIATELY)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATSTARTUP)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATDAILYTIME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATTIME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_DISABLED)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_MANUAL)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_AUTOMATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_SINGLESTEP)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_EXTERNALACTIONS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_COMMANDS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_BREAKS)->EnableWindow();
	EnumTriggerEvents();
	ShowExecutionDetails();
	AdjustToPrivileges();
	return TRUE;
}

void CTCProceduresMonitorExecutionOptionsDialog::OnTriggerImmediately()
{
	CHourglassCursor  cCursor;

	for (CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_IMMEDIATELY, !IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_IMMEDIATELY)); (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_IMMEDIATELY) && m_cItem[0].GetTriggerType() != TCPROCEDURESMONITORITEM_TRIGGERTYPE_IMMEDIATELY) || (!IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_IMMEDIATELY) && m_cItem[0].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_IMMEDIATELY); )
	{
		m_cItem[0].SetTriggerType((IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_IMMEDIATELY)) ? TCPROCEDURESMONITORITEM_TRIGGERTYPE_IMMEDIATELY : TCPROCEDURESMONITORITEM_TRIGGERTYPE_NONE);
		m_cItem[0].SetExecutionStartTime(0);
		m_cItem[0].SetExecutionEndTime(0);
		ShowExecutionDetails();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorExecutionOptionsDialog::OnTriggerAlwaysAfterStartup()
{
	CHourglassCursor  cCursor;

	for (CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATSTARTUP, !IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATSTARTUP)); (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATSTARTUP) && m_cItem[0].GetTriggerType() != TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATSTARTUP) || (!IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATSTARTUP) && m_cItem[0].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATSTARTUP); )
	{
		m_cItem[0].SetTriggerType((IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATSTARTUP)) ? TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATSTARTUP : TCPROCEDURESMONITORITEM_TRIGGERTYPE_NONE);
		m_cItem[0].SetExecutionStartTime(0);
		m_cItem[0].SetExecutionEndTime(0);
		ShowExecutionDetails();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorExecutionOptionsDialog::OnTriggerAtDailyTime()
{
	CHourglassCursor  cCursor;

	for (CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATDAILYTIME, !IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATDAILYTIME)); (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATDAILYTIME) && m_cItem[0].GetTriggerType() != TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATDAILYTIME) || (!IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATDAILYTIME) && m_cItem[0].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATDAILYTIME); )
	{
		m_cItem[0].SetTriggerType((IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATDAILYTIME)) ? TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATDAILYTIME : TCPROCEDURESMONITORITEM_TRIGGERTYPE_NONE);
		m_cItem[0].SetDailyTriggerTime(SECONDSPERHOUR*((CTime::GetCurrentTime().GetTime() % SECONDSPERDAY) / SECONDSPERHOUR));
		m_cItem[0].SetExecutionStartTime(0);
		m_cItem[0].SetExecutionEndTime(0);
		ShowExecutionDetails();
		break;
	}
	for (; IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATDAILYTIME); )
	{
		GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATDAILYTIME_TIME)->SetFocus();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorExecutionOptionsDialog::OnTriggerAtTime()
{
	CHourglassCursor  cCursor;

	for (CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATTIME, !IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATTIME)); (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATTIME) && m_cItem[0].GetTriggerType() != TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATTIME) || (!IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATTIME) && m_cItem[0].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATTIME); )
	{
		m_cItem[0].SetTriggerType((IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATTIME)) ? TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATTIME : TCPROCEDURESMONITORITEM_TRIGGERTYPE_NONE);
		m_cItem[0].SetTriggerTime(SECONDSPERHOUR*((CTime::GetCurrentTime().GetTime() + 2 * SECONDSPERHOUR - 1) / SECONDSPERHOUR));
		m_cItem[0].SetExecutionStartTime(0);
		m_cItem[0].SetExecutionEndTime(0);
		ShowExecutionDetails();
		break;
	}
	for (; IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATTIME); )
	{
		GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATTIME_TIME)->SetFocus();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorExecutionOptionsDialog::OnTriggerAtInterval()
{
	CHourglassCursor  cCursor;

	for (CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL, !IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL)); (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL) && m_cItem[0].GetTriggerType() != TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATINTERVAL) || (!IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL) && m_cItem[0].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATINTERVAL); )
	{
		m_cItem[0].SetTriggerType((IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL)) ? TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATINTERVAL : TCPROCEDURESMONITORITEM_TRIGGERTYPE_NONE);
		m_cItem[0].SetTriggerInterval(SECONDSPERHOUR*((CTime::GetCurrentTime().GetTime() + 2 * SECONDSPERHOUR - 1) / SECONDSPERHOUR), TCPROCEDURESMONITOREXECUTIONOPTIONSDIALOG_DEFAULTTRIGGERINTERVAL);
		m_cItem[0].SetExecutionStartTime(0);
		m_cItem[0].SetExecutionEndTime(0);
		ShowExecutionDetails();
		break;
	}
	for (; IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL); )
	{
		GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STARTTIME)->SetFocus();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorExecutionOptionsDialog::OnTriggerStopAtCount()
{
	UINT  nCount;
	CTimeKey  tStartTime;
	CTimeSpan  tInterval;
	CHourglassCursor  cCursor;

	for (CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT, !IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT)); (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT) && !m_cItem[0].GetTriggerInterval(tStartTime, tInterval, nCount)) || (!IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT) && m_cItem[0].GetTriggerInterval(tStartTime, tInterval, nCount)); )
	{
		m_cItem[0].SetTriggerInterval(tStartTime, tInterval, (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT)) ? TCPROCEDURESMONITOREXECUTIONOPTIONSDIALOG_DEFAULTTRIGGERCOUNT : 0);
		m_cItem[0].SetExecutionStartTime(0);
		m_cItem[0].SetExecutionEndTime(0);
		ShowExecutionDetails();
		break;
	}
	for (; IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT); )
	{
		GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT_NUMBER)->SetFocus();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorExecutionOptionsDialog::OnTriggerStopAtTime()
{
	CTimeKey  tStopTime;
	CTimeKey  tStartTime;
	CTimeSpan  tInterval;
	CHourglassCursor  cCursor;

	for (CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPTIME, !IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPTIME)); (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPTIME) && !m_cItem[0].GetTriggerInterval(tStartTime, tInterval, tStopTime)) || (!IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPTIME) && m_cItem[0].GetTriggerInterval(tStartTime, tInterval, tStopTime)); )
	{
		m_cItem[0].SetTriggerInterval(tStartTime, tInterval, (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPTIME)) ? CTimeKey(tStartTime.GetTime() + TCPROCEDURESMONITOREXECUTIONOPTIONSDIALOG_DEFAULTTRIGGERCOUNT*tInterval.GetTotalSeconds()) : CTimeKey(0));
		m_cItem[0].SetExecutionStartTime(0);
		m_cItem[0].SetExecutionEndTime(0);
		ShowExecutionDetails();
		break;
	}
	for (; IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPTIME); )
	{
		GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPTIME_TIME)->SetFocus();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorExecutionOptionsDialog::OnTriggerAtEvent()
{
	CHourglassCursor  cCursor;

	for (CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT, !IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT)); (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT) && m_cItem[0].GetTriggerType() != TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATEVENT) || (!IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT) && m_cItem[0].GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATEVENT); )
	{
		m_cItem[0].SetTriggerType((IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT)) ? TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATEVENT : TCPROCEDURESMONITORITEM_TRIGGERTYPE_NONE);
		m_cItem[0].SetTriggerEvent(EMPTYSTRING);
		m_cItem[0].SetExecutionStartTime(0);
		m_cItem[0].SetExecutionEndTime(0);
		ShowExecutionDetails();
		break;
	}
	for (; IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT); )
	{
		GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT_NAME)->SetFocus();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorExecutionOptionsDialog::OnTriggerDisabled()
{
	CHourglassCursor  cCursor;

	m_cItem[0].Enable(!IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_DISABLED));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorExecutionOptionsDialog::OnAllowManualExecution()
{
	CHourglassCursor  cCursor;

	m_cItem[0].AllowManualExecution(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_MANUAL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorExecutionOptionsDialog::OnModeAutomatic()
{
	CHourglassCursor  cCursor;

	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_AUTOMATIC, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_SINGLESTEP, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_EXTERNALACTIONS, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_COMMANDS, FALSE);
	m_cItem[0].SetExecutionMode(TCPROCEDURESMONITORITEM_EXECUTIONMODE_AUTOMATIC);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorExecutionOptionsDialog::OnModeSingleStep()
{
	CHourglassCursor  cCursor;

	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_SINGLESTEP, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_AUTOMATIC, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_EXTERNALACTIONS, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_COMMANDS, FALSE);
	m_cItem[0].SetExecutionMode(TCPROCEDURESMONITORITEM_EXECUTIONMODE_SINGLESTEP);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorExecutionOptionsDialog::OnModeExternalActions()
{
	CHourglassCursor  cCursor;

	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_EXTERNALACTIONS, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_AUTOMATIC, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_SINGLESTEP, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_COMMANDS, FALSE);
	m_cItem[0].SetExecutionMode(TCPROCEDURESMONITORITEM_EXECUTIONMODE_EXTERNALACTIONS);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorExecutionOptionsDialog::OnModeCommands()
{
	CHourglassCursor  cCursor;

	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_COMMANDS, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_AUTOMATIC, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_SINGLESTEP, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_EXTERNALACTIONS, FALSE);
	m_cItem[0].SetExecutionMode(TCPROCEDURESMONITORITEM_EXECUTIONMODE_COMMANDS);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorExecutionOptionsDialog::OnModeExecutionBreaks()
{
	CHourglassCursor  cCursor;

	m_cItem[0].AllowExecutionBreaks(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_BREAKS));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorExecutionOptionsDialog::OnSelchangeTriggerEvent()
{
	CString  szEvent;

	GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT_NAME)->GetWindowText(szEvent);
	m_cItem[0].SetTriggerEvent(szEvent);
	m_cItem[0].SetExecutionStartTime(0);
	m_cItem[0].SetExecutionEndTime(0);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorExecutionOptionsDialog::OnSpinchangeTriggerDailyTime()
{
	m_cItem[0].SetDailyTriggerTime(Timespinbox_GetTime(GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATDAILYTIME_TIME)).GetTime() % SECONDSPERDAY);
	m_cItem[0].SetExecutionStartTime(0);
	m_cItem[0].SetExecutionEndTime(0);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorExecutionOptionsDialog::OnSpinchangeTriggerTime()
{
	m_cItem[0].SetTriggerTime(Timespinbox_GetTime(GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATTIME_TIME)));
	m_cItem[0].SetExecutionStartTime(0);
	m_cItem[0].SetExecutionEndTime(0);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorExecutionOptionsDialog::OnSpinchangeTriggerIntervalStartTime()
{
	UINT  nCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tStartTime;
	CTimeSpan  tInterval;

	for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STARTTIME)); m_cItem[0].GetTriggerInterval(tStartTime, tInterval); )
	{
		m_cItem[0].SetTriggerInterval(tTime, tInterval);
		m_cItem[0].SetExecutionStartTime(0);
		m_cItem[0].SetExecutionEndTime(0);
		break;
	}
	if (m_cItem[0].GetTriggerInterval(tStartTime, tInterval, tStopTime))
	{
		Timespinbox_SetTime(GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPTIME_TIME), (tStopTime = max(tTime.GetTime() + tInterval.GetTotalSeconds(), tStopTime.GetTime())));
		m_cItem[0].SetTriggerInterval(tTime, tInterval, tStopTime);
		m_cItem[0].SetExecutionStartTime(0);
		m_cItem[0].SetExecutionEndTime(0);
	}
	if (m_cItem[0].GetTriggerInterval(tStartTime, tInterval, nCount))
	{
		m_cItem[0].SetTriggerInterval(tTime, tInterval, nCount);
		m_cItem[0].SetExecutionStartTime(0);
		m_cItem[0].SetExecutionEndTime(0);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorExecutionOptionsDialog::OnSpinchangeTriggerInterval()
{
	UINT  nCount;
	CTimeKey  tStopTime;
	CTimeKey  tStartTime;
	CTimeSpan  tInterval;

	if (m_cItem[0].GetTriggerInterval(tStartTime, tInterval))
	{
		m_cItem[0].SetTriggerInterval(tStartTime, Spinbox_GetPos(GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_INTERVAL)));
		m_cItem[0].SetExecutionStartTime(0);
		m_cItem[0].SetExecutionEndTime(0);
	}
	if (m_cItem[0].GetTriggerInterval(tStartTime, tInterval, tStopTime))
	{
		Timespinbox_SetTime(GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPTIME), (tStopTime = max(tStartTime.GetTime() + Timespinbox_GetTime(GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_INTERVAL)).GetTime(), tStopTime.GetTime())));
		m_cItem[0].SetTriggerInterval(tStartTime, Spinbox_GetPos(GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_INTERVAL)), tStopTime);
		m_cItem[0].SetExecutionStartTime(0);
		m_cItem[0].SetExecutionEndTime(0);
	}
	if (m_cItem[0].GetTriggerInterval(tStartTime, tInterval, nCount))
	{
		m_cItem[0].SetTriggerInterval(tStartTime, Spinbox_GetPos(GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_INTERVAL)), nCount);
		m_cItem[0].SetExecutionStartTime(0);
		m_cItem[0].SetExecutionEndTime(0);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorExecutionOptionsDialog::OnSpinchangeTriggerIntervalStopCount()
{
	UINT  nCount;
	CTimeKey  tStartTime;
	CTimeSpan  tInterval;

	if (m_cItem[0].GetTriggerInterval(tStartTime, tInterval, nCount))
	{
		m_cItem[0].SetTriggerInterval(tStartTime, tInterval, (UINT)max(Spinbox_GetPos(GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT_NUMBER)), TCPROCEDURESMONITOREXECUTIONOPTIONSDIALOG_MINIMUMTRIGGERCOUNT));
		m_cItem[0].SetExecutionStartTime(0);
		m_cItem[0].SetExecutionEndTime(0);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorExecutionOptionsDialog::OnSpinchangeTriggerIntervalStopTime()
{
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tStartTime;
	CTimeSpan  tInterval;

	if (m_cItem[0].GetTriggerInterval(tStartTime, tInterval, tStopTime))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPTIME_TIME)); tTime < tStartTime + tInterval.GetTotalSeconds(); )
		{
			Timespinbox_SetTime(GetDlgItem(IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPTIME_TIME), (tTime = tStartTime.GetTime() + tInterval.GetTotalSeconds()));
			break;
		}
		m_cItem[0].SetTriggerInterval(tStartTime, tInterval, CTimeKey(tTime));
		m_cItem[0].SetExecutionStartTime(0);
		m_cItem[0].SetExecutionEndTime(0);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorExecutionOptionsDialog::OnOK()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnOK();
}

BOOL CTCProceduresMonitorExecutionOptionsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITOREXECUTIONOPTIONSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCProceduresMonitorExecutionOptionsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITOREXECUTIONOPTIONSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorCommandOptionsDialog dialog

IMPLEMENT_DYNCREATE(CTCProceduresMonitorCommandOptionsDialog, CDisplayDialog)

CTCProceduresMonitorCommandOptionsDialog::CTCProceduresMonitorCommandOptionsDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCProceduresMonitorCommandOptionsDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCProceduresMonitorCommandOptionsDialog::Create(CWnd *pParentWnd, CTCProceduresMonitorItem *pItem)
{
	INT  nResult;

	return(((nResult = (m_cItem[0].Copy(pItem) && m_cItem[1].Copy(pItem)) ? CDisplayDialog::Create(pParentWnd, CTCProceduresMonitorCommandOptionsDialog::IDD) : -1) == IDOK  &&  pItem->Copy(&m_cItem[0])) ? IDOK : nResult);
}

BOOL CTCProceduresMonitorCommandOptionsDialog::Initialize()
{
	return((GetTCService()->GetTCInterlocks(TCINTERLOCK_SOURCETYPE_PROCEDURESMONITOR, m_pInterlocks[0])) ? m_pInterlocks[1].Copy(&m_pInterlocks[0]) : FALSE);
}

BOOL CTCProceduresMonitorCommandOptionsDialog::EnumThreads()
{
	INT  nThread;
	INT  nThreads;
	CDatabaseTCProcedureThread  *pThread;

	for (nThread = 0, nThreads = (INT)m_cItem[0].GetSize(); nThread < nThreads; nThread++)
	{
		if ((pThread = m_cItem[0].GetAt(nThread)) != (CDatabaseTCProcedureThread *)NULL)
		{
			SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_THREAD, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)pThread->GetName());
			continue;
		}
	}
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_THREAD, CB_SETCURSEL);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_THREAD_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_THREAD, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_THREAD)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_THREAD, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_THREAD, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorCommandOptionsDialog::EnumThreadSteps()
{
	INT  nStep;
	INT  nSteps;
	INT  nCount;
	INT  nEntry;
	INT  nEntries;
	INT  nDigits;
	INT  nColumn;
	INT  nColumns;
	CString  szStep[2];
	CPtrArray  pSteps;
	CStringTools  cStringTools;
	CDatabaseTCPacket  cPacket;
	CDatabaseTCFunction  cFunction;
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pStep;
	CDatabaseTCProcedureThread  *pThread;
	CTCProcedureDocumentSendTCFunctionItem  *pSendTCFunctionStep;
	CTCProcedureDocumentSendTCSequenceItem  *pSendTCSequenceStep;

	if ((pThread = m_cItem[0].GetAt((INT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_THREAD, CB_GETCURSEL))))
	{
		if ((pDocument = new CTCProcedureDocument) != (CTCProcedureDocument *)NULL)
		{
			if (pDocument->Unmap(pThread) && pDocument->EnumSteps(pSteps, FALSE, TRUE) >= 0)
			{
				for (nStep = 0, nSteps = (INT)pSteps.GetSize(), nCount = 0; nStep < nSteps; nStep++)
				{
					if ((pStep = (CTCProcedureDocumentItem *)pSteps.GetAt(nStep)))
					{
						if (pStep->GetType() == TCPROCEDURETHREADSTEP_ACTIONOBJECT_SENDTCFUNCTION)
						{
							if ((pSendTCFunctionStep = (CTCProcedureDocumentSendTCFunctionItem *)pStep))
							{
								for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), szStep[0].Empty(), szStep[1].Empty(); nColumn < nColumns; nColumn++)
								{
									for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORCOMMANDOPTIONSDIALOG_TITLEITEM_NAME); )
									{
										szStep[0] = pSendTCFunctionStep->GetName();
										break;
									}
									for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORCOMMANDOPTIONSDIALOG_TITLEITEM_DESCRIPTION) && pSendTCFunctionStep->GetFunction(&cFunction, &cPacket); )
									{
										szStep[1].Format(STRING(IDS_TCPROCEDURESMONITORCOMMANDOPTIONSDIALOG_FUNCTION_FORMAT), (LPCTSTR)cFunction.GetDescription(), (LPCTSTR)cFunction.GetName());
										break;
									}
								}
								if (!szStep[0].IsEmpty() && !szStep[1].IsEmpty())
								{
									if ((nCount >= SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS, LVM_GETITEMCOUNT) && Listview_InsertText(GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS), nCount, szStep[0])) || (nCount < SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS, LVM_GETITEMCOUNT) && Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS), nCount, 0, szStep[0])))
									{
										Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS), nCount, 1, szStep[1]);
										nCount++;
										continue;
									}
								}
							}
						}
						if (pStep->GetType() == TCPROCEDURETHREADSTEP_ACTIONOBJECT_SENDTCSEQUENCE)
						{
							if ((pSendTCSequenceStep = (CTCProcedureDocumentSendTCSequenceItem *)pStep))
							{
								for (nEntry = 0, nEntries = pSendTCSequenceStep->GetSize(), nDigits = max(cStringTools.ConvertIntToString(nEntries).GetLength(), 3); nEntry < nEntries; nEntry++)
								{
									if ((pSendTCFunctionStep = pSendTCSequenceStep->GetAt(nEntry)) && pSendTCFunctionStep->GetFunction(&cFunction, &cPacket))
									{
										for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), szStep[0].Empty(), szStep[1].Empty(); nColumn < nColumns; nColumn++)
										{
											for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORCOMMANDOPTIONSDIALOG_TITLEITEM_NAME); )
											{
												szStep[0] = pSendTCSequenceStep->GetName();
												break;
											}
											for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORCOMMANDOPTIONSDIALOG_TITLEITEM_DESCRIPTION) && pSendTCFunctionStep->GetFunction(&cFunction, &cPacket); )
											{
												szStep[1].Format(STRING(IDS_TCPROCEDURESMONITORCOMMANDOPTIONSDIALOG_SEQUENCE_FORMAT), (LPCTSTR)cStringTools.ConvertIntToPaddedString(nEntry + 1, nDigits), (LPCTSTR)cFunction.GetDescription(), (LPCTSTR)cFunction.GetName());
												break;
											}
										}
										if (!szStep[0].IsEmpty() && !szStep[1].IsEmpty())
										{
											if ((nCount >= SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS, LVM_GETITEMCOUNT) && Listview_InsertText(GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS), nCount, szStep[0])) || (nCount < SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS, LVM_GETITEMCOUNT) && Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS), nCount, 0, szStep[0])))
											{
												Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS), nCount, 1, szStep[1]);
												nCount++;
												continue;
											}
										}
									}
								}
							}
						}
					}
				}
				while (nCount < SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS, LVM_GETITEMCOUNT))
				{
					if (!Listview_DeleteText(GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS), nCount)) break;
					continue;
				}
				delete pDocument;
				Listview_SetCurText(GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS), 0);
				GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
				GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
				return TRUE;
			}
			delete pDocument;
		}
	}
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS)->EnableWindow(FALSE);
	return FALSE;
}

BOOL CTCProceduresMonitorCommandOptionsDialog::EnumInterlocks()
{
	INT  nInterlock;
	INT  nInterlocks;
	CString  szStep;
	CString  szThread;
	CString  szFunction;
	CTCInterlock  *pInterlock;

	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK_NAME, CB_RESETCONTENT);
	for (nInterlock = 0, nInterlocks = (INT)m_pInterlocks[0].GetSize(), FindThreadStep(szThread, szStep, szFunction); nInterlock < nInterlocks; nInterlock++)
	{
		if ((pInterlock = m_pInterlocks[0].GetAt(nInterlock)) && (pInterlock->GetStage() == TCINTERLOCK_STAGE_RECEPTION || pInterlock->GetStage() == TCINTERLOCK_STAGE_TRANSMISSION || CheckTCVerificationStage(szFunction, (pInterlock->GetStage() == TCINTERLOCK_STAGE_ACCEPTANCE) ? TCVERIFICATIONSTAGE_ACCEPTANCE : ((pInterlock->GetStage() == TCINTERLOCK_STAGE_START) ? TCVERIFICATIONSTAGE_START : ((pInterlock->GetStage() == TCINTERLOCK_STAGE_PROGRESS) ? TCVERIFICATIONSTAGE_PROGRESS : TCVERIFICATIONSTAGE_COMPLETION)))))
		{
			SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)pInterlock->GetName());
			continue;
		}
	}
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return TRUE;
}

VOID CTCProceduresMonitorCommandOptionsDialog::ShowThreadStepProperties()
{
	CString  szStep;
	CString  szThread;
	CString  szFunction;
	CString  szInterlock;
	CTimeSpan  tTimeWindow;

	for (GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_DETAILS)->EnableWindow(), m_cItem[0].GetReleaseConstraints(szThread, szStep, szFunction, FindThreadStep(szThread, szStep, szFunction), szInterlock, tTimeWindow); SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS, LVM_GETITEMCOUNT) > 0; )
	{
		SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szInterlock));
		CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK, (SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK_NAME, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_DEFAULT, (tTimeWindow == 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_UNLIMITED, (tTimeWindow == LLONG_MAX) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED, (tTimeWindow != LLONG_MAX  &&  tTimeWindow > 0) ? TRUE : FALSE);
		Spinbox_SetPos(GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED_INTERVAL), tTimeWindow.GetTotalSeconds());
		GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK_NAME)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK));
		GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCKS)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_DEFAULT)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_UNLIMITED)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED_INTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED));
		GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED_INTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED));
		return;
	}
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK_NAME, CB_SETCURSEL, (WPARAM)-1);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_DEFAULT, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_UNLIMITED, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED, FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCKS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_DEFAULT)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_UNLIMITED)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED_INTERVAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED_INTERVAL_STATIC)->EnableWindow(FALSE);
}

INT CTCProceduresMonitorCommandOptionsDialog::FindThreadStep(CString &szThread, CString &szStep, CString &szFunction) CONST
{
	return FindThreadStep(Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS)), szThread, szStep, szFunction);
}
INT CTCProceduresMonitorCommandOptionsDialog::FindThreadStep(INT nIndex, CString &szThread, CString &szStep, CString &szFunction) CONST
{
	INT  nPos;
	INT  nEntry;
	CString  szEntry;
	CString  szFormat;
	CString  szDescription;
	CStringTools  cStringTools;

	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_THREAD)->GetWindowText(szThread);
	for (szStep = Listview_GetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS), nIndex, 0), szDescription = Listview_GetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS), nIndex, (INT)(m_szColumns.GetSize() - 1)), szFormat.Format(STRING(IDS_TCPROCEDURESMONITORCOMMANDOPTIONSDIALOG_SEQUENCE_FORMAT), EMPTYSTRING, EMPTYSTRING, EMPTYSTRING), nPos = (INT)(szDescription.GetLength() - 1); nPos >= 0; nPos--)
	{
		if (szDescription.GetAt(nPos) == szFormat.GetAt(szFormat.GetLength() - 1 - 1))
		{
			szFunction = szDescription.Mid(nPos + 1, szDescription.GetLength() - nPos - 1 - 1);
			break;
		}
	}
	for (nEntry = -1; (nPos = szDescription.Find(szFormat.GetAt(0))) >= 0; )
	{
		for (szEntry = cStringTools.ConvertIntToPaddedString(_ttoi(szDescription), nPos); szDescription.Left(szEntry.GetLength()) == szEntry; )
		{
			nEntry = _ttoi(szEntry);
			break;
		}
		break;
	}
	return nEntry;
}

BOOL CTCProceduresMonitorCommandOptionsDialog::CheckTCVerificationStage(LPCTSTR pszFunction, UINT nStage) CONST
{
	INT  nParameter;
	INT  nParameters;
	CDatabaseTCFunction  *pFunction;
	CDatabaseTCExeVerGroup  *pGroup;
	CDatabaseTCExeVerGroupParameter  *pGroupParameter;

	if ((pFunction = GetDatabase()->GetTCFunctions()->GetAt(GetDatabase()->GetTCFunctions()->Find(pszFunction))))
	{
		if ((pGroup = GetDatabase()->GetTCExeVerGroups()->GetAt(pFunction->GetExeVerGroupRef())))
		{
			for (nParameter = 0, nParameters = (INT)pGroup->GetSize(); nParameter < nParameters; nParameter++)
			{
				if ((pGroupParameter = pGroup->GetAt(nParameter)) && pGroupParameter->GetStage() == nStage) break;
				continue;
			}
			return((nParameter < nParameters) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

VOID CTCProceduresMonitorCommandOptionsDialog::AdjustToPrivileges()
{
	BOOL  bCheck;

	AccessControl(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK, (bCheck = CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)));
	AccessControl(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK_NAME, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_DEFAULT, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_UNLIMITED, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED_INTERVAL, bCheck);
}

BOOL CTCProceduresMonitorCommandOptionsDialog::IsModified() CONST
{
	return((!m_cItem[0].Compare(&m_cItem[1]) || !m_pInterlocks[0].Compare(&m_pInterlocks[1])) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorCommandOptionsDialog::Check(BOOL bModified) CONST
{
	return(!bModified || IsModified());
}

void CTCProceduresMonitorCommandOptionsDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProceduresMonitorCommandOptionsDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCProceduresMonitorCommandOptionsDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorCommandOptionsDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCProceduresMonitorCommandOptionsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK, OnInterlock)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCKS, OnInterlocks)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_DEFAULT, OnTimeWindowDefault)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_UNLIMITED, OnTimeWindowUnlimited)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED, OnTimeWindowLimited)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_THREAD, OnSelchangeThread)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK_NAME, OnSelchangeInterlock)
	ON_CONTROL(SBXN_CHANGE, IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED_INTERVAL, OnSpinchangeTimeWindow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorCommandOptionsDialog message handlers

BOOL CTCProceduresMonitorCommandOptionsDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORCOMMANDOPTIONSDIALOG_TITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORCOMMANDOPTIONSDIALOG_TITLEITEM_DESCRIPTION));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT), Spinbox_SetRange(GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED_INTERVAL), TCPROCEDURESMONITORCOMMANDOPTIONSDIALOG_MINIMUMTIMEWINDOWINTERVAL, TCPROCEDURESMONITORCOMMANDOPTIONSDIALOG_MAXIMUMTIMEWINDOWINTERVAL); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORCOMMANDOPTIONSDIALOG_TITLEITEM_NAME)) ? (rColumns.Width() / 4) : ((3 * rColumns.Width()) / 4));
		continue;
	}
	EnumThreads();
	EnumThreadSteps();
	EnumInterlocks();
	ShowThreadStepProperties();
	AdjustToPrivileges();
	return TRUE;
}

BOOL CTCProceduresMonitorCommandOptionsDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED)) ShowThreadStepProperties();
	}
	return CDisplayDialog::OnNotify(wParam, lParam, pResult);
}

void CTCProceduresMonitorCommandOptionsDialog::OnInterlock()
{
	INT  nEntry;
	CString  szStep;
	CString  szThread;
	CString  szFunction;
	CString  szInterlock;
	CTimeSpan  tTimeWindow;

	for (nEntry = FindThreadStep(szThread, szStep, szFunction); m_cItem[0].GetReleaseConstraints(szThread, szStep, szFunction, nEntry, szInterlock, tTimeWindow) >= 0; )
	{
		m_cItem[0].SetReleaseConstraints(szThread, szStep, szFunction, nEntry, EMPTYSTRING, tTimeWindow);
		break;
	}
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK_NAME, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK_NAME)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandOptionsDialog::OnInterlocks()
{
	INT  nEntry;
	CString  szStep;
	CString  szThread;
	CString  szFunction;
	CString  szInterlock;
	CTimeSpan  tTimeWindow;
	CTCProceduresMonitorCommandInterlocksDialog  cInterlocksDialog;

	if (cInterlocksDialog.Create(this, m_pInterlocks[0]) == IDOK)
	{
		for (EnumInterlocks(), m_cItem[0].GetReleaseConstraints(szThread, szStep, szFunction, (nEntry = FindThreadStep(szThread, szStep, szFunction)), szInterlock, tTimeWindow); SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szInterlock) < 0; )
		{
			m_cItem[0].SetReleaseConstraints(szThread, szStep, szFunction, nEntry, (szInterlock = EMPTYSTRING), tTimeWindow);
			break;
		}
		ShowThreadStepProperties();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandOptionsDialog::OnTimeWindowDefault()
{
	INT  nEntry;
	CString  szStep;
	CString  szThread;
	CString  szFunction;
	CString  szInterlock;
	CTimeSpan  tTimeWindow;

	for (nEntry = FindThreadStep(szThread, szStep, szFunction); m_cItem[0].GetReleaseConstraints(szThread, szStep, szFunction, nEntry, szInterlock, tTimeWindow) >= 0; )
	{
		m_cItem[0].SetReleaseConstraints(szThread, szStep, szFunction, nEntry, szInterlock, 0);
		break;
	}
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_DEFAULT, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_UNLIMITED, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED, FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED_INTERVAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED_INTERVAL_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandOptionsDialog::OnTimeWindowUnlimited()
{
	INT  nEntry;
	CString  szStep;
	CString  szThread;
	CString  szFunction;
	CString  szInterlock;
	CTimeSpan  tTimeWindow;

	for (nEntry = FindThreadStep(szThread, szStep, szFunction); m_cItem[0].GetReleaseConstraints(szThread, szStep, szFunction, nEntry, szInterlock, tTimeWindow) >= 0; )
	{
		m_cItem[0].SetReleaseConstraints(szThread, szStep, szFunction, nEntry, szInterlock, LLONG_MAX);
		break;
	}
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_DEFAULT, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_UNLIMITED, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED, FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED_INTERVAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED_INTERVAL_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandOptionsDialog::OnTimeWindowLimited()
{
	INT  nEntry;
	CString  szStep;
	CString  szThread;
	CString  szFunction;
	CString  szInterlock;
	CTimeSpan  tTimeWindow;

	for (nEntry = FindThreadStep(szThread, szStep, szFunction); m_cItem[0].GetReleaseConstraints(szThread, szStep, szFunction, nEntry, szInterlock, tTimeWindow) >= 0; )
	{
		m_cItem[0].SetReleaseConstraints(szThread, szStep, szFunction, nEntry, szInterlock, TCPROCEDURESMONITORCOMMANDOPTIONSDIALOG_DEFAULTTIMEWINDOWINTERVAL);
		break;
	}
	Spinbox_SetPos(GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED_INTERVAL), TCPROCEDURESMONITORCOMMANDOPTIONSDIALOG_DEFAULTTIMEWINDOWINTERVAL);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_DEFAULT, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_UNLIMITED, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED, TRUE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED_INTERVAL)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED_INTERVAL_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED_INTERVAL)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandOptionsDialog::OnSelchangeThread()
{
	EnumThreadSteps();
	ShowThreadStepProperties();
}

void CTCProceduresMonitorCommandOptionsDialog::OnSelchangeInterlock()
{
	INT  nEntry;
	CString  szStep;
	CString  szThread;
	CString  szFunction;

	m_cItem[0].SetReleaseConstraints(szThread, szStep, szFunction, (nEntry = FindThreadStep(szThread, szStep, szFunction)), Combobox_GetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK_NAME), (INT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK_NAME, CB_GETCURSEL)), (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED)) ? Spinbox_GetPos(GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED_INTERVAL)) : 0);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandOptionsDialog::OnSpinchangeTimeWindow()
{
	INT  nEntry;
	CString  szStep;
	CString  szThread;
	CString  szFunction;

	m_cItem[0].SetReleaseConstraints(szThread, szStep, szFunction, (nEntry = FindThreadStep(szThread, szStep, szFunction)), Combobox_GetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK_NAME), (INT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK_NAME, CB_GETCURSEL)), Spinbox_GetPos(GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED_INTERVAL)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandOptionsDialog::OnOK()
{
	CHourglassCursor  cCursor;

	GetTCService()->SetTCInterlocks(TCINTERLOCK_SOURCETYPE_PROCEDURESMONITOR, m_pInterlocks[0]);
	CDisplayDialog::OnOK();
}

BOOL CTCProceduresMonitorCommandOptionsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORCOMMANDOPTIONSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCProceduresMonitorCommandOptionsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORCOMMANDOPTIONSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorCommandInterlocksDialog dialog

IMPLEMENT_DYNCREATE(CTCProceduresMonitorCommandInterlocksDialog, CDisplayDialog)

CTCProceduresMonitorCommandInterlocksDialog::CTCProceduresMonitorCommandInterlocksDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCProceduresMonitorCommandInterlocksDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCProceduresMonitorCommandInterlocksDialog::Create(CWnd *pParentWnd, CTCInterlocks &pInterlocks)
{
	INT  nResult;

	for (m_pInterlocks[0].Copy(&pInterlocks), m_pInterlocks[1].Copy(&pInterlocks); (nResult = CDisplayDialog::Create(pParentWnd, CTCProceduresMonitorCommandInterlocksDialog::IDD)) == IDOK; )
	{
		pInterlocks.Copy(&m_pInterlocks[0]);
		break;
	}
	return nResult;
}

BOOL CTCProceduresMonitorCommandInterlocksDialog::EnumInterlocks()
{
	INT  nInterlock;
	INT  nInterlocks;
	CTCInterlock  *pInterlock;

	for (nInterlock = 0, nInterlocks = (INT)m_pInterlocks[0].GetSize(); nInterlock < nInterlocks; nInterlock++)
	{
		if ((pInterlock = m_pInterlocks[0].GetAt(nInterlock))) SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)pInterlock->GetName());
		continue;
	}
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_REMOVEALL)->EnableWindow(CanRemoveAllInterlocks());
	return TRUE;
}

BOOL CTCProceduresMonitorCommandInterlocksDialog::EnumSubSystems()
{
	INT  nSubSystem;
	INT  nSubSystems;
	CStringArray  szSubSystems;

	for (nSubSystem = 0, nSubSystems = GetTCService()->EnumTCSubSystems(szSubSystems, FALSE); nSubSystem < nSubSystems; nSubSystem++)
	{
		SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szSubSystems.GetAt(nSubSystem));
		continue;
	}
	return TRUE;
}

VOID CTCProceduresMonitorCommandInterlocksDialog::ShowProperties()
{
	UINT  nScope;
	UINT  nStage;
	CTCInterlock  *pInterlock;

	if ((pInterlock = FindInterlock()))
	{
		CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_GLOBAL, ((nScope = TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope())) == TCINTERLOCK_SCOPE_GLOBAL) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_LOCAL, (nScope == TCINTERLOCK_SCOPE_LOCAL || nScope == TCINTERLOCK_SCOPE_LOCALNOWAIT) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM, ((nScope == TCINTERLOCK_SCOPE_LOCALSUBSYSTEM || nScope == TCINTERLOCK_SCOPE_LOCALSUBSYSTEMNOWAIT) && SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_NOWAITSTATE, (nScope == TCINTERLOCK_SCOPE_LOCALNOWAIT || (nScope == TCINTERLOCK_SCOPE_LOCALSUBSYSTEMNOWAIT  &&  SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME, CB_GETCOUNT) > 0)) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_TELECOMMANDS, (nScope == TCINTERLOCK_SCOPE_COMMANDS) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_RECEPTION, ((nStage = pInterlock->GetStage()) == TCINTERLOCK_STAGE_RECEPTION) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_TRANSMISSION, (nStage == TCINTERLOCK_STAGE_TRANSMISSION) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_ACCEPTANCE, (nStage == TCINTERLOCK_STAGE_ACCEPTANCE) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_START, (nStage == TCINTERLOCK_STAGE_START) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_PROGRESS, (nStage == TCINTERLOCK_STAGE_PROGRESS) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_COMPLETION, (nStage == TCINTERLOCK_STAGE_COMPLETION) ? TRUE : FALSE);
		SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME, CB_SETCURSEL, (WPARAM)((nScope == TCINTERLOCK_SCOPE_LOCALSUBSYSTEM || nScope == TCINTERLOCK_SCOPE_LOCALSUBSYSTEMNOWAIT) ? SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)TranslateIDToSubSystem(TCINTERLOCKAPIDFROMCODE(pInterlock->GetScope()))) : -1));
		GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_NOWAITSTATE)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_LOCAL) || IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM));
		GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM));
		AdjustToPrivileges();
		return;
	}
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_GLOBAL, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_LOCAL, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_TELECOMMANDS, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_NOWAITSTATE, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_RECEPTION, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_TRANSMISSION, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_ACCEPTANCE, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_START, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_PROGRESS, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_COMPLETION, FALSE);
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_NOWAITSTATE)->EnableWindow(FALSE);
	AdjustToPrivileges();
}

CTCInterlock *CTCProceduresMonitorCommandInterlocksDialog::FindInterlock() CONST
{
	CString  szName;

	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME)->GetWindowText(szName);
	return m_pInterlocks[0].GetAt(m_pInterlocks[0].Find(TCINTERLOCK_SOURCETYPE_PROCEDURESMONITOR, szName));
}

UINT CTCProceduresMonitorCommandInterlocksDialog::TranslateToSubSystemID(LPCTSTR pszSubSystem) CONST
{
	return GetTCService()->TranslateTCSubSystemToID(pszSubSystem);
}

CString CTCProceduresMonitorCommandInterlocksDialog::TranslateIDToSubSystem(UINT nSubSystemID) CONST
{
	return GetTCService()->TranslateIDToTCSubSystem(nSubSystemID);
}

BOOL CTCProceduresMonitorCommandInterlocksDialog::CanAddInterlock() CONST
{
	return((!FindInterlock() && Check(FALSE)) ? ((CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) && !IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_GLOBAL)) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)) : FALSE);
}

BOOL CTCProceduresMonitorCommandInterlocksDialog::CanRemoveInterlock() CONST
{
	CTCInterlock  *pInterlock;

	return(((pInterlock = FindInterlock()) && !pInterlock->IsAutomatic()) ? ((CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) && TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) != TCINTERLOCK_SCOPE_GLOBAL) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)) : FALSE);
}

BOOL CTCProceduresMonitorCommandInterlocksDialog::CanRemoveAllInterlocks() CONST
{
	INT  nInterlock;
	INT  nInterlocks;
	CTCInterlock  *pInterlock;

	for (nInterlock = 0, nInterlocks = (INT)m_pInterlocks[0].GetSize(); nInterlock < nInterlocks; nInterlock++)
	{
		if ((pInterlock = m_pInterlocks[0].GetAt(nInterlock)) && !pInterlock->IsAutomatic() && ((CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) && TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) != TCINTERLOCK_SCOPE_GLOBAL) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE))) break;
		continue;
	}
	return((nInterlock < nInterlocks) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorCommandInterlocksDialog::AdjustToPrivileges()
{
	BOOL  bCheck[2];
	CTCInterlock  *pInterlock;

	for (bCheck[0] = CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE), bCheck[1] = CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE), bCheck[0] = bCheck[0] || bCheck[1]; (pInterlock = FindInterlock()); )
	{
		bCheck[0] = ((pInterlock->GetState() == TCINTERLOCK_STATE_NONE || pInterlock->GetState() == TCINTERLOCK_STATE_IDLE) && !pInterlock->IsAutomatic()) ? bCheck[0] : FALSE;
		bCheck[1] = ((pInterlock->GetState() == TCINTERLOCK_STATE_NONE || pInterlock->GetState() == TCINTERLOCK_STATE_IDLE) && !pInterlock->IsAutomatic()) ? bCheck[1] : FALSE;
		bCheck[0] = (TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) != TCINTERLOCK_SCOPE_GLOBAL || bCheck[1]) ? bCheck[0] : FALSE;
		break;
	}
	AccessControl(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME, CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE));
	AccessControl(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_GLOBAL, bCheck[1]);
	AccessControl(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_LOCAL, bCheck[0]);
	AccessControl(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM, bCheck[0]);
	AccessControl(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME, bCheck[0]);
	AccessControl(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_TELECOMMANDS, bCheck[0]);
	AccessControl(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_NOWAITSTATE, bCheck[0]);
	AccessControl(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_RECEPTION, bCheck[0]);
	AccessControl(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_TRANSMISSION, bCheck[0]);
	AccessControl(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_ACCEPTANCE, bCheck[0]);
	AccessControl(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_START, bCheck[0]);
	AccessControl(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_PROGRESS, bCheck[0]);
	AccessControl(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_COMPLETION, bCheck[0]);
}

BOOL CTCProceduresMonitorCommandInterlocksDialog::IsModified() CONST
{
	return !m_pInterlocks[0].Compare(&m_pInterlocks[1]);
}

BOOL CTCProceduresMonitorCommandInterlocksDialog::Check(BOOL bModified) CONST
{
	return(((GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME)->GetWindowTextLength() > 0 && (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_GLOBAL) || IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_LOCAL) || (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM) && GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME)->SendMessage(CB_GETCURSEL) >= 0) || IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_TELECOMMANDS)) && (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_RECEPTION) || IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_TRANSMISSION) || IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_ACCEPTANCE) || IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_START) || IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_PROGRESS) || IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_COMPLETION))) || (!GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME)->GetWindowTextLength() && !IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_GLOBAL) && !IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_LOCAL) && !IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM) && !IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_TELECOMMANDS) && !IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_RECEPTION) && !IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_TRANSMISSION) && !IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_ACCEPTANCE) && !IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_START) && !IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_PROGRESS) && !IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_COMPLETION))) ? (!bModified || IsModified()) : FALSE);
}

void CTCProceduresMonitorCommandInterlocksDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProceduresMonitorCommandInterlocksDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorCommandInterlocksDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCProceduresMonitorCommandInterlocksDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_ADD, OnAdd)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_REMOVEALL, OnRemoveAll)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_GLOBAL, OnScopeGlobal)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_LOCAL, OnScopeLocal)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM, OnScopeSubSystem)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_TELECOMMANDS, OnScopeTeleommands)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_NOWAITSTATE, OnScopeNoWaitState)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_RECEPTION, OnStageReception)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_TRANSMISSION, OnStageTransmission)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_ACCEPTANCE, OnStageAcceptance)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_START, OnStageStart)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_PROGRESS, OnStageProgress)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_COMPLETION, OnStageCompletion)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME, OnEditchangeName)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME, OnSelchangeName)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME, OnSelchangeSubSystem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorCommandInterlocksDialog message handlers

BOOL CTCProceduresMonitorCommandInterlocksDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_GLOBAL)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_LOCAL)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_TELECOMMANDS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_RECEPTION)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_TRANSMISSION)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_ACCEPTANCE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_START)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_PROGRESS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_COMPLETION)->EnableWindow();
	EnumInterlocks();
	EnumSubSystems();
	AdjustToPrivileges();
	return TRUE;
}

void CTCProceduresMonitorCommandInterlocksDialog::OnAdd()
{
	UINT  nScope;
	UINT  nStage;
	CString  szName;
	CString  szSubSystem;
	CTCInterlock  *pInterlock;
	CHourglassCursor  cCursor;

	for (; (pInterlock = new CTCInterlock); )
	{
		GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME)->GetWindowText(szName);
		GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME)->GetWindowText(szSubSystem);
		nScope = (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_GLOBAL)) ? TCINTERLOCK_SCOPE_GLOBAL : TCINTERLOCK_SCOPE_NONE;
		nScope = (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_LOCAL)) ? ((IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_NOWAITSTATE)) ? TCINTERLOCK_SCOPE_LOCALNOWAIT : TCINTERLOCK_SCOPE_LOCAL) : nScope;
		nScope = (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM)) ? ((IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_NOWAITSTATE)) ? TCINTERLOCK_SCOPE_LOCALSUBSYSTEMNOWAIT : TCINTERLOCK_SCOPE_LOCALSUBSYSTEM) : nScope;
		nScope = (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_TELECOMMANDS)) ? TCINTERLOCK_SCOPE_COMMANDS : nScope;
		nStage = (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_RECEPTION)) ? TCINTERLOCK_STAGE_RECEPTION : TCINTERLOCK_STAGE_NONE;
		nStage = (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_TRANSMISSION)) ? TCINTERLOCK_STAGE_TRANSMISSION : nStage;
		nStage = (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_ACCEPTANCE)) ? TCINTERLOCK_STAGE_ACCEPTANCE : nStage;
		nStage = (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_START)) ? TCINTERLOCK_STAGE_START : nStage;
		nStage = (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_PROGRESS)) ? TCINTERLOCK_STAGE_PROGRESS : nStage;
		nStage = (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_COMPLETION)) ? TCINTERLOCK_STAGE_COMPLETION : nStage;
		for (pInterlock->SetName(szName), pInterlock->SetSourceType(TCINTERLOCK_SOURCETYPE_PROCEDURESMONITOR), pInterlock->SetScope((IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM)) ? MAKETCINTERLOCKSCOPECODE(nScope, TranslateToSubSystemID(szSubSystem)) : MAKETCINTERLOCKSCOPECODE(nScope, 0)), pInterlock->SetStage(nStage); m_pInterlocks[0].Add(pInterlock) >= 0; )
		{
			SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szName));
			break;
		}
		if (SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szName) >= 0)
		{
			SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME, CB_SETEDITSEL, (WPARAM)NULL, MAKELPARAM(0, -1));
			GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_ADD)->EnableWindow(FALSE);
			GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_REMOVE)->EnableWindow(CanRemoveInterlock());
			GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_REMOVEALL)->EnableWindow(CanRemoveAllInterlocks());
			GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME)->SetFocus();
			break;
		}
		delete pInterlock;
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandInterlocksDialog::OnRemove()
{
	INT  nIndex;
	CString  szName;
	CTCInterlock  *pInterlock;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME)->GetWindowText(szName); (pInterlock = m_pInterlocks[0].GetAt((nIndex = m_pInterlocks[0].Find(TCINTERLOCK_SOURCETYPE_PROCEDURESMONITOR, szName)))); )
	{
		SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szName));
		SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME, CB_SETCURSEL, (WPARAM)-1);
		m_pInterlocks[0].RemoveAt(nIndex);
		delete pInterlock;
		ShowProperties();
		break;
	}
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_REMOVEALL)->EnableWindow(CanRemoveAllInterlocks());
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandInterlocksDialog::OnRemoveAll()
{
	INT  nInterlock;
	INT  nInterlocks;
	CTCInterlock  *pInterlock;
	CHourglassCursor  cCursor;

	for (nInterlock = 0, nInterlocks = (INT)m_pInterlocks[0].GetSize(); nInterlock < nInterlocks; nInterlock++)
	{
		if ((pInterlock = m_pInterlocks[0].GetAt(nInterlock)) && (pInterlock->GetState() == TCINTERLOCK_STATE_NONE || pInterlock->GetState() == TCINTERLOCK_STATE_IDLE) && (TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) != TCINTERLOCK_SCOPE_GLOBAL || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)))
		{
			SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pInterlock->GetName()));
			m_pInterlocks[0].RemoveAt(nInterlock);
			delete pInterlock;
			nInterlocks--;
			nInterlock--;
		}
	}
	if (!SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME, CB_GETCOUNT))
	{
		SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME, CB_SETCURSEL, (WPARAM)-1);
		ShowProperties();
	}
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandInterlocksDialog::OnScopeGlobal()
{
	CTCInterlock  *pInterlock;
	CHourglassCursor  cCursor;

	if ((pInterlock = FindInterlock())) pInterlock->SetScope(MAKETCINTERLOCKSCOPECODE(TCINTERLOCK_SCOPE_GLOBAL, 0));
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME, CB_SETCURSEL, (WPARAM)-1);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_GLOBAL, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_LOCAL, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_TELECOMMANDS, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_NOWAITSTATE, FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_NOWAITSTATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_ADD)->EnableWindow(CanAddInterlock());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandInterlocksDialog::OnScopeLocal()
{
	CTCInterlock  *pInterlock;
	CHourglassCursor  cCursor;

	if ((pInterlock = FindInterlock())) pInterlock->SetScope((IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_NOWAITSTATE)) ? MAKETCINTERLOCKSCOPECODE(TCINTERLOCK_SCOPE_LOCALNOWAIT, 0) : MAKETCINTERLOCKSCOPECODE(TCINTERLOCK_SCOPE_LOCAL, 0));
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME, CB_SETCURSEL, (WPARAM)-1);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_GLOBAL, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_LOCAL, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_TELECOMMANDS, FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_NOWAITSTATE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_ADD)->EnableWindow(CanAddInterlock());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandInterlocksDialog::OnScopeSubSystem()
{
	CTCInterlock  *pInterlock;
	CHourglassCursor  cCursor;

	if ((pInterlock = FindInterlock())) pInterlock->SetScope((IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_NOWAITSTATE)) ? MAKETCINTERLOCKSCOPECODE(TCINTERLOCK_SCOPE_LOCALSUBSYSTEMNOWAIT, -1) : MAKETCINTERLOCKSCOPECODE(TCINTERLOCK_SCOPE_LOCALSUBSYSTEM, -1));
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_GLOBAL, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_LOCAL, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_TELECOMMANDS, FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_NOWAITSTATE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_ADD)->EnableWindow(CanAddInterlock());
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandInterlocksDialog::OnScopeTeleommands()
{
	CTCInterlock  *pInterlock;
	CHourglassCursor  cCursor;

	if ((pInterlock = FindInterlock())) pInterlock->SetScope(MAKETCINTERLOCKSCOPECODE(TCINTERLOCK_SCOPE_COMMANDS, 0));
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME, CB_SETCURSEL, (WPARAM)-1);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_GLOBAL, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_LOCAL, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_TELECOMMANDS, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_NOWAITSTATE, FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_NOWAITSTATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_ADD)->EnableWindow(CanAddInterlock());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandInterlocksDialog::OnScopeNoWaitState()
{
	CTCInterlock  *pInterlock;
	CHourglassCursor  cCursor;

	if ((pInterlock = FindInterlock())) pInterlock->SetScope((IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_NOWAITSTATE)) ? ((IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_LOCAL)) ? MAKETCINTERLOCKSCOPECODE(TCINTERLOCK_SCOPE_LOCALNOWAIT, 0) : MAKETCINTERLOCKSCOPECODE(TCINTERLOCK_SCOPE_LOCALSUBSYSTEMNOWAIT, -1)) : ((IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_LOCAL)) ? MAKETCINTERLOCKSCOPECODE(TCINTERLOCK_SCOPE_LOCAL, 0) : MAKETCINTERLOCKSCOPECODE(TCINTERLOCK_SCOPE_LOCALSUBSYSTEM, -1)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandInterlocksDialog::OnStageReception()
{
	CTCInterlock  *pInterlock;
	CHourglassCursor  cCursor;

	if ((pInterlock = FindInterlock())) pInterlock->SetStage(TCINTERLOCK_STAGE_RECEPTION);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_RECEPTION, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_TRANSMISSION, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_ACCEPTANCE, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_START, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_PROGRESS, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_COMPLETION, FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_ADD)->EnableWindow(CanAddInterlock());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandInterlocksDialog::OnStageTransmission()
{
	CTCInterlock  *pInterlock;
	CHourglassCursor  cCursor;

	if ((pInterlock = FindInterlock())) pInterlock->SetStage(TCINTERLOCK_STAGE_TRANSMISSION);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_RECEPTION, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_TRANSMISSION, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_ACCEPTANCE, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_START, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_PROGRESS, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_COMPLETION, FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_ADD)->EnableWindow(CanAddInterlock());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandInterlocksDialog::OnStageAcceptance()
{
	CTCInterlock  *pInterlock;
	CHourglassCursor  cCursor;

	if ((pInterlock = FindInterlock())) pInterlock->SetStage(TCINTERLOCK_STAGE_ACCEPTANCE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_RECEPTION, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_TRANSMISSION, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_ACCEPTANCE, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_START, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_PROGRESS, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_COMPLETION, FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_ADD)->EnableWindow(CanAddInterlock());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandInterlocksDialog::OnStageStart()
{
	CTCInterlock  *pInterlock;
	CHourglassCursor  cCursor;

	if ((pInterlock = FindInterlock())) pInterlock->SetStage(TCINTERLOCK_STAGE_START);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_RECEPTION, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_TRANSMISSION, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_ACCEPTANCE, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_START, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_PROGRESS, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_COMPLETION, FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_ADD)->EnableWindow(CanAddInterlock());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandInterlocksDialog::OnStageProgress()
{
	CTCInterlock  *pInterlock;
	CHourglassCursor  cCursor;

	if ((pInterlock = FindInterlock())) pInterlock->SetStage(TCINTERLOCK_STAGE_PROGRESS);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_RECEPTION, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_TRANSMISSION, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_ACCEPTANCE, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_START, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_PROGRESS, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_COMPLETION, FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_ADD)->EnableWindow(CanAddInterlock());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandInterlocksDialog::OnStageCompletion()
{
	CTCInterlock  *pInterlock;
	CHourglassCursor  cCursor;

	if ((pInterlock = FindInterlock())) pInterlock->SetStage(TCINTERLOCK_STAGE_COMPLETION);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_RECEPTION, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_TRANSMISSION, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_ACCEPTANCE, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_START, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_PROGRESS, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_COMPLETION, TRUE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_ADD)->EnableWindow(CanAddInterlock());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandInterlocksDialog::OnEditchangeName()
{
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_ADD)->EnableWindow(CanAddInterlock());
	AdjustToPrivileges();
}

void CTCProceduresMonitorCommandInterlocksDialog::OnSelchangeName()
{
	if (SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME, CB_GETCURSEL)) >= 0)
	{
		AdjustToPrivileges();
		ShowProperties();
	}
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_ADD)->EnableWindow(CanAddInterlock());
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_REMOVE)->EnableWindow(CanRemoveInterlock());
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_REMOVEALL)->EnableWindow(CanRemoveAllInterlocks());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandInterlocksDialog::OnSelchangeSubSystem()
{
	CString  szSubSystem;
	CTCInterlock  *pInterlock;

	if ((pInterlock = FindInterlock()))
	{
		GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME)->GetWindowText(szSubSystem);
		pInterlock->SetScope(MAKETCINTERLOCKSCOPECODE(TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()), TranslateToSubSystemID(szSubSystem)));
	}
	GetDlgItem(IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_ADD)->EnableWindow(CanAddInterlock());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorCommandInterlocksDialog::OnOK()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnOK();
}

BOOL CTCProceduresMonitorCommandInterlocksDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORCOMMANDINTERLOCKSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCProceduresMonitorCommandInterlocksDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORCOMMANDINTERLOCKSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorAlertOptionsDialog dialog

IMPLEMENT_DYNCREATE(CTCProceduresMonitorAlertOptionsDialog, CDisplayDialog)

CTCProceduresMonitorAlertOptionsDialog::CTCProceduresMonitorAlertOptionsDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCProceduresMonitorAlertOptionsDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCProceduresMonitorAlertOptionsDialog::Create(CWnd *pParentWnd, CTCProceduresMonitorItem *pItem)
{
	INT  nResult;

	return(((nResult = (m_cItem[0].Copy(pItem) && m_cItem[1].Copy(pItem)) ? CDisplayDialog::Create(pParentWnd, CTCProceduresMonitorAlertOptionsDialog::IDD) : -1) == IDOK  &&  pItem->Copy(&m_cItem[0])) ? IDOK : nResult);
}

CTCProceduresMonitorSettingsContentsPage *CTCProceduresMonitorAlertOptionsDialog::GetParentDialog() CONST
{
	return((CTCProceduresMonitorSettingsContentsPage *)CDisplayDialog::GetParent());
}

CTCProceduresMonitorWnd *CTCProceduresMonitorAlertOptionsDialog::GetParentDisplay() CONST
{
	return((CTCProceduresMonitorWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CTCProceduresMonitorAlertOptionsDialog::EnumTypes()
{
	return((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_INSERTSTRING, TCPROCEDURESMONITORITEM_ALERTTYPE_INFORMATIONAL, (LPARAM)STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_ALERTTYPE_INFORMATIONALMESSAGES)) >= 0 && SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_INSERTSTRING, TCPROCEDURESMONITORITEM_ALERTTYPE_WARNING, (LPARAM)STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_ALERTTYPE_WARNINGS)) >= 0 && SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_INSERTSTRING, TCPROCEDURESMONITORITEM_ALERTTYPE_ERROR, (LPARAM)STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_ALERTTYPE_ERRORS)) >= 0 && SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_INSERTSTRING, TCPROCEDURESMONITORITEM_ALERTTYPE_ALERT, (LPARAM)STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_ALERTTYPE_ALERTS)) >= 0 && SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_INSERTSTRING, TCPROCEDURESMONITORITEM_ALERTTYPE_AUTHORIZATION, (LPARAM)STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_ALERTTYPE_AUTHORIZATIONS)) >= 0 && SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_ALERTTYPE_ALERTS)))) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorAlertOptionsDialog::EnumAuditions()
{
	INT  nAudition;
	INT  nAuditions;
	CStringArray  szAuditions;

	for (nAudition = 0, nAuditions = (EnumAuditionProfiles(szAuditions)) ? (INT)szAuditions.GetSize() : 0; nAudition < nAuditions; nAudition++)
	{
		SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szAuditions.GetAt(nAudition));
		continue;
	}
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_AUDITION_NONE));
	return((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorAlertOptionsDialog::EnumNotifications()
{
	INT  nNotification;
	INT  nNotifications;
	CStringArray  szNotifications;

	for (nNotification = 0, nNotifications = (EnumNotificationProfiles(szNotifications)) ? (INT)szNotifications.GetSize() : 0; nNotification < nNotifications; nNotification++)
	{
		SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szNotifications.GetAt(nNotification));
		continue;
	}
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_NOTIFICATION_NONE));
	return((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorAlertOptionsDialog::ShowAlertDetails()
{
	INT  nNotification;
	INT  nNotifications;
	CString  szAudition;
	CString  szNotification;
	CStringArray  szNotifications;

	for (nNotification = 0, nNotifications = m_cItem[0].GetNotifications((UINT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_GETCURSEL), szNotifications), SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_RESETCONTENT); nNotification < nNotifications; nNotification++)
	{
		if (SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szNotifications.GetAt(nNotification)) >= 0)
		{
			SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_INSERTSTRING, nNotification, (LPARAM)(LPCTSTR)szNotifications.GetAt(nNotification));
			continue;
		}
	}
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_SETCURSEL);
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szAudition = (!m_cItem[0].GetAudition((UINT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_GETCURSEL)).IsEmpty()) ? m_cItem[0].GetAudition((UINT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_GETCURSEL)) : STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_AUDITION_NONE))));
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_cItem[0].GetAuditionColor((UINT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_GETCURSEL)));
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_NOTIFICATION_NONE)), 0));
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_ACKNOWLEDGMENT_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_cItem[0].GetAcknowledgmentColor((UINT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_GETCURSEL)));
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_BLINK, m_cItem[0].IsAuditionBlinkingEnabled((UINT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_GETCURSEL)));
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_ACKNOWLEDGMENT, m_cItem[0].IsAcknowledgmentEnabled((UINT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_GETCURSEL)));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_BLINK)->EnableWindow((szAudition != STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_AUDITION_NONE)) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_COLOR_STATIC)->EnableWindow((szAudition != STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_AUDITION_NONE)) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_COLOR)->EnableWindow((szAudition != STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_AUDITION_NONE)) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_ADD)->EnableWindow(((szNotification = Combobox_GetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS), (INT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS, CB_GETCURSEL))) != STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_NOTIFICATION_NONE) && SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szNotification) < 0) ? (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)) : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCURSEL) >= 0) ? (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)) : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCOUNT) > 0) ? (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)) : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_ACKNOWLEDGMENT_COLOR_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_ACKNOWLEDGMENT));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_ACKNOWLEDGMENT_COLOR)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_ACKNOWLEDGMENT));
}

VOID CTCProceduresMonitorAlertOptionsDialog::AdjustToPrivileges()
{
	BOOL  bCheck;

	AccessControl(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION, (bCheck = CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)));
	AccessControl(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_BLINK, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_COLOR, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_ACKNOWLEDGMENT, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_ACKNOWLEDGMENT_COLOR, bCheck);
}

BOOL CTCProceduresMonitorAlertOptionsDialog::IsModified() CONST
{
	return !m_cItem[0].Compare(&m_cItem[1]);
}

void CTCProceduresMonitorAlertOptionsDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProceduresMonitorAlertOptionsDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorAlertOptionsDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCProceduresMonitorAlertOptionsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_BLINK, OnAuditionBlink)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_ACKNOWLEDGMENT, OnAcknowledgeAlert)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_ADD, OnAddNotification)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVE, OnRemoveNotification)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVEALL, OnRemoveAllNotifications)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, OnSelchangeType)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION, OnSelchangeAudition)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_COLOR, OnSelchangeAuditionColor)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS, OnSelchangeNotification)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_ACKNOWLEDGMENT_COLOR, OnSelchangeAcknowledgeColor)
	ON_LBN_SELCHANGE(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, OnSelchangeNotificationList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorAlertOptionsDialog message handlers

BOOL CTCProceduresMonitorAlertOptionsDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_ACKNOWLEDGMENT)->EnableWindow();
	EnumTypes();
	EnumAuditions();
	EnumNotifications();
	ShowAlertDetails();
	AdjustToPrivileges();
	return TRUE;
}

void CTCProceduresMonitorAlertOptionsDialog::OnAuditionBlink()
{
	m_cItem[0].EnableAuditionBlinking((UINT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_GETCURSEL), IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_BLINK));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorAlertOptionsDialog::OnAcknowledgeAlert()
{
	m_cItem[0].EnableAcknowledgment((UINT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_GETCURSEL), IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_ACKNOWLEDGMENT));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_ACKNOWLEDGMENT_COLOR_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_ACKNOWLEDGMENT));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_ACKNOWLEDGMENT_COLOR)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_ACKNOWLEDGMENT));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorAlertOptionsDialog::OnAddNotification()
{
	INT  nIndex;
	CString  szNotification;
	CStringArray  szNotifications;
	CHourglassCursor  cCursor;

	if ((nIndex = (INT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)(szNotification = Combobox_GetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS), (INT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS, CB_GETCURSEL))))) >= 0)
	{
		for (SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_SETCURSEL, nIndex); m_cItem[0].GetNotifications((UINT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_GETCURSEL), szNotifications) >= 0; )
		{
			szNotifications.InsertAt(nIndex, szNotification);
			break;
		}
		m_cItem[0].SetNotifications((UINT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_GETCURSEL), szNotifications);
	}
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCURSEL) >= 0) ? (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)) : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCOUNT) > 0) ? (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)) : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorAlertOptionsDialog::OnRemoveNotification()
{
	INT  nIndex;
	CString  szNotification;
	CStringArray  szNotifications;
	CHourglassCursor  cCursor;

	if (SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_DELETESTRING, (nIndex = (INT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCURSEL))) >= 0)
	{
		for (SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_SETCURSEL); m_cItem[0].GetNotifications((UINT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_GETCURSEL), szNotifications) >= 0; )
		{
			szNotifications.RemoveAt(nIndex);
			break;
		}
		m_cItem[0].SetNotifications((UINT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_GETCURSEL), szNotifications);
	}
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_ADD)->EnableWindow(((szNotification = Combobox_GetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS), (INT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS, CB_GETCURSEL))) != STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_NOTIFICATION_NONE) && SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szNotification) < 0) ? (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)) : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCURSEL) >= 0) ? (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)) : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCOUNT) > 0) ? (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)) : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorAlertOptionsDialog::OnRemoveAllNotifications()
{
	CString  szNotification;
	CStringArray  szNotifications;
	CHourglassCursor  cCursor;

	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_RESETCONTENT);
	m_cItem[0].SetNotifications((UINT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_GETCURSEL), szNotifications);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_ADD)->EnableWindow(((szNotification = Combobox_GetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS), (INT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS, CB_GETCURSEL))) != STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_NOTIFICATION_NONE) && SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szNotification) < 0) ? (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)) : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorAlertOptionsDialog::OnSelchangeType()
{
	ShowAlertDetails();
}

void CTCProceduresMonitorAlertOptionsDialog::OnSelchangeAudition()
{
	CString  szAudition;

	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION)->GetWindowText(szAudition);
	m_cItem[0].SetAudition((UINT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_GETCURSEL), (szAudition != STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_AUDITION_NONE)) ? szAudition : EMPTYSTRING);
	m_cItem[0].EnableAuditionBlinking((UINT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_GETCURSEL), (szAudition != STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_AUDITION_NONE)) ? IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_BLINK) : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_BLINK, (szAudition != STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_AUDITION_NONE)) ? IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_BLINK) : FALSE);
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_cItem[0].GetAuditionColor((UINT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_GETCURSEL)));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_BLINK)->EnableWindow((szAudition != STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_AUDITION_NONE)) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_COLOR_STATIC)->EnableWindow((szAudition != STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_AUDITION_NONE)) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_COLOR)->EnableWindow((szAudition != STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_AUDITION_NONE)) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorAlertOptionsDialog::OnSelchangeAuditionColor()
{
	m_cItem[0].SetAuditionColor((UINT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_GETCURSEL), (COLORREF)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_COLOR, CB_GETCURSEL)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorAlertOptionsDialog::OnSelchangeNotification()
{
	CString  szNotification;

	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS)->GetWindowText(szNotification);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_ADD)->EnableWindow((szNotification != STRING(IDS_TCPROCEDURESMONITORALERTOPTIONSDIALOG_NOTIFICATION_NONE) && SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szNotification) < 0) ? (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)) : FALSE);
}

void CTCProceduresMonitorAlertOptionsDialog::OnSelchangeNotificationList()
{
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCURSEL) >= 0) ? (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)) : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCOUNT) > 0) ? (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)) : FALSE);
}

void CTCProceduresMonitorAlertOptionsDialog::OnSelchangeAcknowledgeColor()
{
	m_cItem[0].SetAcknowledgmentColor((UINT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE, CB_GETCURSEL), (COLORREF)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_ACKNOWLEDGMENT_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_ACKNOWLEDGMENT_COLOR, CB_GETCURSEL)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorAlertOptionsDialog::OnOK()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnOK();
}

BOOL CTCProceduresMonitorAlertOptionsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORALERTOPTIONSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCProceduresMonitorAlertOptionsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORALERTOPTIONSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorLoggingOptionsDialog dialog

IMPLEMENT_DYNCREATE(CTCProceduresMonitorLoggingOptionsDialog, CDisplayDialog)

CTCProceduresMonitorLoggingOptionsDialog::CTCProceduresMonitorLoggingOptionsDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCProceduresMonitorLoggingOptionsDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCProceduresMonitorLoggingOptionsDialog::Create(CWnd *pParentWnd, CString &szArchivalFileName, UINT &nArchivalPolicy, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName)
{
	INT  nResult;

	for (m_nArchivalPolicy[0] = m_nArchivalPolicy[1] = nArchivalPolicy, m_szArchivalFileName[0] = m_szArchivalFileName[1] = szArchivalFileName, m_dwArchivalRetention[0] = m_dwArchivalRetention[1] = dwArchivalRetention, m_tArchivalRetention[0] = m_tArchivalRetention[1] = tArchivalRetention, m_szRetrievalFileName[0] = m_szRetrievalFileName[1] = szRetrievalFileName; (nResult = CDisplayDialog::Create(pParentWnd, CTCProceduresMonitorLoggingOptionsDialog::IDD)) == IDOK; )
	{
		szRetrievalFileName = m_szRetrievalFileName[0];
		szArchivalFileName = m_szArchivalFileName[0];
		dwArchivalRetention = m_dwArchivalRetention[0];
		tArchivalRetention = m_tArchivalRetention[0];
		nArchivalPolicy = m_nArchivalPolicy[0];
		break;
	}
	return nResult;
}

CTCProceduresMonitorLoggingPage *CTCProceduresMonitorLoggingOptionsDialog::GetParentDialog() CONST
{
	return((CTCProceduresMonitorLoggingPage *)CDisplayDialog::GetParent());
}

CTCProceduresMonitorWnd *CTCProceduresMonitorLoggingOptionsDialog::GetParentDisplay() CONST
{
	return((CTCProceduresMonitorWnd *)CDisplayDialog::GetParentDisplay());
}

VOID CTCProceduresMonitorLoggingOptionsDialog::ShowLoggingOptions()
{
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_DISABLED, (m_nArchivalPolicy[0] & LOGFILE_POLICY_DISABLED) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_OVERWRITE, ((m_nArchivalPolicy[0] & LOGFILE_POLICY_CYCLICMODE) && (m_nArchivalPolicy[0] & LOGFILE_POLICY_RETENTIONBYTIME) != LOGFILE_POLICY_RETENTIONBYTIME) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_OLDOVERWRITE, ((m_nArchivalPolicy[0] & LOGFILE_POLICY_CYCLICMODE) && (m_nArchivalPolicy[0] & LOGFILE_POLICY_RETENTIONBYTIME)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_NOOVERWRITE, ((m_nArchivalPolicy[0] & LOGFILE_POLICY_CYCLICMODE) != LOGFILE_POLICY_CYCLICMODE) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_UNLIMITED, ((m_nArchivalPolicy[0] & LOGFILE_POLICY_RETENTIONBYSIZE) != LOGFILE_POLICY_RETENTIONBYSIZE) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_LIMITED, (m_nArchivalPolicy[0] & LOGFILE_POLICY_RETENTIONBYSIZE) ? TRUE : FALSE);
	Spinbox_SetPos(GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_DAYS), m_tArchivalRetention[0].GetTotalSeconds() / SECONDSPERDAY);
	Spinbox_SetPos(GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_MAXIMUM), m_dwArchivalRetention[0] / 1024);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_FILENAME)->SetWindowText(m_szArchivalFileName[0]);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_DAYS)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_OLDOVERWRITE));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_DAYS_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_OLDOVERWRITE));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_MAXIMUM)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_LIMITED));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_MAXIMUM_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_LIMITED));
}

VOID CTCProceduresMonitorLoggingOptionsDialog::AdjustToPrivileges()
{
	BOOL  bCheck;

	AccessControl(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_FILENAME, (bCheck = CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)));
	AccessControl(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_DISABLED, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_OVERWRITE, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_OLDOVERWRITE, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_DAYS, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_NOOVERWRITE, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_UNLIMITED, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_LIMITED, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_MAXIMUM, bCheck);
	AccessControl(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_RESET, bCheck);
}

BOOL CTCProceduresMonitorLoggingOptionsDialog::IsModified() CONST
{
	return((m_nArchivalPolicy[0] != m_nArchivalPolicy[1] || m_szArchivalFileName[0].CompareNoCase(m_szArchivalFileName[1]) || m_dwArchivalRetention[0] != m_dwArchivalRetention[1] || m_tArchivalRetention[0] != m_tArchivalRetention[1] || m_szRetrievalFileName[0].CompareNoCase(m_szRetrievalFileName[1])) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorLoggingOptionsDialog::Check(BOOL bModified) CONST
{
	return((!m_szArchivalFileName[0].IsEmpty() && !m_szRetrievalFileName[0].IsEmpty()) ? (!bModified || IsModified()) : FALSE);
}

void CTCProceduresMonitorLoggingOptionsDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProceduresMonitorLoggingOptionsDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorLoggingOptionsDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCProceduresMonitorLoggingOptionsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_RETRIEVALS, OnRetrievals)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_BROWSE, OnBrowseFileName)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_OVERWRITE, OnOverwriteLogs)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_OLDOVERWRITE, OnOverwriteOldLogs)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_NOOVERWRITE, OnOverwriteNoLogs)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_UNLIMITED, OnUnlimitedSize)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_LIMITED, OnLimitedSize)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_RESET, OnResetSize)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_DISABLED, OnDisabled)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_HELP, OnHelp)
	ON_CONTROL(SBXN_CHANGE, IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_DAYS, OnSpinchangeDays)
	ON_CONTROL(SBXN_CHANGE, IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_MAXIMUM, OnSpinchangeSize)
	ON_EN_CHANGE(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_FILENAME, OnEditchangeFileName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorLoggingOptionsDialog message handlers

BOOL CTCProceduresMonitorLoggingOptionsDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	Spinbox_SetRange(GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_DAYS), TCPROCEDURESMONITORLOGGINGOPTIONS_MINIMUMDAYS, TCPROCEDURESMONITORLOGGINGOPTIONS_MAXIMUMDAYS);
	Spinbox_SetRange(GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_MAXIMUM), TCPROCEDURESMONITORLOGGINGOPTIONS_MINIMUMSIZE, TCPROCEDURESMONITORLOGGINGOPTIONS_MAXIMUMSIZE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_FILENAME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_BROWSE)->EnableWindow(CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_DISABLED)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_RETRIEVALS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_OVERWRITE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_OLDOVERWRITE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_NOOVERWRITE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_UNLIMITED)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_LIMITED)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_RESET)->EnableWindow();
	ShowLoggingOptions();
	AdjustToPrivileges();
	return TRUE;
}

void CTCProceduresMonitorLoggingOptionsDialog::OnRetrievals()
{
	CTCProceduresMonitorRetrievalOptionsDialog  cRetrievalOptions;

	cRetrievalOptions.Create(this, m_szRetrievalFileName[0]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorLoggingOptionsDialog::OnBrowseFileName()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_FILENAME, STRING(IDS_FILEBROWSEDIALOG_TCPROCEDURESMONITORLOGFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_TCPROCEDURESMONITORLOGFILEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK) GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_FILENAME)->SetWindowText((m_szArchivalFileName[0] = cFileBrowseDialog.GetPathName()));
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorLoggingOptionsDialog::OnOverwriteLogs()
{
	m_nArchivalPolicy[0] = (m_nArchivalPolicy[0] & LOGFILE_POLICY_RETENTIONBYSIZE) | LOGFILE_POLICY_CYCLICMODE;
	Spinbox_SetPos(GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_DAYS), (m_tArchivalRetention[0] = 0).GetTotalSeconds());
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_OVERWRITE, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_OLDOVERWRITE, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_NOOVERWRITE, FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_DAYS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_DAYS)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorLoggingOptionsDialog::OnOverwriteOldLogs()
{
	m_nArchivalPolicy[0] = (m_nArchivalPolicy[0] & LOGFILE_POLICY_RETENTIONBYSIZE) | LOGFILE_POLICY_CYCLICMODE | LOGFILE_POLICY_RETENTIONBYTIME;
	Spinbox_SetPos(GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_DAYS), (m_tArchivalRetention[0] = SECONDSPERDAY*TCPROCEDURESMONITORLOGGINGOPTIONS_DEFAULTDAYS).GetTotalSeconds() / SECONDSPERDAY);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_OVERWRITE, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_OLDOVERWRITE, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_NOOVERWRITE, FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_DAYS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_DAYS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_DAYS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorLoggingOptionsDialog::OnOverwriteNoLogs()
{
	m_nArchivalPolicy[0] = (m_nArchivalPolicy[0] & LOGFILE_POLICY_RETENTIONBYSIZE) | LOGFILE_POLICY_NONCYCLICMODE;
	Spinbox_SetPos(GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_DAYS), (m_tArchivalRetention[0] = 0).GetTotalSeconds());
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_OVERWRITE, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_OLDOVERWRITE, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_NOOVERWRITE, TRUE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_DAYS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_DAYS)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorLoggingOptionsDialog::OnUnlimitedSize()
{
	m_nArchivalPolicy[0] &= ~LOGFILE_POLICY_RETENTIONBYSIZE;
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_UNLIMITED, TRUE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_LIMITED, FALSE);
	Spinbox_SetPos(GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_MAXIMUM), (m_dwArchivalRetention[0] = 0));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_MAXIMUM_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_MAXIMUM)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorLoggingOptionsDialog::OnLimitedSize()
{
	m_nArchivalPolicy[0] |= LOGFILE_POLICY_RETENTIONBYSIZE;
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_UNLIMITED, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_LIMITED, TRUE);
	Spinbox_SetPos(GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_MAXIMUM), (m_dwArchivalRetention[0] = 1024 * TCPROCEDURESMONITORLOGGINGOPTIONS_DEFAULTSIZE) / 1024);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_MAXIMUM_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_MAXIMUM)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_MAXIMUM)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorLoggingOptionsDialog::OnResetSize()
{
	m_nArchivalPolicy[0] = (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_RESET)) ? (m_nArchivalPolicy[0] | LOGFILE_POLICY_RESET) : (m_nArchivalPolicy[0] & ~LOGFILE_POLICY_RESET);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorLoggingOptionsDialog::OnDisabled()
{
	m_nArchivalPolicy[0] = (IsDlgButtonChecked(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_DISABLED)) ? (m_nArchivalPolicy[0] | LOGFILE_POLICY_DISABLED) : (m_nArchivalPolicy[0] & ~LOGFILE_POLICY_DISABLED);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorLoggingOptionsDialog::OnSpinchangeDays()
{
	m_tArchivalRetention[0] = SECONDSPERDAY*Spinbox_GetPos(GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_DAYS));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorLoggingOptionsDialog::OnSpinchangeSize()
{
	m_dwArchivalRetention[0] = 1024 * Spinbox_GetPos(GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_MAXIMUM));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorLoggingOptionsDialog::OnEditchangeFileName()
{
	GetDlgItem(IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_FILENAME)->GetWindowText(m_szArchivalFileName[0]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorLoggingOptionsDialog::OnOK()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnOK();
}

BOOL CTCProceduresMonitorLoggingOptionsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORLOGGINGOPTIONSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCProceduresMonitorLoggingOptionsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORLOGGINGOPTIONSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorRetrievalOptionsDialog dialog

IMPLEMENT_DYNCREATE(CTCProceduresMonitorRetrievalOptionsDialog, CDisplayDialog)

CTCProceduresMonitorRetrievalOptionsDialog::CTCProceduresMonitorRetrievalOptionsDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCProceduresMonitorRetrievalOptionsDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCProceduresMonitorRetrievalOptionsDialog::Create(CWnd *pParentWnd, CString &szFileName)
{
	INT  nResult;

	for (m_szFileName[0] = m_szFileName[1] = szFileName; (nResult = CDisplayDialog::Create(pParentWnd, CTCProceduresMonitorRetrievalOptionsDialog::IDD)) == IDOK; )
	{
		szFileName = m_szFileName[0];
		break;
	}
	return nResult;
}

CTCProceduresMonitorLoggingOptionsDialog *CTCProceduresMonitorRetrievalOptionsDialog::GetParentDialog() CONST
{
	return((CTCProceduresMonitorLoggingOptionsDialog *)CDisplayDialog::GetParent());
}

CTCProceduresMonitorWnd *CTCProceduresMonitorRetrievalOptionsDialog::GetParentDisplay() CONST
{
	return((CTCProceduresMonitorWnd *)CDisplayDialog::GetParentDisplay());
}

VOID CTCProceduresMonitorRetrievalOptionsDialog::AdjustToPrivileges()
{
	AccessControl(IDC_TCPROCEDURESMONITOR_RETRIEVALOPTIONS_FILENAME, CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE));
}

BOOL CTCProceduresMonitorRetrievalOptionsDialog::IsModified() CONST
{
	return((m_szFileName[0].CompareNoCase(m_szFileName[1])) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorRetrievalOptionsDialog::Check(BOOL bModified) CONST
{
	return((!m_szFileName[0].IsEmpty()) ? (!bModified || IsModified()) : FALSE);
}

void CTCProceduresMonitorRetrievalOptionsDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProceduresMonitorRetrievalOptionsDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorRetrievalOptionsDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCProceduresMonitorRetrievalOptionsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_RETRIEVALOPTIONS_BROWSE, OnBrowseFileName)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_RETRIEVALOPTIONS_HELP, OnHelp)
	ON_EN_CHANGE(IDC_TCPROCEDURESMONITOR_RETRIEVALOPTIONS_FILENAME, OnEditchangeFileName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorRetrievalOptionsDialog message handlers

BOOL CTCProceduresMonitorRetrievalOptionsDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_RETRIEVALOPTIONS_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_RETRIEVALOPTIONS_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_RETRIEVALOPTIONS_FILENAME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_RETRIEVALOPTIONS_FILENAME)->SetWindowText(m_szFileName[0]);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_RETRIEVALOPTIONS_BROWSE)->EnableWindow(CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE));
	AdjustToPrivileges();
	return TRUE;
}

void CTCProceduresMonitorRetrievalOptionsDialog::OnBrowseFileName()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_TCPROCEDURESMONITOR_RETRIEVALOPTIONS_FILENAME, STRING(IDS_FILEBROWSEDIALOG_TCPROCEDURESMONITORLOGFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_TCPROCEDURESMONITORLOGFILEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK) GetDlgItem(IDC_TCPROCEDURESMONITOR_RETRIEVALOPTIONS_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
	SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_RETRIEVALOPTIONS_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_RETRIEVALOPTIONS_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorRetrievalOptionsDialog::OnEditchangeFileName()
{
	GetDlgItem(IDC_TCPROCEDURESMONITOR_RETRIEVALOPTIONS_FILENAME)->GetWindowText(m_szFileName[0]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorRetrievalOptionsDialog::OnOK()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnOK();
}

BOOL CTCProceduresMonitorRetrievalOptionsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORRETRIEVALOPTIONSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCProceduresMonitorRetrievalOptionsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORRETRIEVALOPTIONSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorDetailsDialog dialog

IMPLEMENT_DYNCREATE(CTCProceduresMonitorDetailsDialog, CDisplayDialog)

CTCProceduresMonitorDetailsDialog::CTCProceduresMonitorDetailsDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCProceduresMonitorDetailsDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCProceduresMonitorDetailsDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CTCProceduresMonitorDetailsDialog::IDD);
}

CTCProceduresMonitorWnd *CTCProceduresMonitorDetailsDialog::GetParentDisplay() CONST
{
	return((CTCProceduresMonitorWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CTCProceduresMonitorDetailsDialog::EnumProcedureArguments()
{
	INT  nColumn;
	INT  nColumns;
	INT  nArgument;
	INT  nArguments;
	CString  szItem;
	CDatabaseTCProcedureArgument  *pArgument;
	CDatabaseTCProcedureArguments  pArguments;

	for (nArgument = 0, nArguments = m_cItem.GetArguments(pArguments); nArgument < nArguments; nArgument++)
	{
		if ((pArgument = pArguments.GetAt(nArgument)) != (CDatabaseTCProcedureArgument *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORDETAILSDIALOG_TITLEITEM_NAME); )
				{
					szItem = pArgument->GetTag();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORDETAILSDIALOG_TITLEITEM_DESCRIPTION); )
				{
					szItem = pArgument->GetDescription();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORDETAILSDIALOG_TITLEITEM_VALUE); )
				{
					szItem = pArgument->GetConstValueAsText();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_ARGUMENTS), nArgument, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_ARGUMENTS), nArgument, nColumn, szItem);
			}
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_ARGUMENTS), 0);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_ARGUMENTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ITEM_ARGUMENTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_ARGUMENTS)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ITEM_ARGUMENTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ITEM_ARGUMENTS, LVM_GETITEMCOUNT) == nArguments) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorDetailsDialog::ShowProcedureState()
{
	AccessControl(IDC_TCPROCEDURESMONITOR_ITEM_RUNNINGSTATE_NOTRUNNING, FALSE);
	AccessControl(IDC_TCPROCEDURESMONITOR_ITEM_RUNNINGSTATE_RUNNING, FALSE);
	AccessControl(IDC_TCPROCEDURESMONITOR_ITEM_RUNNINGSTATE_STOPPED, FALSE);
	AccessControl(IDC_TCPROCEDURESMONITOR_ITEM_EXECUTIONMODE_AUTOMATIC, FALSE);
	AccessControl(IDC_TCPROCEDURESMONITOR_ITEM_EXECUTIONMODE_SINGLESTEP, FALSE);
	AccessControl(IDC_TCPROCEDURESMONITOR_ITEM_EXECUTIONMODE_EXTERNALACTIONS, FALSE);
	AccessControl(IDC_TCPROCEDURESMONITOR_ITEM_EXECUTIONMODE_COMMANDS, FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_ITEM_RUNNINGSTATE_NOTRUNNING, (m_cItem.GetRunningState() == TCPROCEDURESMONITORITEM_RUNNINGSTATE_NOTRUNNING) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_ITEM_RUNNINGSTATE_RUNNING, (m_cItem.GetRunningState() == TCPROCEDURESMONITORITEM_RUNNINGSTATE_RUNNING) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_ITEM_RUNNINGSTATE_STOPPED, (m_cItem.GetRunningState() == TCPROCEDURESMONITORITEM_RUNNINGSTATE_STOPPED) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_ITEM_EXECUTIONMODE_AUTOMATIC, (m_cItem.GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_AUTOMATIC) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_ITEM_EXECUTIONMODE_SINGLESTEP, (m_cItem.GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_SINGLESTEP) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_ITEM_EXECUTIONMODE_EXTERNALACTIONS, (m_cItem.GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_EXTERNALACTIONS) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCPROCEDURESMONITOR_ITEM_EXECUTIONMODE_COMMANDS, (m_cItem.GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_COMMANDS) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_NAME)->SetWindowText(m_cItem.GetName());
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_DESCRIPTION)->SetWindowText(m_cItem.GetDescription());
}

BOOL CTCProceduresMonitorDetailsDialog::ShowProcedureAlert()
{
	UINT  nAlertType;
	CString  szAlertMessage;

	if (GetParentDisplay()->GetProcedureInfo(GetParentDisplay()->GetCurProcedure(), &m_cItem) && !m_cItem.GetName().IsEmpty())
	{
		for (GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_ACKNOWLEDGEREQUEST_STATIC)->EnableWindow(), GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_ACKNOWLEDGEREQUEST)->EnableWindow(); m_cItem.GetAlertMessage(nAlertType, szAlertMessage) && nAlertType != TCPROCEDURESMONITORITEM_ALERTTYPE_AUTHORIZATION; )
		{
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_ACKNOWLEDGEREQUEST)->SetWindowText(szAlertMessage);
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_ACKNOWLEDGE)->EnableWindow();
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_ACKNOWLEDGE)->SetFocus();
			return TRUE;
		}
	}
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_ACKNOWLEDGEREQUEST)->SetWindowText(m_szAlert);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_ACKNOWLEDGE)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->SetFocus();
	return TRUE;
}

void CTCProceduresMonitorDetailsDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProceduresMonitorDetailsDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCProceduresMonitorDetailsDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorDetailsDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCProceduresMonitorDetailsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_ITEM_ACKNOWLEDGE, OnAcknowledge)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_ITEM_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorDetailsDialog message handlers

BOOL CTCProceduresMonitorDetailsDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_ARGUMENTS)->GetClientRect(rColumns);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_ACKNOWLEDGEREQUEST)->GetWindowText(m_szAlert);
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORDETAILSDIALOG_TITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORDETAILSDIALOG_TITLEITEM_DESCRIPTION));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORDETAILSDIALOG_TITLEITEM_VALUE));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_ITEM_ARGUMENTS, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_ARGUMENTS), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORDETAILSDIALOG_TITLEITEM_NAME)) ? (rColumns.Width() / 5) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORDETAILSDIALOG_TITLEITEM_DESCRIPTION)) ? ((11 * rColumns.Width()) / 20) : (rColumns.Width() / 4)));
		continue;
	}
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_NAME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_RUNNINGSTATE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_RUNNINGSTATE_NOTRUNNING)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_RUNNINGSTATE_RUNNING)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_RUNNINGSTATE_STOPPED)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_EXECUTIONMODE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_EXECUTIONMODE_AUTOMATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_EXECUTIONMODE_SINGLESTEP)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_EXECUTIONMODE_EXTERNALACTIONS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ITEM_EXECUTIONMODE_COMMANDS)->EnableWindow();
	EnumProcedureArguments();
	ShowProcedureAlert();
	ShowProcedureState();
	return FALSE;
}

void CTCProceduresMonitorDetailsDialog::OnAcknowledge()
{
	CHourglassCursor  cCursor;

	if (GetParentDisplay()->AcknowledgeProcedure(GetParentDisplay()->GetCurProcedure()))
	{
		ShowProcedureAlert();
		return;
	}
}

void CTCProceduresMonitorDetailsDialog::OnOK()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnOK();
}

BOOL CTCProceduresMonitorDetailsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORDETAILSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCProceduresMonitorDetailsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORDETAILSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorAcknowledgmentsDialog dialog

IMPLEMENT_DYNCREATE(CTCProceduresMonitorAcknowledgmentsDialog, CDisplayDialog)

CTCProceduresMonitorAcknowledgmentsDialog::CTCProceduresMonitorAcknowledgmentsDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCProceduresMonitorAcknowledgmentsDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCProceduresMonitorAcknowledgmentsDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CTCProceduresMonitorAcknowledgmentsDialog::IDD);
}

CTCProceduresMonitorWnd *CTCProceduresMonitorAcknowledgmentsDialog::GetParentDisplay() CONST
{
	return((CTCProceduresMonitorWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CTCProceduresMonitorAcknowledgmentsDialog::ShowProcedureAlert()
{
	UINT  nAlertType;
	CString  szAlertMessage;

	if (GetParentDisplay()->GetProcedureInfo(GetParentDisplay()->GetCurProcedure(), &m_cItem) && m_cItem.GetID() < 0)
	{
		for (GetDlgItem(IDC_TCPROCEDURESMONITOR_ACKNOWLEDGMENTS_REQUEST_STATIC)->EnableWindow(), GetDlgItem(IDC_TCPROCEDURESMONITOR_ACKNOWLEDGMENTS_REQUEST)->EnableWindow(); m_cItem.GetAlertMessage(nAlertType, szAlertMessage) && nAlertType != TCPROCEDURESMONITORITEM_ALERTTYPE_AUTHORIZATION; )
		{
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ACKNOWLEDGMENTS_REQUEST)->SetWindowText(szAlertMessage);
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ACKNOWLEDGMENTS_CONFIRM)->EnableWindow();
			GetDlgItem(IDC_TCPROCEDURESMONITOR_ACKNOWLEDGMENTS_CONFIRM)->SetFocus();
			return TRUE;
		}
	}
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ACKNOWLEDGMENTS_REQUEST)->SetWindowText(m_szAlert);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ACKNOWLEDGMENTS_CONFIRM)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->SetFocus();
	return TRUE;
}

void CTCProceduresMonitorAcknowledgmentsDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProceduresMonitorAcknowledgmentsDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorAcknowledgmentsDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCProceduresMonitorAcknowledgmentsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_ACKNOWLEDGMENTS_CONFIRM, OnAcknowledge)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_ACKNOWLEDGMENTS_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorAcknowledgmentsDialog message handlers

BOOL CTCProceduresMonitorAcknowledgmentsDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ACKNOWLEDGMENTS_REQUEST)->GetWindowText(m_szAlert);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_ACKNOWLEDGMENTS_DETAILS)->EnableWindow();
	ShowProcedureAlert();
	return FALSE;
}

void CTCProceduresMonitorAcknowledgmentsDialog::OnAcknowledge()
{
	CHourglassCursor  cCursor;

	if (GetParentDisplay()->AcknowledgeProcedure(GetParentDisplay()->GetCurProcedure()))
	{
		ShowProcedureAlert();
		return;
	}
}

void CTCProceduresMonitorAcknowledgmentsDialog::OnOK()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnOK();
}

BOOL CTCProceduresMonitorAcknowledgmentsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORACKNOWLEDGMENTSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCProceduresMonitorAcknowledgmentsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORACKNOWLEDGMENTSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorAuthorizationsDialog dialog

IMPLEMENT_DYNCREATE(CTCProceduresMonitorAuthorizationsDialog, CDisplayDialog)

CTCProceduresMonitorAuthorizationsDialog::CTCProceduresMonitorAuthorizationsDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCProceduresMonitorAuthorizationsDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCProceduresMonitorAuthorizationsDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CTCProceduresMonitorAuthorizationsDialog::IDD);
}

VOID CTCProceduresMonitorAuthorizationsDialog::ShowTelecommandSource()
{
	CTCItem  *pTCItem;
	CString  szProcedure;
	CDatabaseTCProcedure  *pProcedure;

	if ((pTCItem = (CTCItem *)m_pListedTCItems.GetAt(Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS)))))
	{
		for (GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_GRANT)->EnableWindow((pTCItem->GetAuthorizationStatus() != TCITEM_AUTHORIZATIONSTATUS_GRANTED) ? TRUE : FALSE), GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_DENY)->EnableWindow((pTCItem->GetAuthorizationStatus() != TCITEM_AUTHORIZATIONSTATUS_DENIED) ? TRUE : FALSE); (pProcedure = GetDatabase()->GetTCProcedures()->GetAt(GetDatabase()->GetTCProcedures()->Find(pTCItem->GetVerificationProcedure()))); )
		{
			szProcedure.Format(STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_SOURCE_NAMEFORMAT), (LPCTSTR)pProcedure->GetDescription(), (LPCTSTR)pProcedure->GetName());
			GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE_PROCEDURE)->SetWindowText(szProcedure);
			GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE_THREAD)->SetWindowText(pTCItem->GetVerificationThread());
			GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE_STEP)->SetWindowText(pTCItem->GetVerificationStep());
			return;
		}
	}
	else
	{
		GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_GRANT)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_DENY)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE_PROCEDURE)->SetWindowText(m_szSource[0]);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE_THREAD)->SetWindowText(m_szSource[1]);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE_STEP)->SetWindowText(m_szSource[2]);
}

BOOL CTCProceduresMonitorAuthorizationsDialog::ShowTelecommandAlerts()
{
	INT  nItem;
	INT  nItems;
	INT  nCount;
	INT  nDigits;
	INT  nColumn;
	INT  nColumns;
	INT  nArgument[2];
	INT  nArguments[2];
	INT  nArgumentsCount;
	UINT  nAlertType;
	UINT  nExecutionOBRT;
	BOOL  bAfterDispatch;
	DWORD  dwReleaseOffset;
	CString  szItem;
	CString  szArgument;
	CString  szReleaseTime;
	CString  szExecutionTime;
	CString  szAlertMessage;
	CTCItem  *pTCItem;
	CTCItems  pTCItems;
	CTimeTag  tReleaseTime;
	CTimeTag  tExecutionTime;
	CTimeSpan  tReleaseInterval;
	CUIntArray  nTelecommandIDs;
	CStringTools  cStringTools;
	CDatabaseTCPacket  cPacket;
	CDatabaseTCParameter  *pParameter;
	CDatabaseTCParameters  pParameters;
	CDatabaseTCPacketParameter  *pPacketParameter;
	CDatabaseTCFunctionElement  *pFunctionElement;

	for (nItem = 0, nItems = (GetParentDisplay()->EnumAuthorizableTelecommands((m_nItemIndex = GetParentDisplay()->GetCurProcedure()), pTCItems) && GetParentDisplay()->GetProcedureInfo(m_nItemIndex, &m_cItem) && m_cItem.GetAlertMessage(nAlertType, szAlertMessage) && nAlertType == TCPROCEDURESMONITORITEM_ALERTTYPE_AUTHORIZATION) ? pTCItems.Collect(0, m_pTCItems) : -1, nCount = 0; nItem < nItems; nItem++)
	{
		if ((pTCItem = m_pTCItems.GetAt(nItem)))
		{
			if (pTCItem->GetFlags() & TCITEM_CHECKFLAG_AUTHORIZEABLE)
			{
				for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nDigits = max(cStringTools.ConvertIntToString(nItems).GetLength(), 3); nColumn < nColumns; nColumn++)
				{
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_NUMBER); )
					{
						szItem = cStringTools.ConvertIntToPaddedString((pTCItem->GetMembershipID() != (UINT)-1) ? (pTCItem->GetMembershipID() + 1) : (nItem + 1), nDigits);
						break;
					}
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_NAME); )
					{
						szItem.Format(STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_LIST_NAMEFORMAT), (LPCTSTR)pTCItem->GetName(), (LPCTSTR)pTCItem->GetMembership());
						szItem = (pTCItem->GetMembership().IsEmpty()) ? pTCItem->GetName() : szItem;
						break;
					}
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_DESCRIPTION); )
					{
						szItem = pTCItem->GetDescription();
						break;
					}
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_ARGUMENTS); )
					{
						for (nArgument[1] = 0, nArguments[1] = (((pTCItem->GetFlags() & TCITEM_LINKAGEFLAG_BLOCKED) != TCITEM_LINKAGEFLAG_BLOCKED || !pTCItem->GetReleaseBlockID()) && pTCItem->GetTCPacket(&cPacket)) ? (INT)cPacket.GetSize() : 0, szItem.Empty(), nArgumentsCount = 0; nArgument[1] < nArguments[1]; nArgument[1]++)
						{
							if ((pPacketParameter = cPacket.GetAt(nArgument[1])) && (pPacketParameter->GetAttributes() & TCPARAMETER_VTYPE_AUTO) != TCPARAMETER_VTYPE_AUTO && (pPacketParameter->GetAttributes() & TCPARAMETER_TYPE_VARIABLE))
							{
								szArgument.Format(STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_LIST_ARGUMENTSFORMAT), (LPCTSTR)pPacketParameter->GetTag(), (LPCTSTR)pPacketParameter->GetConstValueAsText());
								szItem += (nArgumentsCount > 0) ? (STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_LIST_ARGUMENTSSEPARATOR) + szArgument) : szArgument;
								nArgumentsCount++;
							}
						}
						for (nArgument[0] = 0, nArguments[0] = (INT)pTCItem->GetSize(); nArgument[0] < nArguments[0]; nArgument[0]++)
						{
							if ((pFunctionElement = pTCItem->GetAt(nArgument[0])) && (pFunctionElement->GetAttributes() & TCPARAMETER_VTYPE_AUTO) != TCPARAMETER_VTYPE_AUTO && (pFunctionElement->GetAttributes() & TCPARAMETER_TYPE_VARIABLE))
							{
								for (szArgument.Format(STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_LIST_ARGUMENTSFORMAT), (LPCTSTR)pFunctionElement->GetName(), (LPCTSTR)pFunctionElement->GetConstValueAsText()); (pParameter = ((pFunctionElement->GetAttributes() & (TCPARAMETER_VTYPE_SEQUENCE | TCPARAMETER_VTYPE_FORMAL)) && pTCItem->GetMembershipParameters(pParameters) > 0) ? pParameters.GetAt(pParameters.Find(pFunctionElement->GetConstValueSource())) : (CDatabaseTCParameter *)NULL); )
								{
									szArgument.Format(STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_LIST_ARGUMENTSFORMAT), (LPCTSTR)pFunctionElement->GetName(), (LPCTSTR)pParameter->GetConstValueAsText());
									break;
								}
								szItem += (nArgumentsCount > 0) ? (STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_LIST_ARGUMENTSSEPARATOR) + szArgument) : szArgument;
								nArgumentsCount++;
							}
						}
						szItem += (!nArgumentsCount  &&  nArguments[0] + nArguments[1] == 0) ? STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_LIST_NOARGUMENTS) : EMPTYSTRING;
						break;
					}
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_FLAGS); )
					{
						szItem = (pTCItem->GetFlags() & TCITEM_LINKAGEFLAG_GROUPED) ? STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_LIST_FLAGS_GROUPED) : EMPTYSTRING;
						szItem += (pTCItem->GetFlags() & TCITEM_LINKAGEFLAG_BLOCKED) ? ((!szItem.IsEmpty()) ? (CString(STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_LIST_FLAGS_SEPARATOR)) + CString(STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_LIST_FLAGS_BLOCKED))) : CString(STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_LIST_FLAGS_BLOCKED))) : EMPTYSTRING;
						break;
					}
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_RELEASETIME); )
					{
						for (szReleaseTime.Empty(); (tReleaseTime = pTCItem->GetReleaseTime().GetTime()) > 0; )
						{
							szReleaseTime = tReleaseTime.FormatGmt(STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_LIST_RELEASETIME_FORMAT));
							break;
						}
						szItem = (szReleaseTime = (tReleaseTime.GetTime() == 0) ? ((pTCItem->GetReleaseTimeWindow(dwReleaseOffset, tReleaseInterval, bAfterDispatch)) ? CTimeTag(1000000 * (TIMETAG)(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY)) + 1000 * (TIMETAG)dwReleaseOffset).FormatGmt(STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_LIST_RELEASETIMEOFFSET_FORMAT)) : STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_LIST_RELEASETIME_IMMEDIATE)) : szReleaseTime);
						break;
					}
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_EXECUTIONTIME); )
					{
						szExecutionTime = (pTCItem->GetExecutionTime(tExecutionTime)) ? tExecutionTime.FormatGmt(STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_LIST_EXECUTIONTIME_FORMAT)) : EMPTYSTRING;
						szExecutionTime = (pTCItem->GetExecutionOBRT(nExecutionOBRT)) ? (cStringTools.ConvertUIntToPaddedString(nExecutionOBRT, 2 * sizeof(nExecutionOBRT), 16) + STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_LIST_EXECUTIONTIME_OBRTFORMAT)) : szExecutionTime;
						szExecutionTime = (szExecutionTime.IsEmpty()) ? STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_LIST_EXECUTIONTIME_IMMEDIATE) : szExecutionTime;
						szItem = szExecutionTime;
						break;
					}
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_STATUS); )
					{
						szItem = (pTCItem->GetAuthorizationStatus() == TCITEM_AUTHORIZATIONSTATUS_NONE) ? STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_LIST_AUTHORIZATIONSTATUS_REQUIRED) : EMPTYSTRING;
						szItem = (pTCItem->GetAuthorizationStatus() == TCITEM_AUTHORIZATIONSTATUS_GRANTED) ? STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_LIST_AUTHORIZATIONSTATUS_GRANTED) : szItem;
						szItem = (pTCItem->GetAuthorizationStatus() == TCITEM_AUTHORIZATIONSTATUS_DENIED) ? STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_LIST_AUTHORIZATIONSTATUS_DENIED) : szItem;
						break;
					}
					if (!nColumn  &&  nItem >= SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS, LVM_GETITEMCOUNT))
					{
						Listview_InsertText(GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS), nCount, szItem);
						continue;
					}
					Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS), nCount, nColumn, szItem);
				}
				if (!nCount)
				{
					GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TIME)->SetWindowText(pTCItem->GetLoadTime().FormatGmt());
					GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TIME_STATIC)->EnableWindow();
					GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TIME_STATIC)->ShowWindow(SW_SHOW);
					GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TIME)->EnableWindow();
					GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TIME)->ShowWindow(SW_SHOW);
				}
				m_pListedTCItems.InsertAt(m_pListedTCItems.GetSize(), pTCItem, 1);
				nCount++;
			}
		}
	}
	if (nItems >= 0)
	{
		while (nCount < SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS, LVM_GETITEMCOUNT))
		{
			Listview_DeleteText(GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS), nCount);
			continue;
		}
		if (!nCount)
		{
			GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TIME)->SetWindowText(EMPTYSTRING);
			GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TIME_STATIC)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TIME_STATIC)->EnableWindow(FALSE);
			GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TIME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TIME)->EnableWindow(FALSE);
		}
		GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_MESSAGE)->SetWindowText(szAlertMessage);
		Listview_SetCurText(GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS), 0);
		ShowTelecommandSource();
		return TRUE;
	}
	return FALSE;
}

CTCProceduresMonitorWnd *CTCProceduresMonitorAuthorizationsDialog::GetParentDisplay() CONST
{
	return((CTCProceduresMonitorWnd *)CDisplayDialog::GetParentDisplay());
}

INT CTCProceduresMonitorAuthorizationsDialog::FindColumnIndex(LPCTSTR pszColumn) CONST
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == pszColumn) break;
		continue;
	}
	return((nColumn < nColumns) ? nColumn : -1);
}

BOOL CTCProceduresMonitorAuthorizationsDialog::Check(BOOL bModified) CONST
{
	INT  nItem;
	INT  nItems;
	CTCItem  *pTCItem[2];

	for (nItem = 0, nItems = (INT)(m_pListedTCItems.GetSize() - 1); nItem < nItems; nItem++)
	{
		if ((pTCItem[1] = ((pTCItem[0] = (CTCItem *)m_pListedTCItems.GetAt(nItem))) ? (CTCItem *)m_pListedTCItems.GetAt(nItem + 1) : (CTCItem *)NULL) && pTCItem[0]->GetAuthorizationStatus() != TCITEM_AUTHORIZATIONSTATUS_NONE  &&  pTCItem[0]->GetAuthorizationStatus() == pTCItem[1]->GetAuthorizationStatus()) continue;
		break;
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

void CTCProceduresMonitorAuthorizationsDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProceduresMonitorAuthorizationsDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCProceduresMonitorAuthorizationsDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pTCItems.RemoveAll();
	m_pListedTCItems.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorAuthorizationsDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCProceduresMonitorAuthorizationsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_GRANT, OnGrantAuthorization)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_DENY, OnDenyAuthorization)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorAuthorizationsDialog message handlers

BOOL CTCProceduresMonitorAuthorizationsDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_NUMBER));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_DESCRIPTION));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_ARGUMENTS));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_FLAGS));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_RELEASETIME));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_EXECUTIONTIME));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_STATUS));
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS)->GetClientRect(rColumns);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE_PROCEDURE)->GetWindowText(m_szSource[0]);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE_THREAD)->GetWindowText(m_szSource[1]);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE_STEP)->GetWindowText(m_szSource[2]);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_NUMBER)) ? rColumns.Width() / 16 : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_NAME)) ? (rColumns.Width() / 4) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_DESCRIPTION) || m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_ARGUMENTS)) ? (rColumns.Width() / 2) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_FLAGS)) ? (rColumns.Width() / 10) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_RELEASETIME) || m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_EXECUTIONTIME)) ? (rColumns.Width() / 4) : rColumns.Width() / 3)))));
		continue;
	}
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_MESSAGE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_MESSAGE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE_PROCEDURE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE_PROCEDURE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE_THREAD_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE_THREAD)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE_STEP_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE_STEP)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_GRANT)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_DENY)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_GRANT)->SetFocus();
	ShowTelecommandAlerts();
	return FALSE;
}

BOOL CTCProceduresMonitorAuthorizationsDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED)) ShowTelecommandSource();
	}
	return CDisplayDialog::OnNotify(wParam, lParam, pResult);
}

void CTCProceduresMonitorAuthorizationsDialog::OnGrantAuthorization()
{
	INT  nItem;
	INT  nItems;
	CTCItem  *pTCItem;
	CHourglassCursor  cCursor;

	for (nItem = 0, nItems = (INT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS, LVM_GETITEMCOUNT); nItem < nItems; nItem++)
	{
		if ((pTCItem = (Listview_IsSelText(GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS), nItem)) ? (CTCItem *)m_pListedTCItems.GetAt(nItem) : (CTCItem *)NULL))
		{
			Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS), nItem, FindColumnIndex(STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_STATUS)), STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_LIST_AUTHORIZATIONSTATUS_GRANTED));
			pTCItem->SetAuthorizationStatus(TCITEM_AUTHORIZATIONSTATUS_GRANTED);
			continue;
		}
	}
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_GRANT)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_DENY)->EnableWindow(TRUE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorAuthorizationsDialog::OnDenyAuthorization()
{
	INT  nItem;
	INT  nItems;
	CTCItem  *pTCItem;
	CHourglassCursor  cCursor;

	for (nItem = 0, nItems = (INT)SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS, LVM_GETITEMCOUNT); nItem < nItems; nItem++)
	{
		if ((pTCItem = (Listview_IsSelText(GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS), nItem)) ? (CTCItem *)m_pListedTCItems.GetAt(nItem) : (CTCItem *)NULL))
		{
			Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS), nItem, FindColumnIndex(STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TITLEITEM_STATUS)), STRING(IDS_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_LIST_AUTHORIZATIONSTATUS_DENIED));
			pTCItem->SetAuthorizationStatus(TCITEM_AUTHORIZATIONSTATUS_DENIED);
			continue;
		}
	}
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_GRANT)->EnableWindow(TRUE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_DENY)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorAuthorizationsDialog::OnOK()
{
	INT  nItem[2];
	INT  nItems[2];
	CTCItem  *pTCItem[2];
	CHourglassCursor  cCursor;

	for (nItem[0] = 0, nItems[0] = (INT)m_pTCItems.GetSize(); nItem[0] < nItems[0]; nItem[0]++)
	{
		if ((pTCItem[0] = m_pTCItems.GetAt(nItem[0])) && (pTCItem[0]->GetAuthorizationStatus() == TCITEM_AUTHORIZATIONSTATUS_GRANTED || pTCItem[0]->GetAuthorizationStatus() == TCITEM_AUTHORIZATIONSTATUS_DENIED))
		{
			for (nItem[1] = 0, nItems[1] = nItems[0]; nItem[1] < nItems[1]; nItem[1]++)
			{
				if ((pTCItem[1] = m_pTCItems.GetAt(nItem[1])))
				{
					pTCItem[1]->SetAuthorizationStatus(pTCItem[0]->GetAuthorizationStatus());
					continue;
				}
			}
			break;
		}
	}
	GetParentDisplay()->AuthorizeTelecommands(m_nItemIndex, m_pTCItems);
	CDisplayDialog::OnOK();
}

BOOL CTCProceduresMonitorAuthorizationsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCProceduresMonitorAuthorizationsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORAUTHORIZATIONSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorInterlocksDialog dialog

IMPLEMENT_DYNCREATE(CTCProceduresMonitorInterlocksDialog, CDisplayDialog)

CTCProceduresMonitorInterlocksDialog::CTCProceduresMonitorInterlocksDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCProceduresMonitorInterlocksDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCProceduresMonitorInterlocksDialog::Create(CWnd *pParentWnd, CTCInterlocks &pInterlocks)
{
	INT  nResult;
	INT  nInterlock;
	INT  nInterlocks;
	CTCInterlock  *pInterlock[2];

	for (pInterlocks.RemoveAll(); (nResult = CDisplayDialog::Create(pParentWnd, CTCProceduresMonitorInterlocksDialog::IDD)) == IDOK; )
	{
		for (nInterlock = 0, nInterlocks = (INT)m_pInterlocks[0].GetSize(); nInterlock < nInterlocks; nInterlock = nInterlock + 1)
		{
			if ((pInterlock[1] = ((pInterlock[0] = m_pInterlocks[0].GetAt(nInterlock)) && pInterlock[0]->GetState() == TCINTERLOCK_STATE_IDLE) ? m_pInterlocks[1].GetAt(m_pInterlocks[1].Find(TCINTERLOCK_SOURCETYPE_PROCEDURESMONITOR, pInterlock[0]->GetName())) : (CTCInterlock *)NULL) && pInterlock[0]->GetState() != pInterlock[1]->GetState())
			{
				pInterlocks.InsertAt(pInterlocks.GetSize(), pInterlock[0], 1);
				m_pInterlocks[0].CPtrArray::RemoveAt(nInterlock);
				nInterlocks--;
				nInterlock--;
			}
		}
		break;
	}
	return nResult;
}

BOOL CTCProceduresMonitorInterlocksDialog::Initialize()
{
	return((GetTCService()->GetTCInterlocks(TCINTERLOCK_SOURCETYPE_PROCEDURESMONITOR, m_pInterlocks[0])) ? m_pInterlocks[1].Copy(&m_pInterlocks[0]) : FALSE);
}

BOOL CTCProceduresMonitorInterlocksDialog::EnumInterlocks()
{
	INT  nColumn;
	INT  nColumns;
	INT  nInterlock;
	INT  nInterlocks;
	CString  szItem;
	CString  szScope[2];
	CTCInterlock  *pInterlock;

	for (nInterlock = 0, nInterlocks = (INT)m_pInterlocks[0].GetSize(); nInterlock < nInterlocks; nInterlock++)
	{
		if ((pInterlock = m_pInterlocks[0].GetAt(nInterlock)) && pInterlock->GetState() != TCINTERLOCK_STATE_IDLE)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn = nColumn + 1)
			{
				for (szItem.Empty(); m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_TITLEITEM_NAME); )
				{
					szItem = pInterlock->GetName();
					break;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_TITLEITEM_TYPE))
				{
					szItem = (pInterlock->GetSourceType() == TCINTERLOCK_SOURCETYPE_MANUALSTACK) ? STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_MANUALSTACKTYPE) : EMPTYSTRING;
					szItem = (pInterlock->GetSourceType() == TCINTERLOCK_SOURCETYPE_AUTOMATICSTACK) ? STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_AUTOMATICSTACKTYPE) : szItem;
					szItem = (pInterlock->GetSourceType() == TCINTERLOCK_SOURCETYPE_PROCEDURESMONITOR) ? STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_PROCEDURESMONITORTYPE) : szItem;
					szItem = (pInterlock->GetSourceType() == TCINTERLOCK_SOURCETYPE_ALLSOURCES) ? STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_ALLSOURCESTYPE) : szItem;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_TITLEITEM_SCOPE))
				{
					szScope[0].Format(STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_SUBSYSTEMSCOPE), (LPCTSTR)GetTCService()->TranslateIDToTCSubSystem(TCINTERLOCKAPIDFROMCODE(pInterlock->GetScope())));
					szScope[1].Format(STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_SUBSYSTEMNOWAITSCOPE), (LPCTSTR)GetTCService()->TranslateIDToTCSubSystem(TCINTERLOCKAPIDFROMCODE(pInterlock->GetScope())));
					szItem = (TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) == TCINTERLOCK_SCOPE_GLOBAL) ? STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_GLOBALSCOPE) : EMPTYSTRING;
					szItem = (TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) == TCINTERLOCK_SCOPE_LOCAL) ? STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_LOCALSCOPE) : szItem;
					szItem = (TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) == TCINTERLOCK_SCOPE_LOCALNOWAIT) ? STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_LOCALNOWAITSCOPE) : szItem;
					szItem = (TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) == TCINTERLOCK_SCOPE_LOCALSUBSYSTEM) ? szScope[0] : szItem;
					szItem = (TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) == TCINTERLOCK_SCOPE_LOCALSUBSYSTEMNOWAIT) ? szScope[1] : szItem;
					szItem = (TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) == TCINTERLOCK_SCOPE_COMMANDS) ? STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_COMMANDSSCOPE) : szItem;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_TITLEITEM_STAGE))
				{
					szItem = (pInterlock->GetStage() == TCINTERLOCK_STAGE_RECEPTION) ? STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_RECEPTIONSTAGE) : EMPTYSTRING;
					szItem = (pInterlock->GetStage() == TCINTERLOCK_STAGE_TRANSMISSION) ? STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_TRANSMISSIONSTAGE) : szItem;
					szItem = (pInterlock->GetStage() == TCINTERLOCK_STAGE_ACCEPTANCE) ? STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_ACCEPTANCESTAGE) : szItem;
					szItem = (pInterlock->GetStage() == TCINTERLOCK_STAGE_START) ? STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_STARTSTAGE) : szItem;
					szItem = (pInterlock->GetStage() == TCINTERLOCK_STAGE_PROGRESS) ? STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_PROGRESSSTAGE) : szItem;
					szItem = (pInterlock->GetStage() == TCINTERLOCK_STAGE_COMPLETION) ? STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_COMPLETIONSTAGE) : szItem;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_TITLEITEM_STATE))
				{
					szItem = (pInterlock->GetState() == TCINTERLOCK_STATE_IDLE) ? STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_IDLESTATE) : EMPTYSTRING;
					szItem = (pInterlock->GetState() == TCINTERLOCK_STATE_PENDING) ? STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_PENDINGSTATE) : szItem;
					szItem = (pInterlock->GetState() == TCINTERLOCK_STATE_SUCCESS) ? STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_SUCCESSSTATE) : szItem;
					szItem = (pInterlock->GetState() == TCINTERLOCK_STATE_FAILURE) ? STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_FAILURESTATE) : szItem;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TCPROCEDURESMONITOR_INTERLOCKS_LIST), nInterlock, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_INTERLOCKS_LIST), nInterlock, nColumn, szItem);
			}
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_TCPROCEDURESMONITOR_INTERLOCKS_LIST), 0);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_INTERLOCKS_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_INTERLOCKS_LIST)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_INTERLOCKS_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_INTERLOCKS_RESET)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITOR_INTERLOCKS_LIST)) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_INTERLOCKS_RESETALL)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_INTERLOCKS_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_INTERLOCKS_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

INT CTCProceduresMonitorInterlocksDialog::FindColumnIndex(LPCTSTR pszColumn) CONST
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == pszColumn) break;
		continue;
	}
	return((nColumn < nColumns) ? nColumn : -1);
}

BOOL CTCProceduresMonitorInterlocksDialog::IsModified() CONST
{
	return !m_pInterlocks[0].Compare(&m_pInterlocks[1]);
}

void CTCProceduresMonitorInterlocksDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProceduresMonitorInterlocksDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCProceduresMonitorInterlocksDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	return CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorInterlocksDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCProceduresMonitorInterlocksDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_INTERLOCKS_RESET, OnReset)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_INTERLOCKS_RESETALL, OnResetAll)
	ON_BN_CLICKED(IDC_TCPROCEDURESMONITOR_INTERLOCKS_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorInterlocksDialog message handlers

BOOL CTCProceduresMonitorInterlocksDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	GetDlgItem(IDC_TCPROCEDURESMONITOR_INTERLOCKS_LIST)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_TITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_TITLEITEM_TYPE));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_TITLEITEM_SCOPE));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_TITLEITEM_STAGE));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_TITLEITEM_STATE));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_TCPROCEDURESMONITOR_INTERLOCKS_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCPROCEDURESMONITOR_INTERLOCKS_LIST), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_TITLEITEM_NAME) || m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_TITLEITEM_TYPE)) ? (rColumns.Width() / 3) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_TITLEITEM_SCOPE)) ? (rColumns.Width() / 2) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_TITLEITEM_STAGE)) ? (rColumns.Width() / 4) : (rColumns.Width() / 5))));
		continue;
	}
	EnumInterlocks();
	return TRUE;
}

BOOL CTCProceduresMonitorInterlocksDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCPROCEDURESMONITOR_INTERLOCKS_LIST)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED)) GetDlgItem(IDC_TCPROCEDURESMONITOR_INTERLOCKS_RESET)->EnableWindow((Listview_GetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_INTERLOCKS_LIST), pNotifyListView->iItem, FindColumnIndex(STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_TITLEITEM_STATE))) != STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_IDLESTATE)) ? TRUE : FALSE);
	}
	return CDisplayDialog::OnNotify(wParam, lParam, pResult);
}

void CTCProceduresMonitorInterlocksDialog::OnReset()
{
	INT  nIndex;
	INT  nInterlock;
	INT  nInterlocks;
	CTCInterlock  *pInterlock;
	CHourglassCursor  cCursor;

	if ((pInterlock = m_pInterlocks[0].GetAt((nIndex = Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESMONITOR_INTERLOCKS_LIST))))))
	{
		for (nInterlock = 0, nInterlocks = (INT)m_pInterlocks[0].GetSize(), pInterlock->SetState(TCINTERLOCK_STATE_IDLE), Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_INTERLOCKS_LIST), nIndex, FindColumnIndex(STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_TITLEITEM_STATE)), STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_IDLESTATE)); nInterlock < nInterlocks; nInterlock++)
		{
			if ((pInterlock = m_pInterlocks[0].GetAt(nInterlock)) && pInterlock->GetState() != TCINTERLOCK_STATE_IDLE) break;
			continue;
		}
		GetDlgItem(IDC_TCPROCEDURESMONITOR_INTERLOCKS_RESET)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCPROCEDURESMONITOR_INTERLOCKS_RESETALL)->EnableWindow((nInterlock < nInterlocks) ? TRUE : FALSE);
		GetDlgItem(IDC_TCPROCEDURESMONITOR_INTERLOCKS_LIST)->SetFocus();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorInterlocksDialog::OnResetAll()
{
	INT  nInterlock;
	INT  nInterlocks;
	CTCInterlock  *pInterlock;
	CHourglassCursor  cCursor;

	for (nInterlock = 0, nInterlocks = (INT)m_pInterlocks[0].GetSize(); nInterlock < nInterlocks; nInterlock++)
	{
		if ((pInterlock = m_pInterlocks[0].GetAt(nInterlock)) && pInterlock->GetState() != TCINTERLOCK_STATE_IDLE)
		{
			Listview_SetText(GetDlgItem(IDC_TCPROCEDURESMONITOR_INTERLOCKS_LIST), nInterlock, FindColumnIndex(STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_TITLEITEM_STATE)), STRING(IDS_TCPROCEDURESMONITORINTERLOCKSDIALOG_LIST_IDLESTATE));
			pInterlock->SetState(TCINTERLOCK_STATE_IDLE);
		}
	}
	GetDlgItem(IDC_TCPROCEDURESMONITOR_INTERLOCKS_RESET)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_INTERLOCKS_RESETALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESMONITOR_INTERLOCKS_LIST)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProceduresMonitorInterlocksDialog::OnOK()
{
	CHourglassCursor  cCursor;

	GetTCService()->SetTCInterlocks(TCINTERLOCK_SOURCETYPE_PROCEDURESMONITOR, m_pInterlocks[0]);
	CDisplayDialog::OnOK();
}

BOOL CTCProceduresMonitorInterlocksDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORINTERLOCKSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCProceduresMonitorInterlocksDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCPROCEDURESMONITORINTERLOCKSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorToolBar

IMPLEMENT_DYNCREATE(CTCProceduresMonitorToolBar, CDisplayToolBar)

CTCProceduresMonitorToolBar::CTCProceduresMonitorToolBar() : CDisplayToolBar()
{
	return;
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorToolBar, CDisplayToolBar)
	//{{AFX_MSG_MAP(CTCProceduresMonitorToolBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorToolBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorStatusBar

IMPLEMENT_DYNCREATE(CTCProceduresMonitorStatusBar, CDisplayStatusBar)

CTCProceduresMonitorStatusBar::CTCProceduresMonitorStatusBar() : CDisplayStatusBar()
{
	m_bPanesColor = TRUE;
}

BOOL CTCProceduresMonitorStatusBar::SetIndicators(CONST UINT *pPanesID, INT nCount)
{
	INT  nIndex;
	CRect  rPane;
	CString  szPane;
	CToolInfo  cToolInfo;
	CDisplayLock  cLock(this);

	if (CDisplayStatusBar::SetIndicators(pPanesID, nCount))
	{
		if (CommandToIndex(ID_TCPROCEDURESMONITOR_STATUSBAR_MESSAGEPANE) >= 0)
		{
			szPane.Format(STRING(IDS_TCPROCEDURESMONITOR_STATUSBAR_UPDATEMESSAGE), (UINT)-1);
			SetPaneInfo(CommandToIndex(ID_TCPROCEDURESMONITOR_STATUSBAR_MESSAGEPANE), ID_TCPROCEDURESMONITOR_STATUSBAR_MESSAGEPANE, SBPS_NOBORDERS | SBPS_STRETCH, CalcPaneWidth(szPane));
		}
		if (!IsWindow(m_wndToolTip.GetSafeHwnd()))
		{
			m_wndToolTip.Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
			SetClassLongPtr(m_wndToolTip.GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip.GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
		}
		if (IsWindow(m_wndToolTip.GetSafeHwnd()))
		{
			if ((nIndex = CommandToIndex(ID_TCPROCEDURESMONITOR_STATUSBAR_UPLINKPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_TCPROCEDURESMONITOR_STATUSBAR_UPLINKPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_TCPROCEDURESMONITOR_STATUSBAR_UPLINKPANE);
					break;
				}
			}
			if ((nIndex = CommandToIndex(ID_TCPROCEDURESMONITOR_STATUSBAR_PEVPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_TCPROCEDURESMONITOR_STATUSBAR_PEVPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_TCPROCEDURESMONITOR_STATUSBAR_PEVPANE);
					break;
				}
			}
			if ((nIndex = CommandToIndex(ID_TCPROCEDURESMONITOR_STATUSBAR_CEVPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_TCPROCEDURESMONITOR_STATUSBAR_CEVPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_TCPROCEDURESMONITOR_STATUSBAR_CEVPANE);
					break;
				}
			}
			if ((nIndex = CommandToIndex(ID_TCPROCEDURESMONITOR_STATUSBAR_STATEPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_TCPROCEDURESMONITOR_STATUSBAR_STATEPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_TCPROCEDURESMONITOR_STATUSBAR_STATEPANE);
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

CTCProceduresMonitorWnd *CTCProceduresMonitorStatusBar::GetParent() CONST
{
	return((CTCProceduresMonitorWnd *)CDisplayStatusBar::GetParent());
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorStatusBar, CDisplayStatusBar)
	//{{AFX_MSG_MAP(CTCProceduresMonitorStatusBar)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorStatusBar message handlers

void CTCProceduresMonitorStatusBar::OnPaint()
{
	INT  nIndex;
	RECT  rPane;
	CToolInfo  cToolInfo;

	for (CDisplayStatusBar::OnPaint(); IsWindow(m_wndToolTip.GetSafeHwnd()); )
	{
		if ((nIndex = CommandToIndex(ID_TCPROCEDURESMONITOR_STATUSBAR_UPLINKPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_TCPROCEDURESMONITOR_STATUSBAR_UPLINKPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		if ((nIndex = CommandToIndex(ID_TCPROCEDURESMONITOR_STATUSBAR_PEVPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_TCPROCEDURESMONITOR_STATUSBAR_PEVPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		if ((nIndex = CommandToIndex(ID_TCPROCEDURESMONITOR_STATUSBAR_CEVPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_TCPROCEDURESMONITOR_STATUSBAR_CEVPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		if ((nIndex = CommandToIndex(ID_TCPROCEDURESMONITOR_STATUSBAR_STATEPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_TCPROCEDURESMONITOR_STATUSBAR_STATEPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		break;
	}
}

void CTCProceduresMonitorStatusBar::OnMouseMove(UINT nFlags, CPoint point)
{
	MSG  sMsg;

	if (IsWindow(m_wndToolTip.GetSafeHwnd()))
	{
		CopyMemory(&sMsg, GetCurrentMessage(), sizeof(MSG));
		m_wndToolTip.RelayEvent(&sMsg);
	}
	CDisplayStatusBar::OnMouseMove(nFlags, point);
}

BOOL CTCProceduresMonitorStatusBar::OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult)
{
	TOOLTIPTEXT  *pToolTipInfo = (TOOLTIPTEXT *)pNotifyInfo;

	switch (pNotifyInfo->idFrom)
	{
	case ID_TCPROCEDURESMONITOR_STATUSBAR_UPLINKPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_TCPROCEDURESMONITOR_STATUSBAR_UPLINKPANE);
	return TRUE;
	}
	case ID_TCPROCEDURESMONITOR_STATUSBAR_PEVPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_TCPROCEDURESMONITOR_STATUSBAR_PEVPANE);
	return TRUE;
	}
	case ID_TCPROCEDURESMONITOR_STATUSBAR_CEVPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_TCPROCEDURESMONITOR_STATUSBAR_CEVPANE);
	return TRUE;
	}
	case ID_TCPROCEDURESMONITOR_STATUSBAR_STATEPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_TCPROCEDURESMONITOR_STATUSBAR_STATEPANE);
	return TRUE;
	}
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorViewToolTip

IMPLEMENT_DYNCREATE(CTCProceduresMonitorViewToolTip, CDisplayToolTip)

CTCProceduresMonitorViewToolTip::CTCProceduresMonitorViewToolTip() : CDisplayToolTip()
{
	return;
}

BOOL CTCProceduresMonitorViewToolTip::Create(CWnd *pParentWnd, CONST POINT &point, LPCTSTR pszTitle, LPCTSTR pszText, BOOL bAutoDestroy)
{
	if (CDisplayToolTip::Create(pParentWnd, point, pszTitle, pszText))
	{
		if ((bAutoDestroy  &&  SetTimer(TCPROCEDURESMONITORVIEW_TOOLTIP_TIMERID, TCPROCEDURESMONITORVIEW_TOOLTIP_TIMEOUT, NULL)) || !bAutoDestroy) return TRUE;
		DestroyWindow();
	}
	return FALSE;
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorViewToolTip, CDisplayToolTip)
	//{{AFX_MSG_MAP(CTCProceduresMonitorViewToolTip)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorViewToolTip message handlers

void CTCProceduresMonitorViewToolTip::OnTimer(UINT_PTR nEventID)
{
	if (nEventID == TCPROCEDURESMONITORVIEW_TOOLTIP_TIMERID)
	{
		Destroy();
		return;
	}
	CDisplayToolTip::OnTimer(nEventID);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorDocument

IMPLEMENT_DYNAMIC(CTCProceduresMonitorDocument, CDocument)

CTCProceduresMonitorDocument::CTCProceduresMonitorDocument() : CDocument()
{
	return;
}

CTCProceduresMonitorDocument::~CTCProceduresMonitorDocument()
{
	return;
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorTextView

IMPLEMENT_DYNCREATE(CTCProceduresMonitorTextView, CTextView)

CTCProceduresMonitorTextView::CTCProceduresMonitorTextView() : CTextView()
{
	m_sizeAlertSymbols.cx = 0;
	m_sizeAlertSymbols.cy = 0;
	m_sizeCheckFlagSymbols.cx = 0;
	m_sizeCheckFlagSymbols.cy = 0;
	m_hToolTipCursor = (HCURSOR)NULL;
	m_bToolTips = TRUE;
}

BOOL CTCProceduresMonitorTextView::Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle)
{
	if (CTextView::Create(pParentWnd, rect, dwStyle))
	{
		SetTextSpacings(1, 1);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorTextView::SetLayout(CONST CUIntArray &nColumns)
{
	INT  nIndex;
	INT  nCount;
	CUIntArray  nWidths;
	CUIntArray  nTitleItems;
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	for (nTitleItems.Copy(nColumns); !nTitleItems.GetSize(); )
	{
		if (TCPROCEDURESMONITOR_TITLEITEM_NAME & TCPROCEDURESMONITOR_TITLEITEMS_DEFAULT) nTitleItems.Add(TCPROCEDURESMONITOR_TITLEITEM_NAME);
		if (TCPROCEDURESMONITOR_TITLEITEM_DESCRIPTION & TCPROCEDURESMONITOR_TITLEITEMS_DEFAULT) nTitleItems.Add(TCPROCEDURESMONITOR_TITLEITEM_DESCRIPTION);
		if (TCPROCEDURESMONITOR_TITLEITEM_COMMENTS & TCPROCEDURESMONITOR_TITLEITEMS_DEFAULT) nTitleItems.Add(TCPROCEDURESMONITOR_TITLEITEM_COMMENTS);
		if (TCPROCEDURESMONITOR_TITLEITEM_AUTHOR & TCPROCEDURESMONITOR_TITLEITEMS_DEFAULT) nTitleItems.Add(TCPROCEDURESMONITOR_TITLEITEM_AUTHOR);
		if (TCPROCEDURESMONITOR_TITLEITEM_CREATIONTIME & TCPROCEDURESMONITOR_TITLEITEMS_DEFAULT) nTitleItems.Add(TCPROCEDURESMONITOR_TITLEITEM_CREATIONTIME);
		if (TCPROCEDURESMONITOR_TITLEITEM_MODIFICATIONTIME & TCPROCEDURESMONITOR_TITLEITEMS_DEFAULT) nTitleItems.Add(TCPROCEDURESMONITOR_TITLEITEM_MODIFICATIONTIME);
		if (TCPROCEDURESMONITOR_TITLEITEM_VERIFICATIONSTATUS & TCPROCEDURESMONITOR_TITLEITEMS_DEFAULT) nTitleItems.Add(TCPROCEDURESMONITOR_TITLEITEM_VERIFICATIONSTATUS);
		if (TCPROCEDURESMONITOR_TITLEITEM_NUMBEROFTHREADS & TCPROCEDURESMONITOR_TITLEITEMS_DEFAULT) nTitleItems.Add(TCPROCEDURESMONITOR_TITLEITEM_NUMBEROFTHREADS);
		if (TCPROCEDURESMONITOR_TITLEITEM_ARGUMENTS & TCPROCEDURESMONITOR_TITLEITEMS_DEFAULT) nTitleItems.Add(TCPROCEDURESMONITOR_TITLEITEM_ARGUMENTS);
		if (TCPROCEDURESMONITOR_TITLEITEM_TRIGGERTYPE & TCPROCEDURESMONITOR_TITLEITEMS_DEFAULT) nTitleItems.Add(TCPROCEDURESMONITOR_TITLEITEM_TRIGGERTYPE);
		if (TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONMODE & TCPROCEDURESMONITOR_TITLEITEMS_DEFAULT) nTitleItems.Add(TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONMODE);
		if (TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONCOUNT & TCPROCEDURESMONITOR_TITLEITEMS_DEFAULT) nTitleItems.Add(TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONCOUNT);
		if (TCPROCEDURESMONITOR_TITLEITEM_RUNNINGSTATE & TCPROCEDURESMONITOR_TITLEITEMS_DEFAULT) nTitleItems.Add(TCPROCEDURESMONITOR_TITLEITEM_RUNNINGSTATE);
		if (TCPROCEDURESMONITOR_TITLEITEM_ACKNOWLEDGEREQUEST & TCPROCEDURESMONITOR_TITLEITEMS_DEFAULT) nTitleItems.Add(TCPROCEDURESMONITOR_TITLEITEM_ACKNOWLEDGEREQUEST);
		if (TCPROCEDURESMONITOR_TITLEITEM_ACKREQUESTTIME & TCPROCEDURESMONITOR_TITLEITEMS_DEFAULT) nTitleItems.Add(TCPROCEDURESMONITOR_TITLEITEM_ACKREQUESTTIME);
		if (TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS & TCPROCEDURESMONITOR_TITLEITEMS_DEFAULT) nTitleItems.Add(TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS);
		if (TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS & TCPROCEDURESMONITOR_TITLEITEMS_DEFAULT) nTitleItems.Add(TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS);
		if (TCPROCEDURESMONITOR_TITLEITEM_STARTTIME & TCPROCEDURESMONITOR_TITLEITEMS_DEFAULT) nTitleItems.Add(TCPROCEDURESMONITOR_TITLEITEM_STARTTIME);
		if (TCPROCEDURESMONITOR_TITLEITEM_ENDTIME & TCPROCEDURESMONITOR_TITLEITEMS_DEFAULT) nTitleItems.Add(TCPROCEDURESMONITOR_TITLEITEM_ENDTIME);
		break;
	}
	for (nIndex = 0, nCount = (LookupColumnsName(nTitleItems, szColumns) && CalcColumnsWidth(nTitleItems, nWidths) && SetColumns(szColumns, nWidths)) ? (INT)nTitleItems.GetSize() : -1; nIndex < nCount; nIndex++)
	{
		SetColumnColor(nIndex, LookupColumnColor(nTitleItems.GetAt(nIndex)), IsWindow(GetSafeHwnd()));
		continue;
	}
	return((nIndex == nCount) ? TRUE : FALSE);
}
BOOL CTCProceduresMonitorTextView::SetLayout(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths)
{
	INT  nIndex;
	INT  nCount;
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	for (nIndex = 0, nCount = (LookupColumnsName(nColumns, szColumns) && SetColumns(szColumns, nWidths)) ? (INT)nColumns.GetSize() : -1; nIndex < nCount; nIndex++)
	{
		SetColumnColor(nIndex, LookupColumnColor(nColumns.GetAt(nIndex)), IsWindow(GetSafeHwnd()));
		continue;
	}
	return((nIndex == nCount) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorTextView::GetLayout(CUIntArray &nColumns) CONST
{
	CUIntArray  nWidths;

	return GetLayout(nColumns, nWidths);
}
BOOL CTCProceduresMonitorTextView::GetLayout(CUIntArray &nColumns, CUIntArray &nWidths) CONST
{
	INT  nIndex;
	INT  nCount;
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	for (nIndex = 0, nCount = (GetColumns(szColumns, nWidths)) ? (INT)szColumns.GetSize() : -1, nColumns.RemoveAll(); nIndex < nCount; nIndex++)
	{
		nColumns.Add(LookupColumnName(szColumns.GetAt(nIndex)));
		continue;
	}
	return((nIndex == nCount) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorTextView::SetTitleFont(CFont *pFont)
{
	return CTextView::SetTitleFont(pFont);
}
BOOL CTCProceduresMonitorTextView::SetTitleFont(CONST LOGFONT *plfFont)
{
	return CTextView::SetTitleFont(plfFont);
}

BOOL CTCProceduresMonitorTextView::GetTitleFont(CFont *pFont) CONST
{
	return CTextView::GetTitleFont(pFont);
}
BOOL CTCProceduresMonitorTextView::GetTitleFont(LOGFONT *plfFont) CONST
{
	return CTextView::GetTitleFont(plfFont);
}

BOOL CTCProceduresMonitorTextView::SetItemsFont(CFont *pFont)
{
	LOGFONT  lfFont;

	return((pFont->GetLogFont(&lfFont) > 0) ? SetItemsFont(&lfFont) : FALSE);
}
BOOL CTCProceduresMonitorTextView::SetItemsFont(CONST LOGFONT *plfFont)
{
	CTextViewLock  cLock(this);

	if (SetTextFont(plfFont))
	{
		SetTextSpacings(max(LOWORD(GetTextSpacings()), 1), max(HIWORD(GetTextSpacings()), 1));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorTextView::GetItemsFont(CFont *pFont) CONST
{
	return CTextView::GetTextFont(pFont);
}
BOOL CTCProceduresMonitorTextView::GetItemsFont(LOGFONT *plfFont) CONST
{
	return CTextView::GetTextFont(plfFont);
}

BOOL CTCProceduresMonitorTextView::EnableToolTipMode(BOOL bEnable)
{
	m_bToolTips = bEnable;
	return TRUE;
}

BOOL CTCProceduresMonitorTextView::IsToolTipModeEnabled() CONST
{
	return m_bToolTips;
}

BOOL CTCProceduresMonitorTextView::SetText(INT nRow, LPCTSTR pszText, CONST CTextViewAttribute *pAttribute, BOOL bRedraw)
{
	return CTextView::SetText(nRow, pszText, pAttribute, bRedraw);
}
BOOL CTCProceduresMonitorTextView::SetText(INT nRow, INT nColumn, LPCTSTR pszText, BOOL bRedraw)
{
	INT  nIndex;
	INT  nCount;
	INT  nHeight;
	BOOL  bRecalc;
	CTextViewLock  cLock(this);

	for (nIndex = nRow, nCount = (CTextView::SetText(nRow, nColumn, pszText, bRedraw)) ? (INT)GetTextCount() : -1, nHeight = 0, bRecalc = FALSE; nIndex < nCount; nIndex++)
	{
		for (nHeight = (nIndex > 0) ? (m_wndContentCtrl.m_nContentTextPos.GetAt(nIndex - 1) + m_wndContentCtrl.CalcTextLines(m_wndContentCtrl.m_szContentText.GetAt(nIndex), m_wndContentCtrl.m_pContentTextAttributes.GetAt(nIndex))) : m_wndContentCtrl.CalcTextLines(m_wndContentCtrl.m_szContentText.GetAt(nIndex), m_wndContentCtrl.m_pContentTextAttributes.GetAt(nIndex)); nHeight != m_wndContentCtrl.m_nContentTextPos.GetAt(nIndex); )
		{
			m_wndContentCtrl.m_nContentTextPos.SetAt(nIndex, nHeight);
			bRecalc = TRUE;
			break;
		}
		if (nIndex == nCount - 1 && bRecalc)
		{
			RecalcLayout();
			continue;
		}
	}
	return((nIndex == nCount) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorTextView::GetText(INT nRow, INT nColumn, CString &szText) CONST
{
	return CTextView::GetText(nRow, nColumn, szText);
}

BOOL CTCProceduresMonitorTextView::SetCurText(INT nIndex)
{
	CTextViewLock  cLock(this);

	if (nIndex != GetCurText() && CTextView::SetCurText(nIndex))
	{
		GetParent()->UpdateContent(TRUE);
		return TRUE;
	}
	return((nIndex == GetCurText()) ? TRUE : FALSE);
}

INT CTCProceduresMonitorTextView::GetCurText() CONST
{
	return CTextView::GetCurText();
}

BOOL CTCProceduresMonitorTextView::GetPrintProperties(CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST
{
	CTextViewLock  cLock(this);

	pSymbols.RemoveAll();
	nSymbolIDs.RemoveAll();
	nSymbolIDs.Add(IDP_TCPROCEDURESMONITORCHECKSON);
	nSymbolIDs.Add(IDP_TCPROCEDURESMONITORCHECKSOFF);
	nSymbolIDs.Add(IDP_TCPROCEDURESMONITORCHECKSDISABLED);
	nSymbolIDs.Add(IDP_TCPROCEDURESMONITORINFORMATION);
	nSymbolIDs.Add(IDP_TCPROCEDURESMONITORWARNING);
	nSymbolIDs.Add(IDP_TCPROCEDURESMONITORERROR);
	nSymbolIDs.Add(IDP_TCPROCEDURESMONITORALERT);
	nSymbolIDs.Add(IDP_TCPROCEDURESMONITORAUTHORIZATION);
	pSymbols.Add(m_pCheckFlagSymbols[TCPROCEDURESMONITORTEXTVIEW_COMMANDCHECKFLAGSYMBOL_ON]);
	pSymbols.Add(m_pCheckFlagSymbols[TCPROCEDURESMONITORTEXTVIEW_COMMANDCHECKFLAGSYMBOL_OFF]);
	pSymbols.Add(m_pCheckFlagSymbols[TCPROCEDURESMONITORTEXTVIEW_COMMANDCHECKFLAGSYMBOL_DISABLED]);
	pSymbols.Add(m_pAlertSymbols[TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOL_INFORMATION]);
	pSymbols.Add(m_pAlertSymbols[TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOL_WARNING]);
	pSymbols.Add(m_pAlertSymbols[TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOL_ERROR]);
	pSymbols.Add(m_pAlertSymbols[TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOL_ALERT]);
	pSymbols.Add(m_pAlertSymbols[TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOL_AUTHORIZATION]);
	return(GetColumns(szColumns) && GetContent(szContents, pAttributes) && pSymbols.GetSize() > 0 && nSymbolIDs.GetSize() > 0);
}

VOID CTCProceduresMonitorTextView::UpdateContent(BOOL bRedraw)
{
	GetParent()->UpdateContent();
}

VOID CTCProceduresMonitorTextView::RefreshContent()
{
	INT  nIndex;
	INT  nCount;
	CString  szColumn;
	CTextViewLock  cLock(this);

	for (nIndex = 0, nCount = (INT)m_wndHeaderCtrl.m_szColumnsText.GetSize(); nIndex < nCount; nIndex++)
	{
		for (SetColumnColor(nIndex, LookupColumnColor(LookupColumnName(m_wndHeaderCtrl.m_szColumnsText.GetAt(nIndex)))); LookupColumnName((szColumn = m_wndHeaderCtrl.m_szColumnsText.GetAt(nIndex))) == TCPROCEDURESMONITOR_TITLEITEM_NAME || LookupColumnName(szColumn) == TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS || LookupColumnName(szColumn) == TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS; )
		{
			SetColumnFormat(nIndex, GetColumnFormat(nIndex) | DT_SINGLELINE);
			break;
		}
	}
	UpdateContent();
}

VOID CTCProceduresMonitorTextView::DrawContent()
{
	CTextView::DrawContent();
}
VOID CTCProceduresMonitorTextView::DrawContent(CDC *pDC)
{
	CTextView::DrawContent(pDC);
}

VOID CTCProceduresMonitorTextView::DrawText(INT nItem, LPCTSTR pszText)
{
	CTextView::DrawText(nItem, pszText);
}
VOID CTCProceduresMonitorTextView::DrawText(CDC *pDC, INT nItem, LPCTSTR pszText)
{
	CTextView::DrawText(pDC, nItem, pszText);
}
VOID CTCProceduresMonitorTextView::DrawText(INT nItem, INT nColumn, LPCTSTR pszText)
{
	CTextView::DrawText(nItem, nColumn, pszText);
}
VOID CTCProceduresMonitorTextView::DrawText(CDC *pDC, INT nItem, INT nColumn, LPCTSTR pszText)
{
	CDC  cDC;
	INT  nPos;
	BOOL  bText;
	BOOL  bState;
	UINT  nFormat;
	UINT  nSymbol;
	CRect  rText[3];
	CFont  cTextFont;
	CFont  *pOldFont;
	CSize  sizeSymbol;
	CSize  sizeBitmap;
	CPoint  ptBitmap;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	COLORREF  nColor[2];
	CTextViewAttribute  *pAttribute;

	for (m_wndContentCtrl.GetClientRect(rText[0]), rText[1] = m_wndContentCtrl.CalcTextRect(nItem, nColumn), sizeBitmap.cx = m_wndContentCtrl.m_wTextIndent[0] + rText[1].Width() + m_wndContentCtrl.m_wTextIndent[1], sizeBitmap.cy = m_wndContentCtrl.m_wTextSpacing[0] + rText[1].Height() + m_wndContentCtrl.m_wTextSpacing[1]; rText[2].IntersectRect(rText[0], CRect(rText[1].left - m_wndContentCtrl.m_wTextIndent[0], rText[1].top - m_wndContentCtrl.m_wTextSpacing[0], rText[1].right + m_wndContentCtrl.m_wTextIndent[1], rText[1].bottom + m_wndContentCtrl.m_wTextSpacing[1])); )
	{
		for (nFormat = GetColumnFormat(nItem, nColumn), nColor[0] = GetColumnColor(nItem, nColumn), bState = TRUE; (pAttribute = m_wndContentCtrl.m_pContentTextAttributes.GetAt(nItem)); )
		{
			bState = (pAttribute->GetColumnBlinkingState(nColumn, bState) || pAttribute->GetColumnBlinkingState(-1, bState)) ? bState : TRUE;
			break;
		}
		if (cDC.CreateCompatibleDC(pDC))
		{
			if (cBitmap.CreateCompatibleBitmap(pDC, sizeBitmap.cx, sizeBitmap.cy))
			{
				if ((pOldBitmap = cDC.SelectObject(&cBitmap)) != (CBitmap *)NULL)
				{
					for (cDC.SetBkMode(TRANSPARENT), cDC.SetTextColor(nColor[0]), DrawBackground(&cDC, nItem, nColumn, CRect(m_wndContentCtrl.m_wTextIndent[0] - rText[1].left, 0, sizeBitmap.cx, sizeBitmap.cy)), bText = FALSE; (pOldFont = (nColumn != FindColumnIndex(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS)) && nColumn != FindColumnIndex(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS))) ? ((GetColumnFont(nItem, nColumn, &cTextFont)) ? cDC.SelectObject(&cTextFont) : cDC.SelectObject(&m_wndContentCtrl.m_cFont)) : (CFont *)NULL); )
					{
						cDC.DrawText(((nPos = (nColumn == FindColumnIndex(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NAME))) ? (INT)_tcscspn(pszText, CString(GetSymbolDelimiter())) : -1) >= 0) ? CString(pszText).Left(nPos) : pszText, CRect(m_wndContentCtrl.m_wTextIndent[0], m_wndContentCtrl.m_wTextSpacing[0], sizeBitmap.cx - m_wndContentCtrl.m_wTextIndent[0], sizeBitmap.cy - m_wndContentCtrl.m_wTextSpacing[0]), nFormat);
						cDC.SelectObject(pOldFont);
						bText = TRUE;
						break;
					}
					if (nColumn == FindColumnIndex(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NAME)) || !bText)
					{
						for (sizeSymbol.cx = sizeSymbol.cy = 0, nColor[1] = cDC.GetNearestColor(VGA_COLOR_WHITE), cTextFont.DeleteObject(); (pOldFont = (GetColumnFont(nItem, nColumn, &cTextFont)) ? cDC.SelectObject(&cTextFont) : cDC.SelectObject(&m_wndContentCtrl.m_cFont)); )
						{
							sizeSymbol.cx = sizeSymbol.cy = cDC.GetTextExtent(SPACE).cy;
							m_sizeCheckFlagSymbols = sizeSymbol;
							m_sizeAlertSymbols = sizeSymbol;
							cDC.SelectObject(pOldFont);
							cTextFont.DeleteObject();
							break;
						}
						if (nColumn == FindColumnIndex(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NAME)))
						{
							for (nSymbol = (!_tcsstr(pszText, STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_INFORMATION))) ? ((!_tcsstr(pszText, STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_WARNING))) ? ((!_tcsstr(pszText, STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_ERROR))) ? ((!_tcsstr(pszText, STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_ALERT))) ? ((_tcsstr(pszText, STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_AUTHORIZATION))) ? TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOL_AUTHORIZATION : -1) : TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOL_ALERT) : TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOL_ERROR) : TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOL_WARNING) : TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOL_INFORMATION; nSymbol != (UINT)-1; )
							{
								if (bState) m_pAlertSymbols[nSymbol]->TransparentBlt(cDC.GetSafeHdc(), m_wndContentCtrl.m_wTextIndent[0] + CalcTelecommandSymbolPosition(nItem, nColumn, pszText).left - rText[1].left, m_wndContentCtrl.m_wTextSpacing[0], sizeSymbol.cx, sizeSymbol.cy, nColor[1]);
								break;
							}
						}
						else if (nColumn == FindColumnIndex(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS)))
						{
							for (nSymbol = (lstrlen(pszText) > 0) ? ((!_tcsstr(pszText, STRING(IDS_TCPROCEDURESMONITOR_LIST_PEVCHECKS_DISABLED))) ? ((_tcsstr(pszText, STRING(IDS_TCPROCEDURESMONITOR_LIST_PEVCHECKS_ON))) ? TCPROCEDURESMONITORTEXTVIEW_COMMANDCHECKFLAGSYMBOL_ON : TCPROCEDURESMONITORTEXTVIEW_COMMANDCHECKFLAGSYMBOL_OFF) : TCPROCEDURESMONITORTEXTVIEW_COMMANDCHECKFLAGSYMBOL_DISABLED) : -1; nSymbol != (UINT)-1; )
							{
								if (bState) m_pCheckFlagSymbols[nSymbol]->TransparentBlt(cDC.GetSafeHdc(), m_wndContentCtrl.m_wTextIndent[0] + CalcTelecommandSymbolPosition(nItem, nColumn, 1, 0).left - rText[1].left, m_wndContentCtrl.m_wTextSpacing[0], sizeSymbol.cx, sizeSymbol.cy, nColor[1]);
								break;
							}
						}
						else if (nColumn == FindColumnIndex(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS)))
						{
							for (nSymbol = (lstrlen(pszText) > 0) ? ((!_tcsstr(pszText, STRING(IDS_TCPROCEDURESMONITOR_LIST_CEVCHECKS_DISABLED))) ? ((_tcsstr(pszText, STRING(IDS_TCPROCEDURESMONITOR_LIST_CEVCHECKS_ON))) ? TCPROCEDURESMONITORTEXTVIEW_COMMANDCHECKFLAGSYMBOL_ON : TCPROCEDURESMONITORTEXTVIEW_COMMANDCHECKFLAGSYMBOL_OFF) : TCPROCEDURESMONITORTEXTVIEW_COMMANDCHECKFLAGSYMBOL_DISABLED) : -1; nSymbol != (UINT)-1; )
							{
								if (bState) m_pCheckFlagSymbols[nSymbol]->TransparentBlt(cDC.GetSafeHdc(), m_wndContentCtrl.m_wTextIndent[0] + CalcTelecommandSymbolPosition(nItem, nColumn, 1, 0).left - rText[1].left, m_wndContentCtrl.m_wTextSpacing[0], sizeSymbol.cx, sizeSymbol.cy, nColor[1]);
								break;
							}
						}
					}
					ptBitmap.x = max(rText[2].left - rText[1].left + m_wndContentCtrl.m_wTextIndent[0], 0);
					ptBitmap.y = max(rText[2].top - rText[1].top + m_wndContentCtrl.m_wTextSpacing[0], 0);
					pDC->BitBlt(max(rText[1].left - m_wndContentCtrl.m_wTextIndent[0], rText[2].left), max(rText[1].top - m_wndContentCtrl.m_wTextSpacing[0], rText[2].top), min(sizeBitmap.cx - ptBitmap.x, rText[2].Width()), min(sizeBitmap.cy - ptBitmap.y, rText[2].Height()), &cDC, ptBitmap.x, ptBitmap.y, SRCCOPY);
					cDC.SelectObject(pOldBitmap);
				}
				cBitmap.DeleteObject();
			}
			cDC.DeleteDC();
		}
		break;
	}
}

BOOL CTCProceduresMonitorTextView::DrawBackground(CDC *pDC, INT nItem, INT nColumn, CONST RECT &rItem)
{
	if (nColumn < 0)
	{
		pDC->FillSolidRect(&rItem, GetSysColor(COLOR_WINDOW));
		return TRUE;
	}
	return CTextView::DrawBackground(pDC, nItem, nColumn, rItem);
}

CTCProceduresMonitorListView *CTCProceduresMonitorTextView::GetParent() CONST
{
	return((CTCProceduresMonitorListView *)CTextView::GetParent());
}

CTCProceduresMonitorWnd *CTCProceduresMonitorTextView::GetParentDisplay() CONST
{
	CTCProceduresMonitorListView  *pView;

	return(((pView = GetParent())) ? pView->GetParentDisplay() : (CTCProceduresMonitorWnd *)NULL);
}

CString CTCProceduresMonitorTextView::LookupColumnName(UINT nColumn) CONST
{
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_NAME) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NAME);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_DESCRIPTION) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_DESCRIPTION);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_COMMENTS) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_COMMENTS);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_AUTHOR) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_AUTHOR);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_CREATIONTIME) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_CREATIONTIME);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_MODIFICATIONTIME) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_MODIFICATIONTIME);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_VERIFICATIONSTATUS) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_VERIFICATIONSTATUS);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_NUMBEROFTHREADS) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NUMBEROFTHREADS);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_ARGUMENTS) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ARGUMENTS);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_TRIGGERTYPE) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_TRIGGERTYPE);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONMODE) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONMODE);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONCOUNT) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONCOUNT);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_RUNNINGSTATE) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_RUNNINGSTATE);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_ACKNOWLEDGEREQUEST) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ACKNOWLEDGEREQUEST);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_ACKREQUESTTIME) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ACKREQUESTTIME);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_STARTTIME) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_STARTTIME);
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_ENDTIME) return STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ENDTIME);
	return EMPTYSTRING;
}
UINT CTCProceduresMonitorTextView::LookupColumnName(LPCTSTR pszColumn) CONST
{
	if (!lstrcmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NAME))) return TCPROCEDURESMONITOR_TITLEITEM_NAME;
	if (!lstrcmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_DESCRIPTION))) return TCPROCEDURESMONITOR_TITLEITEM_DESCRIPTION;
	if (!lstrcmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_COMMENTS))) return TCPROCEDURESMONITOR_TITLEITEM_COMMENTS;
	if (!lstrcmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_AUTHOR))) return TCPROCEDURESMONITOR_TITLEITEM_AUTHOR;
	if (!lstrcmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_CREATIONTIME))) return TCPROCEDURESMONITOR_TITLEITEM_CREATIONTIME;
	if (!lstrcmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_MODIFICATIONTIME))) return TCPROCEDURESMONITOR_TITLEITEM_MODIFICATIONTIME;
	if (!lstrcmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_VERIFICATIONSTATUS))) return TCPROCEDURESMONITOR_TITLEITEM_VERIFICATIONSTATUS;
	if (!lstrcmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NUMBEROFTHREADS))) return TCPROCEDURESMONITOR_TITLEITEM_NUMBEROFTHREADS;
	if (!lstrcmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ARGUMENTS))) return TCPROCEDURESMONITOR_TITLEITEM_ARGUMENTS;
	if (!lstrcmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_TRIGGERTYPE))) return TCPROCEDURESMONITOR_TITLEITEM_TRIGGERTYPE;
	if (!lstrcmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONMODE))) return TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONMODE;
	if (!lstrcmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONCOUNT))) return TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONCOUNT;
	if (!lstrcmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_RUNNINGSTATE))) return TCPROCEDURESMONITOR_TITLEITEM_RUNNINGSTATE;
	if (!lstrcmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ACKNOWLEDGEREQUEST))) return TCPROCEDURESMONITOR_TITLEITEM_ACKNOWLEDGEREQUEST;
	if (!lstrcmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ACKREQUESTTIME))) return TCPROCEDURESMONITOR_TITLEITEM_ACKREQUESTTIME;
	if (!lstrcmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS))) return TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS;
	if (!lstrcmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS))) return TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS;
	if (!lstrcmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_STARTTIME))) return TCPROCEDURESMONITOR_TITLEITEM_STARTTIME;
	if (!lstrcmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ENDTIME))) return TCPROCEDURESMONITOR_TITLEITEM_ENDTIME;
	return 0;
}

INT CTCProceduresMonitorTextView::LookupColumnsName(CONST CUIntArray &nColumns, CStringArray &szColumns) CONST
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

COLORREF CTCProceduresMonitorTextView::LookupColumnColor(UINT nColumn) CONST
{
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_NAME) return GetDatabase()->GetTCProceduresMonitorNameColumnColor();
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_DESCRIPTION) return GetDatabase()->GetTCProceduresMonitorDescriptionColumnColor();
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_COMMENTS) return GetDatabase()->GetTCProceduresMonitorCommentsColumnColor();
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_AUTHOR) return GetDatabase()->GetTCProceduresMonitorAuthorColumnColor();
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_CREATIONTIME) return GetDatabase()->GetTCProceduresMonitorCreationTimeColumnColor();
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_MODIFICATIONTIME) return GetDatabase()->GetTCProceduresMonitorModificationTimeColumnColor();
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_VERIFICATIONSTATUS) return GetDatabase()->GetTCProceduresMonitorVerificationStatusColumnColor();
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_NUMBEROFTHREADS) return GetDatabase()->GetTCProceduresMonitorNumberOfThreadsColumnColor();
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_ARGUMENTS) return GetDatabase()->GetTCProceduresMonitorArgumentsColumnColor();
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_TRIGGERTYPE) return GetDatabase()->GetTCProceduresMonitorTriggerTypeColumnColor();
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONMODE) return GetDatabase()->GetTCProceduresMonitorExecutionModeColumnColor();
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONCOUNT) return GetDatabase()->GetTCProceduresMonitorExecutionCountColumnColor();
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_RUNNINGSTATE) return GetDatabase()->GetTCProceduresMonitorRunningStateColumnColor();
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_ACKNOWLEDGEREQUEST) return GetDatabase()->GetTCProceduresMonitorAcknowledgeRequestColumnColor();
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_ACKREQUESTTIME) return GetDatabase()->GetTCProceduresMonitorAckRequestTimeColumnColor();
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS) return GetDatabase()->GetTCProceduresMonitorPEVChecksColumnColor();
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS) return GetDatabase()->GetTCProceduresMonitorCEVChecksColumnColor();
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_STARTTIME) return GetDatabase()->GetTCProceduresMonitorStartTimeColumnColor();
	if (nColumn == TCPROCEDURESMONITOR_TITLEITEM_ENDTIME) return GetDatabase()->GetTCProceduresMonitorEndTimeColumnColor();
	return GetSysColor(COLOR_WINDOWTEXT);
}

INT CTCProceduresMonitorTextView::CalcColumnWidth(LPCTSTR pszColumn)
{
	CDC  *pDC;
	INT  nWidth;
	INT  nDxChar;
	UINT  nColumn;
	CFont  cFont[2];
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((nColumn = LookupColumnName(pszColumn)) == 0)
		{
			for (GetTextFont(&cFont[1]), nWidth = 0; (pOldFont = pDC->SelectObject(&cFont[1])); )
			{
				nWidth = LOWORD(GetTextIndents()) + pDC->GetTextExtent(pszColumn).cx + HIWORD(GetTextIndents());
				pDC->SelectObject(pOldFont);
				break;
			}
			ReleaseDC(pDC);
			return nWidth;
		}
		for (GetTitleFont(&cFont[0]), GetTextFont(&cFont[1]), nWidth = 0; (pOldFont = pDC->SelectObject(&cFont[0])); )
		{
			nWidth = LOWORD(GetTextIndents()) + pDC->GetTextExtent(pszColumn).cx + HIWORD(GetTextIndents());
			pDC->SelectObject(pOldFont);
			break;
		}
		if ((pOldFont = pDC->SelectObject(&cFont[1])))
		{
			if ((nDxChar = (pDC->GetTextMetrics(&tmFont) > 0) ? (4 * tmFont.tmAveCharWidth / 3) : 0) > 0)
			{
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_NAME) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCProceduresMonitorNameColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_DESCRIPTION) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCProceduresMonitorDescriptionColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_COMMENTS) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCProceduresMonitorCommentsColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_AUTHOR) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCProceduresMonitorAuthorColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_CREATIONTIME) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCProceduresMonitorCreationTimeColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_MODIFICATIONTIME) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCProceduresMonitorModificationTimeColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_VERIFICATIONSTATUS) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCProceduresMonitorVerificationStatusColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_NUMBEROFTHREADS) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCProceduresMonitorNumberOfThreadsColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_ARGUMENTS) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCProceduresMonitorArgumentsColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_TRIGGERTYPE) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCProceduresMonitorTriggerTypeColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONMODE) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCProceduresMonitorExecutionModeColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONCOUNT) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCProceduresMonitorExecutionCountColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_RUNNINGSTATE) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCProceduresMonitorRunningStateColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_ACKNOWLEDGEREQUEST) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCProceduresMonitorAcknowledgeRequestColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_ACKREQUESTTIME) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCProceduresMonitorAckRequestTimeColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCProceduresMonitorPEVChecksColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCProceduresMonitorCEVChecksColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_STARTTIME) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCProceduresMonitorStartTimeColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCPROCEDURESMONITOR_TITLEITEM_ENDTIME) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCProceduresMonitorEndTimeColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
			}
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
		return nWidth;
	}
	return 0;
}

INT CTCProceduresMonitorTextView::CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths)
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

INT CTCProceduresMonitorTextView::FindColumnIndex(LPCTSTR pszColumn) CONST
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_wndHeaderCtrl.m_szColumnsText.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (!m_wndHeaderCtrl.m_szColumnsText.GetAt(nColumn).Compare(pszColumn)) break;
		continue;
	}
	return((nColumn < nColumns) ? nColumn : -1);
}

CRect CTCProceduresMonitorTextView::CalcTelecommandSymbolPosition(INT nRow, INT nColumn, LPCTSTR pszText) CONST
{
	INT  nPos;
	CRect  rText;
	CRect  rSymbol;
	CFont  *pOldFont;
	CString  szText;
	CClientDC  cDC(NULL);

	for (szText = ((nPos = (szText = pszText).Find(GetSymbolDelimiter())) >= 0) ? szText.Left(nPos) : szText, rText = m_wndContentCtrl.CalcTextRect(nRow, nColumn), rSymbol.SetRectEmpty(); (pOldFont = (nColumn == FindColumnIndex(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NAME)) && !rText.IsRectEmpty()) ? cDC.SelectObject((CFont *)&m_wndContentCtrl.m_cFont) : (CFont *)NULL); )
	{
		rSymbol.SetRect(rText.left + cDC.GetTextExtent(szText + SPACE).cx, rText.top, rText.left + cDC.GetTextExtent(szText + SPACE).cx + m_sizeAlertSymbols.cx, rText.top + m_sizeAlertSymbols.cy);
		rSymbol.SetRect(min(max(rText.left, rSymbol.left), rText.right), rSymbol.top, max(min(rText.right, rSymbol.right), rText.left), rSymbol.bottom);
		rSymbol.InflateRect(0, 0, 1, 1);
		cDC.SelectObject(pOldFont);
		break;
	}
	return rSymbol;
}
CRect CTCProceduresMonitorTextView::CalcTelecommandSymbolPosition(INT nRow, INT nColumn, INT nCount, INT nIndex) CONST
{
	CRect  rText;
	CRect  rSymbol;

	for (rText = m_wndContentCtrl.CalcTextRect(nRow, nColumn), rSymbol.SetRectEmpty(); (nColumn == FindColumnIndex(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS)) || nColumn == FindColumnIndex(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS))) && !rText.IsRectEmpty(); )
	{
		rSymbol.SetRect(rText.left + (rText.Width() - (nCount*((m_wndContentCtrl.m_wTextIndent[0] + m_wndContentCtrl.m_wTextIndent[1]) / 4 + m_sizeCheckFlagSymbols.cx))) / 2 + nIndex*((m_wndContentCtrl.m_wTextIndent[0] + m_wndContentCtrl.m_wTextIndent[1]) / 4 + m_sizeCheckFlagSymbols.cx), rText.top, rText.left + (rText.Width() - (nCount*((m_wndContentCtrl.m_wTextIndent[0] + m_wndContentCtrl.m_wTextIndent[1]) / 4 + m_sizeCheckFlagSymbols.cx) + m_wndContentCtrl.m_wTextIndent[1])) / 2 + nIndex*((m_wndContentCtrl.m_wTextIndent[0]) / 4 + m_sizeCheckFlagSymbols.cx) + m_sizeCheckFlagSymbols.cx, rText.top + m_sizeCheckFlagSymbols.cy);
		rSymbol.SetRect(min(max(rText.left, rSymbol.left), rText.right), rSymbol.top, max(min(rText.right, rSymbol.right), rText.left), rSymbol.bottom);
		rSymbol.InflateRect(0, 0, 1, 1);
		break;
	}
	return rSymbol;
}

TCHAR CTCProceduresMonitorTextView::GetSymbolDelimiter()
{
	return TAB;
}

CString CTCProceduresMonitorTextView::ConstructToolTipTitle(LPCTSTR pszTip, UINT nTip) CONST
{
	CString  szTitle;

	if (m_wndHeaderCtrl.m_szColumnsText.GetAt(nTip) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NAME))
	{
		if (_tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_INFORMATION)))
		{
			szTitle = STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_SYMBOLINFORMATION);
			return szTitle;
		}
		if (_tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_WARNING)))
		{
			szTitle = STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_SYMBOLWARNING);
			return szTitle;
		}
		if (_tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_ERROR)))
		{
			szTitle = STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_SYMBOLERROR);
			return szTitle;
		}
		if (_tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_ALERT)))
		{
			szTitle = STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_SYMBOLALERT);
			return szTitle;
		}
		if (_tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_AUTHORIZATION)))
		{
			szTitle = STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_SYMBOLAUTHORIZATION);
			return szTitle;
		}
	}
	if (m_wndHeaderCtrl.m_szColumnsText.GetAt(nTip) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS))
	{
		if (_tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_PEVCHECKS_ON)) || _tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_PEVCHECKS_OFF)) || _tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_PEVCHECKS_DISABLED)))
		{
			szTitle = STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_PEVCHECKSTITLE);
			return szTitle;
		}
	}
	if (m_wndHeaderCtrl.m_szColumnsText.GetAt(nTip) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS))
	{
		if (_tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_CEVCHECKS_ON)) || _tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_CEVCHECKS_OFF)) || _tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_CEVCHECKS_DISABLED)))
		{
			szTitle = STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_CEVCHECKSTITLE);
			return szTitle;
		}
	}
	return szTitle;
}

CString CTCProceduresMonitorTextView::ConstructToolTipText(INT nIndex, LPCTSTR pszTip, UINT nTip) CONST
{
	CString  szText;
	CString  szCheckState[2];
	CTCProceduresMonitorItem  cItem;

	if (m_wndHeaderCtrl.m_szColumnsText.GetAt(nTip) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NAME))
	{
		if (_tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_INFORMATION)) || _tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_WARNING)) || _tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_ERROR)) || _tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_ALERT)) || _tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_AUTHORIZATION)))
		{
			if (GetParent()->GetProcedureInfo(nIndex, &cItem))
			{
				szText = cItem.GetAlertMessage();
				return szText;
			}
		}
	}
	if (m_wndHeaderCtrl.m_szColumnsText.GetAt(nTip) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS))
	{
		if (_tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_PEVCHECKS_ON)) || _tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_PEVCHECKS_OFF)) || _tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_PEVCHECKS_DISABLED)))
		{
			szCheckState[0] = (_tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_PEVCHECKS_OFF))) ? STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_PEVCHECKSSTATEOFF) : STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_PEVCHECKSSTATEON);
			szCheckState[0] = (_tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_PEVCHECKS_DISABLED))) ? STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_PEVCHECKSSTATEDISABLED) : szCheckState[0];
			szCheckState[1].Format(STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_PEVCHECKSTEXT), (LPCTSTR)szCheckState[0]);
			return szCheckState[1];
		}
	}
	if (m_wndHeaderCtrl.m_szColumnsText.GetAt(nTip) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS))
	{
		if (_tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_CEVCHECKS_ON)) || _tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_CEVCHECKS_OFF)) || _tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_CEVCHECKS_DISABLED)))
		{
			szCheckState[0] = (_tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_CEVCHECKS_OFF))) ? STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_CEVCHECKSSTATEOFF) : STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_CEVCHECKSSTATEON);
			szCheckState[0] = (_tcsstr(pszTip, STRING(IDS_TCPROCEDURESMONITOR_LIST_CEVCHECKS_DISABLED))) ? STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_CEVCHECKSSTATEDISABLED) : szCheckState[0];
			szCheckState[1].Format(STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_CEVCHECKSTEXT), (LPCTSTR)szCheckState[0]);
			return szCheckState[1];
		}
	}
	return szText;
}

BOOL CTCProceduresMonitorTextView::LoadTelecommandSymbols()
{
	INT  nSymbol[2];
	INT  nSymbols[2];
	ULONG  cbSymbol;
	HRSRC  hResource;
	LPVOID  pResource;
	HMODULE  hModule;
	HGLOBAL  hMemResource[2];
	LPSTREAM  pIStream;

	for (nSymbol[0] = 0, nSymbols[0] = TCPROCEDURESMONITORTEXTVIEW_COMMANDCHECKFLAGSYMBOLS; nSymbol[0] < nSymbols[0]; nSymbol[0]++)
	{
		if ((hResource = FindResource((hModule = GetModuleHandle((LPCTSTR)NULL)), (nSymbol[0] == TCPROCEDURESMONITORTEXTVIEW_COMMANDCHECKFLAGSYMBOL_NONE) ? MAKEINTRESOURCE(IDP_TCPROCEDURESMONITORCHECKSNONE) : ((nSymbol[0] == TCPROCEDURESMONITORTEXTVIEW_COMMANDCHECKFLAGSYMBOL_ON) ? MAKEINTRESOURCE(IDP_TCPROCEDURESMONITORCHECKSON) : ((nSymbol[0] == TCPROCEDURESMONITORTEXTVIEW_COMMANDCHECKFLAGSYMBOL_OFF) ? MAKEINTRESOURCE(IDP_TCPROCEDURESMONITORCHECKSOFF) : MAKEINTRESOURCE(IDP_TCPROCEDURESMONITORCHECKSDISABLED))), STRING(IDS_RESOURCETYPE_PICTURE))))
		{
			if ((hMemResource[0] = LoadResource(hModule, hResource)))
			{
				if ((pResource = LockResource(hMemResource[0])))
				{
					if ((hMemResource[1] = GlobalAlloc(GMEM_MOVEABLE, 0)))
					{
						if (SUCCEEDED(CreateStreamOnHGlobal(hMemResource[1], TRUE, &pIStream)))
						{
							if ((m_pCheckFlagSymbols[nSymbol[0]] = new CImage) != (CImage *)NULL)
							{
								if (SUCCEEDED(pIStream->Write(pResource, SizeofResource(hModule, hResource), &cbSymbol)) && SUCCEEDED(m_pCheckFlagSymbols[nSymbol[0]]->Load(pIStream)))
								{
									pIStream->Release();
									continue;
								}
								delete m_pCheckFlagSymbols[nSymbol[0]];
								m_pCheckFlagSymbols[nSymbol[0]] = (CImage *)NULL;
							}
							pIStream->Release();
						}
					}
				}
			}
		}
		while (nSymbol[0] > 0)
		{
			delete m_pCheckFlagSymbols[--nSymbol[0]];
			m_pCheckFlagSymbols[nSymbol[0]] = (CImage *)NULL;
		}
		break;
	}
	for (nSymbol[1] = 0, nSymbols[1] = TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOLS; nSymbol[1] < nSymbols[1]; nSymbol[1]++)
	{
		if ((hResource = FindResource((hModule = GetModuleHandle((LPCTSTR)NULL)), (nSymbol[1] == TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOL_INFORMATION) ? MAKEINTRESOURCE(IDP_TCPROCEDURESMONITORINFORMATION) : ((nSymbol[1] == TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOL_WARNING) ? MAKEINTRESOURCE(IDP_TCPROCEDURESMONITORWARNING) : ((nSymbol[1] == TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOL_ERROR) ? MAKEINTRESOURCE(IDP_TCPROCEDURESMONITORERROR) : ((nSymbol[1] == TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOL_ALERT) ? MAKEINTRESOURCE(IDP_TCPROCEDURESMONITORALERT) : MAKEINTRESOURCE(IDP_TCPROCEDURESMONITORAUTHORIZATION)))), STRING(IDS_RESOURCETYPE_PICTURE))))
		{
			if ((hMemResource[0] = LoadResource(hModule, hResource)))
			{
				if ((pResource = LockResource(hMemResource[0])))
				{
					if ((hMemResource[1] = GlobalAlloc(GMEM_MOVEABLE, 0)))
					{
						if (SUCCEEDED(CreateStreamOnHGlobal(hMemResource[1], TRUE, &pIStream)))
						{
							if ((m_pAlertSymbols[nSymbol[1]] = new CImage) != (CImage *)NULL)
							{
								if (SUCCEEDED(pIStream->Write(pResource, SizeofResource(hModule, hResource), &cbSymbol)) && SUCCEEDED(m_pAlertSymbols[nSymbol[1]]->Load(pIStream)))
								{
									pIStream->Release();
									continue;
								}
								delete m_pAlertSymbols[nSymbol[1]];
								m_pAlertSymbols[nSymbol[1]] = (CImage *)NULL;
							}
							pIStream->Release();
						}
					}
				}
			}
		}
		while (nSymbol[1] > 0)
		{
			delete m_pAlertSymbols[--nSymbol[1]];
			m_pAlertSymbols[nSymbol[1]] = (CImage *)NULL;
		}
		break;
	}
	return((nSymbol[0] == nSymbols[0] && nSymbol[1] == nSymbols[1]) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorTextView::FreeTelecommandSymbols()
{
	INT  nSymbol;
	INT  nSymbols;

	for (nSymbol = 0, nSymbols = TCPROCEDURESMONITORTEXTVIEW_COMMANDCHECKFLAGSYMBOLS; nSymbol < nSymbols; nSymbol++)
	{
		if (m_pCheckFlagSymbols[nSymbol] != (CImage *)NULL)
		{
			m_pCheckFlagSymbols[nSymbol]->Destroy();
			delete m_pCheckFlagSymbols[nSymbol];
		}
	}
	for (nSymbol = 0, nSymbols = TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOLS; nSymbol < nSymbols; nSymbol++)
	{
		if (m_pAlertSymbols[nSymbol] != (CImage *)NULL)
		{
			m_pAlertSymbols[nSymbol]->Destroy();
			delete m_pAlertSymbols[nSymbol];
		}
	}
}

BOOL CTCProceduresMonitorTextView::LoadToolTipCursor()
{
	return(((m_hToolTipCursor = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_TOOLTIPCURSOR), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR))) ? TRUE : FALSE);
}

HCURSOR CTCProceduresMonitorTextView::GetToolTipCursor() CONST
{
	return((!m_hToolTipCursor) ? (HCURSOR)(DWORD_PTR)GetClassLongPtr(GetSafeHwnd(), GCLP_HCURSOR) : m_hToolTipCursor);
}

BOOL CTCProceduresMonitorTextView::FreeToolTipCursor()
{
	if (m_hToolTipCursor)
	{
		DestroyCursor(m_hToolTipCursor);
		m_hToolTipCursor = (HCURSOR)NULL;
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorTextView::SetLayoutInfo(INT nIndex, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo)
{
	CTextViewLock  cLock(this);

	SetCurText(nIndex);
	SetScrollInfo(pHorzScrollInfo, pVertScrollInfo);
	return TRUE;
}

BOOL CTCProceduresMonitorTextView::GetLayoutInfo(INT &nIndex, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST
{
	CTextViewLock  cLock(this);

	nIndex = GetCurText();
	GetScrollInfo(pHorzScrollInfo, pVertScrollInfo);
	return TRUE;
}

BOOL CTCProceduresMonitorTextView::Lock()
{
	CTCProceduresMonitorWnd  *pParentWnd;

	return(((pParentWnd = GetParentDisplay())) ? (pParentWnd->Lock() && CTextView::Lock()) : CTextView::Lock());
}

BOOL CTCProceduresMonitorTextView::Unlock()
{
	CTCProceduresMonitorWnd  *pParentWnd;

	return(((pParentWnd = GetParentDisplay())) ? (CTextView::Unlock() && pParentWnd->Unlock()) : CTextView::Unlock());
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorTextView, CTextView)
	//{{AFX_MSG_MAP(CTCProceduresMonitorTextView)
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorTextView message handlers

int CTCProceduresMonitorTextView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CTextViewLock  cLock(this);

	return((CTextView::OnCreate(lpCreateStruct) != -1 && LoadTelecommandSymbols() && LoadToolTipCursor()) ? 0 : -1);
}

BOOL CTCProceduresMonitorTextView::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	INT  nRow;
	INT  nColumn;
	CPoint  ptCursor;
	CString  szText;
	CTextViewLock  cLock(this);

	for (GetCursorPos(&ptCursor), m_wndContentCtrl.ScreenToClient(&ptCursor); IsToolTipModeEnabled() && FindTextFromPoint(ptCursor, nRow, nColumn, TRUE) && GetText(nRow, nColumn, szText); )
	{
		if (nColumn == FindColumnIndex(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NAME)))
		{
			if (_tcsstr(szText, STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_INFORMATION)) || _tcsstr(szText, STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_WARNING)) || _tcsstr(szText, STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_ERROR)) || _tcsstr(szText, STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_ALERT)) || _tcsstr(szText, STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_AUTHORIZATION)))
			{
				if (CalcTelecommandSymbolPosition(nRow, nColumn, szText).PtInRect(ptCursor))
				{
					SetCursor(GetToolTipCursor());
					return TRUE;
				}
			}
			break;
		}
		if (nColumn == FindColumnIndex(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS)))
		{
			if (_tcsstr(szText, STRING(IDS_TCPROCEDURESMONITOR_LIST_PEVCHECKS_ON)) || _tcsstr(szText, STRING(IDS_TCPROCEDURESMONITOR_LIST_PEVCHECKS_OFF)) || _tcsstr(szText, STRING(IDS_TCPROCEDURESMONITOR_LIST_PEVCHECKS_DISABLED)))
			{
				if (CalcTelecommandSymbolPosition(nRow, nColumn, 1, 0).PtInRect(ptCursor))
				{
					SetCursor(GetToolTipCursor());
					return TRUE;
				}
			}
			break;
		}
		if (nColumn == FindColumnIndex(STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS)))
		{
			if (_tcsstr(szText, STRING(IDS_TCPROCEDURESMONITOR_LIST_CEVCHECKS_ON)) || _tcsstr(szText, STRING(IDS_TCPROCEDURESMONITOR_LIST_CEVCHECKS_OFF)) || _tcsstr(szText, STRING(IDS_TCPROCEDURESMONITOR_LIST_CEVCHECKS_DISABLED)))
			{
				if (CalcTelecommandSymbolPosition(nRow, nColumn, 1, 0).PtInRect(ptCursor))
				{
					SetCursor(GetToolTipCursor());
					return TRUE;
				}
			}
			break;
		}
		break;
	}
	return CTextView::OnSetCursor(pWnd, nHitTest, message);
}

BOOL CTCProceduresMonitorTextView::OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	INT  nRow;
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nColumn;
	INT  nHeight;
	CRect  rContent;
	CFont  cFont[2];
	CPoint  ptToolTip;
	LOGFONT  lfFont[2];
	CString  szToolTip[3];
	CTextViewLock  cLock(this);

	if (message == WM_KEYDOWN)
	{
		if (wParam == VK_UP || wParam == VK_DOWN)
		{
			for (BeginWaitCursor(), nIndex = GetCurText(); wParam == VK_UP && (nIndex > 0 || (nIndex < 0 && GetTextCount() > 0)); )
			{
				SetCurText((nIndex = (nIndex < 0) ? (GetTextCount() - 1) : (nIndex - 1)));
				ScrollTo(nIndex);
				EndWaitCursor();
				return TRUE;
			}
			if (wParam == VK_DOWN && (nIndex < (INT)GetTextCount() - 1 || (nIndex < 0 && GetTextCount() > 0)))
			{
				SetCurText((nIndex = (nIndex >= 0) ? (nIndex + 1) : 0));
				ScrollTo(nIndex);
				EndWaitCursor();
				return TRUE;
			}
			EndWaitCursor();
		}
		if (wParam == VK_PRIOR || wParam == VK_NEXT)
		{
			for (BeginWaitCursor(), nItem = nIndex = GetCurText(), nItems = GetTextCount(), m_wndContentCtrl.GetClientRect(rContent), nHeight = (nItems > 0) ? ((nItem > 0) ? (m_wndContentCtrl.m_nContentTextPos.GetAt(nItem) - m_wndContentCtrl.m_nContentTextPos.GetAt(nItem - 1)) : m_wndContentCtrl.m_nContentTextPos.GetAt(0)) : 0; nItem >= 0 && nItem < nItems; nItem = (wParam == VK_NEXT) ? (nItem + 1) : (nItem - 1))
			{
				if (abs((INT)(m_wndContentCtrl.m_nContentTextPos.GetAt(nIndex) - m_wndContentCtrl.m_nContentTextPos.GetAt(nItem))) >= rContent.Height() - nHeight) break;
				continue;
			}
			if ((nItem = (nIndex >= 0) ? max(min(nItem, nItems - 1), 0) : ((wParam == VK_PRIOR) ? (nItems - 1) : 0)) != nIndex)
			{
				SetCurText(nItem);
				ScrollTo(nItem);
			}
			EndWaitCursor();
			return TRUE;
		}
		if (wParam == VK_TAB) GetParent()->SetFocus();
		return FALSE;
	}
	if (message == WM_LBUTTONDOWN)
	{
		if ((nIndex = FindTextFromPoint(CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)), FALSE)) >= 0)
		{
			BeginWaitCursor();
			SetCurText(nIndex);
			EndWaitCursor();
		}
		m_wndHeaderCtrl.SetFocus();
		return FALSE;
	}
	if (message == WM_RBUTTONDOWN)
	{
		if (GetCursor() == GetToolTipCursor() && FindTextFromPoint((ptToolTip = CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))), nRow, nColumn, TRUE) && GetText(nRow, nColumn, szToolTip[2]))
		{
			for (szToolTip[0] = ConstructToolTipTitle(szToolTip[2], nColumn), szToolTip[1] = ConstructToolTipText(nRow, szToolTip[2], nColumn); !szToolTip[0].IsEmpty() || !szToolTip[1].IsEmpty(); )
			{
				for (GetTextFont(&lfFont[0]), GetTextFont(&lfFont[1]), lfFont[0].lfWeight = FW_BOLD, lfFont[1].lfWeight = FW_NORMAL; cFont[0].CreateFontIndirect(&lfFont[0]) && cFont[1].CreateFontIndirect(&lfFont[1]); )
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

void CTCProceduresMonitorTextView::OnDestroy()
{
	CTextViewLock  cLock(this);

	FreeToolTipCursor();
	FreeTelecommandSymbols();
	CTextView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorListView

IMPLEMENT_DYNCREATE(CTCProceduresMonitorListView, CView)

CTCProceduresMonitorListView::CTCProceduresMonitorListView() : CView()
{
	m_nTelecommandingMode = 0;
	m_nTelecommandingFlags = 0;
	m_nTelecommandingState = 0;
	m_nTelecommandingUplinkState = 0;
	m_bTelecommandingReleaseWaitMode = FALSE;
	m_pwndList = new CTCProceduresMonitorTextView;
	m_pTCProcessEngine = (CTCProcessEngine *)NULL;
	m_pTCEnvironment = (CTCEnvironment *)NULL;
	m_pParentWnd = (CWnd *)NULL;
}

CTCProceduresMonitorListView::~CTCProceduresMonitorListView()
{
	delete m_pwndList;
}

BOOL CTCProceduresMonitorListView::SetLayout(CONST CUIntArray &nColumns)
{
	CTextViewLock  cLock(m_pwndList);

	if (m_pwndList->SetLayout(nColumns))
	{
		ShowContent();
		return TRUE;
	}
	return FALSE;
}
BOOL CTCProceduresMonitorListView::SetLayout(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths)
{
	CTextViewLock  cLock(m_pwndList);

	if (m_pwndList->SetLayout(nColumns, nWidths))
	{
		ShowContent();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorListView::GetLayout(CUIntArray &nColumns) CONST
{
	return m_pwndList->GetLayout(nColumns);
}
BOOL CTCProceduresMonitorListView::GetLayout(CUIntArray &nColumns, CUIntArray &nWidths) CONST
{
	return m_pwndList->GetLayout(nColumns, nWidths);
}

BOOL CTCProceduresMonitorListView::SetListTitleFont(CFont *pFont)
{
	return m_pwndList->SetTitleFont(pFont);
}
BOOL CTCProceduresMonitorListView::SetListTitleFont(CONST LOGFONT *plfFont)
{
	return m_pwndList->SetTitleFont(plfFont);
}

BOOL CTCProceduresMonitorListView::GetListTitleFont(CFont *pFont) CONST
{
	return m_pwndList->GetTitleFont(pFont);
}
BOOL CTCProceduresMonitorListView::GetListTitleFont(LOGFONT *plfFont) CONST
{
	return m_pwndList->GetTitleFont(plfFont);
}

BOOL CTCProceduresMonitorListView::SetListItemsFont(CFont *pFont)
{
	return m_pwndList->SetItemsFont(pFont);
}
BOOL CTCProceduresMonitorListView::SetListItemsFont(CONST LOGFONT *plfFont)
{
	return m_pwndList->SetItemsFont(plfFont);
}

BOOL CTCProceduresMonitorListView::GetListItemsFont(CFont *pFont) CONST
{
	return m_pwndList->GetItemsFont(pFont);
}
BOOL CTCProceduresMonitorListView::GetListItemsFont(LOGFONT *plfFont) CONST
{
	return m_pwndList->GetItemsFont(plfFont);
}

BOOL CTCProceduresMonitorListView::EnableToolTipMode(BOOL bEnable)
{
	return m_pwndList->EnableToolTipMode(bEnable);
}

BOOL CTCProceduresMonitorListView::IsToolTipModeEnabled() CONST
{
	return m_pwndList->IsToolTipModeEnabled();
}

BOOL CTCProceduresMonitorListView::SetProcedures(CONST CTCProceduresMonitorItems &pItems)
{
	INT  nIndex;
	INT  nItem[2];
	INT  nItems[2];
	UINT  nMaxCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tStartTime;
	CTimeSpan  tInterval;
	CPtrArray  pItemThreads;
	CTCProceduresMonitorItem  *pItem[2];
	CTCProceduresMonitorItemThread  *pItemThread;

	if (Lock())
	{
		for (nItem[0] = 0, nItems[0] = (INT)m_pItems.GetSize(), nIndex = GetCurProcedure(); nItem[0] < nItems[0]; nItem[0]++)
		{
			for (nItem[1] = 0, nItems[1] = ((pItem[0] = m_pItems.GetAt(nItem[0]))) ? (INT)pItems.GetSize() : 0; nItem[1] < nItems[1]; nItem[1]++)
			{
				if ((pItem[1] = pItems.GetAt(nItem[1])) && pItem[0]->GetID() == pItem[1]->GetID() && pItem[0]->GetID() >= 0) break;
				continue;
			}
			if (nItem[1] == nItems[1])
			{
				if (pItem[0]->GetID() > 0)
				{
					if (nItem[0] < m_pItemThreads.GetSize())
					{
						if ((pItemThread = (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nItem[0])))
						{
							pItemThreads.Add(pItemThread->GetThreadHandle());
							pItemThread->Stop(FALSE);
						}
					}
				}
			}
		}
		Unlock();
	}
	for (; pItemThreads.GetSize() > 0; )
	{
		WaitForMultipleObjects((DWORD)pItemThreads.GetSize(), pItemThreads.GetData(), TRUE, INFINITE);
		break;
	}
	if (Lock())
	{
		for (nItem[0] = 0, nItems[0] = (INT)m_pItems.GetSize(); nItem[0] < nItems[0]; nItem[0]++)
		{
			for (nItem[1] = 0, nItems[1] = ((pItem[0] = m_pItems.GetAt(nItem[0]))) ? (INT)pItems.GetSize() : 0; nItem[1] < nItems[1]; nItem[1]++)
			{
				if ((pItem[1] = pItems.GetAt(nItem[1])) && pItem[0]->GetID() == pItem[1]->GetID() && pItem[0]->GetID() >= 0) break;
				continue;
			}
			if (nItem[1] == nItems[1])
			{
				if (pItem[0]->GetID() >= 0)
				{
					if (nItem[0] < m_pItemThreads.GetSize())
					{
						if ((pItemThread = (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nItem[0])))
						{
							pItemThread->Stop();
							delete pItemThread;
						}
						m_pItemThreads.RemoveAt(nItem[0]);
					}
					nIndex = (nItem[0] < nIndex) ? (nIndex - 1) : nIndex;
					m_pItems.RemoveAt(nItem[0]);
					delete pItem[0];
					nItems[0]--;
					nItem[0]--;
				}
			}
		}
		for (nItem[0] = 0, nItems[0] = (INT)pItems.GetSize(); nItem[0] < nItems[0]; nItem[0]++)
		{
			for (nItem[1] = 0, nItems[1] = ((pItem[0] = pItems.GetAt(nItem[0]))) ? (INT)m_pItems.GetSize() : -1; nItem[1] < nItems[1]; nItem[1]++)
			{
				if ((pItem[1] = m_pItems.GetAt(nItem[1])) && pItem[0]->GetID() == pItem[1]->GetID() && pItem[0]->GetID() >= 0) break;
				continue;
			}
			if (nItem[1] == nItems[1])
			{
				if ((pItem[1] = new CTCProceduresMonitorItem))
				{
					if (pItem[1]->Copy(pItem[0], nItem[0] < nItems[0]))
					{
						if (pItem[1]->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATTIME)
						{
							if (pItem[1]->GetExecutionStartTime() == 0 && pItem[1]->GetTriggerTime() < CTime::GetCurrentTime().GetTime())
							{
								pItem[1]->SetExecutionStartTime(-pItem[1]->GetTriggerTime().GetTime());
								pItem[1]->SetExecutionEndTime(0);
							}
						}
						if (pItem[1]->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATDAILYTIME)
						{
							if ((tTime = CTime::GetCurrentTime().GetTime()).GetTime() / SECONDSPERDAY > pItem[1]->GetExecutionStartTime().GetTime() / SECONDSPERDAY  &&  pItem[1]->GetDailyTriggerTime().GetTotalSeconds() % SECONDSPERDAY < tTime.GetTime() % SECONDSPERDAY)
							{
								pItem[1]->SetExecutionStartTime(-(SECONDSPERDAY*(tTime.GetTime() / SECONDSPERDAY) + pItem[1]->GetDailyTriggerTime().GetTotalSeconds() % SECONDSPERDAY));
								pItem[1]->SetExecutionEndTime(0);
							}
						}
						for (tTime = CTime::GetCurrentTime().GetTime(); pItem[1]->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATINTERVAL; )
						{
							if (pItem[1]->GetTriggerInterval(tStartTime, tInterval) && tTime > tStartTime  &&  pItem[1]->GetExecutionStartTime().GetTime() < tStartTime.GetTime() + tInterval.GetTotalSeconds()*((tTime.GetTime() - tStartTime.GetTime()) / tInterval.GetTotalSeconds()))
							{
								pItem[1]->SetExecutionStartTime(-(tStartTime.GetTime() + tInterval.GetTotalSeconds()*((tTime.GetTime() - tStartTime.GetTime()) / tInterval.GetTotalSeconds())));
								pItem[1]->SetExecutionEndTime(0);
								break;
							}
							if (pItem[1]->GetTriggerInterval(tStartTime, tInterval, nMaxCount) && tTime > tStartTime  &&  pItem[1]->GetExecutionStartTime().GetTime() < tStartTime.GetTime() + tInterval.GetTotalSeconds()*min((tTime.GetTime() - tStartTime.GetTime()) / tInterval.GetTotalSeconds(), nMaxCount - 1))
							{
								pItem[1]->SetExecutionStartTime(-(tStartTime.GetTime() + tInterval.GetTotalSeconds()*min((tTime.GetTime() - tStartTime.GetTime()) / tInterval.GetTotalSeconds(), nMaxCount - 1)));
								pItem[1]->SetExecutionEndTime(0);
								break;
							}
							if (pItem[1]->GetTriggerInterval(tStartTime, tInterval, tStopTime) && tTime > tStartTime  &&  pItem[1]->GetExecutionStartTime().GetTime() < tStartTime.GetTime() + tInterval.GetTotalSeconds()*((min(tTime.GetTime(), tStopTime.GetTime()) - tStartTime.GetTime()) / tInterval.GetTotalSeconds()))
							{
								pItem[1]->SetExecutionStartTime(-(tStartTime.GetTime() + tInterval.GetTotalSeconds()*((min(tTime.GetTime(), tStopTime.GetTime()) - tStartTime.GetTime()) / tInterval.GetTotalSeconds())));
								pItem[1]->SetExecutionEndTime(0);
								break;
							}
							break;
						}
						for (pItem[1]->SetID(GenerateItemID()); IsMonitoring(); )
						{
							if ((pItemThread = new CTCProceduresMonitorItemThread(pItem[1])))
							{
								if (pItemThread->Start(GetParentDisplay(), m_pTCProcessEngine, m_pTCEnvironment, FALSE))
								{
									m_pItemThreads.InsertAt(nItem[0], pItemThread, 1);
									break;
								}
								delete pItemThread;
							}
							pItem[1]->SetID(-1);
							break;
						}
						if (pItem[1]->GetID() >= 0)
						{
							nIndex = (nItem[0] <= nIndex) ? (nIndex + 1) : nIndex;
							m_pItems.InsertAt(nItem[0], pItem[1], 1);
							continue;
						}
					}
					delete pItem[1];
				}
			}
			if ((pItem[1] = m_pItems.GetAt(nItem[1])) && pItem[1]->Copy(pItem[0], FALSE))
			{
				for (pItem[1]->SetExecutionStartTime((pItem[0]->GetExecutionStartTime() > 0) ? pItem[1]->GetExecutionStartTime() : 0), pItem[1]->SetExecutionEndTime((pItem[0]->GetExecutionEndTime() > 0) ? pItem[1]->GetExecutionEndTime() : 0); pItem[1]->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATTIME; )
				{
					if (pItem[1]->GetExecutionStartTime() == 0 && pItem[1]->GetTriggerTime() < CTime::GetCurrentTime().GetTime())
					{
						pItem[1]->SetExecutionStartTime(-pItem[1]->GetTriggerTime().GetTime());
						pItem[1]->SetExecutionEndTime(0);
					}
					break;
				}
				if (pItem[1]->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATDAILYTIME)
				{
					if ((tTime = CTime::GetCurrentTime().GetTime()).GetTime() / SECONDSPERDAY > pItem[1]->GetExecutionStartTime().GetTime() / SECONDSPERDAY  &&  pItem[1]->GetDailyTriggerTime().GetTotalSeconds() % SECONDSPERDAY < tTime.GetTime() % SECONDSPERDAY)
					{
						pItem[1]->SetExecutionStartTime(-(SECONDSPERDAY*(tTime.GetTime() / SECONDSPERDAY) + pItem[1]->GetDailyTriggerTime().GetTotalSeconds() % SECONDSPERDAY));
						pItem[1]->SetExecutionEndTime(0);
					}
				}
				for (tTime = CTime::GetCurrentTime().GetTime(); pItem[1]->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATINTERVAL; )
				{
					if (pItem[1]->GetTriggerInterval(tStartTime, tInterval) && tTime > tStartTime  &&  pItem[1]->GetExecutionStartTime().GetTime() < tStartTime.GetTime() + tInterval.GetTotalSeconds()*((tTime.GetTime() - tStartTime.GetTime()) / tInterval.GetTotalSeconds()))
					{
						pItem[1]->SetExecutionStartTime(-(tStartTime.GetTime() + tInterval.GetTotalSeconds()*((tTime.GetTime() - tStartTime.GetTime()) / tInterval.GetTotalSeconds())));
						pItem[1]->SetExecutionEndTime(0);
						break;
					}
					if (pItem[1]->GetTriggerInterval(tStartTime, tInterval, nMaxCount) && tTime > tStartTime  &&  pItem[1]->GetExecutionStartTime().GetTime() < tStartTime.GetTime() + tInterval.GetTotalSeconds()*min((tTime.GetTime() - tStartTime.GetTime()) / tInterval.GetTotalSeconds(), nMaxCount - 1))
					{
						pItem[1]->SetExecutionStartTime(-(tStartTime.GetTime() + tInterval.GetTotalSeconds()*min((tTime.GetTime() - tStartTime.GetTime()) / tInterval.GetTotalSeconds(), nMaxCount - 1)));
						pItem[1]->SetExecutionEndTime(0);
						break;
					}
					if (pItem[1]->GetTriggerInterval(tStartTime, tInterval, tStopTime) && tTime > tStartTime  &&  pItem[1]->GetExecutionStartTime().GetTime() < tStartTime.GetTime() + tInterval.GetTotalSeconds()*((min(tTime.GetTime(), tStopTime.GetTime()) - tStartTime.GetTime()) / tInterval.GetTotalSeconds()))
					{
						pItem[1]->SetExecutionStartTime(-(tStartTime.GetTime() + tInterval.GetTotalSeconds()*((min(tTime.GetTime(), tStopTime.GetTime()) - tStartTime.GetTime()) / tInterval.GetTotalSeconds())));
						pItem[1]->SetExecutionEndTime(0);
						break;
					}
					break;
				}
				for (; (pItemThread = (nItem[1] < m_pItemThreads.GetSize()) ? (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nItem[1]) : (CTCProceduresMonitorItemThread *)NULL); )
				{
					pItemThread->Update(pItem[1]);
					break;
				}
				continue;
			}
			break;
		}
		ShowContent(nIndex);
		Unlock();
		return((nItem[0] == nItems[0]) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CTCProceduresMonitorListView::GetProcedures(CTCProceduresMonitorItems &pItems) CONST
{
	INT  nItem;
	INT  nItems;
	CTCProceduresMonitorItem  *pItem;
	CTextViewLock  cLock(m_pwndList);

	for (nItem = 0, nItems = (pItems.Copy(&m_pItems)) ? (INT)pItems.GetSize() : -1; nItem < nItems; nItem++)
	{
		if ((pItem = pItems.GetAt(nItem)) && pItem->GetID() < 0)
		{
			pItems.RemoveAt(nItem);
			delete pItem;
			nItems--;
			nItem--;
		}
	}
	return((nItems >= 0) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorListView::UpdateProcedure(CONST CTCItem *pTCItem)
{
	CTCItem  *pItem;
	CTextViewLock  cLock(m_pwndList);

	if (IsMonitoring())
	{
		if ((pItem = new CTCItem))
		{
			if (pTCItem->GetType() == TCITEM_TYPE_PROCEDURE)
			{
				if (pItem->Copy(pTCItem) && m_pTCItems.Add(pItem) >= 0)
				{
					SetTimer(TCPROCEDURESMONITORLISTVIEW_STARTPROCEDURE_TIMERID, TCPROCEDURESMONITORLISTVIEW_STARTPROCEDURE_TIMEOUT, NULL);
					return TRUE;
				}
			}
			delete pItem;
		}
	}
	return FALSE;
}

BOOL CTCProceduresMonitorListView::StartProcedure(INT nIndex)
{
	CTCProceduresMonitorItem  *pItem[2];
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	if ((pItem[0] = m_pItems.GetAt(nIndex)))
	{
		for (; pItem[0]->IsAlerted(); )
		{
			AcknowledgeProcedure(nIndex, TRUE);
			break;
		}
		if ((pItem[1] = new CTCProceduresMonitorItem))
		{
			if ((pItemThread = (pItem[1]->Copy(pItem[0]) && nIndex < m_pItemThreads.GetSize()) ? (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nIndex) : (CTCProceduresMonitorItemThread *)NULL))
			{
				for (pItem[1]->SetTriggerType(TCPROCEDURESMONITORITEM_TRIGGERTYPE_MANUAL); pItemThread->Update(pItem[1]); )
				{
					delete pItem[1];
					return TRUE;
				}
			}
			delete pItem[1];
		}
	}
	return FALSE;
}

BOOL CTCProceduresMonitorListView::CanStartProcedure(INT nIndex) CONST
{
	CTCProceduresMonitorItem  *pItem;
	CTextViewLock  cLock(m_pwndList);

	return(((pItem = (GetTelecommandingUplinkState() & TCSERVICE_COMMANDHANDLERSTATE_RUNNING) ? m_pItems.GetAt(nIndex) : (CTCProceduresMonitorItem *)NULL)) ? (pItem->IsManualExecutionAllowed() && !pItem->IsAlerted()) : FALSE);
}

BOOL CTCProceduresMonitorListView::IsProcedureRunning(INT nIndex) CONST
{
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	return(((pItemThread = (nIndex >= 0 && nIndex < m_pItemThreads.GetSize()) ? (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nIndex) : (CTCProceduresMonitorItemThread *)NULL)) ? pItemThread->IsRunning() : FALSE);
}

BOOL CTCProceduresMonitorListView::SuspendProcedure(INT nIndex)
{
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	if ((pItemThread = (nIndex >= 0 && nIndex < m_pItemThreads.GetSize()) ? (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nIndex) : (CTCProceduresMonitorItemThread *)NULL))
	{
		pItemThread->Suspend();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorListView::ResumeProcedure(INT nIndex)
{
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	if ((pItemThread = (nIndex >= 0 && nIndex < m_pItemThreads.GetSize()) ? (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nIndex) : (CTCProceduresMonitorItemThread *)NULL))
	{
		pItemThread->Resume(FALSE);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorListView::IsProcedureSuspended(INT nIndex) CONST
{
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	return(((pItemThread = (nIndex >= 0 && nIndex < m_pItemThreads.GetSize()) ? (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nIndex) : (CTCProceduresMonitorItemThread *)NULL)) ? pItemThread->IsSuspended() : FALSE);
}

BOOL CTCProceduresMonitorListView::IsProcedureDisabled(INT nIndex) CONST
{
	CTCProceduresMonitorItem  *pItem;
	CTextViewLock  cLock(m_pwndList);

	return(((pItem = m_pItems.GetAt(nIndex))) ? !pItem->IsEnabled() : FALSE);
}

BOOL CTCProceduresMonitorListView::StepIntoProcedure(INT nIndex, INT nThreadID)
{
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	if ((pItemThread = (nIndex >= 0 && nIndex < m_pItemThreads.GetSize()) ? (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nIndex) : (CTCProceduresMonitorItemThread *)NULL))
	{
		pItemThread->StepIntoExecutionBlock(nThreadID);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorListView::CanStepIntoProcedure(INT nIndex, INT nThreadID) CONST
{
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	return(((pItemThread = (nIndex >= 0 && nIndex < m_pItemThreads.GetSize()) ? (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nIndex) : (CTCProceduresMonitorItemThread *)NULL)) ? pItemThread->CanStepIntoExecutionBlock(nThreadID) : FALSE);
}

BOOL CTCProceduresMonitorListView::StepOverProcedure(INT nIndex, INT nThreadID)
{
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	if ((pItemThread = (nIndex >= 0 && nIndex < m_pItemThreads.GetSize()) ? (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nIndex) : (CTCProceduresMonitorItemThread *)NULL))
	{
		pItemThread->StepOverExecutionBlock(nThreadID);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorListView::CanStepOverProcedure(INT nIndex, INT nThreadID) CONST
{
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	return(((pItemThread = (nIndex >= 0 && nIndex < m_pItemThreads.GetSize()) ? (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nIndex) : (CTCProceduresMonitorItemThread *)NULL)) ? pItemThread->CanStepOverExecutionBlock(nThreadID) : FALSE);
}

BOOL CTCProceduresMonitorListView::StepOutProcedure(INT nIndex, INT nThreadID)
{
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	if ((pItemThread = (nIndex >= 0 && nIndex < m_pItemThreads.GetSize()) ? (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nIndex) : (CTCProceduresMonitorItemThread *)NULL))
	{
		pItemThread->StepOutExecutionBlock(nThreadID);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorListView::CanStepOutProcedure(INT nIndex, INT nThreadID) CONST
{
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	return(((pItemThread = (nIndex >= 0 && nIndex < m_pItemThreads.GetSize()) ? (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nIndex) : (CTCProceduresMonitorItemThread *)NULL)) ? pItemThread->CanStepOutExecutionBlock(nThreadID) : FALSE);
}

BOOL CTCProceduresMonitorListView::ResetProcedure(INT nIndex)
{
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	if ((pItemThread = (nIndex >= 0 && nIndex < m_pItemThreads.GetSize()) ? (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nIndex) : (CTCProceduresMonitorItemThread *)NULL))
	{
		pItemThread->Reset();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorListView::CanResetProcedure(INT nIndex) CONST
{
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	return(((pItemThread = (nIndex >= 0 && nIndex < m_pItemThreads.GetSize()) ? (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nIndex) : (CTCProceduresMonitorItemThread *)NULL)) ? pItemThread->CanReset() : FALSE);
}

BOOL CTCProceduresMonitorListView::CanBreakProcedure(INT nIndex) CONST
{
	CTCProceduresMonitorItem  *pItem;
	CTextViewLock  cLock(m_pwndList);

	return(((pItem = m_pItems.GetAt(nIndex))) ? pItem->AreExecutionBreaksAllowed() : FALSE);
}

BOOL CTCProceduresMonitorListView::AbortProcedure(INT nIndex)
{
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	if ((pItemThread = (nIndex >= 0 && nIndex < m_pItemThreads.GetSize()) ? (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nIndex) : (CTCProceduresMonitorItemThread *)NULL))
	{
		pItemThread->Abort();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorListView::UpdateProcedure(INT nIndex)
{
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	if ((pItemThread = ((nIndex = (nIndex < 0) ? GetCurProcedure() : nIndex) >= 0 && nIndex < m_pItemThreads.GetSize()) ? (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nIndex) : (CTCProceduresMonitorItemThread *)NULL))
	{
		pItemThread->Refresh();
		return TRUE;
	}
	return FALSE;
}
BOOL CTCProceduresMonitorListView::UpdateProcedure(INT nIndex, UINT nTriggerType, UINT nRunningState, CONST CTimeKey &tExecutionStartTime, CONST CTimeKey &tExecutionEndTime, UINT nExecutionCount)
{
	INT  nColumn;
	INT  nColumns;
	UINT  nTriggerCycles;
	CString  szTriggerType;
	CString  szRunningState;
	CString  szTimeInterval;
	CTimeKey  tTriggerStartTime;
	CTimeKey  tTriggerEndTime;
	CTimeSpan  tTriggerInterval;
	CStringArray  szColumns;
	CStringTools  cStringTools;
	CTCProceduresMonitorItem  *pItem;
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	if ((pItem = m_pItems.GetAt((nIndex = FindItem(nIndex)))))
	{
		if (tExecutionStartTime > 0 && nExecutionCount > 0)
		{
			pItem->SetExecutionStartTime(tExecutionStartTime);
			pItem->SetExecutionEndTime(tExecutionEndTime);
			pItem->SetExecutionCount(nExecutionCount);
		}
		for (nColumn = 0, nColumns = (m_pwndList->GetColumns(szColumns)) ? (INT)szColumns.GetSize() : 0, pItem->SetTriggerType(nTriggerType), pItem->SetRunningState(nRunningState), szRunningState = (nRunningState == TCPROCEDURE_RUNNINGSTATE_NOTRUNNING) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_RUNNINGSTATE_NOTRUNNING) : EMPTYSTRING, szRunningState = (nRunningState == TCPROCEDURE_RUNNINGSTATE_RUNNING) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_RUNNINGSTATE_RUNNING) : szRunningState, szRunningState = (nRunningState == TCPROCEDURE_RUNNINGSTATE_STOPPED) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_RUNNINGSTATE_STOPPED) : szRunningState; nColumn < nColumns; nColumn++)
		{
			if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_TRIGGERTYPE))
			{
				if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_NONE)
				{
					szTriggerType = STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_NONE);
					szTriggerType += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
				}
				if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_MANUAL)
				{
					szTriggerType = STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_MANUAL);
					szTriggerType += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
				}
				if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_AUTOMATIC)
				{
					szTriggerType = STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_AUTOMATIC);
					szTriggerType += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
				}
				if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_IMMEDIATELY)
				{
					szTriggerType = STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_IMMEDIATELY);
					szTriggerType += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
				}
				if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATSTARTUP)
				{
					szTriggerType = STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_ATSTARTUP);
					szTriggerType += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
				}
				if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATTIME)
				{
					szTriggerType.Format(STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_ATTIME), (LPCTSTR)pItem->GetTriggerTime().FormatGmt());
					szTriggerType += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
				}
				if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATDAILYTIME)
				{
					szTriggerType.Format(STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_ATDAILYTIME), (LPCTSTR)CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + pItem->GetDailyTriggerTime().GetTotalSeconds()).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT)));
					szTriggerType += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
				}
				if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATINTERVAL)
				{
					if (pItem->GetTriggerInterval(tTriggerStartTime, tTriggerInterval) || pItem->GetTriggerInterval(tTriggerStartTime, tTriggerInterval, tTriggerEndTime) || pItem->GetTriggerInterval(tTriggerStartTime, tTriggerInterval, nTriggerCycles))
					{
						szTriggerType.Format(STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_ATINTERVAL), (LPCTSTR)cStringTools.ConvertLongIntToStructuredString(tTriggerInterval.GetTotalSeconds()), (LPCTSTR)tTriggerStartTime.FormatGmt());
						szTriggerType += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
					}
				}
				if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATEVENT)
				{
					szTriggerType.Format(STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_ATEVENT), (LPCTSTR)pItem->GetTriggerEvent());
					szTriggerType += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
				}
				m_pwndList->SetText(nIndex, nColumn, szTriggerType);
				continue;
			}
			if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_RUNNINGSTATE))
			{
				m_pwndList->SetText(nIndex, nColumn, szRunningState);
				continue;
			}
			if (tExecutionStartTime != 0 && nExecutionCount > 0)
			{
				if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_STARTTIME))
				{
					m_pwndList->SetText(nIndex, nColumn, (tExecutionStartTime < 0) ? (CTimeKey(-tExecutionStartTime.GetTime()).FormatGmt() + STRING(IDS_TCPROCEDURESMONITOR_LIST_TIMESKIPPEDFLAG)) : tExecutionStartTime.FormatGmt());
					continue;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ENDTIME))
				{
					szTimeInterval.Format(STRING(IDS_TCPROCEDURESMONITOR_LIST_TIMEINTERVALFORMAT), (LPCTSTR)cStringTools.ConvertLongIntToStructuredString(max(tExecutionEndTime.GetTime() - tExecutionStartTime.GetTime(), 0)));
					m_pwndList->SetText(nIndex, nColumn, (tExecutionEndTime > 0) ? (tExecutionEndTime.FormatGmt() + szTimeInterval) : EMPTYSTRING);
					continue;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONCOUNT))
				{
					m_pwndList->SetText(nIndex, nColumn, cStringTools.ConvertIntToStructuredString(nExecutionCount));
					continue;
				}
			}
		}
		if (nRunningState == TCPROCEDURE_RUNNINGSTATE_NOTRUNNING)
		{
			if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_AUTOMATIC  &&  pItem->GetExecutionStartTime() > 0 && !pItem->IsAlerted())
			{
				for (; (pItemThread = (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nIndex)) && !pItemThread->CheckExecution(); )
				{
					SetTimer(TCPROCEDURESMONITORLISTVIEW_STOPPROCEDURE_TIMERID, TCPROCEDURESMONITORLISTVIEW_STOPPROCEDURE_TIMEOUT, NULL);
					break;
				}
			}
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorListView::AlertProcedure(INT nIndex, UINT nType, LPCTSTR pszAlert)
{
	CTimeTag  tAlertTime;

	return AlertProcedure(nIndex, nType, pszAlert, tAlertTime);
}
BOOL CTCProceduresMonitorListView::AlertProcedure(INT nIndex, UINT nType, LPCTSTR pszAlert, CONST CTimeTag &tAlertTime)
{
	WORD  wVoiceAge;
	WORD  wVoiceGender;
	UINT  nNotification;
	UINT  nNotifications;
	UINT  nAlertType;
	DWORD  dwPitch;
	DWORD  dwVolume;
	DWORD  dwPlayback;
	CString  szAdapter;
	CString  szSpeaker;
	CString  szMessage;
	CString  szAlertMessage;
	CTimeTag  tAlertMessage;
	CEventObject  *pEvent;
	CStringArray  szNotifications;
	CTCProceduresMonitorItem  *pItem;
	CAuditionProfiles  pAuditionProfiles;
	CAuditionProfileInfo  *pAuditionProfileInfo;
	CTextViewLock  cLock(m_pwndList);

	if ((pEvent = new CEventObject))
	{
		if (nType == TCPROCEDURESMONITORITEM_ALERTTYPE_ALERT)
		{
			if (TranslateAlertLoggingInfo(pEvent, pszAlert))
			{
				ReportEvent(pEvent);
				return TRUE;
			}
		}
		delete pEvent;
	}
	if ((pItem = m_pItems.GetAt((nIndex = (FindItem(nIndex) < 0) ? CreateItem(nIndex) : FindItem(nIndex)))))
	{
		if (pItem->IsAcknowledgmentEnabled(nType) && pItem->GetAlertMessage(nAlertType, szAlertMessage, tAlertMessage) >= 0)
		{
			for (pItem->AddAlertMessage(nType, pszAlert, tAlertTime), pItem->Alert(); nType != nAlertType || pszAlert != szAlertMessage || tAlertTime != tAlertMessage; )
			{
				ShowContent();
				break;
			}
		}
		if (pItem->GetID() < 0)
		{
			if (!pItem->IsAlerted()) DestroyItem(pItem->GetID());
			ShowContent();
			return TRUE;
		}
		for (szMessage.Format(STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGE_FORMAT), (LPCTSTR)pItem->GetName(), pszAlert); (pAuditionProfileInfo = (GetAuditionProfiles(pAuditionProfiles)) ? pAuditionProfiles.GetAt(pAuditionProfiles.Find(pItem->GetAudition(nType))) : (CAuditionProfileInfo *)NULL); )
		{
			for (pAuditionProfileInfo->GetAdapterInfo(szAdapter, dwVolume, dwPitch, dwPlayback), pAuditionProfileInfo->GetVoiceSound(szSpeaker, wVoiceGender, wVoiceAge); (pEvent = new CEventObject); )
			{
				pEvent->SetCategory(EVENT_CATEGORY_SYSTEM);
				pEvent->SetType(STRING(MINTCPROCEDURESMONITORALERTTYPE + nType));
				pEvent->SetSubtype(STRING(IDS_TCPROCEDURESMONITOR_ALERTSUBTYPE_DEFAULT));
				pEvent->SetAudition(pAuditionProfileInfo->GetAudition());
				pEvent->SetAudioInfo(szAdapter, dwVolume, dwPitch, dwPlayback);
				pEvent->SetAuditBeep(pAuditionProfileInfo->GetBeepSound());
				pEvent->SetAuditWave(pAuditionProfileInfo->GetWaveSound());
				pEvent->SetAuditVoice(szSpeaker, wVoiceGender, wVoiceAge);
				pEvent->SetAuditColor(pItem->GetAuditionColor(nType));
				pEvent->SetAuditTime(tAlertTime.GetTime());
				pEvent->SetUser(GetAccountUserName());
				pEvent->SetMessage(szMessage);
				pEvent->Acknowledge(!pItem->IsAuditionBlinkingEnabled(nType));
				pEvent->Show(TRUE);
				ReportEvent(pEvent);
				break;
			}
			break;
		}
		for (nNotification = 0, nNotifications = pItem->GetNotifications(nType, szNotifications); nNotification < nNotifications; nNotification++)
		{
			DoNotification(szNotifications.GetAt(nNotification), szMessage);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorListView::AcknowledgeProcedure(INT nIndex, BOOL bAll)
{
	UINT  nAlertType;
	CString  szAlert;
	CTimeTag  tAlertTime;
	CTCProceduresMonitorItem  *pItem;
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	if ((pItem = m_pItems.GetAt(nIndex)) && pItem->IsAlerted())
	{
		do
		{
			if (pItem->GetAlertMessage(nAlertType, szAlert, tAlertTime))
			{
				pItem->RemoveAlertMessage();
				continue;
			}
			break;
		} while ((!bAll  &&  !pItem->IsAcknowledgmentEnabled(nAlertType)) || bAll);
		if (!pItem->GetAlertMessage(nAlertType, szAlert))
		{
			if (pItem->GetID() < 0)
			{
				DestroyItem(pItem->GetID());
				ShowContent();
				return TRUE;
			}
			for (pItem->Alert(FALSE); pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_AUTOMATIC && pItem->GetExecutionStartTime() > 0; )
			{
				if ((pItemThread = (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nIndex)) && !pItemThread->CheckExecution())
				{
					m_pItemThreads.RemoveAt(nIndex);
					m_pItems.RemoveAt(nIndex);
					delete pItemThread;
					delete pItem;
				}
				break;
			}
		}
		ShowContent();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorListView::CanAcknowledgeProcedure(INT nIndex) CONST
{
	UINT  nAlertType;
	CString  szAlertMessage;
	CTCProceduresMonitorItem  cItem;
	CTextViewLock  cLock(m_pwndList);

	return(GetProcedureInfo(nIndex, &cItem) && cItem.GetAlertMessage(nAlertType, szAlertMessage) && nAlertType != TCPROCEDURESMONITORITEM_ALERTTYPE_AUTHORIZATION);
}

BOOL CTCProceduresMonitorListView::AcknowledgeAllProcedures()
{
	INT  nItem;
	INT  nItems;
	CTCProceduresMonitorItem  *pItem;
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	for (nItem = 0, nItems = (INT)m_pItems.GetSize(); nItem < nItems; nItem++)
	{
		if ((pItem = m_pItems.GetAt(nItem)) && pItem->IsAlerted())
		{
			for (pItem->RemoveAllAlertMessages(), pItem->Alert(FALSE); pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_AUTOMATIC && pItem->GetExecutionStartTime() > 0; )
			{
				if ((pItemThread = (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nItem)) && !pItemThread->CheckExecution())
				{
					m_pItemThreads.RemoveAt(nItem);
					m_pItems.RemoveAt(nItem);
					delete pItemThread;
					delete pItem;
					nItems--;
					nItem--;
				}
				break;
			}
			ShowContent();
		}
	}
	return TRUE;
}

BOOL CTCProceduresMonitorListView::SetProcedureInfo(INT nIndex, CONST CTCProceduresMonitorItem *pItem, BOOL bAll)
{
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	if ((pItemThread = (nIndex >= 0 && nIndex < m_pItemThreads.GetSize()) ? (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nIndex) : (CTCProceduresMonitorItemThread *)NULL))
	{
		if (m_pItems.GetAt(nIndex)->Copy(pItem, bAll) && pItemThread->Update(pItem))
		{
			for (ShowContent(); pItem->IsAlerted(); )
			{
				m_pwndList->StartTextBlinking(nIndex);
				break;
			}
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTCProceduresMonitorListView::GetProcedureInfo(INT nIndex, CTCProceduresMonitorItem *pItem, BOOL bAll) CONST
{
	CTextViewLock  cLock(m_pwndList);

	return((nIndex >= 0 && nIndex < m_pItems.GetSize()) ? pItem->Copy(m_pItems.GetAt(nIndex), bAll) : FALSE);
}
BOOL CTCProceduresMonitorListView::GetProcedureInfo(INT nIndex, CDatabaseTCProcedure *pProcedure) CONST
{
	CTCProceduresMonitorItem  *pItem;
	CTextViewLock  cLock(m_pwndList);

	return(((pItem = m_pItems.GetAt(nIndex))) ? pProcedure->Copy(pItem) : FALSE);
}
BOOL CTCProceduresMonitorListView::GetProcedureInfo(INT nIndex, CString &szName, UINT &nMode, UINT &nState) CONST
{
	CTCProceduresMonitorItem  *pItem;
	CTextViewLock  cLock(m_pwndList);

	if ((pItem = m_pItems.GetAt(nIndex)))
	{
		szName = pItem->GetName();
		nMode = pItem->GetExecutionMode();
		nState = pItem->GetRunningState();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorListView::SetCurProcedure(INT nIndex)
{
	return m_pwndList->SetCurText(nIndex);
}

INT CTCProceduresMonitorListView::GetCurProcedure() CONST
{
	return m_pwndList->GetCurText();
}

UINT CTCProceduresMonitorListView::GetProcedureCount() CONST
{
	return m_pwndList->GetTextCount();
}

BOOL CTCProceduresMonitorListView::StartMonitoring(CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, BOOL bStartup)
{
	INT  nItem;
	INT  nItems;
	UINT  nMaxCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tStartTime;
	CTimeSpan  tInterval;
	CTCProceduresMonitorItem  *pItem;
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	for (nItem = 0, nItems = (INT)m_pItems.GetSize(), m_pTCProcessEngine = pTCProcessEngine, m_pTCEnvironment = pTCEnvironment; nItem < nItems; nItem++)
	{
		if ((pItem = m_pItems.GetAt(nItem)) != (CTCProceduresMonitorItem *)NULL)
		{
			if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATTIME)
			{
				if (pItem->GetExecutionStartTime() == 0 && pItem->GetTriggerTime() < CTime::GetCurrentTime().GetTime())
				{
					pItem->SetExecutionStartTime(-pItem->GetTriggerTime().GetTime());
					pItem->SetExecutionEndTime(0);
				}
			}
			if (pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATDAILYTIME)
			{
				if ((tTime = CTime::GetCurrentTime().GetTime()).GetTime() / SECONDSPERDAY > pItem->GetExecutionStartTime().GetTime() / SECONDSPERDAY  &&  pItem->GetDailyTriggerTime().GetTotalSeconds() % SECONDSPERDAY < tTime.GetTime() % SECONDSPERDAY)
				{
					pItem->SetExecutionStartTime(-(SECONDSPERDAY*(tTime.GetTime() / SECONDSPERDAY) + pItem->GetDailyTriggerTime().GetTotalSeconds() % SECONDSPERDAY));
					pItem->SetExecutionEndTime(0);
				}
			}
			for (tTime = CTime::GetCurrentTime().GetTime(); pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATINTERVAL; )
			{
				if (pItem->GetTriggerInterval(tStartTime, tInterval) && tTime > tStartTime  &&  pItem->GetExecutionStartTime().GetTime() < tStartTime.GetTime() + tInterval.GetTotalSeconds()*((tTime.GetTime() - tStartTime.GetTime()) / tInterval.GetTotalSeconds()))
				{
					pItem->SetExecutionStartTime(-(tStartTime.GetTime() + tInterval.GetTotalSeconds()*((tTime.GetTime() - tStartTime.GetTime()) / tInterval.GetTotalSeconds())));
					pItem->SetExecutionEndTime(0);
					break;
				}
				if (pItem->GetTriggerInterval(tStartTime, tInterval, nMaxCount) && tTime > tStartTime  &&  pItem->GetExecutionStartTime().GetTime() < tStartTime.GetTime() + tInterval.GetTotalSeconds()*min((tTime.GetTime() - tStartTime.GetTime()) / tInterval.GetTotalSeconds(), nMaxCount - 1))
				{
					pItem->SetExecutionStartTime(-(tStartTime.GetTime() + tInterval.GetTotalSeconds()*min((tTime.GetTime() - tStartTime.GetTime()) / tInterval.GetTotalSeconds(), nMaxCount - 1)));
					pItem->SetExecutionEndTime(0);
					break;
				}
				if (pItem->GetTriggerInterval(tStartTime, tInterval, tStopTime) && tTime > tStartTime  &&  pItem->GetExecutionStartTime().GetTime() < tStartTime.GetTime() + tInterval.GetTotalSeconds()*((min(tTime.GetTime(), tStopTime.GetTime()) - tStartTime.GetTime()) / tInterval.GetTotalSeconds()))
				{
					pItem->SetExecutionStartTime(-(tStartTime.GetTime() + tInterval.GetTotalSeconds()*((min(tTime.GetTime(), tStopTime.GetTime()) - tStartTime.GetTime()) / tInterval.GetTotalSeconds())));
					pItem->SetExecutionEndTime(0);
					break;
				}
				break;
			}
			if ((pItemThread = new CTCProceduresMonitorItemThread(pItem)))
			{
				if (pItemThread->Start(GetParentDisplay(), pTCProcessEngine, pTCEnvironment, bStartup))
				{
					m_pItemThreads.InsertAt(nItem, pItemThread, 1);
					continue;
				}
				delete pItemThread;
			}
		}
		StopMonitoring();
		break;
	}
	ShowContent();
	return((nItem == nItems) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorListView::UpdateMonitoring(CONST CTMEnvironment *pTMEnvironment)
{
	INT  nItem;
	INT  nItems;
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	for (nItem = 0, nItems = (INT)m_pItemThreads.GetSize(); nItem < nItems; nItem++)
	{
		if ((pItemThread = (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nItem)))
		{
			pItemThread->Update(pTMEnvironment);
			continue;
		}
	}
	return TRUE;
}
BOOL CTCProceduresMonitorListView::UpdateMonitoring(LPCTSTR pszEvent)
{
	INT  nItem;
	INT  nItems;
	CTCProceduresMonitorItem  *pItem[2];
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	for (nItem = 0, nItems = (INT)m_pItems.GetSize(); nItem < nItems; nItem++)
	{
		if ((pItem[0] = m_pItems.GetAt(nItem)) && pItem[0]->GetTriggerEvent() == pszEvent)
		{
			if ((pItem[1] = new CTCProceduresMonitorItem) != (CTCProceduresMonitorItem *)NULL)
			{
				for (pItem[1]->Copy(pItem[0]), pItem[1]->EnableTriggerEvent(); (pItemThread = (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nItem)); )
				{
					pItemThread->Update(pItem[1]);
					break;
				}
				delete pItem[1];
				continue;
			}
			break;
		}
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorListView::IsMonitoring() CONST
{
	CTextViewLock  cLock(m_pwndList);

	return(m_pTCProcessEngine != (CTCProcessEngine *)NULL  &&  m_pTCEnvironment != (CTCEnvironment *)NULL);
}

BOOL CTCProceduresMonitorListView::StopMonitoring()
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nCount;
	INT  nThread;
	INT  nThreads;
	INT  nMessage;
	INT  nMessages;
	CTCItem  *pTCItem;
	CTCItems  pTCItems;
	CString  szMessage[3];
	CString  szMembership;
	CString  szTelecommand;
	CString  szTelecommands;
	CPtrArray  pItemThreads;
	CUIntArray  nTCItemIDs;
	CStringArray  szMessages;
	CTCProceduresMonitorItem  *pItem;
	CTCProceduresMonitorItemThread  *pItemThread;

	if (Lock())
	{
		for (nThread = 0, nThreads = (INT)m_pItemThreads.GetSize(); nThread < nThreads; nThread++)
		{
			if ((pItemThread = (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nThread)))
			{
				pItemThreads.Add(pItemThread->GetThreadHandle());
				pItemThread->Stop(FALSE);
			}
		}
		Unlock();
	}
	for (; pItemThreads.GetSize() > 0; )
	{
		WaitForMultipleObjects((DWORD)pItemThreads.GetSize(), pItemThreads.GetData(), TRUE, INFINITE);
		break;
	}
	if (Lock())
	{
		for (nItem = 0, nItems = (INT)m_pItems.GetSize(); nItem < nItems; nItem++)
		{
			if ((pItem = m_pItems.GetAt(nItem)) != (CTCProceduresMonitorItem *)NULL)
			{
				for (pItem->EnumAuthorizableTelecommands(pTCItems); pTCItems.GetSize() > 0; )
				{
					for (nIndex = 0, nCount = pTCItems.Collect(0, nTCItemIDs), szTelecommands.Empty(); nIndex < nCount; nIndex++)
					{
						if ((pTCItem = pTCItems.GetAt(nTCItemIDs.GetAt(nIndex))) != (CTCItem *)NULL)
						{
							szTelecommand.Format(STRING(IDS_TCPROCEDURESMONITOR_MESSAGE_TELECOMMAND_FORMAT), (LPCTSTR)pTCItem->GetName());
							szTelecommands += (!szTelecommands.IsEmpty()) ? (STRING(IDS_TCPROCEDURESMONITOR_MESSAGE_TELECOMMAND_DELIMITER) + szTelecommand) : szTelecommand;
							szMembership = (!nIndex) ? pTCItem->GetMembership() : szMembership;
						}
					}
					for (nIndex = 0, szMessage[0].Format(STRING(IDS_TCPROCEDURESMONITOR_MESSAGE_AUTHORIZATIONDENIAL), (LPCTSTR)szTelecommands), szMessage[1].Format(STRING(IDS_TCPROCEDURESMONITOR_MESSAGE_AUTHORIZATIONMEMBERDENIAL), (LPCTSTR)szTelecommands, (LPCTSTR)szMembership), szMessage[2].Format(STRING(IDS_TCPROCEDURESMONITOR_MESSAGE_AUTHORIZATIONMEMBERSDENIAL), (LPCTSTR)szTelecommands, (LPCTSTR)szMembership), szMessages.Add((!szMembership.IsEmpty()) ? ((nTCItemIDs.GetSize() > 1) ? szMessage[2] : szMessage[1]) : szMessage[0]); nIndex < nCount; nIndex++)
					{
						if ((pTCItem = pTCItems.GetAt(nTCItemIDs.GetAt(nIndex) - nIndex)))
						{
							pTCItems.RemoveAt(nTCItemIDs.GetAt(nIndex) - nIndex);
							delete pTCItem;
						}
					}
				}
			}
		}
		while (m_pItemThreads.GetSize() > 0)
		{
			if ((pItemThread = (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(m_pItemThreads.GetUpperBound())))
			{
				pItemThread->Stop();
				delete pItemThread;
			}
			m_pItemThreads.RemoveAt(m_pItemThreads.GetUpperBound());
		}
		for (nMessage = 0, nMessages = (INT)szMessages.GetSize(), m_pTCProcessEngine = (CTCProcessEngine *)NULL, m_pTCEnvironment = (CTCEnvironment *)NULL; nMessage < nMessages; nMessage++)
		{
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessages.GetAt(nMessage), (nMessage == nMessages - 1) ? TRUE : FALSE);
			continue;
		}
		Unlock();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorListView::SetTelecommandingMode(UINT nMode)
{
	m_nTelecommandingMode = nMode;
	return TRUE;
}

UINT CTCProceduresMonitorListView::GetTelecommandingMode() CONST
{
	return m_nTelecommandingMode;
}

BOOL CTCProceduresMonitorListView::SetTelecommandingChecks(UINT nFlags)
{
	m_nTelecommandingFlags = nFlags;
	return TRUE;
}

UINT CTCProceduresMonitorListView::GetTelecommandingChecks() CONST
{
	return m_nTelecommandingFlags;
}

BOOL CTCProceduresMonitorListView::SetTelecommandingState(UINT nState)
{
	m_nTelecommandingState = nState & ~TCPROCEDURESMONITOR_STATE_IDLE;
	return TRUE;
}

UINT CTCProceduresMonitorListView::GetTelecommandingState() CONST
{
	INT  nItem;
	INT  nItems;
	UINT  nState;
	CTCProceduresMonitorItem  *pItem;
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	for (nItem = 0, nItems = (INT)m_pItems.GetSize(), nState = m_nTelecommandingState; nItem < nItems; nItem++)
	{
		if ((pItem = m_pItems.GetAt(nItem)) != (CTCProceduresMonitorItem *)NULL  &&  pItem->HasAuthorizableTelecommands()) break;
		if ((pItemThread = (nItem >= 0 && nItem < m_pItemThreads.GetSize()) ? (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nItem) : (CTCProceduresMonitorItemThread *)NULL) && pItemThread->CheckExecution()) break;
	}
	nState |= (nItem == nItems) ? TCPROCEDURESMONITOR_STATE_IDLE : 0;
	return nState;
}

BOOL CTCProceduresMonitorListView::SetTelecommandingUplinkState(UINT nState)
{
	m_nTelecommandingUplinkState = nState;
	return TRUE;
}

UINT CTCProceduresMonitorListView::GetTelecommandingUplinkState() CONST
{
	return m_nTelecommandingUplinkState;
}

BOOL CTCProceduresMonitorListView::EnableTelecommandingReleaseWaitMode(BOOL bEnable)
{
	m_bTelecommandingReleaseWaitMode = bEnable;
	return TRUE;
}

BOOL CTCProceduresMonitorListView::IsTelecommandingReleaseWaitModeEnabled() CONST
{
	return m_bTelecommandingReleaseWaitMode;
}

BOOL CTCProceduresMonitorListView::InitializeTelecommand(INT nProcedureID, LPCTSTR pszThread, LPCTSTR pszStep, LPCTSTR pszFunction, INT nEntry, CTCItem *pTCItem)
{
	INT  nStep;
	INT  nSteps;
	INT  nItem[2];
	INT  nItems[2];
	BOOL bAfterDispatch;
	DWORD  dwReleaseOffset;
	CString  szInterlock;
	CPtrArray  pThreadSteps;
	CTimeSpan  tTimeWindow;
	CTimeSpan  tReleaseInterval;
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pStep;
	CTCProceduresMonitorItem  *pItem;
	CDatabaseTCProcedureThread  *pThread;
	CTCProceduresMonitorItemThread  *pItemThread;
	CTCProcedureDocumentSendTCFunctionItem  *pSendTCFunctionStep;
	CTCProcedureDocumentSendTCSequenceItem  *pSendTCSequenceStep;
	CTextViewLock  cLock(m_pwndList);

	for (nItem[0] = 0, nItems[0] = ((m_nTelecommandingState & TCPROCEDURESMONITOR_STATE_DISABLED) != TCPROCEDURESMONITOR_STATE_DISABLED) ? (INT)m_pItemThreads.GetSize() : -1; nItem[0] < nItems[0]; nItem[0]++)
	{
		if ((pItemThread = (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nItem[0])) && ((nProcedureID >= 0 && pItemThread->CheckExecution(nProcedureID)) || (nProcedureID < 0 && pItemThread->CheckExecution(pTCItem->GetVerificationProcessID())))) break;
		continue;
	}
	for (nItem[1] = 0, nItems[1] = (nItem[0] == nItems[0] && nItems[0] >= 0) ? (INT)m_pItems.GetSize() : -1; nItem[1] < nItems[1]; nItem[1]++)
	{
		if ((pItem = m_pItems.GetAt(nItem[1])) && pItem->GetName() == pTCItem->GetVerificationProcedure()) break;
		continue;
	}
	if ((pItem = (nItem[0] < nItems[0]) ? m_pItems.GetAt(nItem[0]) : m_pItems.GetAt(nItem[1])))
	{
		for (pItem->GetReleaseConstraints(pszThread, pszStep, pszFunction, nEntry, szInterlock, tTimeWindow), pTCItem->SetFlags(pTCItem->GetFlags() | (pItem->GetFlags() & (TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDEPTV | TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLEPTV | TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDEPEV | TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLEPEV | TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDECEV | TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLECEV))), pTCItem->SetInterlock(szInterlock); tTimeWindow > 0 || GetTCService()->GetCommandHandlerDefaultReleaseTimeWindow(tTimeWindow); )
		{
			if (pTCItem->GetReleaseTimeWindow(dwReleaseOffset, tReleaseInterval, bAfterDispatch))
			{
				pTCItem->SetReleaseTimeWindow(dwReleaseOffset, tTimeWindow, bAfterDispatch);
				break;
			}
			pTCItem->SetReleaseTimeWindow(pTCItem->GetReleaseTime(), tTimeWindow);
			break;
		}
		if ((pThread = pItem->GetAt(pItem->Find(pszThread))))
		{
			if ((pDocument = new CTCProcedureDocument) != (CTCProcedureDocument *)NULL)
			{
				for (nStep = 0, nSteps = (pDocument->Unmap(pThread) && pDocument->EnumSteps(pThreadSteps, FALSE, TRUE) > 0) ? (INT)pThreadSteps.GetSize() : -1; nStep < nSteps; nStep++)
				{
					if ((pStep = (CTCProcedureDocumentItem *)pThreadSteps.GetAt(nStep)) && pStep->GetName() == pszStep)
					{
						if (pStep->GetType() == TCPROCEDURETHREADSTEP_ACTIONOBJECT_SENDTCFUNCTION)
						{
							if ((pSendTCFunctionStep = (CTCProcedureDocumentSendTCFunctionItem *)pStep))
							{
								pTCItem->SetPreExeGroupRef((((pSendTCFunctionStep->GetOptions() & TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_IGNOREPREEXEVERIFICATION) != TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_IGNOREPREEXEVERIFICATION  &&  pTCItem->GetPreExeGroupRef() >= 0) || !pSendTCFunctionStep->GetPreexecutionVerificationCondition().IsEmpty()) ? max(pTCItem->GetPreExeGroupRef(), 0) : -1);
								pTCItem->SetExeVerGroupRef((((pSendTCFunctionStep->GetOptions() & TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_IGNOREEXEVERIFICATION) != TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_IGNOREEXEVERIFICATION  &&  pTCItem->GetExeVerGroupRef() >= 0) || !pSendTCFunctionStep->GetExecutionVerificationCondition().IsEmpty()) ? max(pTCItem->GetExeVerGroupRef(), 0) : -1);
								break;
							}
						}
						if (pStep->GetType() == TCPROCEDURETHREADSTEP_ACTIONOBJECT_SENDTCSEQUENCE)
						{
							if ((pSendTCFunctionStep = ((pSendTCSequenceStep = (CTCProcedureDocumentSendTCSequenceItem *)pStep)) ? pSendTCSequenceStep->GetAt(nEntry - 1) : (CTCProcedureDocumentSendTCFunctionItem *)NULL))
							{
								pTCItem->SetPreExeGroupRef((((pSendTCFunctionStep->GetOptions() & TCPROCEDURESENDTCSEQUENCEITEM_OPTIONS_IGNOREPREEXEVERIFICATION) != TCPROCEDURESENDTCSEQUENCEITEM_OPTIONS_IGNOREPREEXEVERIFICATION  &&  pTCItem->GetPreExeGroupRef() >= 0) || !pSendTCFunctionStep->GetPreexecutionVerificationCondition().IsEmpty()) ? max(pTCItem->GetPreExeGroupRef(), 0) : -1);
								pTCItem->SetExeVerGroupRef((((pSendTCFunctionStep->GetOptions() & TCPROCEDURESENDTCSEQUENCEITEM_OPTIONS_IGNOREEXEVERIFICATION) != TCPROCEDURESENDTCSEQUENCEITEM_OPTIONS_IGNOREEXEVERIFICATION  &&  pTCItem->GetExeVerGroupRef() >= 0) || !pSendTCFunctionStep->GetExecutionVerificationCondition().IsEmpty()) ? max(pTCItem->GetExeVerGroupRef(), 0) : -1);
								break;
							}
						}
					}
				}
				if (nStep < nSteps)
				{
					delete pDocument;
					return TRUE;
				}
				delete pDocument;
			}
		}
	}
	return FALSE;
}

BOOL CTCProceduresMonitorListView::EnumAuthorizableTelecommands(INT nIndex, CTCItems &pTCItems) CONST
{
	CTCProceduresMonitorItem  *pItem;
	CTextViewLock  cLock(m_pwndList);

	return(((pItem = m_pItems.GetAt(nIndex))) ? pItem->EnumAuthorizableTelecommands(pTCItems) : FALSE);
}

BOOL CTCProceduresMonitorListView::AuthorizeTelecommands(INT nIndex, CONST CTCItems &pTCItems)
{
	INT  nItem[2];
	INT  nItems[2];
	UINT  nAlertType;
	BOOL  bAfterDispatch;
	DWORD  dwReleaseOffset;
	CTCItem  *pTCItem;
	CString  szAlertMessage;
	CTimeTag  tDispatchTime;
	CTimeTag  tReleaseTime;
	CTimeSpan  tReleaseInterval;
	CTCProceduresMonitorItem  *pItem;
	CTextViewLock  cLock(m_pwndList);

	if ((pItem = m_pItems.GetAt(nIndex)))
	{
		if (pItem->AuthorizeTelecommands(pTCItems))
		{
			for (nItem[0] = 0, nItems[0] = (INT)pTCItems.GetSize(); nItem[0] < nItems[0]; nItem[0]++)
			{
				if ((pTCItem = pTCItems.GetAt(nItem[0])) != (CTCItem *)NULL)
				{
					for (pTCItem->SetDispatchTime(tDispatchTime), tReleaseTime = (!nItem[0]) ? ((pTCItem->GetReleaseTime() > 0) ? pTCItem->GetReleaseTime() : tReleaseTime) : tReleaseTime; pTCItem->GetReleaseTimeWindow(dwReleaseOffset, tReleaseInterval, bAfterDispatch); )
					{
						pTCItem->SetReleaseTime(CTimeTag(tReleaseTime.GetTime() + 1000 * (TIMETAG)dwReleaseOffset));
						break;
					}
				}
			}
			do
			{
				if (pItem->GetAlertMessage(nAlertType, szAlertMessage))
				{
					pItem->RemoveAlertMessage();
					continue;
				}
				break;
			} while (!pItem->IsAcknowledgmentEnabled(nAlertType));
			for (; !pItem->GetAlertMessage(nAlertType, szAlertMessage); )
			{
				pItem->Alert(FALSE);
				break;
			}
			if (GetTCService()->DispatchTelecommands(pTCItems))
			{
				ShowContent();
				return TRUE;
			}
			ShowContent();
		}
	}
	return FALSE;
}
BOOL CTCProceduresMonitorListView::AuthorizeTelecommands(CONST CTCItems &pTCItems)
{
	INT  nID;
	INT  nIDs;
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nCount;
	BOOL  bAfterDispatch;
	DWORD  dwReleaseOffset;
	CTCItem  *pTCItem;
	CString  szTelecommand;
	CString  szTelecommands[2];
	CString  szAlertMessage;
	CTimeTag  tAlertTime;
	CTimeTag  tReleaseTime;
	CTimeSpan  tReleaseInterval;
	CUIntArray  nTCItemIDs;
	CTCProceduresMonitorItem  *pItem;
	CTextViewLock  cLock(m_pwndList);

	for (nItem = 0, nItems = (INT)pTCItems.GetSize(); nItem < nItems; nItem++)
	{
		if ((pTCItem = pTCItems.GetAt(nItem)) != (CTCItem *)NULL)
		{
			if ((pItem = m_pItems.GetAt((nIndex = FindItem(-pTCItem->GetVerificationProcessID() - 1)))))
			{
				for (nID = 0, nIDs = (pItem->HasAuthorizableTelecommands()) ? (INT)nTCItemIDs.GetSize() : -1; nID < nIDs; nID++)
				{
					if (nTCItemIDs.GetAt(nID) == pTCItem->GetVerificationProcessID()) break;
					continue;
				}
				if (pItem->IsAcknowledgmentEnabled(TCPROCEDURESMONITORITEM_ALERTTYPE_AUTHORIZATION) && nID == nIDs)
				{
					nTCItemIDs.Add(pTCItem->GetVerificationProcessID());
					continue;
				}
				if (!pItem->IsAcknowledgmentEnabled(TCPROCEDURESMONITORITEM_ALERTTYPE_AUTHORIZATION) || nIDs >= 0) continue;
			}
			if (pTCItem->GetFlags() & TCITEM_CHECKFLAG_AUTHORIZEABLE)
			{
				for (nID = 0, nIDs = (INT)nTCItemIDs.GetSize(); nID < nIDs; nID++)
				{
					if (nTCItemIDs.GetAt(nID) == pTCItem->GetVerificationProcessID()) break;
					continue;
				}
				if (nID == nIDs)
				{
					nTCItemIDs.Add(pTCItem->GetVerificationProcessID());
					continue;
				}
			}
		}
	}
	for (nItem = 0, nItems = (INT)pTCItems.GetSize(); nItem < nItems; nItem++)
	{
		if ((pTCItem = pTCItems.GetAt(nItem)) != (CTCItem *)NULL)
		{
			for (nID = 0, nIDs = (INT)nTCItemIDs.GetSize(), szTelecommands[0].Empty(), szTelecommands[1].Empty(); nID < nIDs; nID++)
			{
				if (nTCItemIDs.GetAt(nID) == pTCItem->GetVerificationProcessID()) break;
				continue;
			}
			if (nID < nIDs)
			{
				if ((pItem = m_pItems.GetAt((nIndex = ((nIndex = FindItem(-pTCItem->GetVerificationProcessID() - 1)) < 0) ? CreateItem(-pTCItem->GetVerificationProcessID() - 1) : nIndex))))
				{
					for (nItem = 0, nCount = 0; nItem < nItems; nItem++)
					{
						if ((pTCItem = pTCItems.GetAt(nItem)))
						{
							if (pTCItem->GetVerificationProcessID() == nTCItemIDs.GetAt(nID))
							{
								if ((pTCItem->GetFlags() & TCITEM_CHECKFLAG_AUTHORIZEABLE) == TCITEM_CHECKFLAG_AUTHORIZEABLE)
								{
									szTelecommand.Format(STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGE_TELECOMMAND_FORMAT), (LPCTSTR)pTCItem->GetName());
									szTelecommands[0] += (!szTelecommands[0].IsEmpty()) ? (STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGE_TELECOMMAND_DELIMITER) + szTelecommand) : szTelecommand;
									szTelecommands[1] = (szTelecommands[1].IsEmpty()) ? pTCItem->GetMembership() : szTelecommands[1];
									nCount++;
								}
								pItem->AddAuthorizableTelecommand(pTCItem);
							}
						}
					}
					for (szAlertMessage.Empty(); szTelecommands[1].IsEmpty() && nCount == 1; )
					{
						szAlertMessage.Format(STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGE_AUTHORIZATIONREQUEST), (LPCTSTR)szTelecommands[0]);
						break;
					}
					for (; !szTelecommands[1].IsEmpty() && nCount == 1; )
					{
						szAlertMessage.Format(STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGE_AUTHORIZATIONMEMBERREQUEST), (LPCTSTR)szTelecommands[0], (LPCTSTR)szTelecommands[1]);
						break;
					}
					for (; !szTelecommands[1].IsEmpty() && nCount > 1; )
					{
						szAlertMessage.Format(STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGE_AUTHORIZATIONMEMBERSREQUEST), (LPCTSTR)szTelecommands[0], (LPCTSTR)szTelecommands[1]);
						break;
					}
					AlertProcedure(nIndex, TCPROCEDURESMONITORITEM_ALERTTYPE_AUTHORIZATION, szAlertMessage, tAlertTime);
				}
				nTCItemIDs.RemoveAt(nID);
				nIDs--;
				nID--;
			}
		}
	}
	for (nItem = 0, nItems = (INT)pTCItems.GetSize(); nItem < nItems; nItem++)
	{
		if ((pTCItem = pTCItems.GetAt(nItem)) != (CTCItem *)NULL)
		{
			for (tReleaseTime = (!nItem) ? ((pTCItem->GetReleaseTime() > 0) ? pTCItem->GetReleaseTime() : tReleaseTime) : tReleaseTime; pTCItem->GetReleaseTimeWindow(dwReleaseOffset, tReleaseInterval, bAfterDispatch); )
			{
				pTCItem->SetReleaseTime(CTimeTag(tReleaseTime.GetTime() + 1000 * (TIMETAG)dwReleaseOffset));
				break;
			}
		}
	}
	return((!pTCItems.GetSize()) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorListView::CanAuthorizeTelecommands(INT nIndex) CONST
{
	UINT  nAlertType;
	CString  szAlertMessage;
	CTCProceduresMonitorItem  cItem;
	CTextViewLock  cLock(m_pwndList);

	return(GetProcedureInfo(nIndex, &cItem) && cItem.GetAlertMessage(nAlertType, szAlertMessage) && nAlertType == TCPROCEDURESMONITORITEM_ALERTTYPE_AUTHORIZATION);
}

BOOL CTCProceduresMonitorListView::SetLayoutInfo(INT nIndex, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo)
{
	return m_pwndList->SetLayoutInfo(nIndex, pHorzScrollInfo, pVertScrollInfo);
}

BOOL CTCProceduresMonitorListView::GetLayoutInfo(INT &nIndex, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST
{
	return m_pwndList->GetLayoutInfo(nIndex, pHorzScrollInfo, pVertScrollInfo);
}

BOOL CTCProceduresMonitorListView::GetPrintProperties(CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs, BOOL bAll) CONST
{
	INT  nItem;
	INT  nItems;
	CTextViewLock  cLock(m_pwndList);

	if (m_pwndList->GetPrintProperties(szColumns, szContents, pAttributes, pSymbols, nSymbolIDs) && GetListTitleFont(pTitleFont) && GetListItemsFont(pItemsFont))
	{
		for (nItem = 0, nItems = (!bAll) ? m_pwndList->GetCurText() : 0; nItem < nItems; nItem++)
		{
			delete pAttributes.GetAt(nItem);
			pAttributes.RemoveAt(nItem);
			szContents.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
		for (nItem = nItems + 1, nItems = (!bAll) ? (INT)szContents.GetSize() : 0; nItem < nItems; nItem++)
		{
			delete pAttributes.GetAt(nItem);
			pAttributes.RemoveAt(nItem);
			szContents.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorListView::UpdateContent(BOOL bAll)
{
	INT  nIndex;
	CTCProceduresMonitorItem  *pItem;
	CTCProceduresMonitorItemThread  *pItemThread;
	CTextViewLock  cLock(m_pwndList);

	if (!bAll)
	{
		if ((pItem = m_pItems.GetAt(GetCurProcedure())) && GetParentDisplay()->GetItemFlowcharts(pItem))
		{
			ShowContent();
			return TRUE;
		}
		return FALSE;
	}
	for (GetParent()->GetItemView()->UpdateContents(); (pItemThread = ((pItem = ((nIndex = GetCurProcedure()) >= 0 && nIndex < m_pItemThreads.GetSize()) ? (CTCProceduresMonitorItem *)m_pItems.GetAt(nIndex) : (CTCProceduresMonitorItem *)NULL)) ? (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nIndex) : (CTCProceduresMonitorItemThread *)NULL); )
	{
		for (GetParent()->ResizeToContents((pItem->GetTriggerType() != TCPROCEDURESMONITORITEM_TRIGGERTYPE_AUTOMATIC) ? TRUE : FALSE); !pItemThread->IsRunning(); )
		{
			pItemThread->Reset();
			break;
		}
		return TRUE;
	}
	return FALSE;
}

VOID CTCProceduresMonitorListView::SetTrackSize(CONST SIZE &size)
{
	m_pwndList->SetTrackSize(size);
}

CSize CTCProceduresMonitorListView::GetTrackSize() CONST
{
	return m_pwndList->GetTrackSize();
}

CTCProceduresMonitorView *CTCProceduresMonitorListView::GetParent() CONST
{
	return((CTCProceduresMonitorView *)m_pParentWnd);
}

CTCProceduresMonitorWnd *CTCProceduresMonitorListView::GetParentDisplay() CONST
{
	CTCProceduresMonitorView  *pView;

	return(((pView = GetParent())) ? pView->GetParent() : (CTCProceduresMonitorWnd *)NULL);
}

VOID CTCProceduresMonitorListView::ShowContent(INT nIndex)
{
	INT  nItem;
	INT  nItems;
	INT  nCount;
	INT  nColumn;
	INT  nColumns;
	INT  nArgument;
	INT  nArguments;
	UINT  nCycles;
	UINT  nAlertType;
	CString  szItem;
	CString  szAlert;
	CString  szTrigger;
	CString  szArgument;
	CString  szDelimiter;
	CString  szDescription;
	CString  szTimeInterval;
	CString  szChecks[3];
	CTimeKey  tStopTime;
	CTimeKey  tStartTime;
	CTimeTag  tAlertTime;
	CTimeSpan  tInterval;
	CStringArray  szColumns;
	CStringTools  cStringTools;
	CTextViewAttribute  cAttribute;
	CDatabaseTCProcedureArgument  *pArgument;
	CDatabaseTCProcedureArguments  pArguments;
	CTCProceduresMonitorItem  *pItem;

	for (nItem = 0, nItems = (m_pwndList->GetColumns(szColumns)) ? (INT)m_pItems.GetSize() : 0, szDelimiter = CTextView::GetColumnDelimiter(), nCount = 0; nItem < nItems; nItem++)
	{
		if ((pItem = m_pItems.GetAt(nItem)) != (CTCProceduresMonitorItem *)NULL)
		{
			while (pItem->GetAlertMessage(nAlertType, szAlert, tAlertTime))
			{
				if (!pItem->IsAcknowledgmentEnabled(nAlertType))
				{
					pItem->RemoveAlertMessage();
					continue;
				}
				break;
			}
			for (szAlert.Empty(), nAlertType = -1, tAlertTime = 0; pItem->GetAlertMessage(nAlertType, szAlert, tAlertTime); )
			{
				cAttribute.SetColumnColor(-1, pItem->GetAcknowledgmentColor(nAlertType));
				cAttribute.SetColumnBlinking(-1, TRUE);
				break;
			}
			if (!pItem->GetAlertMessage(nAlertType, szAlert, tAlertTime))
			{
				cAttribute.SetColumnColor(-1, GetSysColor(COLOR_WINDOWTEXT));
				cAttribute.SetColumnBlinking(-1, FALSE);
			}
			for (nColumn = 0, nColumns = (INT)szColumns.GetSize(), szItem.Empty(); nColumn < nColumns; nColumn++)
			{
				if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NAME))
				{
					szItem += (nColumn > 0) ? (szDelimiter + pItem->GetName()) : pItem->GetName();
					szItem += (nAlertType == TCPROCEDURESMONITORITEM_ALERTTYPE_INFORMATIONAL) ? (CString(CTCProceduresMonitorTextView::GetSymbolDelimiter()) + STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_INFORMATION)) : EMPTYSTRING;
					szItem += (nAlertType == TCPROCEDURESMONITORITEM_ALERTTYPE_WARNING) ? (CString(CTCProceduresMonitorTextView::GetSymbolDelimiter()) + STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_WARNING)) : EMPTYSTRING;
					szItem += (nAlertType == TCPROCEDURESMONITORITEM_ALERTTYPE_ERROR) ? (CString(CTCProceduresMonitorTextView::GetSymbolDelimiter()) + STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_ERROR)) : EMPTYSTRING;
					szItem += (nAlertType == TCPROCEDURESMONITORITEM_ALERTTYPE_ALERT) ? (CString(CTCProceduresMonitorTextView::GetSymbolDelimiter()) + STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_ALERT)) : EMPTYSTRING;
					szItem += (nAlertType == TCPROCEDURESMONITORITEM_ALERTTYPE_AUTHORIZATION) ? (CString(CTCProceduresMonitorTextView::GetSymbolDelimiter()) + STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_AUTHORIZATION)) : EMPTYSTRING;
					continue;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_DESCRIPTION))
				{
					szDescription = (nAlertType == TCPROCEDURESMONITORITEM_ALERTTYPE_INFORMATIONAL) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_INFORMATION) : EMPTYSTRING;
					szDescription = (nAlertType == TCPROCEDURESMONITORITEM_ALERTTYPE_WARNING) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_WARNING) : szDescription;
					szDescription = (nAlertType == TCPROCEDURESMONITORITEM_ALERTTYPE_ERROR) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_ERROR) : szDescription;
					szDescription = (nAlertType == TCPROCEDURESMONITORITEM_ALERTTYPE_ALERT) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_ALERT) : szDescription;
					szDescription = (nAlertType == TCPROCEDURESMONITORITEM_ALERTTYPE_AUTHORIZATION) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_AUTHORIZATION) : szDescription;
					szItem += (pItem->GetID() >= 0) ? ((nColumn > 0) ? (szDelimiter + pItem->GetDescription()) : pItem->GetDescription()) : ((nColumn > 0) ? (szDelimiter + szDescription) : szDescription);
					continue;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_COMMENTS))
				{
					szItem += (pItem->GetID() >= 0) ? ((nColumn > 0) ? (szDelimiter + pItem->GetComments()) : pItem->GetComments()) : ((nColumn > 0) ? szDelimiter : EMPTYSTRING);
					continue;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_AUTHOR))
				{
					szItem += (pItem->GetID() >= 0) ? ((nColumn > 0) ? (szDelimiter + pItem->GetAuthor()) : pItem->GetAuthor()) : ((nColumn > 0) ? szDelimiter : EMPTYSTRING);
					continue;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_CREATIONTIME))
				{
					szItem += (pItem->GetID() >= 0) ? ((nColumn > 0) ? (szDelimiter + pItem->GetCreationDate().FormatGmt()) : pItem->GetCreationDate().FormatGmt()) : ((nColumn > 0) ? szDelimiter : EMPTYSTRING);
					continue;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_MODIFICATIONTIME))
				{
					szItem += (pItem->GetID() >= 0) ? ((nColumn > 0) ? (szDelimiter + pItem->GetModificationDate().FormatGmt()) : pItem->GetModificationDate().FormatGmt()) : ((nColumn > 0) ? szDelimiter : EMPTYSTRING);
					continue;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_VERIFICATIONSTATUS))
				{
					szItem += (pItem->GetID() >= 0) ? ((nColumn > 0) ? (szDelimiter + pItem->GetVerificationStatus()) : pItem->GetVerificationStatus()) : ((nColumn > 0) ? szDelimiter : EMPTYSTRING);
					continue;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NUMBEROFTHREADS))
				{
					szItem += (pItem->GetID() >= 0) ? ((nColumn > 0) ? (szDelimiter + cStringTools.ConvertIntToString((INT)pItem->GetSize())) : cStringTools.ConvertIntToString((INT)pItem->GetSize())) : ((nColumn > 0) ? szDelimiter : EMPTYSTRING);
					continue;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ARGUMENTS))
				{
					for (nArgument = 0, nArguments = (pItem->GetID() >= 0) ? pItem->GetArguments(pArguments) : -1, szItem += (nColumn > 0) ? szDelimiter : EMPTYSTRING; nArgument < nArguments; nArgument++)
					{
						if ((pArgument = pArguments.GetAt(nArgument)) != (CDatabaseTCProcedureArgument *)NULL)
						{
							szArgument.Format(STRING(IDS_TCPROCEDURESMONITOR_LIST_ARGUMENTSFORMAT), (LPCTSTR)pArgument->GetTag(), (!pArgument->GetConstValueAsText().IsEmpty()) ? (LPCTSTR)pArgument->GetConstValueAsText() : STRING(IDS_TCPROCEDURESMONITOR_LIST_NOARGUMENTVALUESYMBOL));
							szItem += (nArgument > 0) ? (STRING(IDS_TCPROCEDURESMONITOR_LIST_ARGUMENTSSEPARATOR) + szArgument) : szArgument;
						}
					}
					if (!nArguments)
					{
						szArgument = STRING(IDS_TCPROCEDURESMONITOR_LIST_NOARGUMENTS);
						szItem += szArgument;
					}
					continue;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_TRIGGERTYPE))
				{
					if (pItem->GetID() >= 0 && pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_NONE)
					{
						szItem += (nColumn > 0) ? (szDelimiter + STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_NONE)) : STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_NONE);
						szItem += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
						continue;
					}
					if (pItem->GetID() >= 0 && pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_MANUAL)
					{
						szItem += (nColumn > 0) ? (szDelimiter + STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_MANUAL)) : STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_MANUAL);
						szItem += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
						continue;
					}
					if (pItem->GetID() >= 0 && pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_AUTOMATIC)
					{
						szItem += (nColumn > 0) ? (szDelimiter + STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_AUTOMATIC)) : STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_AUTOMATIC);
						szItem += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
						continue;
					}
					if (pItem->GetID() >= 0 && pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_IMMEDIATELY)
					{
						szItem += (nColumn > 0) ? (szDelimiter + STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_IMMEDIATELY)) : STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_IMMEDIATELY);
						szItem += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
						continue;
					}
					if (pItem->GetID() >= 0 && pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATSTARTUP)
					{
						szItem += (nColumn > 0) ? (szDelimiter + STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_ATSTARTUP)) : STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_ATSTARTUP);
						szItem += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
						continue;
					}
					if (pItem->GetID() >= 0 && pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATTIME)
					{
						szTrigger.Format(STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_ATTIME), (LPCTSTR)pItem->GetTriggerTime().FormatGmt());
						szTrigger += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
						szItem += (nColumn > 0) ? (szDelimiter + szTrigger) : szTrigger;
						continue;
					}
					if (pItem->GetID() >= 0 && pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATDAILYTIME)
					{
						szTrigger.Format(STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_ATDAILYTIME), (LPCTSTR)CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + pItem->GetDailyTriggerTime().GetTotalSeconds()).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT)));
						szTrigger += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
						szItem += (nColumn > 0) ? (szDelimiter + szTrigger) : szTrigger;
						continue;
					}
					if (pItem->GetID() >= 0 && pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATINTERVAL)
					{
						if (pItem->GetTriggerInterval(tStartTime, tInterval) || pItem->GetTriggerInterval(tStartTime, tInterval, tStopTime) || pItem->GetTriggerInterval(tStartTime, tInterval, nCycles))
						{
							szTrigger.Format(STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_ATINTERVAL), (LPCTSTR)cStringTools.ConvertLongIntToStructuredString(tInterval.GetTotalSeconds()), (LPCTSTR)tStartTime.FormatGmt());
							szTrigger += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
							szItem += (nColumn > 0) ? (szDelimiter + szTrigger) : szTrigger;
							continue;
						}
					}
					if (pItem->GetID() >= 0 && pItem->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATEVENT)
					{
						szTrigger.Format(STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERTYPE_ATEVENT), (LPCTSTR)pItem->GetTriggerEvent());
						szTrigger += (!pItem->IsEnabled()) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_TRIGGERFLAG_DISABLED) : EMPTYSTRING;
						szItem += (nColumn > 0) ? (szDelimiter + szTrigger) : szTrigger;
						continue;
					}
					szItem += (nColumn > 0) ? szDelimiter : EMPTYSTRING;
					continue;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONMODE))
				{
					if (pItem->GetID() >= 0 && pItem->GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_AUTOMATIC)
					{
						szItem += (nColumn > 0) ? (szDelimiter + STRING(IDS_TCPROCEDURESMONITOR_LIST_EXECUTIONMODE_AUTOMATIC)) : STRING(IDS_TCPROCEDURESMONITOR_LIST_EXECUTIONMODE_AUTOMATIC);
						continue;
					}
					if (pItem->GetID() >= 0 && pItem->GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_SINGLESTEP)
					{
						szItem += (nColumn > 0) ? (szDelimiter + STRING(IDS_TCPROCEDURESMONITOR_LIST_EXECUTIONMODE_SINGLESTEP)) : STRING(IDS_TCPROCEDURESMONITOR_LIST_EXECUTIONMODE_SINGLESTEP);
						continue;
					}
					if (pItem->GetID() >= 0 && pItem->GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_EXTERNALACTIONS)
					{
						szItem += (nColumn > 0) ? (szDelimiter + STRING(IDS_TCPROCEDURESMONITOR_LIST_EXECUTIONMODE_EXTERNALACTIONS)) : STRING(IDS_TCPROCEDURESMONITOR_LIST_EXECUTIONMODE_EXTERNALACTIONS);
						continue;
					}
					if (pItem->GetID() >= 0 && pItem->GetExecutionMode() == TCPROCEDURESMONITORITEM_EXECUTIONMODE_COMMANDS)
					{
						szItem += (nColumn > 0) ? (szDelimiter + STRING(IDS_TCPROCEDURESMONITOR_LIST_EXECUTIONMODE_COMMANDS)) : STRING(IDS_TCPROCEDURESMONITOR_LIST_EXECUTIONMODE_COMMANDS);
						continue;
					}
					szItem += (nColumn > 0) ? szDelimiter : EMPTYSTRING;
					continue;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONCOUNT))
				{
					szItem += (pItem->GetID() >= 0) ? ((nColumn > 0) ? (szDelimiter + cStringTools.ConvertIntToStructuredString(pItem->GetExecutionCount())) : cStringTools.ConvertIntToStructuredString(pItem->GetExecutionCount())) : ((nColumn > 0) ? szDelimiter : EMPTYSTRING);
					continue;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_RUNNINGSTATE))
				{
					if (pItem->GetID() >= 0 && pItem->GetRunningState() == TCPROCEDURESMONITORITEM_RUNNINGSTATE_NOTRUNNING)
					{
						szItem += (nColumn > 0) ? (szDelimiter + STRING(IDS_TCPROCEDURESMONITOR_LIST_RUNNINGSTATE_NOTRUNNING)) : STRING(IDS_TCPROCEDURESMONITOR_LIST_RUNNINGSTATE_NOTRUNNING);
						continue;
					}
					if (pItem->GetID() >= 0 && pItem->GetRunningState() == TCPROCEDURESMONITORITEM_RUNNINGSTATE_RUNNING)
					{
						szItem += (nColumn > 0) ? (szDelimiter + STRING(IDS_TCPROCEDURESMONITOR_LIST_RUNNINGSTATE_RUNNING)) : STRING(IDS_TCPROCEDURESMONITOR_LIST_RUNNINGSTATE_RUNNING);
						continue;
					}
					if (pItem->GetID() >= 0 && pItem->GetRunningState() == TCPROCEDURESMONITORITEM_RUNNINGSTATE_STOPPED)
					{
						szItem += (nColumn > 0) ? (szDelimiter + STRING(IDS_TCPROCEDURESMONITOR_LIST_RUNNINGSTATE_STOPPED)) : STRING(IDS_TCPROCEDURESMONITOR_LIST_RUNNINGSTATE_STOPPED);
						continue;
					}
					szItem += (nColumn > 0) ? szDelimiter : EMPTYSTRING;
					continue;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ACKNOWLEDGEREQUEST))
				{
					szItem += (nColumn > 0) ? (szDelimiter + szAlert) : szAlert;
					continue;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ACKREQUESTTIME))
				{
					szItem += (nColumn > 0) ? ((!szAlert.IsEmpty()) ? (szDelimiter + tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_FORMAT))) : szDelimiter) : ((!szAlert.IsEmpty()) ? tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_FORMAT)) : EMPTYSTRING);
					continue;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS))
				{
					szChecks[1] = (((pItem->GetFlags() | GetParent()->GetTelecommandingChecks()) & TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLEPEV) != TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLEPEV) ? (((pItem->GetFlags() | GetParent()->GetTelecommandingChecks()) & TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDEPEV) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_PEVCHECKS_OFF) : STRING(IDS_TCPROCEDURESMONITOR_LIST_PEVCHECKS_ON)) : STRING(IDS_TCPROCEDURESMONITOR_LIST_PEVCHECKS_DISABLED);
					szItem += (pItem->GetID() >= 0) ? ((nColumn > 0) ? (szDelimiter + szChecks[1]) : szChecks[1]) : ((nColumn > 0) ? szDelimiter : EMPTYSTRING);
					continue;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS))
				{
					szChecks[2] = (((pItem->GetFlags() | GetParent()->GetTelecommandingChecks()) & TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLECEV) != TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLECEV) ? (((pItem->GetFlags() | GetParent()->GetTelecommandingChecks()) & TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDECEV) ? STRING(IDS_TCPROCEDURESMONITOR_LIST_CEVCHECKS_OFF) : STRING(IDS_TCPROCEDURESMONITOR_LIST_CEVCHECKS_ON)) : STRING(IDS_TCPROCEDURESMONITOR_LIST_CEVCHECKS_DISABLED);
					szItem += (pItem->GetID() >= 0) ? ((nColumn > 0) ? (szDelimiter + szChecks[2]) : szChecks[2]) : ((nColumn > 0) ? szDelimiter : EMPTYSTRING);
					continue;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_STARTTIME))
				{
					szItem += (pItem->GetID() >= 0) ? ((nColumn > 0) ? ((pItem->GetExecutionStartTime() > 0) ? (szDelimiter + pItem->GetExecutionStartTime().FormatGmt()) : ((pItem->GetExecutionStartTime() < 0) ? (szDelimiter + CTimeKey(-pItem->GetExecutionStartTime().GetTime()).FormatGmt() + STRING(IDS_TCPROCEDURESMONITOR_LIST_TIMESKIPPEDFLAG)) : szDelimiter)) : ((pItem->GetExecutionStartTime() > 0) ? pItem->GetExecutionStartTime().FormatGmt() : ((pItem->GetExecutionStartTime() < 0) ? (CTimeKey(-pItem->GetExecutionStartTime().GetTime()).FormatGmt() + STRING(IDS_TCPROCEDURESMONITOR_LIST_TIMESKIPPEDFLAG)) : EMPTYSTRING))) : ((nColumn > 0) ? szDelimiter : EMPTYSTRING);
					continue;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ENDTIME))
				{
					szTimeInterval.Format(STRING(IDS_TCPROCEDURESMONITOR_LIST_TIMEINTERVALFORMAT), (LPCTSTR)cStringTools.ConvertLongIntToStructuredString(max(pItem->GetExecutionEndTime().GetTime() - pItem->GetExecutionStartTime().GetTime(), 0)));
					szItem += (pItem->GetID() >= 0) ? ((nColumn > 0) ? ((pItem->GetExecutionEndTime() > 0) ? (szDelimiter + pItem->GetExecutionEndTime().FormatGmt() + szTimeInterval) : szDelimiter) : ((pItem->GetExecutionEndTime() > 0) ? (pItem->GetExecutionEndTime().FormatGmt() + szTimeInterval) : EMPTYSTRING)) : ((nColumn > 0) ? szDelimiter : EMPTYSTRING);
					continue;
				}
			}
			if (nCount >= m_pwndList->GetTextCount())
			{
				m_pwndList->InsertText(nCount, szItem, &cAttribute, nItem == nItems - 1);
				nCount++;
				continue;
			}
			m_pwndList->SetText(nCount, szItem, &cAttribute, nItem == nItems - 1);
			nCount++;
		}
	}
	while (nCount < m_pwndList->GetTextCount())
	{
		m_pwndList->DeleteText(nCount, nCount == m_pwndList->GetTextCount() - 1);
		continue;
	}
	SetCurProcedure((nIndex >= 0) ? min(m_pwndList->GetTextCount() - 1, nIndex) : max(m_pwndList->GetCurText(), 0));
}

INT CTCProceduresMonitorListView::CreateItem(INT nID)
{
	INT  nIndex;
	INT  nCount;
	CString  szSubRoutine;
	CTCProceduresMonitorItem  *pItem;
	CTCProceduresMonitorItemThread  *pItemThread;

	for (nIndex = 0, nCount = (INT)m_pItemThreads.GetSize(); nIndex < nCount; nIndex++)
	{
		if ((pItemThread = (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nIndex)) && pItemThread->CheckExecution(-nID - 1, szSubRoutine)) break;
		continue;
	}
	if ((pItem = (nIndex < nCount) ? new CTCProceduresMonitorItem : (CTCProceduresMonitorItem *)NULL))
	{
		for (pItem->SetName(szSubRoutine), pItem->SetID(nID), m_pItems.InsertAt(nCount, pItem, 1), m_pItemThreads.InsertAt(nCount, NULL, 1); m_pItems.GetSize() == m_pItemThreads.GetSize(); ) return nCount;
		delete pItem;
	}
	return -1;
}

INT CTCProceduresMonitorListView::FindItem(INT nID) CONST
{
	INT  nIndex[2];
	INT  nCount[2];
	CTCProceduresMonitorItem  *pItem;
	CTCProceduresMonitorItemThread  *pItemThread;

	for (nIndex[0] = 0, nCount[0] = (INT)m_pItems.GetSize(); nIndex[0] < nCount[0]; nIndex[0]++)
	{
		if ((pItem = m_pItems.GetAt(nIndex[0])) && pItem->GetID() == nID) break;
		continue;
	}
	for (nIndex[1] = 0, nCount[1] = (nIndex[0] == nCount[0]) ? nCount[0] : 0; nIndex[1] < nCount[1]; nIndex[1]++)
	{
		if ((pItemThread = (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nIndex[1])) && pItemThread->CheckExecution(-nID - 1)) break;
		continue;
	}
	return((nIndex[0] == nCount[0]) ? ((nIndex[1] < nCount[1]) ? nIndex[1] : -1) : nIndex[0]);
}

BOOL CTCProceduresMonitorListView::DestroyItem(INT nID)
{
	INT  nIndex;
	INT  nCount;
	CTCProceduresMonitorItem  *pItem;

	for (nIndex = 0, nCount = (INT)m_pItems.GetSize(); nIndex < nCount; nIndex++)
	{
		if ((pItem = m_pItems.GetAt(nIndex)) && pItem->GetID() == nID)
		{
			m_pItemThreads.RemoveAt(nIndex);
			m_pItems.RemoveAt(nIndex);
			delete pItem;
			break;
		}
	}
	return((nIndex < nCount) ? TRUE : FALSE);
}

INT CTCProceduresMonitorListView::GenerateItemID() CONST
{
	INT  nID;
	INT  nIndex;
	INT  nCount;
	CTCProceduresMonitorItem  *pItem;

	for (nIndex = 0, nCount = (INT)m_pItems.GetSize(), nID = 0; nIndex < nCount; nIndex++)
	{
		if ((pItem = m_pItems.GetAt(nIndex)) && pItem->GetID() == nID)
		{
			nID = nID + 1;
			nIndex = -1;
		}
	}
	return nID;
}

BOOL CTCProceduresMonitorListView::TranslateAlertLoggingInfo(CEventObject *pEvent, LPCTSTR pszLog) CONST
{
	INT  nPos;
	INT  nFlag;
	INT  nFlags;
	BOOL  bFlags;
	WORD  wAge;
	WORD  wGender;
	DWORD  dwPitch;
	DWORD  dwVolume;
	DWORD  dwPlayback;
	CString  szLog;
	CString  szOption;
	CString  szAdapter;
	CString  szSpeaker;
	CStringArray  szRecipients;
	CAuditionProfiles  pAuditionProfiles;
	CAuditionProfileInfo  *pAuditionProfileInfo;
	CNotificationProfiles  pNotificationProfiles;
	CNotificationProfileInfo  *pNotificationProfileInfo;

	for (nFlag = 0, nFlags = MAXTCPROCEDURESMONITORALERTMESSAGEFLAGS - MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + 1, bFlags = FALSE, szLog = pszLog, szLog.MakeUpper(), pEvent->SetCategory(EVENT_CATEGORY_SYSTEM), pEvent->SetType(STRING(IDS_TCPROCEDURESMONITOR_ALERTTYPE_ALERT)), pEvent->SetSubtype(EMPTYSTRING), pEvent->SetMessage(pszLog), pEvent->SetComments(EMPTYSTRING), pEvent->SetUser(GetAccountUserName()), pEvent->SetAudition(AUDIO_NO_SOUND), pEvent->SetNotification(NOTIFICATIONINFO_TYPE_NONE, EMPTYSTRING), pEvent->SetAuditTime(CTime::GetCurrentTime().GetTime()), pEvent->SetAuditColor(VGA_COLOR_BLACK), pEvent->Acknowledge(); nFlag < nFlags; nFlag++)
	{
		if ((nPos = szLog.Find(STRING(MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + nFlag))) >= 0 && szLog.Mid(nPos + lstrlen(STRING(MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + nFlag))).Find(STRING(MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + nFlag)) < 0)
		{
			if (!_tcsncmp(STRING(MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + nFlag), STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGEFLAG_CATEGORY), lstrlen(STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGEFLAG_CATEGORY))))
			{
				if (!_tcsicmp((szOption = ParseAlertLoggingOption(pszLog, STRING(MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + nFlag), nPos)), STRING(IDS_EVENTCATEGORY_SYSTEM)) || !_tcsicmp(szOption, STRING(IDS_EVENTCATEGORY_SPACECRAFT)) || !_tcsicmp(szOption, STRING(IDS_EVENTCATEGORY_USER)))
				{
					pEvent->SetCategory((!_tcsicmp(szOption, STRING(IDS_EVENTCATEGORY_SYSTEM))) ? EVENT_CATEGORY_SYSTEM : ((!_tcsicmp(szOption, STRING(IDS_EVENTCATEGORY_SPACECRAFT))) ? EVENT_CATEGORY_SPACECRAFT : EVENT_CATEGORY_USER));
					bFlags = TRUE;
					continue;
				}
				break;
			}
			if (!_tcscmp(STRING(MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + nFlag), STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGEFLAG_TYPE)))
			{
				if (lstrlen((szOption = ParseAlertLoggingOption(pszLog, STRING(MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + nFlag), nPos))) > 0)
				{
					pEvent->SetType(szOption);
					bFlags = TRUE;
					continue;
				}
				break;
			}
			if (!_tcscmp(STRING(MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + nFlag), STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGEFLAG_SUBTYPE)))
			{
				if (lstrlen((szOption = ParseAlertLoggingOption(pszLog, STRING(MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + nFlag), nPos))) > 0)
				{
					pEvent->SetSubtype(szOption);
					bFlags = TRUE;
					continue;
				}
				break;
			}
			if (!_tcscmp(STRING(MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + nFlag), STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGEFLAG_MESSAGE)))
			{
				if (lstrlen((szOption = ParseAlertLoggingOption(pszLog, STRING(MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + nFlag), nPos))) > 0)
				{
					pEvent->SetMessage(szOption);
					bFlags = TRUE;
					continue;
				}
				break;
			}
			if (!_tcscmp(STRING(MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + nFlag), STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGEFLAG_COMMENT)))
			{
				if (lstrlen((szOption = ParseAlertLoggingOption(pszLog, STRING(MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + nFlag), nPos))) > 0)
				{
					pEvent->SetComments(szOption);
					bFlags = TRUE;
					continue;
				}
				break;
			}
			if (!_tcscmp(STRING(MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + nFlag), STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGEFLAG_AUDITION)))
			{
				if ((pAuditionProfileInfo = (GetAuditionProfiles(pAuditionProfiles) && lstrlen((szOption = ParseAlertLoggingOption(pszLog, STRING(MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + nFlag), nPos))) > 0) ? pAuditionProfiles.GetAt(pAuditionProfiles.Find(szOption)) : (CAuditionProfileInfo *)NULL))
				{
					for (pAuditionProfileInfo->GetAdapterInfo(szAdapter, dwVolume, dwPitch, dwPlayback), pAuditionProfileInfo->GetVoiceSound(szSpeaker, wGender, wAge); TRUE; )
					{
						pEvent->SetAudition(pAuditionProfileInfo->GetAudition());
						pEvent->SetAudioInfo(szAdapter, dwVolume, dwPitch, dwPlayback);
						pEvent->SetAuditBeep(pAuditionProfileInfo->GetBeepSound());
						pEvent->SetAuditWave(pAuditionProfileInfo->GetWaveSound());
						pEvent->SetAuditVoice(szSpeaker, wGender, wAge);
						break;
					}
					bFlags = TRUE;
					continue;
				}
				pEvent->SetAudition(AUDIO_NO_SOUND);
				bFlags = TRUE;
				continue;
			}
			if (!_tcscmp(STRING(MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + nFlag), STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGEFLAG_NOTIFICATION)))
			{
				if ((pNotificationProfileInfo = (GetNotificationProfiles(pNotificationProfiles) && lstrlen((szOption = ParseAlertLoggingOption(pszLog, STRING(MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + nFlag), nPos))) > 0) ? pNotificationProfiles.GetAt(pNotificationProfiles.Find(szOption)) : (CNotificationProfileInfo *)NULL) && pNotificationProfileInfo->GetRecipients(szRecipients) > 0)
				{
					pEvent->SetNotification(pNotificationProfileInfo->GetType(), pNotificationProfileInfo->GetName());
					pEvent->SetNotificationRecipients(szRecipients);
					bFlags = TRUE;
					continue;
				}
				pEvent->SetNotification(NOTIFICATIONINFO_TYPE_NONE, EMPTYSTRING);
				bFlags = TRUE;
				continue;
			}
			if (!_tcscmp(STRING(MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + nFlag), STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGEFLAG_COLOR)))
			{
				if (lstrlen((szOption = ParseAlertLoggingOption(pszLog, STRING(MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + nFlag), nPos))) > 0)
				{
					pEvent->SetAuditColor(_ttoi(szOption));
					bFlags = TRUE;
					continue;
				}
				break;
			}
			if (!_tcscmp(STRING(MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + nFlag), STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGEFLAG_BLINK)))
			{
				pEvent->Acknowledge(FALSE);
				bFlags = TRUE;
				continue;
			}
		}
	}
	return((nFlag == nFlags) ? bFlags : FALSE);
}

CString CTCProceduresMonitorListView::ParseAlertLoggingOption(LPCTSTR pszLog, LPCTSTR pszOption, INT &nPos) CONST
{
	INT  nFlag;
	INT  nFlags;
	INT  nLength;
	CString  szOption;

	for (nPos += lstrlen(pszOption), nLength = lstrlen(pszLog); nPos < nLength; nPos++)
	{
		if (!_istspace(pszLog[nPos])) break;
		continue;
	}
	if (nPos < nLength  &&  pszLog[nPos] == STRINGCHAR(IDS_TCPROCEDURESMONITOR_ALERTMESSAGEFLAG_DELIMITER))
	{
		for (szOption.Empty(), nPos = nPos + 1; nPos < nLength; nPos++)
		{
			if (pszLog[nPos] != pszOption[0])
			{
				szOption += pszLog[nPos];
				continue;
			}
			for (nFlag = 0, nFlags = MAXTCPROCEDURESMONITORALERTMESSAGEFLAGS - MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + 1; nFlag < nFlags; nFlag++)
			{
				if (!_tcsncmp(&pszLog[nPos], STRING(MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + nFlag), lstrlen(STRING(MINTCPROCEDURESMONITORALERTMESSAGEFLAGS + nFlag)))) break;
				continue;
			}
			if (nFlag == nFlags)
			{
				szOption += pszLog[nPos];
				continue;
			}
			break;
		}
		while (szOption.GetLength() > 0)
		{
			if (szOption.Right(1).GetAt(0) != STRINGCHAR(IDS_TCPROCEDURESMONITOR_ALERTMESSAGEFLAG_DELIMITER))
			{
				szOption = szOption.Left(szOption.GetLength() - 1);
				continue;
			}
			szOption = szOption.Left(szOption.GetLength() - 1);
			break;
		}
		return szOption;
	}
	if (nPos < nLength  &&  pszLog[nPos] != STRINGCHAR(IDS_TCPROCEDURESMONITOR_ALERTMESSAGEFLAG_DELIMITER))
	{
		for (szOption.Empty(); nPos < nLength; nPos++)
		{
			if (_istdigit(pszLog[nPos]))
			{
				szOption += pszLog[nPos];
				continue;
			}
			break;
		}
		return szOption;
	}
	return EMPTYSTRING;
}

BOOL CTCProceduresMonitorListView::Lock()
{
	return m_pwndList->Lock();
}

BOOL CTCProceduresMonitorListView::Unlock()
{
	return m_pwndList->Unlock();
}

void CTCProceduresMonitorListView::PostNcDestroy()
{
	m_pItems.RemoveAll();
	CView::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorListView, CView)
	//{{AFX_MSG_MAP(CTCProceduresMonitorListView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorListView drawing

void CTCProceduresMonitorListView::OnDraw(CDC *pDC)
{
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorListView message handlers

int CTCProceduresMonitorListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CView::OnCreate(lpCreateStruct) != -1 && m_pwndList->Create(this, (m_pParentWnd = CView::GetParent()) ? CRect(0, 0, lpCreateStruct->cx, lpCreateStruct->cy) : CRect(0, 0, 0, 0), TVS_HEADER | TVS_TOP | TVS_HSCROLL | TVS_VSCROLL | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE)) ? 0 : -1);
}

void CTCProceduresMonitorListView::OnSize(UINT nType, int cx, int cy)
{
	m_pwndList->MoveWindow(0, 0, cx, cy);
	CView::OnSize(nType, cx, cy);
}

BOOL CTCProceduresMonitorListView::OnEraseBkgnd(CDC *pDC)
{
	return TRUE;
}

void CTCProceduresMonitorListView::OnSetFocus(CWnd *pOldWnd)
{
	if (IsWindow(pOldWnd->GetSafeHwnd()))
	{
		if (pOldWnd == GetParent())
		{
			m_pwndList->SetFocus();
			return;
		}
		if (m_pwndList->IsChild(pOldWnd))
		{
			GetParent()->SetFocus();
			return;
		}
	}
	CView::OnSetFocus(pOldWnd);
}

void CTCProceduresMonitorListView::OnTimer(UINT_PTR nEventID)
{
	INT  nItem[2];
	INT  nItems[2];
	INT  nArgument;
	INT  nArguments;
	CString  szMessage;
	CTCItem  *pTCItem;
	CPtrArray  pProcedureItems[2];
	CDatabaseTCProcedure  *pProcedure;
	CTCProceduresMonitorItem  *pItem[2];
	CDatabaseTCFunctionElement  *pFunctionElement;
	CDatabaseTCProcedureArgument  *pArgument;
	CDatabaseTCProcedureArguments  pArguments;
	CTCProceduresMonitorItemThread  *pItemThread;

	if (Lock())
	{
		if (nEventID == TCPROCEDURESMONITORLISTVIEW_STARTPROCEDURE_TIMERID)
		{
			for (nItem[0] = 0, nItems[0] = (INT)m_pTCItems.GetSize(), KillTimer(nEventID); nItem[0] < nItems[0]; nItem[0]++)
			{
				if ((pTCItem = m_pTCItems.GetAt(nItem[0])))
				{
					if ((pItem[0] = new CTCProceduresMonitorItem))
					{
						for (nItem[1] = 0, nItems[1] = (INT)m_pItems.GetSize(); nItem[1] < nItems[1]; nItem[1]++)
						{
							if ((pItem[1] = m_pItems.GetAt(nItem[1])) && pItem[1]->GetName() == pTCItem->GetName() && pItem[0]->Copy(pItem[1], FALSE)) break;
							continue;
						}
						if ((pProcedure = GetDatabase()->GetTCProcedures()->GetAt(GetDatabase()->GetTCProcedures()->Find(pTCItem->GetName()))))
						{
							if (((nItem[1] == nItems[1] && pItem[0]->CDatabaseTCProcedure::Copy(pProcedure)) || nItem[1] < nItems[1]) && pProcedure->GetArguments(pArguments) >= 0)
							{
								for (nArgument = 0, nArguments = (INT)pTCItem->GetSize(); nArgument < nArguments; nArgument++)
								{
									if ((pArgument = ((pFunctionElement = pTCItem->GetAt(nArgument))) ? pArguments.GetAt(nArgument) : (CDatabaseTCProcedureArgument *)NULL))
									{
										if (((pFunctionElement->GetAttributes() & (TCPARAMETER_CALIBRATION_NUMERICAL | TCPARAMETER_CALIBRATION_STATUS)) == 0 && (pFunctionElement->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TEXTSTRING | TCPARAMETER_CODING_TIME)) == (pArgument->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TEXTSTRING | TCPARAMETER_CODING_TIME))) || ((pFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL) && (pArgument->GetAttributes() & (TCPARAMETER_CALIBRATION_NUMERICAL | TCPARAMETER_CODING_FLOATINGPOINT))) || ((pFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) && (pArgument->GetAttributes() & (TCPARAMETER_CALIBRATION_STATUS | TCPARAMETER_CODING_TEXTSTRING))))
										{
											for (pArgument->SetDescription((!pArgument->GetDescription().IsEmpty()) ? pFunctionElement->GetDescription() : pArgument->GetDescription()), pArgument->SetConstValueAsText(pFunctionElement->GetConstValueAsText()); pFunctionElement->HasConstValue(); )
											{
												pArgument->SetConstValue(pFunctionElement->GetConstValue());
												break;
											}
											continue;
										}
									}
									break;
								}
								if ((nArgument == nArguments))
								{
									for (pItem[0]->SetName(pTCItem->GetName()), pItem[0]->SetID(GenerateItemID()), pItem[0]->SetFlags((pTCItem->GetFlags() & (TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDEPTV | TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLEPTV | TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDEPEV | TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLEPEV | TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDECEV | TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLECEV)) | GetTelecommandingChecks()), pItem[0]->SetTriggerType(TCPROCEDURESMONITORITEM_TRIGGERTYPE_AUTOMATIC), pItem[0]->SetExecutionMode(TCPROCEDURESMONITORITEM_EXECUTIONMODE_AUTOMATIC), pItem[0]->SetArguments(pArguments); (pItemThread = new CTCProceduresMonitorItemThread(pItem[0])); )
									{
										for (m_pItems.InsertAt(nItems[1], pItem[0], 1), m_pItemThreads.InsertAt(nItems[1], pItemThread, 1); !pItemThread->Start(GetParentDisplay(), m_pTCProcessEngine, m_pTCEnvironment, FALSE); )
										{
											m_pItemThreads.RemoveAt(nItems[1]);
											m_pItems.RemoveAt(nItems[1]);
											delete pItemThread;
											break;
										}
										break;
									}
									if (nItems[1] < m_pItems.GetSize()) continue;
								}
							}
						}
						delete pItem[0];
					}
				}
				szMessage.Format(STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGE_EXECUTIONFAILURE), (LPCTSTR)pTCItem->GetName());
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR, szMessage);
			}
			m_pTCItems.RemoveAll();
			ShowContent();
			Unlock();
			return;
		}
		if (nEventID == TCPROCEDURESMONITORLISTVIEW_STOPPROCEDURE_TIMERID)
		{
			for (nItem[0] = 0, nItems[0] = (INT)m_pItems.GetSize(), KillTimer(nEventID); nItem[0] < nItems[0]; nItem[0]++)
			{
				if ((pItem[0] = m_pItems.GetAt(nItem[0])) && pItem[0]->GetTriggerType() == TCPROCEDURESMONITORITEM_TRIGGERTYPE_AUTOMATIC  &&  pItem[0]->GetExecutionStartTime() > 0 && !pItem[0]->IsAlerted())
				{
					if ((pItemThread = (CTCProceduresMonitorItemThread *)m_pItemThreads.GetAt(nItem[0])) && !pItemThread->CheckExecution())
					{
						pProcedureItems[0].Add(pItem[0]);
						pProcedureItems[1].Add(pItemThread);
						m_pItemThreads.RemoveAt(nItem[0]);
						m_pItems.RemoveAt(nItem[0]);
						nItems[0]--;
						nItem[0]--;
					}
				}
			}
			for (nItem[0] = 0, nItems[0] = (INT)pProcedureItems[0].GetSize(), ShowContent(), Unlock(); nItem[0] < nItems[0]; nItem[0]++)
			{
				if ((pItemThread = (CTCProceduresMonitorItemThread *)pProcedureItems[1].GetAt(nItem[0]))) delete pItemThread;
				if ((pItem[0] = (CTCProceduresMonitorItem *)pProcedureItems[0].GetAt(nItem[0]))) delete pItem[0];
			}
			return;
		}
		Unlock();
	}
	CView::OnTimer(nEventID);
}

void CTCProceduresMonitorListView::OnDestroy()
{
	StopMonitoring();
	CView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemFlowchartThreadViewStatePane

IMPLEMENT_DYNCREATE(CTCProceduresMonitorItemFlowchartThreadViewStatePane, CWnd)

CTCProceduresMonitorItemFlowchartThreadViewStatePane::CTCProceduresMonitorItemFlowchartThreadViewStatePane() : CWnd()
{
	m_bBreaks = TRUE;
	m_bToolTips = TRUE;
	m_nExecutionState = 0;
	m_pCriticalSection = new CCriticalSection;
	m_pParentWnd = (CWnd *)NULL;
}

CTCProceduresMonitorItemFlowchartThreadViewStatePane::~CTCProceduresMonitorItemFlowchartThreadViewStatePane()
{
	delete m_pCriticalSection;
}

BOOL CTCProceduresMonitorItemFlowchartThreadViewStatePane::Create(CWnd *pParentWnd, CONST RECT &rect)
{
	return CWnd::Create(AfxRegisterWndClass(CS_NOCLOSE, LoadCursor((HINSTANCE)NULL, IDC_ARROW), (HBRUSH)NULL), (LPCTSTR)NULL, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, rect, (m_pParentWnd = pParentWnd), 0);
}

VOID CTCProceduresMonitorItemFlowchartThreadViewStatePane::SetBreakpoints(CONST CDatabaseTCProcedureThreadBreakpoints &pBreakpoints)
{
	INT  nBreakpoint[2];
	INT  nBreakpoints[2];
	CDatabaseTCProcedureThreadBreakpoint  *pBreakpoint;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nBreakpoint[0] = 0, nBreakpoints[0] = (INT)m_szBreakpoints.GetSize(), m_pBreakpoints.Copy(&pBreakpoints); nBreakpoint[0] < nBreakpoints[0]; nBreakpoint[0]++)
	{
		for (nBreakpoint[1] = 0, nBreakpoints[1] = (INT)pBreakpoints.GetSize(); nBreakpoint[1] < nBreakpoints[1]; nBreakpoint[1]++)
		{
			if ((pBreakpoint = pBreakpoints.GetAt(nBreakpoint[1])) != (CDatabaseTCProcedureThreadBreakpoint *)NULL)
			{
				if (m_szBreakpoints.GetAt(nBreakpoint[0]) == pBreakpoint->GetLocation()) break;
				continue;
			}
		}
		if (nBreakpoint[1] == nBreakpoints[1])
		{
			m_szBreakpoints.RemoveAt(nBreakpoint[0]);
			nBreakpoints[0]--;
			nBreakpoint[0]--;
		}
	}
	DrawContent();
}

INT CTCProceduresMonitorItemFlowchartThreadViewStatePane::GetBreakpoints(CDatabaseTCProcedureThreadBreakpoints &pBreakpoints) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	pBreakpoints.Copy(&m_pBreakpoints);
	return((INT)pBreakpoints.GetSize());
}

VOID CTCProceduresMonitorItemFlowchartThreadViewStatePane::AllowExecutionBreaks(BOOL bAllow)
{
	m_bBreaks = bAllow;
}

BOOL CTCProceduresMonitorItemFlowchartThreadViewStatePane::AreExecutionBreaksAllowed() CONST
{
	return m_bBreaks;
}

VOID CTCProceduresMonitorItemFlowchartThreadViewStatePane::EnableToolTipMode(BOOL bEnable)
{
	m_bToolTips = bEnable;
}

BOOL CTCProceduresMonitorItemFlowchartThreadViewStatePane::IsToolTipModeEnabled() CONST
{
	return m_bToolTips;
}

VOID CTCProceduresMonitorItemFlowchartThreadViewStatePane::UpdateExecutionpoint()
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	UpdateExecutionpoint(m_szExecutionStep, m_nExecutionState);
}
VOID CTCProceduresMonitorItemFlowchartThreadViewStatePane::UpdateExecutionpoint(UINT nState)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	UpdateExecutionpoint(m_szExecutionStep, nState);
}
VOID CTCProceduresMonitorItemFlowchartThreadViewStatePane::UpdateExecutionpoint(LPCTSTR pszStep, UINT nState)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_szExecutionStep = pszStep;
	m_nExecutionState = nState;
	RedrawWindow((LPCRECT)NULL, (CRgn *)NULL, RDW_INVALIDATE);
}

CTCProceduresMonitorItemFlowchartThreadView *CTCProceduresMonitorItemFlowchartThreadViewStatePane::GetParent() CONST
{
	return((CTCProceduresMonitorItemFlowchartThreadView *)m_pParentWnd);
}

VOID CTCProceduresMonitorItemFlowchartThreadViewStatePane::DrawContent()
{
	CDC  *pDC;

	if ((pDC = GetDC()))
	{
		DrawContent(pDC);
		ReleaseDC(pDC);
	}
}
VOID CTCProceduresMonitorItemFlowchartThreadViewStatePane::DrawContent(CDC *pDC)
{
	CDC  cDC;
	CRect  rPane;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;

	GetClientRect(rPane);
	if (cDC.CreateCompatibleDC(pDC))
	{
		if (cBitmap.CreateCompatibleBitmap(pDC, rPane.Width(), rPane.Height()))
		{
			if ((pOldBitmap = cDC.SelectObject(&cBitmap)) != (CBitmap *)NULL)
			{
				cDC.FillSolidRect(rPane, GetSysColor(COLOR_3DFACE));
				cDC.DrawEdge(rPane, EDGE_ETCHED, BF_RIGHT);
				DrawBreakpoints(&cDC);
				DrawExecutionpoint(&cDC);
				pDC->BitBlt(0, 0, rPane.Width(), rPane.Height(), &cDC, 0, 0, SRCCOPY);
				cDC.SelectObject(pOldBitmap);
			}
			cBitmap.DeleteObject();
		}
		cDC.DeleteDC();
	}
}

VOID CTCProceduresMonitorItemFlowchartThreadViewStatePane::DrawBreakpoints(CDC *pDC)
{
	INT  nBreakpoint;
	INT  nBreakpoints;
	CPen  *pOldPen;
	CPen  cBreakpointPen;
	CRect  rBreakpoint;
	CBrush  *pOldBrush;
	CBrush  cBreakpointBrush;
	CTCProcedureDocumentItem  *pStep;
	CDatabaseTCProcedureThreadBreakpoint  *pBreakpoint;

	for (nBreakpoint = 0, nBreakpoints = (INT)m_pBreakpoints.GetSize(); nBreakpoint < nBreakpoints; nBreakpoint++)
	{
		if ((pStep = ((pBreakpoint = m_pBreakpoints.GetAt(nBreakpoint))) ? (CTCProcedureDocumentItem *)GetParent()->FindStep(pBreakpoint->GetLocation()) : (CTCProcedureDocumentItem *)NULL))
		{
			for (rBreakpoint = CalcBreakpointPosition(pStep); cBreakpointPen.CreatePen(PS_SOLID, 1, VGA_COLOR_RED) && cBreakpointBrush.CreateSolidBrush((pBreakpoint->GetOptions() & TCPROCEDURETHREADBREAKPOINT_OPTION_DISABLED) ? GetSysColor(COLOR_3DLIGHT) : VGA_COLOR_RED); )
			{
				if ((pOldPen = pDC->SelectObject(&cBreakpointPen)) != (CPen *)NULL)
				{
					if ((pOldBrush = pDC->SelectObject(&cBreakpointBrush)))
					{
						pDC->Ellipse(rBreakpoint);
						pDC->SelectObject(pOldBrush);
					}
					pDC->SelectObject(pOldPen);
				}
				break;
			}
			cBreakpointBrush.DeleteObject();
			cBreakpointPen.DeleteObject();
		}
	}
}

VOID CTCProceduresMonitorItemFlowchartThreadViewStatePane::DrawExecutionpoint(CDC *pDC)
{
	CPen  *pOldPen;
	CPen  cExecutionpointPen;
	UINT  nExecutionState;
	CRect  rExecutionpoint;
	CBrush  *pOldBrush;
	CBrush  cExecutionpointBrush;
	CPoint  ptExecutionpoint[7];
	CString  szExecutionStep;
	CTCProcedureDocumentItem  *pStep;

	if (Lock())
	{
		szExecutionStep = m_szExecutionStep;
		nExecutionState = m_nExecutionState;
		Unlock();
	}
	for (rExecutionpoint = ((pStep = FindExecutionpoint(szExecutionStep))) ? CalcExecutionpointPosition(pStep) : CRect(0, 0, 0, 0); !rExecutionpoint.IsRectEmpty(); )
	{
		if (cExecutionpointBrush.CreateSolidBrush((nExecutionState & TCPROCEDURETHREAD_RUNNINGSTATE_RUNNING) ? VGA_COLOR_GREEN : (((nExecutionState & TCPROCEDURETHREAD_ACTIONSTATE_ABORT) != TCPROCEDURETHREAD_ACTIONSTATE_ABORT) ? VGA_COLOR_LTYELLOW : VGA_COLOR_LTRED)))
		{
			if (cExecutionpointPen.CreatePen(PS_SOLID, 1, VGA_COLOR_BLACK))
			{
				if ((pOldPen = pDC->SelectObject(&cExecutionpointPen)))
				{
					if ((pOldBrush = pDC->SelectObject(&cExecutionpointBrush)))
					{
						ptExecutionpoint[0].x = rExecutionpoint.right;
						ptExecutionpoint[0].y = rExecutionpoint.CenterPoint().y;
						ptExecutionpoint[1].x = rExecutionpoint.CenterPoint().x;
						ptExecutionpoint[1].y = rExecutionpoint.top;
						ptExecutionpoint[2].x = ptExecutionpoint[1].x;
						ptExecutionpoint[2].y = ptExecutionpoint[1].y + rExecutionpoint.Height() / 4;
						ptExecutionpoint[3].x = rExecutionpoint.left;
						ptExecutionpoint[3].y = ptExecutionpoint[2].y;
						ptExecutionpoint[4].x = ptExecutionpoint[3].x;
						ptExecutionpoint[4].y = rExecutionpoint.bottom - rExecutionpoint.Height() / 4;
						ptExecutionpoint[5].x = ptExecutionpoint[2].x;
						ptExecutionpoint[5].y = ptExecutionpoint[4].y;
						ptExecutionpoint[6].x = ptExecutionpoint[5].x;
						ptExecutionpoint[6].y = rExecutionpoint.bottom;
						pDC->Polygon(ptExecutionpoint, sizeof(ptExecutionpoint) / sizeof(CPoint));
						pDC->SelectObject(pOldBrush);
					}
					pDC->SelectObject(pOldPen);
				}
				cExecutionpointPen.DeleteObject();
			}
			cExecutionpointBrush.DeleteObject();
		}
		break;
	}
}

CTCProcedureDocumentItem *CTCProceduresMonitorItemFlowchartThreadViewStatePane::FindBreakpoint(CTCProcedureDocumentItem *pStep) CONST
{
	POSITION  lPosition;
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pBreakpoint;

	for (lPosition = ((pDocument = GetParent()->GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pBreakpoint = pDocument->GetNextStep(lPosition)))
		{
			if (!pBreakpoint->GetSubSteps()->FindStep(pStep, TRUE)) continue;
			return((!pBreakpoint->GetSubSteps()->FindStep(pStep, FALSE)) ? FindBreakpoint(pBreakpoint->GetSubSteps(), pStep) : pBreakpoint);
		}
	}
	return((CTCProcedureDocumentItem *)NULL);
}
CTCProcedureDocumentItem *CTCProceduresMonitorItemFlowchartThreadViewStatePane::FindBreakpoint(CTCProcedureDocument *pSubSteps, CTCProcedureDocumentItem *pStep) CONST
{
	POSITION  lPosition;
	CTCProcedureDocumentItem  *pBreakpoint;

	for (lPosition = pSubSteps->GetStartPosition(); lPosition; )
	{
		if ((pBreakpoint = pSubSteps->GetNextStep(lPosition)))
		{
			if (!pBreakpoint->GetSubSteps()->FindStep(pStep, TRUE)) continue;
			return((!pBreakpoint->GetSubSteps()->FindStep(pStep, FALSE)) ? FindBreakpoint(pBreakpoint->GetSubSteps(), pStep) : pBreakpoint);
		}
	}
	return((CTCProcedureDocumentItem *)NULL);
}

CTCProcedureDocumentItem *CTCProceduresMonitorItemFlowchartThreadViewStatePane::FindExecutionpoint(LPCTSTR pszStep) CONST
{
	INT  nStep;
	INT  nSteps;
	CPtrArray  pSteps;
	CTCProcedureDocumentItem  *pStep;

	for (nStep = 0, nSteps = (lstrcmp(pszStep, STRING(IDS_TELECOMMANDPROCEDURESTEP_FLOWCONTROL_START)) && lstrcmp(pszStep, STRING(IDS_TELECOMMANDPROCEDURESTEP_FLOWCONTROL_END))) ? GetParent()->GetDocument()->EnumSteps(pSteps, FALSE, TRUE) : 0; nStep < nSteps; nStep++)
	{
		if ((pStep = (CTCProcedureDocumentItem *)pSteps.GetAt(nStep)) && pStep->GetName() == pszStep) break;
		continue;
	}
	return((nStep < nSteps) ? (CTCProcedureDocumentItem *)pSteps.GetAt(nStep) : ((!lstrcmp(pszStep, STRING(IDS_TELECOMMANDPROCEDURESTEP_FLOWCONTROL_START))) ? GetParent()->GetDocument()->GetFirstStep() : ((!lstrcmp(pszStep, STRING(IDS_TELECOMMANDPROCEDURESTEP_FLOWCONTROL_END))) ? GetParent()->GetDocument()->GetLastStep() : (CTCProcedureDocumentItem *)NULL)));
}

CTCProcedureDocumentItem *CTCProceduresMonitorItemFlowchartThreadViewStatePane::FindContainerStep(CONST CTCProcedureDocumentItem *pStep) CONST
{
	INT  nStep;
	INT  nSteps;
	CPtrArray  pSteps;
	CTCProcedureDocumentItem  *pItem;

	for (nStep = 0, nSteps = GetParent()->GetDocument()->EnumSteps(pSteps); nStep < nSteps; nStep++)
	{
		if ((pItem = (CTCProcedureDocumentItem *)pSteps.GetAt(nSteps - nStep - 1)))
		{
			if (pItem->GetSubSteps()->FindStep(pStep, FALSE)) break;
			continue;
		}
	}
	return((nStep < nSteps) ? (CTCProcedureDocumentItem *)pSteps.GetAt(nSteps - nStep - 1) : (CTCProcedureDocumentItem *)NULL);
}

CRect CTCProceduresMonitorItemFlowchartThreadViewStatePane::CalcBreakpointPosition(CTCProcedureDocumentItem *pStep) CONST
{
	CTCProcedureDocumentItem  *pBreakpoint[2];

	for (pBreakpoint[0] = pStep; (pBreakpoint[1] = FindBreakpoint(pBreakpoint[0])) && !pBreakpoint[1]->IsExpanded(); )
	{
		pBreakpoint[0] = pBreakpoint[1];
		continue;
	}
	return CRect(CalcBreakpointIndent(), pBreakpoint[0]->GetPosition().top + (pBreakpoint[0]->GetImageSize().cy - 2 * CalcBreakpointRadius()) / 2, CalcBreakpointIndent() + 2 * CalcBreakpointRadius(), pBreakpoint[0]->GetPosition().top + (pBreakpoint[0]->GetImageSize().cy - 2 * CalcBreakpointRadius()) / 2 + 2 * CalcBreakpointRadius());
}

INT CTCProceduresMonitorItemFlowchartThreadViewStatePane::CalcBreakpointRadius() CONST
{
	CRect  rBreakpoint;

	GetClientRect(rBreakpoint);
	return((rBreakpoint.Width() - 2 * CalcBreakpointIndent()) / 2);
}

INT CTCProceduresMonitorItemFlowchartThreadViewStatePane::CalcBreakpointIndent() CONST
{
	return GetSystemMetrics(SM_CXEDGE);
}

CRect CTCProceduresMonitorItemFlowchartThreadViewStatePane::CalcExecutionpointPosition(CTCProcedureDocumentItem *pStep) CONST
{
	CPoint  ptExecution;
	CTCProcedureDocumentItem  *pExecutionpoint[2];

	for (pExecutionpoint[0] = pStep; (pExecutionpoint[1] = FindContainerStep(pExecutionpoint[0])) && !pExecutionpoint[1]->IsExpanded(); )
	{
		pExecutionpoint[0] = pExecutionpoint[1];
		continue;
	}
	return(((ptExecution = CPoint(pExecutionpoint[0]->GetPosition().CenterPoint().x, pExecutionpoint[0]->GetPosition().top + pExecutionpoint[0]->GetImageSize().cy / 2)).x != 0 && ptExecution.y != 0) ? CRect(CalcExecutionpointIndent(), ptExecution.y - (CalcExecutionpointExtent() - CalcExecutionpointExtent() % 2) / 2, CalcExecutionpointIndent() + CalcExecutionpointExtent(), ptExecution.y - (CalcExecutionpointExtent() - CalcExecutionpointExtent() % 2) / 2 + CalcExecutionpointExtent()) : CRect(0, 0, 0, 0));
}

INT CTCProceduresMonitorItemFlowchartThreadViewStatePane::CalcExecutionpointExtent() CONST
{
	INT  nExtent;
	CRect  rExecutionpoint;

	GetClientRect(rExecutionpoint);
	return(((nExtent = (rExecutionpoint.Width() - 2 * CalcExecutionpointIndent())) % 2) ? (nExtent - 1) : nExtent);
}

INT CTCProceduresMonitorItemFlowchartThreadViewStatePane::CalcExecutionpointIndent() CONST
{
	return GetSystemMetrics(SM_CXEDGE);
}

BOOL CTCProceduresMonitorItemFlowchartThreadViewStatePane::Lock()
{
	return m_pCriticalSection->Lock();
}

BOOL CTCProceduresMonitorItemFlowchartThreadViewStatePane::Unlock()
{
	return m_pCriticalSection->Unlock();
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorItemFlowchartThreadViewStatePane, CWnd)
	//{{AFX_MSG_MAP(CTCProceduresMonitorItemFlowchartThreadViewStatePane)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemFlowchartThreadViewStatePane message handlers

void CTCProceduresMonitorItemFlowchartThreadViewStatePane::OnPaint()
{
	CPaintDC  cDC(this);

	DrawContent(&cDC);
}

void CTCProceduresMonitorItemFlowchartThreadViewStatePane::OnMouseMove(UINT nFlags, CPoint point)
{
	INT  nBreakpoint;
	INT  nBreakpoints;
	CRect  rBreakpoint;
	CString  szToolTipTitle;
	CString  szToolTipText;
	CTCProcedureDocumentItem  *pStep;
	CDatabaseTCProcedureThreadBreakpoint  *pBreakpoint;

	for (nBreakpoint = 0, nBreakpoints = (m_bToolTips) ? (INT)m_pBreakpoints.GetSize() : -1; nBreakpoint < nBreakpoints; nBreakpoint++)
	{
		if ((pStep = ((pBreakpoint = m_pBreakpoints.GetAt(nBreakpoint))) ? (CTCProcedureDocumentItem *)GetParent()->FindStep(pBreakpoint->GetLocation()) : (CTCProcedureDocumentItem *)NULL))
		{
			rBreakpoint.SetRect(CalcBreakpointIndent(), pStep->GetPosition().top + (pStep->GetImageSize().cy - 2 * CalcBreakpointRadius()) / 2, CalcBreakpointIndent() + 2 * CalcBreakpointRadius(), pStep->GetPosition().top + (pStep->GetImageSize().cy - 2 * CalcBreakpointRadius()) / 2 + 2 * CalcBreakpointRadius());
			if ((point.x - rBreakpoint.CenterPoint().x)*(point.x - rBreakpoint.CenterPoint().x) + (point.y - rBreakpoint.CenterPoint().y)*(point.y - rBreakpoint.CenterPoint().y) <= (rBreakpoint.Width()*rBreakpoint.Width()) / 4)
			{
				for (szToolTipTitle.Format(STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_BREAKPOINTSTEPTITLE), (LPCTSTR)pBreakpoint->GetLocation()), szToolTipText = (pBreakpoint->GetOptions() & TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKALWAYS) ? STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_BREAKPOINTBREAKALWAYS) : EMPTYSTRING, szToolTipText = (pBreakpoint->GetOptions() & TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDTRIGGER) ? STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_BREAKPOINTBREAKATFAILEDTRIGGER) : szToolTipText, szToolTipText += (pBreakpoint->GetOptions() & TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDBODY) ? ((!szToolTipText.IsEmpty()) ? (CString(EOL) + STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_BREAKPOINTBREAKATFAILEDBODY)) : STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_BREAKPOINTBREAKATFAILEDBODY)) : EMPTYSTRING, szToolTipText += (pBreakpoint->GetOptions() & TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDCONFIRMATION) ? ((!szToolTipText.IsEmpty()) ? (CString(EOL) + STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_BREAKPOINTBREAKATFAILEDCONFIRMATION)) : STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_BREAKPOINTBREAKATFAILEDCONFIRMATION)) : EMPTYSTRING, szToolTipText += (pBreakpoint->GetOptions() & TCPROCEDURETHREADBREAKPOINT_OPTION_DISABLED) ? (CString(EOL) + STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_BREAKPOINTDISABLED)) : (CString(EOL) + STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_BREAKPOINTENABLED)); IsWindow(m_wndToolTip.GetSafeHwnd()) && m_szToolTip != szToolTipTitle; )
				{
					m_wndToolTip.Destroy();
					m_szToolTip.Empty();
					break;
				}
				if (!IsWindow(m_wndToolTip.GetSafeHwnd()) && m_szToolTip != szToolTipTitle && (nFlags & MK_RBUTTON) != MK_RBUTTON)
				{
					m_wndToolTip.Create(this, point, (m_szToolTip = szToolTipTitle), szToolTipText, TRUE);
					break;
				}
				break;
			}
		}
	}
	if (nBreakpoint == nBreakpoints)
	{
		m_wndToolTip.Destroy();
		m_szToolTip.Empty();
	}
	CWnd::OnMouseMove(nFlags, point);
}

void CTCProceduresMonitorItemFlowchartThreadViewStatePane::OnLButtonDown(UINT nFlags, CPoint point)
{
	INT  nStep;
	INT  nSteps;
	INT  nBreakpoint[2];
	INT  nBreakpoints[2];
	BOOL  bBreakpoints;
	CRect  rBreakpoint;
	CString  szStep;
	CPtrArray  pSteps;
	CStringArray  szSteps;
	CTCProcedureDocumentItem  *pStep;
	CDatabaseTCProcedureThreadBreakpoint  *pBreakpoint;

	for (nBreakpoint[0] = 0, nBreakpoints[0] = (m_bBreaks) ? (INT)m_pBreakpoints.GetSize() : -1, bBreakpoints = FALSE; nBreakpoint[0] < nBreakpoints[0]; nBreakpoint[0]++)
	{
		if ((pStep = ((pBreakpoint = m_pBreakpoints.GetAt(nBreakpoint[0]))) ? (CTCProcedureDocumentItem *)GetParent()->FindStep(pBreakpoint->GetLocation()) : (CTCProcedureDocumentItem *)NULL))
		{
			rBreakpoint.SetRect(CalcBreakpointIndent(), pStep->GetPosition().top + (pStep->GetImageSize().cy - 2 * CalcBreakpointRadius()) / 2, CalcBreakpointIndent() + 2 * CalcBreakpointRadius(), pStep->GetPosition().top + (pStep->GetImageSize().cy - 2 * CalcBreakpointRadius()) / 2 + 2 * CalcBreakpointRadius());
			if ((point.x - rBreakpoint.CenterPoint().x)*(point.x - rBreakpoint.CenterPoint().x) + (point.y - rBreakpoint.CenterPoint().y)*(point.y - rBreakpoint.CenterPoint().y) <= (rBreakpoint.Width()*rBreakpoint.Width()) / 4)
			{
				for (nStep = 0, nSteps = GetParent()->EnumSteps(point.y, pSteps, szSteps); nStep < nSteps; nStep = nStep + 1)
				{
					if ((pStep = (CTCProcedureDocumentItem *)pSteps.GetAt(nStep)) && pStep->GetName() == pBreakpoint->GetLocation())
					{
						for (nBreakpoint[1] = 0, nBreakpoints[1] = (INT)m_szBreakpoints.GetSize(); nBreakpoint[1] < nBreakpoints[1]; nBreakpoint[1]++)
						{
							if (m_szBreakpoints.GetAt(nBreakpoint[1]) == pBreakpoint->GetLocation())
							{
								m_szBreakpoints.RemoveAt(nBreakpoint[1]);
								pStep->SetName(EMPTYSTRING);
								break;
							}
						}
						bBreakpoints = TRUE;
						break;
					}
				}
				m_pBreakpoints.RemoveAt(nBreakpoint[0]);
				delete pBreakpoint;
				nBreakpoints[0]--;
				nBreakpoint[0]--;
				break;
			}
		}
	}
	for (nStep = 0, nSteps = (nBreakpoint[0] == nBreakpoints[0]) ? GetParent()->EnumSteps(point.y, pSteps, szSteps) : 0; nStep < nSteps; nStep++)
	{
		if ((pStep = (CTCProcedureDocumentItem *)pSteps.GetAt(nStep)) && pStep->IsActivated())
		{
			if ((pBreakpoint = new CDatabaseTCProcedureThreadBreakpoint))
			{
				pBreakpoint->SetLocation((szStep = szSteps.GetAt(nStep)));
				pBreakpoint->SetOptions(TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKALWAYS);
				if (m_pBreakpoints.Add(pBreakpoint) >= 0)
				{
					if (pStep->GetName().IsEmpty())
					{
						m_szBreakpoints.Add(szStep);
						pStep->SetName(szStep);
						bBreakpoints = TRUE;
					}
					break;
				}
				delete pBreakpoint;
			}
		}
	}
	if (nBreakpoint[0] < nBreakpoints[0] || nStep < nSteps)
	{
		for (GetParent()->UpdateAllBreakpoints(); bBreakpoints; )
		{
			GetParent()->UpdateAllSteps();
			break;
		}
		DrawContent();
	}
	if (IsWindow(m_wndToolTip.GetSafeHwnd()) && nBreakpoint[0] < nBreakpoints[0]) m_wndToolTip.Destroy();
	CWnd::OnLButtonDown(nFlags, point);
}

void CTCProceduresMonitorItemFlowchartThreadViewStatePane::OnRButtonDown(UINT nFlags, CPoint point)
{
	INT  nItem;
	INT  nItems;
	INT  nItemID;
	INT  nBreakpoint;
	INT  nBreakpoints;
	CRect  rBreakpoint;
	CPoint  ptBreakpointMenu;
	CString  szBreakpointMenuItem;
	CLocaleMenu  cBreakpointMenu[2];
	CTCProcedureDocumentItem  *pStep;
	CDatabaseTCProcedureThreadBreakpoint  *pBreakpoint;

	for (nBreakpoint = 0, nBreakpoints = (INT)m_pBreakpoints.GetSize(), ptBreakpointMenu = point, ClientToScreen(&ptBreakpointMenu); nBreakpoint < nBreakpoints; nBreakpoint++)
	{
		if ((pStep = ((pBreakpoint = m_pBreakpoints.GetAt(nBreakpoint))) ? (CTCProcedureDocumentItem *)GetParent()->FindStep(pBreakpoint->GetLocation()) : (CTCProcedureDocumentItem *)NULL))
		{
			rBreakpoint.SetRect(CalcBreakpointIndent(), pStep->GetPosition().top + (pStep->GetImageSize().cy - 2 * CalcBreakpointRadius()) / 2, CalcBreakpointIndent() + 2 * CalcBreakpointRadius(), pStep->GetPosition().top + (pStep->GetImageSize().cy - 2 * CalcBreakpointRadius()) / 2 + 2 * CalcBreakpointRadius());
			if ((point.x - rBreakpoint.CenterPoint().x)*(point.x - rBreakpoint.CenterPoint().x) + (point.y - rBreakpoint.CenterPoint().y)*(point.y - rBreakpoint.CenterPoint().y) <= (rBreakpoint.Width()*rBreakpoint.Width()) / 4)
			{
				for (nItem = 0, nItems = (cBreakpointMenu[0].CreatePopupMenu() && cBreakpointMenu[1].LoadMenu(IDR_TCPROCEDURESMONITORFLOATINGMENU)) ? cBreakpointMenu[1].GetMenuItemCount() : 0, m_wndToolTip.Destroy(); nItem < nItems; nItem++)
				{
					if ((nItemID = cBreakpointMenu[1].GetMenuItemID(nItem)) >= 0 && (!nItemID || cBreakpointMenu[1].GetMenuString(nItem, szBreakpointMenuItem, MF_BYPOSITION) > 0))
					{
						cBreakpointMenu[0].AppendMenu(((nItemID > 0) ? MF_STRING : MF_SEPARATOR) | MF_ENABLED, (UINT_PTR)nItemID, szBreakpointMenuItem);
						cBreakpointMenu[0].CheckMenuItem(nItemID, (((pBreakpoint->GetOptions() & TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKALWAYS) && nItemID == IDM_TCPROCEDURESMONITORBREAKALWAYS)) ? (MF_CHECKED | MF_BYCOMMAND) : ((cBreakpointMenu[0].GetMenuState(nItemID, MF_BYCOMMAND) & MF_CHECKED) | MF_BYCOMMAND));
						cBreakpointMenu[0].CheckMenuItem(nItemID, (((pBreakpoint->GetOptions() & TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDTRIGGER) && nItemID == IDM_TCPROCEDURESMONITORBREAKATFAILEDTRIGGER)) ? (MF_CHECKED | MF_BYCOMMAND) : ((cBreakpointMenu[0].GetMenuState(nItemID, MF_BYCOMMAND) & MF_CHECKED) | MF_BYCOMMAND));
						cBreakpointMenu[0].CheckMenuItem(nItemID, (((pBreakpoint->GetOptions() & TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDBODY) && nItemID == IDM_TCPROCEDURESMONITORBREAKATFAILEDBODY)) ? (MF_CHECKED | MF_BYCOMMAND) : ((cBreakpointMenu[0].GetMenuState(nItemID, MF_BYCOMMAND) & MF_CHECKED) | MF_BYCOMMAND));
						cBreakpointMenu[0].CheckMenuItem(nItemID, (((pBreakpoint->GetOptions() & TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDCONFIRMATION) && nItemID == IDM_TCPROCEDURESMONITORBREAKATFAILEDCONFIRMATION)) ? (MF_CHECKED | MF_BYCOMMAND) : ((cBreakpointMenu[0].GetMenuState(nItemID, MF_BYCOMMAND) & MF_CHECKED) | MF_BYCOMMAND));
						cBreakpointMenu[0].CheckMenuItem(nItemID, (((pBreakpoint->GetOptions() & TCPROCEDURETHREADBREAKPOINT_OPTION_DISABLED) && nItemID == IDM_TCPROCEDURESMONITORDISABLEBREAKPOINT)) ? (MF_CHECKED | MF_BYCOMMAND) : ((cBreakpointMenu[0].GetMenuState(nItemID, MF_BYCOMMAND) & MF_CHECKED) | MF_BYCOMMAND));
					}
				}
				if (nItems > 0)
				{
					if ((nItemID = cBreakpointMenu[0].TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD, ptBreakpointMenu.x, ptBreakpointMenu.y, GetParent()->GetParentDisplay())) == IDM_TCPROCEDURESMONITORBREAKALWAYS)
					{
						pBreakpoint->SetOptions((pBreakpoint->GetOptions() & ~(TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDTRIGGER | TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDBODY | TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDCONFIRMATION)) | TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKALWAYS);
						GetParent()->UpdateAllBreakpoints();
						DrawContent();
					}
					if (nItemID == IDM_TCPROCEDURESMONITORBREAKATFAILEDTRIGGER)
					{
						pBreakpoint->SetOptions(((pBreakpoint->GetOptions() & (TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDTRIGGER | TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDBODY | TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDCONFIRMATION)) == TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDTRIGGER) ? ((pBreakpoint->GetOptions() & ~TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDTRIGGER) | TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKALWAYS) : ((pBreakpoint->GetOptions() ^ TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDTRIGGER) & ~TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKALWAYS));
						GetParent()->UpdateAllBreakpoints();
						DrawContent();
					}
					if (nItemID == IDM_TCPROCEDURESMONITORBREAKATFAILEDBODY)
					{
						pBreakpoint->SetOptions(((pBreakpoint->GetOptions() & (TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDTRIGGER | TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDBODY | TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDCONFIRMATION)) == TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDBODY) ? ((pBreakpoint->GetOptions() & ~TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDBODY) | TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKALWAYS) : ((pBreakpoint->GetOptions() ^ TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDBODY) & ~TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKALWAYS));
						GetParent()->UpdateAllBreakpoints();
						DrawContent();
					}
					if (nItemID == IDM_TCPROCEDURESMONITORBREAKATFAILEDCONFIRMATION)
					{
						pBreakpoint->SetOptions(((pBreakpoint->GetOptions() & (TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDTRIGGER | TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDBODY | TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDCONFIRMATION)) == TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDCONFIRMATION) ? ((pBreakpoint->GetOptions() & ~TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDCONFIRMATION) | TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKALWAYS) : ((pBreakpoint->GetOptions() ^ TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDCONFIRMATION) & ~TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKALWAYS));
						GetParent()->UpdateAllBreakpoints();
						DrawContent();
					}
					if (nItemID == IDM_TCPROCEDURESMONITORDISABLEBREAKPOINT)
					{
						pBreakpoint->SetOptions(pBreakpoint->GetOptions() ^ TCPROCEDURETHREADBREAKPOINT_OPTION_DISABLED);
						GetParent()->UpdateAllBreakpoints();
						DrawContent();
					}
					cBreakpointMenu[1].DestroyMenu();
				}
				break;
			}
		}
	}
	CWnd::OnRButtonDown(nFlags, point);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemFlowchartThreadView

IMPLEMENT_DYNCREATE(CTCProceduresMonitorItemFlowchartThreadView, CScrollView)

CTCProceduresMonitorItemFlowchartThreadView::CTCProceduresMonitorItemFlowchartThreadView() : CScrollView()
{
	CFontTools  cFontTools(&m_lfStepsLabelFont);

	m_ptScroll.x = 0;
	m_ptScroll.y = 0;
	m_bBreaks = TRUE;
	m_bRunning = FALSE;
	m_bToolTips = TRUE;
	m_hToolTipCursor = (HCURSOR)NULL;
	m_nStepsLabelColor = GetSysColor(COLOR_WINDOWTEXT);
	m_nBackgroundColor = GetSysColor(COLOR_WINDOW);
	m_pFlowchart = (CTCProcedureDocument *)NULL;
	m_pParentWnd = (CWnd *)NULL;
}

BOOL CTCProceduresMonitorItemFlowchartThreadView::Create(CWnd *pParentWnd, CONST RECT &rect, UINT nID, BOOL bVisible)
{
	CFontTools  cFontTools;
	CTCProcedureDocumentItem  *pStep[2];
	CCreateContext  cContext;

	if ((m_pFlowchart = new CTCProcedureDocument))
	{
		for (cContext.m_pCurrentDoc = m_pFlowchart; CScrollView::Create(AfxRegisterWndClass(CS_DBLCLKS | CS_NOCLOSE, LoadCursor((HINSTANCE)NULL, IDC_ARROW), GetSysColorBrush(COLOR_WINDOW)), (LPCTSTR)NULL, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | ((bVisible) ? WS_VISIBLE : 0), rect, (m_pParentWnd = pParentWnd), nID, &cContext); )
		{
			if ((pStep[0] = new CTCProcedureDocumentStartItem))
			{
				if ((pStep[1] = new CTCProcedureDocumentEndItem))
				{
					pStep[0]->SetPosition(CRect(CalcStatePaneMarginSize() + TCPROCEDUREDOCUMENT_DEFAULT_STEPHORZINDENT, TCPROCEDUREDOCUMENT_DEFAULT_MARGIN + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT + cFontTools.QueryHeight(&m_lfStepsLabelFont), CalcStatePaneMarginSize() + TCPROCEDUREDOCUMENT_DEFAULT_STEPHORZINDENT + pStep[0]->GetImageSize().cx, TCPROCEDUREDOCUMENT_DEFAULT_MARGIN + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT + cFontTools.QueryHeight(&m_lfStepsLabelFont) + pStep[0]->GetImageSize().cy));
					pStep[1]->SetPosition(CRect(CalcStatePaneMarginSize() + TCPROCEDUREDOCUMENT_DEFAULT_STEPHORZINDENT, pStep[0]->GetPosition().bottom + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL, CalcStatePaneMarginSize() + TCPROCEDUREDOCUMENT_DEFAULT_STEPHORZINDENT + pStep[1]->GetImageSize().cx, pStep[0]->GetPosition().bottom + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + pStep[1]->GetImageSize().cy));
					GetDocument()->AddStep(pStep[0]);
					GetDocument()->AddStep(pStep[1]);
					return TRUE;
				}
				delete pStep[0];
			}
			break;
		}
		delete m_pFlowchart;
		m_pFlowchart = (CTCProcedureDocument *)NULL;
	}
	return FALSE;
}

VOID CTCProceduresMonitorItemFlowchartThreadView::SetBreakpoints(CONST CDatabaseTCProcedureThreadBreakpoints &pBreakpoints)
{
	m_wndStatePane.SetBreakpoints(pBreakpoints);
}

INT CTCProceduresMonitorItemFlowchartThreadView::GetBreakpoints(CDatabaseTCProcedureThreadBreakpoints &pBreakpoints) CONST
{
	return m_wndStatePane.GetBreakpoints(pBreakpoints);
}

BOOL CTCProceduresMonitorItemFlowchartThreadView::SetSteps(CONST CTCProcedureDocument *pFlowchart)
{
	CFontTools  cFontTools;
	CTCProcedureDocumentItem  *pStep[2];

	if (!pFlowchart->GetStepCount())
	{
		if ((pStep[0] = new CTCProcedureDocumentStartItem))
		{
			if ((pStep[1] = new CTCProcedureDocumentEndItem))
			{
				pStep[0]->SetPosition(CRect(CalcStatePaneMarginSize() + TCPROCEDUREDOCUMENT_DEFAULT_STEPHORZINDENT, TCPROCEDUREDOCUMENT_DEFAULT_MARGIN + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT + cFontTools.QueryHeight(&m_lfStepsLabelFont), CalcStatePaneMarginSize() + TCPROCEDUREDOCUMENT_DEFAULT_STEPHORZINDENT + pStep[0]->GetImageSize().cx, TCPROCEDUREDOCUMENT_DEFAULT_MARGIN + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT + cFontTools.QueryHeight(&m_lfStepsLabelFont) + pStep[0]->GetImageSize().cy));
				pStep[1]->SetPosition(CRect(CalcStatePaneMarginSize() + TCPROCEDUREDOCUMENT_DEFAULT_STEPHORZINDENT, pStep[0]->GetPosition().bottom + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL, CalcStatePaneMarginSize() + TCPROCEDUREDOCUMENT_DEFAULT_STEPHORZINDENT + pStep[1]->GetImageSize().cx, pStep[0]->GetPosition().bottom + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + pStep[1]->GetImageSize().cy));
				GetDocument()->DeleteContents();
				GetDocument()->AddStep(pStep[0]);
				GetDocument()->AddStep(pStep[1]);
				m_wndStatePane.UpdateExecutionpoint(EMPTYSTRING, 0);
				SetStepsLabelFont(&m_lfStepsLabelFont);
				SetStepsLabelColor(m_nStepsLabelColor);
				UpdateAllSteps(FALSE);
				return TRUE;
			}
			delete pStep[1];
		}
		return FALSE;
	}
	if (GetDocument()->Copy(pFlowchart))
	{
		m_wndStatePane.UpdateExecutionpoint(EMPTYSTRING, 0);
		SetStepsLabelFont(&m_lfStepsLabelFont);
		SetStepsLabelColor(m_nStepsLabelColor);
		UpdateAllSteps(FALSE);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemFlowchartThreadView::GetSteps(CTCProcedureDocument *pFlowchart) CONST
{
	return pFlowchart->Copy(GetDocument());
}

INT CTCProceduresMonitorItemFlowchartThreadView::EnumSteps(INT nY, CPtrArray &pSteps, CStringArray &szSteps) CONST
{
	INT  nStep;
	INT  nSteps;
	CPtrArray  pNamedSteps;
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pItem[2];

	if ((pDocument = new CTCProcedureDocument))
	{
		for (nStep = 0, nSteps = (pDocument->Copy(GetDocument()) && GetDocument()->EnumSteps(pSteps) == pDocument->EnumSteps(pNamedSteps, FALSE, TRUE)) ? (INT)pSteps.GetSize() : 0, szSteps.RemoveAll(); nStep < nSteps; nStep++)
		{
			if ((pItem[1] = ((pItem[0] = (CTCProcedureDocumentItem *)pSteps.GetAt(nStep)) && pItem[0]->GetPosition().top <= nY  &&  pItem[0]->GetPosition().top + pItem[0]->GetImageSize().cy >= nY) ? (CTCProcedureDocumentItem *)pNamedSteps.GetAt(nStep) : (CTCProcedureDocumentItem *)NULL))
			{
				szSteps.Add(pItem[1]->GetName());
				continue;
			}
			pNamedSteps.RemoveAt(nStep);
			pSteps.RemoveAt(nStep);
			nSteps--;
			nStep--;
		}
		delete pDocument;
	}
	return((INT)pSteps.GetSize());
}

BOOL CTCProceduresMonitorItemFlowchartThreadView::SetActiveStep(CONST CTCProcedureDocumentItem *pStep)
{
	POSITION  lPosition;
	CTCProcedureDocumentItem  *pItem;

	for (; (pItem = GetActiveStep()) && pItem != pStep; )
	{
		pItem->Activate(FALSE);
		break;
	}
	if ((pItem = FindStep((lPosition = FindStep(pStep, TRUE)))))
	{
		for (pItem->Activate(); GetActiveStep(); )
		{
			UpdateAllSteps();
			return TRUE;
		}
	}
	UpdateAllSteps();
	return FALSE;
}

CTCProcedureDocumentItem *CTCProceduresMonitorItemFlowchartThreadView::GetActiveStep(BOOL bAll) CONST
{
	INT  nStep;
	INT  nSteps;
	CPtrArray  pSteps;
	CTCProcedureDocumentItem  *pItem;

	for (nStep = 0, nSteps = GetDocument()->EnumSteps(pSteps, bAll); nStep < nSteps; nStep++)
	{
		if ((pItem = (CTCProcedureDocumentItem *)pSteps.GetAt(nStep)) && (pItem->IsActivated() || (bAll  &&  pItem->IsSelected()))) break;
		continue;
	}
	return((nStep < nSteps) ? (CTCProcedureDocumentItem *)pSteps.GetAt(nStep) : (CTCProcedureDocumentItem *)NULL);
}

CTCProcedureDocumentItem *CTCProceduresMonitorItemFlowchartThreadView::FindStep(LPCTSTR pszName) CONST
{
	INT  nStep;
	INT  nSteps;
	CPtrArray  pSteps;
	CTCProcedureDocumentItem  *pItem;

	for (nStep = 0, nSteps = GetDocument()->EnumSteps(pSteps); nStep < nSteps; nStep++)
	{
		if ((pItem = (CTCProcedureDocumentItem *)pSteps.GetAt(nStep)) && pItem->GetName() == pszName) break;
		continue;
	}
	return((nStep < nSteps) ? (CTCProcedureDocumentItem *)pSteps.GetAt(nStep) : (CTCProcedureDocumentItem *)NULL);
}

INT CTCProceduresMonitorItemFlowchartThreadView::GetTotalSteps() CONST
{
	return GetDocument()->GetStepCount();
}

VOID CTCProceduresMonitorItemFlowchartThreadView::SetStepsLabelFont(CONST LOGFONT *plfFont)
{
	INT  nStep;
	INT  nSteps;
	INT  nOffset;
	CFont  cFont;
	CPtrArray  pSteps;
	CTCProcedureDocumentItem  *pStep;

	for (nStep = 0, nSteps = (cFont.CreateFontIndirect(plfFont)) ? GetDocument()->EnumSteps(pSteps, TRUE) : 0; nStep < nSteps; nStep++)
	{
		if ((pStep = (CTCProcedureDocumentItem *)pSteps.GetAt(nStep)))
		{
			pStep->SetLabelFont(&cFont);
			continue;
		}
	}
	if ((pStep = GetDocument()->GetFirstStep()))
	{
		pStep->SetPosition(pStep->GetPosition() + CPoint(0, (nOffset = abs(plfFont->lfHeight) - abs(m_lfStepsLabelFont.lfHeight))));
		AdjustSteps(pStep, nOffset);
	}
	CopyMemory(&m_lfStepsLabelFont, plfFont, sizeof(LOGFONT));
	UpdateAllSteps();
}

BOOL CTCProceduresMonitorItemFlowchartThreadView::GetStepsLabelFont(LOGFONT *plfFont) CONST
{
	CFont  cFont;
	CTCProcedureDocumentItem  *pStep;

	return(((pStep = GetDocument()->GetFirstStep())) ? (pStep->GetLabelFont(&cFont) && cFont.GetLogFont(plfFont) > 0) : FALSE);
}

VOID CTCProceduresMonitorItemFlowchartThreadView::SetStepsLabelColor(COLORREF nColor)
{
	INT  nStep;
	INT  nSteps;
	CPtrArray  pSteps;
	CTCProcedureDocumentItem  *pStep;

	for (nStep = 0, nSteps = GetDocument()->EnumSteps(pSteps, TRUE), m_nStepsLabelColor = nColor; nStep < nSteps; nStep++)
	{
		if ((pStep = (CTCProcedureDocumentItem *)pSteps.GetAt(nStep)))
		{
			pStep->SetLabelColor(nColor);
			continue;
		}
	}
	UpdateAllSteps();
}

COLORREF CTCProceduresMonitorItemFlowchartThreadView::GetStepsLabelColor() CONST
{
	CTCProcedureDocumentItem  *pStep;

	return(((pStep = GetDocument()->GetFirstStep())) ? pStep->GetLabelColor() : GetSysColor(COLOR_WINDOWTEXT));
}

VOID CTCProceduresMonitorItemFlowchartThreadView::SetBackgroundColor(COLORREF nColor)
{
	m_nBackgroundColor = nColor;
	UpdateAllSteps();
}

COLORREF CTCProceduresMonitorItemFlowchartThreadView::GetBackgroundColor() CONST
{
	return m_nBackgroundColor;
}

VOID CTCProceduresMonitorItemFlowchartThreadView::AllowExecutionBreaks(BOOL bAllow)
{
	m_wndStatePane.AllowExecutionBreaks((m_bBreaks = bAllow));
}

BOOL CTCProceduresMonitorItemFlowchartThreadView::AreExecutionBreaksAllowed() CONST
{
	return m_bBreaks;
}

VOID CTCProceduresMonitorItemFlowchartThreadView::EnableToolTipMode(BOOL bEnable)
{
	m_wndStatePane.EnableToolTipMode((m_bToolTips = bEnable));
}

BOOL CTCProceduresMonitorItemFlowchartThreadView::IsToolTipModeEnabled() CONST
{
	return m_bToolTips;
}

VOID CTCProceduresMonitorItemFlowchartThreadView::UpdateAllSteps(CPtrArray &pSteps)
{
	GetDocument()->EnumSteps(pSteps);
}
VOID CTCProceduresMonitorItemFlowchartThreadView::UpdateAllSteps(BOOL bRedraw)
{
	CPoint  ptScroll;

	for (SetScrollSizes(MM_TEXT, CalcScrollSizes()), m_wndStatePane.MoveWindow(CalcStatePanePosition()), GetParentDisplay()->UpdateBars(); (ptScroll = GetScrollPosition()) != m_ptScroll; )
	{
		m_ptScroll = ptScroll;
		break;
	}
	if (bRedraw)
	{
		DrawContent();
		return;
	}
}
VOID CTCProceduresMonitorItemFlowchartThreadView::UpdateAllSteps(UINT nState, CONST CStringArray &szSteps, CONST CUIntArray &nStates)
{
	INT  nStep[2];
	INT  nSteps[2];
	CPtrArray  pSteps[2];
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pStep[3];

	for (nStep[0] = 0, nSteps[0] = (INT)szSteps.GetSize(), GetDocument()->EnumSteps(pSteps[0]), pDocument = (CTCProcedureDocument *)NULL, m_bRunning = ((nState & TCPROCEDURETHREAD_RUNNINGSTATE_NOTRUNNING) != TCPROCEDURETHREAD_RUNNINGSTATE_NOTRUNNING && nState != 0) ? TRUE : FALSE; nStep[0] < nSteps[0]; nStep[0]++)
	{
		for (nStep[1] = 0, nSteps[1] = ((pDocument = (!pDocument) ? new CTCProcedureDocument : pDocument) && ((!pDocument->GetStepCount() && pDocument->Copy(GetDocument()) && pDocument->EnumSteps(pSteps[1], FALSE, TRUE) == pSteps[0].GetSize()) || pDocument->GetStepCount() > 0)) ? (INT)pSteps[1].GetSize() : 0; nStep[1] < nSteps[1]; nStep[1]++)
		{
			if ((pStep[0] = ((pStep[1] = (CTCProcedureDocumentItem *)pSteps[1].GetAt(nStep[1])) && pStep[1]->GetName() == szSteps.GetAt(nStep[0])) ? (CTCProcedureDocumentItem *)pSteps[0].GetAt(nStep[1]) : (CTCProcedureDocumentItem *)NULL))
			{
				for (; (pStep[1] = GetActiveStep()) != pStep[0] && pStep[1] != (CTCProcedureDocumentItem *)NULL; )
				{
					pStep[1]->Activate(FALSE);
					break;
				}
				for (pStep[0]->SetState(nStates.GetAt(nStep[0])); ((nState & TCPROCEDURETHREAD_RUNNINGSTATE_RUNNING) || (nState & TCPROCEDURETHREAD_RUNNINGSTATE_STOPPED)) && nStep[0] == nSteps[0] - 1; )
				{
					m_wndStatePane.UpdateExecutionpoint(szSteps.GetAt(nStep[0]), nState);
					pStep[0]->Activate();
					break;
				}
				if ((pStep[1] = (nState & TCPROCEDURETHREAD_RUNNINGSTATE_NOTRUNNING) ? GetDocument()->GetLastStep() : (CTCProcedureDocumentItem *)NULL) && pStep[1]->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_END)
				{
					for (m_wndStatePane.UpdateExecutionpoint(STRING(IDS_TELECOMMANDPROCEDURESTEP_FLOWCONTROL_END), nState); (pStep[2] = GetActiveStep()); )
					{
						pStep[2]->Activate(FALSE);
						break;
					}
				}
				break;
			}
		}
		if (nStep[0] == nSteps[0] - 1)
		{
			delete pDocument;
			continue;
		}
	}
	for (nStep[1] = 0, nSteps[1] = (!nState && !nSteps[0]) ? (INT)pSteps[0].GetSize() : 0; nStep[1] < nSteps[1]; nStep[1]++)
	{
		if ((pStep[0] = (CTCProcedureDocumentItem *)pSteps[0].GetAt(nStep[1])))
		{
			for (pStep[0]->SetState(0); nStep[1] == nSteps[1] - 1; )
			{
				m_wndStatePane.UpdateExecutionpoint(EMPTYSTRING, 0);
				break;
			}
		}
	}
	if ((nState & TCPROCEDURETHREAD_ACTIONSTATE_ABORT) != TCPROCEDURETHREAD_ACTIONSTATE_ABORT)
	{
		if ((pStep[0] = (nState & TCPROCEDURETHREAD_AUTHORITY_DISABLED) ? GetDocument()->GetFirstStep() : (CTCProcedureDocumentItem *)NULL) && pStep[0]->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_START)
		{
			for (m_wndStatePane.UpdateExecutionpoint(STRING(IDS_TELECOMMANDPROCEDURESTEP_FLOWCONTROL_START), nState); (pStep[1] = GetActiveStep()); )
			{
				pStep[1]->Activate(FALSE);
				break;
			}
		}
		if ((pStep[0] = (nState & TCPROCEDURETHREAD_RUNNINGSTATE_NOTRUNNING) ? GetDocument()->GetLastStep() : (CTCProcedureDocumentItem *)NULL) && pStep[0]->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_END)
		{
			for (m_wndStatePane.UpdateExecutionpoint(STRING(IDS_TELECOMMANDPROCEDURESTEP_FLOWCONTROL_END), nState); (pStep[1] = GetActiveStep()); )
			{
				pStep[1]->Activate(FALSE);
				break;
			}
		}
	}
	for (; nState & TCPROCEDURETHREAD_ACTIONSTATE_ABORT; )
	{
		m_wndStatePane.UpdateExecutionpoint(nState);
		break;
	}
	DrawContent();
}

BOOL CTCProceduresMonitorItemFlowchartThreadView::UpdateAllBreakpoints()
{
	INT  nIndex;
	INT  nBreakpoint;
	INT  nBreakpoints;
	CDatabaseTCProcedureThread  *pThread;
	CDatabaseTCProcedureThreadBreakpoint  *pBreakpoint;
	CDatabaseTCProcedureThreadBreakpoints  pBreakpoints[2];
	CTCProceduresMonitorItem  cProcedure;

	if ((pThread = (GetParentDisplay()->GetProcedureInfo((nIndex = GetParentDisplay()->GetCurProcedure()), &cProcedure, FALSE)) ? cProcedure.GetAt(GetDlgCtrlID()) : (CDatabaseTCProcedureThread *)NULL))
	{
		for (nBreakpoint = 0, nBreakpoints = pThread->GetBreakpoints(pBreakpoints[0]); nBreakpoint < nBreakpoints; nBreakpoint++)
		{
			if ((pBreakpoint = pBreakpoints[0].GetAt(nBreakpoint)) && !pBreakpoint->GetLocation().IsEmpty())
			{
				pBreakpoints[0].RemoveAt(nBreakpoint);
				delete pBreakpoint;
				nBreakpoints--;
				nBreakpoint--;
			}
		}
		for (nBreakpoint = 0, nBreakpoints = m_wndStatePane.GetBreakpoints(pBreakpoints[1]); nBreakpoint < nBreakpoints; nBreakpoint++)
		{
			if ((pBreakpoint = pBreakpoints[1].GetAt(nBreakpoint)) && !pBreakpoint->GetLocation().IsEmpty())
			{
				pBreakpoints[0].Add(pBreakpoints[1].GetAt(nBreakpoint));
				pBreakpoints[1].RemoveAt(nBreakpoint);
				nBreakpoints--;
				nBreakpoint--;
			}
		}
		return((pThread->SetBreakpoints(pBreakpoints[0]) && GetParentDisplay()->SetProcedureInfo(nIndex, &cProcedure, FALSE)) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemFlowchartThreadView::HasImage() CONST
{
	return((GetDocument()->GetStepCount() > 0) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorItemFlowchartThreadView::GetPrintProperties(CMetaFileDC *pMetaDC) CONST
{
	CDC  cDC[2];
	INT  nOldMode;
	CPoint  pt[2];
	CBitmap  cBitmap[2];
	CBitmap  *pOldBitmap[2];
	POSITION  lPosition;
	BLENDFUNCTION  sBlend;
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pStep[2];

	if ((pStep[0] = GetActiveStep()))
	{
		if (pStep[0]->IsActivated())
		{
			if (pStep[0]->IsExpanded())
			{
				if (cDC[0].CreateCompatibleDC(pMetaDC))
				{
					if (cDC[1].CreateCompatibleDC(pMetaDC))
					{
						if (cBitmap[0].CreateCompatibleBitmap(pMetaDC, pStep[0]->GetPosition().Width(), pStep[0]->GetPosition().Height()))
						{
							if (cBitmap[1].CreateCompatibleBitmap(pMetaDC, pStep[0]->GetPosition().Width(), pStep[0]->GetPosition().Height()))
							{
								if ((pOldBitmap[0] = cDC[0].SelectObject(&cBitmap[0])))
								{
									if ((pOldBitmap[1] = cDC[1].SelectObject(&cBitmap[1])))
									{
										nOldMode = cDC[0].SetROP2(R2_MERGEPEN);
										cDC[0].FillSolidRect(0, 0, pStep[0]->GetPosition().Width(), pStep[0]->GetPosition().Height(), VGA_COLOR_WHITE);
										cDC[0].FillSolidRect(0, 0, pStep[0]->GetPosition().Width(), pStep[0]->GetPosition().Height(), TCPROCEDUREDOCUMENTITEM_BACKGROUNDCOLOR);
										for (sBlend.BlendFlags = 0, sBlend.BlendOp = AC_SRC_OVER, sBlend.AlphaFormat = 0, sBlend.SourceConstantAlpha = TCPROCEDUREDOCUMENTITEM_BACKGROUNDALPHA; TRUE; )
										{
											cDC[1].FillSolidRect(0, 0, pStep[0]->GetPosition().Width(), pStep[0]->GetPosition().Height(), VGA_COLOR_WHITE);
											cDC[1].AlphaBlend(0, 0, pStep[0]->GetPosition().Width(), pStep[0]->GetPosition().Height(), &cDC[0], 0, 0, pStep[0]->GetPosition().Width(), pStep[0]->GetPosition().Height(), sBlend);
											pMetaDC->FillSolidRect(0, 0, GetTotalSize().cx, GetTotalSize().cy, m_nBackgroundColor);
											pMetaDC->BitBlt(pStep[0]->GetPosition().left, pStep[0]->GetPosition().top + pStep[0]->GetImageSize().cy / 2, pStep[0]->GetPosition().Width(), pStep[0]->GetPosition().Height() - pStep[0]->GetImageSize().cy / 2, &cDC[1], 0, 0, SRCCOPY);
											pMetaDC->BitBlt(pStep[0]->GetPosition().left + pStep[0]->GetImageSize().cx / 2, pStep[0]->GetPosition().top, pStep[0]->GetPosition().Width() - pStep[0]->GetImageSize().cx / 2, pStep[0]->GetImageSize().cy / 2, &cDC[1], 0, 0, SRCCOPY);
											break;
										}
										cDC[1].SelectObject(pOldBitmap[1]);
										cDC[0].SetROP2(nOldMode);
									}
									cDC[0].SelectObject(pOldBitmap[0]);
								}
								cBitmap[1].DeleteObject();
							}
							cBitmap[0].DeleteObject();
						}
						cDC[1].DeleteDC();
					}
					cDC[0].DeleteDC();
				}
			}
		}
	}
	for (; (pStep[0] = GetActiveStep()) && (!pStep[0]->IsActivated() || !pStep[0]->IsExpanded()); )
	{
		pMetaDC->FillSolidRect(0, 0, GetTotalSize().cx, GetTotalSize().cy, m_nBackgroundColor);
		break;
	}
	for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL, pStep[0] = pStep[1] = (CTCProcedureDocumentItem *)NULL; lPosition; pStep[1] = pStep[0])
	{
		if ((pStep[0] = pDocument->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			if (pStep[1] && pStep[1]->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_GOTO)
			{
				pt[0] = pStep[1]->CalcConnectionPoint(FALSE, pStep[1]->IsExpanded());
				pt[1] = pStep[0]->CalcConnectionPoint(TRUE);
				CTCProcedureDocumentItem::DrawConnectionLine(pMetaDC, pt[0], pt[1]);
			}
		}
	}
	for (lPosition = pDocument->GetStartPosition(); lPosition; )
	{
		if ((pStep[0] = pDocument->GetNextStep(lPosition)))
		{
			pStep[0]->Draw(pMetaDC);
			continue;
		}
	}
}

CTCProcedureDocument *CTCProceduresMonitorItemFlowchartThreadView::GetDocument() CONST
{
	return m_pFlowchart;
}

CTCProceduresMonitorItemFlowchartTabCtrl *CTCProceduresMonitorItemFlowchartThreadView::GetParent() CONST
{
	return((CTCProceduresMonitorItemFlowchartTabCtrl *)m_pParentWnd);
}

CTCProceduresMonitorWnd *CTCProceduresMonitorItemFlowchartThreadView::GetParentDisplay() CONST
{
	CTCProceduresMonitorItemFlowchartTabCtrl  *pTabCtrl;

	return(((pTabCtrl = GetParent())) ? pTabCtrl->GetParentDisplay() : (CTCProceduresMonitorWnd *)NULL);
}

VOID CTCProceduresMonitorItemFlowchartThreadView::DrawContent()
{
	CDC  *pDC;

	if ((pDC = GetDC()))
	{
		pDC->SetViewportOrg(-m_ptScroll);
		DrawContent(pDC);
		ReleaseDC(pDC);
	}
}
VOID CTCProceduresMonitorItemFlowchartThreadView::DrawContent(CDC *pDC)
{
	CDC  cDC[2];
	INT  nOldMode;
	CRect  rView;
	CPoint  pt[2];
	CBitmap  cBitmap[2];
	CBitmap  *pOldBitmap[2];
	POSITION  lPosition;
	BLENDFUNCTION  sBlend;
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pStep[2];

	GetClientRect(rView);
	if (cDC[0].CreateCompatibleDC(pDC))
	{
		if (cBitmap[0].CreateCompatibleBitmap(pDC, rView.Width(), rView.Height()))
		{
			if ((pOldBitmap[0] = cDC[0].SelectObject(&cBitmap[0])) != (CBitmap *)NULL)
			{
				for (cDC[0].SetViewportOrg(-m_ptScroll), cDC[0].FillSolidRect(CalcStatePaneMarginSize(), 0, max(GetTotalSize().cx, rView.Width()) - CalcStatePaneMarginSize() + 1, max(GetTotalSize().cy, rView.Height()) + 1, m_nBackgroundColor); (pStep[0] = GetActiveStep()); )
				{
					if (pStep[0]->IsActivated())
					{
						if (pStep[0]->IsExpanded())
						{
							if (cDC[1].CreateCompatibleDC(pDC))
							{
								if (cBitmap[1].CreateCompatibleBitmap(pDC, pStep[0]->GetPosition().Width(), pStep[0]->GetPosition().Height()))
								{
									if ((pOldBitmap[1] = cDC[1].SelectObject(&cBitmap[1])))
									{
										nOldMode = cDC[1].SetROP2(R2_MERGEPEN);
										cDC[1].FillSolidRect(0, 0, pStep[0]->GetPosition().Width(), pStep[0]->GetPosition().Height(), VGA_COLOR_WHITE);
										cDC[1].FillSolidRect(0, 0, pStep[0]->GetPosition().Width(), pStep[0]->GetPosition().Height(), TCPROCEDUREDOCUMENTITEM_BACKGROUNDCOLOR);
										for (sBlend.BlendFlags = 0, sBlend.BlendOp = AC_SRC_OVER, sBlend.AlphaFormat = 0, sBlend.SourceConstantAlpha = TCPROCEDUREDOCUMENTITEM_BACKGROUNDALPHA; TRUE; )
										{
											cDC[0].FillSolidRect(pStep[0]->GetPosition().left, pStep[0]->GetPosition().top + pStep[0]->GetImageSize().cy / 2, pStep[0]->GetPosition().Width(), pStep[0]->GetPosition().Height() - pStep[0]->GetImageSize().cy / 2, VGA_COLOR_WHITE);
											cDC[0].FillSolidRect(pStep[0]->GetPosition().left + pStep[0]->GetImageSize().cx / 2, pStep[0]->GetPosition().top, pStep[0]->GetPosition().Width() - pStep[0]->GetImageSize().cx / 2, pStep[0]->GetImageSize().cy / 2, VGA_COLOR_WHITE);
											cDC[0].AlphaBlend(pStep[0]->GetPosition().left, pStep[0]->GetPosition().top + pStep[0]->GetImageSize().cy / 2, pStep[0]->GetPosition().Width(), pStep[0]->GetPosition().Height() - pStep[0]->GetImageSize().cy / 2, &cDC[1], 0, 0, pStep[0]->GetPosition().Width(), pStep[0]->GetPosition().Height() - pStep[0]->GetImageSize().cy / 2, sBlend);
											cDC[0].AlphaBlend(pStep[0]->GetPosition().left + pStep[0]->GetImageSize().cx / 2, pStep[0]->GetPosition().top, pStep[0]->GetPosition().Width() - pStep[0]->GetImageSize().cx / 2, pStep[0]->GetImageSize().cy / 2, &cDC[1], 0, 0, pStep[0]->GetPosition().Width() - pStep[0]->GetImageSize().cx / 2, pStep[0]->GetImageSize().cy / 2, sBlend);
											break;
										}
										cDC[1].SelectObject(pOldBitmap[1]);
										cDC[1].SetROP2(nOldMode);
									}
									cBitmap[1].DeleteObject();
								}
								cDC[1].DeleteDC();
							}
						}
					}
					break;
				}
				for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL, pStep[0] = pStep[1] = (CTCProcedureDocumentItem *)NULL; lPosition; pStep[1] = pStep[0])
				{
					if ((pStep[0] = pDocument->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
					{
						if (pStep[1] && pStep[1]->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_GOTO)
						{
							pt[0] = pStep[1]->CalcConnectionPoint(FALSE, pStep[1]->IsExpanded());
							pt[1] = pStep[0]->CalcConnectionPoint(TRUE);
							CTCProcedureDocumentItem::DrawConnectionLine(&cDC[0], pt[0], pt[1]);
						}
					}
				}
				for (lPosition = pDocument->GetStartPosition(); lPosition; )
				{
					if ((pStep[0] = pDocument->GetNextStep(lPosition)))
					{
						pStep[0]->Draw(&cDC[0]);
						continue;
					}
				}
				pDC->BitBlt(m_ptScroll.x, m_ptScroll.y, rView.Width(), rView.Height(), &cDC[0], m_ptScroll.x, m_ptScroll.y, SRCCOPY);
				m_wndStatePane.UpdateExecutionpoint();
				cDC[0].SelectObject(pOldBitmap[0]);
			}
			cBitmap[0].DeleteObject();
		}
		cDC[0].DeleteDC();
	}
}

VOID CTCProceduresMonitorItemFlowchartThreadView::AdjustSteps(CONST CTCProcedureDocumentItem *pStep, INT nOffset)
{
	CRect  rStep[2];
	POSITION  lPosition;
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pItem;

	for (lPosition = ((pDocument = (CTCProcedureDocument *)pStep->GetDocument())) ? pDocument->FindStep(pDocument->GetNextStep(pStep), FALSE) : (POSITION)NULL; lPosition; )
	{
		if ((pItem = pDocument->GetNextStep(lPosition)) && pItem->GetSubThreadID() == pStep->GetSubThreadID())
		{
			pItem->SetPosition(pItem->GetPosition() + CPoint(0, nOffset));
			AdjustSteps(pItem, pStep, nOffset);
		}
	}
	if ((pItem = FindContainerStep(pStep)))
	{
		rStep[0] = pItem->GetPosition();
		pItem->RecalcLayout();
		rStep[1] = pItem->GetPosition();
		AdjustSteps(pItem, rStep[1].Height() - rStep[0].Height());
	}
}
VOID CTCProceduresMonitorItemFlowchartThreadView::AdjustSteps(CONST CTCProcedureDocumentItem *pSteps, CONST CTCProcedureDocumentItem *pStep, INT nOffset)
{
	POSITION  lPosition;
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pItem;

	for (lPosition = ((pDocument = pSteps->GetSubSteps())) ? pDocument->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pItem = pDocument->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			pItem->SetPosition(pItem->GetPosition() + CPoint(0, nOffset));
			AdjustSteps(pItem, pStep, nOffset);
		}
	}
}

POSITION CTCProceduresMonitorItemFlowchartThreadView::FindStep(CONST CTCProcedureDocumentItem *pStep, BOOL bAll) CONST
{
	BOOL  bContinue;
	POSITION  lPosition[2];
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pItem;

	for (lPosition[0] = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL; lPosition[0]; )
	{
		if ((pItem = pDocument->GetNextStep(lPosition[0])) != (CTCProcedureDocumentItem *)NULL)
		{
			if ((bContinue = (pItem != pStep)) && pItem->GetSubSteps()->GetStepCount(bAll) > 0)
			{
				if ((lPosition[1] = FindStep(pItem, pStep, bAll))) return lPosition[1];
				continue;
			}
			if (!bContinue) return pDocument->FindStep(pItem, bAll);
		}
	}
	return((POSITION)NULL);
}
POSITION CTCProceduresMonitorItemFlowchartThreadView::FindStep(CONST CTCProcedureDocumentItem *pSteps, CONST CTCProcedureDocumentItem *pStep, BOOL bAll) CONST
{
	BOOL  bContinue;
	POSITION  lPosition[2];
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pItem;

	for (lPosition[0] = ((pDocument = pSteps->GetSubSteps())) ? pDocument->GetStartPosition() : (POSITION)NULL; lPosition[0]; )
	{
		if ((pItem = pDocument->GetNextStep(lPosition[0])) != (CTCProcedureDocumentItem *)NULL)
		{
			if ((bContinue = (pItem != pStep)) && pItem->GetSubSteps()->GetStepCount(bAll) > 0)
			{
				if ((lPosition[1] = FindStep(pItem, pStep, bAll))) return lPosition[1];
				continue;
			}
			if (!bContinue) return pDocument->FindStep(pItem, bAll);
		}
	}
	return((POSITION)NULL);
}
CTCProcedureDocumentItem *CTCProceduresMonitorItemFlowchartThreadView::FindStep(CONST POINT &pt, BOOL bImage, BOOL bTreeSymbol, BOOL bAll) CONST
{
	POSITION  lPosition;
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pStep[2];

	for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pStep[0] = (CTCProcedureDocumentItem *)pDocument->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			if ((!bImage || !pStep[0]->IsPtOnImage(pt)) && (!bTreeSymbol || !pStep[0]->IsPtOnTreeSymbol(pt)))
			{
				if ((pStep[1] = (pStep[0]->GetSubSteps()->GetStepCount(bAll) > 0 && pStep[0]->IsExpanded()) ? FindStep(pStep[0], pt, bImage, bTreeSymbol, bAll) : (CTCProcedureDocumentItem *)NULL)) return pStep[1];
				continue;
			}
			return pStep[0];
		}
	}
	return((CTCProcedureDocumentItem *)NULL);
}
CTCProcedureDocumentItem *CTCProceduresMonitorItemFlowchartThreadView::FindStep(CONST CTCProcedureDocumentItem *pSteps, CONST POINT &pt, BOOL bImage, BOOL bTreeSymbol, BOOL bAll) CONST
{
	POSITION  lPosition;
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pStep[2];

	for (lPosition = ((pDocument = pSteps->GetSubSteps())) ? pDocument->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pStep[0] = (CTCProcedureDocumentItem *)pDocument->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			if ((!bImage || !pStep[0]->IsPtOnImage(pt)) && (!bTreeSymbol || !pStep[0]->IsPtOnTreeSymbol(pt)))
			{
				if ((pStep[1] = (pStep[0]->GetSubSteps()->GetStepCount(bAll) > 0 && pStep[0]->IsExpanded()) ? FindStep(pStep[0], pt, bImage, bTreeSymbol, bAll) : (CTCProcedureDocumentItem *)NULL)) return pStep[1];
				continue;
			}
			return pStep[0];
		}
	}
	return((CTCProcedureDocumentItem *)NULL);
}
CTCProcedureDocumentItem *CTCProceduresMonitorItemFlowchartThreadView::FindStep(POSITION &lPosition) CONST
{
	POSITION  lDocumentPosition;
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pStep[2];

	for (lDocumentPosition = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL; lPosition != lDocumentPosition && lDocumentPosition; )
	{
		if ((pStep[0] = (CTCProcedureDocumentItem *)pDocument->GetNextStep(lDocumentPosition)))
		{
			if ((pStep[1] = FindStep(pStep[0], lPosition))) return pStep[1];
			continue;
		}
	}
	return((lDocumentPosition == lPosition  &&  lDocumentPosition) ? pDocument->GetNextStep(lDocumentPosition) : (CTCProcedureDocumentItem *)NULL);
}
CTCProcedureDocumentItem *CTCProceduresMonitorItemFlowchartThreadView::FindStep(CONST CTCProcedureDocumentItem *pSteps, POSITION &lPosition) CONST
{
	POSITION  lDocumentPosition;
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pStep[2];

	for (lDocumentPosition = ((pDocument = pSteps->GetSubSteps())) ? pDocument->GetStartPosition() : (POSITION)NULL; lPosition != lDocumentPosition && lDocumentPosition; )
	{
		if ((pStep[0] = (CTCProcedureDocumentItem *)pDocument->GetNextStep(lDocumentPosition)))
		{
			if ((pStep[1] = FindStep(pStep[0], lPosition))) return pStep[1];
			continue;
		}
	}
	return((lDocumentPosition == lPosition  &&  lDocumentPosition) ? pDocument->GetNextStep(lDocumentPosition) : (CTCProcedureDocumentItem *)NULL);
}

CTCProcedureDocumentItem *CTCProceduresMonitorItemFlowchartThreadView::FindContainerStep(CONST CTCProcedureDocumentItem *pStep) CONST
{
	INT  nStep;
	INT  nSteps;
	CPtrArray  pSteps;
	CTCProcedureDocumentItem  *pItem;

	for (nStep = 0, nSteps = GetDocument()->EnumSteps(pSteps); nStep < nSteps; nStep++)
	{
		if ((pItem = (CTCProcedureDocumentItem *)pSteps.GetAt(nSteps - nStep - 1)))
		{
			if (pItem->GetSubSteps()->FindStep(pStep, FALSE)) break;
			continue;
		}
	}
	return((nStep < nSteps) ? (CTCProcedureDocumentItem *)pSteps.GetAt(nSteps - nStep - 1) : (CTCProcedureDocumentItem *)NULL);
}

CRect CTCProceduresMonitorItemFlowchartThreadView::CalcStatePanePosition() CONST
{
	CRect  rView;

	GetClientRect(rView);
	return CalcStatePanePosition(rView.Width(), rView.Height());
}
CRect CTCProceduresMonitorItemFlowchartThreadView::CalcStatePanePosition(INT cx, INT cy) CONST
{
	return CRect(0, -m_ptScroll.y, CalcStatePaneMarginSize(), max(CalcScrollSizes().cy - m_ptScroll.y, cy) + 1);
}

INT CTCProceduresMonitorItemFlowchartThreadView::CalcStatePaneMarginSize() CONST
{
	return GetSystemMetrics(SM_CXVSCROLL);
}

CSize CTCProceduresMonitorItemFlowchartThreadView::CalcScrollSizes() CONST
{
	CRect  rView;
	CRect  rPosition;
	POSITION  lPosition;
	CFontTools  cFontTools;
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pStep;

	if ((pDocument = GetDocument()))
	{
		for (lPosition = pDocument->GetStartPosition(), rView.SetRectEmpty(); lPosition; )
		{
			if ((pStep = (CTCProcedureDocumentItem *)pDocument->GetNextStep(lPosition)))
			{
				rPosition.SetRect(pStep->GetPosition().TopLeft(), pStep->GetPosition().BottomRight());
				rView.SetRect(min(rPosition.left, rView.left), min(rPosition.top, rView.top), max(rPosition.right + 1, rView.right), max(rPosition.bottom + 1, rView.bottom));
			}
		}
		return CSize(TCPROCEDUREDOCUMENT_DEFAULT_MARGIN + rView.right, TCPROCEDUREDOCUMENT_DEFAULT_MARGIN + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT + cFontTools.QueryHeight(&m_lfStepsLabelFont) + rView.bottom);
	}
	return CSize(0, 0);
}

BOOL CTCProceduresMonitorItemFlowchartThreadView::LoadToolTipCursor()
{
	return(((m_hToolTipCursor = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_TOOLTIPCURSOR), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR))) ? TRUE : FALSE);
}

HCURSOR CTCProceduresMonitorItemFlowchartThreadView::GetToolTipCursor() CONST
{
	return((!m_hToolTipCursor) ? (HCURSOR)(DWORD_PTR)GetClassLongPtr(GetSafeHwnd(), GCLP_HCURSOR) : m_hToolTipCursor);
}

BOOL CTCProceduresMonitorItemFlowchartThreadView::FreeToolTipCursor()
{
	if (m_hToolTipCursor)
	{
		DestroyCursor(m_hToolTipCursor);
		m_hToolTipCursor = (HCURSOR)NULL;
		return TRUE;
	}
	return FALSE;
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorItemFlowchartThreadView, CScrollView)
	//{{AFX_MSG_MAP(CTCProceduresMonitorItemFlowchartThreadView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemFlowchartThreadView drawing

void CTCProceduresMonitorItemFlowchartThreadView::OnDraw(CDC *pDC)
{
	for (m_ptScroll = GetScrollPosition(); m_ptScroll.x >= 0 && m_ptScroll.y >= 0; )
	{
		DrawContent(pDC);
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemFlowchartThreadView message handlers

int CTCProceduresMonitorItemFlowchartThreadView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) != -1 && LoadToolTipCursor())
	{
		if (m_wndStatePane.Create(this, CRect(0, 0, 0, 0)))
		{
			SetScrollSizes(MM_TEXT, CalcScrollSizes());
			return 0;
		}
	}
	return -1;
}

void CTCProceduresMonitorItemFlowchartThreadView::OnSize(UINT nType, int cx, int cy)
{
	m_wndStatePane.MoveWindow(CalcStatePanePosition(cx, cy));
	CScrollView::OnSize(nType, cx, cy);
}

BOOL CTCProceduresMonitorItemFlowchartThreadView::OnEraseBkgnd(CDC *pDC)
{
	return TRUE;
}

void CTCProceduresMonitorItemFlowchartThreadView::OnSetFocus(CWnd *pOldWnd)
{
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pStep[2];

	if (pOldWnd == GetParent())
	{
		if ((pDocument = (!GetActiveStep(TRUE) && !m_bRunning) ? (CTCProcedureDocument *)(pStep[0] = GetDocument()->GetFirstStep())->GetDocument() : (CTCProcedureDocument *)NULL))
		{
			while ((pStep[1] = pDocument->GetNextStep(pStep[0])))
			{
				if (pStep[1]->CanActivate() || pStep[1]->CanSelect())
				{
					if (pStep[1]->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_START  &&  pStep[1]->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_END)
					{
						SetActiveStep(pStep[1]);
						break;
					}
				}
				pStep[0] = pStep[1];
			}
		}
		return;
	}
	CScrollView::OnSetFocus(pOldWnd);
}

BOOL CTCProceduresMonitorItemFlowchartThreadView::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	POINT  ptCursor;
	CTCProcedureDocumentItem  *pStep;

	for (GetCursorPos(&ptCursor), ScreenToClient(&ptCursor), ptCursor.x += GetScrollPosition().x, ptCursor.y += GetScrollPosition().y; (pStep = FindStep(ptCursor, TRUE, FALSE)) && !pStep->GetComments().IsEmpty(); )
	{
		SetCursor(GetToolTipCursor());
		return TRUE;
	}
	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}

void CTCProceduresMonitorItemFlowchartThreadView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect  rStep[2];
	CPoint  ptStep;
	CTCProcedureDocumentItem  *pStep;

	for (ptStep = point + GetScrollPosition(); (pStep = FindStep(ptStep)); )
	{
		if (pStep->IsPtOnTreeSymbol(ptStep))
		{
			rStep[0] = pStep->GetPosition();
			pStep->Expand(!pStep->IsExpanded());
			rStep[1] = pStep->GetPosition();
			AdjustSteps(pStep, rStep[1].Height() - rStep[0].Height());
		}
		if (pStep->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_START  &&  pStep->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_END  &&  !m_bRunning)
		{
			SetActiveStep(pStep);
			break;
		}
		UpdateAllSteps();
		break;
	}
	for (; !pStep; )
	{
		SetActiveStep();
		break;
	}
	GetParentDisplay()->GetListView()->UpdateContent();
	CScrollView::OnLButtonDown(nFlags, point);
}

void CTCProceduresMonitorItemFlowchartThreadView::OnRButtonDown(UINT nFlags, CPoint point)
{
	INT  nStep;
	INT  nSteps;
	CString  szText;
	CString  szTitle;
	CPtrArray  pSteps[2];
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pStep[2];

	if ((pDocument = ((pStep[0] = FindStep(point + GetScrollPosition(), TRUE, FALSE)) && IsToolTipModeEnabled()) ? new CTCProcedureDocument : (CTCProcedureDocument *)NULL))
	{
		for (nStep = 0, nSteps = ((szTitle = pStep[0]->GetName()).IsEmpty() && pDocument->Copy(GetDocument()) && GetDocument()->EnumSteps(pSteps[0]) == pDocument->EnumSteps(pSteps[1], FALSE, TRUE)) ? (INT)pSteps[0].GetSize() : 0; nStep < nSteps; nStep++)
		{
			if ((pStep[1] = (pStep[0] == (CTCProcedureDocumentItem *)pSteps[0].GetAt(nStep)) ? (CTCProcedureDocumentItem *)pSteps[1].GetAt(nStep) : (CTCProcedureDocumentItem *)NULL))
			{
				szTitle = pStep[1]->GetName();
				break;
			}
		}
		for (szText = pStep[0]->GetComments(); !szTitle.IsEmpty(); )
		{
			m_wndToolTip.Create(this, point, szTitle, szText);
			break;
		}
		delete pDocument;
	}
	CScrollView::OnRButtonDown(nFlags, point);
}

void CTCProceduresMonitorItemFlowchartThreadView::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_wndToolTip.Destroy();
	CScrollView::OnRButtonUp(nFlags, point);
}

void CTCProceduresMonitorItemFlowchartThreadView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CRect  rStep[2];
	CPoint  ptDrop;
	CPoint  ptStep;
	POSITION  lPosition;
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pStep[4];

	for (; (nChar == VK_UP || nChar == VK_DOWN) && !m_bRunning; )
	{
		if ((pDocument = ((pStep[0] = GetActiveStep(TRUE))) ? (CTCProcedureDocument *)pStep[0]->GetDocument() : ((nChar == VK_DOWN) ? (CTCProcedureDocument *)(pStep[0] = GetDocument()->GetFirstStep())->GetDocument() : (CTCProcedureDocument *)(pStep[0] = GetDocument()->GetLastStep())->GetDocument())))
		{
			for (; (pStep[1] = (nChar == VK_DOWN) ? pDocument->GetNextStep(pStep[0]) : pDocument->GetPreviousStep(pStep[0])) != (CTCProcedureDocumentItem *)NULL; pStep[0] = pStep[1])
			{
				if ((pStep[1]->CanActivate() || pStep[1]->CanSelect()) && pStep[1]->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_START  &&  pStep[1]->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_END)
				{
					SetActiveStep(pStep[1]);
					break;
				}
			}
		}
		break;
	}
	for (; nChar == VK_LEFT && !m_bRunning; )
	{
		if ((pStep[0] = GetActiveStep(TRUE)) != (CTCProcedureDocumentItem *)NULL)
		{
			if ((pStep[1] = FindContainerStep(pStep[0])))
			{
				SetActiveStep(pStep[1]);
				break;
			}
		}
		break;
	}
	for (; nChar == VK_RIGHT && !m_bRunning; )
	{
		if ((pStep[0] = GetActiveStep(TRUE)))
		{
			if (!pStep[0]->IsExpanded())
			{
				for (rStep[0] = pStep[0]->GetPosition(), pStep[0]->Expand(), rStep[1] = pStep[0]->GetPosition(); rStep[0].Height() != rStep[1].Height(); )
				{
					AdjustSteps(pStep[0], rStep[1].Height() - rStep[0].Height());
					break;
				}
			}
			for (lPosition = ((pDocument = pStep[0]->GetSubSteps())) ? pDocument->GetStartPosition() : (POSITION)NULL; lPosition; )
			{
				if ((pStep[1] = pDocument->GetNextStep(lPosition)) && (pStep[1]->CanActivate() || pStep[1]->CanSelect()) && pStep[1]->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_START  &&  pStep[1]->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_END)
				{
					SetActiveStep(pStep[1]);
					break;
				}
			}
		}
		break;
	}
	for (; nChar == VK_RETURN; )
	{
		if ((pStep[0] = GetActiveStep()))
		{
			for (rStep[0] = pStep[0]->GetPosition(), pStep[0]->Expand(!pStep[0]->IsExpanded()), rStep[1] = pStep[0]->GetPosition(); rStep[0].Height() != rStep[1].Height(); )
			{
				AdjustSteps(pStep[0], rStep[1].Height() - rStep[0].Height());
				SetActiveStep(pStep[0]);
				break;
			}
		}
		break;
	}
	if (nChar == VK_ESCAPE)
	{
		GetParent()->SetFocus();
		return;
	}
	GetParentDisplay()->GetListView()->UpdateContent();
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTCProceduresMonitorItemFlowchartThreadView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
	CRect  rView;
	SCROLLINFO  sScrollInfo;

	for (GetClientRect(rView), rView.DeflateRect(CalcStatePanePosition().Width(), 0, 0, 0), GetScrollInfo(SB_HORZ, &sScrollInfo); nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK; )
	{
		ScrollWindow((nSBCode == SB_THUMBTRACK) ? (GetScrollPos(SB_HORZ) - sScrollInfo.nTrackPos) : (GetScrollPos(SB_HORZ) - sScrollInfo.nPos), 0, rView, rView);
		SetScrollPos(SB_HORZ, (nSBCode == SB_THUMBTRACK) ? sScrollInfo.nTrackPos : sScrollInfo.nPos);
		return;
	}
	if (nSBCode == SB_LEFT || nSBCode == SB_RIGHT)
	{
		ScrollWindow((nSBCode != SB_LEFT) ? (GetScrollPos(SB_HORZ) - (sScrollInfo.nMax - sScrollInfo.nPage + 1)) : GetScrollPos(SB_HORZ), 0, rView, rView);
		SetScrollPos(SB_HORZ, (nSBCode != SB_LEFT) ? (sScrollInfo.nMax - sScrollInfo.nPage + 1) : 0);
		return;
	}
	if (nSBCode == SB_LINELEFT || nSBCode == SB_LINERIGHT)
	{
		ScrollWindow((nSBCode != SB_LINELEFT) ? -min((INT)sScrollInfo.nPage / 16, (INT)(sScrollInfo.nMax - sScrollInfo.nPage + 1) - GetScrollPos(SB_HORZ)) : min((INT)sScrollInfo.nPage / 16, GetScrollPos(SB_HORZ)), 0, rView, rView);
		SetScrollPos(SB_HORZ, (nSBCode == SB_LINELEFT) ? max(GetScrollPos(SB_HORZ) - sScrollInfo.nPage / 16, 0) : min(GetScrollPos(SB_HORZ) + sScrollInfo.nPage / 16, sScrollInfo.nMax - sScrollInfo.nPage + 1));
		return;
	}
	if (nSBCode == SB_PAGELEFT || nSBCode == SB_PAGERIGHT)
	{
		ScrollWindow((nSBCode != SB_PAGELEFT) ? -min((INT)sScrollInfo.nPage, (INT)(sScrollInfo.nMax - sScrollInfo.nPage + 1) - GetScrollPos(SB_HORZ)) : min((INT)sScrollInfo.nPage, GetScrollPos(SB_HORZ)), 0, rView, rView);
		SetScrollPos(SB_HORZ, (nSBCode == SB_PAGELEFT) ? max(GetScrollPos(SB_HORZ) - sScrollInfo.nPage, 0) : min(GetScrollPos(SB_HORZ) + sScrollInfo.nPage, sScrollInfo.nMax - sScrollInfo.nPage + 1));
		return;
	}
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CTCProceduresMonitorItemFlowchartThreadView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
	SCROLLINFO  sScrollInfo[2];

	for (GetScrollInfo(SB_HORZ, &sScrollInfo[0]), GetScrollInfo(SB_VERT, &sScrollInfo[1]); nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK; )
	{
		ScrollToPosition(CPoint(sScrollInfo[0].nPos, (nSBCode == SB_THUMBTRACK) ? sScrollInfo[1].nTrackPos : sScrollInfo[1].nPos));
		return;
	}
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CTCProceduresMonitorItemFlowchartThreadView::OnDestroy()
{
	for (FreeToolTipCursor(), m_wndStatePane.DestroyWindow(); m_pFlowchart != (CTCProcedureDocument *)NULL; )
	{
		delete m_pFlowchart;
		break;
	}
	m_pFlowchart = (CTCProcedureDocument *)NULL;
	CScrollView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemFlowchartTabCtrl

IMPLEMENT_DYNCREATE(CTCProceduresMonitorItemFlowchartTabCtrl, CTabCtrl)

CTCProceduresMonitorItemFlowchartTabCtrl::CTCProceduresMonitorItemFlowchartTabCtrl() : CTabCtrl()
{
	m_nIndex = -1;
	m_sizeTabMargins.cx = 0;
	m_sizeTabMargins.cy = 0;
	m_pParentWnd = (CWnd *)NULL;
}

BOOL CTCProceduresMonitorItemFlowchartTabCtrl::Create(CWnd *pParentWnd, CONST RECT &rect)
{
	CStringArray  szTabs;

	szTabs.Add(STRING(IDS_TCPROCEDURESMONITOR_FLOWCHART_DEFAULTTAB));
	return Create(pParentWnd, rect, szTabs);
}
BOOL CTCProceduresMonitorItemFlowchartTabCtrl::Create(CWnd *pParentWnd, CONST RECT &rect, CONST CStringArray &szTabs)
{
	INT  nTab;
	INT  nTabs;
	CRect  rTabs;
	CRect  rView;
	CTCProceduresMonitorItemFlowchartThreadView  *pView;

	if (CTabCtrl::Create(TCS_TABS | TCS_SINGLELINE | WS_CHILD | WS_VISIBLE, rect, (m_pParentWnd = pParentWnd), 0))
	{
		for (nTab = 0, nTabs = (INT)szTabs.GetSize(), GetClientRect(rView), AdjustRect(FALSE, rView); nTab < nTabs; nTab++)
		{
			if ((pView = new CTCProceduresMonitorItemFlowchartThreadView))
			{
				if (InsertItem(nTab, szTabs.GetAt(nTab)) >= 0)
				{
					if (pView->Create(this, rView, nTab, nTab == 0))
					{
						m_szViews.Add(szTabs.GetAt(nTab));
						m_pViews.Add(pView);
						continue;
					}
					DeleteItem(nTab);
				}
				delete pView;
			}
			break;
		}
		if (nTab == nTabs)
		{
			m_sizeTabMargins = (GetItemRect(0, rTabs)) ? CSize(rTabs.left, rTabs.top) : m_sizeTabMargins;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemFlowchartTabCtrl::SetFlowcharts(CONST CTCProceduresMonitorItem *pItem)
{
	INT  nTab;
	INT  nTabs;
	BOOL  bTab;
	CRect  rView;
	CTCProcedureDocument  *pFlowchart;
	CTCProceduresMonitorItemFlowchartThreadView  *pView;
	CDatabaseTCProcedureThreadBreakpoints  pBreakpoints;
	CDatabaseTCProcedureThread  *pThread;

	for (nTab = 0, nTabs = (INT)pItem->GetSize(); nTab < nTabs; nTab++)
	{
		if ((pThread = pItem->GetAt(nTab)) && pThread->GetBreakpoints(pBreakpoints) >= 0)
		{
			if ((pView = (nTab < GetTabCount()) ? (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nTab) : (CTCProceduresMonitorItemFlowchartThreadView *)NULL))
			{
				if (m_szViews.GetAt(nTab) == pThread->GetName())
				{
					if ((pFlowchart = new CTCProcedureDocument))
					{
						if (pFlowchart->Unmap(pThread) && pView->SetSteps(pFlowchart))
						{
							pView->SetBreakpoints(pBreakpoints);
							delete pFlowchart;
							continue;
						}
						delete pFlowchart;
					}
					continue;
				}
			}
			for (GetClientRect(rView), AdjustRect(FALSE, rView), bTab = (nTab == GetCurTab()) ? TRUE : FALSE; (pView = new CTCProceduresMonitorItemFlowchartThreadView); )
			{
				if (InsertItem(nTab, pThread->GetName()) >= 0)
				{
					if ((pFlowchart = new CTCProcedureDocument))
					{
						if (pView->Create(this, rView, nTab, bTab))
						{
							if (pFlowchart->Unmap(pThread))
							{
								if (pView->SetSteps(pFlowchart))
								{
									pView->SetBreakpoints(pBreakpoints);
									m_szViews.InsertAt(nTab, pThread->GetName());
									m_pViews.InsertAt(nTab, pView);
									delete pFlowchart;
									break;
								}
							}
						}
						delete pFlowchart;
					}
					DeleteItem(nTab);
				}
				nTabs = nTab;
				delete pView;
				break;
			}
			if (nTab == nTabs) break;
		}
	}
	while ((nTabs = GetTabCount()) > nTab  &&  nTabs > 1)
	{
		if ((pView = (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nTabs - 1)))
		{
			m_szViews.RemoveAt(nTabs - 1);
			m_pViews.RemoveAt(nTabs - 1);
			pView->DestroyWindow();
		}
		DeleteItem(nTabs - 1);
	}
	if ((pView = ((nTabs = GetTabCount()) > 0 && !pItem->GetSize()) ? (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(0) : (CTCProceduresMonitorItemFlowchartThreadView *)NULL))
	{
		if ((pFlowchart = new CTCProcedureDocument))
		{
			if (pView->SetSteps(pFlowchart))
			{
				pView->SetBreakpoints(pBreakpoints);
				pView->ShowWindow(SW_SHOW);
				delete pFlowchart;
				SetCurTab(0);
				RedrawWindow();
				return TRUE;
			}
			delete pFlowchart;
		}
	}
	for (GetParentDisplay()->UpdateProcedure(-1); (pView = (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(0)); )
	{
		pView->ShowWindow(SW_SHOW);
		SetCurTab(0);
		break;
	}
	RedrawWindow();
	return((pItem->GetSize() == nTabs) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorItemFlowchartTabCtrl::GetFlowcharts(CTCProceduresMonitorItem *pItem) CONST
{
	INT  nTab;
	INT  nTabs;
	INT  nThread[2];
	INT  nThreads[2];
	CPtrArray  pThreads;
	CTCProcedureDocument  *pFlowchart;
	CTCProceduresMonitorItemFlowchartThreadView  *pView;
	CDatabaseTCProcedureThreadBreakpoints  pBreakpoints;
	CDatabaseTCProcedureThread  *pThread;

	for (nTab = 0, nTabs = GetTabCount(); nTab < nTabs; nTab++)
	{
		if ((pFlowchart = ((pView = (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nTab))) ? new CTCProcedureDocument : (CTCProcedureDocument *)NULL))
		{
			if ((pThread = pItem->GetAt(pItem->Find(m_szViews.GetAt(nTab)))) && pThread->GetBreakpoints(pBreakpoints) >= 0)
			{
				if (pView->GetSteps(pFlowchart) && pFlowchart->Map(pThread) && pThread->SetBreakpoints(pBreakpoints))
				{
					delete pFlowchart;
					continue;
				}
				break;
			}
			if ((pThread = new CDatabaseTCProcedureThread))
			{
				for (pThread->SetName(m_szViews.GetAt(nTab)); pView->GetSteps(pFlowchart) && pFlowchart->Map(pThread); )
				{
					pItem->Add(pThread);
					break;
				}
				if (pItem->Find(pThread->GetName()) >= 0)
				{
					delete pFlowchart;
					continue;
				}
				delete pThread;
			}
			delete pFlowchart;
		}
		break;
	}
	for (nThread[0] = 0, nThreads[0] = (INT)pItem->GetSize(); nThread[0] < nThreads[0]; nThread[0]++)
	{
		if ((pThread = pItem->GetAt(nThread[0])) != (CDatabaseTCProcedureThread *)NULL)
		{
			for (nThread[1] = 0, nThreads[1] = (INT)m_szViews.GetSize(); nThread[1] < nThreads[1]; nThread[1]++)
			{
				if (pThread->GetName() == m_szViews.GetAt(nThread[1])) break;
				continue;
			}
			if (nThread[1] == nThreads[1])
			{
				pItem->RemoveAt(nThread[0]);
				delete pThread;
				nThreads[0]--;
				nThread[0]--;
				continue;
			}
			pThreads.SetAtGrow(nThread[1], pThread);
		}
	}
	for (nThread[0] = 0, nThreads[0] = (INT)pThreads.GetSize(); nThread[0] < nThreads[0]; nThread[0]++)
	{
		pItem->SetAt(nThread[0], pThreads.GetAt(nThread[0]));
		continue;
	}
	return((nTab == nTabs) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorItemFlowchartTabCtrl::SetBreakpoints(CONST CStringArray &szBreakpoints, CONST CDatabaseTCProcedureThreadBreakpoints &pBreakpoints)
{
	INT  nTab;
	INT  nTabs;
	INT  nBreakpoint;
	INT  nBreakpoints;
	CStringArray  szThreadBreakpoints;
	CDatabaseTCProcedureThreadBreakpoints  pThreadBreakpoints[2];
	CTCProceduresMonitorItemFlowchartThreadView  *pView;

	for (nTab = 0, nTabs = GetTabCount(), szThreadBreakpoints.Copy(szBreakpoints), pThreadBreakpoints[0].Copy(&pBreakpoints); nTab < nTabs; nTab++)
	{
		if ((pView = (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nTab)) != (CTCProceduresMonitorItemFlowchartThreadView *)NULL)
		{
			for (nBreakpoint = 0, nBreakpoints = (INT)szThreadBreakpoints.GetSize(), pThreadBreakpoints[1].RemoveAll(); nBreakpoint < nBreakpoints; nBreakpoint++)
			{
				if (!szThreadBreakpoints.GetAt(nBreakpoint).Compare(m_szViews.GetAt(nTab)))
				{
					pThreadBreakpoints[1].Add(pThreadBreakpoints[0].GetAt(nBreakpoint));
					pThreadBreakpoints[0].RemoveAt(nBreakpoint);
					szThreadBreakpoints.RemoveAt(nBreakpoint);
					nBreakpoints--;
					nBreakpoint--;
				}
			}
			pView->SetBreakpoints(pThreadBreakpoints[1]);
		}
	}
}

INT CTCProceduresMonitorItemFlowchartTabCtrl::GetBreakpoints(CStringArray &szBreakpoints, CDatabaseTCProcedureThreadBreakpoints &pBreakpoints) CONST
{
	INT  nTab;
	INT  nTabs;
	INT  nBreakpoint;
	INT  nBreakpoints;
	CDatabaseTCProcedureThreadBreakpoints  pThreadBreakpoints;
	CTCProceduresMonitorItemFlowchartThreadView  *pView;

	for (nTab = 0, nTabs = GetTabCount(), szBreakpoints.RemoveAll(), pBreakpoints.RemoveAll(); nTab < nTabs; nTab++)
	{
		if ((pView = (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nTab)) != (CTCProceduresMonitorItemFlowchartThreadView *)NULL)
		{
			for (nBreakpoint = 0, nBreakpoints = pView->GetBreakpoints(pThreadBreakpoints); nBreakpoint < nBreakpoints; nBreakpoint++)
			{
				pBreakpoints.Add(pThreadBreakpoints.GetAt(nBreakpoint));
				pThreadBreakpoints.RemoveAt(nBreakpoint);
				szBreakpoints.Add(m_szViews.GetAt(nTab));
				nBreakpoints--;
				nBreakpoint--;
			}
		}
	}
	return((INT)szBreakpoints.GetSize());
}

BOOL CTCProceduresMonitorItemFlowchartTabCtrl::SetActiveStep(CONST CTCProcedureDocumentItem *pStep)
{
	INT  nIndex;
	CTCProceduresMonitorItemFlowchartThreadView  *pView;

	return(((pView = ((nIndex = GetCurTab()) >= 0 && nIndex < GetTabCount()) ? (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nIndex) : (CTCProceduresMonitorItemFlowchartThreadView *)NULL)) ? pView->SetActiveStep(pStep) : FALSE);
}

CTCProcedureDocumentItem *CTCProceduresMonitorItemFlowchartTabCtrl::GetActiveStep(BOOL bAll) CONST
{
	INT  nIndex;
	CTCProceduresMonitorItemFlowchartThreadView  *pView;

	return(((pView = ((nIndex = GetCurTab()) >= 0 && nIndex < GetTabCount()) ? (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nIndex) : (CTCProceduresMonitorItemFlowchartThreadView *)NULL)) ? pView->GetActiveStep(bAll) : (CTCProcedureDocumentItem *)NULL);
}

INT CTCProceduresMonitorItemFlowchartTabCtrl::GetTotalSteps() CONST
{
	INT  nIndex;
	CTCProceduresMonitorItemFlowchartThreadView  *pView;

	return(((pView = ((nIndex = GetCurTab()) >= 0 && nIndex < GetTabCount()) ? (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nIndex) : (CTCProceduresMonitorItemFlowchartThreadView *)NULL)) ? pView->GetTotalSteps() : 0);
}

BOOL CTCProceduresMonitorItemFlowchartTabCtrl::SetStepsTitleFont(CONST LOGFONT *plfFont)
{
	CFont  cFont;

	if (cFont.CreateFontIndirect(plfFont))
	{
		for (m_cTabFont.DeleteObject(); m_cTabFont.Attach(cFont.Detach()); )
		{
			SetFont(&m_cTabFont);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemFlowchartTabCtrl::GetStepsTitleFont(LOGFONT *plfFont) CONST
{
	return((m_cTabFont.GetObject(sizeof(LOGFONT), plfFont) > 0) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorItemFlowchartTabCtrl::SetStepsLabelFont(CONST LOGFONT *plfFont)
{
	INT  nTab;
	INT  nTabs;
	CTCProceduresMonitorItemFlowchartThreadView  *pView;

	for (nTab = 0, nTabs = GetTabCount(); nTab < nTabs; nTab++)
	{
		if ((pView = (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nTab)))
		{
			pView->SetStepsLabelFont(plfFont);
			continue;
		}
	}
}

BOOL CTCProceduresMonitorItemFlowchartTabCtrl::GetStepsLabelFont(LOGFONT *plfFont) CONST
{
	INT  nIndex;
	CTCProceduresMonitorItemFlowchartThreadView  *pView;

	return(((pView = ((nIndex = GetCurTab()) >= 0 && nIndex < GetTabCount()) ? (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nIndex) : (CTCProceduresMonitorItemFlowchartThreadView *)NULL)) ? pView->GetStepsLabelFont(plfFont) : FALSE);
}

VOID CTCProceduresMonitorItemFlowchartTabCtrl::SetStepsLabelColor(COLORREF nColor)
{
	INT  nTab;
	INT  nTabs;
	CTCProceduresMonitorItemFlowchartThreadView  *pView;

	for (nTab = 0, nTabs = GetTabCount(); nTab < nTabs; nTab++)
	{
		if ((pView = (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nTab)))
		{
			pView->SetStepsLabelColor(nColor);
			continue;
		}
	}
}

COLORREF CTCProceduresMonitorItemFlowchartTabCtrl::GetStepsLabelColor() CONST
{
	INT  nIndex;
	CTCProceduresMonitorItemFlowchartThreadView  *pView;

	return(((pView = ((nIndex = GetCurTab()) >= 0 && nIndex < GetTabCount()) ? (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nIndex) : (CTCProceduresMonitorItemFlowchartThreadView *)NULL)) ? pView->GetStepsLabelColor() : GetSysColor(COLOR_WINDOWTEXT));
}

VOID CTCProceduresMonitorItemFlowchartTabCtrl::SetBackgroundColor(COLORREF nColor)
{
	INT  nTab;
	INT  nTabs;
	CTCProceduresMonitorItemFlowchartThreadView  *pView;

	for (nTab = 0, nTabs = GetTabCount(); nTab < nTabs; nTab++)
	{
		if ((pView = (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nTab)))
		{
			pView->SetBackgroundColor(nColor);
			continue;
		}
	}
}

COLORREF CTCProceduresMonitorItemFlowchartTabCtrl::GetBackgroundColor() CONST
{
	INT  nIndex;
	CTCProceduresMonitorItemFlowchartThreadView  *pView;

	return(((pView = ((nIndex = GetCurTab()) >= 0 && nIndex < GetTabCount()) ? (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nIndex) : (CTCProceduresMonitorItemFlowchartThreadView *)NULL)) ? pView->GetBackgroundColor() : GetSysColor(COLOR_WINDOW));
}

VOID CTCProceduresMonitorItemFlowchartTabCtrl::AllowExecutionBreaks(BOOL bAllow)
{
	INT  nTab;
	INT  nTabs;
	CTCProceduresMonitorItemFlowchartThreadView  *pView;

	for (nTab = 0, nTabs = GetTabCount(); nTab < nTabs; nTab++)
	{
		if ((pView = (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nTab)))
		{
			pView->AllowExecutionBreaks(bAllow);
			continue;
		}
	}
}

BOOL CTCProceduresMonitorItemFlowchartTabCtrl::AreExecutionBreaksAllowed() CONST
{
	INT  nTab;
	INT  nTabs;
	CTCProceduresMonitorItemFlowchartThreadView  *pView;

	for (nTab = 0, nTabs = GetTabCount(); nTab < nTabs; nTab++)
	{
		if ((pView = (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nTab)) && pView->AreExecutionBreaksAllowed()) break;
		continue;
	}
	return((nTab < nTabs) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorItemFlowchartTabCtrl::EnableToolTipMode(BOOL bEnable)
{
	INT  nTab;
	INT  nTabs;
	CTCProceduresMonitorItemFlowchartThreadView  *pView;

	for (nTab = 0, nTabs = GetTabCount(); nTab < nTabs; nTab++)
	{
		if ((pView = (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nTab)))
		{
			pView->EnableToolTipMode(bEnable);
			continue;
		}
	}
}

BOOL CTCProceduresMonitorItemFlowchartTabCtrl::IsToolTipModeEnabled() CONST
{
	INT  nTab;
	INT  nTabs;
	CTCProceduresMonitorItemFlowchartThreadView  *pView;

	for (nTab = 0, nTabs = GetTabCount(); nTab < nTabs; nTab++)
	{
		if ((pView = (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nTab)) && pView->IsToolTipModeEnabled()) break;
		continue;
	}
	return((nTab < nTabs) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorItemFlowchartTabCtrl::SetSelectedThreadID(INT nThreadID)
{
	CTCProceduresMonitorItemFlowchartThreadView  *pView[2];

	if ((pView[0] = (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(max(GetCurTab(), 0))))
	{
		if ((pView[1] = (nThreadID >= 0 && nThreadID < GetTabCount()) ? (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nThreadID) : (CTCProceduresMonitorItemFlowchartThreadView *)NULL))
		{
			pView[0]->ShowWindow((pView[0] == pView[1]) ? SW_SHOW : SW_HIDE);
			pView[1]->ShowWindow(SW_SHOW);
			pView[1]->RedrawWindow();
			SetCurTab(nThreadID);
		}
		pView[0]->UpdateAllSteps();
	}
}

INT CTCProceduresMonitorItemFlowchartTabCtrl::GetSelectedThreadID() CONST
{
	return((GetTabCount() > 0) ? GetCurTab() : -1);
}

INT CTCProceduresMonitorItemFlowchartTabCtrl::SetCurTab(INT nIndex)
{
	return SetCurSel((m_nIndex = nIndex));
}

INT CTCProceduresMonitorItemFlowchartTabCtrl::GetCurTab() CONST
{
	return m_nIndex;
}

INT CTCProceduresMonitorItemFlowchartTabCtrl::GetTabCount() CONST
{
	return((INT)m_pViews.GetSize());
}

BOOL CTCProceduresMonitorItemFlowchartTabCtrl::HasImage() CONST
{
	INT  nTab;
	INT  nTabs;
	CTCProceduresMonitorItemFlowchartThreadView  *pView;

	for (nTab = 0, nTabs = GetTabCount(); nTab < nTabs; nTab++)
	{
		if ((pView = (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nTab)))
		{
			if (pView->HasImage()) break;
			continue;
		}
	}
	return((nTab < nTabs) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorItemFlowchartTabCtrl::UpdateSteps()
{
	INT  nIndex;
	CTCProceduresMonitorItemFlowchartThreadView  *pView;

	if ((pView = ((nIndex = GetCurTab()) >= 0 && nIndex < GetTabCount()) ? (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nIndex) : (CTCProceduresMonitorItemFlowchartThreadView *)NULL))
	{
		pView->UpdateAllSteps();
		return;
	}
}
BOOL CTCProceduresMonitorItemFlowchartTabCtrl::UpdateSteps(INT nThreadID, UINT nState, CONST CStringArray &szSteps, CONST CUIntArray &nStates)
{
	CTCProceduresMonitorItemFlowchartThreadView  *pView;

	if ((pView = (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nThreadID)))
	{
		pView->UpdateAllSteps(nState, szSteps, nStates);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemFlowchartTabCtrl::GetPrintProperties(CStringArray &szThreads, CPtrArray &pThreadMetaDCs) CONST
{
	INT  nTab;
	INT  nTabs;
	CMetaFileDC  *pThreadMetaDC;
	CTCProceduresMonitorItemFlowchartThreadView  *pView;
	CClientDC  cDC(NULL);

	for (nTab = 0, nTabs = GetTabCount(), szThreads.RemoveAll(), pThreadMetaDCs.RemoveAll(); nTab < nTabs; nTab++)
	{
		if ((pThreadMetaDC = ((pView = (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nTab))) ? new CMetaFileDC : (CMetaFileDC *)NULL))
		{
			if (pThreadMetaDC->CreateEnhanced(&cDC, (LPCTSTR)NULL, (LPCRECT)NULL, (LPCTSTR)NULL))
			{
				pThreadMetaDC->SetAttribDC(cDC.GetSafeHdc());
				pView->GetPrintProperties(pThreadMetaDC);
				szThreads.Add(m_szViews.GetAt(nTab));
				pThreadMetaDCs.Add(pThreadMetaDC);
				continue;
			}
			delete pThreadMetaDC;
			break;
		}
	}
	return((nTabs == szThreads.GetSize()) ? TRUE : FALSE);
}

CSize CTCProceduresMonitorItemFlowchartTabCtrl::GetMargins() CONST
{
	return m_sizeTabMargins;
}

CTCProceduresMonitorItemFlowchartView *CTCProceduresMonitorItemFlowchartTabCtrl::GetParent() CONST
{
	return((CTCProceduresMonitorItemFlowchartView *)m_pParentWnd);
}

CTCProceduresMonitorWnd *CTCProceduresMonitorItemFlowchartTabCtrl::GetParentDisplay() CONST
{
	CTCProceduresMonitorItemFlowchartView  *pView;

	return(((pView = GetParent())) ? pView->GetParentDisplay() : (CTCProceduresMonitorWnd *)NULL);
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorItemFlowchartTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CTCProceduresMonitorItemFlowchartTabCtrl)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemFlowchartTabCtrl message handlers

int CTCProceduresMonitorItemFlowchartTabCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CFontTools  cFontTools(&m_cTabFont);

	if (CTabCtrl::OnCreate(lpCreateStruct) != -1)
	{
		SetFont(&m_cTabFont);
		return 0;
	}
	return -1;
}

BOOL CTCProceduresMonitorItemFlowchartTabCtrl::OnEraseBkgnd(CDC *pDC)
{
	INT  nTab;
	INT  nTabs;
	CRect  rView[3];
	CTCProceduresMonitorItemFlowchartThreadView  *pView;

	for (nTab = 0, nTabs = GetTabCount(), GetClientRect(rView[0]), AdjustRect(FALSE, rView[0]), rView[0].DeflateRect(GetSystemMetrics(SM_CXEDGE), GetSystemMetrics(SM_CYEDGE)), pDC->DrawEdge((rView[1] = rView[0]), EDGE_SUNKEN, BF_ADJUST | BF_RECT), pDC->ExcludeClipRect(rView[1]); nTab < nTabs; nTab++)
	{
		if ((pView = (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nTab)) != (CTCProceduresMonitorItemFlowchartThreadView *)NULL)
		{
			for (pView->GetWindowRect(rView[2]), ScreenToClient(rView[2]); rView[1] != rView[2]; )
			{
				pView->MoveWindow(rView[1]);
				InvalidateRect(rView[0]);
				break;
			}
			pDC->ExcludeClipRect(rView[1]);
		}
	}
	pDC->ExcludeClipRect(rView[0].left, rView[0].top, rView[1].left, rView[0].bottom);
	pDC->ExcludeClipRect(rView[0].left, rView[0].top, rView[0].right, rView[1].top);
	pDC->ExcludeClipRect(rView[1].right, rView[0].top, rView[0].right, rView[0].bottom);
	pDC->ExcludeClipRect(rView[0].left, rView[1].bottom, rView[0].right, rView[0].bottom);
	return CTabCtrl::OnEraseBkgnd(pDC);
}

void CTCProceduresMonitorItemFlowchartTabCtrl::OnSelchange(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	INT  nIndex;
	CTCProceduresMonitorItemFlowchartThreadView  *pView[2];

	if ((pView[0] = ((nIndex = TabCtrl_GetCurSel(GetSafeHwnd())) >= 0 && nIndex < GetTabCount() && nIndex != m_nIndex) ? (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nIndex) : (CTCProceduresMonitorItemFlowchartThreadView *)NULL))
	{
		for (pView[0]->ShowWindow(SW_SHOW); (pView[1] = (nIndex != m_nIndex) ? (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(m_nIndex) : (CTCProceduresMonitorItemFlowchartThreadView *)NULL); m_nIndex = nIndex)
		{
			pView[1]->ShowWindow(SW_HIDE);
			continue;
		}
		pView[0]->UpdateAllSteps();
		*pResult = TRUE;
	}
}

void CTCProceduresMonitorItemFlowchartTabCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	INT  nIndex;
	CTCProceduresMonitorItemFlowchartThreadView  *pView;

	if (nChar == VK_DOWN)
	{
		if ((pView = ((nIndex = GetCurTab()) >= 0 && nIndex < GetTabCount()) ? (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nIndex) : (CTCProceduresMonitorItemFlowchartThreadView *)NULL))
		{
			pView->SetFocus();
			return;
		}
	}
	if (nChar == VK_TAB)
	{
		GetParent()->SetFocus();
		return;
	}
	CTabCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTCProceduresMonitorItemFlowchartTabCtrl::OnDestroy()
{
	INT  nTab;
	INT  nTabs;
	CTCProceduresMonitorItemFlowchartThreadView  *pView;

	for (nTab = 0, nTabs = GetTabCount(); nTab < nTabs; nTab++)
	{
		if ((pView = (CTCProceduresMonitorItemFlowchartThreadView *)m_pViews.GetAt(nTab)))
		{
			pView->DestroyWindow();
			continue;
		}
	}
	m_cTabFont.DeleteObject();
	CTabCtrl::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemFlowchartView

IMPLEMENT_DYNCREATE(CTCProceduresMonitorItemFlowchartView, CView)

CTCProceduresMonitorItemFlowchartView::CTCProceduresMonitorItemFlowchartView() : CView(), CDisplayLockable()
{
	CFontTools  cFontTools[2] = { &m_lfTitleFont,&m_lfLabelsFont };

	m_bBreaks = TRUE;
	m_bToolTips = TRUE;
	m_sizeTrackLayout.cx = 0;
	m_sizeTrackLayout.cy = 0;
	m_nLabelsColor = GetSysColor(COLOR_WINDOWTEXT);
	m_nBackgroundColor = GetSysColor(COLOR_WINDOW);
	m_pParentWnd = (CWnd *)NULL;
}

BOOL CTCProceduresMonitorItemFlowchartView::SetFlowcharts(CONST CTCProceduresMonitorItem *pItem)
{
	CDisplayLock  cLock(this);

	return m_wndTabCtrl.SetFlowcharts(pItem);
}

BOOL CTCProceduresMonitorItemFlowchartView::GetFlowcharts(CTCProceduresMonitorItem *pItem) CONST
{
	CDisplayLock  cLock(this);

	return m_wndTabCtrl.GetFlowcharts(pItem);
}

BOOL CTCProceduresMonitorItemFlowchartView::SetTitleFont(CFont *pFont)
{
	LOGFONT  lfFont;
	CDisplayLock  cLock(this);

	return(pFont->GetLogFont(&lfFont) && SetTitleFont(&lfFont));
}
BOOL CTCProceduresMonitorItemFlowchartView::SetTitleFont(CONST LOGFONT *plfFont)
{
	CDisplayLock  cLock(this);

	m_wndTabCtrl.SetStepsTitleFont(plfFont);
	CopyMemory(&m_lfTitleFont, plfFont, sizeof(LOGFONT));
	return TRUE;
}

BOOL CTCProceduresMonitorItemFlowchartView::GetTitleFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;
	CDisplayLock  cLock(this);

	return(m_wndTabCtrl.GetStepsTitleFont(&lfFont) && pFont->CreateFontIndirect(&lfFont));
}
BOOL CTCProceduresMonitorItemFlowchartView::GetTitleFont(LOGFONT *plfFont) CONST
{
	CDisplayLock  cLock(this);

	CopyMemory(plfFont, &m_lfTitleFont, sizeof(LOGFONT));
	return TRUE;
}

BOOL CTCProceduresMonitorItemFlowchartView::SetLabelsFont(CFont *pFont)
{
	LOGFONT  lfFont;
	CDisplayLock  cLock(this);

	return(pFont->GetLogFont(&lfFont) && SetLabelsFont(&lfFont));
}
BOOL CTCProceduresMonitorItemFlowchartView::SetLabelsFont(CONST LOGFONT *plfFont)
{
	CDisplayLock  cLock(this);

	m_wndTabCtrl.SetStepsLabelFont(plfFont);
	CopyMemory(&m_lfLabelsFont, plfFont, sizeof(LOGFONT));
	return TRUE;
}

BOOL CTCProceduresMonitorItemFlowchartView::GetLabelsFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;
	CDisplayLock  cLock(this);

	return(GetLabelsFont(&lfFont) && pFont->CreateFontIndirect(&lfFont));
}
BOOL CTCProceduresMonitorItemFlowchartView::GetLabelsFont(LOGFONT *plfFont) CONST
{
	CDisplayLock  cLock(this);

	CopyMemory(plfFont, &m_lfLabelsFont, sizeof(LOGFONT));
	return TRUE;
}

BOOL CTCProceduresMonitorItemFlowchartView::SetLabelsColor(COLORREF nColor)
{
	CDisplayLock  cLock(this);

	m_wndTabCtrl.SetStepsLabelColor(nColor);
	m_nLabelsColor = nColor;
	return TRUE;
}

BOOL CTCProceduresMonitorItemFlowchartView::GetLabelsColor(COLORREF &nColor) CONST
{
	nColor = m_nLabelsColor;
	return TRUE;
}

BOOL CTCProceduresMonitorItemFlowchartView::SetBackgroundColor(COLORREF nColor)
{
	CDisplayLock  cLock(this);

	m_wndTabCtrl.SetBackgroundColor(nColor);
	m_nBackgroundColor = nColor;
	return TRUE;
}

BOOL CTCProceduresMonitorItemFlowchartView::GetBackgroundColor(COLORREF &nColor) CONST
{
	nColor = m_nBackgroundColor;
	return TRUE;
}

BOOL CTCProceduresMonitorItemFlowchartView::AllowExecutionBreaks(BOOL bAllow)
{
	CDisplayLock  cLock(this);

	m_wndTabCtrl.AllowExecutionBreaks((m_bBreaks = bAllow));
	return TRUE;
}

BOOL CTCProceduresMonitorItemFlowchartView::AreExecutionBreaksAllowed() CONST
{
	return m_bBreaks;
}

BOOL CTCProceduresMonitorItemFlowchartView::EnableToolTipMode(BOOL bEnable)
{
	CDisplayLock  cLock(this);

	m_wndTabCtrl.EnableToolTipMode((m_bToolTips = bEnable));
	return TRUE;
}

BOOL CTCProceduresMonitorItemFlowchartView::IsToolTipModeEnabled() CONST
{
	return m_bToolTips;
}

BOOL CTCProceduresMonitorItemFlowchartView::SetSelectedThreadID(INT nThreadID)
{
	CDisplayLock  cLock(this);

	m_wndTabCtrl.SetSelectedThreadID(nThreadID);
	return TRUE;
}

INT CTCProceduresMonitorItemFlowchartView::GetSelectedThreadID() CONST
{
	CDisplayLock  cLock(this);

	return m_wndTabCtrl.GetSelectedThreadID();
}

BOOL CTCProceduresMonitorItemFlowchartView::SetLayoutInfo(INT nThreadID)
{
	CDisplayLock  cLock(this);

	m_wndTabCtrl.SetSelectedThreadID(nThreadID);
	return TRUE;
}

BOOL CTCProceduresMonitorItemFlowchartView::GetLayoutInfo(INT &nThreadID) CONST
{
	CDisplayLock  cLock(this);

	nThreadID = m_wndTabCtrl.GetSelectedThreadID();
	return TRUE;
}

BOOL CTCProceduresMonitorItemFlowchartView::GetPrintProperties(CStringArray &szThreads, CPtrArray &pThreadMetaDCs) CONST
{
	CDisplayLock  cLock(this);

	return m_wndTabCtrl.GetPrintProperties(szThreads, pThreadMetaDCs);
}

BOOL CTCProceduresMonitorItemFlowchartView::UpdateContents()
{
	INT  nIndex;
	INT  nThread;
	INT  nThreads;
	INT  nBreakpoint;
	INT  nBreakpoints;
	CStringArray  szBreakpoints;
	CTCProceduresMonitorItem  cProcedure;
	CDatabaseTCProcedureThread  *pThread;
	CDatabaseTCProcedureThreadBreakpoint  *pBreakpoint;
	CDatabaseTCProcedureThreadBreakpoints  pBreakpoints[2];
	CDisplayLock  cLock(this);

	if (GetParentDisplay()->GetProcedureInfo((nIndex = GetParentDisplay()->GetCurProcedure()), &cProcedure))
	{
		for (nThread = 0, nThreads = (cProcedure.AreExecutionBreaksAllowed()) ? (INT)cProcedure.GetSize() : 0, AllowExecutionBreaks(cProcedure.AreExecutionBreaksAllowed()); nThread < nThreads; nThread++)
		{
			if ((pThread = cProcedure.GetAt(nThread)) && pThread->GetBreakpoints(pBreakpoints[0]) > 0)
			{
				for (nBreakpoint = 0, nBreakpoints = (INT)pBreakpoints[0].GetSize(); nBreakpoint < nBreakpoints; nBreakpoint++)
				{
					if ((pBreakpoint = pBreakpoints[0].GetAt(nBreakpoint)) && !pBreakpoint->GetLocation().IsEmpty())
					{
						szBreakpoints.Add(pThread->GetName());
						pBreakpoints[1].Add(pBreakpoint);
						pBreakpoints[0].RemoveAt(nBreakpoint);
						nBreakpoints--;
						nBreakpoint--;
					}
				}
			}
		}
		m_wndTabCtrl.SetFlowcharts(&cProcedure);
		m_wndTabCtrl.SetBreakpoints(szBreakpoints, pBreakpoints[1]);
		return TRUE;
	}
	if (nIndex < 0)
	{
		m_wndTabCtrl.SetFlowcharts(&cProcedure);
		return TRUE;
	}
	return FALSE;
}
BOOL CTCProceduresMonitorItemFlowchartView::UpdateContents(INT nThreadID, UINT nState, CONST CStringArray &szSteps, CONST CUIntArray &nStates)
{
	CDisplayLock  cLock(this);

	return m_wndTabCtrl.UpdateSteps(nThreadID, nState, szSteps, nStates);
}

BOOL CTCProceduresMonitorItemFlowchartView::HasContents() CONST
{
	CDisplayLock  cLock(this);

	return m_wndTabCtrl.HasImage();
}

VOID CTCProceduresMonitorItemFlowchartView::SetTrackSize(CONST SIZE &size)
{
	CDisplayLock  cLock(this);

	m_sizeTrackLayout = size;
}

CSize CTCProceduresMonitorItemFlowchartView::GetTrackSize() CONST
{
	CDisplayLock  cLock(this);

	return m_sizeTrackLayout;
}

CTCProceduresMonitorItemContents *CTCProceduresMonitorItemFlowchartView::GetParent() CONST
{
	return((CTCProceduresMonitorItemContents *)m_pParentWnd);
}

CTCProceduresMonitorWnd *CTCProceduresMonitorItemFlowchartView::GetParentDisplay() CONST
{
	CTCProceduresMonitorItemContents  *pContents;

	return(((pContents = GetParent())) ? pContents->GetParent()->GetParent()->GetParent() : (CTCProceduresMonitorWnd *)NULL);
}

BOOL CTCProceduresMonitorItemFlowchartView::Lock()
{
	CTCProceduresMonitorWnd  *pParentWnd;

	return(((pParentWnd = GetParentDisplay())) ? (pParentWnd->Lock() && GetLock()->Lock()) : GetLock()->Lock());
}

BOOL CTCProceduresMonitorItemFlowchartView::Unlock()
{
	CTCProceduresMonitorWnd  *pParentWnd;

	return(((pParentWnd = GetParentDisplay())) ? (GetLock()->Unlock() && pParentWnd->Unlock()) : GetLock()->Unlock());
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorItemFlowchartView, CView)
	//{{AFX_MSG_MAP(CTCProceduresMonitorItemFlowchartView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemFlowchartView drawing

void CTCProceduresMonitorItemFlowchartView::OnDraw(CDC *pDC)
{
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemFlowchartView message handlers

int CTCProceduresMonitorItemFlowchartView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) != -1 && m_wndTabCtrl.Create(this, CRect(0, 0, 0, 0)))
	{
		m_pParentWnd = CView::GetParent();
		return 0;
	}
	return -1;
}

void CTCProceduresMonitorItemFlowchartView::OnSize(UINT nType, int cx, int cy)
{
	m_wndTabCtrl.MoveWindow(0, 0, cx, cy);
	CView::OnSize(nType, cx, cy);
}

BOOL CTCProceduresMonitorItemFlowchartView::OnEraseBkgnd(CDC *pDC)
{
	CRect  rView;
	CRect  rPage[3];

	for (GetClientRect(rView), m_wndTabCtrl.GetItemRect(0, rPage[0]), m_wndTabCtrl.GetItemRect(m_wndTabCtrl.GetCurSel(), rPage[1]), m_wndTabCtrl.GetItemRect(m_wndTabCtrl.GetItemCount() - 1, rPage[2]), m_wndTabCtrl.ClientToScreen(rPage[0]), m_wndTabCtrl.ClientToScreen(rPage[1]), m_wndTabCtrl.ClientToScreen(rPage[2]), ScreenToClient(rPage[0]), ScreenToClient(rPage[1]), ScreenToClient(rPage[2]), rPage[0].InflateRect((!m_wndTabCtrl.GetCurSel()) ? m_wndTabCtrl.GetMargins().cx : 0, 0, 0, 0), rPage[1].InflateRect(0, m_wndTabCtrl.GetMargins().cy); m_wndTabCtrl.GetCurSel() != m_wndTabCtrl.GetItemCount() - 1; )
	{
		rPage[2].DeflateRect(0, 0, m_wndTabCtrl.GetMargins().cx, 0);
		break;
	}
	rView.SetRect(rView.left, rView.top, rView.right, rPage[0].bottom);
	pDC->ExcludeClipRect(rPage[0].left, rPage[0].top, rPage[2].right, (rView.Width() < rPage[2].right - rPage[0].left) ? (rPage[0].top + GetSystemMetrics(SM_CYHSCROLL)) : rPage[2].bottom);
	pDC->ExcludeClipRect(rPage[1].left, rPage[1].top, rPage[1].right, (rView.Width() < rPage[2].right - rPage[0].left) ? (rPage[0].top + GetSystemMetrics(SM_CYHSCROLL)) : rPage[1].bottom);
	pDC->FillSolidRect(rView, GetSysColor(COLOR_BTNFACE));
	return TRUE;
}

void CTCProceduresMonitorItemFlowchartView::OnSetFocus(CWnd *pOldWnd)
{
	if (IsWindow(pOldWnd->GetSafeHwnd()))
	{
		if (pOldWnd == GetParent())
		{
			m_wndTabCtrl.SetFocus();
			return;
		}
		if (IsChild(pOldWnd))
		{
			GetParent()->SetFocus();
			return;
		}
	}
	CView::OnSetFocus(pOldWnd);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemCodeEdit

IMPLEMENT_DYNCREATE(CTCProceduresMonitorItemCodeEdit, CTPLCodeEdit)

CTCProceduresMonitorItemCodeEdit::CTCProceduresMonitorItemCodeEdit() : CTPLCodeEdit(), CDisplayLockable()
{
	CFontTools  cFontTools(&m_cCodeFont);

	m_bBreaks = TRUE;
	m_bToolTips = TRUE;
	m_sizeCodeFont.cx = 0;
	m_sizeCodeFont.cy = 0;
	m_pParentWnd = (CWnd *)NULL;
}

BOOL CTCProceduresMonitorItemCodeEdit::Create(CWnd *pParentWnd, CONST RECT &rect)
{
	return CTPLCodeEdit::Create((m_pParentWnd = pParentWnd), rect, 0);
}

VOID CTCProceduresMonitorItemCodeEdit::SetSourceCode(LPCTSTR pszCode)
{
	CDisplayLock  cLock(this);

	SetWindowText(pszCode);
	LineScroll(-GetFirstVisibleLine());
}
BOOL CTCProceduresMonitorItemCodeEdit::SetSourceCode(CONST CByteArray &nCode)
{
	EDITSTREAM  sStream;
	CTPLCodeEdit  *pEdit;
	CDisplayLock  cLock(this);

	for (pEdit = (CTPLCodeEdit *) this, sStream.dwCookie = (DWORD_PTR)&nCode, sStream.pfnCallback = SetCodeCallback, pEdit->StreamIn(SF_RTF, sStream); !sStream.dwError; )
	{
		LineScroll(-GetFirstVisibleLine());
		return TRUE;
	}
	return FALSE;
}

CString CTCProceduresMonitorItemCodeEdit::GetSourceCode() CONST
{
	CString  szSourceCode;
	CDisplayLock  cLock(this);

	GetWindowText(szSourceCode);
	return szSourceCode;
}
BOOL CTCProceduresMonitorItemCodeEdit::GetSourceCode(CByteArray &nCode) CONST
{
	EDITSTREAM  sStream;
	CTPLCodeEdit  *pEdit;
	CDisplayLock  cLock(this);

	for (pEdit = (CTPLCodeEdit *) this, nCode.RemoveAll(), sStream.dwCookie = (DWORD_PTR)&nCode, sStream.pfnCallback = GetCodeCallback, pEdit->StreamOut(SF_RTF, sStream); !sStream.dwError; ) return TRUE;
	return FALSE;
}

VOID CTCProceduresMonitorItemCodeEdit::SetBreakpoints(CONST CStringArray &szBreakpoints, CONST CDatabaseTCProcedureThreadBreakpoints &pBreakpoints)
{
	CDisplayLock  cLock(this);

	m_szBreakpoints.Copy(szBreakpoints);
	m_pBreakpoints.Copy(&pBreakpoints);
	DrawMargin();
}

INT CTCProceduresMonitorItemCodeEdit::GetBreakpoints(CStringArray &szBreakpoints, CDatabaseTCProcedureThreadBreakpoints &pBreakpoints) CONST
{
	CDisplayLock  cLock(this);

	szBreakpoints.Copy(m_szBreakpoints);
	pBreakpoints.Copy(&m_pBreakpoints);
	return((INT)szBreakpoints.GetSize());
}

VOID CTCProceduresMonitorItemCodeEdit::AllowExecutionBreaks(BOOL bAllow)
{
	m_bBreaks = bAllow;
}

BOOL CTCProceduresMonitorItemCodeEdit::AreExecutionBreaksAllowed() CONST
{
	return m_bBreaks;
}

VOID CTCProceduresMonitorItemCodeEdit::EnableToolTipMode(BOOL bEnable)
{
	m_bToolTips = bEnable;
}

BOOL CTCProceduresMonitorItemCodeEdit::IsToolTipModeEnabled() CONST
{
	return m_bToolTips;
}

BOOL CTCProceduresMonitorItemCodeEdit::SetFont(CFont *pFont, BOOL bRedraw)
{
	CDC  *pDC;
	CFont  *pOldFont;
	LOGFONT  lfFont;
	TEXTMETRIC  tmFont;
	CDisplayLock  cLock(this);

	if (pFont->GetLogFont(&lfFont) > 0)
	{
		for (m_cCodeFont.DeleteObject(); m_cCodeFont.CreateFontIndirect(&lfFont); )
		{
			for (CTPLCodeEdit::SetFont(&m_cCodeFont, bRedraw); (pDC = GetDC()); )
			{
				if ((pOldFont = pDC->SelectObject(&m_cCodeFont)))
				{
					if (pDC->GetTextMetrics(&tmFont))
					{
						m_sizeCodeFont.cx = tmFont.tmAveCharWidth;
						m_sizeCodeFont.cy = tmFont.tmHeight;
					}
					pDC->SelectObject(pOldFont);
				}
				ReleaseDC(pDC);
				break;
			}
			DrawMargin();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemCodeEdit::GetFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;
	CDisplayLock  cLock(this);

	return((m_cCodeFont.GetObject(sizeof(LOGFONT), &lfFont) > 0 && pFont->CreateFontIndirect(&lfFont)) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorItemCodeEdit::UpdateBreakpoints()
{
	INT  nBreakpoint[2];
	INT  nBreakpoints[2];
	CStringArray  szBreakpoints;
	CDatabaseTCProcedureThreadBreakpoint  *pBreakpoint;
	CDatabaseTCProcedureThreadBreakpoints  pBreakpoints;
	CDisplayLock  cLock(this);

	for (nBreakpoint[0] = 0, nBreakpoints[0] = (INT)m_szBreakpoints.GetSize(); nBreakpoint[0] < nBreakpoints[0]; nBreakpoint[0]++)
	{
		for (nBreakpoint[1] = 0, nBreakpoints[1] = (INT)szBreakpoints.GetSize(); nBreakpoint[1] < nBreakpoints[1]; nBreakpoint[1]++)
		{
			if (m_szBreakpoints.GetAt(nBreakpoint[0]) == szBreakpoints.GetAt(nBreakpoint[1])) break;
			continue;
		}
		if (nBreakpoint[1] == nBreakpoints[1])
		{
			szBreakpoints.Add(m_szBreakpoints.GetAt(nBreakpoint[0]));
			continue;
		}
	}
	for (nBreakpoint[0] = 0, nBreakpoints[0] = (INT)szBreakpoints.GetSize(); nBreakpoint[0] < nBreakpoints[0]; nBreakpoint[0]++)
	{
		for (nBreakpoint[1] = 0, nBreakpoints[1] = (INT)m_szBreakpoints.GetSize(), pBreakpoints.RemoveAll(); nBreakpoint[1] < nBreakpoints[1]; nBreakpoint[1]++)
		{
			if (szBreakpoints.GetAt(nBreakpoint[0]) == m_szBreakpoints.GetAt(nBreakpoint[1]))
			{
				if ((pBreakpoint = new CDatabaseTCProcedureThreadBreakpoint))
				{
					pBreakpoint->Copy(m_pBreakpoints.GetAt(nBreakpoint[1]));
					if (pBreakpoints.Add(pBreakpoint) >= 0) continue;
					delete pBreakpoint;
				}
			}
		}
		GetParent()->UpdateBreakpoints(szBreakpoints.GetAt(nBreakpoint[0]), pBreakpoints);
	}
	for (pBreakpoints.RemoveAll(); !nBreakpoints[0]; )
	{
		GetParent()->UpdateBreakpoints(EMPTYSTRING, pBreakpoints);
		break;
	}
}

VOID CTCProceduresMonitorItemCodeEdit::UpdateExecutionpoint(UINT nThreadID, UINT nState, UINT nLine)
{
	INT  nThread;
	INT  nThreads;
	CDisplayLock  cLock(this);

	for (nThread = 0, nThreads = (INT)m_nExecutionThreadIDs.GetSize(); nThread < nThreads; nThread++)
	{
		if (m_nExecutionThreadIDs.GetAt(nThread) == nThreadID) break;
		continue;
	}
	if (nLine != 0)
	{
		if (nThread < m_nExecutionThreadIDs.GetSize() || nLine != (UINT)-1)
		{
			m_nExecutionThreadIDs.SetAtGrow(nThread, nThreadID);
			m_nExecutionStates.SetAtGrow(nThread, nState);
			m_nExecutionLines.SetAtGrow(nThread, (nLine == (UINT)-1) ? m_nExecutionLines.GetAt(nThread) : nLine);
		}
	}
	else if (nThread < m_nExecutionThreadIDs.GetSize())
	{
		m_nExecutionThreadIDs.RemoveAt(nThread);
		m_nExecutionStates.RemoveAt(nThread);
		m_nExecutionLines.RemoveAt(nThread);
	}
	RedrawWindow((LPCRECT)NULL, (CRgn *)NULL, RDW_INVALIDATE);
}

CTCProceduresMonitorItemCodeView *CTCProceduresMonitorItemCodeEdit::GetParent() CONST
{
	return((CTCProceduresMonitorItemCodeView *)m_pParentWnd);
}

CTCProceduresMonitorWnd *CTCProceduresMonitorItemCodeEdit::GetParentDisplay() CONST
{
	CTCProceduresMonitorItemCodeView  *pView;

	return(((pView = GetParent())) ? pView->GetParentDisplay() : (CTCProceduresMonitorWnd *)NULL);
}

VOID CTCProceduresMonitorItemCodeEdit::DrawMargin()
{
	CDC  *pDC;

	if ((pDC = GetDC()))
	{
		DrawMargin(pDC);
		ReleaseDC(pDC);
	}
}
VOID CTCProceduresMonitorItemCodeEdit::DrawMargin(CDC *pDC)
{
	CDC  cDC;
	CRect  rMargin;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;

	for (rMargin = CalcMargin(); cDC.CreateCompatibleDC(pDC); )
	{
		if (cBitmap.CreateCompatibleBitmap(pDC, rMargin.Width(), rMargin.Height()))
		{
			if ((pOldBitmap = cDC.SelectObject(&cBitmap)) != (CBitmap *)NULL)
			{
				cDC.FillSolidRect(rMargin, GetSysColor(COLOR_3DFACE));
				cDC.DrawEdge(rMargin, EDGE_ETCHED, BF_RIGHT);
				DrawBreakpoints(&cDC);
				DrawExecutionpoint(&cDC);
				pDC->BitBlt(0, 0, rMargin.Width(), rMargin.Height(), &cDC, 0, 0, SRCCOPY);
				cDC.SelectObject(pOldBitmap);
			}
			cBitmap.DeleteObject();
		}
		cDC.DeleteDC();
		break;
	}
}

VOID CTCProceduresMonitorItemCodeEdit::DrawBreakpoints(CDC *pDC)
{
	INT  nPoint;
	INT  nPoints;
	CPen  *pOldPen;
	CPen  cBreakpointPen;
	CRect  rBreakpoint;
	CBrush  *pOldBrush;
	CBrush  cBreakpointBrush;
	CDatabaseTCProcedureThreadBreakpoint  *pBreakpoint;

	for (nPoint = 0, nPoints = (INT)m_pBreakpoints.GetSize(); nPoint < nPoints; nPoint++)
	{
		if ((pBreakpoint = m_pBreakpoints.GetAt(nPoint)) != (CDatabaseTCProcedureThreadBreakpoint *)NULL)
		{
			for (rBreakpoint = CalcBreakpointPosition(pBreakpoint->GetLine()); pBreakpoint->GetLine() > 0; )
			{
				if (cBreakpointBrush.CreateSolidBrush((pBreakpoint->GetOptions() & TCPROCEDURETHREADBREAKPOINT_OPTION_DISABLED) ? GetSysColor(COLOR_3DLIGHT) : VGA_COLOR_RED))
				{
					if (cBreakpointPen.CreatePen(PS_SOLID, 1, VGA_COLOR_RED))
					{
						if ((pOldPen = pDC->SelectObject(&cBreakpointPen)))
						{
							if ((pOldBrush = pDC->SelectObject(&cBreakpointBrush)))
							{
								pDC->Ellipse(rBreakpoint);
								pDC->SelectObject(pOldBrush);
							}
							pDC->SelectObject(pOldPen);
						}
						cBreakpointPen.DeleteObject();
					}
					cBreakpointBrush.DeleteObject();
				}
				break;
			}
		}
	}
}

VOID CTCProceduresMonitorItemCodeEdit::DrawExecutionpoint(CDC *pDC)
{
	INT  nPoint;
	INT  nPoints;
	CPen  *pOldPen;
	CPen  cExecutionpointPen;
	CRect  rExecutionpoint;
	CBrush  *pOldBrush;
	CBrush  cExecutionpointBrush;
	CPoint  ptExecutionpoint[7];
	CUIntArray  nExecutionLines;
	CUIntArray  nExecutionStates;

	if (Lock())
	{
		nExecutionLines.Copy(m_nExecutionLines);
		nExecutionStates.Copy(m_nExecutionStates);
		Unlock();
	}
	for (nPoint = 0, nPoints = (INT)nExecutionLines.GetSize(); nPoint < nPoints; nPoint++)
	{
		for (rExecutionpoint = CalcExecutionpointPosition(nExecutionLines.GetAt(nPoint)); !rExecutionpoint.IsRectEmpty(); )
		{
			if (cExecutionpointBrush.CreateSolidBrush((nExecutionStates.GetAt(nPoint) & TCPROCEDURETHREAD_RUNNINGSTATE_RUNNING) ? VGA_COLOR_GREEN : (((nExecutionStates.GetAt(nPoint) & TCPROCEDURETHREAD_ACTIONSTATE_ABORT) != TCPROCEDURETHREAD_ACTIONSTATE_ABORT) ? VGA_COLOR_LTYELLOW : VGA_COLOR_LTRED)))
			{
				if (cExecutionpointPen.CreatePen(PS_SOLID, 1, VGA_COLOR_BLACK))
				{
					if ((pOldPen = pDC->SelectObject(&cExecutionpointPen)))
					{
						if ((pOldBrush = pDC->SelectObject(&cExecutionpointBrush)))
						{
							ptExecutionpoint[0].x = rExecutionpoint.right;
							ptExecutionpoint[0].y = rExecutionpoint.CenterPoint().y;
							ptExecutionpoint[1].x = rExecutionpoint.CenterPoint().x;
							ptExecutionpoint[1].y = rExecutionpoint.top;
							ptExecutionpoint[2].x = ptExecutionpoint[1].x;
							ptExecutionpoint[2].y = ptExecutionpoint[1].y + rExecutionpoint.Height() / 4;
							ptExecutionpoint[3].x = rExecutionpoint.left;
							ptExecutionpoint[3].y = ptExecutionpoint[2].y;
							ptExecutionpoint[4].x = ptExecutionpoint[3].x;
							ptExecutionpoint[4].y = rExecutionpoint.bottom - rExecutionpoint.Height() / 4;
							ptExecutionpoint[5].x = ptExecutionpoint[2].x;
							ptExecutionpoint[5].y = ptExecutionpoint[4].y;
							ptExecutionpoint[6].x = ptExecutionpoint[5].x;
							ptExecutionpoint[6].y = rExecutionpoint.bottom;
							pDC->Polygon(ptExecutionpoint, sizeof(ptExecutionpoint) / sizeof(CPoint));
							pDC->SelectObject(pOldBrush);
						}
						pDC->SelectObject(pOldPen);
					}
					cExecutionpointPen.DeleteObject();
				}
				cExecutionpointBrush.DeleteObject();
			}
			break;
		}
	}
}

CString CTCProceduresMonitorItemCodeEdit::CheckLine(UINT nLine) CONST
{
	INT  nPos[6];
	INT  nLength;
	INT  nKeyword;
	INT  nKeywords;
	CString  szLine;
	CString  szCode;
	CString  szKeyword;
	CString  szBreakpoint;

	if (GetLine(nLine, szLine.GetBufferSetLength(max(LineLength(LineIndex(nLine)), sizeof(UINT) / sizeof(TCHAR))), max(LineLength(LineIndex(nLine)), sizeof(UINT) / sizeof(TCHAR)) + 1) > 0)
	{
		for (nPos[0] = 0, GetWindowText(szCode), nLength = LineLength(LineIndex(nLine)), szLine.ReleaseBuffer(nLength); nPos[0] < nLength; nPos[0]++)
		{
			if (_istalpha(szLine.GetAt(nPos[0])) || szLine.GetAt(nPos[0]) == STRINGCHAR(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_SUBSTITUTE))
			{
				if (szLine.Mid(nPos[0]) == (szKeyword = STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_KEYWORD_ELSE)) || !_tcsncmp(szLine.Mid(nPos[0]), szKeyword, lstrlen((szKeyword = CString(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_KEYWORD_ELSE)) + SPACE))) || !_tcsncmp(szLine.Mid(nPos[0]), szKeyword, lstrlen((szKeyword = CString(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_KEYWORD_ELSE)) + STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_KEYWORDEXTENSION)))))
				{
					szLine = szLine.Mid(nPos[0] + szKeyword.GetLength());
					nLength = szLine.GetLength();
					nPos[0] = -1;
					continue;
				}
				if (!_tcsncmp(szLine.Mid(nPos[0]), szKeyword, lstrlen((szKeyword = CString(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_KEYWORD_CASE))))) || !_tcsncmp(szLine.Mid(nPos[0]), szKeyword, lstrlen((szKeyword = CString(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_KEYWORD_DEFAULT))))))
				{
					for (nPos[0] += szKeyword.GetLength(); nPos[0] < nLength; nPos[0]++)
					{
						if (!_istspace(szLine.GetAt(nPos[0]))) break;
						continue;
					}
					for (; nPos[0] < nLength; nPos[0]++)
					{
						if (!_istalnum(szLine.GetAt(nPos[0])) && szLine.GetAt(nPos[0]) != STRINGCHAR(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_SUBSTITUTE)) break;
						continue;
					}
					for (; nPos[0] < nLength; nPos[0]++)
					{
						if (!_istspace(szLine.GetAt(nPos[0]))) break;
						continue;
					}
					if (nPos[0] < nLength  &&  szLine.GetAt(nPos[0]) == STRINGCHAR(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_KEYWORDEXTENSION))
					{
						szLine = szLine.Mid(nPos[0] + lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_KEYWORDEXTENSION)));
						nLength = szLine.GetLength();
						nPos[0] = -1;
						continue;
					}
					break;
				}
				if (!_tcsncmp(szLine.Mid(nPos[0]), szKeyword, lstrlen((szKeyword = STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_KEYWORD_SWITCH)))))
				{
					for (nPos[0] += szKeyword.GetLength(); nPos[0] < nLength; nPos[0]++)
					{
						if (!_istspace(szLine.GetAt(nPos[0]))) break;
						continue;
					}
					if (nPos[0] < nLength  &&  szLine.GetAt(nPos[0]) == STRINGCHAR(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_BEGINARGUMENTS))
					{
						for (nPos[0] += lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_BEGINARGUMENTS)); nPos[0] < nLength; nPos[0]++)
						{
							if (szLine.GetAt(nPos[0]) == STRINGCHAR(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_ENDARGUMENTS)) break;
							continue;
						}
						if (nPos[0] < nLength)
						{
							szLine = szLine.Mid(nPos[0]);
							nLength = szLine.GetLength();
							nPos[0] = -1;
							continue;
						}
					}
				}
				break;
			}
			if ((nPos[1] = nPos[2] = szLine.Mid(nPos[0]).Find(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_ENDCOMMENTS))) >= 0)
			{
				for (nPos[1] -= lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_ENDCOMMENTS)); nPos[0] + nPos[1] >= 0; nPos[1]--)
				{
					if (szLine.Mid(nPos[0] + nPos[1], lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_BEGINCOMMENTS))) == STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_BEGINCOMMENTS))
					{
						szLine = szLine.Left(nPos[0] + nPos[1]) + szLine.Mid(nPos[0] + nPos[2] + lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_ENDCOMMENTS)));
						nLength = szLine.GetLength();
						nPos[0] = -1;
						break;
					}
				}
				if (nPos[0] + nPos[1] < 0 && nPos[0] >= 0)
				{
					szLine.Empty();
					nLength = 0;
					break;
				}
				continue;
			}
			if (szLine.GetAt(nPos[0]) == STRINGCHAR(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_TERMINATOR)) break;
		}
		for (nPos[0] = (nPos[0] == nLength) ? nPos[0] : 0; nPos[0] < nLength; nPos[0]++)
		{
			if (szLine.Mid(nPos[0], lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_LINECOMMENTS))) == STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_LINECOMMENTS))
			{
				nPos[0] = nLength;
				break;
			}
			if (!_istspace(szLine.GetAt(nPos[0]))) break;
		}
		if (nPos[0] < nLength)
		{
			for (nPos[0] = 0, nPos[1] = -1, nPos[4] = LineIndex(nLine) + nLine; (nPos[0] = FindKeyword(szCode, STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_KEYWORD_THREAD), max(nPos[1], 0))) >= 0 && nPos[0] + max(nPos[1], 0) < nPos[4]; )
			{
				nPos[1] = nPos[0] + max(nPos[1], 0) + lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_KEYWORD_THREAD));
				continue;
			}
			for (nPos[5] = (nPos[1] < 0) ? (nPos[0] + lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_KEYWORD_THREAD))) : nPos[1], szBreakpoint.Empty(); nPos[5] < szCode.GetLength() && (nPos[0] >= 0 || nPos[1] >= 0); nPos[5]++)
			{
				if (szCode.GetAt(nPos[5]) == STRINGCHAR(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_DELIMITER))
				{
					if (szBreakpoint.GetLength() >= lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_DELIMITER)))
					{
						szBreakpoint = szBreakpoint.Mid(lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_DELIMITER)));
						break;
					}
					szBreakpoint += szCode.GetAt(nPos[5]);
					continue;
				}
				if (!_istspace(szCode.GetAt(nPos[5])) || !szBreakpoint.IsEmpty())
				{
					if (szBreakpoint.GetLength() > 0)
					{
						szBreakpoint += szCode.GetAt(nPos[5]);
						continue;
					}
					break;
				}
			}
			for (nPos[0] = 0, nPos[2] = -1; (nPos[0] = FindKeyword(szCode, STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_KEYWORD_BEGIN), max(nPos[2], 0))) >= 0 && nPos[0] + max(nPos[2], 0) < nPos[4]; )
			{
				nPos[2] = nPos[0] + max(nPos[2], 0) + lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_KEYWORD_BEGIN));
				continue;
			}
			for (nPos[0] = 0, nPos[3] = -1; (nPos[0] = szCode.Mid(max(nPos[3], 0)).Find(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_BEGINCOMMENTS))) >= 0 && nPos[0] + max(nPos[3], 0) < nPos[4]; )
			{
				nPos[3] = nPos[0] + max(nPos[3], 0) + lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_BEGINCOMMENTS));
				continue;
			}
			for (nKeyword = MINTELECOMMANDPROCEDURELANGUAGEKEYWORD, nKeywords = MAXTELECOMMANDPROCEDURELANGUAGEKEYWORD; nKeyword <= nKeywords; nKeyword++)
			{
				for (nPos[5] = 0; nPos[5] < nLength; nPos[5]++)
				{
					if (!_istspace(szLine.GetAt(nPos[5]))) break;
					continue;
				}
				if (!szLine.Mid(nPos[5]).Find(CString(STRING(nKeyword)) + SPACE) || szLine.Mid(nPos[5]) == STRING(nKeyword)) break;
				continue;
			}
			return((nPos[1] < nPos[2] && nPos[1] >= 0 && (nPos[3] < 0 || szCode.Mid(nPos[3]).Find(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_ENDCOMMENTS)) < nLength - nPos[3] + nPos[4] - lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_ENDCOMMENTS))) && nKeyword == nKeywords + 1) ? szBreakpoint : EMPTYSTRING);
		}
	}
	return EMPTYSTRING;
}

INT CTCProceduresMonitorItemCodeEdit::FindKeyword(LPCTSTR pszSourceCode, LPCTSTR pszKeyword, INT nPos) CONST
{
	LPCTSTR  pPos;

	return(((pPos = FindKeyword(&pszSourceCode[nPos], pszKeyword))) ? ((INT)(pPos - pszSourceCode) - nPos) : -1);
}
LPCTSTR CTCProceduresMonitorItemCodeEdit::FindKeyword(LPCTSTR pszSourceCode, LPCTSTR pszKeyword) CONST
{
	LPCTSTR  pPos[2];

	for (pPos[0] = pszSourceCode; (pPos[1] = _tcsstr(pPos[0], pszKeyword)); pPos[0] = pPos[1] + lstrlen(pszKeyword))
	{
		if ((pPos[1] == pszSourceCode || (!_istalnum(pPos[1][-1]) && pPos[1][-1] != STRINGCHAR(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_SUBSTITUTE))) && (pPos[1] == pszSourceCode + lstrlen(pszSourceCode) - lstrlen(pszKeyword) || (!_istalnum(pPos[1][lstrlen(pszKeyword)]) && pPos[1][lstrlen(pszKeyword)] != STRINGCHAR(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_SUBSTITUTE)))) break;
		continue;
	}
	return pPos[1];
}

CRect CTCProceduresMonitorItemCodeEdit::CalcBreakpointPosition(INT nLine) CONST
{
	INT  nPos;

	return(((nPos = (nLine > 0) ? LineIndex(nLine - 1) : -1) >= 0) ? CRect(CalcBreakpointIndent(), PosFromChar(nPos).y + (m_sizeCodeFont.cy - 2 * CalcBreakpointRadius()) / 2, CalcBreakpointIndent() + 2 * CalcBreakpointRadius(), PosFromChar(nPos).y + (m_sizeCodeFont.cy - 2 * CalcBreakpointRadius()) / 2 + 2 * CalcBreakpointRadius()) : CRect(0, 0, 0, 0));
}

INT CTCProceduresMonitorItemCodeEdit::CalcBreakpointRadius() CONST
{
	return min(CalcMargin().Width() - 2 * CalcBreakpointIndent(), m_sizeCodeFont.cy) / 2;
}

INT CTCProceduresMonitorItemCodeEdit::CalcBreakpointIndent() CONST
{
	return GetSystemMetrics(SM_CXEDGE);
}

CRect CTCProceduresMonitorItemCodeEdit::CalcExecutionpointPosition(INT nLine) CONST
{
	INT  nPos;

	return(((nPos = (nLine > 0) ? LineIndex(nLine - 1) : -1) >= 0) ? CRect(CalcExecutionpointIndent(), PosFromChar(nPos).y + (m_sizeCodeFont.cy - CalcExecutionpointExtent()) / 2, CalcExecutionpointIndent() + CalcExecutionpointExtent(), PosFromChar(nPos).y + (m_sizeCodeFont.cy - CalcExecutionpointExtent()) / 2 + CalcExecutionpointExtent()) : CRect(0, 0, 0, 0));
}

INT CTCProceduresMonitorItemCodeEdit::CalcExecutionpointExtent() CONST
{
	INT  nExtent;

	return(((nExtent = min(CalcMargin().Width() - 2 * CalcExecutionpointIndent(), m_sizeCodeFont.cy)) % 2) ? (nExtent - 1) : nExtent);
}

INT CTCProceduresMonitorItemCodeEdit::CalcExecutionpointIndent() CONST
{
	return GetSystemMetrics(SM_CXEDGE);
}

CRect CTCProceduresMonitorItemCodeEdit::CalcMargin() CONST
{
	CRect  rMargin;

	GetClientRect(rMargin);
	rMargin.right = rMargin.left + GetSystemMetrics(SM_CXVSCROLL);
	return rMargin;
}

DWORD CALLBACK CTCProceduresMonitorItemCodeEdit::SetCodeCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	LONG  cbCode;
	CByteArray  *pCode = (CByteArray *)dwCookie;
	static LONG  nCode = 0;

	CopyMemory(pbBuff, pCode->GetData() + nCode, (cbCode = (LONG)max(min(pCode->GetSize() - nCode, cb), 0)));
	CopyMemory(pcb, &cbCode, sizeof(LONG));
	nCode = (nCode + cbCode < pCode->GetSize()) ? (nCode + cbCode) : 0;
	return 0;
}

DWORD CALLBACK CTCProceduresMonitorItemCodeEdit::GetCodeCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	LONG  cbCode;
	CByteArray  *pCode = (CByteArray *)dwCookie;

	pCode->SetSize((cbCode = (LONG)pCode->GetSize()) + cb);
	CopyMemory(pCode->GetData() + cbCode, pbBuff, cb);
	CopyMemory(pcb, &cb, sizeof(LONG));
	return 0;
}

BOOL CTCProceduresMonitorItemCodeEdit::Lock()
{
	CTCProceduresMonitorWnd  *pParentWnd;

	return(((pParentWnd = GetParentDisplay())) ? (pParentWnd->Lock() && GetLock()->Lock()) : GetLock()->Lock());
}

BOOL CTCProceduresMonitorItemCodeEdit::Unlock()
{
	CTCProceduresMonitorWnd  *pParentWnd;

	return(((pParentWnd = GetParentDisplay())) ? (GetLock()->Unlock() && pParentWnd->Unlock()) : GetLock()->Unlock());
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorItemCodeEdit, CTPLCodeEdit)
	//{{AFX_MSG_MAP(CTCProceduresMonitorItemCodeEdit)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_SETFOCUS()
	ON_CONTROL_REFLECT(EN_CHANGE, OnEditchangeCode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemCodeEdit message handlers

int CTCProceduresMonitorItemCodeEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CRect  rEdit;
	CFontTools  cFontTools;

	if (CTPLCodeEdit::OnCreate(lpCreateStruct) != -1)
	{
		for (GetRect(rEdit); rEdit.Width() >= 0 || rEdit.Height() >= 0; )
		{
			rEdit.DeflateRect(CalcMargin().Width() + rEdit.left, 0, 0, 0);
			SetRect(rEdit);
			break;
		}
		SetFont(&m_cCodeFont);
		return 0;
	}
	return -1;
}

BOOL CTCProceduresMonitorItemCodeEdit::OnEraseBkgnd(CDC *pDC)
{
	CRect  rMargin;

	DrawMargin(pDC);
	pDC->DrawEdge((rMargin = CalcMargin()), EDGE_ETCHED, BF_RIGHT | BF_ADJUST);
	pDC->ExcludeClipRect(rMargin.left, rMargin.top, rMargin.right + 1, rMargin.bottom);
	return CTPLCodeEdit::OnEraseBkgnd(pDC);
}

void CTCProceduresMonitorItemCodeEdit::OnPaint()
{
	CDC  *pDC;
	CRect  rMargin;

	if ((pDC = GetDC()))
	{
		DrawMargin(pDC);
		ReleaseDC(pDC);
		pDC->DrawEdge((rMargin = CalcMargin()), EDGE_ETCHED, BF_RIGHT | BF_ADJUST);
		ValidateRect(CRect(rMargin.left, rMargin.top, rMargin.right + 1, rMargin.bottom));
	}
	CTPLCodeEdit::OnPaint();
}

BOOL CTCProceduresMonitorItemCodeEdit::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	POINT  ptCursor;

	if (nHitTest == HTCLIENT)
	{
		for (GetCursorPos(&ptCursor), ScreenToClient(&ptCursor); !CalcMargin().PtInRect(ptCursor); )
		{
			SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
			return TRUE;
		}
	}
	return CTPLCodeEdit::OnSetCursor(pWnd, nHitTest, message);
}

void CTCProceduresMonitorItemCodeEdit::OnMouseMove(UINT nFlags, CPoint point)
{
	INT  nBreakpoint;
	INT  nBreakpoints;
	CString  szToolTipTitle;
	CString  szToolTipText;
	CDatabaseTCProcedureThreadBreakpoint  *pBreakpoint;

	for (nBreakpoint = 0, nBreakpoints = (m_bToolTips) ? (INT)m_pBreakpoints.GetSize() : -1; nBreakpoint < nBreakpoints; nBreakpoint++)
	{
		if ((pBreakpoint = m_pBreakpoints.GetAt(nBreakpoint)) && pBreakpoint->GetLine() > 0 && CalcBreakpointPosition(pBreakpoint->GetLine()).PtInRect(point))
		{
			for (szToolTipTitle.Format(STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_BREAKPOINTLINETITLE), pBreakpoint->GetLine()), szToolTipText = STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_BREAKPOINTBREAKALWAYS), szToolTipText += (pBreakpoint->GetOptions() & TCPROCEDURETHREADBREAKPOINT_OPTION_DISABLED) ? (CString(EOL) + STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_BREAKPOINTDISABLED)) : (CString(EOL) + STRING(IDS_TCPROCEDURESMONITOR_TOOLTIP_BREAKPOINTENABLED)); IsWindow(m_wndToolTip.GetSafeHwnd()) && m_szToolTip != szToolTipTitle; )
			{
				m_wndToolTip.Destroy();
				m_szToolTip.Empty();
				break;
			}
			if (!IsWindow(m_wndToolTip.GetSafeHwnd()) && m_szToolTip != szToolTipTitle && (nFlags & MK_RBUTTON) != MK_RBUTTON)
			{
				m_wndToolTip.Create(this, point, (m_szToolTip = szToolTipTitle), szToolTipText, TRUE);
				break;
			}
			break;
		}
	}
	if (nBreakpoint == nBreakpoints)
	{
		m_wndToolTip.Destroy();
		m_szToolTip.Empty();
	}
	CTPLCodeEdit::OnMouseMove(nFlags, point);
}

void CTCProceduresMonitorItemCodeEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	INT  nIndex;
	INT  nBreakpoint;
	INT  nBreakpoints;
	CRect  rBreakpoint;
	CString  szBreakpoint;
	CDatabaseTCProcedureThreadBreakpoint  *pBreakpoint;

	for (nBreakpoint = 0, nBreakpoints = (CalcMargin().PtInRect(point) && m_bBreaks) ? (INT)m_pBreakpoints.GetSize() : -1; nBreakpoint < nBreakpoints; nBreakpoint++)
	{
		if ((pBreakpoint = m_pBreakpoints.GetAt(nBreakpoint)) && pBreakpoint->GetLine() > 0)
		{
			rBreakpoint = CalcBreakpointPosition(pBreakpoint->GetLine());
			if ((point.x - rBreakpoint.CenterPoint().x)*(point.x - rBreakpoint.CenterPoint().x) + (point.y - rBreakpoint.CenterPoint().y)*(point.y - rBreakpoint.CenterPoint().y) <= (rBreakpoint.Width()*rBreakpoint.Width()) / 4)
			{
				m_szBreakpoints.RemoveAt(nBreakpoint);
				m_pBreakpoints.RemoveAt(nBreakpoint);
				delete pBreakpoint;
				nBreakpoints--;
				nBreakpoint--;
				break;
			}
		}
	}
	for (; GetLineCount() > 0 && nBreakpoint == nBreakpoints; )
	{
		if ((pBreakpoint = new CDatabaseTCProcedureThreadBreakpoint))
		{
			pBreakpoint->SetLine(LineFromChar(CharFromPos(point)) + 1);
			pBreakpoint->SetOptions(TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKALWAYS);
			if ((nIndex = (lstrlen((szBreakpoint = CheckLine(pBreakpoint->GetLine() - 1))) > 0) ? m_pBreakpoints.Add(pBreakpoint) : -1) >= 0)
			{
				m_szBreakpoints.SetAtGrow(nIndex, szBreakpoint);
				break;
			}
			delete pBreakpoint;
		}
		nBreakpoints = -1;
		break;
	}
	for (; IsWindow(m_wndToolTip.GetSafeHwnd()) && nBreakpoint < nBreakpoints; )
	{
		m_wndToolTip.Destroy();
		break;
	}
	if (nBreakpoints >= 0 || nBreakpoints == -1)
	{
		UpdateBreakpoints();
		DrawMargin();
		return;
	}
	CTPLCodeEdit::OnLButtonDown(nFlags, point);
}

void CTCProceduresMonitorItemCodeEdit::OnRButtonDown(UINT nFlags, CPoint point)
{
	INT  nItem;
	INT  nItems;
	INT  nItemID;
	INT  nBreakpoint;
	INT  nBreakpoints;
	CPoint  ptBreakpointMenu;
	CString  szBreakpointMenuItem;
	CLocaleMenu  cBreakpointMenu[2];
	CDatabaseTCProcedureThreadBreakpoint  *pBreakpoint;

	for (nBreakpoint = 0, nBreakpoints = (INT)m_pBreakpoints.GetSize(), ptBreakpointMenu = point, ClientToScreen(&ptBreakpointMenu); nBreakpoint < nBreakpoints; nBreakpoint++)
	{
		if ((pBreakpoint = m_pBreakpoints.GetAt(nBreakpoint)) && pBreakpoint->GetLine() > 0 && CalcBreakpointPosition(pBreakpoint->GetLine()).PtInRect(point))
		{
			for (nItem = 0, nItems = (cBreakpointMenu[0].CreatePopupMenu() && cBreakpointMenu[1].LoadMenu(IDR_TCPROCEDURESMONITORFLOATINGMENU)) ? cBreakpointMenu[1].GetMenuItemCount() : 0, m_wndToolTip.Destroy(); nItem < nItems; nItem++)
			{
				if ((nItemID = cBreakpointMenu[1].GetMenuItemID(nItem)) >= 0 && (!nItemID || cBreakpointMenu[1].GetMenuString(nItem, szBreakpointMenuItem, MF_BYPOSITION) > 0))
				{
					if ((!nItemID  &&  cBreakpointMenu[0].GetMenuItemCount() == 1) || nItemID == IDM_TCPROCEDURESMONITORBREAKALWAYS || nItemID == IDM_TCPROCEDURESMONITORDISABLEBREAKPOINT)
					{
						cBreakpointMenu[0].AppendMenu(((nItemID > 0) ? MF_STRING : MF_SEPARATOR) | MF_ENABLED, (UINT_PTR)nItemID, szBreakpointMenuItem);
						cBreakpointMenu[0].CheckMenuItem(nItemID, (((pBreakpoint->GetOptions() & TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKALWAYS) && nItemID == IDM_TCPROCEDURESMONITORBREAKALWAYS)) ? (MF_CHECKED | MF_BYCOMMAND) : ((cBreakpointMenu[0].GetMenuState(nItemID, MF_BYCOMMAND) & MF_CHECKED) | MF_BYCOMMAND));
						cBreakpointMenu[0].CheckMenuItem(nItemID, (((pBreakpoint->GetOptions() & TCPROCEDURETHREADBREAKPOINT_OPTION_DISABLED) && nItemID == IDM_TCPROCEDURESMONITORDISABLEBREAKPOINT)) ? (MF_CHECKED | MF_BYCOMMAND) : ((cBreakpointMenu[0].GetMenuState(nItemID, MF_BYCOMMAND) & MF_CHECKED) | MF_BYCOMMAND));
					}
				}
			}
			if (nItems > 0)
			{
				if ((nItemID = cBreakpointMenu[0].TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD, ptBreakpointMenu.x, ptBreakpointMenu.y, GetParentDisplay())) == IDM_TCPROCEDURESMONITORBREAKALWAYS)
				{
					pBreakpoint->SetOptions((pBreakpoint->GetOptions() & ~(TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDTRIGGER | TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDBODY | TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDCONFIRMATION)) | TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKALWAYS);
					UpdateBreakpoints();
					DrawMargin();
				}
				if (nItemID == IDM_TCPROCEDURESMONITORDISABLEBREAKPOINT)
				{
					pBreakpoint->SetOptions(pBreakpoint->GetOptions() ^ TCPROCEDURETHREADBREAKPOINT_OPTION_DISABLED);
					UpdateBreakpoints();
					DrawMargin();
				}
				cBreakpointMenu[1].DestroyMenu();
			}
			break;
		}
	}
	CTPLCodeEdit::OnRButtonDown(nFlags, point);
}

void CTCProceduresMonitorItemCodeEdit::OnSetFocus(CWnd *pOldWnd)
{
	return;
}

void CTCProceduresMonitorItemCodeEdit::OnEditchangeCode()
{
	if (Lock())
	{
		m_nExecutionThreadIDs.RemoveAll();
		m_nExecutionStates.RemoveAll();
		m_nExecutionLines.RemoveAll();
		Unlock();
	}
	CTPLCodeEdit::RenderCode(this, &m_cCodeFont);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemCodeView

IMPLEMENT_DYNCREATE(CTCProceduresMonitorItemCodeView, CView)

CTCProceduresMonitorItemCodeView::CTCProceduresMonitorItemCodeView() : CView()
{
	m_bBreaks = TRUE;
	m_sizeTrackLayout.cx = 0;
	m_sizeTrackLayout.cy = 0;
	m_pwndCode = new CTCProceduresMonitorItemCodeEdit;
	m_pParentWnd = (CWnd *)NULL;
}

CTCProceduresMonitorItemCodeView::~CTCProceduresMonitorItemCodeView()
{
	delete m_pwndCode;
}

BOOL CTCProceduresMonitorItemCodeView::SetFont(CFont *pFont)
{
	return m_pwndCode->SetFont(pFont);
}
BOOL CTCProceduresMonitorItemCodeView::SetFont(CONST LOGFONT *plfFont)
{
	CFont  cFont;

	return(cFont.CreateFontIndirect(plfFont) && SetFont(&cFont));
}

BOOL CTCProceduresMonitorItemCodeView::GetFont(CFont *pFont) CONST
{
	return m_pwndCode->GetFont(pFont);
}
BOOL CTCProceduresMonitorItemCodeView::GetFont(LOGFONT *plfFont) CONST
{
	CFont  cFont;

	return(GetFont(&cFont) && cFont.GetLogFont(plfFont) > 0);
}

BOOL CTCProceduresMonitorItemCodeView::AllowExecutionBreaks(BOOL bAllow)
{
	CDisplayLock  cLock((CDisplayLockable *)m_pwndCode);

	m_pwndCode->AllowExecutionBreaks((m_bBreaks = bAllow));
	return TRUE;
}

BOOL CTCProceduresMonitorItemCodeView::AreExecutionBreaksAllowed() CONST
{
	return m_bBreaks;
}

BOOL CTCProceduresMonitorItemCodeView::EnableToolTipMode(BOOL bEnable)
{
	CDisplayLock  cLock((CDisplayLockable *)m_pwndCode);

	m_pwndCode->EnableToolTipMode((m_bToolTips = bEnable));
	return TRUE;
}

BOOL CTCProceduresMonitorItemCodeView::IsToolTipModeEnabled() CONST
{
	return m_bToolTips;
}

BOOL CTCProceduresMonitorItemCodeView::UpdateBreakpoints(LPCTSTR pszThread, CONST CDatabaseTCProcedureThreadBreakpoints &pBreakpoints)
{
	INT  nIndex;
	INT  nThread;
	INT  nThreads;
	INT  nBreakpoint;
	INT  nBreakpoints;
	CTCProceduresMonitorItem  cProcedure;
	CDatabaseTCProcedureThread  *pThread;
	CDatabaseTCProcedureThreadBreakpoint  *pBreakpoint[2];
	CDatabaseTCProcedureThreadBreakpoints  pThreadBreakpoints;
	CDisplayLock  cLock((CDisplayLockable *)m_pwndCode);

	for (nThread = 0, nThreads = (GetParentDisplay()->GetProcedureInfo((nIndex = GetParentDisplay()->GetCurProcedure()), &cProcedure, FALSE)) ? (INT)cProcedure.GetSize() : -1; nThread < nThreads; nThread++)
	{
		if ((pThread = cProcedure.GetAt(nThread)) && (pThread->GetName() == pszThread || !lstrlen(pszThread)))
		{
			for (nBreakpoint = 0, nBreakpoints = pThread->GetBreakpoints(pThreadBreakpoints); nBreakpoint < nBreakpoints; nBreakpoint++)
			{
				if ((pBreakpoint[0] = pThreadBreakpoints.GetAt(nBreakpoint)) && pBreakpoint[0]->GetLine() > 0)
				{
					pThreadBreakpoints.RemoveAt(nBreakpoint);
					delete pBreakpoint[0];
					nBreakpoints--;
					nBreakpoint--;
				}
			}
			for (nBreakpoint = 0, nBreakpoints = (INT)pBreakpoints.GetSize(); nBreakpoint < nBreakpoints; nBreakpoint++)
			{
				if ((pBreakpoint[0] = pBreakpoints.GetAt(nBreakpoint)) && pBreakpoint[0]->GetLine() > 0)
				{
					if ((pBreakpoint[1] = new CDatabaseTCProcedureThreadBreakpoint))
					{
						pBreakpoint[1]->Copy(pBreakpoint[0]);
						if (pThreadBreakpoints.Add(pBreakpoint[1]) >= 0) continue;
						delete pBreakpoint[1];
					}
				}
			}
			pThread->SetBreakpoints(pThreadBreakpoints);
		}
	}
	return((nThread == nThreads) ? GetParentDisplay()->SetProcedureInfo(nIndex, &cProcedure, FALSE) : FALSE);
}

BOOL CTCProceduresMonitorItemCodeView::UpdateContent()
{
	INT  nIndex;
	INT  nThread;
	INT  nThreads;
	INT  nBreakpoint;
	INT  nBreakpoints;
	CByteArray  nCode;
	CStringArray  szBreakpoints;
	CTCProceduresMonitorItem  cProcedure;
	CDatabaseTCProcedureThread  *pThread;
	CDatabaseTCProcedureThreadBreakpoint  *pBreakpoint;
	CDatabaseTCProcedureThreadBreakpoints  pBreakpoints[2];
	CDisplayLock  cLock((CDisplayLockable *)m_pwndCode);

	if (GetParentDisplay()->GetProcedureInfo((nIndex = GetParentDisplay()->GetCurProcedure()), &cProcedure))
	{
		for (nThread = 0, nThreads = (cProcedure.AreExecutionBreaksAllowed()) ? (INT)cProcedure.GetSize() : 0, AllowExecutionBreaks(cProcedure.AreExecutionBreaksAllowed()); nThread < nThreads; nThread++)
		{
			if ((pThread = cProcedure.GetAt(nThread)) && pThread->GetBreakpoints(pBreakpoints[0]) > 0)
			{
				for (nBreakpoint = 0, nBreakpoints = (INT)pBreakpoints[0].GetSize(); nBreakpoint < nBreakpoints; nBreakpoint++)
				{
					if ((pBreakpoint = pBreakpoints[0].GetAt(nBreakpoint)) && pBreakpoint->GetLine() > 0)
					{
						szBreakpoints.Add(pThread->GetName());
						pBreakpoints[1].Add(pBreakpoint);
						pBreakpoints[0].RemoveAt(nBreakpoint);
						nBreakpoints--;
						nBreakpoint--;
					}
				}
			}
		}
		if (!cProcedure.GetSourceCode(nCode))
		{
			for (m_pwndCode->SetSourceCode(cProcedure.GetSourceCode()); m_pwndCode->GetSourceCode(nCode); )
			{
				cProcedure.SetSourceCode(nCode);
				GetParentDisplay()->SetProcedureInfo(nIndex, &cProcedure);
				break;
			}
			m_pwndCode->SetBreakpoints(szBreakpoints, pBreakpoints[1]);
			return TRUE;
		}
		m_pwndCode->SetSourceCode(nCode);
		m_pwndCode->SetBreakpoints(szBreakpoints, pBreakpoints[1]);
		return TRUE;
	}
	if (nIndex < 0)
	{
		m_pwndCode->SetSourceCode(EMPTYSTRING);
		return TRUE;
	}
	return FALSE;
}
BOOL CTCProceduresMonitorItemCodeView::UpdateContent(INT nThreadID, UINT nState, UINT nLine)
{
	CDisplayLock  cLock((CDisplayLockable *)m_pwndCode);

	m_pwndCode->UpdateExecutionpoint(nThreadID, nState, nLine);
	return TRUE;
}

VOID CTCProceduresMonitorItemCodeView::SetTrackSize(CONST SIZE &size)
{
	CDisplayLock  cLock((CDisplayLockable *)m_pwndCode);

	m_sizeTrackLayout = size;
}

CSize CTCProceduresMonitorItemCodeView::GetTrackSize() CONST
{
	CDisplayLock  cLock((CDisplayLockable *)m_pwndCode);

	return m_sizeTrackLayout;
}

CTCProceduresMonitorItemContents *CTCProceduresMonitorItemCodeView::GetParent() CONST
{
	return((CTCProceduresMonitorItemContents *)m_pParentWnd);
}

CTCProceduresMonitorWnd *CTCProceduresMonitorItemCodeView::GetParentDisplay() CONST
{
	CTCProceduresMonitorItemContents  *pContents;

	return(((pContents = GetParent())) ? pContents->GetParent()->GetParent()->GetParent() : (CTCProceduresMonitorWnd *)NULL);
}

CRect CTCProceduresMonitorItemCodeView::CalcCodePosition() CONST
{
	CRect  rView;

	GetClientRect(rView);
	return CalcCodePosition(rView.Width(), rView.Height());
}
CRect CTCProceduresMonitorItemCodeView::CalcCodePosition(INT cx, INT cy) CONST
{
	return CRect(-GetSystemMetrics(SM_CXEDGE), -GetSystemMetrics(SM_CYEDGE), cx + GetSystemMetrics(SM_CXEDGE), cy + GetSystemMetrics(SM_CYEDGE));
}

BOOL CTCProceduresMonitorItemCodeView::Lock()
{
	return m_pwndCode->Lock();
}

BOOL CTCProceduresMonitorItemCodeView::Unlock()
{
	return m_pwndCode->Unlock();
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorItemCodeView, CView)
	//{{AFX_MSG_MAP(CTCProceduresMonitorItemCodeView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemCodeView drawing

void CTCProceduresMonitorItemCodeView::OnDraw(CDC *pDC)
{
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemCodeView message handlers

int CTCProceduresMonitorItemCodeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CView::OnCreate(lpCreateStruct) != -1 && m_pwndCode->Create(this, ((m_pParentWnd = CView::GetParent())) ? CalcCodePosition(lpCreateStruct->cx, lpCreateStruct->cy) : CRect(0, 0, 0, 0))) ? 0 : -1);
}

void CTCProceduresMonitorItemCodeView::OnSize(UINT nType, int cx, int cy)
{
	m_pwndCode->MoveWindow(CalcCodePosition(cx, cy));
	CView::OnSize(nType, cx, cy);
}

BOOL CTCProceduresMonitorItemCodeView::OnEraseBkgnd(CDC *pDC)
{
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemContents

IMPLEMENT_DYNCREATE(CTCProceduresMonitorItemContents, CSplitterWndEx)

CTCProceduresMonitorItemContents::CTCProceduresMonitorItemContents() : CSplitterWndEx()
{
	m_sizeCodePane.cx = 0;
	m_sizeCodePane.cy = 0;
	m_sizeFlowchartPane.cx = 0;
	m_sizeFlowchartPane.cy = 0;
	m_pFlowchartView = (CTCProceduresMonitorItemFlowchartView *)NULL;
	m_pCodeView = (CTCProceduresMonitorItemCodeView *)NULL;
	m_pParentWnd = (CWnd *)NULL;
	m_bTracking = TRUE;
}

BOOL CTCProceduresMonitorItemContents::Create(CWnd *pParentWnd)
{
	CRect  rPanes;
	CCreateContext  cContext;

	if (CreateStatic((m_pParentWnd = pParentWnd), 1, 2))
	{
		for (pParentWnd->GetClientRect(rPanes), cContext.m_pCurrentDoc = new CTCProceduresMonitorDocument; CreateView(0, 0, RUNTIME_CLASS(CTCProceduresMonitorItemFlowchartView), CSize(rPanes.Width() / 2, rPanes.Height()), &cContext) && CreateView(0, 1, RUNTIME_CLASS(CTCProceduresMonitorItemCodeView), CSize(rPanes.Width() / 2, rPanes.Height()), &cContext); )
		{
			for (m_pFlowchartView = (CTCProceduresMonitorItemFlowchartView *)GetPane(0, 0), m_pCodeView = (CTCProceduresMonitorItemCodeView *)GetPane(0, 1); TRUE; ) return TRUE;
			break;
		}
	}
	return FALSE;
}

BOOL CTCProceduresMonitorItemContents::SetLayout(CONST SIZE &sizeFlowchartPane, CONST SIZE &sizeCodePane)
{
	INT  nPaneWidth[2][2];

	GetColumnInfo(0, nPaneWidth[0][0], nPaneWidth[0][1]);
	GetColumnInfo(1, nPaneWidth[1][0], nPaneWidth[1][1]);
	SetColumnInfo(0, max(sizeFlowchartPane.cx, 0), max(nPaneWidth[0][1], 0));
	SetColumnInfo(1, max(sizeCodePane.cx, 0), max(nPaneWidth[1][1], 0));
	if (sizeFlowchartPane.cx > 0 && sizeCodePane.cx > 0)
	{
		m_sizeFlowchartPane = sizeFlowchartPane;
		m_sizeCodePane = sizeCodePane;
	}
	RecalcLayout();
	return TRUE;
}

BOOL CTCProceduresMonitorItemContents::GetLayout(CSize &sizeFlowchartPane, CSize &sizeCodePane) CONST
{
	INT  nPaneWidth[2][2];
	INT  nPaneHeight[2];

	GetRowInfo(0, nPaneHeight[0], nPaneHeight[1]);
	GetColumnInfo(0, nPaneWidth[0][0], nPaneWidth[0][1]);
	GetColumnInfo(1, nPaneWidth[1][0], nPaneWidth[1][1]);
	sizeFlowchartPane.cx = (!nPaneWidth[0][0] && !nPaneWidth[1][0]) ? m_sizeFlowchartPane.cx : nPaneWidth[0][0];
	sizeFlowchartPane.cy = (!nPaneHeight[0]) ? m_sizeFlowchartPane.cy : nPaneHeight[0];
	sizeCodePane.cx = (!nPaneWidth[0][0] && !nPaneWidth[1][0]) ? m_sizeCodePane.cx : nPaneWidth[1][0];
	sizeCodePane.cy = (!nPaneHeight[0]) ? m_sizeCodePane.cy : nPaneHeight[0];
	return TRUE;
}

BOOL CTCProceduresMonitorItemContents::SetFlowcharts(CONST CTCProceduresMonitorItem *pItem)
{
	return GetFlowchartView()->SetFlowcharts(pItem);
}

BOOL CTCProceduresMonitorItemContents::GetFlowcharts(CTCProceduresMonitorItem *pItem) CONST
{
	return GetFlowchartView()->GetFlowcharts(pItem);
}

BOOL CTCProceduresMonitorItemContents::SetFlowchartTitleFont(CFont *pFont)
{
	return GetFlowchartView()->SetTitleFont(pFont);
}
BOOL CTCProceduresMonitorItemContents::SetFlowchartTitleFont(CONST LOGFONT *plfFont)
{
	return GetFlowchartView()->SetTitleFont(plfFont);
}

BOOL CTCProceduresMonitorItemContents::GetFlowchartTitleFont(CFont *pFont) CONST
{
	return GetFlowchartView()->GetTitleFont(pFont);
}
BOOL CTCProceduresMonitorItemContents::GetFlowchartTitleFont(LOGFONT *plfFont) CONST
{
	return GetFlowchartView()->GetTitleFont(plfFont);
}

BOOL CTCProceduresMonitorItemContents::SetFlowchartLabelsFont(CFont *pFont)
{
	return GetFlowchartView()->SetLabelsFont(pFont);
}
BOOL CTCProceduresMonitorItemContents::SetFlowchartLabelsFont(CONST LOGFONT *plfFont)
{
	return GetFlowchartView()->SetLabelsFont(plfFont);
}

BOOL CTCProceduresMonitorItemContents::GetFlowchartLabelsFont(CFont *pFont) CONST
{
	return GetFlowchartView()->GetLabelsFont(pFont);
}
BOOL CTCProceduresMonitorItemContents::GetFlowchartLabelsFont(LOGFONT *plfFont) CONST
{
	return GetFlowchartView()->GetLabelsFont(plfFont);
}

BOOL CTCProceduresMonitorItemContents::SetFlowchartLabelsColor(COLORREF nColor)
{
	return GetFlowchartView()->SetLabelsColor(nColor);
}

BOOL CTCProceduresMonitorItemContents::GetFlowchartLabelsColor(COLORREF &nColor) CONST
{
	return GetFlowchartView()->GetLabelsColor(nColor);
}

BOOL CTCProceduresMonitorItemContents::SetFlowchartBackgroundColor(COLORREF nColor)
{
	return GetFlowchartView()->SetBackgroundColor(nColor);
}

BOOL CTCProceduresMonitorItemContents::GetFlowchartBackgroundColor(COLORREF &nColor) CONST
{
	return GetFlowchartView()->GetBackgroundColor(nColor);
}

BOOL CTCProceduresMonitorItemContents::SetSourceCodeFont(CFont *pFont)
{
	return GetCodeView()->SetFont(pFont);
}
BOOL CTCProceduresMonitorItemContents::SetSourceCodeFont(CONST LOGFONT *plfFont)
{
	return GetCodeView()->SetFont(plfFont);
}

BOOL CTCProceduresMonitorItemContents::GetSourceCodeFont(CFont *pFont) CONST
{
	return GetCodeView()->GetFont(pFont);
}
BOOL CTCProceduresMonitorItemContents::GetSourceCodeFont(LOGFONT *plfFont) CONST
{
	return GetCodeView()->GetFont(plfFont);
}

BOOL CTCProceduresMonitorItemContents::EnableToolTipMode(BOOL bEnable)
{
	return GetFlowchartView()->EnableToolTipMode(bEnable) && GetCodeView()->EnableToolTipMode(bEnable);
}

BOOL CTCProceduresMonitorItemContents::IsToolTipModeEnabled() CONST
{
	return GetFlowchartView()->IsToolTipModeEnabled() || GetCodeView()->IsToolTipModeEnabled();
}

BOOL CTCProceduresMonitorItemContents::SetSelectedThreadID(INT nThreadID)
{
	return GetFlowchartView()->SetSelectedThreadID(nThreadID);
}

INT CTCProceduresMonitorItemContents::GetSelectedThreadID() CONST
{
	return GetFlowchartView()->GetSelectedThreadID();
}

BOOL CTCProceduresMonitorItemContents::SetLayoutInfo(INT nThreadID)
{
	return GetFlowchartView()->SetLayoutInfo(nThreadID);
}

BOOL CTCProceduresMonitorItemContents::GetLayoutInfo(INT &nThreadID) CONST
{
	return GetFlowchartView()->GetLayoutInfo(nThreadID);
}

BOOL CTCProceduresMonitorItemContents::GetPrintProperties(CStringArray &szThreads, CPtrArray &pThreadMetaDCs) CONST
{
	return GetFlowchartView()->GetPrintProperties(szThreads, pThreadMetaDCs);
}

BOOL CTCProceduresMonitorItemContents::UpdateContents()
{
	CSize  sizePane[2];

	if (GetFlowchartView()->UpdateContents() + GetCodeView()->UpdateContent() > TRUE)
	{
		for (GetLayout(sizePane[0], sizePane[1]); GetParent()->GetParent()->GetCurProcedure() >= 0; )
		{
			for (m_bTracking = GetFlowchartView()->HasContents(); !m_bTracking && sizePane[0].cx > 0; )
			{
				m_sizeFlowchartPane = sizePane[0];
				m_sizeCodePane.cx = sizePane[1].cx;
				m_sizeCodePane.cy = sizePane[1].cy;
				sizePane[1].cx += sizePane[0].cx;
				sizePane[0].cx -= sizePane[0].cx;
				SetLayout(sizePane[0], sizePane[1]);
				break;
			}
			for (; m_bTracking && m_sizeFlowchartPane.cx > 0 && m_sizeCodePane.cx > 0 && !sizePane[0].cx; )
			{
				SetLayout(m_sizeFlowchartPane, m_sizeCodePane);
				break;
			}
			break;
		}
		return TRUE;
	}
	return FALSE;
}
BOOL CTCProceduresMonitorItemContents::UpdateContents(INT nThreadID, UINT nState, CONST CStringArray &szSteps, CONST CUIntArray &nStates, UINT nLine)
{
	return((GetFlowchartView()->UpdateContents(nThreadID, nState, szSteps, nStates) + GetCodeView()->UpdateContent(nThreadID, nState, nLine) > TRUE) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorItemContents::SetTrackSize(CONST SIZE &size)
{
	GetFlowchartView()->SetTrackSize(size);
	GetCodeView()->SetTrackSize(size);
}

CSize CTCProceduresMonitorItemContents::GetTrackSize() CONST
{
	return CSize(GetFlowchartView()->GetTrackSize().cx + GetCodeView()->GetTrackSize().cx, max(GetFlowchartView()->GetTrackSize().cy, GetCodeView()->GetTrackSize().cy));
}

CTCProceduresMonitorItemFlowchartView *CTCProceduresMonitorItemContents::GetFlowchartView() CONST
{
	return m_pFlowchartView;
}

CTCProceduresMonitorItemCodeView *CTCProceduresMonitorItemContents::GetCodeView() CONST
{
	return m_pCodeView;
}

CTCProceduresMonitorItemView *CTCProceduresMonitorItemContents::GetParent() CONST
{
	return((CTCProceduresMonitorItemView *)m_pParentWnd);
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorItemContents, CSplitterWndEx)
	//{{AFX_MSG_MAP(CTCProceduresMonitorItemContents)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemContents message handlers

void CTCProceduresMonitorItemContents::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bTracking) return;
	CSplitterWndEx::OnMouseMove(nFlags, point);
}

void CTCProceduresMonitorItemContents::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!m_bTracking) return;
	CSplitterWndEx::OnLButtonDown(nFlags, point);
}

void CTCProceduresMonitorItemContents::OnSetFocus(CWnd *pOldWnd)
{
	if (IsWindow(pOldWnd->GetSafeHwnd()))
	{
		if (pOldWnd == GetParent())
		{
			GetFlowchartView()->SetFocus();
			return;
		}
		if (pOldWnd == (CWnd *)GetFlowchartView())
		{
			GetParent()->SetFocus();
			return;
		}
	}
	CSplitterWndEx::OnSetFocus(pOldWnd);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemView

IMPLEMENT_DYNCREATE(CTCProceduresMonitorItemView, CView)

CTCProceduresMonitorItemView::CTCProceduresMonitorItemView() : CView()
{
	m_pParentWnd = (CWnd *)NULL;
}

BOOL CTCProceduresMonitorItemView::SetLayout(CONST SIZE &sizeFlowchartPane, CONST SIZE &sizeCodePane)
{
	return m_wndContents.SetLayout(sizeFlowchartPane, sizeCodePane);
}

BOOL CTCProceduresMonitorItemView::GetLayout(CSize &sizeFlowchartPane, CSize &sizeCodePane) CONST
{
	return m_wndContents.GetLayout(sizeFlowchartPane, sizeCodePane);
}

BOOL CTCProceduresMonitorItemView::SetFlowcharts(CONST CTCProceduresMonitorItem *pItem)
{
	return m_wndContents.SetFlowcharts(pItem);
}

BOOL CTCProceduresMonitorItemView::GetFlowcharts(CTCProceduresMonitorItem *pItem) CONST
{
	return m_wndContents.GetFlowcharts(pItem);
}

BOOL CTCProceduresMonitorItemView::SetFlowchartTitleFont(CFont *pFont)
{
	return m_wndContents.SetFlowchartTitleFont(pFont);
}
BOOL CTCProceduresMonitorItemView::SetFlowchartTitleFont(CONST LOGFONT *plfFont)
{
	return m_wndContents.SetFlowchartTitleFont(plfFont);
}

BOOL CTCProceduresMonitorItemView::GetFlowchartTitleFont(CFont *pFont) CONST
{
	return m_wndContents.GetFlowchartTitleFont(pFont);
}
BOOL CTCProceduresMonitorItemView::GetFlowchartTitleFont(LOGFONT *plfFont) CONST
{
	return m_wndContents.GetFlowchartTitleFont(plfFont);
}

BOOL CTCProceduresMonitorItemView::SetFlowchartLabelsFont(CFont *pFont)
{
	return m_wndContents.SetFlowchartLabelsFont(pFont);
}
BOOL CTCProceduresMonitorItemView::SetFlowchartLabelsFont(CONST LOGFONT *plfFont)
{
	return m_wndContents.SetFlowchartLabelsFont(plfFont);
}

BOOL CTCProceduresMonitorItemView::GetFlowchartLabelsFont(CFont *pFont) CONST
{
	return m_wndContents.GetFlowchartLabelsFont(pFont);
}
BOOL CTCProceduresMonitorItemView::GetFlowchartLabelsFont(LOGFONT *plfFont) CONST
{
	return m_wndContents.GetFlowchartLabelsFont(plfFont);
}

BOOL CTCProceduresMonitorItemView::SetFlowchartLabelsColor(COLORREF nColor)
{
	return m_wndContents.SetFlowchartLabelsColor(nColor);
}

BOOL CTCProceduresMonitorItemView::GetFlowchartLabelsColor(COLORREF &nColor) CONST
{
	return m_wndContents.GetFlowchartLabelsColor(nColor);
}

BOOL CTCProceduresMonitorItemView::SetFlowchartBackgroundColor(COLORREF nColor)
{
	return m_wndContents.SetFlowchartBackgroundColor(nColor);
}

BOOL CTCProceduresMonitorItemView::GetFlowchartBackgroundColor(COLORREF &nColor) CONST
{
	return m_wndContents.GetFlowchartBackgroundColor(nColor);
}

BOOL CTCProceduresMonitorItemView::SetSourceCodeFont(CFont *pFont)
{
	return m_wndContents.SetSourceCodeFont(pFont);
}
BOOL CTCProceduresMonitorItemView::SetSourceCodeFont(CONST LOGFONT *plfFont)
{
	return m_wndContents.SetSourceCodeFont(plfFont);
}

BOOL CTCProceduresMonitorItemView::GetSourceCodeFont(CFont *pFont) CONST
{
	return m_wndContents.GetSourceCodeFont(pFont);
}
BOOL CTCProceduresMonitorItemView::GetSourceCodeFont(LOGFONT *plfFont) CONST
{
	return m_wndContents.GetSourceCodeFont(plfFont);
}

BOOL CTCProceduresMonitorItemView::EnableToolTipMode(BOOL bEnable)
{
	return m_wndContents.EnableToolTipMode(bEnable);
}

BOOL CTCProceduresMonitorItemView::IsToolTipModeEnabled() CONST
{
	return m_wndContents.IsToolTipModeEnabled();
}

BOOL CTCProceduresMonitorItemView::SetSelectedThreadID(INT nThreadID)
{
	return m_wndContents.SetSelectedThreadID(nThreadID);
}

INT CTCProceduresMonitorItemView::GetSelectedThreadID() CONST
{
	return m_wndContents.GetSelectedThreadID();
}

BOOL CTCProceduresMonitorItemView::SetLayoutInfo(INT nThreadID)
{
	return m_wndContents.SetLayoutInfo(nThreadID);
}

BOOL CTCProceduresMonitorItemView::GetLayoutInfo(INT &nThreadID) CONST
{
	return m_wndContents.GetLayoutInfo(nThreadID);
}

BOOL CTCProceduresMonitorItemView::GetPrintProperties(CStringArray &szThreads, CPtrArray &pThreadMetaDCs) CONST
{
	return m_wndContents.GetPrintProperties(szThreads, pThreadMetaDCs);
}

BOOL CTCProceduresMonitorItemView::UpdateContents()
{
	return m_wndContents.UpdateContents();
}
BOOL CTCProceduresMonitorItemView::UpdateContents(INT nThreadID, UINT nState, CONST CStringArray &szSteps, CONST CUIntArray &nStates, UINT nLine)
{
	return m_wndContents.UpdateContents(nThreadID, nState, szSteps, nStates, nLine);
}

VOID CTCProceduresMonitorItemView::SetTrackSize(CONST SIZE &size)
{
	m_wndContents.SetTrackSize(size);
}

CSize CTCProceduresMonitorItemView::GetTrackSize() CONST
{
	return m_wndContents.GetTrackSize();
}

CTCProceduresMonitorView *CTCProceduresMonitorItemView::GetParent() CONST
{
	return((CTCProceduresMonitorView *)m_pParentWnd);
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorItemView, CView)
	//{{AFX_MSG_MAP(CTCProceduresMonitorItemView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemView drawing

void CTCProceduresMonitorItemView::OnDraw(CDC *pDC)
{
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemView message handlers

int CTCProceduresMonitorItemView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) != -1)
	{
		m_pParentWnd = CView::GetParent();
		return((m_wndContents.Create(this)) ? 0 : -1);
	}
	return -1;
}

void CTCProceduresMonitorItemView::OnSize(UINT nType, int cx, int cy)
{
	m_wndContents.MoveWindow(-GetSystemMetrics(SM_CXEDGE), -GetSystemMetrics(SM_CYEDGE), cx + 2 * GetSystemMetrics(SM_CXEDGE), cy + 2 * GetSystemMetrics(SM_CYEDGE));
	CView::OnSize(nType, cx, cy);
}

BOOL CTCProceduresMonitorItemView::OnEraseBkgnd(CDC *pDC)
{
	return TRUE;
}

void CTCProceduresMonitorItemView::OnSetFocus(CWnd *pOldWnd)
{
	if (IsWindow(pOldWnd->GetSafeHwnd()))
	{
		if (pOldWnd == GetParent())
		{
			m_wndContents.SetFocus();
			return;
		}
		if (pOldWnd->GetSafeHwnd() == m_wndContents.GetSafeHwnd())
		{
			GetParent()->SetFocus();
			return;
		}
	}
	CView::OnSetFocus(pOldWnd);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorView

IMPLEMENT_DYNCREATE(CTCProceduresMonitorView, CSplitterWndEx)

CTCProceduresMonitorView::CTCProceduresMonitorView() : CSplitterWndEx()
{
	CFontTools  cFontTools[5] = { &m_lfListTitleFont,&m_lfListItemsFont,&m_lfItemSourceCodeFont,&m_lfItemFlowchartTitleFont,&m_lfItemFlowchartLabelsFont };

	m_bTracking = TRUE;
	m_bToolTips = TRUE;
	m_sizeListPane.cx = 0;
	m_sizeListPane.cy = 0;
	m_sizeCodePane.cx = 0;
	m_sizeCodePane.cy = 0;
	m_sizeFlowchartPane.cx = 0;
	m_sizeFlowchartPane.cy = 0;
	m_nTelecommandingMode = 0;
	m_nTelecommandingFlags = 0;
	m_nTelecommandingState = 0;
	m_nTelecommandingUplinkState = 0;
	m_bTelecommandingReleaseWaitMode = FALSE;
	m_nItemFlowchartColor[0] = GetSysColor(COLOR_WINDOW);
	m_nItemFlowchartColor[1] = GetSysColor(COLOR_WINDOWTEXT);
	m_pListView = (CTCProceduresMonitorListView *)NULL;
	m_pItemView = (CTCProceduresMonitorItemView *)NULL;
	m_pParentWnd = (CWnd *)NULL;
}

BOOL CTCProceduresMonitorView::Create(CWnd *pParentWnd)
{
	CRect  rPanes;
	CSize  sizePanes[2];
	CCreateContext  cContext;

	if (CreateStatic((m_pParentWnd = pParentWnd), 2, 1))
	{
		for (pParentWnd->GetClientRect(rPanes), cContext.m_pCurrentDoc = new CTCProceduresMonitorDocument; CreateView(0, 0, RUNTIME_CLASS(CTCProceduresMonitorListView), (sizePanes[0] = CSize(rPanes.Width(), rPanes.Height() / 2)), &cContext) && CreateView(1, 0, RUNTIME_CLASS(CTCProceduresMonitorItemView), (sizePanes[1] = CSize(rPanes.Width(), rPanes.Height() / 2)), &cContext); )
		{
			for (m_pListView = (CTCProceduresMonitorListView *)GetPane(0, 0), m_pItemView = (CTCProceduresMonitorItemView *)GetPane(1, 0); SetLayout(m_nColumns, m_nColumnWidths, (m_sizeListPane = (!m_sizeListPane.cy) ? sizePanes[0] : m_sizeListPane), (m_sizeFlowchartPane = (!m_sizeFlowchartPane.cy) ? CSize(sizePanes[1].cx / 2, sizePanes[1].cy) : m_sizeFlowchartPane), (m_sizeCodePane = (!m_sizeCodePane.cy) ? CSize(sizePanes[1].cx / 2, sizePanes[1].cy) : m_sizeCodePane)) && SetListTitleFont(&m_lfListTitleFont) && SetListItemsFont(&m_lfListItemsFont) && SetItemFlowchartTitleFont(&m_lfItemFlowchartTitleFont) && SetItemFlowchartLabelsFont(&m_lfItemFlowchartLabelsFont) && SetItemFlowchartBackgroundColor(m_nItemFlowchartColor[0]) && SetItemFlowchartLabelsColor(m_nItemFlowchartColor[1]) && SetItemSourceCodeFont(&m_lfItemSourceCodeFont) && SetProcedures(m_pContents) && SetTelecommandingMode(m_nTelecommandingMode) && SetTelecommandingState(m_nTelecommandingState) && SetTelecommandingChecks(m_nTelecommandingFlags) && EnableTelecommandingReleaseWaitMode(m_bTelecommandingReleaseWaitMode) && EnableToolTipMode(m_bToolTips); ) return TRUE;
			break;
		}
	}
	return FALSE;
}

BOOL CTCProceduresMonitorView::SetLayout(CONST CUIntArray &nColumns)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->SetLayout(nColumns) : FALSE);
}
BOOL CTCProceduresMonitorView::SetLayout(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->SetLayout(nColumns, nWidths) : FALSE);
}
BOOL CTCProceduresMonitorView::SetLayout(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST SIZE &sizeListPane, CONST SIZE &sizeFlowchartPane, CONST SIZE &sizeCodePane)
{
	INT  nPaneHeight[2][2];

	if (IsWindow(GetSafeHwnd()))
	{
		if (GetListView()->SetLayout(nColumns, nWidths))
		{
			for (GetRowInfo(0, nPaneHeight[0][0], nPaneHeight[0][1]), GetRowInfo(1, nPaneHeight[1][0], nPaneHeight[1][1]), SetRowInfo(0, max(sizeListPane.cy, 0), max(nPaneHeight[0][1], 0)), SetRowInfo(1, max(max(sizeFlowchartPane.cy, sizeCodePane.cy), 0), max(nPaneHeight[1][1], 0)), RecalcLayout(); TRUE; )
			{
				for (GetRowInfo(0, nPaneHeight[0][0], nPaneHeight[0][1]), GetRowInfo(1, nPaneHeight[1][0], nPaneHeight[1][1]); nPaneHeight[0][0] > 0 && nPaneHeight[1][0] >= 0; )
				{
					m_sizeListPane.cy = nPaneHeight[0][0];
					m_sizeCodePane.cy = nPaneHeight[1][0];
					m_sizeFlowchartPane.cy = nPaneHeight[1][0];
					break;
				}
				break;
			}
			return GetItemView()->SetLayout(sizeFlowchartPane, sizeCodePane);
		}
		if (GetListView()->SetLayout(nColumns))
		{
			for (GetRowInfo(0, nPaneHeight[0][0], nPaneHeight[0][1]), GetRowInfo(1, nPaneHeight[1][0], nPaneHeight[1][1]), SetRowInfo(0, max(sizeListPane.cy, 0), max(nPaneHeight[0][1], 0)), SetRowInfo(1, max(max(sizeFlowchartPane.cy, sizeCodePane.cy), 0), max(nPaneHeight[1][1], 0)), RecalcLayout(); TRUE; )
			{
				for (GetRowInfo(0, nPaneHeight[0][0], nPaneHeight[0][1]), GetRowInfo(1, nPaneHeight[1][0], nPaneHeight[1][1]); nPaneHeight[0][0] > 0 && nPaneHeight[1][0] >= 0; )
				{
					m_sizeListPane.cy = nPaneHeight[0][0];
					m_sizeCodePane.cy = nPaneHeight[1][0];
					m_sizeFlowchartPane.cy = nPaneHeight[1][0];
					break;
				}
				break;
			}
			return GetItemView()->SetLayout(sizeFlowchartPane, sizeCodePane);
		}
		return FALSE;
	}
	m_sizeListPane = sizeListPane;
	m_sizeCodePane = sizeCodePane;
	m_sizeFlowchartPane = sizeFlowchartPane;
	m_nColumnWidths.Copy(nWidths);
	m_nColumns.Copy(nColumns);
	return TRUE;
}

BOOL CTCProceduresMonitorView::GetLayout(CUIntArray &nColumns) CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->GetLayout(nColumns) : FALSE);
}
BOOL CTCProceduresMonitorView::GetLayout(CUIntArray &nColumns, CUIntArray &nWidths) CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->GetLayout(nColumns, nWidths) : FALSE);
}
BOOL CTCProceduresMonitorView::GetLayout(CUIntArray &nColumns, CUIntArray &nWidths, CSize &sizeListPane, CSize &sizeFlowchartPane, CSize &sizeCodePane) CONST
{
	INT  nPaneHeight[2][2];

	if (IsWindow(GetSafeHwnd()))
	{
		if (GetListView()->GetLayout(nColumns, nWidths) && GetItemView()->GetLayout(sizeFlowchartPane, sizeCodePane))
		{
			GetRowInfo(0, nPaneHeight[0][0], nPaneHeight[0][1]);
			GetRowInfo(1, nPaneHeight[1][0], nPaneHeight[1][1]);
			sizeListPane.cx = 0;
			sizeListPane.cy = nPaneHeight[0][0];
			sizeCodePane.cy = nPaneHeight[1][0];
			sizeFlowchartPane.cy = nPaneHeight[1][0];
			return TRUE;
		}
		return FALSE;
	}
	sizeListPane = m_sizeListPane;
	sizeCodePane = m_sizeCodePane;
	sizeFlowchartPane = m_sizeFlowchartPane;
	nWidths.Copy(m_nColumnWidths);
	nColumns.Copy(m_nColumns);
	return TRUE;
}

BOOL CTCProceduresMonitorView::SetListTitleFont(CFont *pFont)
{
	LOGFONT  lfFont;

	return((pFont->GetLogFont(&lfFont)) ? SetListTitleFont(&lfFont) : FALSE);
}
BOOL CTCProceduresMonitorView::SetListTitleFont(CONST LOGFONT *plfFont)
{
	if (!IsWindow(GetSafeHwnd()))
	{
		CopyMemory(&m_lfListTitleFont, plfFont, sizeof(LOGFONT));
		return TRUE;
	}
	return GetListView()->SetListTitleFont(plfFont);
}

BOOL CTCProceduresMonitorView::GetListTitleFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return((GetListTitleFont(&lfFont)) ? pFont->CreateFontIndirect(&lfFont) : FALSE);
}
BOOL CTCProceduresMonitorView::GetListTitleFont(LOGFONT *plfFont) CONST
{
	if (!IsWindow(GetSafeHwnd()))
	{
		CopyMemory(plfFont, &m_lfListTitleFont, sizeof(LOGFONT));
		return TRUE;
	}
	return GetListView()->GetListTitleFont(plfFont);
}

BOOL CTCProceduresMonitorView::SetListItemsFont(CFont *pFont)
{
	LOGFONT  lfFont;

	return((pFont->GetLogFont(&lfFont)) ? SetListItemsFont(&lfFont) : FALSE);
}
BOOL CTCProceduresMonitorView::SetListItemsFont(CONST LOGFONT *plfFont)
{
	if (!IsWindow(GetSafeHwnd()))
	{
		CopyMemory(&m_lfListItemsFont, plfFont, sizeof(LOGFONT));
		return TRUE;
	}
	return GetListView()->SetListItemsFont(plfFont);
}

BOOL CTCProceduresMonitorView::GetListItemsFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return((GetListItemsFont(&lfFont)) ? pFont->CreateFontIndirect(&lfFont) : FALSE);
}
BOOL CTCProceduresMonitorView::GetListItemsFont(LOGFONT *plfFont) CONST
{
	if (!IsWindow(GetSafeHwnd()))
	{
		CopyMemory(plfFont, &m_lfListItemsFont, sizeof(LOGFONT));
		return TRUE;
	}
	return GetListView()->GetListItemsFont(plfFont);
}

BOOL CTCProceduresMonitorView::SetItemFlowcharts(CONST CTCProceduresMonitorItem *pItem)
{
	return GetItemView()->SetFlowcharts(pItem);
}

BOOL CTCProceduresMonitorView::GetItemFlowcharts(CTCProceduresMonitorItem *pItem) CONST
{
	return GetItemView()->GetFlowcharts(pItem);
}

BOOL CTCProceduresMonitorView::SetItemFlowchartTitleFont(CFont *pFont)
{
	LOGFONT  lfFont;

	return((pFont->GetLogFont(&lfFont)) ? SetItemFlowchartTitleFont(&lfFont) : FALSE);
}
BOOL CTCProceduresMonitorView::SetItemFlowchartTitleFont(CONST LOGFONT *plfFont)
{
	if (!IsWindow(GetSafeHwnd()))
	{
		CopyMemory(&m_lfItemFlowchartTitleFont, plfFont, sizeof(LOGFONT));
		return TRUE;
	}
	return GetItemView()->SetFlowchartTitleFont(plfFont);
}

BOOL CTCProceduresMonitorView::GetItemFlowchartTitleFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return((GetItemFlowchartTitleFont(&lfFont)) ? pFont->CreateFontIndirect(&lfFont) : FALSE);
}
BOOL CTCProceduresMonitorView::GetItemFlowchartTitleFont(LOGFONT *plfFont) CONST
{
	if (!IsWindow(GetSafeHwnd()))
	{
		CopyMemory(plfFont, &m_lfItemFlowchartTitleFont, sizeof(LOGFONT));
		return TRUE;
	}
	return GetItemView()->GetFlowchartTitleFont(plfFont);
}

BOOL CTCProceduresMonitorView::SetItemFlowchartLabelsFont(CFont *pFont)
{
	LOGFONT  lfFont;

	return((pFont->GetLogFont(&lfFont)) ? SetItemFlowchartLabelsFont(&lfFont) : FALSE);
}
BOOL CTCProceduresMonitorView::SetItemFlowchartLabelsFont(CONST LOGFONT *plfFont)
{
	if (!IsWindow(GetSafeHwnd()))
	{
		CopyMemory(&m_lfItemFlowchartLabelsFont, plfFont, sizeof(LOGFONT));
		return TRUE;
	}
	return GetItemView()->SetFlowchartLabelsFont(plfFont);
}

BOOL CTCProceduresMonitorView::GetItemFlowchartLabelsFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return((GetItemFlowchartLabelsFont(&lfFont)) ? pFont->CreateFontIndirect(&lfFont) : FALSE);
}
BOOL CTCProceduresMonitorView::GetItemFlowchartLabelsFont(LOGFONT *plfFont) CONST
{
	if (!IsWindow(GetSafeHwnd()))
	{
		CopyMemory(plfFont, &m_lfItemFlowchartLabelsFont, sizeof(LOGFONT));
		return TRUE;
	}
	return GetItemView()->GetFlowchartLabelsFont(plfFont);
}

BOOL CTCProceduresMonitorView::SetItemFlowchartLabelsColor(COLORREF nColor)
{
	if (!IsWindow(GetSafeHwnd()))
	{
		m_nItemFlowchartColor[1] = nColor;
		return TRUE;
	}
	return GetItemView()->SetFlowchartLabelsColor(nColor);
}

BOOL CTCProceduresMonitorView::GetItemFlowchartLabelsColor(COLORREF &nColor) CONST
{
	if (!IsWindow(GetSafeHwnd()))
	{
		nColor = m_nItemFlowchartColor[1];
		return TRUE;
	}
	return GetItemView()->GetFlowchartLabelsColor(nColor);
}

BOOL CTCProceduresMonitorView::SetItemFlowchartBackgroundColor(COLORREF nColor)
{
	if (!IsWindow(GetSafeHwnd()))
	{
		m_nItemFlowchartColor[0] = nColor;
		return TRUE;
	}
	return GetItemView()->SetFlowchartBackgroundColor(nColor);
}

BOOL CTCProceduresMonitorView::GetItemFlowchartBackgroundColor(COLORREF &nColor) CONST
{
	if (!IsWindow(GetSafeHwnd()))
	{
		nColor = m_nItemFlowchartColor[0];
		return TRUE;
	}
	return GetItemView()->GetFlowchartBackgroundColor(nColor);
}

BOOL CTCProceduresMonitorView::SetItemSourceCodeFont(CFont *pFont)
{
	LOGFONT  lfFont;

	return((pFont->GetLogFont(&lfFont)) ? SetItemSourceCodeFont(&lfFont) : FALSE);
}
BOOL CTCProceduresMonitorView::SetItemSourceCodeFont(CONST LOGFONT *plfFont)
{
	if (!IsWindow(GetSafeHwnd()))
	{
		CopyMemory(&m_lfItemSourceCodeFont, plfFont, sizeof(LOGFONT));
		return TRUE;
	}
	return GetItemView()->SetSourceCodeFont(plfFont);
}

BOOL CTCProceduresMonitorView::GetItemSourceCodeFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return((GetItemSourceCodeFont(&lfFont)) ? pFont->CreateFontIndirect(&lfFont) : FALSE);
}
BOOL CTCProceduresMonitorView::GetItemSourceCodeFont(LOGFONT *plfFont) CONST
{
	if (!IsWindow(GetSafeHwnd()))
	{
		CopyMemory(plfFont, &m_lfItemSourceCodeFont, sizeof(LOGFONT));
		return TRUE;
	}
	return GetItemView()->GetSourceCodeFont(plfFont);
}

BOOL CTCProceduresMonitorView::EnableToolTipMode(BOOL bEnable)
{
	if (!IsWindow(GetSafeHwnd()))
	{
		m_bToolTips = bEnable;
		return TRUE;
	}
	return GetListView()->EnableToolTipMode(bEnable) && GetItemView()->EnableToolTipMode(bEnable);
}

BOOL CTCProceduresMonitorView::IsToolTipModeEnabled() CONST
{
	return((IsWindow(GetSafeHwnd())) ? (GetListView()->IsToolTipModeEnabled() || GetItemView()->IsToolTipModeEnabled()) : m_bToolTips);
}

BOOL CTCProceduresMonitorView::SetProcedures(CONST CTCProceduresMonitorItems &pItems)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->SetProcedures(pItems) : m_pContents.Copy(&pItems));
}

BOOL CTCProceduresMonitorView::GetProcedures(CTCProceduresMonitorItems &pItems) CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->GetProcedures(pItems) : pItems.Copy(&m_pContents));
}

BOOL CTCProceduresMonitorView::UpdateProcedure(CONST CTCItem *pTCItem)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->UpdateProcedure(pTCItem) : FALSE);
}

BOOL CTCProceduresMonitorView::StartProcedure(INT nIndex)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->StartProcedure(nIndex) : FALSE);
}

BOOL CTCProceduresMonitorView::CanStartProcedure(INT nIndex) CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->CanStartProcedure(nIndex) : FALSE);
}

BOOL CTCProceduresMonitorView::IsProcedureRunning(INT nIndex) CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->IsProcedureRunning(nIndex) : FALSE);
}

BOOL CTCProceduresMonitorView::SuspendProcedure(INT nIndex)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->SuspendProcedure(nIndex) : FALSE);
}

BOOL CTCProceduresMonitorView::ResumeProcedure(INT nIndex)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->ResumeProcedure(nIndex) : FALSE);
}

BOOL CTCProceduresMonitorView::IsProcedureSuspended(INT nIndex) CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->IsProcedureSuspended(nIndex) : FALSE);
}

BOOL CTCProceduresMonitorView::IsProcedureDisabled(INT nIndex) CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->IsProcedureDisabled(nIndex) : FALSE);
}

BOOL CTCProceduresMonitorView::StepIntoProcedure(INT nIndex)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->StepIntoProcedure(nIndex, GetItemView()->GetSelectedThreadID()) : FALSE);
}

BOOL CTCProceduresMonitorView::CanStepIntoProcedure(INT nIndex) CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->CanStepIntoProcedure(nIndex, GetItemView()->GetSelectedThreadID()) : FALSE);
}

BOOL CTCProceduresMonitorView::StepOverProcedure(INT nIndex)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->StepOverProcedure(nIndex, GetItemView()->GetSelectedThreadID()) : FALSE);
}

BOOL CTCProceduresMonitorView::CanStepOverProcedure(INT nIndex) CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->CanStepOverProcedure(nIndex, GetItemView()->GetSelectedThreadID()) : FALSE);
}

BOOL CTCProceduresMonitorView::StepOutProcedure(INT nIndex)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->StepOutProcedure(nIndex, GetItemView()->GetSelectedThreadID()) : FALSE);
}

BOOL CTCProceduresMonitorView::CanStepOutProcedure(INT nIndex) CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->CanStepOutProcedure(nIndex, GetItemView()->GetSelectedThreadID()) : FALSE);
}

BOOL CTCProceduresMonitorView::UpdateProcedure(INT nIndex)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->UpdateProcedure(nIndex) : FALSE);
}
BOOL CTCProceduresMonitorView::UpdateProcedure(INT nIndex, UINT nTriggerType, UINT nRunningState, CONST CTimeKey &tExecutionStartTime, CONST CTimeKey &tExecutionEndTime, UINT nExecutionCount)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->UpdateProcedure(nIndex, nTriggerType, nRunningState, tExecutionStartTime, tExecutionEndTime, nExecutionCount) : FALSE);
}
BOOL CTCProceduresMonitorView::UpdateProcedure(INT nIndex, UINT nTriggerType, UINT nRunningState, INT nThreadID, UINT nThreadState, CONST CStringArray &szThreadSteps, CONST CUIntArray &nThreadStates, UINT nThreadLine)
{
	return((IsWindow(GetSafeHwnd())) ? (GetListView()->UpdateProcedure(nIndex, nTriggerType, nRunningState) && (nIndex != GetCurProcedure() || GetItemView()->UpdateContents(nThreadID, nThreadState, szThreadSteps, nThreadStates, nThreadLine))) : FALSE);
}
BOOL CTCProceduresMonitorView::UpdateProcedure(INT nIndex, INT nThreadID, UINT nThreadState, CONST CStringArray &szThreadSteps, CONST CUIntArray &nThreadStates, UINT nThreadLine)
{
	return((IsWindow(GetSafeHwnd())) ? (nIndex != GetCurProcedure() || GetItemView()->UpdateContents(nThreadID, nThreadState, szThreadSteps, nThreadStates, nThreadLine)) : FALSE);
}

BOOL CTCProceduresMonitorView::AlertProcedure(INT nIndex, UINT nType, LPCTSTR pszAlert)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->AlertProcedure(nIndex, nType, pszAlert) : FALSE);
}

BOOL CTCProceduresMonitorView::AcknowledgeProcedure(INT nIndex)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->AcknowledgeProcedure(nIndex) : FALSE);
}

BOOL CTCProceduresMonitorView::CanAcknowledgeProcedure(INT nIndex) CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->CanAcknowledgeProcedure(nIndex) : FALSE);
}

BOOL CTCProceduresMonitorView::ResetProcedure(INT nIndex)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->ResetProcedure(nIndex) : FALSE);
}

BOOL CTCProceduresMonitorView::CanResetProcedure(INT nIndex) CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->CanResetProcedure(nIndex) : FALSE);
}

BOOL CTCProceduresMonitorView::CanBreakProcedure(INT nIndex) CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->CanBreakProcedure(nIndex) : FALSE);
}

BOOL CTCProceduresMonitorView::AbortProcedure(INT nIndex)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->AbortProcedure(nIndex) : FALSE);
}

BOOL CTCProceduresMonitorView::SetProcedureInfo(INT nIndex, CONST CTCProceduresMonitorItem *pItem, BOOL bAll)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->SetProcedureInfo(nIndex, pItem, bAll) : FALSE);
}

BOOL CTCProceduresMonitorView::GetProcedureInfo(INT nIndex, CTCProceduresMonitorItem *pItem, BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->GetProcedureInfo(nIndex, pItem, bAll) : FALSE);
}
BOOL CTCProceduresMonitorView::GetProcedureInfo(INT nIndex, CDatabaseTCProcedure *pProcedure) CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->GetProcedureInfo(nIndex, pProcedure) : FALSE);
}
BOOL CTCProceduresMonitorView::GetProcedureInfo(INT nIndex, CString &szName, UINT &nMode, UINT &nState) CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->GetProcedureInfo(nIndex, szName, nMode, nState) : FALSE);
}

BOOL CTCProceduresMonitorView::SetCurProcedure(INT nIndex)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->SetCurProcedure(nIndex) : FALSE);
}

INT CTCProceduresMonitorView::GetCurProcedure() CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->GetCurProcedure() : -1);
}

BOOL CTCProceduresMonitorView::AcknowledgeAllProcedures()
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->AcknowledgeAllProcedures() : FALSE);
}

UINT CTCProceduresMonitorView::GetProcedureCount() CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->GetProcedureCount() : 0);
}

BOOL CTCProceduresMonitorView::StartMonitoring(CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, BOOL bStartup)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->StartMonitoring(pTCProcessEngine, pTCEnvironment, bStartup) : FALSE);
}

BOOL CTCProceduresMonitorView::UpdateMonitoring(CONST CTMEnvironment *pTMEnvironment)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->UpdateMonitoring(pTMEnvironment) : FALSE);
}
BOOL CTCProceduresMonitorView::UpdateMonitoring(LPCTSTR pszEvent)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->UpdateMonitoring(pszEvent) : FALSE);
}

BOOL CTCProceduresMonitorView::IsMonitoring() CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->IsMonitoring() : FALSE);
}

BOOL CTCProceduresMonitorView::StopMonitoring()
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->StopMonitoring() : FALSE);
}

BOOL CTCProceduresMonitorView::SetTelecommandingMode(UINT nMode)
{
	m_nTelecommandingMode = nMode;
	return((IsWindow(GetSafeHwnd())) ? GetListView()->SetTelecommandingMode(nMode) : TRUE);
}

UINT CTCProceduresMonitorView::GetTelecommandingMode() CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->GetTelecommandingMode() : m_nTelecommandingMode);
}

BOOL CTCProceduresMonitorView::SetTelecommandingChecks(UINT nFlags)
{
	m_nTelecommandingFlags = nFlags;
	return((IsWindow(GetSafeHwnd())) ? GetListView()->SetTelecommandingChecks(nFlags) : TRUE);
}

UINT CTCProceduresMonitorView::GetTelecommandingChecks() CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->GetTelecommandingChecks() : m_nTelecommandingFlags);
}

BOOL CTCProceduresMonitorView::SetTelecommandingState(UINT nState)
{
	m_nTelecommandingState = nState;
	return((IsWindow(GetSafeHwnd())) ? GetListView()->SetTelecommandingState(nState) : TRUE);
}

UINT CTCProceduresMonitorView::GetTelecommandingState() CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->GetTelecommandingState() : m_nTelecommandingState);
}

BOOL CTCProceduresMonitorView::SetTelecommandingUplinkState(UINT nState)
{
	m_nTelecommandingUplinkState = nState;
	return((IsWindow(GetSafeHwnd())) ? GetListView()->SetTelecommandingUplinkState(nState) : FALSE);
}

UINT CTCProceduresMonitorView::GetTelecommandingUplinkState() CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->GetTelecommandingUplinkState() : m_nTelecommandingUplinkState);
}

BOOL CTCProceduresMonitorView::EnableTelecommandingReleaseWaitMode(BOOL bEnable)
{
	m_bTelecommandingReleaseWaitMode = bEnable;
	return((IsWindow(GetSafeHwnd())) ? GetListView()->EnableTelecommandingReleaseWaitMode(bEnable) : TRUE);
}

BOOL CTCProceduresMonitorView::IsTelecommandingReleaseWaitModeEnabled() CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->IsTelecommandingReleaseWaitModeEnabled() : m_bTelecommandingReleaseWaitMode);
}

BOOL CTCProceduresMonitorView::InitializeTelecommand(INT nProcedureID, LPCTSTR pszThread, LPCTSTR pszStep, LPCTSTR pszFunction, INT nEntry, CTCItem *pTCItem)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->InitializeTelecommand(nProcedureID, pszThread, pszStep, pszFunction, nEntry, pTCItem) : FALSE);
}

BOOL CTCProceduresMonitorView::EnumAuthorizableTelecommands(INT nIndex, CTCItems &pTCItems) CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->EnumAuthorizableTelecommands(nIndex, pTCItems) : FALSE);
}

BOOL CTCProceduresMonitorView::AuthorizeTelecommands(INT nIndex, CONST CTCItems &pTCItems)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->AuthorizeTelecommands(nIndex, pTCItems) : FALSE);
}
BOOL CTCProceduresMonitorView::AuthorizeTelecommands(CONST CTCItems &pTCItems)
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->AuthorizeTelecommands(pTCItems) : FALSE);
}

BOOL CTCProceduresMonitorView::CanAuthorizeTelecommands(INT nIndex) CONST
{
	return((IsWindow(GetSafeHwnd())) ? GetListView()->CanAuthorizeTelecommands(nIndex) : FALSE);
}

VOID CTCProceduresMonitorView::UpdateContents(BOOL bAll)
{
	if (IsWindow(GetSafeHwnd()))
	{
		for (GetListView()->UpdateContent(); bAll; )
		{
			GetItemView()->UpdateContents();
			break;
		}
	}
}

void CTCProceduresMonitorView::StartTracking(int ht)
{
	CSplitterWndEx::StartTracking(ht);
	m_rectLimit.top += GetListView()->GetTrackSize().cy;
	m_rectLimit.bottom -= GetItemView()->GetTrackSize().cy;
}

VOID CTCProceduresMonitorView::ResizeToContents(BOOL bAll)
{
	INT  nPaneHeight[2][2];

	if (bAll)
	{
		if (!m_bTracking)
		{
			SetRowInfo(0, max(m_sizeListPane.cy, 0), 0);
			SetRowInfo(1, max(m_sizeFlowchartPane.cy, m_sizeCodePane.cy), 0);
			m_bTracking = TRUE;
			RecalcLayout();
		}
		return;
	}
	if (m_bTracking)
	{
		for (GetRowInfo(0, nPaneHeight[0][0], nPaneHeight[0][1]), GetRowInfo(1, nPaneHeight[1][0], nPaneHeight[1][1]); GetProcedureCount() > 0 && nPaneHeight[0][0] > 0 && nPaneHeight[1][0] >= 0; )
		{
			m_sizeListPane.cy = nPaneHeight[0][0];
			m_sizeCodePane.cy = nPaneHeight[1][0];
			m_sizeFlowchartPane.cy = nPaneHeight[1][0];
			SetRowInfo(0, max(m_sizeListPane.cy + max(m_sizeFlowchartPane.cy, m_sizeCodePane.cy), 0), max(m_sizeListPane.cy + max(m_sizeFlowchartPane.cy, m_sizeCodePane.cy), 0));
			SetRowInfo(1, 0, 0);
			m_bTracking = FALSE;
			RecalcLayout();
			return;
		}
	}
}

BOOL CTCProceduresMonitorView::SetLayoutInfo(INT nIndex, INT nThreadID, CONST SCROLLINFO *pListPaneHorzScrollInfo, CONST SCROLLINFO *pListPaneVertScrollInfo)
{
	return((IsWindow(GetSafeHwnd())) ? (GetListView()->SetLayoutInfo(nIndex, pListPaneHorzScrollInfo, pListPaneVertScrollInfo) && GetItemView()->SetLayoutInfo(nThreadID)) : FALSE);
}

BOOL CTCProceduresMonitorView::GetLayoutInfo(INT &nIndex, INT &nThreadID, SCROLLINFO *pListPaneHorzScrollInfo, SCROLLINFO *pListPaneVertScrollInfo) CONST
{
	return((IsWindow(GetSafeHwnd())) ? (GetListView()->GetLayoutInfo(nIndex, pListPaneHorzScrollInfo, pListPaneVertScrollInfo) && GetItemView()->GetLayoutInfo(nThreadID)) : FALSE);
}

BOOL CTCProceduresMonitorView::GetPrintProperties(CONST CTCProceduresMonitorPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, CStringArray &szThreads, CPtrArray &pThreadMetaDCs, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST
{
	return((IsWindow(GetSafeHwnd())) ? (GetListView()->GetPrintProperties(szColumns, szContents, pAttributes, pTitleFont, pItemsFont, pSymbols, nSymbolIDs, ((pJobInfo->GetPrintMode() & TCPROCEDURESMONITOR_PRINT_ONEONLY) != TCPROCEDURESMONITOR_PRINT_ONEONLY) ? TRUE : FALSE) && ((pJobInfo->GetPrintMode() & TCPROCEDURESMONITOR_PRINT_FLOWCHART) != TCPROCEDURESMONITOR_PRINT_FLOWCHART || GetItemView()->GetPrintProperties(szThreads, pThreadMetaDCs))) : FALSE);
}

CTCProceduresMonitorListView *CTCProceduresMonitorView::GetListView() CONST
{
	return m_pListView;
}

CTCProceduresMonitorItemView *CTCProceduresMonitorView::GetItemView() CONST
{
	return m_pItemView;
}

CTCProceduresMonitorWnd *CTCProceduresMonitorView::GetParent() CONST
{
	return((CTCProceduresMonitorWnd *)m_pParentWnd);
}

VOID CTCProceduresMonitorView::RecalcLayout()
{
	CSplitterWndEx::RecalcLayout();
}
VOID CTCProceduresMonitorView::RecalcLayout(BOOL bRecalc)
{
	CWnd  *pWnd;
	CRect  rWnd;
	CRect  rView;

	if (CThread::IsSameThread(this) && IsWindow(m_pListView->GetSafeHwnd()) && IsWindow(m_pItemView->GetSafeHwnd()))
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

void CTCProceduresMonitorView::PostNcDestroy()
{
	m_nColumns.RemoveAll();
	m_nColumnWidths.RemoveAll();
	m_pContents.RemoveAll();
	CSplitterWndEx::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorView, CSplitterWndEx)
	//{{AFX_MSG_MAP(CTCProceduresMonitorView)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorView message handlers

void CTCProceduresMonitorView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bTracking) return;
	CSplitterWndEx::OnMouseMove(nFlags, point);
}

void CTCProceduresMonitorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!m_bTracking) return;
	CSplitterWndEx::OnLButtonDown(nFlags, point);
}

void CTCProceduresMonitorView::OnSetFocus(CWnd *pOldWnd)
{
	if (pOldWnd == GetParent())
	{
		GetListView()->SetFocus();
		return;
	}
	if (pOldWnd == GetListView())
	{
		GetItemView()->SetFocus();
		return;
	}
	if (pOldWnd == GetItemView())
	{
		GetParent()->SetFocus();
		return;
	}
	CSplitterWndEx::OnSetFocus(pOldWnd);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorWnd

IMPLEMENT_DYNAMIC(CTCProceduresMonitorWnd, CDisplayWnd)

CTCProceduresMonitorWnd::CTCProceduresMonitorWnd() : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_TCPROCEDURESMONITOR);
	SetTelecommandingMode(TCPROCEDURESMONITOR_MODE_DEFAULT);
	SetTelecommandingState(TCPROCEDURESMONITOR_STATE_DEFAULT);
	SetTelecommandingChecks(TCPROCEDURESMONITOR_CHECKS_DEFAULT);
	EnableTelecommandingReleaseWaitMode(FALSE);
	SetLoggingOptions();
}

BOOL CTCProceduresMonitorWnd::Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault)
{
	if (CDisplayWnd::Create(pParentWnd, (!pszTitle || !_tcsstr(pszTitle, STRING(IDS_DISPLAY_TITLE_TCPROCEDURESMONITOR))) ? STRING(IDS_DISPLAY_TITLE_TCPROCEDURESMONITOR) : pszTitle, pDefaultInfo->rWnd, IDR_TCPROCEDURESMONITORFRAME))
	{
		if (SetScope(pDefaultInfo->nScope) && SetMode(pDefaultInfo->nMode) && Customize(bDefault)) return TRUE;
		DestroyWindow();
	}
	return FALSE;
}

BOOL CTCProceduresMonitorWnd::SetLayout(CONST CUIntArray &nColumns)
{
	return m_wndView.SetLayout(nColumns);
}
BOOL CTCProceduresMonitorWnd::SetLayout(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths)
{
	return m_wndView.SetLayout(nColumns, nWidths);
}
BOOL CTCProceduresMonitorWnd::SetLayout(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST SIZE &sizeListPane, CONST SIZE &sizeFlowchartPane, CONST SIZE &sizeCodePane)
{
	return m_wndView.SetLayout(nColumns, nWidths, sizeListPane, sizeFlowchartPane, sizeCodePane);
}

BOOL CTCProceduresMonitorWnd::GetLayout(CUIntArray &nColumns) CONST
{
	return m_wndView.GetLayout(nColumns);
}
BOOL CTCProceduresMonitorWnd::GetLayout(CUIntArray &nColumns, CUIntArray &nWidths) CONST
{
	return m_wndView.GetLayout(nColumns, nWidths);
}
BOOL CTCProceduresMonitorWnd::GetLayout(CUIntArray &nColumns, CUIntArray &nWidths, CSize &sizeListPane, CSize &sizeFlowchartPane, CSize &sizeCodePane) CONST
{
	return m_wndView.GetLayout(nColumns, nWidths, sizeListPane, sizeFlowchartPane, sizeCodePane);
}

BOOL CTCProceduresMonitorWnd::SetListTitleFont(CFont *pFont)
{
	return m_wndView.SetListTitleFont(pFont);
}
BOOL CTCProceduresMonitorWnd::SetListTitleFont(CONST LOGFONT *plfFont)
{
	return m_wndView.SetListTitleFont(plfFont);
}

BOOL CTCProceduresMonitorWnd::GetListTitleFont(CFont *pFont) CONST
{
	return m_wndView.GetListTitleFont(pFont);
}
BOOL CTCProceduresMonitorWnd::GetListTitleFont(LOGFONT *plfFont) CONST
{
	return m_wndView.GetListTitleFont(plfFont);
}

BOOL CTCProceduresMonitorWnd::SetListItemsFont(CFont *pFont)
{
	return m_wndView.SetListItemsFont(pFont);
}
BOOL CTCProceduresMonitorWnd::SetListItemsFont(CONST LOGFONT *plfFont)
{
	return m_wndView.SetListItemsFont(plfFont);
}

BOOL CTCProceduresMonitorWnd::GetListItemsFont(CFont *pFont) CONST
{
	return m_wndView.GetListItemsFont(pFont);
}
BOOL CTCProceduresMonitorWnd::GetListItemsFont(LOGFONT *plfFont) CONST
{
	return m_wndView.GetListItemsFont(plfFont);
}

BOOL CTCProceduresMonitorWnd::SetItemFlowcharts(CONST CTCProceduresMonitorItem *pItem)
{
	return m_wndView.SetItemFlowcharts(pItem);
}

BOOL CTCProceduresMonitorWnd::GetItemFlowcharts(CTCProceduresMonitorItem *pItem) CONST
{
	return m_wndView.GetItemFlowcharts(pItem);
}

BOOL CTCProceduresMonitorWnd::SetItemFlowchartTitleFont(CFont *pFont)
{
	return m_wndView.SetItemFlowchartTitleFont(pFont);
}
BOOL CTCProceduresMonitorWnd::SetItemFlowchartTitleFont(CONST LOGFONT *plfFont)
{
	return m_wndView.SetItemFlowchartTitleFont(plfFont);
}

BOOL CTCProceduresMonitorWnd::GetItemFlowchartTitleFont(CFont *pFont) CONST
{
	return m_wndView.GetItemFlowchartTitleFont(pFont);
}
BOOL CTCProceduresMonitorWnd::GetItemFlowchartTitleFont(LOGFONT *plfFont) CONST
{
	return m_wndView.GetItemFlowchartTitleFont(plfFont);
}

BOOL CTCProceduresMonitorWnd::SetItemFlowchartLabelsFont(CFont *pFont)
{
	return m_wndView.SetItemFlowchartLabelsFont(pFont);
}
BOOL CTCProceduresMonitorWnd::SetItemFlowchartLabelsFont(CONST LOGFONT *plfFont)
{
	return m_wndView.SetItemFlowchartLabelsFont(plfFont);
}

BOOL CTCProceduresMonitorWnd::GetItemFlowchartLabelsFont(CFont *pFont) CONST
{
	return m_wndView.GetItemFlowchartLabelsFont(pFont);
}
BOOL CTCProceduresMonitorWnd::GetItemFlowchartLabelsFont(LOGFONT *plfFont) CONST
{
	return m_wndView.GetItemFlowchartLabelsFont(plfFont);
}

BOOL CTCProceduresMonitorWnd::SetItemFlowchartLabelsColor(COLORREF nColor)
{
	return m_wndView.SetItemFlowchartLabelsColor(nColor);
}

BOOL CTCProceduresMonitorWnd::GetItemFlowchartLabelsColor(COLORREF &nColor) CONST
{
	return m_wndView.GetItemFlowchartLabelsColor(nColor);
}

BOOL CTCProceduresMonitorWnd::SetItemFlowchartBackgroundColor(COLORREF nColor)
{
	return m_wndView.SetItemFlowchartBackgroundColor(nColor);
}

BOOL CTCProceduresMonitorWnd::GetItemFlowchartBackgroundColor(COLORREF &nColor) CONST
{
	return m_wndView.GetItemFlowchartBackgroundColor(nColor);
}

BOOL CTCProceduresMonitorWnd::SetItemSourceCodeFont(CFont *pFont)
{
	return m_wndView.SetItemSourceCodeFont(pFont);
}
BOOL CTCProceduresMonitorWnd::SetItemSourceCodeFont(CONST LOGFONT *plfFont)
{
	return m_wndView.SetItemSourceCodeFont(plfFont);
}

BOOL CTCProceduresMonitorWnd::GetItemSourceCodeFont(CFont *pFont) CONST
{
	return m_wndView.GetItemSourceCodeFont(pFont);
}
BOOL CTCProceduresMonitorWnd::GetItemSourceCodeFont(LOGFONT *plfFont) CONST
{
	return m_wndView.GetItemSourceCodeFont(plfFont);
}

BOOL CTCProceduresMonitorWnd::EnableToolTipMode(BOOL bEnable)
{
	return m_wndView.EnableToolTipMode(bEnable);
}

BOOL CTCProceduresMonitorWnd::IsToolTipModeEnabled() CONST
{
	return m_wndView.IsToolTipModeEnabled();
}

BOOL CTCProceduresMonitorWnd::SetProcedures(CONST CTCProceduresMonitorItems &pItems)
{
	INT  nItem;
	INT  nItems;
	INT  nStep;
	INT  nSteps;
	INT  nIndex;
	INT  nEntry;
	INT  nEntries;
	INT  nThread;
	INT  nThreads;
	CString  szInterlock;
	CPtrArray  pSteps;
	CTimeSpan  tTimeWindow;
	CTCInterlock  *pInterlock;
	CTCInterlocks  pInterlocks;
	CComputerToken  cComputerToken;
	CDatabaseTCFunction  *pFunction;
	CDatabaseTCSequence  *pSequence;
	CDatabaseTCProcedure  *pProcedure;
	CDatabaseTCProcedures  pProcedures;
	CDatabaseTCProcedureThread  *pThread;
	CDatabaseTCSequenceEntry  *pSequenceEntry;
	CTCProcedureDocumentSendTCSequenceItem  *pSendTCSequenceItem;
	CTCProceduresMonitorItems  pOldItems;
	CTCProceduresMonitorItem  *pItem;
	CTCProcedureDocumentItem  *pStep;
	CTCProcedureDocument  *pDocument;
	CTCServiceLock  cLock(this);

	for (nItem = 0, nItems = (GetDatabase()->EnumProcedures(pProcedures) >= 0) ? (INT)pItems.GetSize() : 0; nItem < nItems; nItem++)
	{
		if ((pProcedure = ((pItem = pItems.GetAt(nItem))) ? pProcedures.GetAt(pProcedures.Find(pItem->GetName())) : (CDatabaseTCProcedure *)NULL))
		{
			for (nThread = 0, nThreads = (pProcedure->Compare(pItem) || pItem->CDatabaseTCProcedure::Copy(pProcedure)) ? (INT)pProcedure->GetSize() : 0; nThread < nThreads; nThread++)
			{
				if ((pThread = pProcedure->GetAt(nThread)))
				{
					if ((pDocument = new CTCProcedureDocument))
					{
						if (pDocument->Unmap(pThread) && pDocument->EnumSteps(pSteps, FALSE, TRUE) >= 0)
						{
							for (nStep = 0, nSteps = (INT)pSteps.GetSize(); nStep < nSteps; nStep++)
							{
								if ((pStep = (CTCProcedureDocumentItem *)pSteps.GetAt(nStep)))
								{
									if (pStep->GetType() == TCPROCEDURETHREADSTEP_ACTIONOBJECT_SENDTCSEQUENCE)
									{
										if ((pSendTCSequenceItem = (CTCProcedureDocumentSendTCSequenceItem *)pStep))
										{
											if ((pSequence = GetDatabase()->GetTCSequences()->GetAt(GetDatabase()->GetTCSequences()->Find(pSendTCSequenceItem->GetSequence()))))
											{
												for (nEntry = 0, nEntries = (INT)pSequence->GetSize(); nEntry < nEntries; nEntry++)
												{
													if ((pSequenceEntry = pSequence->GetAt(nEntry)))
													{
														if (pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_TYPE_FUNCTION)
														{
															if ((pFunction = GetDatabase()->GetTCFunctions()->GetAt(GetDatabase()->GetTCFunctions()->Find(pSequenceEntry->GetName()))))
															{
																if ((pInterlock = ((pSequenceEntry->GetAttributes() & (TCSEQUENCEENTRY_ILSCOPE_GLOBAL | TCSEQUENCEENTRY_ILSCOPE_LOCAL | TCSEQUENCEENTRY_ILSCOPE_LOCALNOWAIT | TCSEQUENCEENTRY_ILSCOPE_GLOBALSUBSYSTEM | TCSEQUENCEENTRY_ILSCOPE_LOCALSUBSYSTEM | TCSEQUENCEENTRY_ILSCOPE_LOCALSUBSYSTEMNOWAIT)) || (pFunction->GetAttributes() & (TCFUNCTION_ILSCOPE_GLOBAL | TCFUNCTION_ILSCOPE_LOCAL | TCFUNCTION_ILSCOPE_GLOBALSUBSYSTEM | TCFUNCTION_ILSCOPE_LOCALSUBSYSTEM))) ? new CTCInterlock : (CTCInterlock *)NULL))
																{
																	for (pInterlock->SetSourceType(TCINTERLOCK_SOURCETYPE_PROCEDURESMONITOR), pInterlock->SetScope(((pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_ILSCOPE_GLOBAL) || (pFunction->GetAttributes() & TCFUNCTION_ILSCOPE_GLOBAL)) ? TCINTERLOCK_SCOPE_GLOBAL : (((pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_ILSCOPE_LOCAL) || (pFunction->GetAttributes() & TCFUNCTION_ILSCOPE_LOCAL)) ? TCINTERLOCK_SCOPE_LOCAL : ((pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_ILSCOPE_LOCALNOWAIT) ? TCINTERLOCK_SCOPE_LOCALNOWAIT : (((pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_ILSCOPE_GLOBALSUBSYSTEM) || (pFunction->GetAttributes() & TCFUNCTION_ILSCOPE_GLOBALSUBSYSTEM)) ? TCINTERLOCK_SCOPE_GLOBALSUBSYSTEM : (((pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_ILSCOPE_LOCALSUBSYSTEM) || (pFunction->GetAttributes() & TCFUNCTION_ILSCOPE_LOCALSUBSYSTEM)) ? TCINTERLOCK_SCOPE_LOCALSUBSYSTEM : ((pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_ILSCOPE_LOCALSUBSYSTEMNOWAIT) ? TCINTERLOCK_SCOPE_LOCALSUBSYSTEMNOWAIT : TCINTERLOCK_SCOPE_NONE)))))), pInterlock->SetStage(((pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_ILSTAGE_RECEPTION) || (pFunction->GetAttributes() & TCFUNCTION_ILSTAGE_RECEPTION)) ? TCINTERLOCK_STAGE_RECEPTION : (((pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_ILSTAGE_UPLINK) || (pFunction->GetAttributes() & TCFUNCTION_ILSTAGE_UPLINK)) ? TCINTERLOCK_STAGE_TRANSMISSION : (((pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_ILSTAGE_ONBOARD) || (pFunction->GetAttributes() & TCFUNCTION_ILSTAGE_ONBOARD)) ? TCINTERLOCK_STAGE_ACCEPTANCE : (((pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_ILSTAGE_ACCEPTANCE) || (pFunction->GetAttributes() & TCFUNCTION_ILSTAGE_ACCEPTANCE)) ? TCINTERLOCK_STAGE_START : (((pSequenceEntry->GetAttributes() & TCSEQUENCEENTRY_ILSTAGE_COMPLETION) || (pFunction->GetAttributes() & TCFUNCTION_ILSTAGE_COMPLETION)) ? TCINTERLOCK_STAGE_COMPLETION : TCINTERLOCK_STAGE_NONE))))), pInterlock->SetState(TCINTERLOCK_STATE_IDLE), pItem->GetReleaseConstraints(pThread->GetName(), pStep->GetName(), pFunction->GetName(), nEntry + 1, szInterlock, tTimeWindow), pItem->SetReleaseConstraints(pThread->GetName(), pStep->GetName(), pFunction->GetName(), nEntry + 1, pInterlock->GetName(), tTimeWindow); (nIndex = (GetTCService()->GetTCInterlocks(pInterlocks)) ? pInterlocks.Find(pInterlock) : -1) < 0; )
																	{
																		if (pInterlocks.Add(pInterlock) < 0)
																		{
																			delete pInterlock;
																			break;
																		}
																		GetTCService()->SetTCInterlocks(pInterlocks);
																		break;
																	}
																	if (nIndex >= 0) delete pInterlock;
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
						delete pDocument;
					}
				}
			}
		}
	}
	for (GetProcedures(pOldItems); m_wndView.SetProcedures(pItems); )
	{
		LogProcedures(pItems, pOldItems);
		UpdateBars();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorWnd::GetProcedures(CTCProceduresMonitorItems &pItems) CONST
{
	return m_wndView.GetProcedures(pItems);
}

BOOL CTCProceduresMonitorWnd::UpdateProcedure(CONST CTCItem *pTCItem)
{
	return m_wndView.UpdateProcedure(pTCItem);
}

BOOL CTCProceduresMonitorWnd::StartProcedure(INT nIndex)
{
	return m_wndView.StartProcedure(nIndex);
}

BOOL CTCProceduresMonitorWnd::CanStartProcedure(INT nIndex) CONST
{
	return m_wndView.CanStartProcedure(nIndex);
}

BOOL CTCProceduresMonitorWnd::IsProcedureRunning(INT nIndex) CONST
{
	return m_wndView.IsProcedureRunning(nIndex);
}

BOOL CTCProceduresMonitorWnd::SuspendProcedure(INT nIndex)
{
	return m_wndView.SuspendProcedure(nIndex);
}

BOOL CTCProceduresMonitorWnd::ResumeProcedure(INT nIndex)
{
	return m_wndView.ResumeProcedure(nIndex);
}

BOOL CTCProceduresMonitorWnd::IsProcedureSuspended(INT nIndex) CONST
{
	return m_wndView.IsProcedureSuspended(nIndex);
}

BOOL CTCProceduresMonitorWnd::IsProcedureDisabled(INT nIndex) CONST
{
	return m_wndView.IsProcedureDisabled(nIndex);
}

BOOL CTCProceduresMonitorWnd::StepIntoProcedure(INT nIndex)
{
	return m_wndView.StepIntoProcedure(nIndex);
}

BOOL CTCProceduresMonitorWnd::CanStepIntoProcedure(INT nIndex) CONST
{
	return m_wndView.CanStepIntoProcedure(nIndex);
}

BOOL CTCProceduresMonitorWnd::StepOverProcedure(INT nIndex)
{
	return m_wndView.StepOverProcedure(nIndex);
}

BOOL CTCProceduresMonitorWnd::CanStepOverProcedure(INT nIndex) CONST
{
	return m_wndView.CanStepOverProcedure(nIndex);
}

BOOL CTCProceduresMonitorWnd::StepOutProcedure(INT nIndex)
{
	return m_wndView.StepOutProcedure(nIndex);
}

BOOL CTCProceduresMonitorWnd::CanStepOutProcedure(INT nIndex) CONST
{
	return m_wndView.CanStepOutProcedure(nIndex);
}

BOOL CTCProceduresMonitorWnd::UpdateProcedure(INT nIndex)
{
	if (m_wndView.UpdateProcedure(nIndex))
	{
		UpdateBars();
		return TRUE;
	}
	return FALSE;
}
BOOL CTCProceduresMonitorWnd::UpdateProcedure(INT nIndex, UINT nTriggerType, UINT nRunningState, CONST CTimeKey &tExecutionStartTime, CONST CTimeKey &tExecutionEndTime, UINT nExecutionCount)
{
	if (m_wndView.UpdateProcedure(nIndex, nTriggerType, nRunningState, tExecutionStartTime, tExecutionEndTime, nExecutionCount))
	{
		UpdateBars();
		return TRUE;
	}
	return FALSE;
}
BOOL CTCProceduresMonitorWnd::UpdateProcedure(INT nIndex, UINT nTriggerType, UINT nRunningState, INT nThreadID, UINT nThreadState, CONST CStringArray &szThreadSteps, CONST CUIntArray &nThreadStates, UINT nThreadLine)
{
	if (m_wndView.UpdateProcedure(nIndex, nTriggerType, nRunningState, nThreadID, nThreadState, szThreadSteps, nThreadStates, nThreadLine))
	{
		UpdateBars();
		return TRUE;
	}
	return FALSE;
}
BOOL CTCProceduresMonitorWnd::UpdateProcedure(INT nIndex, INT nThreadID, UINT nThreadState, CONST CStringArray &szThreadSteps, CONST CUIntArray &nThreadStates, UINT nThreadLine)
{
	if (m_wndView.UpdateProcedure(nIndex, nThreadID, nThreadState, szThreadSteps, nThreadStates, nThreadLine))
	{
		UpdateBars();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorWnd::AlertProcedure(INT nIndex, UINT nType, LPCTSTR pszAlert)
{
	return m_wndView.AlertProcedure(nIndex, nType, pszAlert);
}

BOOL CTCProceduresMonitorWnd::AcknowledgeProcedure(INT nIndex)
{
	return m_wndView.AcknowledgeProcedure(nIndex);
}

BOOL CTCProceduresMonitorWnd::CanAcknowledgeProcedure(INT nIndex) CONST
{
	return m_wndView.CanAcknowledgeProcedure(nIndex);
}

BOOL CTCProceduresMonitorWnd::ResetProcedure(INT nIndex)
{
	return m_wndView.ResetProcedure(nIndex);
}

BOOL CTCProceduresMonitorWnd::CanResetProcedure(INT nIndex) CONST
{
	return m_wndView.CanResetProcedure(nIndex);
}

BOOL CTCProceduresMonitorWnd::CanBreakProcedure(INT nIndex) CONST
{
	return m_wndView.CanBreakProcedure(nIndex);
}

BOOL CTCProceduresMonitorWnd::AbortProcedure(INT nIndex)
{
	return m_wndView.AbortProcedure(nIndex);
}

VOID CTCProceduresMonitorWnd::ShowProcedureDetails(INT nIndex)
{
	CTCProceduresMonitorItem  cItem;

	if (CanAuthorizeTelecommands(nIndex))
	{
		ReportEvent((m_dlgAuthorizations.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
		return;
	}
	if (GetProcedureInfo(nIndex, &cItem) && cItem.GetID() >= 0)
	{
		ReportEvent((m_dlgDetails.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
		return;
	}
	ReportEvent((m_dlgAcknowledgments.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL CTCProceduresMonitorWnd::SetProcedureInfo(INT nIndex, CONST CTCProceduresMonitorItem *pItem, BOOL bAll)
{
	return m_wndView.SetProcedureInfo(nIndex, pItem, bAll);
}

BOOL CTCProceduresMonitorWnd::GetProcedureInfo(INT nIndex, CTCProceduresMonitorItem *pItem, BOOL bAll) CONST
{
	return m_wndView.GetProcedureInfo(nIndex, pItem, bAll);
}
BOOL CTCProceduresMonitorWnd::GetProcedureInfo(INT nIndex, CDatabaseTCProcedure *pProcedure) CONST
{
	return m_wndView.GetProcedureInfo(nIndex, pProcedure);
}
BOOL CTCProceduresMonitorWnd::GetProcedureInfo(INT nIndex, CString &szName, UINT &nMode, UINT &nState) CONST
{
	return m_wndView.GetProcedureInfo(nIndex, szName, nMode, nState);
}

BOOL CTCProceduresMonitorWnd::SetCurProcedure(INT nIndex)
{
	return m_wndView.SetCurProcedure(nIndex);
}

INT CTCProceduresMonitorWnd::GetCurProcedure() CONST
{
	return m_wndView.GetCurProcedure();
}

BOOL CTCProceduresMonitorWnd::AcknowledgeAllProcedures()
{
	return m_wndView.AcknowledgeAllProcedures();
}

UINT CTCProceduresMonitorWnd::GetProcedureCount() CONST
{
	return m_wndView.GetProcedureCount();
}

BOOL CTCProceduresMonitorWnd::StartMonitoring(CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, BOOL bStartup)
{
	return m_wndView.StartMonitoring(pTCProcessEngine, pTCEnvironment, bStartup);
}

BOOL CTCProceduresMonitorWnd::UpdateMonitoring(LPCTSTR pszOriginator, CONST CTCProcessCommandSourceInfo *pCommandSourceInfo)
{
	CTCServiceLock  cLock(this);

	SetTelecommandingMode(pszOriginator, pCommandSourceInfo->GetTelecommandingMode());
	SetTelecommandingState(pszOriginator, pCommandSourceInfo->GetTelecommandingState());
	SetTelecommandingChecks(pszOriginator, pCommandSourceInfo->GetTelecommandingChecks());
	EnableTelecommandingReleaseWaitMode(pszOriginator, pCommandSourceInfo->IsTelecommandingReleaseWaitModeEnabled());
	UpdateContents(FALSE);
	return TRUE;
}
BOOL CTCProceduresMonitorWnd::UpdateMonitoring(CONST CTMEnvironment *pTMEnvironment)
{
	return m_wndView.UpdateMonitoring(pTMEnvironment);
}
BOOL CTCProceduresMonitorWnd::UpdateMonitoring(LPCTSTR pszEvent)
{
	return m_wndView.UpdateMonitoring(pszEvent);
}

BOOL CTCProceduresMonitorWnd::IsMonitoring() CONST
{
	return m_wndView.IsMonitoring();
}

BOOL CTCProceduresMonitorWnd::StopMonitoring()
{
	return m_wndView.StopMonitoring();
}

BOOL CTCProceduresMonitorWnd::SetTelecommandingMode(UINT nMode, BOOL bUser)
{
	CComputerToken  cComputerToken;

	return SetTelecommandingMode(cComputerToken.GetComputerName(), nMode, bUser);
}
BOOL CTCProceduresMonitorWnd::SetTelecommandingMode(LPCTSTR pszOriginator, UINT nMode, BOOL bUser)
{
	CComputerToken  cComputerToken(pszOriginator);
	CTCServiceLock  cLock(this);

	if (nMode != GetTelecommandingMode())
	{
		if (m_wndView.SetTelecommandingMode(nMode) && (!cComputerToken.IsHost() || !lstrlen(pszOriginator) || GetTCService()->SetCommandSourceTelecommandingMode(TCSERVICE_COMMANDSOURCETYPE_PROCEDURESMONITOR, nMode) >= 0))
		{
			LogTelecommandingMode(pszOriginator, nMode, bUser);
			UpdateBars();
			return TRUE;
		}
		return FALSE;
	}
	return TRUE;
}

UINT CTCProceduresMonitorWnd::GetTelecommandingMode() CONST
{
	return m_wndView.GetTelecommandingMode();
}

BOOL CTCProceduresMonitorWnd::SetTelecommandingChecks(UINT nFlags, BOOL bUser)
{
	CComputerToken  cComputerToken;

	return SetTelecommandingChecks(cComputerToken.GetComputerName(), nFlags, bUser);
}
BOOL CTCProceduresMonitorWnd::SetTelecommandingChecks(LPCTSTR pszOriginator, UINT nFlags, BOOL bUser)
{
	UINT  nOldFlags;
	CComputerToken  cComputerToken(pszOriginator);
	CTCServiceLock  cLock(this);

	for (; (nOldFlags = GetTelecommandingChecks()) != nFlags; )
	{
		if (m_wndView.SetTelecommandingChecks(nFlags) && (!cComputerToken.IsHost() || !lstrlen(pszOriginator) || GetTCService()->SetCommandSourceTelecommandingChecks(TCSERVICE_COMMANDSOURCETYPE_PROCEDURESMONITOR, nFlags) >= 0))
		{
			if ((nFlags & (TCPROCEDURESMONITOR_CHECKS_PEV_OVERRIDE | TCPROCEDURESMONITOR_CHECKS_PEV_DISABLE)) != (nOldFlags & (TCPROCEDURESMONITOR_CHECKS_PEV_OVERRIDE | TCPROCEDURESMONITOR_CHECKS_PEV_DISABLE))) LogTelecommandingChecks(pszOriginator, ((nFlags & (TCPROCEDURESMONITOR_CHECKS_PEV_OVERRIDE | TCPROCEDURESMONITOR_CHECKS_PEV_DISABLE)) == 0) ? ~(TCPROCEDURESMONITOR_CHECKS_PEV_OVERRIDE | TCPROCEDURESMONITOR_CHECKS_PEV_DISABLE) : (nFlags & (TCPROCEDURESMONITOR_CHECKS_PEV_OVERRIDE | TCPROCEDURESMONITOR_CHECKS_PEV_DISABLE)), bUser);
			if ((nFlags & (TCPROCEDURESMONITOR_CHECKS_CEV_OVERRIDE | TCPROCEDURESMONITOR_CHECKS_CEV_DISABLE)) != (nOldFlags & (TCPROCEDURESMONITOR_CHECKS_CEV_OVERRIDE | TCPROCEDURESMONITOR_CHECKS_CEV_DISABLE))) LogTelecommandingChecks(pszOriginator, ((nFlags & (TCPROCEDURESMONITOR_CHECKS_CEV_OVERRIDE | TCPROCEDURESMONITOR_CHECKS_CEV_DISABLE)) == 0) ? ~(TCPROCEDURESMONITOR_CHECKS_CEV_OVERRIDE | TCPROCEDURESMONITOR_CHECKS_CEV_DISABLE) : (nFlags & (TCPROCEDURESMONITOR_CHECKS_CEV_OVERRIDE | TCPROCEDURESMONITOR_CHECKS_CEV_DISABLE)), bUser);
			UpdateBars();
			break;
		}
		return FALSE;
	}
	return TRUE;
}

UINT CTCProceduresMonitorWnd::GetTelecommandingChecks() CONST
{
	return m_wndView.GetTelecommandingChecks();
}

BOOL CTCProceduresMonitorWnd::SetTelecommandingState(UINT nState, BOOL bUser)
{
	CComputerToken  cComputerToken;

	return SetTelecommandingState(cComputerToken.GetComputerName(), nState, bUser);
}
BOOL CTCProceduresMonitorWnd::SetTelecommandingState(LPCTSTR pszOriginator, UINT nState, BOOL bUser)
{
	CComputerToken  cComputerToken(pszOriginator);
	CTCServiceLock  cLock(this);

	for (; nState != GetTelecommandingState(); )
	{
		if (m_wndView.SetTelecommandingState(nState) && (!cComputerToken.IsHost() || !lstrlen(pszOriginator) || GetTCService()->SetCommandSourceTelecommandingState(TCSERVICE_COMMANDSOURCETYPE_PROCEDURESMONITOR, nState) >= 0))
		{
			LogTelecommandingState(pszOriginator, nState, bUser);
			UpdateBars();
			break;
		}
		return FALSE;
	}
	return TRUE;
}

UINT CTCProceduresMonitorWnd::GetTelecommandingState() CONST
{
	return m_wndView.GetTelecommandingState();
}

BOOL CTCProceduresMonitorWnd::SetTelecommandingUplinkState(UINT nState)
{
	CTCServiceLock  cLock(this);

	if (nState != GetTelecommandingUplinkState())
	{
		m_wndView.SetTelecommandingUplinkState(nState);
		UpdateBars();
	}
	return TRUE;
}

UINT CTCProceduresMonitorWnd::GetTelecommandingUplinkState() CONST
{
	return m_wndView.GetTelecommandingUplinkState();
}

BOOL CTCProceduresMonitorWnd::EnableTelecommandingReleaseWaitMode(BOOL bEnable, BOOL bUser)
{
	CComputerToken  cComputerToken;

	return EnableTelecommandingReleaseWaitMode(cComputerToken.GetComputerName(), bEnable, bUser);
}
BOOL CTCProceduresMonitorWnd::EnableTelecommandingReleaseWaitMode(LPCTSTR pszOriginator, BOOL bEnable, BOOL bUser)
{
	CComputerToken  cComputerToken(pszOriginator);
	CTCServiceLock  cLock(this);

	for (; bEnable != IsTelecommandingReleaseWaitModeEnabled(); )
	{
		if (m_wndView.EnableTelecommandingReleaseWaitMode(bEnable) && (!cComputerToken.IsHost() || !lstrlen(pszOriginator) || GetTCService()->EnableCommandSourceTelecommandingReleaseWaitMode(TCSERVICE_COMMANDSOURCETYPE_PROCEDURESMONITOR, bEnable) >= 0))
		{
			LogTelecommandingReleaseWaitMode(pszOriginator, bEnable, bUser);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CTCProceduresMonitorWnd::IsTelecommandingReleaseWaitModeEnabled() CONST
{
	return m_wndView.IsTelecommandingReleaseWaitModeEnabled();
}

BOOL CTCProceduresMonitorWnd::InitializeTelecommand(INT nProcedureID, LPCTSTR pszThread, LPCTSTR pszStep, LPCTSTR pszFunction, INT nEntry, CTCItem *pTCItem)
{
	return m_wndView.InitializeTelecommand(nProcedureID, pszThread, pszStep, pszFunction, nEntry, pTCItem);
}

BOOL CTCProceduresMonitorWnd::EnumAuthorizableTelecommands(INT nIndex, CTCItems &pTCItems) CONST
{
	return m_wndView.EnumAuthorizableTelecommands(nIndex, pTCItems);
}

BOOL CTCProceduresMonitorWnd::AuthorizeTelecommands(INT nIndex, CONST CTCItems &pTCItems)
{
	return m_wndView.AuthorizeTelecommands(nIndex, pTCItems);
}
BOOL CTCProceduresMonitorWnd::AuthorizeTelecommands(CONST CTCItems &pTCItems)
{
	return m_wndView.AuthorizeTelecommands(pTCItems);
}

BOOL CTCProceduresMonitorWnd::CanAuthorizeTelecommands(INT nIndex) CONST
{
	return m_wndView.CanAuthorizeTelecommands(nIndex);
}

BOOL CTCProceduresMonitorWnd::DoResetInterlocks()
{
	CTCInterlocks  pInterlocks;

	if (m_dlgInterlocks.Create(this, pInterlocks) == IDOK)
	{
		LogResetInterlocks(pInterlocks);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorWnd::CanResetInterlocks() CONST
{
	return GetTCService()->CheckTCInterlocks(TCSERVICE_COMMANDSOURCETYPE_PROCEDURESMONITOR, TCINTERLOCK_STATE_SUCCESS) || GetTCService()->CheckTCInterlocks(TCSERVICE_COMMANDSOURCETYPE_PROCEDURESMONITOR, TCINTERLOCK_STATE_FAILURE);
}

BOOL CTCProceduresMonitorWnd::Start()
{
	Initialize(TRUE);
	UpdateAllPanes();
	return TRUE;
}

BOOL CTCProceduresMonitorWnd::Prepare(BOOL bDialog)
{
	return TRUE;
}

BOOL CTCProceduresMonitorWnd::Check() CONST
{
	return((CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorWnd::Update()
{
	if (!Check())
	{
		if (IsWindowVisible())
		{
			ReportEvent(USER_INFORMATIONAL_DISPLAY_ACCESS_VIOLATION);
			ActivateFrame(SW_HIDE);
			return;
		}
	}
	UpdateAllPanes();
	CDisplayWnd::Update();
}

BOOL CTCProceduresMonitorWnd::Stop()
{
	Initialize(FALSE);
	return TRUE;
}

BOOL CTCProceduresMonitorWnd::SaveInfo(INT nPage, INT nDisplay, LPCTSTR pszTitle, CONST PDISPLAYINFO pDisplayInfo)
{
	BOOL  bEvent;
	UINT  nCount;
	UINT  nPolicy;
	CSize  size[3];
	LOGFONT  sFontInfo[5];
	CString  szFileName[2];
	COLORREF  nColor[2];
	CTimeSpan  tRetention;
	DWORDLONG  dwRetention;
	CUIntArray  nColumns;
	CUIntArray  nWidths;
	CByteArray  nPrintInfo;
	CByteArray  nContentData;
	CProfile  cProfile;

	return((CDisplayWnd::SaveInfo(nPage, nDisplay, pszTitle, pDisplayInfo) && (nPage > 0 || (GetLayout(nColumns, nWidths, size[0], size[1], size[2]) && GetContents(nContentData) && GetListTitleFont(&sFontInfo[0]) && GetListItemsFont(&sFontInfo[1]) && GetItemFlowchartTitleFont(&sFontInfo[2]) && GetItemFlowchartLabelsFont(&sFontInfo[3]) && GetItemSourceCodeFont(&sFontInfo[4]) && GetItemFlowchartBackgroundColor(nColor[0]) && GetItemFlowchartLabelsColor(nColor[1]) && GetLoggingOptions(nPolicy, szFileName[0], dwRetention, tRetention, szFileName[1], nCount, bEvent) && GetPrintJobs(nPrintInfo) && cProfile.SetTCProceduresMonitorLayoutInfo(nPage, nDisplay, nColumns, nWidths, size[0], size[1], size[2], nColor[0], nColor[1], IsToolTipModeEnabled()) && cProfile.SetTCProceduresMonitorFontsInfo(nPage, nDisplay, &sFontInfo[0], &sFontInfo[1], &sFontInfo[2], &sFontInfo[3], &sFontInfo[4]) && cProfile.SetTCProceduresMonitorContentsInfo(nPage, nDisplay, nContentData, GetTelecommandingMode(), GetTelecommandingState(), GetTelecommandingChecks(), IsTelecommandingReleaseWaitModeEnabled()) && cProfile.SetTCProceduresMonitorLoggingInfo(nPage, nDisplay, nPolicy, szFileName[0], dwRetention, tRetention, szFileName[1], nCount, bEvent) && cProfile.SetTCProceduresMonitorPrintInfo(nPage, nDisplay, nPrintInfo)))) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorWnd::LoadInfo(INT nPage, INT nDisplay, CString &szTitle, PDISPLAYINFO pDisplayInfo)
{
	BOOL  bMode;
	BOOL  bEvent;
	BOOL  bToolTips;
	UINT  nCount;
	UINT  nPolicy;
	UINT  nFlags[3];
	CSize  size[3];
	LOGFONT  sFontInfo[5];
	CString  szFileName[2];
	COLORREF  nColor[2];
	CTimeSpan  tRetention;
	DWORDLONG  dwRetention;
	CUIntArray  nColumns;
	CUIntArray  nWidths;
	CByteArray  nPrintInfo;
	CByteArray  nContentData;
	CProfile  cProfile;

	return((CDisplayWnd::LoadInfo(nPage, nDisplay, szTitle, pDisplayInfo) && (nPage > 0 || (cProfile.GetTCProceduresMonitorLayoutInfo(nPage, nDisplay, nColumns, nWidths, size[0], size[1], size[2], nColor[0], nColor[1], bToolTips) && cProfile.GetTCProceduresMonitorFontsInfo(nPage, nDisplay, &sFontInfo[0], &sFontInfo[1], &sFontInfo[2], &sFontInfo[3], &sFontInfo[4]) && cProfile.GetTCProceduresMonitorContentsInfo(nPage, nDisplay, nContentData, nFlags[0], nFlags[1], nFlags[2], bMode) && cProfile.GetTCProceduresMonitorLoggingInfo(nPage, nDisplay, nPolicy, szFileName[0], dwRetention, tRetention, szFileName[1], nCount, bEvent) && cProfile.GetTCProceduresMonitorPrintInfo(nPage, nDisplay, nPrintInfo) && SetLayout(nColumns, nWidths, size[0], size[1], size[2]) && EnableToolTipMode(bToolTips) && SetListTitleFont(&sFontInfo[0]) && SetListItemsFont(&sFontInfo[1]) && SetItemFlowchartTitleFont(&sFontInfo[2]) && SetItemFlowchartLabelsFont(&sFontInfo[3]) && SetItemSourceCodeFont(&sFontInfo[4]) && SetItemFlowchartBackgroundColor(nColor[0]) && SetItemFlowchartLabelsColor(nColor[1]) && SetContents(nContentData) && SetTelecommandingMode(nFlags[0]) && SetTelecommandingState(nFlags[1]) && SetTelecommandingChecks(nFlags[2]) && EnableTelecommandingReleaseWaitMode(bMode) && SetLoggingOptions(nPolicy, szFileName[0], dwRetention, tRetention, szFileName[1], nCount, bEvent) && SetPrintJobs(nPrintInfo)))) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorWnd::SetLayoutInfo(LPCVOID pData)
{
	INT  cbData;
	DATA  sData;
	CUIntArray  nColumns;
	CUIntArray  nWidths;
	CTCServiceLock  cLock(this);

	if (GetScope() == DISPLAY_SCOPE_GLOBAL)
	{
		for (CopyMemory(&sData, pData, ((cbData = (INT)GlobalSize((HGLOBAL)pData)) >= sizeof(DATA)) ? sizeof(DATA) : 0); cbData >= sizeof(DATA) && sData.cbSize == sizeof(DATA) + sData.cbColumns[0] + sData.cbColumns[1] && sData.cbColumns[0] >= 0 && sData.cbColumns[1] >= 0; )
		{
			for (nColumns.SetSize(sData.cbColumns[0] / sizeof(UINT)), nWidths.SetSize(sData.cbColumns[1] / sizeof(UINT)), CopyMemory(nColumns.GetData(), (LPBYTE)pData + (cbData = sizeof(DATA)), sData.cbColumns[0]), CopyMemory(nWidths.GetData(), (LPBYTE)pData + (cbData = cbData + sData.cbColumns[0]), sData.cbColumns[1]); SetLayoutInfo(nColumns, nWidths, sData.sizePanes[0], sData.sizePanes[1], sData.sizePanes[2], &sData.sFont[0], &sData.sFont[1], &sData.sFont[2], &sData.sFont[3], sData.nColor[0], sData.nColor[1], sData.nIndex, sData.nThreadID, &sData.sScrollInfo[0], &sData.sScrollInfo[1]); ) return TRUE;
			break;
		}
		return FALSE;
	}
	return TRUE;
}

INT CTCProceduresMonitorWnd::GetLayoutInfo(LPVOID *pData) CONST
{
	INT  cbData;
	DATA  sData;
	LPVOID  pBlock;
	CSize  sizePanes[3];
	CUIntArray  nColumns;
	CUIntArray  nWidths;
	CTCServiceLock  cLock(this);

	if (GetScope() == DISPLAY_SCOPE_GLOBAL)
	{
		if (GetLayoutInfo(nColumns, nWidths, sizePanes[0], sizePanes[1], sizePanes[2], &sData.sFont[0], &sData.sFont[1], &sData.sFont[2], &sData.sFont[3], sData.nColor[0], sData.nColor[1], sData.nIndex, sData.nThreadID, &sData.sScrollInfo[0], &sData.sScrollInfo[1]))
		{
			for (sData.cbColumns[0] = (INT)(nColumns.GetSize()*sizeof(UINT)), sData.cbColumns[1] = (INT)(nWidths.GetSize()*sizeof(UINT)), sData.sizePanes[0].cx = sizePanes[0].cx, sData.sizePanes[0].cy = sizePanes[0].cy, sData.sizePanes[1].cx = sizePanes[1].cx, sData.sizePanes[1].cy = sizePanes[1].cy, sData.sizePanes[2].cx = sizePanes[2].cx, sData.sizePanes[2].cy = sizePanes[2].cy, sData.cbSize = sizeof(DATA) + sData.cbColumns[0] + sData.cbColumns[1]; (pBlock = (pData != (LPVOID *)NULL) ? (LPVOID)GlobalReAlloc(*pData, sData.cbSize, GMEM_MOVEABLE | GMEM_ZEROINIT) : (LPVOID)NULL); )
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

BOOL CTCProceduresMonitorWnd::QueryDefaultInfo(PDISPLAYINFO pDefaultInfo) CONST
{
	pDefaultInfo->ptWnd.x = 0;
	pDefaultInfo->ptWnd.y = 0;
	pDefaultInfo->nNumber = -1;
	pDefaultInfo->rWnd = rectDefault;
	pDefaultInfo->nScope = DISPLAY_SCOPE_GLOBAL;
	pDefaultInfo->nMode = DISPLAY_MODE_REALTIME;
	pDefaultInfo->pData = (LPVOID)NULL;
	pDefaultInfo->nShow = SW_SHOWNORMAL;
	pDefaultInfo->bShow = TRUE;
	return TRUE;
}

BOOL CTCProceduresMonitorWnd::QueryDefaultMenu(CLocaleMenu &cMenu, CImageList &cImages, CUIntArray &nImageIDs) CONST
{
	INT  nIndex;
	INT  nCount;
	INT  iImage;
	UINT  nButtonID;
	UINT  nButtonStyle;
	CBitmap  cBitmap;
	BITMAP  sBitmap;

	for (cImages.DeleteImageList(), nImageIDs.RemoveAll(); cBitmap.LoadBitmap(IDB_TCPROCEDURESMONITORFRAMESMALLIMAGES) && cBitmap.GetBitmap(&sBitmap); )
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
	return cMenu.LoadMenu(IDR_TCPROCEDURESMONITORFRAME);
}

VOID CTCProceduresMonitorWnd::UpdateBars()
{
	CTCServiceLock  cLock(this);

	UpdateToolBar();
	UpdateMessagePane();
	UpdateUplinkPane();
	UpdatePreexecutionVerificationPane();
	UpdateExecutionVerificationPane();
	UpdateStatePane();
}

BOOL CTCProceduresMonitorWnd::Print(PRINTDLG *pPrintInfo)
{
	INT  nJob;
	INT  nJobs;
	CTCProceduresMonitorPrintJobs  pJobs;
	CTCProceduresMonitorPrintJobInfo  *pJobInfo;
	CTCServiceLock  cLock(this);

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
		if (pJobInfo->GetPrintMode() & TCPROCEDURESMONITOR_PRINT_CLEARCOMMENTS)
		{
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~TCPROCEDURESMONITOR_PRINT_CLEARCOMMENTS);
			pJobInfo->SetComments(EMPTYSTRING);
			SetPrintJobs(pJobs);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorWnd::CanPrint() CONST
{
	return((GetProcedureCount() > 0) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorWnd::SetLoggingOptions()
{
	CString  szFileName;
	CEventLog  cEventLog;
	CFileFindEx  cFileFind;
	CLogicalDrives  cDrives;
	CTCServiceLock  cLock(this);

	if (cEventLog.SetOwner(GetAccountComputerName(), GetAccountSpacecraftName(), GetAccountUserName()))
	{
		if (cEventLog.QuerySpacecraftLogFileName(szFileName) && cFileFind.FindFile(szFileName) && !cFileFind.FindNextFile())
		{
			m_szLoggingFileName[0] = m_szLoggingFileName[1] = (cFileFind.GetRoot().Right(1).GetAt(0) != cDrives.GetPathDelimiter()) ? (cFileFind.GetRoot() + cDrives.GetPathDelimiter() + STRING(IDS_TCPROCEDURESMONITOR_LOGFILE_DEFAULTFILENAME)) : (cFileFind.GetRoot() + STRING(IDS_TCPROCEDURESMONITOR_LOGFILE_DEFAULTFILENAME));
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
BOOL CTCProceduresMonitorWnd::SetLoggingOptions(UINT nArchivalPolicy, LPCTSTR pszArchivalFileName, DWORDLONG dwArchivalRetention, CONST CTimeSpan &tArchivalRetention, LPCTSTR pszRetrievalFileName, UINT nRetrievalReloadCount, BOOL bShowAsEvent)
{
	CTCServiceLock  cLock(this);

	m_nLoggingPolicy = nArchivalPolicy;
	m_szLoggingFileName[0] = pszArchivalFileName;
	m_szLoggingFileName[1] = pszRetrievalFileName;
	m_dwLoggingRetention = dwArchivalRetention;
	m_tLoggingRetention = tArchivalRetention;
	m_nLoggingReloadCount = nRetrievalReloadCount;
	m_bLoggingAsEvent = bShowAsEvent;
	return TRUE;
}

BOOL CTCProceduresMonitorWnd::GetLoggingOptions(UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST
{
	CTCServiceLock  cLock(this);

	nArchivalPolicy = m_nLoggingPolicy;
	szArchivalFileName = m_szLoggingFileName[0];
	szRetrievalFileName = m_szLoggingFileName[1];
	dwArchivalRetention = m_dwLoggingRetention;
	tArchivalRetention = m_tLoggingRetention;
	nRetrievalReloadCount = m_nLoggingReloadCount;
	bShowAsEvent = m_bLoggingAsEvent;
	return TRUE;
}

BOOL CTCProceduresMonitorWnd::LogActivity(CONST CTCLogEntry *pEntry)
{
	CString  szLog[2];
	CString  szMessage;
	CLogFile  cLogFile;
	CTimeKey  tLogTime;
	CByteArray  nLogData;
	CEventObject  *pEvent;
	CTCServiceLock  cLock(this);

	if (m_bLoggingAsEvent)
	{
		for (szLog[0].Format(STRING(IDS_TCPROCEDURESMONITOR_LOGEVENTMESSAGE_FORMAT), STRING(IDS_TCPROCEDURESMONITOR_LOGOBJECT_SOURCE), (LPCTSTR)pEntry->GetDescription(), (LPCTSTR)pEntry->GetActivity()), szLog[1].Format(STRING(IDS_TCPROCEDURESMONITOR_LOGSHORTEVENTMESSAGE_FORMAT), STRING(IDS_TCPROCEDURESMONITOR_LOGOBJECT_SOURCE), (pEntry->GetActivity().IsEmpty()) ? (LPCTSTR)pEntry->GetDescription() : (LPCTSTR)pEntry->GetActivity()), szMessage = (!pEntry->GetDescription().IsEmpty() && !pEntry->GetActivity().IsEmpty()) ? szLog[0] : szLog[1]; (pEvent = new CEventObject); )
		{
			pEvent->SetCategory(EVENT_CATEGORY_USER);
			pEvent->SetType(STRING(IDS_EVENTTYPE_INFORMATIONAL));
			pEvent->SetSubtype(STRING(IDS_TCPROCEDURESMONITOR_LOGOBJECT_SOURCE));
			pEvent->SetMessage(szMessage);
			pEvent->SetComments(EMPTYSTRING);
			pEvent->SetUser(pEntry->GetUser());
			pEvent->SetAuditTime(pEntry->GetTime());
			pEvent->SetAuditColor(VGA_COLOR_BLACK);
			pEvent->Acknowledge();
			pEvent->Show(TRUE);
			ReportEvent(pEvent);
			break;
		}
	}
	if ((m_nLoggingPolicy & LOGFILE_POLICY_DISABLED) != LOGFILE_POLICY_DISABLED)
	{
		if (cLogFile.Open(m_szLoggingFileName[0], GetAccountSpacecraftName(), STRING(IDS_LOGFILETYPE_TCLOG), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite))
		{
			if (pEntry->Map(nLogData) && cLogFile.Write(tLogTime, nLogData))
			{
				cLogFile.Close();
				return TRUE;
			}
			cLogFile.Close();
		}
	}
	return FALSE;
}

BOOL CTCProceduresMonitorWnd::SetPrintJobs(CONST CTCProceduresMonitorPrintJobs &pPrintJobs)
{
	CTCServiceLock  cLock(this);

	return m_pPrintJobs.Copy(&pPrintJobs);
}

BOOL CTCProceduresMonitorWnd::GetPrintJobs(CTCProceduresMonitorPrintJobs &pPrintJobs) CONST
{
	CTCServiceLock  cLock(this);

	return pPrintJobs.Copy(&m_pPrintJobs);
}

BOOL CTCProceduresMonitorWnd::Print(CONST CTCProceduresMonitorPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo)
{
	CDC  cDC;
	BOOL  bMetric;
	RECT  rtMargin[2];
	SIZE  ptPaperSize;
	LOGFONT  lfFont[2];
	DEVMODE  *pDevMode;
	DEVNAMES  *pDevNames;
	CPtrArray  pThreadMetaDCs;
	CPtrArray  pSymbols;
	CUIntArray  nSymbolIDs;
	CMetaFileDC  *pThreadMetaDC;
	CStringArray  szThreads;
	CStringArray  szColumns;
	CStringArray  szContents;
	CPrintProfiles  cPrintProfiles;
	CPrintProfileInfo  *pPrintProfileInfo;
	CTextViewAttributes  pAttributes;

	if ((pPrintProfileInfo = (GetPrintProfiles(cPrintProfiles)) ? cPrintProfiles.GetAt(cPrintProfiles.Find(pJobInfo->GetProfile())) : (CPrintProfileInfo *)NULL) && pPrintProfileInfo->GetPaperInfo(ptPaperSize, rtMargin[0], rtMargin[1], bMetric))
	{
		if (GetPrintProperties(pJobInfo, szColumns, szContents, pAttributes, szThreads, pThreadMetaDCs, &lfFont[0], &lfFont[1], pSymbols, nSymbolIDs))
		{
			if (pPrintInfo == (PRINTDLG *)NULL)
			{
				if (CreatePrinterDC(pPrintProfileInfo, cDC))
				{
					if (PrintJob(cDC, pJobInfo, pPrintProfileInfo->GetPrinterName(), 0, 0, rtMargin[0], bMetric, szColumns, szContents, pAttributes, szThreads, pThreadMetaDCs, &lfFont[0], &lfFont[1], pSymbols, nSymbolIDs))
					{
						cDC.DeleteDC();
						return TRUE;
					}
					cDC.DeleteDC();
				}
				while (pThreadMetaDCs.GetSize() > 0)
				{
					if ((pThreadMetaDC = (CMetaFileDC *)pThreadMetaDCs.GetAt(0))) delete pThreadMetaDC;
					pThreadMetaDCs.RemoveAt(0);
				}
				return FALSE;
			}
			if ((pDevNames = (DEVNAMES *)GlobalLock(pPrintInfo->hDevNames)))
			{
				if ((pDevMode = (DEVMODE *)GlobalLock(pPrintInfo->hDevMode)))
				{
					if (CreatePrinterDC(pPrintInfo->hDevNames, pPrintInfo->hDevMode, cDC))
					{
						if (PrintJob(cDC, pJobInfo, (LPCTSTR)pDevMode->dmDeviceName, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nFromPage : 0, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nToPage : 0, rtMargin[0], bMetric, szColumns, szContents, pAttributes, szThreads, pThreadMetaDCs, &lfFont[0], &lfFont[1], pSymbols, nSymbolIDs))
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
			while (pThreadMetaDCs.GetSize() > 0)
			{
				if ((pThreadMetaDC = (CMetaFileDC *)pThreadMetaDCs.GetAt(0))) delete pThreadMetaDC;
				pThreadMetaDCs.RemoveAt(0);
			}
		}
	}
	return FALSE;
}

CTCProceduresMonitorListView *CTCProceduresMonitorWnd::GetListView() CONST
{
	return m_wndView.GetListView();
}

CTCProceduresMonitorItemView *CTCProceduresMonitorWnd::GetItemView() CONST
{
	return m_wndView.GetItemView();
}

BOOL CTCProceduresMonitorWnd::CreateToolBar()
{
	if (m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndToolBar.LoadToolBar(IDB_TCPROCEDURESMONITORFRAMELARGEIMAGES, 0, IDB_TCPROCEDURESMONITORFRAMESMALLIMAGES, TRUE))
	{
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCPROCEDURESMONITORSETTINGS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCPROCEDURESMONITORDETAILS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCPROCEDURESMONITORAUTHORIZATIONS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCPROCEDURESMONITORSTART), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCPROCEDURESMONITORSUSPEND), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCPROCEDURESMONITORSTEPINTO), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCPROCEDURESMONITORSTEPOVER), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCPROCEDURESMONITORSTEPOUT), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCPROCEDURESMONITORABORT), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCPROCEDURESMONITORRESET), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCPROCEDURESMONITORRESETINTERLOCKS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCPROCEDURESMONITORRELEASEWAITMODE), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCPROCEDURESMONITORPRINT), TBBS_DISABLED);
		DockPane(&m_wndToolBar);
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorWnd::CreateStatusBar()
{
	if (m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndStatusBar.SetIndicators(nTCProceduresMonitorStatusBarIndicators, 1))
	{
		m_wndStatusBar.EnableToolTips();
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorWnd::CreateView()
{
	if (m_wndView.Create(this))
	{
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorWnd::Customize(BOOL bDefault)
{
	CByteArray  nPrintInfo;

	return(((!bDefault  &&  GetPrintJobs(nPrintInfo) && nPrintInfo.GetSize() > 0) || SetPrintJobs(nPrintInfo)) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorWnd::UpdateToolBar()
{
	INT  nIndex;
	BOOL  bRunning;
	BOOL  bDisabled;
	BOOL  bSuspended;

	for (bRunning = IsProcedureRunning((nIndex = GetCurProcedure())), bSuspended = IsProcedureSuspended(nIndex), bDisabled = IsProcedureDisabled(nIndex); IsInitialized() && IsMonitoring(); )
	{
		m_wndToolBar.EnableButton(IDM_TCPROCEDURESMONITORSTART, nIndex >= 0 && (!bRunning || bSuspended) && !bDisabled  &&  CanStartProcedure(nIndex));
		m_wndToolBar.EnableButton(IDM_TCPROCEDURESMONITORSUSPEND, bRunning  &&  !bSuspended  &&  CanBreakProcedure(nIndex));
		m_wndToolBar.EnableButton(IDM_TCPROCEDURESMONITORSTEPINTO, bRunning  &&  bSuspended  &&  CanStepIntoProcedure(nIndex));
		m_wndToolBar.EnableButton(IDM_TCPROCEDURESMONITORSTEPOVER, bRunning  &&  bSuspended  &&  CanStepOverProcedure(nIndex));
		m_wndToolBar.EnableButton(IDM_TCPROCEDURESMONITORSTEPOUT, bRunning  &&  bSuspended  &&  CanStepOutProcedure(nIndex));
		m_wndToolBar.EnableButton(IDM_TCPROCEDURESMONITORABORT, bRunning  &&  CanBreakProcedure(nIndex));
		m_wndToolBar.EnableButton(IDM_TCPROCEDURESMONITORRESET, nIndex >= 0 && !bRunning  &&  CanResetProcedure(nIndex));
		break;
	}
}

BOOL CTCProceduresMonitorWnd::UpdateAllPanes()
{
	INT  nPane;
	INT  nPanes;

	for (nPane = 0, nPanes = sizeof(nTCProceduresMonitorStatusBarIndicators) / sizeof(UINT); nPane < nPanes; nPane++)
	{
		if (m_wndStatusBar.CommandToIndex(nTCProceduresMonitorStatusBarIndicators[nPane]) != nPane) break;
		continue;
	}
	if (nPane < nPanes)
	{
		if (m_wndStatusBar.SetIndicators(nTCProceduresMonitorStatusBarIndicators, sizeof(nTCProceduresMonitorStatusBarIndicators) / sizeof(UINT)))
		{
			UpdateBars();
			return TRUE;
		}
		return FALSE;
	}
	UpdateBars();
	return TRUE;
}

VOID CTCProceduresMonitorWnd::UpdateMessagePane()
{
	UINT  nCount;
	CString  szMessage;

	szMessage.Format(((nCount = GetProcedureCount()) > 0) ? ((nCount > 1) ? STRING(IDS_TCPROCEDURESMONITOR_STATUSBAR_UPDATEMESSAGE) : STRING(IDS_TCPROCEDURESMONITOR_STATUSBAR_DATAMESSAGE)) : STRING(IDS_TCPROCEDURESMONITOR_STATUSBAR_NODATAMESSAGE), nCount);
	m_wndStatusBar.SetPaneText(ID_TCPROCEDURESMONITOR_STATUSBAR_MESSAGEPANE, szMessage);
}

VOID CTCProceduresMonitorWnd::UpdateUplinkPane()
{
	m_wndStatusBar.SetPaneText(ID_TCPROCEDURESMONITOR_STATUSBAR_UPLINKPANE, ((GetTelecommandingUplinkState() & (TCSERVICE_COMMANDHANDLERSTATE_LINK_GOOD | TCSERVICE_COMMANDHANDLERSTATE_FRONTENDLINK_GOOD | TCSERVICE_COMMANDHANDLERSTATE_FRONTEND_OK)) == (TCSERVICE_COMMANDHANDLERSTATE_LINK_GOOD | TCSERVICE_COMMANDHANDLERSTATE_FRONTENDLINK_GOOD | TCSERVICE_COMMANDHANDLERSTATE_FRONTEND_OK)) ? STRING(IDS_TCPROCEDURESMONITOR_STATUSBAR_UPLINK_OK) : STRING(IDS_TCPROCEDURESMONITOR_STATUSBAR_UPLINK_NOTOK), ((GetTelecommandingUplinkState() & (TCSERVICE_COMMANDHANDLERSTATE_LINK_GOOD | TCSERVICE_COMMANDHANDLERSTATE_FRONTENDLINK_GOOD | TCSERVICE_COMMANDHANDLERSTATE_FRONTEND_OK)) != (TCSERVICE_COMMANDHANDLERSTATE_LINK_GOOD | TCSERVICE_COMMANDHANDLERSTATE_FRONTENDLINK_GOOD | TCSERVICE_COMMANDHANDLERSTATE_FRONTEND_OK)) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorWnd::UpdatePreexecutionVerificationPane()
{
	UINT  nFlags;

	m_wndStatusBar.SetPaneText(ID_TCPROCEDURESMONITOR_STATUSBAR_PEVPANE, (((nFlags = GetTelecommandingChecks()) & (TCPROCEDURESMONITOR_CHECKS_PEV_OVERRIDE | TCPROCEDURESMONITOR_CHECKS_PEV_DISABLE)) == 0) ? STRING(IDS_TCPROCEDURESMONITOR_STATUSBAR_PEV_ON) : (((nFlags & TCPROCEDURESMONITOR_CHECKS_PEV_DISABLE) == 0) ? STRING(IDS_TCPROCEDURESMONITOR_STATUSBAR_PEV_OVERRIDE) : STRING(IDS_TCPROCEDURESMONITOR_STATUSBAR_PEV_OFF)), (GetTelecommandingChecks() & (TCPROCEDURESMONITOR_CHECKS_PEV_OVERRIDE | TCPROCEDURESMONITOR_CHECKS_PEV_DISABLE)) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorWnd::UpdateExecutionVerificationPane()
{
	UINT  nFlags;

	m_wndStatusBar.SetPaneText(ID_TCPROCEDURESMONITOR_STATUSBAR_CEVPANE, (((nFlags = GetTelecommandingChecks()) & (TCPROCEDURESMONITOR_CHECKS_CEV_OVERRIDE | TCPROCEDURESMONITOR_CHECKS_CEV_DISABLE)) == 0) ? STRING(IDS_TCPROCEDURESMONITOR_STATUSBAR_CEV_ON) : (((nFlags & TCPROCEDURESMONITOR_CHECKS_CEV_DISABLE) == 0) ? STRING(IDS_TCPROCEDURESMONITOR_STATUSBAR_CEV_OVERRIDE) : STRING(IDS_TCPROCEDURESMONITOR_STATUSBAR_CEV_OFF)), (GetTelecommandingChecks() & (TCPROCEDURESMONITOR_CHECKS_CEV_OVERRIDE | TCPROCEDURESMONITOR_CHECKS_CEV_DISABLE)) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorWnd::UpdateStatePane()
{
	UINT  nState;

	m_wndStatusBar.SetPaneText(ID_TCPROCEDURESMONITOR_STATUSBAR_STATEPANE, (((nState = GetTelecommandingState()) & TCPROCEDURESMONITOR_STATE_DEFAULT) != TCPROCEDURESMONITOR_STATE_DEFAULT) ? ((nState & TCPROCEDURESMONITOR_STATE_DISABLED) ? STRING(IDS_TCPROCEDURESMONITOR_STATUSBAR_STATE_DISABLED) : STRING(IDS_TCPROCEDURESMONITOR_STATUSBAR_STATE_ILLEGAL)) : ((nState & TCPROCEDURESMONITOR_STATE_DISABLED) ? STRING(IDS_TCPROCEDURESMONITOR_STATUSBAR_STATE_DISABLED) : STRING(IDS_TCPROCEDURESMONITOR_STATUSBAR_STATE_DEFAULT)), (((nState = GetTelecommandingState()) & TCPROCEDURESMONITOR_STATE_DEFAULT) != TCPROCEDURESMONITOR_STATE_DEFAULT || (nState & TCPROCEDURESMONITOR_STATE_DISABLED)) ? TRUE : FALSE);
}

VOID CTCProceduresMonitorWnd::UpdateContents(BOOL bAll)
{
	m_wndView.UpdateContents(bAll);
}

BOOL CTCProceduresMonitorWnd::LogProcedures(CONST CTCProceduresMonitorItems &pItems, CONST CTCProceduresMonitorItems &pProcedures)
{
	INT  nItem[3];
	INT  nItems[3];
	INT  nCount[2];
	CString  szActivity;
	CTCLogEntry  cEntry;
	CTCProceduresMonitorItem  *pItem[2];

	if (IsInitialized())
	{
		for (nItem[0] = 0, nItems[0] = (INT)pItems.GetSize(); nItem[0] < nItems[0]; nItem[0]++)
		{
			for (nItem[1] = 0, nItems[1] = ((pItem[0] = pItems.GetAt(nItem[0]))) ? (INT)pProcedures.GetSize() : -1, szActivity.Format(STRING(IDS_TCPROCEDURESMONITOR_LOGOPERATION_PROCEDURE), (nItems[1] >= 0) ? (LPCTSTR)pItem[0]->GetName() : EMPTYSTRING); nItem[1] < nItems[1]; nItem[1]++)
			{
				if ((pItem[1] = pProcedures.GetAt(nItem[1])) && pItem[0]->Compare(pItem[1])) break;
				continue;
			}
			for (nItem[2] = 0, nItems[2] = (nItem[1] == nItems[1]) ? nItem[0] : 0, nCount[0] = 0; nItem[2] < nItems[2]; nItem[2]++)
			{
				if ((pItem[1] = pItems.GetAt(nItem[2])) && pItem[0]->GetName() == pItem[1]->GetName())
				{
					nCount[0]++;
					continue;
				}
			}
			for (nItem[2] = 0, nItems[2] = (nItem[1] == nItems[1]) ? nItems[1] : 0, nCount[1] = 0; nItem[2] < nItems[2]; nItem[2]++)
			{
				if ((pItem[1] = pProcedures.GetAt(nItem[2])) && pItem[0]->GetName() == pItem[1]->GetName())
				{
					nCount[1]++;
					continue;
				}
			}
			if (nItem[1] == nItems[1])
			{
				if (nCount[0] < nCount[1])
				{
					cEntry.SetName(STRING(IDS_TCPROCEDURESMONITOR_LOGOBJECT_SOURCE));
					cEntry.SetDescription(STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_CONTENTSCHANGE));
					cEntry.SetActivity(CString(STRING(IDS_TCPROCEDURESMONITOR_LOGACTIVITY_CHANGING)) + SPACE + szActivity);
					cEntry.SetTime(CTime::GetCurrentTime().GetTime());
					cEntry.SetUser(GetAccountUserName());
					LogActivity(&cEntry);
					continue;
				}
				cEntry.SetName(STRING(IDS_TCPROCEDURESMONITOR_LOGOBJECT_SOURCE));
				cEntry.SetDescription(STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_CONTENTSCHANGE));
				cEntry.SetActivity(CString(STRING(IDS_TCPROCEDURESMONITOR_LOGACTIVITY_ADDING)) + SPACE + szActivity);
				cEntry.SetTime(CTime::GetCurrentTime().GetTime());
				cEntry.SetUser(GetAccountUserName());
				LogActivity(&cEntry);
			}
		}
		for (nItem[0] = 0, nItems[0] = (INT)pProcedures.GetSize(); nItem[0] < nItems[0]; nItem[0]++)
		{
			for (nItem[1] = 0, nItems[1] = ((pItem[0] = pProcedures.GetAt(nItem[0]))) ? (INT)pItems.GetSize() : -1, szActivity.Format(STRING(IDS_TCPROCEDURESMONITOR_LOGOPERATION_PROCEDURE), (nItems[1] >= 0) ? (LPCTSTR)pItem[0]->GetName() : EMPTYSTRING); nItem[1] < nItems[1]; nItem[1]++)
			{
				if ((pItem[1] = pItems.GetAt(nItem[1])) && pItem[0]->Compare(pItem[1])) break;
				continue;
			}
			for (nItem[2] = 0, nItems[2] = (nItem[1] == nItems[1]) ? nItem[0] : 0, nCount[0] = 0; nItem[2] < nItems[2]; nItem[2]++)
			{
				if ((pItem[1] = pProcedures.GetAt(nItem[2])) && pItem[0]->GetName() == pItem[1]->GetName())
				{
					nCount[0]++;
					continue;
				}
			}
			for (nItem[2] = 0, nItems[2] = (nItem[1] == nItems[1]) ? nItems[1] : 0, nCount[1] = 0; nItem[2] < nItems[2]; nItem[2]++)
			{
				if ((pItem[1] = pItems.GetAt(nItem[2])) && pItem[0]->GetName() == pItem[1]->GetName())
				{
					nCount[1]++;
					continue;
				}
			}
			if (nItem[1] == nItems[1])
			{
				if (nCount[0] >= nCount[1])
				{
					cEntry.SetName(STRING(IDS_TCPROCEDURESMONITOR_LOGOBJECT_SOURCE));
					cEntry.SetDescription(STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_CONTENTSCHANGE));
					cEntry.SetActivity(CString(STRING(IDS_TCPROCEDURESMONITOR_LOGACTIVITY_REMOVING)) + SPACE + szActivity);
					cEntry.SetTime(CTime::GetCurrentTime().GetTime());
					cEntry.SetUser(GetAccountUserName());
					LogActivity(&cEntry);
				}
			}
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorWnd::LogTelecommandingMode(LPCTSTR pszOriginator, UINT nMode, BOOL bUser)
{
	CTCLogEntry  cEntry;
	CComputerToken  cComputerToken(pszOriginator);

	if (IsInitialized())
	{
		for (cEntry.SetName(STRING(IDS_TCPROCEDURESMONITOR_LOGOBJECT_SOURCE)); nMode & TCPROCEDURESMONITOR_MODE_DEFAULT; )
		{
			cEntry.SetActivity(CString(STRING(IDS_TCPROCEDURESMONITOR_LOGACTIVITY_ENABLING)) + SPACE + STRING(IDS_TCPROCEDURESMONITOR_LOGOPERATION_DEFAULTMODE));
			cEntry.SetDescription(STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_MODECHANGE));
			break;
		}
		cEntry.SetUser((cComputerToken.IsHost()) ? ((bUser) ? GetAccountUserName() : STRING(IDS_TCPROCEDURESMONITOR_LOGUSER_UNKNOWN)) : cComputerToken.GetComputerName());
		cEntry.SetTime(CTime::GetCurrentTime().GetTime());
		return LogActivity(&cEntry);
	}
	return FALSE;
}

BOOL CTCProceduresMonitorWnd::LogTelecommandingState(LPCTSTR pszOriginator, UINT nState, BOOL bUser)
{
	CTCLogEntry  cEntry;
	CComputerToken  cComputerToken(pszOriginator);

	if (IsInitialized())
	{
		for (cEntry.SetName(STRING(IDS_TCPROCEDURESMONITOR_LOGOBJECT_SOURCE)); nState & TCPROCEDURESMONITOR_STATE_DEFAULT; )
		{
			cEntry.SetDescription(STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_STATECHANGE));
			cEntry.SetActivity(STRING(IDS_TCPROCEDURESMONITOR_LOGACTIVITY_RESUMED));
			break;
		}
		if (nState & TCPROCEDURESMONITOR_STATE_DISABLED)
		{
			cEntry.SetDescription(STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_STATECHANGE));
			cEntry.SetActivity(STRING(IDS_TCPROCEDURESMONITOR_LOGACTIVITY_DISABLED));
		}
		cEntry.SetUser((cComputerToken.IsHost()) ? ((bUser) ? GetAccountUserName() : STRING(IDS_TCPROCEDURESMONITOR_LOGUSER_UNKNOWN)) : cComputerToken.GetComputerName());
		cEntry.SetTime(CTime::GetCurrentTime().GetTime());
		return LogActivity(&cEntry);
	}
	return FALSE;
}

BOOL CTCProceduresMonitorWnd::LogTelecommandingChecks(LPCTSTR pszOriginator, UINT nFlags, BOOL bUser)
{
	CTCLogEntry  cEntry;
	CComputerToken  cComputerToken(pszOriginator);

	if (IsInitialized())
	{
		for (cEntry.SetName(STRING(IDS_TCPROCEDURESMONITOR_LOGOBJECT_SOURCE)); nFlags == ~(TCPROCEDURESMONITOR_CHECKS_PEV_OVERRIDE | TCPROCEDURESMONITOR_CHECKS_PEV_DISABLE); )
		{
			cEntry.SetActivity(CString(STRING(IDS_TCPROCEDURESMONITOR_LOGACTIVITY_ENABLING)) + SPACE + STRING(IDS_TCPROCEDURESMONITOR_LOGOPERATION_PEVCHECKS));
			cEntry.SetDescription(STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_CHECKSCHANGE));
			break;
		}
		if (nFlags == ~(TCPROCEDURESMONITOR_CHECKS_CEV_OVERRIDE | TCPROCEDURESMONITOR_CHECKS_CEV_DISABLE))
		{
			cEntry.SetActivity(CString(STRING(IDS_TCPROCEDURESMONITOR_LOGACTIVITY_ENABLING)) + SPACE + STRING(IDS_TCPROCEDURESMONITOR_LOGOPERATION_CEVCHECKS));
			cEntry.SetDescription(STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_CHECKSCHANGE));
		}
		if (cEntry.GetActivity().IsEmpty())
		{
			if (nFlags & TCPROCEDURESMONITOR_CHECKS_PEV_OVERRIDE)
			{
				cEntry.SetActivity(CString(STRING(IDS_TCPROCEDURESMONITOR_LOGACTIVITY_OVERRIDING)) + SPACE + STRING(IDS_TCPROCEDURESMONITOR_LOGOPERATION_PEVCHECKS));
				cEntry.SetDescription(STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_CHECKSCHANGE));
			}
			if (nFlags & TCPROCEDURESMONITOR_CHECKS_CEV_OVERRIDE)
			{
				cEntry.SetActivity(CString(STRING(IDS_TCPROCEDURESMONITOR_LOGACTIVITY_OVERRIDING)) + SPACE + STRING(IDS_TCPROCEDURESMONITOR_LOGOPERATION_CEVCHECKS));
				cEntry.SetDescription(STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_CHECKSCHANGE));
			}
			if (nFlags & TCPROCEDURESMONITOR_CHECKS_PEV_DISABLE)
			{
				cEntry.SetActivity(CString(STRING(IDS_TCPROCEDURESMONITOR_LOGACTIVITY_DISABLING)) + SPACE + STRING(IDS_TCPROCEDURESMONITOR_LOGOPERATION_PEVCHECKS));
				cEntry.SetDescription(STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_CHECKSCHANGE));
			}
			if (nFlags & TCPROCEDURESMONITOR_CHECKS_CEV_DISABLE)
			{
				cEntry.SetActivity(CString(STRING(IDS_TCPROCEDURESMONITOR_LOGACTIVITY_DISABLING)) + SPACE + STRING(IDS_TCPROCEDURESMONITOR_LOGOPERATION_CEVCHECKS));
				cEntry.SetDescription(STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_CHECKSCHANGE));
			}
		}
		cEntry.SetUser((cComputerToken.IsHost()) ? ((bUser) ? GetAccountUserName() : STRING(IDS_TCPROCEDURESMONITOR_LOGUSER_UNKNOWN)) : cComputerToken.GetComputerName());
		cEntry.SetTime(CTime::GetCurrentTime().GetTime());
		return LogActivity(&cEntry);
	}
	return FALSE;
}

BOOL CTCProceduresMonitorWnd::LogTelecommandingReleaseWaitMode(LPCTSTR pszOriginator, BOOL bEnabled, BOOL bUser)
{
	CTCLogEntry  cEntry;
	CComputerToken  cComputerToken(pszOriginator);

	if (IsInitialized())
	{
		for (cEntry.SetName(STRING(IDS_TCPROCEDURESMONITOR_LOGOBJECT_SOURCE)); bEnabled; )
		{
			cEntry.SetActivity(CString(STRING(IDS_TCPROCEDURESMONITOR_LOGACTIVITY_ENABLING)) + SPACE + STRING(IDS_TCPROCEDURESMONITOR_LOGOPERATION_RELEASEWAITMODE));
			cEntry.SetDescription(STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_RELEASEWAITMODECHANGE));
			break;
		}
		if (!bEnabled)
		{
			cEntry.SetActivity(CString(STRING(IDS_TCPROCEDURESMONITOR_LOGACTIVITY_DISABLING)) + SPACE + STRING(IDS_TCPROCEDURESMONITOR_LOGOPERATION_RELEASEWAITMODE));
			cEntry.SetDescription(STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_RELEASEWAITMODECHANGE));
		}
		cEntry.SetUser((cComputerToken.IsHost()) ? ((bUser) ? GetAccountUserName() : STRING(IDS_TCPROCEDURESMONITOR_LOGUSER_UNKNOWN)) : cComputerToken.GetComputerName());
		cEntry.SetTime(CTime::GetCurrentTime().GetTime());
		return LogActivity(&cEntry);
	}
	return FALSE;
}

BOOL CTCProceduresMonitorWnd::LogResetInterlocks(CONST CTCInterlocks &pInterlocks)
{
	INT  nInterlock;
	INT  nInterlocks;
	CString  szScope;
	CString  szStage;
	CString  szActivity;
	CString  szDescription;
	CTCInterlock  *pInterlock;
	CTCLogEntry  cEntry;

	if (IsInitialized())
	{
		for (nInterlock = 0, nInterlocks = (INT)pInterlocks.GetSize(); nInterlock < nInterlocks; nInterlock++)
		{
			if ((pInterlock = (CTCInterlock *)pInterlocks.GetAt(nInterlock)) != (CTCInterlock *)NULL)
			{
				szScope = (TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) == TCINTERLOCK_SCOPE_GLOBAL) ? STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_INTERLOCKSCOPEGLOBAL) : EMPTYSTRING;
				szScope = (TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) == TCINTERLOCK_SCOPE_LOCAL) ? STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_INTERLOCKSCOPELOCAL) : szScope;
				szScope = (TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) == TCINTERLOCK_SCOPE_LOCALNOWAIT) ? STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_INTERLOCKSCOPELOCALNOWAIT) : szScope;
				szScope = (TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) == TCINTERLOCK_SCOPE_LOCALSUBSYSTEM) ? STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_INTERLOCKSCOPESUBSYSTEM) : szScope;
				szScope = (TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) == TCINTERLOCK_SCOPE_LOCALSUBSYSTEMNOWAIT) ? STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_INTERLOCKSCOPESUBSYSTEMNOWAIT) : szScope;
				szScope = (TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) == TCINTERLOCK_SCOPE_COMMANDS) ? STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_INTERLOCKSCOPECOMMANDS) : szScope;
				szStage = (pInterlock->GetStage() == TCINTERLOCK_STAGE_RECEPTION) ? STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_INTERLOCKSTAGERECEPTION) : EMPTYSTRING;
				szStage = (pInterlock->GetStage() == TCINTERLOCK_STAGE_TRANSMISSION) ? STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_INTERLOCKSTAGETRANSMISSION) : szStage;
				szStage = (pInterlock->GetStage() == TCINTERLOCK_STAGE_ACCEPTANCE) ? STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_INTERLOCKSTAGEACCEPTANCE) : szStage;
				szStage = (pInterlock->GetStage() == TCINTERLOCK_STAGE_START) ? STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_INTERLOCKSTAGESTART) : szStage;
				szStage = (pInterlock->GetStage() == TCINTERLOCK_STAGE_PROGRESS) ? STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_INTERLOCKSTAGEPROGRESS) : szStage;
				szStage = (pInterlock->GetStage() == TCINTERLOCK_STAGE_COMPLETION) ? STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_INTERLOCKSTAGECOMPLETION) : szStage;
				szActivity = CString(STRING(IDS_TCPROCEDURESMONITOR_LOGACTIVITY_RESETTING)) + SPACE + STRING(IDS_TCPROCEDURESMONITOR_LOGOBJECT_INTERLOCK);
				szDescription.Format(STRING(IDS_TCPROCEDURESMONITOR_LOGDESCRIPTION_INTERLOCK), (LPCTSTR)szScope, (LPCTSTR)szStage);
				cEntry.SetName(pInterlock->GetName());
				cEntry.SetDescription(szDescription);
				cEntry.SetActivity(szActivity);
				cEntry.SetTime(CTime::GetCurrentTime().GetTime());
				cEntry.SetUser(GetAccountUserName());
				LogActivity(&cEntry);
				continue;
			}
			break;
		}
		return((nInterlock == nInterlocks) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CTCProceduresMonitorWnd::SetContents(CONST CByteArray &nContentsInfo)
{
	INT  nItem;
	INT  nItems;
	INT  nStep;
	INT  nSteps;
	INT  nThread;
	INT  nThreads;
	INT  nArgument;
	INT  nArguments;
	CPtrArray  pSteps;
	CTCProcedureDocument  *pDocument;
	CDatabaseTCProcedure  *pProcedure;
	CTCProcedureDocumentItem  *pStep;
	CTCProceduresMonitorItem  *pItem;
	CTCProceduresMonitorItems  pItems;
	CDatabaseTCProcedureThread  *pThread;
	CDatabaseTCProcedureArgument  *pArgument[2];
	CDatabaseTCProcedureArguments  pArguments[2];

	for (nItem = 0, nItems = (pItems.Unmap(nContentsInfo)) ? (INT)pItems.GetSize() : -1; nItem < nItems; nItem++)
	{
		if ((pProcedure = ((pItem = pItems.GetAt(nItem))) ? GetDatabase()->GetTCProcedures()->GetAt(GetDatabase()->GetTCProcedures()->Find(pItem->GetName())) : (CDatabaseTCProcedure *)NULL) && pItem->CDatabaseTCProcedure::Copy(pProcedure))
		{
			for (nThread = 0, nThreads = (INT)pItem->GetSize(); nThread < nThreads; nThread++)
			{
				if ((pThread = pItem->GetAt(nThread)) != (CDatabaseTCProcedureThread *)NULL)
				{
					if ((pDocument = new CTCProcedureDocument) && pDocument->Unmap(pThread))
					{
						for (nStep = 0, nSteps = pDocument->EnumSteps(pSteps); nStep < nSteps; nStep++)
						{
							if ((pStep = (CTCProcedureDocumentItem *)pSteps.GetAt(nStep)))
							{
								pStep->Activate(FALSE);
								continue;
							}
						}
						if (pDocument->Map(pThread))
						{
							delete pDocument;
							continue;
						}
					}
					delete pDocument;
				}
				break;
			}
			if (nThread == nThreads)
			{
				if (pProcedure->GetArguments(pArguments[0]) != pItem->GetArguments(pArguments[1]))
				{
					pItem->SetArguments(pArguments[0]);
					continue;
				}
				for (nArgument = 0, nArguments = (INT)pArguments[0].GetSize(); nArgument < nArguments; nArgument++)
				{
					if ((pArgument[0] = pArguments[0].GetAt(nArgument)))
					{
						if ((pArgument[1] = pArguments[1].GetAt(nArgument)))
						{
							if (pArgument[0]->GetTag() != pArgument[1]->GetTag() || pArgument[0]->GetAttributes() != pArgument[1]->GetAttributes())
							{
								pItem->SetArguments(pArguments[0]);
								nArgument = nArguments;
								break;
							}
							continue;
						}
					}
					break;
				}
				if (nArgument == nArguments) continue;
			}
		}
		pItems.RemoveAt(nItem);
		delete pItem;
		nItems--;
		nItem--;
	}
	return((nItem == nItems) ? SetProcedures(pItems) : FALSE);
}

BOOL CTCProceduresMonitorWnd::GetContents(CByteArray &nContentsInfo) CONST
{
	CTCProceduresMonitorItems  pItems;

	return((GetProcedures(pItems)) ? pItems.Map(nContentsInfo) : FALSE);
}

BOOL CTCProceduresMonitorWnd::SetPrintJobs(CONST CByteArray &nPrintInfo)
{
	CTCProceduresMonitorPrintJobs  pPrintJobs;

	return((pPrintJobs.Unmap(nPrintInfo)) ? SetPrintJobs(pPrintJobs) : FALSE);
}

BOOL CTCProceduresMonitorWnd::GetPrintJobs(CByteArray &nPrintInfo) CONST
{
	CTCProceduresMonitorPrintJobs  pPrintJobs;

	return((GetPrintJobs(pPrintJobs)) ? pPrintJobs.Map(nPrintInfo) : FALSE);
}

BOOL CTCProceduresMonitorWnd::GetPrintProperties(CONST CTCProceduresMonitorPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, CStringArray &szThreads, CPtrArray &pThreadMetaDCs, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST
{
	return m_wndView.GetPrintProperties(pJobInfo, szColumns, szContents, pAttributes, szThreads, pThreadMetaDCs, pTitleFont, pItemsFont, pSymbols, nSymbolIDs);
}

BOOL CTCProceduresMonitorWnd::StartPrintJob(CDC &cDC)
{
	DOCINFO  sJobInfo;
	CString  szJobTitle;

	for (sJobInfo.fwType = 0, sJobInfo.cbSize = sizeof(DOCINFO), sJobInfo.lpszDocName = (LPTSTR)EMPTYSTRING, sJobInfo.lpszOutput = (LPCTSTR)NULL, sJobInfo.lpszDatatype = (LPCTSTR)NULL, szJobTitle.Format(STRING(IDS_PRINTJOB_SIMPLETITLE), (LPCTSTR)GetAppTitle(), (LPCTSTR)GetAccountSpacecraftName(), STRING(IDS_DISPLAY_TITLE_TCPROCEDURESMONITOR)); szJobTitle.GetLength() >= 0; )
	{
		sJobInfo.lpszDocName = (LPTSTR)(LPCTSTR)szJobTitle;
		break;
	}
	return((cDC.StartDoc(&sJobInfo) >= 0) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorWnd::PrintJob(CDC &cDC, CONST CTCProceduresMonitorPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST CTextViewAttributes &pAttributes, CONST CStringArray &szThreads, CONST CPtrArray &pThreadMetaDCs, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CONST CPtrArray &pSymbols, CONST CUIntArray &nSymbolIDs)
{
	INT  nID;
	INT  nPos;
	INT  nLine;
	INT  nLines;
	INT  nColumn;
	INT  nColumns;
	INT  nPage[2];
	INT  nPages[2];
	INT  nFont;
	INT  nFonts;
	INT  nThread;
	INT  nThreads;
	INT  nSpacing;
	INT  nHeight[2];
	UINT  nScale;
	UINT  nFormat;
	BOOL  bOverlap;
	BOOL  bOutput;
	CRgn  rgnArea;
	CRgn  rgnClip;
	CRect  rArea;
	CRect  rCalc;
	CRect  rClip;
	CRect  rItem;
	CFont  *pOldFont;
	CFont  cFont[TCPROCEDURESMONITOR_PRINTFONTS];
	CSize  sizeSymbol;
	double  fScale;
	CString  szColumn;
	COLORREF  nColor;
	COLORREF  nOldColor;
	CTimeKey  tPrint;
	CPtrArray  pFonts;
	CUIntArray  nTabs;
	TEXTMETRIC  tmFont;
	CPtrArray  pMetaHandles;
	CUIntArray  nThreadPages;
	CMetaFileDC  *pThreadMetaDC;
	CStringArray  szColumnsText;
	ENHMETAHEADER  sMetaHeader;
	CTextViewAttribute  *pAttribute;
	CDatabaseTCProcedure  cProcedure;
	CClientDC  cClientDC(this);

	for (nPage[0] = nPages[0] = 0; (!nPages[0] || nPage[0] <= nPages[0]) && (nPages[0] > 0 || (nPages[0] = (GetProcedureInfo(max(GetCurProcedure(), 0), &cProcedure) && CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(rArea) != ERROR && rgnArea.CreateRectRgnIndirect(rArea) && CalcPrintDocTitleFont(cDC, rArea, cFont[TCPROCEDURESMONITOR_PRINTFONT_TITLE]) && CalcPrintDocSubTitleFont(cDC, rArea, cFont[TCPROCEDURESMONITOR_PRINTFONT_SUBTITLE]) && CalcPrintDocOperatingDetailsFont(cDC, rArea, cFont[TCPROCEDURESMONITOR_PRINTFONT_OPERATINGDETAILS]) && CalcPrintDocListItemsFonts(cDC, rArea, szColumns, szContents, pTitleFont, pItemsFont, cFont[TCPROCEDURESMONITOR_PRINTFONT_LISTITEMSTITLE], cFont[TCPROCEDURESMONITOR_PRINTFONT_LISTITEMS]) && CalcPrintDocNoticeFonts(cDC, rArea, cFont[TCPROCEDURESMONITOR_PRINTFONT_NOTICE], cFont[TCPROCEDURESMONITOR_PRINTFONT_LOGO]) && CalcPrintDocFooterFont(cDC, rArea, cFont[TCPROCEDURESMONITOR_PRINTFONT_FOOTER]) && CalcPrintDocTitleWidth(cDC, rArea, szColumns, szContents, &cFont[TCPROCEDURESMONITOR_PRINTFONT_LISTITEMSTITLE], &cFont[TCPROCEDURESMONITOR_PRINTFONT_LISTITEMS], nTabs) == szColumns.GetSize()) ? nPages[0] : -1) == 0); )
	{
		for (nFont = 0, nFonts = (!nPages[0]) ? (INT)(sizeof(cFont) / sizeof(cFont[0])) : 0; nFont < nFonts; nFont++)
		{
			pFonts.SetAtGrow(nFont, &cFont[nFont]);
			continue;
		}
		for (nThread = 0, nThreads = (!nPages[0]) ? (INT)pThreadMetaDCs.GetSize() : 0; nThread < nThreads; nThread++)
		{
			if ((pThreadMetaDC = (CMetaFileDC *)pThreadMetaDCs.GetAt(nThread)))
			{
				pMetaHandles.Add(pThreadMetaDC->CloseEnhanced());
				continue;
			}
		}
		for (nThread = 0; nThread < nThreads; nThread++)
		{
			if (GetEnhMetaFileHeader((HENHMETAFILE)pMetaHandles.GetAt(nThread), sizeof(sMetaHeader), &sMetaHeader) > 0)
			{
				if (DrawPrintDocPage(cDC, pJobInfo, tPrint, pszPrinterName, rtMargin, bMetric, cProcedure.GetName(), cProcedure.GetDescription(), szThreads.GetAt(nThread), szColumns, pFonts, nTabs, 0, 0, rClip))
				{
					fScale = max(max((double)cDC.GetDeviceCaps(LOGPIXELSX) / (double)cClientDC.GetDeviceCaps(LOGPIXELSX), (double)cDC.GetDeviceCaps(LOGPIXELSY) / (double)cClientDC.GetDeviceCaps(LOGPIXELSY)), 1.0);
					fScale = ((pJobInfo->GetPrintMode() & TCPROCEDURESMONITOR_PRINT_AUTOSCALE) && sMetaHeader.rclBounds.right - sMetaHeader.rclBounds.left > 0 && sMetaHeader.rclBounds.bottom - sMetaHeader.rclBounds.top > 0) ? ((((double)rClip.Width() / (double)(sMetaHeader.rclBounds.right - sMetaHeader.rclBounds.left)) <= (double)rClip.Height() / (double)(sMetaHeader.rclBounds.bottom - sMetaHeader.rclBounds.top)) ? ((double)rClip.Width() / (double)(sMetaHeader.rclBounds.right - sMetaHeader.rclBounds.left)) : ((double)rClip.Height() / (double)(sMetaHeader.rclBounds.bottom - sMetaHeader.rclBounds.top))) : ((pJobInfo->GetPrintScale(nScale)) ? (((double)nScale / 100.0)*fScale) : fScale);
					nThreadPages.SetAtGrow(nThread, (UINT)(((fScale*(sMetaHeader.rclBounds.right - sMetaHeader.rclBounds.left - 1)) / rClip.Width() + 1))*(UINT)(((fScale*(sMetaHeader.rclBounds.bottom - sMetaHeader.rclBounds.top - 1)) / rClip.Height() + 1)));
					continue;
				}
			}
			break;
		}
		for (nLine = 0, nLines = (pJobInfo->GetPrintMode() & TCPROCEDURESMONITOR_PRINT_LIST) ? (INT)szContents.GetSize() : 0, nSpacing = 0, rCalc.SetRectEmpty(), rClip.SetRectEmpty(), bOverlap = FALSE, bOutput = TRUE; (nPages[0] = (nThread == nThreads) ? nPages[0] : -1) >= 0 && nLine < nLines; nLine++, bOutput = TRUE)
		{
			for (nColumn = 0, nColumns = (INT)szColumns.GetSize(), ExtractPrintDocText(szContents.GetAt(nLine), szColumnsText), nHeight[0] = nHeight[1] = 0; nPages[0] >= 0 && nColumn < nColumns; nColumn++, nHeight[1] = 0)
			{
				if (rClip.Height() > 0)
				{
					if ((pOldFont = cDC.SelectObject((CFont *)pFonts.GetAt(TCPROCEDURESMONITOR_PRINTFONT_LISTITEMS))))
					{
						if ((nSpacing = (cDC.GetTextMetrics(&tmFont)) ? max(tmFont.tmHeight / 16, 1) : -1) >= 0)
						{
							for (rCalc.SetRect(rCalc.left, (!nColumn) ? (rCalc.top + nSpacing) : rCalc.top, rCalc.right, (!nColumn) ? (rCalc.top + nSpacing + tmFont.tmHeight*((rClip.bottom - (rCalc.top + nSpacing)) / tmFont.tmHeight)) : (rCalc.top + tmFont.tmHeight*((rClip.bottom - rCalc.top) / tmFont.tmHeight))), nFormat = DT_LEFT | DT_NOPREFIX | DT_WORDBREAK, nColor = cDC.GetTextColor(); (pAttribute = pAttributes.GetAt(nLine)); )
							{
								pAttribute->GetColumnFormat(nColumn, nFormat);
								pAttribute->GetColumnColor(nColumn, nColor);
								break;
							}
							for (szColumn = (!szColumnsText.GetAt(nColumn).IsEmpty()) ? (((nPos = (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NAME)) ? szColumnsText.GetAt(nColumn).Find(CTCProceduresMonitorTextView::GetSymbolDelimiter()) : -1) >= 0) ? (szColumnsText.GetAt(nColumn).Left(nPos)) : (szColumnsText.GetAt(nColumn) + SPACE)) : EMPTYSTRING, nFormat = (nPages[0] > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage[0] >= nFromPage && nPage[0] <= nToPage))) ? nFormat : (nFormat | DT_CALCRECT), nOldColor = cDC.SetTextColor((cDC.GetDeviceCaps(NUMCOLORS) > 2) ? nColor : cDC.GetTextColor()), sizeSymbol.cx = sizeSymbol.cy = tmFont.tmHeight, nHeight[1] = (szColumns.GetAt(nColumn) != STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS) && szColumns.GetAt(nColumn) != STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS)) ? cDC.DrawText(szColumn, (rItem = CRect((nColumn > 0) ? (rCalc.left + nTabs.GetAt(nColumn - 1)) : rCalc.left, rCalc.top, rCalc.left + nTabs.GetAt(nColumn), rCalc.bottom)), nFormat) : sizeSymbol.cy; szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NAME); )
							{
								DrawPrintDocSymbol(cDC, ((nFormat & DT_CALCRECT) != DT_CALCRECT  &&  rItem.top + sizeSymbol.cy <= rCalc.bottom) ? (rItem = CRect(rItem.left + cDC.GetTextExtent(szColumn).cx + sizeSymbol.cx / 2, rItem.top, rItem.left + cDC.GetTextExtent(szColumn).cx + sizeSymbol.cx / 2 + sizeSymbol.cx, rItem.top + sizeSymbol.cy)) : CRect(0, 0, 0, 0), (szColumnsText.GetAt(nColumn).Find(STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_INFORMATION)) >= 0) ? IDP_TCPROCEDURESMONITORINFORMATION : ((szColumnsText.GetAt(nColumn).Find(STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_WARNING)) >= 0) ? IDP_TCPROCEDURESMONITORWARNING : ((szColumnsText.GetAt(nColumn).Find(STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_ERROR)) >= 0) ? IDP_TCPROCEDURESMONITORERROR : ((szColumnsText.GetAt(nColumn).Find(STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_ALERT)) >= 0) ? IDP_TCPROCEDURESMONITORALERT : ((szColumnsText.GetAt(nColumn).Find(STRING(IDS_TCPROCEDURESMONITOR_LIST_SYMBOL_AUTHORIZATION)) >= 0) ? IDP_TCPROCEDURESMONITORAUTHORIZATION : -1)))), pSymbols, nSymbolIDs);
								break;
							}
							if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS))
							{
								for (nID = (szColumn.Find(STRING(IDS_TCPROCEDURESMONITOR_LIST_PEVCHECKS_ON)) >= 0) ? IDP_TCPROCEDURESMONITORCHECKSON : -1, nID = (szColumn.Find(STRING(IDS_TCPROCEDURESMONITOR_LIST_PEVCHECKS_OFF)) >= 0) ? IDP_TCPROCEDURESMONITORCHECKSOFF : nID, nID = (szColumn.Find(STRING(IDS_TCPROCEDURESMONITOR_LIST_PEVCHECKS_DISABLED)) >= 0) ? IDP_TCPROCEDURESMONITORCHECKSDISABLED : nID, rItem.SetRect((nColumn > 0) ? (rCalc.left + nTabs.GetAt(nColumn - 1)) : rCalc.left, rCalc.top, rCalc.left + nTabs.GetAt(nColumn), rCalc.top + sizeSymbol.cy), rItem.DeflateRect((rItem.Width() - rItem.Height()) / 2, 0); (nFormat & DT_CALCRECT) != DT_CALCRECT && rItem.bottom <= rCalc.bottom; )
								{
									DrawPrintDocSymbol(cDC, rItem, nID, pSymbols, nSymbolIDs);
									break;
								}
							}
							if (szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS))
							{
								for (nID = (szColumn.Find(STRING(IDS_TCPROCEDURESMONITOR_LIST_CEVCHECKS_ON)) >= 0) ? IDP_TCPROCEDURESMONITORCHECKSON : -1, nID = (szColumn.Find(STRING(IDS_TCPROCEDURESMONITOR_LIST_CEVCHECKS_OFF)) >= 0) ? IDP_TCPROCEDURESMONITORCHECKSOFF : nID, nID = (szColumn.Find(STRING(IDS_TCPROCEDURESMONITOR_LIST_CEVCHECKS_DISABLED)) >= 0) ? IDP_TCPROCEDURESMONITORCHECKSDISABLED : nID, rItem.SetRect((nColumn > 0) ? (rCalc.left + nTabs.GetAt(nColumn - 1)) : rCalc.left, rCalc.top, rCalc.left + nTabs.GetAt(nColumn), rCalc.top + sizeSymbol.cy), rItem.DeflateRect((rItem.Width() - rItem.Height()) / 2, 0); (nFormat & DT_CALCRECT) != DT_CALCRECT && rItem.bottom <= rCalc.bottom; )
								{
									DrawPrintDocSymbol(cDC, rItem, nID, pSymbols, nSymbolIDs);
									break;
								}
							}
							nHeight[0] = max(max(nHeight[0], sizeSymbol.cy), nHeight[1]);
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
					if (nPages[0] > 0 && (nPage[0] == nPages[0] || (nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage  &&  nPage[0] == nToPage)))
					{
						nPages[0] = nPage[0];
						nColumns = nColumn;
						nLines = nLine;
						break;
					}
					if (bOutput && (!nPages[0] || ((!nPage[0] || (nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage && (nPage[0] < nFromPage || nPage[0] > nToPage)) || cDC.EndPage() >= 0) && ((nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage && (nPage[0] < nFromPage - 1 || nPage[0] >= nToPage)) || (((((nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage) && nPage[0] > 0) || (nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage  &&  nPage[0] != nFromPage - 1)) || StartPrintJob(cDC)) && cDC.StartPage() >= 0)))))
					{
						if (cDC.SelectClipRgn(&rgnArea) != ERROR  &&  DrawPrintDocPage(cDC, pJobInfo, tPrint, pszPrinterName, rtMargin, bMetric, cProcedure.GetName(), cProcedure.GetDescription(), EMPTYSTRING, szColumns, pFonts, nTabs, nPages[0], (nPages[0] > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage[0] >= nFromPage - 1 && nPage[0] < nToPage))) ? (nPage[0] + 1) : 0, rClip) && cDC.IntersectClipRect(rClip) != ERROR)
						{
							rCalc.SetRect(rClip.left, rClip.top - rCalc.Height() - nSpacing, rClip.right, rClip.bottom);
							bOverlap = FALSE;
							bOutput = FALSE;
							nColumn = -1;
							nPage[0]++;
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
		if (nPages[0] >= 0)
		{
			if (nLine == nLines  &&  !nPages[0])
			{
				for (nThread = 0, nThreads = (pJobInfo->GetPrintMode() & TCPROCEDURESMONITOR_PRINT_FLOWCHART) ? (INT)nThreadPages.GetSize() : 0, nPages[0] = nPage[0], nPage[0] = 0; nThread < nThreads; nThread++)
				{
					nPages[0] += nThreadPages.GetAt(nThread);
					continue;
				}
				if ((nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || nPages[0] >= nFromPage) && nPages[0] > 0) continue;
				nPages[0] = nPage[0] = 0;
			}
			if (nLine == nLines  &&  nPages[0] > 0)
			{
				for (nThread = 0, nThreads = (pJobInfo->GetPrintMode() & TCPROCEDURESMONITOR_PRINT_FLOWCHART) ? (INT)pMetaHandles.GetSize() : 0, cDC.SelectClipRgn((CRgn *)NULL); nThread < nThreads; nThread++)
				{
					if (GetEnhMetaFileHeader((HENHMETAFILE)pMetaHandles.GetAt(nThread), sizeof(sMetaHeader), &sMetaHeader) > 0)
					{
						for (nPage[1] = 0, nPages[1] = nThreadPages.GetAt(nThread); nPage[1] < nPages[1]; nPage[1]++)
						{
							if ((++nPage[0] >= nFromPage  &&  nPage[0] <= nToPage) || (nFromPage <= 0 && nToPage <= 0))
							{
								if (((nPage[0] <= 1 || nPage[0] == nFromPage) && StartPrintJob(cDC) && cDC.StartPage() >= 0) || (nPage[0] > 1 && nPage[0] > nFromPage  &&  cDC.EndPage() >= 0 && cDC.StartPage() >= 0))
								{
									if (DrawPrintDocPage(cDC, pJobInfo, tPrint, pszPrinterName, rtMargin, bMetric, cProcedure.GetName(), cProcedure.GetDescription(), szThreads.GetAt(nThread), szColumns, pFonts, nTabs, nPages[0], nPage[0], rClip))
									{
										for (fScale = max(max((double)cDC.GetDeviceCaps(LOGPIXELSX) / (double)cClientDC.GetDeviceCaps(LOGPIXELSX), (double)cDC.GetDeviceCaps(LOGPIXELSY) / (double)cClientDC.GetDeviceCaps(LOGPIXELSY)), 1.0), fScale = ((pJobInfo->GetPrintMode() & TCPROCEDURESMONITOR_PRINT_AUTOSCALE) && sMetaHeader.rclBounds.right - sMetaHeader.rclBounds.left > 0 && sMetaHeader.rclBounds.bottom - sMetaHeader.rclBounds.top > 0) ? ((((double)rClip.Width() / (double)(sMetaHeader.rclBounds.right - sMetaHeader.rclBounds.left)) <= (double)rClip.Height() / (double)(sMetaHeader.rclBounds.bottom - sMetaHeader.rclBounds.top)) ? ((double)rClip.Width() / (double)(sMetaHeader.rclBounds.right - sMetaHeader.rclBounds.left)) : ((double)rClip.Height() / (double)(sMetaHeader.rclBounds.bottom - sMetaHeader.rclBounds.top))) : ((pJobInfo->GetPrintScale(nScale)) ? (((double)nScale / 100.0)*fScale) : fScale), cDC.SetViewportOrg(-(nPage[1] % (INT)((fScale*(sMetaHeader.rclBounds.right - sMetaHeader.rclBounds.left - 1)) / rClip.Width() + 1))*rClip.Width(), -(nPage[1] / (INT)((fScale*(sMetaHeader.rclBounds.right - sMetaHeader.rclBounds.left - 1)) / rClip.Width() + 1))*rClip.Height()); rgnClip.CreateRectRgn(rClip.left, rClip.top, rClip.right, rClip.bottom) && cDC.SelectClipRgn(&rgnClip) != ERROR; )
										{
											cDC.PlayMetaFile((HENHMETAFILE)pMetaHandles.GetAt(nThread), CRect((INT)(rClip.left + max((rClip.Width() - fScale*(sMetaHeader.rclBounds.right - sMetaHeader.rclBounds.left)) / 2, 0)), rClip.top, (INT)(rClip.left + max((rClip.Width() - fScale*(sMetaHeader.rclBounds.right - sMetaHeader.rclBounds.left)) / 2, 0) + fScale*(sMetaHeader.rclBounds.right - sMetaHeader.rclBounds.left)), (INT)(rClip.top + fScale*(sMetaHeader.rclBounds.bottom - sMetaHeader.rclBounds.top))));
											cDC.SelectClipRgn((CRgn *)NULL);
											break;
										}
										rgnClip.DeleteObject();
										continue;
									}
								}
								break;
							}
						}
						if (nPage[1] == nPages[1]) continue;
					}
					nLines = 0;
					nLine = -1;
					break;
				}
			}
			if (nLine < nLines)
			{
				if (nPages[0] > 0) cDC.AbortDoc();
				nPages[0] = -1;
				break;
			}
			for (nThread = 0, nThreads = (nPages[0] >= 0) ? (INT)pThreadMetaDCs.GetSize() : 0; nThread < nThreads; nThread++)
			{
				if ((pThreadMetaDC = (CMetaFileDC *)pThreadMetaDCs.GetAt(nThread)))
				{
					delete pThreadMetaDC;
					continue;
				}
			}
		}
		break;
	}
	return(((!nPages[0] || (nPages[0] > 0 && ((nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage  &&  nPage[0] < nFromPage) || (cDC.EndPage() >= 0 && EndPrintJob(cDC))))) && nPage[0] == nPages[0]) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorWnd::EndPrintJob(CDC &cDC)
{
	return((cDC.EndDoc() >= 0) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorWnd::DrawPrintDocPage(CDC &cDC, CONST CTCProceduresMonitorPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, LPCTSTR pszName, LPCTSTR pszDescription, LPCTSTR pszDetails, CONST CStringArray &szColumns, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nPages, INT nPage, LPRECT prClip)
{
	return((CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(prClip) != ERROR  &&  DrawPrintDocTitle(cDC, prClip, GetPrintDocTitle(), (CFont *)pFonts.GetAt(TCPROCEDURESMONITOR_PRINTFONT_TITLE), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocSubTitle(cDC, prClip, GetPrintDocSubTitle(pJobInfo, pszName, pszDescription), (CFont *)pFonts.GetAt(TCPROCEDURESMONITOR_PRINTFONT_SUBTITLE), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocOperatingDetails(cDC, prClip, GetPrintDocOperatingDetails(pJobInfo, pszDetails), (CFont *)pFonts.GetAt(TCPROCEDURESMONITOR_PRINTFONT_OPERATINGDETAILS), (nPage <= 0) ? TRUE : FALSE) && (lstrlen(pszDetails) > 0 || DrawPrintDocListItemsTitle(cDC, prClip, szColumns, (CFont *)pFonts.GetAt(TCPROCEDURESMONITOR_PRINTFONT_LISTITEMSTITLE), nTabs, (nPage <= 0) ? TRUE : FALSE)) && DrawPrintDocNotice(cDC, prClip, GetPrintDocNotice(), (CFont *)pFonts.GetAt(TCPROCEDURESMONITOR_PRINTFONT_NOTICE), (CFont *)pFonts.GetAt(TCPROCEDURESMONITOR_PRINTFONT_LOGO), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocFooter(cDC, prClip, GetPrintDocFooter(tTime, pszPrinterName, nPages, nPage), (CFont *)pFonts.GetAt(TCPROCEDURESMONITOR_PRINTFONT_FOOTER), (nPage <= 0) ? TRUE : FALSE)) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorWnd::DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc)
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

BOOL CTCProceduresMonitorWnd::DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc)
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

BOOL CTCProceduresMonitorWnd::DrawPrintDocOperatingDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszDetails, CFont *pFont, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszDetails, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
		cDC.DrawText(pszDetails, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
		prClip->top += 2 * cDC.GetTextExtent(SPACE).cy;
		prClip->top += rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorWnd::DrawPrintDocListItemsTitle(CDC &cDC, LPRECT prClip, CONST CStringArray &szColumns, CFont *pFont, CONST CUIntArray &nTabs, BOOL bCalc)
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

BOOL CTCProceduresMonitorWnd::DrawPrintDocSymbol(CDC &cDC, LPRECT prClip, UINT nSymbolID, CONST CPtrArray &pSymbols, CONST CUIntArray &nSymbolIDs)
{
	INT  nID;
	INT  nIDs;
	CImage  *pSymbol;

	for (nID = 0, nIDs = (nSymbolID != (UINT)-1) ? (INT)nSymbolIDs.GetSize() : -1; nID < nIDs; nID++)
	{
		if (nSymbolIDs.GetAt(nID) == nSymbolID) break;
		continue;
	}
	if ((pSymbol = (nID < nIDs) ? (CImage *)pSymbols.GetAt(nID) : (CImage *)NULL) && prClip->right - prClip->left > 0 && prClip->bottom - prClip->top > 0)
	{
		pSymbol->Draw(cDC.GetSafeHdc(), prClip->left, prClip->top, prClip->right - prClip->left, prClip->bottom - prClip->top);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProceduresMonitorWnd::DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc)
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

BOOL CTCProceduresMonitorWnd::DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc)
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

CString CTCProceduresMonitorWnd::GetPrintDocTitle() CONST
{
	CString  szTitle;

	szTitle.Format(STRING(IDS_TCPROCEDURESMONITOR_PRINTDOCUMENT_TITLE), (LPCTSTR)GetAccountSpacecraftName());
	return szTitle;
}

CString CTCProceduresMonitorWnd::GetPrintDocSubTitle(CONST CTCProceduresMonitorPrintJobInfo *pJobInfo, LPCTSTR pszName, LPCTSTR pszDescription) CONST
{
	CString  szTitle;

	if ((pJobInfo->GetPrintMode() & TCPROCEDURESMONITOR_PRINT_ONEONLY) != TCPROCEDURESMONITOR_PRINT_ONEONLY)
	{
		szTitle = STRING(IDS_TCPROCEDURESMONITOR_PRINTDOCUMENT_DEFAULTSUBTITLE);
		return szTitle;
	}
	szTitle.Format(STRING(IDS_TCPROCEDURESMONITOR_PRINTDOCUMENT_SPECIALSUBTITLE), pszDescription, pszName);
	return szTitle;
}

CString CTCProceduresMonitorWnd::GetPrintDocOperatingDetails(CONST CTCProceduresMonitorPrintJobInfo *pJobInfo, LPCTSTR pszDetails) CONST
{
	CString  szDetails;

	szDetails = (!pJobInfo->GetComments().IsEmpty() && lstrlen(pszDetails) > 0) ? (CString(pszDetails) + CR + EOL + pJobInfo->GetComments()) : ((!pJobInfo->GetComments().IsEmpty()) ? pJobInfo->GetComments() : pszDetails);
	return szDetails;
}

CString CTCProceduresMonitorWnd::GetPrintDocListItemsTitle(CONST CStringArray &szColumns) CONST
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

CString CTCProceduresMonitorWnd::GetPrintDocNotice() CONST
{
	CVersionInfo  cVersionInfo;

	return cVersionInfo.QueryComments();
}

CString CTCProceduresMonitorWnd::GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST
{
	CString  szFooter;

	szFooter.Format(STRING(IDS_OOL_PRINTDOCUMENT_FOOTER), (LPCTSTR)tTime.Format(IDS_TIMEKEY_DATEFORMAT), (LPCTSTR)tTime.Format(IDS_TIMEKEY_TIMEFORMAT), pszPrinterName, nPage, nPages);
	return szFooter;
}

INT CTCProceduresMonitorWnd::ExtractPrintDocText(LPCTSTR pszText, CStringArray &szColumnsText) CONST
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

BOOL CTCProceduresMonitorWnd::CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 48, (INT)((-5.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CTCProceduresMonitorWnd::CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 64, (INT)((-4.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CTCProceduresMonitorWnd::CalcPrintDocOperatingDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 76, (INT)((-3.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CTCProceduresMonitorWnd::CalcPrintDocListItemsFonts(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CFont &cTitleFont, CFont &cItemsFont) CONST
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
				if (CalcPrintDocTitleWidth(cDC, rArea, szColumns, szContents, &cFont[0], &cFont[1], nTabs) > 0)
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

BOOL CTCProceduresMonitorWnd::CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL) && cLogoFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, STRING(IDS_FONTFACE_COMPANYLOGO));
}

BOOL CTCProceduresMonitorWnd::CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 80, (INT)((-3.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

INT CTCProceduresMonitorWnd::CalcPrintDocTitleWidth(CDC &cDC, LPCTSTR pszColumn, CFont *pTitleFont) CONST
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
INT CTCProceduresMonitorWnd::CalcPrintDocTitleWidth(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CFont *pTitleFont, CFont *pItemsFont, CUIntArray &nTabs) CONST
{
	INT  nIndent;
	INT  nColumn;
	INT  nColumns;
	INT  nWidth[2];
	CSize  sizeSymbol;
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;
	CStringArray  szLines;

	for (nIndent = 0, sizeSymbol.cx = sizeSymbol.cy = 0, nTabs.RemoveAll(); (pOldFont = cDC.SelectObject(pTitleFont)); )
	{
		nIndent = (cDC.GetTextMetrics(&tmFont)) ? max(tmFont.tmAveCharWidth, nIndent) : nIndent;
		cDC.SelectObject(pOldFont);
		break;
	}
	if ((pOldFont = cDC.SelectObject(pItemsFont)))
	{
		if (cDC.GetTextMetrics(&tmFont))
		{
			sizeSymbol.cx = tmFont.tmHeight;
			sizeSymbol.cy = tmFont.tmHeight;
			nIndent = max(tmFont.tmAveCharWidth, nIndent);
		}
		cDC.SelectObject(pOldFont);
	}
	for (nColumn = 0, nColumns = (INT)szColumns.GetSize(), szLines.Copy(szContents); nColumn < nColumns; nColumn++)
	{
		for (nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont), nWidth[1] = CalcPrintDocColumnWidth(cDC, rArea, szColumns.GetAt(nColumn), szLines, pItemsFont); szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NAME); )
		{
			nWidth[1] += 3 * sizeSymbol.cx / 2;
			break;
		}
		for (; szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ARGUMENTS); )
		{
			nWidth[1] = min(3 * nWidth[0], nWidth[1]);
			break;
		}
		for (; szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS) || szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS); )
		{
			nWidth[1] = sizeSymbol.cx;
			break;
		}
		for (; szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_ACKNOWLEDGEREQUEST); )
		{
			nWidth[1] = min(2 * nWidth[0], nWidth[1]);
			break;
		}
		nTabs.Add((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1) + max(nWidth[0], nWidth[1])) : (2 * nIndent + max(nWidth[0], nWidth[1])));
	}
	if (nTabs.GetSize() > 0)
	{
		nTabs.SetAt(nTabs.GetSize() - 1, nTabs.GetAt(nTabs.GetSize() - 1) - nIndent);
		return((INT)nTabs.GetSize());
	}
	return 0;
}

INT CTCProceduresMonitorWnd::CalcPrintDocColumnWidth(CDC &cDC, CONST RECT &rArea, LPCTSTR pszColumn, CStringArray &szContents, CFont *pItemsFont) CONST
{
	INT  nPos;
	INT  nLine;
	INT  nLines;
	INT  nWidth;
	CRect  rColumn;
	CFont  *pOldFont;
	CString  szLine;

	if ((pOldFont = cDC.SelectObject(pItemsFont)))
	{
		for (nLine = 0, nLines = (INT)szContents.GetSize(), nWidth = 0; nLine < nLines; nLine++)
		{
			if ((nPos = szContents.GetAt(nLine).Find(CTextView::GetColumnDelimiter())) >= 0)
			{
				for (rColumn.SetRect(0, 0, cDC.GetTextExtent((szLine = (!lstrcmp(pszColumn, STRING(IDS_TCPROCEDURESMONITOR_TITLEITEM_NAME)) && szContents.GetAt(nLine).Left(nPos).Find(CTCProceduresMonitorTextView::GetSymbolDelimiter()) >= 0) ? szContents.GetAt(nLine).Left(nPos).Left(szContents.GetAt(nLine).Left(nPos).Find(CTCProceduresMonitorTextView::GetSymbolDelimiter())) : szContents.GetAt(nLine).Left(nPos))).cx, 0); rColumn.Width() > rArea.right - rArea.left; )
				{
					cDC.DrawText(szLine, (rColumn = CRect(0, 0, rArea.right - rArea.left, 0)), DT_LEFT | DT_NOPREFIX | DT_WORDBREAK | DT_CALCRECT);
					break;
				}
				szContents.SetAt(nLine, szContents.GetAt(nLine).Mid(nPos + 1));
				nWidth = max(rColumn.Width(), nWidth);
				continue;
			}
			if (szContents.GetAt(nLine).GetLength() > 0)
			{
				for (rColumn.SetRect(0, 0, cDC.GetTextExtent((szLine = szContents.GetAt(nLine))).cx, 0); rColumn.Width() > rArea.right - rArea.left; )
				{
					cDC.DrawText(szLine, (rColumn = CRect(0, 0, rArea.right - rArea.left, 0)), DT_LEFT | DT_NOPREFIX | DT_WORDBREAK | DT_CALCRECT);
					break;
				}
				szContents.SetAt(nLine, EMPTYSTRING);
				nWidth = max(rColumn.Width(), nWidth);
				continue;
			}
		}
		cDC.SelectObject(pOldFont);
		return nWidth;
	}
	return 0;
}

BOOL CTCProceduresMonitorWnd::CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST
{
	CRect  rClip;

	rClip.SetRect(0, 0, cDC.GetDeviceCaps(HORZRES), cDC.GetDeviceCaps(VERTRES));
	rClip.DeflateRect((bMetric) ? (rtMargin.left*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.left*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.top*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.top*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000, (bMetric) ? (rtMargin.right*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.right*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.bottom*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.bottom*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000);
	return((cDC.IntersectClipRect(rClip) != ERROR) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorWnd::SetLayoutInfo(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST SIZE &sizeListPane, CONST SIZE &sizeFlowchartPane, CONST SIZE &sizeCodePane, CONST LOGFONT *pListPaneTitleFont, CONST LOGFONT *pListPaneItemsFont, CONST LOGFONT *pCodePaneFont, CONST LOGFONT *pFlowchartPaneLabelFont, COLORREF nFlowchartPaneBackgroundColor, COLORREF nFlowchartPaneLabelColor, INT nIndex, INT nThreadID, CONST SCROLLINFO *pListPaneHorzScrollInfo, CONST SCROLLINFO *pListPaneVertScrollInfo)
{
	return((m_wndView.SetLayout(nColumns, nWidths, sizeListPane, sizeFlowchartPane, sizeCodePane) && m_wndView.SetListTitleFont(pListPaneTitleFont) && m_wndView.SetListItemsFont(pListPaneItemsFont) && m_wndView.SetItemSourceCodeFont(pCodePaneFont) && m_wndView.SetItemFlowchartLabelsFont(pFlowchartPaneLabelFont) && m_wndView.SetItemFlowchartBackgroundColor(nFlowchartPaneBackgroundColor) && m_wndView.SetItemFlowchartLabelsColor(nFlowchartPaneLabelColor) && m_wndView.SetLayoutInfo(nIndex, nThreadID, pListPaneHorzScrollInfo, pListPaneVertScrollInfo)) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorWnd::GetLayoutInfo(CUIntArray &nColumns, CUIntArray &nWidths, CSize &sizeListPane, CSize &sizeFlowchartPane, CSize &sizeCodePane, LOGFONT *pListPaneTitleFont, LOGFONT *pListPaneItemsFont, LOGFONT *pCodePaneFont, LOGFONT *pFlowchartPaneLabelFont, COLORREF &nFlowchartPaneBackgroundColor, COLORREF &nFlowchartPaneLabelColor, INT &nIndex, INT &nThreadID, SCROLLINFO *pListPaneHorzScrollInfo, SCROLLINFO *pListPaneVertScrollInfo) CONST
{
	return((m_wndView.GetLayout(nColumns, nWidths, sizeListPane, sizeFlowchartPane, sizeCodePane) && m_wndView.GetListTitleFont(pListPaneTitleFont) && m_wndView.GetListItemsFont(pListPaneItemsFont) && m_wndView.GetItemSourceCodeFont(pCodePaneFont) && m_wndView.GetItemFlowchartLabelsFont(pFlowchartPaneLabelFont) && m_wndView.GetItemFlowchartBackgroundColor(nFlowchartPaneBackgroundColor) && m_wndView.GetItemFlowchartLabelsColor(nFlowchartPaneLabelColor) && m_wndView.GetLayoutInfo(nIndex, nThreadID, pListPaneHorzScrollInfo, pListPaneVertScrollInfo)) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorWnd::Lock()
{
	return((GetTCService()->Lock() && CDisplayWnd::Lock()) ? TRUE : FALSE);
}

BOOL CTCProceduresMonitorWnd::Unlock()
{
	return((CDisplayWnd::Unlock() && GetTCService()->Unlock()) ? TRUE : FALSE);
}

BEGIN_MESSAGE_MAP(CTCProceduresMonitorWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CTCProceduresMonitorWnd)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_COMMAND(IDM_TCPROCEDURESMONITORSETTINGS, OnSettings)
	ON_COMMAND(IDM_TCPROCEDURESMONITORDETAILS, OnDetails)
	ON_COMMAND(IDM_TCPROCEDURESMONITORAUTHORIZATIONS, OnAuthorizations)
	ON_COMMAND(IDM_TCPROCEDURESMONITORSTART, OnStart)
	ON_COMMAND(IDM_TCPROCEDURESMONITORSUSPEND, OnSuspend)
	ON_COMMAND(IDM_TCPROCEDURESMONITORSTEPINTO, OnStepInto)
	ON_COMMAND(IDM_TCPROCEDURESMONITORSTEPOVER, OnStepOver)
	ON_COMMAND(IDM_TCPROCEDURESMONITORSTEPOUT, OnStepOut)
	ON_COMMAND(IDM_TCPROCEDURESMONITORABORT, OnAbort)
	ON_COMMAND(IDM_TCPROCEDURESMONITORRESET, OnReset)
	ON_COMMAND(IDM_TCPROCEDURESMONITORRESETINTERLOCKS, OnResetInterlocks)
	ON_COMMAND(IDM_TCPROCEDURESMONITORRELEASEWAITMODE, OnReleaseWaitMode)
	ON_COMMAND(IDM_TCPROCEDURESMONITORPRINT, OnPrint)
	ON_UPDATE_COMMAND_UI(IDM_TCPROCEDURESMONITORSETTINGS, OnUpdateSettings)
	ON_UPDATE_COMMAND_UI(IDM_TCPROCEDURESMONITORDETAILS, OnUpdateDetails)
	ON_UPDATE_COMMAND_UI(IDM_TCPROCEDURESMONITORAUTHORIZATIONS, OnUpdateAuthorizations)
	ON_UPDATE_COMMAND_UI(IDM_TCPROCEDURESMONITORSTART, OnUpdateStart)
	ON_UPDATE_COMMAND_UI(IDM_TCPROCEDURESMONITORSUSPEND, OnUpdateSuspend)
	ON_UPDATE_COMMAND_UI(IDM_TCPROCEDURESMONITORSTEPINTO, OnUpdateStepInto)
	ON_UPDATE_COMMAND_UI(IDM_TCPROCEDURESMONITORSTEPOVER, OnUpdateStepOver)
	ON_UPDATE_COMMAND_UI(IDM_TCPROCEDURESMONITORSTEPOUT, OnUpdateStepOut)
	ON_UPDATE_COMMAND_UI(IDM_TCPROCEDURESMONITORABORT, OnUpdateAbort)
	ON_UPDATE_COMMAND_UI(IDM_TCPROCEDURESMONITORRESET, OnUpdateReset)
	ON_UPDATE_COMMAND_UI(IDM_TCPROCEDURESMONITORRESETINTERLOCKS, OnUpdateResetInterlocks)
	ON_UPDATE_COMMAND_UI(IDM_TCPROCEDURESMONITORRELEASEWAITMODE, OnUpdateReleaseWaitMode)
	ON_UPDATE_COMMAND_UI(IDM_TCPROCEDURESMONITORPRINT, OnUpdatePrint)
	ON_UPDATE_COMMAND_UI(IDM_TCPROCEDURESMONITORBREAKALWAYS, OnUpdateBreakAlways)
	ON_UPDATE_COMMAND_UI(IDM_TCPROCEDURESMONITORBREAKATFAILEDTRIGGER, OnUpdateBreakAtFailedTrigger)
	ON_UPDATE_COMMAND_UI(IDM_TCPROCEDURESMONITORBREAKATFAILEDBODY, OnUpdateBreakAtFailedBody)
	ON_UPDATE_COMMAND_UI(IDM_TCPROCEDURESMONITORBREAKATFAILEDCONFIRMATION, OnUpdateBreakAtFailedConfirmation)
	ON_UPDATE_COMMAND_UI(IDM_TCPROCEDURESMONITORDISABLEBREAKPOINT, OnUpdateDisableBreakpoint)
	ON_UPDATE_COMMAND_UI(ID_TCPROCEDURESMONITOR_STATUSBAR_MESSAGEPANE, OnUpdateStatusBarMessagePane)
	ON_UPDATE_COMMAND_UI(ID_TCPROCEDURESMONITOR_STATUSBAR_UPLINKPANE, OnUpdateStatusBarUplinkPane)
	ON_UPDATE_COMMAND_UI(ID_TCPROCEDURESMONITOR_STATUSBAR_PEVPANE, OnUpdateStatusBarPEVPane)
	ON_UPDATE_COMMAND_UI(ID_TCPROCEDURESMONITOR_STATUSBAR_CEVPANE, OnUpdateStatusBarCEVPane)
	ON_UPDATE_COMMAND_UI(ID_TCPROCEDURESMONITOR_STATUSBAR_STATEPANE, OnUpdateStatusBarStatePane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorWnd message handlers

int CTCProceduresMonitorWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDisplayWnd::OnCreate(lpCreateStruct) != -1)
	{
		for (EnableDocking(CBRS_ALIGN_TOP); CreateToolBar() && CreateStatusBar() && CreateView() && LoadAccelTable(MAKEINTRESOURCE(IDR_TCPROCEDURESMONITORFRAME)); )
		{
			UpdateBars();
			return 0;
		}
	}
	return -1;
}

void CTCProceduresMonitorWnd::OnGetMinMaxInfo(MINMAXINFO *lpMMI)
{
	CRect  rView;
	CRect  rPane[2];
	CRect  rToolBar;
	CRect  rStatusBar;

	for (rView.SetRectEmpty(); IsWindow(m_wndView.GetSafeHwnd()); )
	{
		GetListView()->GetWindowRect(rPane[0]);
		GetItemView()->GetWindowRect(rPane[1]);
		rView.SetRect(0, 0, GetListView()->GetTrackSize().cx + GetItemView()->GetTrackSize().cx, GetListView()->GetTrackSize().cy + GetItemView()->GetTrackSize().cy + (rPane[1].top - rPane[0].bottom + 1) / 2);
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

void CTCProceduresMonitorWnd::OnSize(UINT nType, int cx, int cy)
{
	CDisplayWnd::OnSize(nType, cx, cy);
	m_wndView.RecalcLayout(TRUE);
}

BOOL CTCProceduresMonitorWnd::OnEraseBkgnd(CDC *pDC)
{
	if (!IsInitialized())
	{
		m_wndView.UpdateWindow();
		m_wndToolBar.UpdateWindow();
		m_wndStatusBar.UpdateWindow();
	}
	return TRUE;
}

void CTCProceduresMonitorWnd::OnSetFocus(CWnd *pOldWnd)
{
	if (IsWindow(pOldWnd->GetSafeHwnd()) && IsChild(pOldWnd))
	{
		GetParent()->SetFocus();
		return;
	}
	if (GetProcedureCount() > 0)
	{
		m_wndView.SetCurProcedure(max(GetCurProcedure(), 0));
		m_wndView.SetFocus();
		return;
	}
	CDisplayWnd::OnSetFocus(pOldWnd);
}

BOOL CTCProceduresMonitorWnd::OnCloseSettingsDialog(UINT nCode)
{
	BOOL  bLogEvent;
	BOOL  bToolTips;
	BOOL  bModeFlag;
	BOOL  bStateFlag;
	UINT  nCheckFlags;
	UINT  nLogPolicy;
	UINT  nLogCount;
	LOGFONT  fntCode;
	LOGFONT  fntTitle;
	LOGFONT  fntItems;
	LOGFONT  fntLabels;
	CString  szLogFileName[2];
	COLORREF  nColor[2];
	CUIntArray  nColumns;
	DWORDLONG  dwLogRetention;
	CTimeSpan  tLogRetention;
	CTCProceduresMonitorItems  pItems;
	CTCProceduresMonitorPrintJobs  pJobs;

	if (nCode == IDOK)
	{
		if (m_dlgSettings.IsLayoutModified())
		{
			m_dlgSettings.GetColumns(nColumns);
			m_dlgSettings.GetTitleFont(&fntTitle);
			m_dlgSettings.GetItemsFont(&fntItems);
			m_dlgSettings.GetToolTipMode(bToolTips);
			m_dlgSettings.GetSourceCodeFont(&fntCode);
			m_dlgSettings.GetFlowchartLabelsFont(&fntLabels);
			m_dlgSettings.GetFlowchartLabelsColor(nColor[0]);
			m_dlgSettings.GetFlowchartBackgroundColor(nColor[1]);
			if (!SetLayout(nColumns) || !SetListTitleFont(&fntTitle) || !SetListItemsFont(&fntItems) || !SetItemSourceCodeFont(&fntCode) || !SetItemFlowchartTitleFont(&fntTitle) || !SetItemFlowchartLabelsFont(&fntLabels) || !SetItemFlowchartLabelsColor(nColor[0]) || !SetItemFlowchartBackgroundColor(nColor[1]) || !EnableToolTipMode(bToolTips)) return FALSE;
		}
		if (m_dlgSettings.IsContentsModified())
		{
			m_dlgSettings.GetContents(pItems);
			m_dlgSettings.GetCheckOptions(nCheckFlags);
			m_dlgSettings.GetReleaseWaitModeFlag(bModeFlag);
			m_dlgSettings.GetDisabledStateFlag(bStateFlag);
			if (!SetProcedures(pItems) || !SetTelecommandingMode(TCPROCEDURESMONITOR_MODE_DEFAULT) || !SetTelecommandingState((bStateFlag) ? (GetTelecommandingState() | TCPROCEDURESMONITOR_STATE_DISABLED) : (GetTelecommandingState() & ~TCPROCEDURESMONITOR_STATE_DISABLED)) || !SetTelecommandingChecks(nCheckFlags) || !EnableTelecommandingReleaseWaitMode(bModeFlag)) return FALSE;
		}
		if (m_dlgSettings.IsLoggingModified())
		{
			m_dlgSettings.GetLoggingOptions(nLogPolicy, szLogFileName[0], dwLogRetention, tLogRetention, szLogFileName[1], nLogCount, bLogEvent);
			if (!SetLoggingOptions(nLogPolicy, szLogFileName[0], dwLogRetention, tLogRetention, szLogFileName[1], nLogCount, bLogEvent)) return FALSE;
		}
		if (m_dlgSettings.IsPrintingModified())
		{
			m_dlgSettings.GetPrintJobs(pJobs);
			if (!SetPrintJobs(pJobs)) return FALSE;
		}
		UpdateContents();
		UpdateAllPanes();
	}
	return TRUE;
}

void CTCProceduresMonitorWnd::OnSettings()
{
	ReportEvent((m_dlgSettings.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CTCProceduresMonitorWnd::OnDetails()
{
	CTCProceduresMonitorItem  cItem;

	if (GetProcedureInfo(GetCurProcedure(), &cItem) && cItem.GetID() >= 0)
	{
		ReportEvent((m_dlgDetails.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
		return;
	}
	ReportEvent((m_dlgAcknowledgments.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CTCProceduresMonitorWnd::OnAuthorizations()
{
	ReportEvent((m_dlgAuthorizations.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CTCProceduresMonitorWnd::OnStart()
{
	INT  nIndex;
	CHourglassCursor  cCursor;

	if (IsProcedureRunning((nIndex = GetCurProcedure())))
	{
		ResumeProcedure(nIndex);
		return;
	}
	if (!StartProcedure(nIndex))
	{
		AlertProcedure(nIndex, TCPROCEDURESMONITORITEM_ALERTTYPE_ERROR, STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGE_STARTFAILURE));
		return;
	}
}

void CTCProceduresMonitorWnd::OnSuspend()
{
	CHourglassCursor  cCursor;

	SuspendProcedure(GetCurProcedure());
}

void CTCProceduresMonitorWnd::OnStepInto()
{
	CHourglassCursor  cCursor;

	StepIntoProcedure(GetCurProcedure());
}

void CTCProceduresMonitorWnd::OnStepOver()
{
	CHourglassCursor  cCursor;

	StepOverProcedure(GetCurProcedure());
}

void CTCProceduresMonitorWnd::OnStepOut()
{
	CHourglassCursor  cCursor;

	StepOutProcedure(GetCurProcedure());
}

void CTCProceduresMonitorWnd::OnAbort()
{
	CHourglassCursor  cCursor;

	AbortProcedure(GetCurProcedure());
}

void CTCProceduresMonitorWnd::OnReset()
{
	CHourglassCursor  cCursor;

	ResetProcedure(GetCurProcedure());
}

void CTCProceduresMonitorWnd::OnResetInterlocks()
{
	CHourglassCursor  cCursor;

	DoResetInterlocks();
}

void CTCProceduresMonitorWnd::OnReleaseWaitMode()
{
	CHourglassCursor  cCursor;

	EnableTelecommandingReleaseWaitMode(!IsTelecommandingReleaseWaitModeEnabled());
}

void CTCProceduresMonitorWnd::OnPrint()
{
	CHourglassCursor  cCursor;

	ReportEvent((!Print()) ? SYSTEM_WARNING_DISPLAY_PRINT_FAILURE : SYSTEM_NOERROR);
}

void CTCProceduresMonitorWnd::OnUpdateSettings(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized());
	pCmdUI->SetCheck(IsWindow(m_dlgSettings.GetSafeHwnd()));
}

void CTCProceduresMonitorWnd::OnUpdateDetails(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized() && GetCurProcedure() >= 0);
	pCmdUI->SetCheck(IsWindow(m_dlgDetails.GetSafeHwnd()) || IsWindow(m_dlgAcknowledgments.GetSafeHwnd()));
}

void CTCProceduresMonitorWnd::OnUpdateAuthorizations(CCmdUI *pCmdUI)
{
	INT  nIndex;

	pCmdUI->Enable(IsInitialized() && (nIndex = GetCurProcedure()) >= 0 && CanAuthorizeTelecommands(nIndex));
	pCmdUI->SetCheck(IsWindow(m_dlgAuthorizations.GetSafeHwnd()));
}

void CTCProceduresMonitorWnd::OnUpdateStart(CCmdUI *pCmdUI)
{
	INT  nIndex;

	pCmdUI->Enable(IsInitialized() && (nIndex = GetCurProcedure()) >= 0 && (!IsProcedureRunning(nIndex) || IsProcedureSuspended(nIndex)) && !IsProcedureDisabled(nIndex) && CanStartProcedure(nIndex));
}

void CTCProceduresMonitorWnd::OnUpdateSuspend(CCmdUI *pCmdUI)
{
	INT  nIndex;

	pCmdUI->Enable(IsInitialized() && IsProcedureRunning((nIndex = GetCurProcedure())) && !IsProcedureSuspended(nIndex) && CanBreakProcedure(nIndex));
}

void CTCProceduresMonitorWnd::OnUpdateStepInto(CCmdUI *pCmdUI)
{
	INT  nIndex;

	pCmdUI->Enable(IsInitialized() && IsProcedureRunning((nIndex = GetCurProcedure())) && IsProcedureSuspended(nIndex) && CanStepIntoProcedure(nIndex));
}

void CTCProceduresMonitorWnd::OnUpdateStepOver(CCmdUI *pCmdUI)
{
	INT  nIndex;

	pCmdUI->Enable(IsInitialized() && IsProcedureRunning((nIndex = GetCurProcedure())) && IsProcedureSuspended(nIndex) && CanStepOverProcedure(nIndex));
}

void CTCProceduresMonitorWnd::OnUpdateStepOut(CCmdUI *pCmdUI)
{
	INT  nIndex;

	pCmdUI->Enable(IsInitialized() && IsProcedureRunning((nIndex = GetCurProcedure())) && IsProcedureSuspended(nIndex) && CanStepOutProcedure(nIndex));
}

void CTCProceduresMonitorWnd::OnUpdateAbort(CCmdUI *pCmdUI)
{
	INT  nIndex;

	pCmdUI->Enable(IsInitialized() && IsProcedureRunning((nIndex = GetCurProcedure())) && CanBreakProcedure(nIndex));
}

void CTCProceduresMonitorWnd::OnUpdateReset(CCmdUI *pCmdUI)
{
	INT  nIndex;

	pCmdUI->Enable(IsInitialized() && (nIndex = GetCurProcedure()) >= 0 && !IsProcedureRunning(nIndex) && CanResetProcedure(nIndex));
}

void CTCProceduresMonitorWnd::OnUpdateResetInterlocks(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized() && CanResetInterlocks() && (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE)));
	pCmdUI->SetCheck(IsWindow(m_dlgInterlocks.GetSafeHwnd()));
}

void CTCProceduresMonitorWnd::OnUpdateReleaseWaitMode(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized());
	pCmdUI->SetCheck(IsTelecommandingReleaseWaitModeEnabled());
}

void CTCProceduresMonitorWnd::OnUpdatePrint(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && IsDefaultPrinterAvailable() && CanPrint()) ? TRUE : FALSE);
}

void CTCProceduresMonitorWnd::OnUpdateBreakAlways(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized());
}

void CTCProceduresMonitorWnd::OnUpdateBreakAtFailedTrigger(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized());
}

void CTCProceduresMonitorWnd::OnUpdateBreakAtFailedBody(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized());
}

void CTCProceduresMonitorWnd::OnUpdateBreakAtFailedConfirmation(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized());
}

void CTCProceduresMonitorWnd::OnUpdateDisableBreakpoint(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized());
}

void CTCProceduresMonitorWnd::OnUpdateStatusBarMessagePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CTCProceduresMonitorWnd::OnUpdateStatusBarUplinkPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CTCProceduresMonitorWnd::OnUpdateStatusBarPEVPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CTCProceduresMonitorWnd::OnUpdateStatusBarCEVPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CTCProceduresMonitorWnd::OnUpdateStatusBarStatePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}
