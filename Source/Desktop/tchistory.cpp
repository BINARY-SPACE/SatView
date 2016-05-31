// TCHISTORY.CPP : Telecommand History Display Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the telecommand history
// display related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2007/04/04 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static UINT BASED_CODE nTCHistoryStatusBarIndicators[] =
{
	ID_TCHISTORY_STATUSBAR_MESSAGEPANE,
	ID_TCHISTORY_STATUSBAR_MODEPANE,
	ID_TCHISTORY_STATUSBAR_TYPEPANE
};



/////////////////////////////////////////////////////////////////////////////
// CTCHistoryItem

CTCHistoryItem::CTCHistoryItem() : CTCItem()
{
	m_nSourceType = TCITEM_SOURCETYPE_NONE;
	m_bSelected = FALSE;
}

BOOL CTCHistoryItem::SetAlerts(CONST CByteArray &nAlertsInfo)
{
	INT  cbData;
	INT  cbMessage;
	INT  cbMessages;
	CByteArray  nMessagesData;
	PROPERTIESDATA  sData;

	for (CopyMemory(&sData, nAlertsInfo.GetData(), (nAlertsInfo.GetSize() >= sizeof(PROPERTIESDATA)) ? sizeof(PROPERTIESDATA) : 0); nAlertsInfo.GetSize() >= sizeof(PROPERTIESDATA) && nAlertsInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(PROPERTIESDATA) + sData.cbAlertTypes + sData.cbAlertMessages[0] + sData.cbAlertMessages[1] && sData.cbAlertTypes >= 0 && sData.cbAlertMessages[0] >= 0 && sData.cbAlertMessages[1] >= 0; )
	{
		for (m_nAlertTypes.SetSize(sData.cbAlertTypes / sizeof(UINT)), m_nAlertMessages.SetSize(sData.cbAlertMessages[0] / sizeof(UINT)), nMessagesData.SetSize(sData.cbAlertMessages[1]), CopyMemory(m_nAlertTypes.GetData(), nAlertsInfo.GetData() + (cbData = sizeof(PROPERTIESDATA)), sData.cbAlertTypes), CopyMemory(m_nAlertMessages.GetData(), nAlertsInfo.GetData() + (cbData = cbData + sData.cbAlertTypes), sData.cbAlertMessages[0]), CopyMemory(nMessagesData.GetData(), nAlertsInfo.GetData() + (cbData = cbData + sData.cbAlertMessages[0]), sData.cbAlertMessages[1]), m_szAlertMessages.RemoveAll(), cbMessages = 0; cbMessages < sData.cbAlertMessages[1]; cbMessages += (cbMessage = (m_szAlertMessages.GetAt(m_szAlertMessages.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szAlertMessages.Add((LPCTSTR)(nMessagesData.GetData() + cbMessages));
			continue;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryItem::GetAlerts(CByteArray &nAlertsInfo) CONST
{
	INT  cbData;
	INT  nMessage;
	INT  nMessages;
	CByteArray  nMessagesData;
	PROPERTIESDATA  sData;

	for (nMessage = 0, nMessages = (INT)m_szAlertMessages.GetSize(), sData.cbAlertTypes = (INT)(m_nAlertTypes.GetSize()*sizeof(UINT)), sData.cbAlertMessages[0] = (INT)(m_nAlertMessages.GetSize()*sizeof(UINT)), sData.cbAlertMessages[1] = 0; nMessage < nMessages; nMessage++, sData.cbAlertMessages[1] += cbData)
	{
		nMessagesData.SetSize(sData.cbAlertMessages[1] + (cbData = (m_szAlertMessages.GetAt(nMessage).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nMessagesData.GetData() + sData.cbAlertMessages[1], (LPCTSTR)m_szAlertMessages.GetAt(nMessage), cbData);
	}
	for (nAlertsInfo.SetSize((sData.cbSize = sizeof(PROPERTIESDATA) + sData.cbAlertTypes + sData.cbAlertMessages[0] + sData.cbAlertMessages[1])); nAlertsInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nAlertsInfo.GetData(), &sData, sizeof(PROPERTIESDATA));
		CopyMemory(nAlertsInfo.GetData() + (cbData = sizeof(PROPERTIESDATA)), m_nAlertTypes.GetData(), sData.cbAlertTypes);
		CopyMemory(nAlertsInfo.GetData() + (cbData = cbData + sData.cbAlertTypes), m_nAlertMessages.GetData(), sData.cbAlertMessages[0]);
		CopyMemory(nAlertsInfo.GetData() + (cbData = cbData + sData.cbAlertMessages[0]), nMessagesData.GetData(), sData.cbAlertMessages[1]);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryItem::Alert(UINT nType, UINT nMessage, LPCTSTR pszMessage, BOOL bOverwrite)
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = (!bOverwrite) ? (INT)m_nAlertMessages.GetSize() : 0, nCount = (INT)m_nAlertMessages.GetSize(); nIndex < nCount; nIndex++)
	{
		if (nMessage == m_nAlertMessages.GetAt(nIndex)) break;
		continue;
	}
	if (nType >= TCHISTORYITEM_ALERTTYPE_INFORMATION  &&  nType <= TCHISTORYITEM_ALERTTYPE_ERROR)
	{
		m_nAlertTypes.SetAtGrow(nIndex, nType);
		m_nAlertMessages.SetAtGrow(nIndex, nMessage);
		m_szAlertMessages.SetAtGrow(nIndex, pszMessage);
		return TRUE;
	}
	return FALSE;
}
BOOL CTCHistoryItem::Alert(UINT nType, UINT nMessage, BOOL bEnable)
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = ((nType != TCHISTORYITEM_ALERTTYPE_ANY && !bEnable) || nMessage == (UINT)-1) ? (INT)m_nAlertMessages.GetSize() : 0, nCount = (INT)m_nAlertMessages.GetSize(); nIndex < nCount; nIndex++)
	{
		if ((bEnable  &&  nMessage == m_nAlertMessages.GetAt(nIndex)) || (!bEnable  &&  nMessage == m_nAlertMessages.GetAt(nCount - nIndex - 1))) break;
		continue;
	}
	if (nType >= TCHISTORYITEM_ALERTTYPE_INFORMATION  &&  nType <= TCHISTORYITEM_ALERTTYPE_ERROR  &&  nMessage != (UINT)-1 && bEnable)
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
			if (nType == TCHISTORYITEM_ALERTTYPE_ANY  &&  nIndex < nCount)
			{
				m_nAlertTypes.RemoveAt(nCount - nIndex - 1);
				m_nAlertMessages.RemoveAt(nCount - nIndex - 1);
				m_szAlertMessages.RemoveAt(nCount - nIndex - 1);
				return TRUE;
			}
			for (nIndex = 0, nCount = ((nType >= TCHISTORYITEM_ALERTTYPE_INFORMATION && nType <= TCHISTORYITEM_ALERTTYPE_ERROR) || nType == TCHISTORYITEM_ALERTTYPE_NONE) ? (INT)m_nAlertTypes.GetSize() : -1; nIndex < nCount; nIndex++)
			{
				if ((nType == TCHISTORYITEM_ALERTTYPE_NONE || m_nAlertTypes.GetAt(nIndex) == nType) && m_nAlertMessages.GetAt(nIndex) == nMessage)
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
			if (nType == TCHISTORYITEM_ALERTTYPE_ANY  &&  nCount > 0)
			{
				m_nAlertTypes.RemoveAt(nCount - 1);
				m_nAlertMessages.RemoveAt(nCount - 1);
				m_szAlertMessages.RemoveAt(nCount - 1);
				return TRUE;
			}
			for (nIndex = 0, nCount = (nType >= TCHISTORYITEM_ALERTTYPE_INFORMATION && nType <= TCHISTORYITEM_ALERTTYPE_ERROR) ? (INT)m_nAlertTypes.GetSize() : -1; nIndex < nCount; nIndex++)
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
			if (nType == TCHISTORYITEM_ALERTTYPE_NONE)
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

UINT CTCHistoryItem::IsAlerted(UINT nMessage, CString &szMessage) CONST
{
	INT  nIndex;
	INT  nCount;
	UINT  nType;

	for (nIndex = 0, nCount = (INT)m_nAlertMessages.GetSize(), nType = TCHISTORYITEM_ALERTTYPE_NONE, szMessage.Empty(); nIndex < nCount; nIndex++)
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
UINT CTCHistoryItem::IsAlerted(UINT nMessage) CONST
{
	CString  szMessage;

	return IsAlerted(nMessage, szMessage);
}

INT CTCHistoryItem::GetAlertCount(UINT nType) CONST
{
	INT  nIndex;
	INT  nCount[2];

	for (nIndex = 0, nCount[0] = (INT)m_nAlertTypes.GetSize(), nCount[1] = 0; nIndex < nCount[0]; nIndex++)
	{
		if (m_nAlertTypes.GetAt(nIndex) == nType || nType == TCHISTORYITEM_ALERTTYPE_ANY)
		{
			nCount[1]++;
			continue;
		}
	}
	return nCount[1];
}

VOID CTCHistoryItem::Select(BOOL bSelect)
{
	m_bSelected = bSelect;
}

BOOL CTCHistoryItem::IsSelected() CONST
{
	return m_bSelected;
}

BOOL CTCHistoryItem::Copy(CONST CTCHistoryItem *pItem)
{
	m_bSelected = pItem->m_bSelected;
	m_nAlertTypes.Copy(pItem->m_nAlertTypes);
	m_nAlertMessages.Copy(pItem->m_nAlertMessages);
	m_szAlertMessages.Copy(pItem->m_szAlertMessages);
	return CTCItem::Copy(pItem);
}

BOOL CTCHistoryItem::Compare(CONST CTCHistoryItem *pItem) CONST
{
	INT  nMessage;
	INT  nMessages;

	for (nMessage = 0, nMessages = (pItem->m_nAlertTypes.GetSize() == m_nAlertTypes.GetSize() && pItem->m_nAlertMessages.GetSize() == m_nAlertMessages.GetSize() && !memcmp(pItem->m_nAlertTypes.GetData(), m_nAlertTypes.GetData(), m_nAlertTypes.GetSize()*sizeof(UINT)) && !memcmp(pItem->m_nAlertMessages.GetData(), m_nAlertMessages.GetData(), m_nAlertMessages.GetSize()*sizeof(UINT)) && pItem->m_szAlertMessages.GetSize() == m_szAlertMessages.GetSize() && pItem->m_bSelected == m_bSelected) ? (INT)m_szAlertMessages.GetSize() : -1; nMessage < nMessages; nMessage++)
	{
		if (pItem->m_szAlertMessages.GetAt(nMessage) != m_szAlertMessages.GetAt(nMessage)) break;
		continue;
	}
	return((nMessage == nMessages) ? CTCItem::Compare(pItem) : FALSE);
}

BOOL CTCHistoryItem::Map(CByteArray &nInfo) CONST
{
	return CTCItem::Map(nInfo);
}

BOOL CTCHistoryItem::Unmap(CONST CByteArray &nInfo)
{
	return CTCItem::Unmap(nInfo);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistoryItems

CTCHistoryItems::CTCHistoryItems() : CTCItems()
{
	return;
}

CTCHistoryItems::~CTCHistoryItems()
{
	RemoveAll();
}

INT CTCHistoryItems::Add(CTCHistoryItem *pItem)
{
	return CTCItems::Add(pItem);
}

INT CTCHistoryItems::Collect(INT nIndex, CTCHistoryItems &pItems) CONST
{
	INT  nItem;
	INT  nItems;
	CUIntArray  nItemIDs;
	CTCHistoryItem  *pItem[2];

	for (nItem = 0, nItems = Collect(nIndex, nItemIDs), pItems.RemoveAll(); nItem < nItems; nItem++)
	{
		if ((pItem[1] = ((pItem[0] = GetAt(nItemIDs.GetAt(nItem)))) ? new CTCHistoryItem : (CTCHistoryItem *)NULL))
		{
			if (pItem[1]->Copy(pItem[0]) && pItems.Add(pItem[1]) >= 0) continue;
			delete pItem[1];
		}
		pItems.RemoveAll();
		break;
	}
	return((INT)pItems.GetSize());
}
INT CTCHistoryItems::Collect(INT nIndex, CUIntArray &nItemIDs) CONST
{
	return CTCItems::Collect(nIndex, nItemIDs);
}
INT CTCHistoryItems::Collect(INT nIndex, CPtrArray &pItems) CONST
{
	return CTCItems::Collect(nIndex, pItems);
}

CTCHistoryItem *CTCHistoryItems::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCHistoryItem *)CPtrArray::GetAt(nIndex) : (CTCHistoryItem *)NULL);
}

CTCHistoryItem *CTCHistoryItems::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCHistoryItem *)CPtrArray::GetAt(nIndex) : (CTCHistoryItem *)NULL);
}

VOID CTCHistoryItems::RemoveAll()
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

BOOL CTCHistoryItems::Copy(CONST CTCHistoryItems *pItems)
{
	INT  nItem;
	INT  nItems;
	CTCHistoryItem  *pItem;

	for (nItem = 0, nItems = (INT)pItems->GetSize(), RemoveAll(); nItem < nItems; nItem++)
	{
		if ((pItem = new CTCHistoryItem) != (CTCHistoryItem *)NULL)
		{
			pItem->Copy(pItems->GetAt(nItem));
			InsertAt(nItem, pItem, 1);
			continue;
		}
		break;
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

BOOL CTCHistoryItems::Compare(CONST CTCHistoryItems *pItems) CONST
{
	INT  nItem;
	INT  nItems;
	CTCHistoryItem  *pItem;

	for (nItem = 0, nItems = (pItems->GetSize() == GetSize()) ? (INT)GetSize() : -1; nItem < nItems; nItem++)
	{
		if ((pItem = pItems->GetAt(nItem)) && pItem->Compare(GetAt(nItem))) continue;
		break;
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

BOOL CTCHistoryItems::Map(CByteArray &nInfo) CONST
{
	INT  nItem;
	INT  nItems;
	CByteArray  nItemData;
	CTCHistoryItem  *pItem;

	for (nItem = 0, nItems = (INT)GetSize(), nInfo.RemoveAll(); nItem < nItems; nItem++)
	{
		if ((pItem = GetAt(nItem)) && pItem->Map(nItemData) && nInfo.Append(nItemData) >= 0) continue;
		break;
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

BOOL CTCHistoryItems::Unmap(CONST CByteArray &nInfo)
{
	INT  cbItem;
	INT  cbItems;
	CByteArray  nItemData;
	CTCHistoryItem  *pItem;

	for (cbItems = 0, RemoveAll(); cbItems < nInfo.GetSize(); cbItems += cbItem)
	{
		for (CopyMemory(&cbItem, nInfo.GetData() + cbItems, sizeof(cbItem)), nItemData.SetSize(max(min(cbItem, nInfo.GetSize() - cbItems), 0)); nItemData.GetSize() >= 0; )
		{
			CopyMemory(nItemData.GetData(), nInfo.GetData() + cbItems, nItemData.GetSize());
			break;
		}
		if ((pItem = new CTCHistoryItem))
		{
			if (pItem->Unmap(nItemData) && Add(pItem) >= 0) continue;
			delete pItem;
		}
		break;
	}
	return((cbItems == nInfo.GetSize()) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistoryPrintJobInfo

CTCHistoryPrintJobInfo::CTCHistoryPrintJobInfo() : CObject()
{
	m_nPrintMode = 0;
	m_nPrintRange[0] = 0;
	m_nPrintRange[1] = 0;
	m_tPrintRange[0][0] = 0;
	m_tPrintRange[0][1] = 0;
	m_tPrintRange[1][0] = 0;
	m_tPrintRange[1][1] = 0;
}

VOID CTCHistoryPrintJobInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CTCHistoryPrintJobInfo::GetName() CONST
{
	return m_szName;
}

VOID CTCHistoryPrintJobInfo::SetProfile(LPCTSTR pszProfile)
{
	m_szProfile = pszProfile;
}

CString CTCHistoryPrintJobInfo::GetProfile() CONST
{
	return m_szProfile;
}

VOID CTCHistoryPrintJobInfo::SetComments(LPCTSTR pszComments)
{
	m_szComments = pszComments;
}

CString CTCHistoryPrintJobInfo::GetComments() CONST
{
	return m_szComments;
}

BOOL CTCHistoryPrintJobInfo::SetPrintMode(UINT nMode)
{
	m_nPrintMode = nMode;
	return TRUE;
}

UINT CTCHistoryPrintJobInfo::GetPrintMode() CONST
{
	return m_nPrintMode;
}

BOOL CTCHistoryPrintJobInfo::SetPrintRange(UINT nMin, UINT nMax)
{
	if (m_nPrintMode & TCHISTORY_PRINT_ITEMRANGE)
	{
		m_nPrintRange[0] = nMin;
		m_nPrintRange[1] = nMax;
		return TRUE;
	}
	return FALSE;
}
BOOL CTCHistoryPrintJobInfo::SetPrintRange(CONST CTimeKey &tMin, CONST CTimeKey &tMax, BOOL bReleaseTime)
{
	if ((m_nPrintMode & TCHISTORY_PRINT_RELEASETIMERANGE) && bReleaseTime)
	{
		m_tPrintRange[0][0] = tMin;
		m_tPrintRange[0][1] = tMax;
		return TRUE;
	}
	if ((m_nPrintMode & TCHISTORY_PRINT_EXECUTIONTIMERANGE) && !bReleaseTime)
	{
		m_tPrintRange[1][0] = tMin;
		m_tPrintRange[1][1] = tMax;
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryPrintJobInfo::GetPrintRange(UINT &nMin, UINT &nMax) CONST
{
	if (m_nPrintMode & TCHISTORY_PRINT_ITEMRANGE)
	{
		nMin = m_nPrintRange[0];
		nMax = m_nPrintRange[1];
		return TRUE;
	}
	return FALSE;
}
BOOL CTCHistoryPrintJobInfo::GetPrintRange(CTimeKey &tMin, CTimeKey &tMax, BOOL bReleaseTime) CONST
{
	if ((m_nPrintMode & TCHISTORY_PRINT_RELEASETIMERANGE) && bReleaseTime)
	{
		tMin = m_tPrintRange[0][0];
		tMax = m_tPrintRange[0][1];
		return TRUE;
	}
	if ((m_nPrintMode & TCHISTORY_PRINT_EXECUTIONTIMERANGE) && !bReleaseTime)
	{
		tMin = m_tPrintRange[1][0];
		tMax = m_tPrintRange[1][1];
		return TRUE;
	}
	return FALSE;
}

VOID CTCHistoryPrintJobInfo::Copy(CONST CTCHistoryPrintJobInfo *pJobInfo)
{
	m_szName = pJobInfo->m_szName;
	m_szProfile = pJobInfo->m_szProfile;
	m_szComments = pJobInfo->m_szComments;
	m_nPrintMode = pJobInfo->m_nPrintMode;
	m_nPrintRange[0] = pJobInfo->m_nPrintRange[0];
	m_nPrintRange[1] = pJobInfo->m_nPrintRange[1];
	m_tPrintRange[0][0] = pJobInfo->m_tPrintRange[0][0];
	m_tPrintRange[0][1] = pJobInfo->m_tPrintRange[0][1];
	m_tPrintRange[1][0] = pJobInfo->m_tPrintRange[1][0];
	m_tPrintRange[1][1] = pJobInfo->m_tPrintRange[1][1];
}

BOOL CTCHistoryPrintJobInfo::Compare(CONST CTCHistoryPrintJobInfo *pJobInfo) CONST
{
	return((pJobInfo->m_szName == m_szName  &&  pJobInfo->m_szProfile == m_szProfile  &&  pJobInfo->m_szComments == m_szComments  &&  pJobInfo->m_nPrintMode == m_nPrintMode && ((m_nPrintMode & TCHISTORY_PRINT_ITEMRANGE) != TCHISTORY_PRINT_ITEMRANGE || (pJobInfo->m_nPrintRange[0] == m_nPrintRange[0] && pJobInfo->m_nPrintRange[1] == m_nPrintRange[1])) && ((m_nPrintMode & TCHISTORY_PRINT_RELEASETIMERANGE) != TCHISTORY_PRINT_RELEASETIMERANGE || (pJobInfo->m_tPrintRange[0][0] == m_tPrintRange[0][0] && pJobInfo->m_tPrintRange[0][1] == m_tPrintRange[0][1])) && ((m_nPrintMode & TCHISTORY_PRINT_EXECUTIONTIMERANGE) != TCHISTORY_PRINT_EXECUTIONTIMERANGE || (pJobInfo->m_tPrintRange[1][0] == m_tPrintRange[1][0] && pJobInfo->m_tPrintRange[1][1] == m_tPrintRange[1][1]))) ? TRUE : FALSE);
}

BOOL CTCHistoryPrintJobInfo::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbProfile = (m_szProfile.GetLength() + 1)*sizeof(TCHAR);
	sData.cbComments = (m_szComments.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbProfile + sData.cbComments)), sData.nPrintMode = m_nPrintMode, sData.nPrintRange[0] = m_nPrintRange[0], sData.nPrintRange[1] = m_nPrintRange[1], sData.tPrintRange[0][0] = m_tPrintRange[0][0].GetTime(), sData.tPrintRange[0][1] = m_tPrintRange[0][1].GetTime(), sData.tPrintRange[1][0] = m_tPrintRange[1][0].GetTime(), sData.tPrintRange[1][1] = m_tPrintRange[1][1].GetTime(); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szProfile, sData.cbProfile);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbProfile), (LPCTSTR)m_szComments, sData.cbComments);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryPrintJobInfo::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbProfile + sData.cbComments && sData.cbName > 0 && sData.cbProfile > 0 && sData.cbComments > 0; )
	{
		CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName));
		CopyMemory(m_szProfile.GetBufferSetLength(STRINGCHARS(sData.cbProfile)), nInfo.GetData() + (cbData = cbData + sData.cbName), STRINGBYTES(sData.cbProfile));
		CopyMemory(m_szComments.GetBufferSetLength(STRINGCHARS(sData.cbComments)), nInfo.GetData() + (cbData = cbData + sData.cbProfile), STRINGBYTES(sData.cbComments));
		m_nPrintMode = sData.nPrintMode;
		m_nPrintRange[0] = sData.nPrintRange[0];
		m_nPrintRange[1] = sData.nPrintRange[1];
		m_tPrintRange[0][0] = sData.tPrintRange[0][0];
		m_tPrintRange[0][1] = sData.tPrintRange[0][1];
		m_tPrintRange[1][0] = sData.tPrintRange[1][0];
		m_tPrintRange[1][1] = sData.tPrintRange[1][1];
		m_szName.ReleaseBuffer();
		m_szProfile.ReleaseBuffer();
		m_szComments.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistoryPrintJobs

CTCHistoryPrintJobs::CTCHistoryPrintJobs() : CPtrArray()
{
	return;
}

CTCHistoryPrintJobs::~CTCHistoryPrintJobs()
{
	RemoveAll();
}

INT CTCHistoryPrintJobs::Add(CTCHistoryPrintJobInfo *pJobInfo)
{
	return((INT)CPtrArray::Add(pJobInfo));
}

INT CTCHistoryPrintJobs::Find(LPCTSTR pszName) CONST
{
	INT  nJob;
	INT  nJobs;
	CTCHistoryPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = GetAt(nJob)) && pJobInfo->GetName() == pszName) break;
		continue;
	}
	return((nJob < nJobs) ? nJob : -1);
}

CTCHistoryPrintJobInfo *CTCHistoryPrintJobs::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCHistoryPrintJobInfo *)CPtrArray::GetAt(nIndex) : (CTCHistoryPrintJobInfo *)NULL);
}

CTCHistoryPrintJobInfo *CTCHistoryPrintJobs::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCHistoryPrintJobInfo *)CPtrArray::GetAt(nIndex) : (CTCHistoryPrintJobInfo *)NULL);
}

VOID CTCHistoryPrintJobs::RemoveAll()
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

BOOL CTCHistoryPrintJobs::Copy(CONST CTCHistoryPrintJobs *pPrintJobs)
{
	INT  nJob;
	INT  nJobs;
	CTCHistoryPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)pPrintJobs->GetSize(), RemoveAll(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = new CTCHistoryPrintJobInfo))
		{
			pJobInfo->Copy(pPrintJobs->GetAt(nJob));
			InsertAt(nJob, pJobInfo, 1);
			continue;
		}
		break;
	}
	return((nJob == nJobs) ? TRUE : FALSE);
}

BOOL CTCHistoryPrintJobs::Compare(CONST CTCHistoryPrintJobs *pPrintJobs) CONST
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

BOOL CTCHistoryPrintJobs::Map(CByteArray &nInfo) CONST
{
	INT  nJob;
	INT  nJobs;
	CByteArray  nJobData;
	CTCHistoryPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)GetSize(), nInfo.RemoveAll(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = GetAt(nJob)) && pJobInfo->Map(nJobData) && nInfo.Append(nJobData) >= 0) continue;
		break;
	}
	return((nJob == nJobs) ? TRUE : FALSE);
}

BOOL CTCHistoryPrintJobs::Unmap(CONST CByteArray &nInfo)
{
	INT  cbJob;
	INT  cbJobs;
	CByteArray  nJobData;
	CTCHistoryPrintJobInfo  *pJobInfo;

	for (cbJobs = 0, RemoveAll(); cbJobs < nInfo.GetSize(); cbJobs += cbJob)
	{
		for (CopyMemory(&cbJob, nInfo.GetData() + cbJobs, sizeof(cbJob)), nJobData.SetSize(max(min(cbJob, nInfo.GetSize() - cbJobs), 0)); nJobData.GetSize() >= 0; )
		{
			CopyMemory(nJobData.GetData(), nInfo.GetData() + cbJobs, nJobData.GetSize());
			break;
		}
		if ((pJobInfo = new CTCHistoryPrintJobInfo))
		{
			if (pJobInfo->Unmap(nJobData) && Add(pJobInfo) >= 0) continue;
			delete pJobInfo;
		}
		break;
	}
	if ((pJobInfo = (!GetSize()) ? new CTCHistoryPrintJobInfo : (CTCHistoryPrintJobInfo *)NULL))
	{
		for (pJobInfo->SetName(STRING(IDS_PRINTJOB_DEFAULTNAME)), pJobInfo->SetProfile(STRING(IDS_PRINTPROFILE_DEFAULTNAME)); Add(pJobInfo) >= 0; ) return TRUE;
		delete pJobInfo;
		return FALSE;
	}
	return((cbJobs == nInfo.GetSize()) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySettingsLayoutPage property page

IMPLEMENT_DYNCREATE(CTCHistorySettingsLayoutPage, CLocalePropertyPage)

CTCHistorySettingsLayoutPage::CTCHistorySettingsLayoutPage() : CLocalePropertyPage(CTCHistorySettingsLayoutPage::IDD)
{
	//{{AFX_DATA_INIT(CTCHistorySettingsLayoutPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySettingsLayoutPage::Initialize()
{
	CString  szLayout;
	CTCHistoryOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && (pDialog->GetLayout(szLayout, m_nColumns[0]) || GetParentDisplay()->GetLayout(szLayout, m_nColumns[0])) && (pDialog->GetLayoutListTitleFont(&m_fntTitle[0]) || GetParentDisplay()->GetListTitleFont(&m_fntTitle[0])) && (pDialog->GetLayoutListItemsFont(&m_fntItems[0]) || GetParentDisplay()->GetListItemsFont(&m_fntItems[0])) && (pDialog->GetLayoutGridBackgroundColor(m_nGridBackgroundColor[0]) || GetParentDisplay()->GetGridBackgroundColor(m_nGridBackgroundColor[0]))) || (GetParentDisplay()->GetLayout(szLayout, m_nColumns[0]) && GetParentDisplay()->GetListTitleFont(&m_fntTitle[0]) && GetParentDisplay()->GetListItemsFont(&m_fntItems[0]) && GetParentDisplay()->GetGridBackgroundColor(m_nGridBackgroundColor[0])))
	{
		m_bToolTips[0] = m_bToolTips[1] = (!pDialog || !pDialog->GetLayoutToolTipMode(m_bToolTips[0])) ? GetParentDisplay()->IsToolTipModeEnabled() : m_bToolTips[0];
		CopyMemory(&m_fntTitle[1], &m_fntTitle[0], sizeof(LOGFONT));
		CopyMemory(&m_fntItems[1], &m_fntItems[0], sizeof(LOGFONT));
		m_nGridBackgroundColor[1] = m_nGridBackgroundColor[0];
		m_nColumns[1].Copy(m_nColumns[0]);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistorySettingsLayoutPage::GetColumns(CUIntArray &nColumns) CONST
{
	nColumns.Copy(m_nColumns[0]);
	return((nColumns.GetSize() > 0) ? Check(FALSE) : FALSE);
}

BOOL CTCHistorySettingsLayoutPage::GetTitleFont(LPLOGFONT pTitleFont) CONST
{
	CopyMemory(pTitleFont, &m_fntTitle[0], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL CTCHistorySettingsLayoutPage::GetItemsFont(LPLOGFONT pItemsFont) CONST
{
	CopyMemory(pItemsFont, &m_fntItems[0], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL CTCHistorySettingsLayoutPage::GetGridBackgroundColor(COLORREF &nColor) CONST
{
	nColor = m_nGridBackgroundColor[0];
	return Check(FALSE);
}

BOOL CTCHistorySettingsLayoutPage::GetToolTipMode(BOOL &bEnable) CONST
{
	bEnable = m_bToolTips[0];
	return Check(FALSE);
}

CTCHistorySettingsDialog *CTCHistorySettingsLayoutPage::GetParentDialog() CONST
{
	return((CTCHistorySettingsDialog *)CLocalePropertyPage::GetParent());
}

CTCHistoryWnd *CTCHistorySettingsLayoutPage::GetParentDisplay() CONST
{
	return((CTCHistoryWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL CTCHistorySettingsLayoutPage::EnumLayoutColumns()
{
	INT  nColumn;
	INT  nColumns;
	CStringArray  szColumns;

	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_NUMBER));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_NAME));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_COMPUTER));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_COMMANDSOURCE));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_DESCRIPTION));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_CATEGORY));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_SUBSYSTEM));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_ARGUMENTS));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_FLAGS));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_TCPACKET));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_DISPATCHTIME));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_RELEASETIME));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_RELEASETIMEOFFSET));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_TRANSMISSIONTIME));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_EXECUTIONTIME));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_EXECUTIONTIMEOFFSET));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_AUTHORIZATION));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_PTVTIMEWINDOW));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_PTVCHECKS));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_PTVRESULT));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_PEVCHECKS));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_PEVRESULT));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_CEVTIMEWINDOW));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_CEVCHECKS));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_CEVRESULT));
	szColumns.Add(LookupColumnName(TCHISTORY_TITLEITEM_STATUS));
	for (nColumn = 0, nColumns = (INT)szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szColumns.GetAt(nColumn));
		continue;
	}
	SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_NAME, CB_SETCURSEL);
	return((nColumn == nColumns) ? TRUE : FALSE);
}

BOOL CTCHistorySettingsLayoutPage::ShowLayoutColumns()
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_nColumns[0].GetSize(), SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_VIEW, LVM_DELETEALLITEMS), m_nColumnIndex = 0; nColumn < nColumns; nColumn++)
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
		if ((!nColumn  &&  !Listview_InsertText(GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_VIEW), 0, EMPTYSTRING)) || (nColumn > 0 && !Listview_SetText(GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_VIEW), 0, nColumn, EMPTYSTRING))) break;
		continue;
	}
	return((nColumn == nColumns) ? SetCurLayoutColumn() : FALSE);
}

VOID CTCHistorySettingsLayoutPage::ShowLayoutFontDetails()
{
	INT  nSize;
	INT  nSizes;
	INT  nStyle;
	INT  nStyles;
	BOOL  bUnderlined;
	CStringArray  szSizes;
	CStringArray  szStyles;
	CFontTools  cFontTools;

	for (SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_RESETCONTENT), SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_RESETCONTENT), SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)) ? m_fntTitle[0].lfFaceName : m_fntItems[0].lfFaceName))); (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE) && cFontTools.EnumerateFont(m_fntTitle[0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS) && cFontTools.EnumerateFont(m_fntItems[0].lfFaceName, szStyles, szSizes, bUnderlined)); )
	{
		for (nStyle = 0, nStyles = (INT)szStyles.GetSize(); nStyle < nStyles; nStyle++) SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szStyles.GetAt(nStyle));
		for (nSize = 0, nSizes = (INT)szSizes.GetSize(); nSize < nSizes; nSize++) SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szSizes.GetAt(nSize));
		break;
	}
	if (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntTitle[0])), 0));
		SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntTitle[0])), max(SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntTitle[1])), 0)));
	}
	if (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntItems[0])), 0));
		SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntItems[0])), max(SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntItems[1])), 0)));
	}
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_STYLE)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SAMPLE)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CTCHistorySettingsLayoutPage::ShowLayoutFontSample()
{
	CRect  rSampleText;

	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText);
	ScreenToClient(rSampleText);
	InvalidateRect(rSampleText);
	UpdateWindow();
}

BOOL CTCHistorySettingsLayoutPage::InsertLayoutColumn(INT nIndex, LPCTSTR pszColumn)
{
	m_szColumns.InsertAt(nIndex, pszColumn);
	m_nColumnIndex = (nIndex <= m_nColumnIndex) ? (INT)min(m_nColumnIndex + 1, m_szColumns.GetSize() - 1) : m_nColumnIndex;
	return Listview_InsertColumn(GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex, m_szColumns.GetAt(nIndex), CalcColumnWidth(pszColumn));
}

BOOL CTCHistorySettingsLayoutPage::ModifyLayoutColumn(INT nIndex, LPCTSTR pszColumn)
{
	m_szColumns.SetAt(nIndex, pszColumn);
	return Listview_SetColumn(GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex, m_szColumns.GetAt(nIndex), CalcColumnWidth(pszColumn));
}

BOOL CTCHistorySettingsLayoutPage::RemoveLayoutColumn(INT nIndex)
{
	if (Listview_DeleteColumn(GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex))
	{
		m_nColumnIndex = (nIndex >= m_nColumnIndex) ? ((nIndex > m_nColumnIndex) ? m_nColumnIndex : 0) : max(m_nColumnIndex - 1, 0);
		m_szColumns.RemoveAt(nIndex);
		return SetCurLayoutColumn(m_nColumnIndex);
	}
	return FALSE;
}

BOOL CTCHistorySettingsLayoutPage::SetCurLayoutColumn(INT nIndex)
{
	if (nIndex < m_nColumns[0].GetSize())
	{
		for (m_szColumns.SetAt(m_nColumnIndex, (m_szColumns.GetAt(m_nColumnIndex).Right(lstrlen(STRING(IDS_TCHISTORYSETTINGS_LAYOUTPAGE_COLUMNMARKER))) == STRING(IDS_TCHISTORYSETTINGS_LAYOUTPAGE_COLUMNMARKER)) ? (m_szColumns.GetAt(m_nColumnIndex).Left(m_szColumns.GetAt(m_nColumnIndex).GetLength() - lstrlen(STRING(IDS_TCHISTORYSETTINGS_LAYOUTPAGE_COLUMNMARKER)))) : m_szColumns.GetAt(m_nColumnIndex)), m_szColumns.SetAt(nIndex, m_szColumns.GetAt(nIndex) + STRING(IDS_TCHISTORYSETTINGS_LAYOUTPAGE_COLUMNMARKER)); TRUE; )
		{
			Listview_SetColumn(GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_VIEW), m_nColumnIndex, m_szColumns.GetAt(m_nColumnIndex), CalcColumnWidth(m_szColumns.GetAt(m_nColumnIndex)));
			Listview_SetColumn(GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex, m_szColumns.GetAt(nIndex), CalcColumnWidth(m_szColumns.GetAt((m_nColumnIndex = nIndex))));
			break;
		}
		GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE)->EnableWindow((m_nColumnIndex > 0) ? (CheckLayoutColumn() && CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE)) : FALSE);
		GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER)->EnableWindow((m_nColumnIndex >= 0) ? (CheckLayoutColumn() && CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE)) : FALSE);
		GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_REMOVE)->EnableWindow((m_nColumnIndex > 0) ? CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE) : FALSE);
		return TRUE;
	}
	return FALSE;
}

INT CTCHistorySettingsLayoutPage::GetCurLayoutColumn() CONST
{
	return m_nColumnIndex;
}

BOOL CTCHistorySettingsLayoutPage::CheckLayoutColumn() CONST
{
	INT  nColumn;
	INT  nColumns;
	CString  szColumn;

	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_NAME)->GetWindowText(szColumn);
	for (nColumn = 0, nColumns = (INT)m_nColumns[0].GetSize(); nColumn < nColumns; nColumn++)
	{
		if (LookupColumnName(m_nColumns[0].GetAt(nColumn)) == szColumn) break;
		continue;
	}
	return((nColumn == nColumns) ? TRUE : FALSE);
}

CString CTCHistorySettingsLayoutPage::LookupColumnName(UINT nColumn) CONST
{
	if (nColumn == TCHISTORY_TITLEITEM_NUMBER) return STRING(IDS_TCHISTORY_TITLEITEM_NUMBER);
	if (nColumn == TCHISTORY_TITLEITEM_NAME) return STRING(IDS_TCHISTORY_TITLEITEM_NAME);
	if (nColumn == TCHISTORY_TITLEITEM_COMPUTER) return STRING(IDS_TCHISTORY_TITLEITEM_COMPUTER);
	if (nColumn == TCHISTORY_TITLEITEM_COMMANDSOURCE) return STRING(IDS_TCHISTORY_TITLEITEM_COMMANDSOURCE);
	if (nColumn == TCHISTORY_TITLEITEM_DESCRIPTION) return STRING(IDS_TCHISTORY_TITLEITEM_DESCRIPTION);
	if (nColumn == TCHISTORY_TITLEITEM_CATEGORY) return STRING(IDS_TCHISTORY_TITLEITEM_CATEGORY);
	if (nColumn == TCHISTORY_TITLEITEM_SUBSYSTEM) return STRING(IDS_TCHISTORY_TITLEITEM_SUBSYSTEM);
	if (nColumn == TCHISTORY_TITLEITEM_ARGUMENTS) return STRING(IDS_TCHISTORY_TITLEITEM_ARGUMENTS);
	if (nColumn == TCHISTORY_TITLEITEM_FLAGS) return STRING(IDS_TCHISTORY_TITLEITEM_FLAGS);
	if (nColumn == TCHISTORY_TITLEITEM_TCPACKET) return STRING(IDS_TCHISTORY_TITLEITEM_TCPACKET);
	if (nColumn == TCHISTORY_TITLEITEM_DISPATCHTIME) return STRING(IDS_TCHISTORY_TITLEITEM_DISPATCHTIME);
	if (nColumn == TCHISTORY_TITLEITEM_RELEASETIME) return STRING(IDS_TCHISTORY_TITLEITEM_RELEASETIME);
	if (nColumn == TCHISTORY_TITLEITEM_RELEASETIMEOFFSET) return STRING(IDS_TCHISTORY_TITLEITEM_RELEASETIMEOFFSET);
	if (nColumn == TCHISTORY_TITLEITEM_TRANSMISSIONTIME) return STRING(IDS_TCHISTORY_TITLEITEM_TRANSMISSIONTIME);
	if (nColumn == TCHISTORY_TITLEITEM_EXECUTIONTIME) return STRING(IDS_TCHISTORY_TITLEITEM_EXECUTIONTIME);
	if (nColumn == TCHISTORY_TITLEITEM_EXECUTIONTIMEOFFSET) return STRING(IDS_TCHISTORY_TITLEITEM_EXECUTIONTIMEOFFSET);
	if (nColumn == TCHISTORY_TITLEITEM_AUTHORIZATION) return STRING(IDS_TCHISTORY_TITLEITEM_AUTHORIZATION);
	if (nColumn == TCHISTORY_TITLEITEM_PTVTIMEWINDOW) return STRING(IDS_TCHISTORY_TITLEITEM_PTVTIMEWINDOW);
	if (nColumn == TCHISTORY_TITLEITEM_PTVCHECKS) return STRING(IDS_TCHISTORY_TITLEITEM_PTVCHECKS);
	if (nColumn == TCHISTORY_TITLEITEM_PTVRESULT) return STRING(IDS_TCHISTORY_TITLEITEM_PTVRESULT);
	if (nColumn == TCHISTORY_TITLEITEM_PEVCHECKS) return STRING(IDS_TCHISTORY_TITLEITEM_PEVCHECKS);
	if (nColumn == TCHISTORY_TITLEITEM_PEVRESULT) return STRING(IDS_TCHISTORY_TITLEITEM_PEVRESULT);
	if (nColumn == TCHISTORY_TITLEITEM_CEVTIMEWINDOW) return STRING(IDS_TCHISTORY_TITLEITEM_CEVTIMEWINDOW);
	if (nColumn == TCHISTORY_TITLEITEM_CEVCHECKS) return STRING(IDS_TCHISTORY_TITLEITEM_CEVCHECKS);
	if (nColumn == TCHISTORY_TITLEITEM_CEVRESULT) return STRING(IDS_TCHISTORY_TITLEITEM_CEVRESULT);
	if (nColumn == TCHISTORY_TITLEITEM_STATUS) return STRING(IDS_TCHISTORY_TITLEITEM_STATUS);
	return EMPTYSTRING;
}
UINT CTCHistorySettingsLayoutPage::LookupColumnName(LPCTSTR pszColumn) CONST
{
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_NUMBER), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_NUMBER)))) return TCHISTORY_TITLEITEM_NUMBER;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_NAME), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_NAME)))) return TCHISTORY_TITLEITEM_NAME;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_COMPUTER), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_COMPUTER)))) return TCHISTORY_TITLEITEM_COMPUTER;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_COMMANDSOURCE), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_COMMANDSOURCE)))) return TCHISTORY_TITLEITEM_COMMANDSOURCE;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_DESCRIPTION), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_DESCRIPTION)))) return TCHISTORY_TITLEITEM_DESCRIPTION;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_CATEGORY), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_CATEGORY)))) return TCHISTORY_TITLEITEM_CATEGORY;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_SUBSYSTEM), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_SUBSYSTEM)))) return TCHISTORY_TITLEITEM_SUBSYSTEM;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_ARGUMENTS), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_ARGUMENTS)))) return TCHISTORY_TITLEITEM_ARGUMENTS;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_FLAGS), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_FLAGS)))) return TCHISTORY_TITLEITEM_FLAGS;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_TCPACKET), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_TCPACKET)))) return TCHISTORY_TITLEITEM_TCPACKET;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_DISPATCHTIME), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_DISPATCHTIME)))) return TCHISTORY_TITLEITEM_DISPATCHTIME;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_RELEASETIME), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_RELEASETIME)))) return TCHISTORY_TITLEITEM_RELEASETIME;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_RELEASETIMEOFFSET), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_RELEASETIMEOFFSET)))) return TCHISTORY_TITLEITEM_RELEASETIMEOFFSET;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_TRANSMISSIONTIME), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_TRANSMISSIONTIME)))) return TCHISTORY_TITLEITEM_TRANSMISSIONTIME;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_EXECUTIONTIME), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_EXECUTIONTIME)))) return TCHISTORY_TITLEITEM_EXECUTIONTIME;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_EXECUTIONTIMEOFFSET), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_EXECUTIONTIMEOFFSET)))) return TCHISTORY_TITLEITEM_EXECUTIONTIMEOFFSET;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_AUTHORIZATION), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_AUTHORIZATION)))) return TCHISTORY_TITLEITEM_AUTHORIZATION;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_PTVTIMEWINDOW), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_PTVTIMEWINDOW)))) return TCHISTORY_TITLEITEM_PTVTIMEWINDOW;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_PTVCHECKS), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_PTVCHECKS)))) return TCHISTORY_TITLEITEM_PTVCHECKS;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_PTVRESULT), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_PTVRESULT)))) return TCHISTORY_TITLEITEM_PTVRESULT;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_PEVCHECKS), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_PEVCHECKS)))) return TCHISTORY_TITLEITEM_PEVCHECKS;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_PEVRESULT), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_PEVRESULT)))) return TCHISTORY_TITLEITEM_PEVRESULT;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_CEVTIMEWINDOW), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_CEVTIMEWINDOW)))) return TCHISTORY_TITLEITEM_CEVTIMEWINDOW;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_CEVCHECKS), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_CEVCHECKS)))) return TCHISTORY_TITLEITEM_CEVCHECKS;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_CEVRESULT), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_CEVRESULT)))) return TCHISTORY_TITLEITEM_CEVRESULT;
	if (!_tcsncmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_STATUS), lstrlen(STRING(IDS_TCHISTORY_TITLEITEM_STATUS)))) return TCHISTORY_TITLEITEM_STATUS;
	return 0;
}

INT CTCHistorySettingsLayoutPage::CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths)
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

INT CTCHistorySettingsLayoutPage::CalcColumnWidth(LPCTSTR pszColumn)
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
				nWidth = ((nColumn = LookupColumnName(pszColumn)) == TCHISTORY_TITLEITEM_NUMBER) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryNumberColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : 0;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_NAME) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryNameColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_COMPUTER) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryComputerColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_COMMANDSOURCE) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryCommandSourceColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_DESCRIPTION) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryDescriptionColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_CATEGORY) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryCategoryColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_SUBSYSTEM) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistorySubSystemColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_ARGUMENTS) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryArgumentsColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_FLAGS) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryFlagsColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_TCPACKET) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryTCPacketColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_DISPATCHTIME) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryDispatchTimeColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_RELEASETIME) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryReleaseTimeColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_RELEASETIMEOFFSET) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryReleaseTimeOffsetColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_TRANSMISSIONTIME) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryTransmissionTimeColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_EXECUTIONTIME) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryExecutionTimeColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_EXECUTIONTIMEOFFSET) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryExecutionTimeOffsetColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_AUTHORIZATION) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryAuthorizationColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_PTVTIMEWINDOW) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryPTVTimeWindowColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_PTVCHECKS) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryPTVChecksColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_PTVRESULT) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryPTVResultColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_PEVCHECKS) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryPEVChecksColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_PEVRESULT) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryPEVResultColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_CEVTIMEWINDOW) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryCEVTimeWindowColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_CEVCHECKS) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryCEVChecksColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_CEVRESULT) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryCEVResultColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_STATUS) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTCHistoryStatusColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
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

INT CTCHistorySettingsLayoutPage::CalcColumnIndent() CONST
{
	return 3 * GetSystemMetrics(SM_CXEDGE);
}

VOID CTCHistorySettingsLayoutPage::AdjustToPrivileges()
{
	BOOL  bCheck;

	AccessControl(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_NAME, (bCheck = CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE)));
	AccessControl(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_GRID, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_GRIDCOLOR, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_NAMES, bCheck, TRUE, FALSE);
	AccessControl(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_STYLE, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE, bCheck);
}

BOOL CTCHistorySettingsLayoutPage::IsModified(BOOL bAll) CONST
{
	INT  nColumn;
	INT  nColumns;
	CFontTools  cFontTools;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		for (nColumn = 0, nColumns = (m_nColumns[0].GetSize() == m_nColumns[1].GetSize() && !lstrcmp(m_fntTitle[0].lfFaceName, m_fntTitle[1].lfFaceName) && (m_fntTitle[0].lfHeight == m_fntTitle[1].lfHeight || cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[0])) == cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[1]))) && m_fntTitle[0].lfWeight == m_fntTitle[1].lfWeight && m_fntTitle[0].lfItalic == m_fntTitle[1].lfItalic && !lstrcmp(m_fntItems[0].lfFaceName, m_fntItems[1].lfFaceName) && (m_fntItems[0].lfHeight == m_fntItems[1].lfHeight || cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntItems[0])) == cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntItems[1]))) && m_fntItems[0].lfWeight == m_fntItems[1].lfWeight && m_fntItems[0].lfItalic == m_fntItems[1].lfItalic && m_nGridBackgroundColor[0] == m_nGridBackgroundColor[1] && m_bToolTips[0] == m_bToolTips[1]) ? (INT)m_nColumns[0].GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			if (m_nColumns[0].GetAt(nColumn) != m_nColumns[1].GetAt(nColumn)) break;
			continue;
		}
		return((nColumn != nColumns) ? TRUE : FALSE);
	}
	return((bAll) ? CLocalePropertyPage::IsModified() : FALSE);
}

BOOL CTCHistorySettingsLayoutPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (m_nColumns[0].GetSize() > 0 && m_nColumns[0].GetAt(0) == TCHISTORY_TITLEITEM_NUMBER  &&  GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_NAMES)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowTextLength() > 0 && (!IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_GRID) || GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_GRIDCOLOR)->SendMessage(CB_GETCURSEL) >= 0)) : CLocalePropertyPage::Check()) : TRUE);
}

void CTCHistorySettingsLayoutPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySettingsLayoutPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCHistorySettingsLayoutPage::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_nColumns[0].RemoveAll();
	m_nColumns[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCHistorySettingsLayoutPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CTCHistorySettingsLayoutPage)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE, OnInsertColumnBefore)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER, OnInsertColumnAfter)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_REMOVE, OnRemoveColumn)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_GRID, OnGridBackground)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS, OnToolTips)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, OnTitleFont)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS, OnItemsFont)
	ON_CBN_EDITCHANGE(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_NAMES, OnEditchangeFontName)
	ON_CBN_SELCHANGE(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_NAME, OnSelchangeColumnName)
	ON_CBN_SELCHANGE(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_NAMES, OnSelchangeFontName)
	ON_CBN_SELCHANGE(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_STYLE, OnSelchangeFontStyle)
	ON_CBN_SELCHANGE(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE, OnSelchangeFontSize)
	ON_CBN_SELCHANGE(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_GRIDCOLOR, OnSelchangeGridBackgroundColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySettingsLayoutPage message handlers

BOOL CTCHistorySettingsLayoutPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	CheckRadioButton(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS, IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_GRID, (m_nGridBackgroundColor[0] != GetSysColor(COLOR_WINDOW)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS, m_bToolTips[0]);
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowText(m_szFontSampleText);
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_NAME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_VIEW)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_GRID)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_GRIDCOLOR)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_GRID));
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_CHARACTERISTICS)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_NAMES)->EnableWindow();
	SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_NAMES, FCB_DIR, CF_EFFECTS | CF_SCREENFONTS);
	SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_fntTitle[0].lfFaceName));
	SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_GRIDCOLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nGridBackgroundColor[0]);
	EnumLayoutColumns();
	ShowLayoutColumns();
	ShowLayoutFontDetails();
	AdjustToPrivileges();
	return TRUE;
}

void CTCHistorySettingsLayoutPage::OnPaint()
{
	INT  nBkMode;
	CFont  cFont;
	CFont  *pOldFont;
	CRect  rSampleText;
	COLORREF  nOldColor;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText), ScreenToClient(rSampleText); cFont.CreateFontIndirect((IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)) ? &m_fntTitle[0] : &m_fntItems[0]); )
	{
		if ((pOldFont = cDC.SelectObject(&cFont)))
		{
			nBkMode = cDC.SetBkMode(TRANSPARENT);
			nOldColor = cDC.SetTextColor((SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? GetSysColor(COLOR_WINDOWTEXT) : GetSysColor(COLOR_GRAYTEXT));
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

BOOL CTCHistorySettingsLayoutPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMLISTVIEW  *pNotifyInfo = (NMLISTVIEW *)lParam;

	if (pNotifyInfo->hdr.idFrom == IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_VIEW)
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

void CTCHistorySettingsLayoutPage::OnInsertColumnBefore()
{
	INT  nIndex;
	CString  szColumn;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_NAME)->GetWindowText(szColumn); InsertLayoutColumn((nIndex = m_nColumnIndex), szColumn); )
	{
		m_nColumns[0].InsertAt(nIndex, LookupColumnName(szColumn));
		SetCurLayoutColumn(nIndex);
		break;
	}
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsLayoutPage::OnInsertColumnAfter()
{
	INT  nIndex;
	CString  szColumn;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_NAME)->GetWindowText(szColumn); InsertLayoutColumn((nIndex = m_nColumnIndex + 1), szColumn); )
	{
		m_nColumns[0].InsertAt(nIndex, LookupColumnName(szColumn));
		SetCurLayoutColumn(nIndex);
		break;
	}
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsLayoutPage::OnRemoveColumn()
{
	INT  nIndex;
	CHourglassCursor  cCursor;

	if (RemoveLayoutColumn((nIndex = m_nColumnIndex)))
	{
		m_nColumns[0].RemoveAt(nIndex);
		SetCurLayoutColumn();
	}
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsLayoutPage::OnGridBackground()
{
	COLORREF  nColor;

	SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_GRIDCOLOR, CCB_SELECTCOLOR, (WPARAM)-1, (nColor = VGA_COLOR_GRAY));
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_GRIDCOLOR)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_GRID));
	m_nGridBackgroundColor[0] = (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_GRID)) ? nColor : GetSysColor(COLOR_WINDOW);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsLayoutPage::OnToolTips()
{
	m_bToolTips[0] = IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsLayoutPage::OnTitleFont()
{
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CTCHistorySettingsLayoutPage::OnItemsFont()
{
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CTCHistorySettingsLayoutPage::OnEditchangeFontName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsLayoutPage::OnSelchangeColumnName()
{
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE)->EnableWindow((m_nColumnIndex > 0) ? (CheckLayoutColumn() && CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE)) : FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER)->EnableWindow((m_nColumnIndex >= 0) ? (CheckLayoutColumn() && CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE)) : FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_REMOVE)->EnableWindow((m_nColumnIndex > 0) ? CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE) : FALSE);
}

void CTCHistorySettingsLayoutPage::OnSelchangeFontName()
{
	CString  szSize;
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		_tcscpy_s(m_fntTitle[0].lfFaceName, sizeof(m_fntTitle[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		_tcscpy_s(m_fntItems[0].lfFaceName, sizeof(m_fntItems[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntTitle[0].lfWeight, m_fntTitle[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntTitle[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntTitle[0]);
	}
	if (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntItems[0].lfWeight, m_fntItems[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntItems[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntItems[0]);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsLayoutPage::OnSelchangeFontStyle()
{
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntTitle[0].lfWeight, m_fntTitle[0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntItems[0].lfWeight, m_fntItems[0].lfItalic);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsLayoutPage::OnSelchangeFontSize()
{
	CString  szSize;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntTitle[0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		GetDlgItem(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntItems[0].lfHeight);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsLayoutPage::OnSelchangeGridBackgroundColor()
{
	m_nGridBackgroundColor[0] = (COLORREF)SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_GRIDCOLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_GRIDCOLOR, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySettingsFilteringPage property page

IMPLEMENT_DYNCREATE(CTCHistorySettingsFilteringPage, CLocalePropertyPage)

CTCHistorySettingsFilteringPage::CTCHistorySettingsFilteringPage() : CLocalePropertyPage(CTCHistorySettingsFilteringPage::IDD)
{
	//{{AFX_DATA_INIT(CTCHistorySettingsFilteringPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySettingsFilteringPage::Initialize()
{
	CTCHistoryOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && (pDialog->GetFilterMode(m_nMode[0][0]) || GetParentDisplay()->GetFilterMode(m_nMode[0][0])) && (pDialog->GetFilterComputer(m_szComputer[0]) || GetParentDisplay()->GetFilterComputer(m_szComputer[0])) && (pDialog->GetFilterTelecommandName(m_szTelecommand[0][0]) || GetParentDisplay()->GetFilterTelecommandName(m_szTelecommand[0][0])) && (pDialog->GetFilterTelecommandSequence(m_szTelecommand[1][0]) || GetParentDisplay()->GetFilterTelecommandSequence(m_szTelecommand[1][0])) && (pDialog->GetFilterLimitation(m_nLimitation[0]) || GetParentDisplay()->GetFilterLimitation(m_nLimitation[0])) && (pDialog->GetFilterAutoload(m_nAutoload[0]) || GetParentDisplay()->GetFilterAutoload(m_nAutoload[0])) && (pDialog->GetFilterSortMode(m_nMode[1][0]) || GetParentDisplay()->GetFilterSortMode(m_nMode[1][0]))) || (GetParentDisplay()->GetFilterMode(m_nMode[0][0]) && GetParentDisplay()->GetFilterComputer(m_szComputer[0]) && GetParentDisplay()->GetFilterTelecommandName(m_szTelecommand[0][0]) && GetParentDisplay()->GetFilterTelecommandSequence(m_szTelecommand[1][0]) && GetParentDisplay()->GetFilterLimitation(m_nLimitation[0]) && GetParentDisplay()->GetFilterAutoload(m_nAutoload[0]) && GetParentDisplay()->GetFilterSortMode(m_nMode[1][0])))
	{
		m_szTelecommand[0][1] = m_szTelecommand[0][0];
		m_szTelecommand[1][1] = m_szTelecommand[1][0];
		m_bAlerts[0] = m_bAlerts[1] = FALSE;
		m_nLimitation[1] = m_nLimitation[0];
		m_szComputer[1] = m_szComputer[0];
		m_nAutoload[1] = m_nAutoload[0];
		m_nMode[0][1] = m_nMode[0][0];
		m_nMode[1][1] = m_nMode[1][0];
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistorySettingsFilteringPage::GetMode(UINT &nMode) CONST
{
	nMode = m_nMode[0][0];
	return Check(FALSE);
}

BOOL CTCHistorySettingsFilteringPage::GetComputer(CString &szComputer) CONST
{
	szComputer = m_szComputer[0];
	return Check(FALSE);
}

BOOL CTCHistorySettingsFilteringPage::GetTelecommandName(CString &szName) CONST
{
	szName = m_szTelecommand[0][0];
	return Check(FALSE);
}

BOOL CTCHistorySettingsFilteringPage::GetTelecommandSequence(CString &szSequence) CONST
{
	szSequence = m_szTelecommand[1][0];
	return Check(FALSE);
}

BOOL CTCHistorySettingsFilteringPage::GetLimitation(UINT &nCount) CONST
{
	nCount = m_nLimitation[0];
	return Check(FALSE);
}

BOOL CTCHistorySettingsFilteringPage::GetAutoload(UINT &nCount) CONST
{
	nCount = m_nAutoload[0];
	return Check(FALSE);
}

BOOL CTCHistorySettingsFilteringPage::GetSortMode(UINT &nMode) CONST
{
	nMode = m_nMode[1][0];
	return Check(FALSE);
}

CTCHistorySettingsDialog *CTCHistorySettingsFilteringPage::GetParentDialog() CONST
{
	return((CTCHistorySettingsDialog *)CLocalePropertyPage::GetParent());
}

CTCHistoryWnd *CTCHistorySettingsFilteringPage::GetParentDisplay() CONST
{
	return((CTCHistoryWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL CTCHistorySettingsFilteringPage::EnumComputers()
{
	INT  nComputer;
	INT  nComputers;
	CStringArray  szComputers;
	CComputerToken  cComputerToken;

	for (nComputer = 0, nComputers = GetNetworkBrowseService()->EnumNetworkComputers(szComputers); nComputer < nComputers; nComputer++)
	{
		SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szComputers.GetAt(nComputer));
		continue;
	}
	return((SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER_NAME, CB_GETCOUNT) >= 0) ? TRUE : FALSE);
}

BOOL CTCHistorySettingsFilteringPage::EnumVerificationStages()
{
	return((SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_TRANSMISSION)) >= 0 && SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_ACCEPTANCE)) >= 0 && SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_START)) >= 0 && SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_PROGRESS)) >= 0 && SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_COMPLETION)) >= 0) ? TRUE : FALSE);
}

BOOL CTCHistorySettingsFilteringPage::EnumVerificationStates()
{
	INT  nIndex;
	CString  szStage;

	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE)->GetWindowText(szStage);
	return(((SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_PASSED)) >= 0 || SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_PASSED)) >= 0) && (SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_FAILED)) >= 0 || SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_FAILED)) >= 0) && ((szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_TRANSMISSION) && ((nIndex = (INT)SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_UNKNOWN))) < 0 || SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME, CB_DELETESTRING, nIndex) >= 0)) || (szStage != STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_TRANSMISSION) && (SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_UNKNOWN)) >= 0 || SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_UNKNOWN)) >= 0))) && ((szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_TRANSMISSION) && ((nIndex = (INT)SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_UNVERIFIED))) < 0 || SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME, CB_DELETESTRING, nIndex) >= 0)) || (szStage != STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_TRANSMISSION) && (SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_UNVERIFIED)) >= 0 || SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_UNVERIFIED)) >= 0)))) ? TRUE : FALSE);
}

VOID CTCHistorySettingsFilteringPage::ShowFilterInfo()
{
	UINT  nState;

	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER, (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYCOMPUTER) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE, (m_nMode[0][0] & (TCHISTORY_FILTERMODE_BYMANUALSTACK | TCHISTORY_FILTERMODE_BYAUTOMATICSTACK | TCHISTORY_FILTERMODE_BYPROCEDURESMONITOR)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_MANUALSTACK, (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYMANUALSTACK) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_AUTOMATICSTACK, (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYAUTOMATICSTACK) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_PROCEDURESMONITOR, (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYPROCEDURESMONITOR) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND, (m_nMode[0][0] & (TCHISTORY_FILTERMODE_BYTELECOMMAND | TCHISTORY_FILTERMODE_BYTELECOMMANDITEM | TCHISTORY_FILTERMODE_BYTELECOMMANDSEQUENCE | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPEIMMEDIATE | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPETIMETAGGED | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE1STSTEP | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE2NDSTEP)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM, (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYTELECOMMANDITEM) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE, (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYTELECOMMANDSEQUENCE) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE, (m_nMode[0][0] & (TCHISTORY_FILTERMODE_BYTELECOMMANDTYPEIMMEDIATE | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPETIMETAGGED | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE1STSTEP | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE2NDSTEP)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_IMMEDIATE, (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYTELECOMMANDTYPEIMMEDIATE) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_TIMETAGGED, (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYTELECOMMANDTYPETIMETAGGED) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_1STSTEP, (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE1STSTEP) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_2NDSTEP, (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE2NDSTEP) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION, (m_nMode[0][0] & (TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNVERIFIED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNVERIFIED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNVERIFIED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNVERIFIED)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE, (m_nMode[0][0] & (TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNVERIFIED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNVERIFIED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNVERIFIED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNVERIFIED)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES, (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYLIMITENTRIES) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES, (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYAUTOLOADENTRIES) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_BYRELEASETIME, (m_nMode[1][0] & TCHISTORY_SORTMODE_BYRELEASETIME) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_BYEXECUTIONTIME, (m_nMode[1][0] & TCHISTORY_SORTMODE_BYEXECUTIONTIME) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_ORDER_LATESTFIRST, (m_nMode[1][0] & TCHISTORY_SORTMODE_BYLATESTFIRST) ? TRUE : FALSE);
	SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szComputer[0]));
	SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(((nState = (m_nMode[0][0] & (TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONFAILED)))) ? STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_TRANSMISSION) : (((nState = (m_nMode[0][0] & (TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNVERIFIED)))) ? STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_ACCEPTANCE) : (((nState = (m_nMode[0][0] & (TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNVERIFIED)))) ? STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_START) : (((nState = (m_nMode[0][0] & (TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNVERIFIED)))) ? STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_PROGRESS) : (((nState = (m_nMode[0][0] & (TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNVERIFIED)))) ? STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_COMPLETION) : EMPTYSTRING)))))));
	SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((nState & (TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONPASSED)) ? STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_PASSED) : ((nState & (TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONFAILED)) ? STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_FAILED) : ((nState & (TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNKNOWN)) ? STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_UNKNOWN) : ((nState & (TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNVERIFIED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNVERIFIED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNVERIFIED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNVERIFIED)) ? STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_UNVERIFIED) : EMPTYSTRING))))));
	Spinbox_SetPos(GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES_COUNT), m_nLimitation[0]);
	Spinbox_SetPos(GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES_COUNT), m_nAutoload[0]);
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER_NAME)->SetWindowText(m_szComputer[0]);
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM_NAME)->SetWindowText(m_szTelecommand[0][0]);
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE_NAME)->SetWindowText(m_szTelecommand[1][0]);
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER_NAME)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_MANUALSTACK)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_AUTOMATICSTACK)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_PROCEDURESMONITOR)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM_NAME)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE_NAME)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_IMMEDIATE)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_TIMETAGGED)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_1STSTEP)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_2NDSTEP)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES_COUNT)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES_COUNT)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES));
}

VOID CTCHistorySettingsFilteringPage::AdjustToPrivileges()
{
	BOOL  bCheck;

	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER, (bCheck = CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE)));
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER_NAME, bCheck, TRUE, FALSE);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_MANUALSTACK, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_AUTOMATICSTACK, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_PROCEDURESMONITOR, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM_NAME, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE_NAME, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_IMMEDIATE, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_TIMETAGGED, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_1STSTEP, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_2NDSTEP, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES_COUNT, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES_COUNT, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_BYRELEASETIME, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_BYEXECUTIONTIME, bCheck);
	AccessControl(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_ORDER_LATESTFIRST, bCheck);
}

BOOL CTCHistorySettingsFilteringPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (m_nMode[0][0] != m_nMode[0][1] || m_nMode[1][0] != m_nMode[1][1] || m_szComputer[0].CompareNoCase(m_szComputer[1]) || m_szTelecommand[0][0] != m_szTelecommand[0][1] || m_szTelecommand[1][0] != m_szTelecommand[1][1] || m_nLimitation[0] != m_nLimitation[1] || m_nAutoload[0] != m_nAutoload[1] || m_bAlerts[0] != m_bAlerts[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CTCHistorySettingsFilteringPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((!IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER) || GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER_NAME)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE) || IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_MANUALSTACK) || IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_AUTOMATICSTACK) || IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_PROCEDURESMONITOR)) && (!IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM) || GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM_NAME)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE) || GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE_NAME)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE) || IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_IMMEDIATE) || IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_TIMETAGGED) || IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_1STSTEP) || IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_2NDSTEP)) && (!IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION) || (GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE)->SendMessage(CB_GETCURSEL) >= 0 && (!IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE) || GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME)->SendMessage(CB_GETCURSEL) >= 0))) && (!IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES) || Spinbox_GetPos(GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES_COUNT)) > 0) && (!IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES) || Spinbox_GetPos(GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES_COUNT)) > 0) && (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_BYRELEASETIME) || IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_BYEXECUTIONTIME))) : CLocalePropertyPage::Check()) : TRUE);
}

void CTCHistorySettingsFilteringPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySettingsFilteringPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySettingsFilteringPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CTCHistorySettingsFilteringPage)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER, OnComputer)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE, OnCommandSource)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_MANUALSTACK, OnCommandSourceManualStack)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_AUTOMATICSTACK, OnCommandSourceAutomaticStack)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_PROCEDURESMONITOR, OnCommandSourceProceduresMonitor)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND, OnTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM, OnTelecommandName)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE, OnTelecommandSequence)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE, OnTelecommandType)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_IMMEDIATE, OnTelecommandTypeImmediate)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_TIMETAGGED, OnTelecommandTypeTimeTagged)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_1STSTEP, OnTelecommandType1stStep)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_2NDSTEP, OnTelecommandType2ndStep)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION, OnVerificationStatus)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE, OnVerificationState)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES, OnLimitEntries)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES, OnAutoloadEntries)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_ALERTS, OnAlerts)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_BYRELEASETIME, OnSortByReleaseTime)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_BYEXECUTIONTIME, OnSortByExecutionTime)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_ORDER_LATESTFIRST, OnSortOrderLatestFirst)
	ON_CBN_EDITCHANGE(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER_NAME, OnEditchangeComputer)
	ON_CBN_SELCHANGE(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER_NAME, OnSelchangeComputer)
	ON_CBN_SELCHANGE(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE, OnSelchangeVerificationStage)
	ON_CBN_SELCHANGE(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME, OnSelchangeVerificationState)
	ON_CONTROL(SBXN_CHANGE, IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES_COUNT, OnSpinchangeLimitationCount)
	ON_CONTROL(SBXN_CHANGE, IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES_COUNT, OnSpinchangeAutoloadCount)
	ON_EN_CHANGE(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM_NAME, OnEditchangeTelecommandTypeName)
	ON_EN_CHANGE(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE_NAME, OnEditchangeTelecommandTypeSequence)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySettingsFilteringPage message handlers

BOOL CTCHistorySettingsFilteringPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	Spinbox_SetRange(GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES_COUNT), TCHISTORYSETTINGSFILTERINGPAGE_MINIMUMENTRYLIMITATION, TCHISTORYSETTINGSFILTERINGPAGE_MAXIMUMENTRYLIMITATION);
	Spinbox_SetRange(GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES_COUNT), TCHISTORYSETTINGSFILTERINGPAGE_MINIMUMAUTOLOADENTRIES, TCHISTORYSETTINGSFILTERINGPAGE_MAXIMUMAUTOLOADENTRIES);
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES)->EnableWindow((GetParentDisplay()->GetScope() == DISPLAY_SCOPE_GLOBAL) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_ALERTS)->EnableWindow((GetParentDisplay()->GetScope() == DISPLAY_SCOPE_GLOBAL) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_BYRELEASETIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_BYEXECUTIONTIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_ORDER_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_ORDER_LATESTFIRST)->EnableWindow();
	EnumComputers();
	EnumVerificationStages();
	EnumVerificationStates();
	ShowFilterInfo();
	AdjustToPrivileges();
	return TRUE;
}

void CTCHistorySettingsFilteringPage::OnComputer()
{
	CComputerToken  cComputerToken;

	if (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER))
	{
		m_nMode[0][0] = m_nMode[0][0] | TCHISTORY_FILTERMODE_BYCOMPUTER;
		SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER_NAME, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cComputerToken.GetComputerName()), 0));
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER_NAME)->EnableWindow();
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER_NAME)->SetFocus();
	}
	else
	{
		m_nMode[0][0] = m_nMode[0][0] & ~TCHISTORY_FILTERMODE_BYCOMPUTER;
		SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER_NAME, CB_SETCURSEL, (WPARAM)-1);
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER_NAME)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER_NAME)->GetWindowText(m_szComputer[0]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnCommandSource()
{
	if (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE))
	{
		m_nMode[0][0] = (m_nMode[0][0] & ~(TCHISTORY_FILTERMODE_BYAUTOMATICSTACK | TCHISTORY_FILTERMODE_BYPROCEDURESMONITOR)) | TCHISTORY_FILTERMODE_BYMANUALSTACK;
		CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_MANUALSTACK, TRUE);
		CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_AUTOMATICSTACK, FALSE);
		CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_PROCEDURESMONITOR, FALSE);
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_MANUALSTACK)->EnableWindow();
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_AUTOMATICSTACK)->EnableWindow();
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_PROCEDURESMONITOR)->EnableWindow();
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_MANUALSTACK)->SetFocus();
	}
	else
	{
		m_nMode[0][0] = m_nMode[0][0] & ~(TCHISTORY_FILTERMODE_BYMANUALSTACK | TCHISTORY_FILTERMODE_BYAUTOMATICSTACK | TCHISTORY_FILTERMODE_BYPROCEDURESMONITOR);
		CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_MANUALSTACK, FALSE);
		CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_AUTOMATICSTACK, FALSE);
		CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_PROCEDURESMONITOR, FALSE);
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_MANUALSTACK)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_AUTOMATICSTACK)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_PROCEDURESMONITOR)->EnableWindow(FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnCommandSourceManualStack()
{
	m_nMode[0][0] = (m_nMode[0][0] & ~(TCHISTORY_FILTERMODE_BYAUTOMATICSTACK | TCHISTORY_FILTERMODE_BYPROCEDURESMONITOR)) | TCHISTORY_FILTERMODE_BYMANUALSTACK;
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_MANUALSTACK, TRUE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_AUTOMATICSTACK, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_PROCEDURESMONITOR, FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnCommandSourceAutomaticStack()
{
	m_nMode[0][0] = (m_nMode[0][0] & ~(TCHISTORY_FILTERMODE_BYMANUALSTACK | TCHISTORY_FILTERMODE_BYPROCEDURESMONITOR)) | TCHISTORY_FILTERMODE_BYAUTOMATICSTACK;
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_MANUALSTACK, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_AUTOMATICSTACK, TRUE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_PROCEDURESMONITOR, FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnCommandSourceProceduresMonitor()
{
	m_nMode[0][0] = (m_nMode[0][0] & ~(TCHISTORY_FILTERMODE_BYMANUALSTACK | TCHISTORY_FILTERMODE_BYAUTOMATICSTACK)) | TCHISTORY_FILTERMODE_BYPROCEDURESMONITOR;
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_MANUALSTACK, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_AUTOMATICSTACK, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_PROCEDURESMONITOR, TRUE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnTelecommand()
{
	m_nMode[0][0] &= ~(TCHISTORY_FILTERMODE_BYTELECOMMAND | TCHISTORY_FILTERMODE_BYTELECOMMANDITEM | TCHISTORY_FILTERMODE_BYTELECOMMANDSEQUENCE | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPEIMMEDIATE | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPETIMETAGGED | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE1STSTEP | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE2NDSTEP);
	m_nMode[0][0] |= (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND)) ? TCHISTORY_FILTERMODE_BYTELECOMMAND : 0;
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_IMMEDIATE, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_TIMETAGGED, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_1STSTEP, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_2NDSTEP, FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM_NAME)->SetWindowText((m_szTelecommand[0][0] = EMPTYSTRING));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE_NAME)->SetWindowText((m_szTelecommand[1][0] = EMPTYSTRING));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_IMMEDIATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_TIMETAGGED)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_1STSTEP)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_2NDSTEP)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnTelecommandName()
{
	for (m_nMode[0][0] = (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM)) ? (m_nMode[0][0] | TCHISTORY_FILTERMODE_BYTELECOMMANDITEM) : (m_nMode[0][0] & ~TCHISTORY_FILTERMODE_BYTELECOMMANDITEM); !IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM); )
	{
		m_szTelecommand[0][0].Empty();
		break;
	}
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM_NAME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM_NAME)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnTelecommandSequence()
{
	for (m_nMode[0][0] = (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE)) ? (m_nMode[0][0] | TCHISTORY_FILTERMODE_BYTELECOMMANDSEQUENCE) : (m_nMode[0][0] & ~TCHISTORY_FILTERMODE_BYTELECOMMANDSEQUENCE); !IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE); )
	{
		m_szTelecommand[1][0].Empty();
		break;
	}
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE_NAME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE_NAME)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnTelecommandType()
{
	m_nMode[0][0] = (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE)) ? ((m_nMode[0][0] & ~(TCHISTORY_FILTERMODE_BYTELECOMMANDTYPETIMETAGGED | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE1STSTEP | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE2NDSTEP)) | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPEIMMEDIATE) : (m_nMode[0][0] & ~(TCHISTORY_FILTERMODE_BYTELECOMMANDTYPEIMMEDIATE | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPETIMETAGGED | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE1STSTEP | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE2NDSTEP));
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_IMMEDIATE, IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE));
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_TIMETAGGED, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_1STSTEP, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_2NDSTEP, FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_IMMEDIATE)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_TIMETAGGED)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_1STSTEP)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_2NDSTEP)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnTelecommandTypeImmediate()
{
	m_nMode[0][0] = (m_nMode[0][0] & ~(TCHISTORY_FILTERMODE_BYTELECOMMANDTYPETIMETAGGED | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE1STSTEP | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE2NDSTEP)) | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPEIMMEDIATE;
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_IMMEDIATE, TRUE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_TIMETAGGED, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_1STSTEP, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_2NDSTEP, FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnTelecommandTypeTimeTagged()
{
	m_nMode[0][0] = (m_nMode[0][0] & ~(TCHISTORY_FILTERMODE_BYTELECOMMANDTYPEIMMEDIATE | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE1STSTEP | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE2NDSTEP)) | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPETIMETAGGED;
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_IMMEDIATE, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_TIMETAGGED, TRUE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_1STSTEP, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_2NDSTEP, FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnTelecommandType1stStep()
{
	m_nMode[0][0] = (m_nMode[0][0] & ~(TCHISTORY_FILTERMODE_BYTELECOMMANDTYPEIMMEDIATE | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPETIMETAGGED | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE2NDSTEP)) | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE1STSTEP;
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_IMMEDIATE, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_TIMETAGGED, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_1STSTEP, TRUE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_2NDSTEP, FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnTelecommandType2ndStep()
{
	m_nMode[0][0] = (m_nMode[0][0] & ~(TCHISTORY_FILTERMODE_BYTELECOMMANDTYPEIMMEDIATE | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPETIMETAGGED | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE1STSTEP)) | TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE2NDSTEP;
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_IMMEDIATE, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_TIMETAGGED, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_1STSTEP, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_2NDSTEP, TRUE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnVerificationStatus()
{
	for (m_nMode[0][0] &= ~(TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNVERIFIED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNVERIFIED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNVERIFIED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNVERIFIED); IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION); )
	{
		SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_ACCEPTANCE)));
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE)->EnableWindow();
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE)->EnableWindow();
		break;
	}
	if (!IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION))
	{
		CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE, FALSE);
		SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE, CB_SETCURSEL, (WPARAM)-1);
		SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME, CB_SETCURSEL, (WPARAM)-1);
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME)->EnableWindow(FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnVerificationState()
{
	CString  szStage;

	for (GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE)->GetWindowText(szStage); IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE); )
	{
		m_nMode[0][0] = (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_TRANSMISSION)) ? ((m_nMode[0][0] & ~TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONFAILED) | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONPASSED) : ((szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_ACCEPTANCE)) ? ((m_nMode[0][0] & ~(TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNVERIFIED)) | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEPASSED) : ((szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_START)) ? ((m_nMode[0][0] & ~(TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNVERIFIED)) | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTPASSED) : ((szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_PROGRESS)) ? ((m_nMode[0][0] & ~(TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNVERIFIED)) | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSPASSED) : ((m_nMode[0][0] & ~(TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNVERIFIED)) | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONPASSED))));
		SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_PASSED)));
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME)->EnableWindow();
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME)->SetFocus();
		break;
	}
	if (!IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE))
	{
		m_nMode[0][0] = (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_TRANSMISSION)) ? (m_nMode[0][0] & ~(TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONFAILED)) : ((szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_ACCEPTANCE)) ? (m_nMode[0][0] & ~(TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNVERIFIED)) : ((szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_START)) ? (m_nMode[0][0] & ~(TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNVERIFIED)) : ((szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_PROGRESS)) ? (m_nMode[0][0] & ~(TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNVERIFIED)) : (m_nMode[0][0] & ~(TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNVERIFIED)))));
		SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME, CB_SETCURSEL, (WPARAM)-1);
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME)->EnableWindow();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnLimitEntries()
{
	if (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES))
	{
		m_nMode[0][0] = m_nMode[0][0] | TCHISTORY_FILTERMODE_BYLIMITENTRIES;
		Spinbox_SetPos(GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES_COUNT), (m_nLimitation[0] = TCHISTORYSETTINGSFILTERINGPAGE_DEFAULTENTRYLIMITATION));
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES_COUNT)->EnableWindow();
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES_COUNT)->SetFocus();
	}
	else
	{
		m_nMode[0][0] &= ~TCHISTORY_FILTERMODE_BYLIMITENTRIES;
		Spinbox_SetPos(GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES_COUNT), (m_nLimitation[0] = 0));
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES_COUNT)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES_STATIC)->EnableWindow(FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnAutoloadEntries()
{
	if (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES))
	{
		m_nMode[0][0] = m_nMode[0][0] | TCHISTORY_FILTERMODE_BYAUTOLOADENTRIES;
		Spinbox_SetPos(GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES_COUNT), (m_nAutoload[0] = TCHISTORYSETTINGSFILTERINGPAGE_DEFAULTAUTOLOADENTRIES));
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES_COUNT)->EnableWindow();
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES_COUNT)->SetFocus();
	}
	else
	{
		m_nMode[0][0] &= ~TCHISTORY_FILTERMODE_BYAUTOLOADENTRIES;
		Spinbox_SetPos(GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES_COUNT), (m_nAutoload[0] = 0));
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES_COUNT)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES_STATIC)->EnableWindow(FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnAlerts()
{
	CTCHistoryAlertOptionsDialog  cAlertOptionsDialog;

	m_bAlerts[0] |= (cAlertOptionsDialog.Create(this) == IDOK) ? TRUE : FALSE;
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnSortByReleaseTime()
{
	m_nMode[1][0] = (m_nMode[1][0] & ~TCHISTORY_SORTMODE_BYEXECUTIONTIME) | TCHISTORY_SORTMODE_BYRELEASETIME;
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_BYRELEASETIME, TRUE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_BYEXECUTIONTIME, FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnSortByExecutionTime()
{
	m_nMode[1][0] = (m_nMode[1][0] & ~TCHISTORY_SORTMODE_BYRELEASETIME) | TCHISTORY_SORTMODE_BYEXECUTIONTIME;
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_BYRELEASETIME, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_BYEXECUTIONTIME, TRUE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnSortOrderLatestFirst()
{
	m_nMode[1][0] = (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_ORDER_LATESTFIRST)) ? (m_nMode[1][0] | TCHISTORY_SORTMODE_BYLATESTFIRST) : (m_nMode[1][0] & ~TCHISTORY_SORTMODE_BYLATESTFIRST);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnSelchangeComputer()
{
	m_szComputer[0] = Combobox_GetText(GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER_NAME), (INT)SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER_NAME, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnSelchangeVerificationStage()
{
	CString  szStage;

	EnumVerificationStates();
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE)->GetWindowText(szStage);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE, ((szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_TRANSMISSION) && (m_nMode[0][0] & (TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONFAILED))) || (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_ACCEPTANCE) && (m_nMode[0][0] & (TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNVERIFIED))) || (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_START) && (m_nMode[0][0] & (TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNVERIFIED))) || (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_PROGRESS) && (m_nMode[0][0] & (TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNVERIFIED))) || (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_COMPLETION) && (m_nMode[0][0] & (TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNVERIFIED)))) ? TRUE : FALSE);
	SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(((szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_TRANSMISSION) && (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONPASSED)) || (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_ACCEPTANCE) && (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEPASSED)) || (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_START) && (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTPASSED)) || (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_PROGRESS) && (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSPASSED)) || (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_COMPLETION) && (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONPASSED))) ? STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_PASSED) : (((szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_TRANSMISSION) && (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONFAILED)) || (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_ACCEPTANCE) && (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEFAILED)) || (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_START) && (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTFAILED)) || (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_PROGRESS) && (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSFAILED)) || (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_COMPLETION) && (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONFAILED))) ? STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_FAILED) : (((szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_ACCEPTANCE) && (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNKNOWN)) || (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_START) && (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNKNOWN)) || (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_PROGRESS) && (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNKNOWN)) || (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_COMPLETION) && (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNKNOWN))) ? STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_UNKNOWN) : (((szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_ACCEPTANCE) && (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNVERIFIED)) || (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_START) && (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNVERIFIED)) || (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_PROGRESS) && (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNVERIFIED)) || (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_COMPLETION) && (m_nMode[0][0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNVERIFIED))) ? STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_UNVERIFIED) : EMPTYSTRING))))));
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnSelchangeVerificationState()
{
	CString  szStage;
	CString  szState;

	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE)->GetWindowText(szStage);
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME)->GetWindowText(szState);
	m_nMode[0][0] &= (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_TRANSMISSION)) ? ~(TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONFAILED) : m_nMode[0][0];
	m_nMode[0][0] &= (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_ACCEPTANCE)) ? ~(TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNVERIFIED) : m_nMode[0][0];
	m_nMode[0][0] &= (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_START)) ? ~(TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNVERIFIED) : m_nMode[0][0];
	m_nMode[0][0] &= (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_PROGRESS)) ? ~(TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNVERIFIED) : m_nMode[0][0];
	m_nMode[0][0] &= (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_COMPLETION)) ? ~(TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONPASSED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONFAILED | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNKNOWN | TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNVERIFIED) : m_nMode[0][0];
	m_nMode[0][0] |= (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_TRANSMISSION)) ? ((szState == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_PASSED)) ? TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONPASSED : TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONFAILED) : 0;
	m_nMode[0][0] |= (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_ACCEPTANCE)) ? ((szState == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_PASSED)) ? TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEPASSED : ((szState == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_FAILED)) ? TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEFAILED : ((szState == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_UNKNOWN)) ? TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNKNOWN : TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNVERIFIED))) : 0;
	m_nMode[0][0] |= (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_START)) ? ((szState == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_PASSED)) ? TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTPASSED : ((szState == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_FAILED)) ? TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTFAILED : ((szState == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_UNKNOWN)) ? TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNKNOWN : TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNVERIFIED))) : 0;
	m_nMode[0][0] |= (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_PROGRESS)) ? ((szState == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_PASSED)) ? TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSPASSED : ((szState == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_FAILED)) ? TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSFAILED : ((szState == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_UNKNOWN)) ? TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNKNOWN : TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNVERIFIED))) : 0;
	m_nMode[0][0] |= (szStage == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTAGE_COMPLETION)) ? ((szState == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_PASSED)) ? TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONPASSED : ((szState == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_FAILED)) ? TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONFAILED : ((szState == STRING(IDS_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATIONSTATE_UNKNOWN)) ? TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNKNOWN : TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNVERIFIED))) : 0;
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnSpinchangeLimitationCount()
{
	m_nLimitation[0] = (UINT)Spinbox_GetPos(GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES_COUNT));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnSpinchangeAutoloadCount()
{
	m_nAutoload[0] = (UINT)Spinbox_GetPos(GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES_COUNT));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnEditchangeComputer()
{
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER_NAME)->GetWindowText(m_szComputer[0]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnEditchangeTelecommandTypeName()
{
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM_NAME)->GetWindowText(m_szTelecommand[0][0]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsFilteringPage::OnEditchangeTelecommandTypeSequence()
{
	GetDlgItem(IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE_NAME)->GetWindowText(m_szTelecommand[1][0]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySettingsRetrievingPage property page

IMPLEMENT_DYNCREATE(CTCHistorySettingsRetrievingPage, CLocalePropertyPage)

CTCHistorySettingsRetrievingPage::CTCHistorySettingsRetrievingPage() : CLocalePropertyPage(CTCHistorySettingsRetrievingPage::IDD)
{
	//{{AFX_DATA_INIT(CTCHistorySettingsRetrievingPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySettingsRetrievingPage::Initialize()
{
	CTCHistoryOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && (pDialog->GetRetrieveMode(m_nMode[0]) || GetParentDisplay()->GetRetrieveMode(m_nMode[0])) && (pDialog->GetRetrieveFileName(m_szFileName[0]) || GetParentDisplay()->GetRetrieveFileName(m_szFileName[0]))) || (GetParentDisplay()->GetRetrieveMode(m_nMode[0]) && GetParentDisplay()->GetRetrieveFileName(m_szFileName[0])))
	{
		m_nMode[1] = m_nMode[0] = ((m_nMode[0] & (TCHISTORY_RETRIEVE_BYRELEASETIME | TCHISTORY_RETRIEVE_BYEXECUTIONTIME)) == 0) ? (m_nMode[0] | TCHISTORY_RETRIEVE_BYRELEASETIME) : m_nMode[0];
		m_szFileName[1] = m_szFileName[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistorySettingsRetrievingPage::GetMode(UINT &nMode) CONST
{
	if (m_nMode[0] & (TCHISTORY_RETRIEVE_BYRELEASETIME | TCHISTORY_RETRIEVE_BYEXECUTIONTIME))
	{
		nMode = (nMode & ~(TCHISTORY_RETRIEVE_BYRELEASETIME | TCHISTORY_RETRIEVE_BYEXECUTIONTIME)) | (m_nMode[0] & (TCHISTORY_RETRIEVE_BYRELEASETIME | TCHISTORY_RETRIEVE_BYEXECUTIONTIME));
		return Check(FALSE);
	}
	return FALSE;
}

BOOL CTCHistorySettingsRetrievingPage::GetDataSourceFileName(CString &szFileName) CONST
{
	szFileName = m_szFileName[0];
	return Check(FALSE);
}

CTCHistorySettingsDialog *CTCHistorySettingsRetrievingPage::GetParentDialog() CONST
{
	return((CTCHistorySettingsDialog *)CLocalePropertyPage::GetParent());
}

CTCHistoryWnd *CTCHistorySettingsRetrievingPage::GetParentDisplay() CONST
{
	return((CTCHistoryWnd *)GetParentDialog()->GetParentDisplay());
}

VOID CTCHistorySettingsRetrievingPage::EnumDataSources()
{
	INT  nFile;
	INT  nFiles;
	CHistoryStoreFile  cFile;
	CHistoryStoreFiles  pFiles;
	CUIntArray  nOptions;

	for (nFile = 0, nFiles = GetTCService()->GetTCHistoryFiles(HISTORYFILE_TYPE_RETRIEVE, pFiles), GetTCService()->GetDefaultTCHistoryFile(HISTORYFILE_TYPE_RETRIEVE, cFile), m_szFileName[0] = (pFiles.Find(m_szFileName[0]) < 0) ? cFile.GetFileName() : m_szFileName[0]; nFile < nFiles || (!nFiles && !nFile && !m_szFileName[0].IsEmpty()); nFile++)
	{
		SendDlgItemMessage(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)((nFiles > 0) ? (LPCTSTR)pFiles.GetAt(nFile)->GetFileName() : (LPCTSTR)m_szFileName[0]));
		continue;
	}
	CheckDlgButton(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_KEY_RELEASETIME, ((m_nMode[0] & TCHISTORY_RETRIEVE_BYRELEASETIME) || (m_nMode[0] & (TCHISTORY_RETRIEVE_BYRELEASETIME | TCHISTORY_RETRIEVE_BYEXECUTIONTIME)) == 0) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_KEY_EXECUTIONTIME, (m_nMode[0] & TCHISTORY_RETRIEVE_BYEXECUTIONTIME) ? TRUE : FALSE);
	SendDlgItemMessage(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szFileName[0]), 0));
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_DATASOURCE)->GetWindowText(m_szFileName[0]);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_DATASOURCE)->GetWindowText(m_szFileName[1]);
	ShowDataSourceInfo();
}

VOID CTCHistorySettingsRetrievingPage::ShowDataSourceInfo()
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
		GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->SetWindowText(szProduct);
		GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->SetWindowText(szCompany);
		GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->SetWindowText(szSpacecraft);
		GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->SetWindowText(szDataSourceType);
		GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->SetWindowText(szStartTime);
		GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->SetWindowText(szStopTime);
		GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->SetWindowText(szCreationTime);
		GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->SetWindowText(szDataSourceSize);
	}
	else
	{
		GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->SetWindowText((szProduct = EMPTYSTRING));
		GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->SetWindowText((szCompany = EMPTYSTRING));
		GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->SetWindowText((szSpacecraft = EMPTYSTRING));
		GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->SetWindowText((szDataSourceType = EMPTYSTRING));
		GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->SetWindowText((szStartTime = EMPTYSTRING));
		GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->SetWindowText((szStopTime = EMPTYSTRING));
		GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->SetWindowText((szCreationTime = EMPTYSTRING));
		GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->SetWindowText((szDataSourceSize = EMPTYSTRING));
	}
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS)->EnableWindow(szProduct.IsEmpty());
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS)->ShowWindow((szProduct.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC)->ShowWindow((!szProduct.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC)->EnableWindow(!szProduct.IsEmpty());
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->ShowWindow((!szProduct.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->EnableWindow(!szProduct.IsEmpty());
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC)->ShowWindow((!szCompany.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC)->EnableWindow(!szCompany.IsEmpty());
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->ShowWindow((!szCompany.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->EnableWindow(!szCompany.IsEmpty());
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC)->ShowWindow((!szSpacecraft.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC)->EnableWindow(!szSpacecraft.IsEmpty());
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->ShowWindow((!szSpacecraft.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->EnableWindow(!szSpacecraft.IsEmpty());
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC)->ShowWindow((!szDataSourceType.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC)->EnableWindow(!szDataSourceType.IsEmpty());
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->ShowWindow((!szDataSourceType.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->EnableWindow(!szDataSourceType.IsEmpty());
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC)->ShowWindow((GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC)->EnableWindow((GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->ShowWindow((GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->EnableWindow((GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO)->ShowWindow((GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO)->EnableWindow((GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->ShowWindow((GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->EnableWindow((GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC)->ShowWindow((GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC)->EnableWindow((GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->ShowWindow((GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->EnableWindow((GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC)->ShowWindow((!szDataSourceSize.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC)->EnableWindow(!szDataSourceSize.IsEmpty());
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->ShowWindow((!szDataSourceSize.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->EnableWindow(!szDataSourceSize.IsEmpty());
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_INSPECT)->EnableWindow(!m_szFileName[0].IsEmpty());
}

BOOL CTCHistorySettingsRetrievingPage::CheckDataSource(LPCTSTR pszFileName) CONST
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
BOOL CTCHistorySettingsRetrievingPage::CheckDataSource(LPCTSTR pszFileName, CString &szProduct, CString &szCompany, CString &szTrademark, CString &szSpacecraft, CString &szDataSourceType, CString &szStartTime, CString &szStopTime, CString &szCreationTime, CString &szDataSourceSize) CONST
{
	CTimeKey  tTime;
	DWORDLONG  dwSize;
	CByteArray  nData;
	CFileFindEx  cFileFind;
	CHistoryFile  cHistoryFile;

	if (cFileFind.FindFile(pszFileName))
	{
		if (cHistoryFile.Open(pszFileName, (LPCTSTR)NULL, HISTORYSTORE_TYPE_TC, CFile::modeRead, TRUE) == HISTORYFILE_SUCCESS)
		{
			for (cHistoryFile.GetCopyrightProduct(szProduct), cHistoryFile.GetCopyrightCompany(szCompany), cHistoryFile.GetCopyrightTrademark(szTrademark), cHistoryFile.GetSpacecraft(szSpacecraft), cHistoryFile.GetType(szDataSourceType), szStartTime = (cHistoryFile.CLogFile::SeekToFirst() && cHistoryFile.CLogFile::Read(tTime, nData)) ? (LPCTSTR)tTime.FormatGmt(STRING(IDS_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEDATATIMEFORMAT)) : EMPTYSTRING, szStopTime = (cHistoryFile.CLogFile::SeekToLast() && cHistoryFile.CLogFile::Read(tTime, nData)) ? (LPCTSTR)tTime.FormatGmt(STRING(IDS_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEDATATIMEFORMAT)) : EMPTYSTRING, szCreationTime = (cHistoryFile.GetCopyrightCreationTime(tTime)) ? (LPCTSTR)tTime.FormatGmt(STRING(IDS_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEDATAFILETIMEFORMAT)) : EMPTYSTRING, szDataSourceSize.Format(STRING(IDS_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEDATASIZEFORMAT), ((dwSize = cHistoryFile.CLogFile::GetSize()) + 512) / 1024), szDataSourceSize = FormatDataSourceSize(szDataSourceSize); !szProduct.IsEmpty() && !szCompany.IsEmpty() && !szTrademark.IsEmpty(); )
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

CString CTCHistorySettingsRetrievingPage::FormatDataSourceSize(LPCTSTR pszDataSourceSize) CONST
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

BOOL CTCHistorySettingsRetrievingPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (m_nMode[0] != m_nMode[1] || m_szFileName[0].CompareNoCase(m_szFileName[1])) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CTCHistorySettingsRetrievingPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (m_szFileName[0].IsEmpty() || CheckDataSource(m_szFileName[0])) : CLocalePropertyPage::Check()) : TRUE);
}

void CTCHistorySettingsRetrievingPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySettingsRetrievingPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySettingsRetrievingPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CTCHistorySettingsRetrievingPage)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_KEY_RELEASETIME, OnRetrieveByReleaseTime)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_KEY_EXECUTIONTIME, OnRetrieveByExecutionTime)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_INSPECT, OnInspect)
	ON_CBN_EDITCHANGE(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_DATASOURCE, OnEditchangeFileName)
	ON_CBN_SELCHANGE(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_DATASOURCE, OnSelchangeFileName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySettingsRetrievingPage message handlers

BOOL CTCHistorySettingsRetrievingPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_KEY_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_KEY_RELEASETIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_KEY_EXECUTIONTIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_DATASOURCE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_DATASOURCE)->EnableWindow();
	EnumDataSources();
	return TRUE;
}

BOOL CTCHistorySettingsRetrievingPage::OnSetActive()
{
	ShowDataSourceInfo();
	return CLocalePropertyPage::OnSetActive();
}

void CTCHistorySettingsRetrievingPage::OnRetrieveByReleaseTime()
{
	m_nMode[0] = (m_nMode[0] & ~TCHISTORY_RETRIEVE_BYEXECUTIONTIME) | TCHISTORY_RETRIEVE_BYRELEASETIME;
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsRetrievingPage::OnRetrieveByExecutionTime()
{
	m_nMode[0] = (m_nMode[0] & ~TCHISTORY_RETRIEVE_BYRELEASETIME) | TCHISTORY_RETRIEVE_BYEXECUTIONTIME;
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsRetrievingPage::OnInspect()
{
	CHourglassCursor  cCursor;

	ShowDataSourceInfo();
}

void CTCHistorySettingsRetrievingPage::OnEditchangeFileName()
{
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_DATASOURCE)->GetWindowText(m_szFileName[0]);
	GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_INSPECT)->EnableWindow(!m_szFileName[0].IsEmpty());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsRetrievingPage::OnSelchangeFileName()
{
	for (m_szFileName[0] = Combobox_GetText(GetDlgItem(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_DATASOURCE), (INT)SendDlgItemMessage(IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_GETCURSEL)); !m_szFileName[0].IsEmpty(); )
	{
		ShowDataSourceInfo();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySettingsPrintingComments

IMPLEMENT_DYNCREATE(CTCHistorySettingsPrintingComments, CEdit)

BEGIN_MESSAGE_MAP(CTCHistorySettingsPrintingComments, CEdit)
	//{{AFX_MSG_MAP(CTCHistorySettingsPrintingComments)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySettingsPrintingComments message handlers

void CTCHistorySettingsPrintingComments::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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
// CTCHistorySettingsPrintingPage property page

IMPLEMENT_DYNCREATE(CTCHistorySettingsPrintingPage, CLocalePropertyPage)

CTCHistorySettingsPrintingPage::CTCHistorySettingsPrintingPage() : CLocalePropertyPage(CTCHistorySettingsPrintingPage::IDD)
{
	//{{AFX_DATA_INIT(CTCHistorySettingsPrintingPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySettingsPrintingPage::Initialize()
{
	CTCHistoryOpenDialog  *pDialog;

	return((((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetPrintJobs(m_pJobs[0])) || GetParentDisplay()->GetPrintJobs(m_pJobs[0])) ? m_pJobs[1].Copy(&m_pJobs[0]) : FALSE);
}

BOOL CTCHistorySettingsPrintingPage::GetJobs(CTCHistoryPrintJobs &pJobs) CONST
{
	return((pJobs.Copy(&m_pJobs[0])) ? Check(FALSE) : FALSE);
}

CTCHistorySettingsDialog *CTCHistorySettingsPrintingPage::GetParentDialog() CONST
{
	return((CTCHistorySettingsDialog *)CLocalePropertyPage::GetParent());
}

CTCHistoryWnd *CTCHistorySettingsPrintingPage::GetParentDisplay() CONST
{
	return((CTCHistoryWnd *)GetParentDialog()->GetParentDisplay());
}

VOID CTCHistorySettingsPrintingPage::ShowJobInfo()
{
	UINT  nMode;
	UINT  nRange[2];
	CTimeKey  tRange[2];
	CTCHistoryPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		CheckDlgButton(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER, ((nMode = pJobInfo->GetPrintMode()) & TCHISTORY_PRINT_ITEMRANGE) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME, (nMode & TCHISTORY_PRINT_RELEASETIMERANGE) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME, (nMode & TCHISTORY_PRINT_EXECUTIONTIMERANGE) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION, ((nMode & TCHISTORY_PRINT_VERIFICATIONSUCCESS) || (nMode & TCHISTORY_PRINT_VERIFICATIONFAILURE)) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION_SUCCESS, (nMode & TCHISTORY_PRINT_VERIFICATIONSUCCESS) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION_FAILURE, (nMode & TCHISTORY_PRINT_VERIFICATIONFAILURE) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_CLEARCOMMENTS, (nMode & TCHISTORY_PRINT_CLEARCOMMENTS) ? TRUE : FALSE);
		SendDlgItemMessage(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_PROFILE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetProfile()));
		Timespinbox_SetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_START), (pJobInfo->GetPrintRange(tRange[0], tRange[1], TRUE)) ? tRange[0] : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_STOP), (pJobInfo->GetPrintRange(tRange[0], tRange[1], TRUE)) ? tRange[1] : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_START), (pJobInfo->GetPrintRange(tRange[0], tRange[1], FALSE)) ? tRange[0] : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_STOP), (pJobInfo->GetPrintRange(tRange[0], tRange[1], FALSE)) ? tRange[1] : CTime::GetCurrentTime().GetTime());
		Spinbox_SetPos(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW), (pJobInfo->GetPrintRange(nRange[0], nRange[1])) ? nRange[0] : 0);
		Spinbox_SetPos(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH), (pJobInfo->GetPrintRange(nRange[0], nRange[1])) ? nRange[1] : 0);
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_COMMENTSTEXT)->SetWindowText(pJobInfo->GetComments());
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_PROFILE_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_PROFILE)->EnableWindow();
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS)->EnableWindow();
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER)->EnableWindow();
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER));
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_TO_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER));
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER));
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME)->EnableWindow();
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_START)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME));
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_TO_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME));
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_STOP)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME));
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME)->EnableWindow();
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_START)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME));
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_TO_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME));
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_STOP)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME));
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION)->EnableWindow();
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION_SUCCESS)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION));
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION_FAILURE)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION));
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_COMMENTS)->EnableWindow();
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_COMMENTSTEXT_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_COMMENTSTEXT)->EnableWindow();
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_CLEARCOMMENTS)->EnableWindow(!pJobInfo->GetComments().IsEmpty());
		return;
	}
	SendDlgItemMessage(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_PROFILE, CB_SETCURSEL, (WPARAM)-1);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION_SUCCESS, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION_FAILURE, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_CLEARCOMMENTS, FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_COMMENTSTEXT)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_DETAILS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_PROFILE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_PROFILE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_TO_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_TO_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_TO_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION_SUCCESS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION_FAILURE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_COMMENTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_COMMENTSTEXT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_COMMENTSTEXT)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_CLEARCOMMENTS)->EnableWindow(FALSE);
}

CTCHistoryPrintJobInfo *CTCHistorySettingsPrintingPage::FindJobInfo() CONST
{
	return m_pJobs[0].GetAt(m_pJobs[0].Find(STRING(IDS_PRINTJOB_DEFAULTNAME)));
}

BOOL CTCHistorySettingsPrintingPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_pJobs[0].Compare(&m_pJobs[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CTCHistorySettingsPrintingPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_PROFILE)->SendMessage(CB_GETCURSEL) >= 0 && (!IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER) || Spinbox_GetPos(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW)) <= Spinbox_GetPos(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH)) && (!IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME) || Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_START)) <= Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_STOP))) && (!IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME) || Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_START)) <= Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_STOP)))) && (!IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION) || IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION_SUCCESS) || IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION_FAILURE))) : CLocalePropertyPage::Check()) : TRUE);
}

void CTCHistorySettingsPrintingPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySettingsPrintingPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCHistorySettingsPrintingPage::PostNcDestroy()
{
	m_pJobs[0].RemoveAll();
	m_pJobs[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCHistorySettingsPrintingPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CTCHistorySettingsPrintingPage)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER, OnPrintItemRange)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME, OnPrintReleaseTimeRange)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME, OnPrintExecutionTimeRange)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION, OnVerificationStatus)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION_SUCCESS, OnVerificationSuccess)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION_FAILURE, OnVerificationFailure)
	ON_BN_CLICKED(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_CLEARCOMMENTS, OnResetComments)
	ON_CBN_SELCHANGE(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_PROFILE, OnSelchangeProfile)
	ON_EN_CHANGE(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_COMMENTSTEXT, OnEditchangeComments)
	ON_CONTROL(SBXN_CHANGE, IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW, OnSpinchangeLowItemRange)
	ON_CONTROL(SBXN_CHANGE, IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH, OnSpinchangeHighItemRange)
	ON_CONTROL(TSBXN_CHANGE, IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_START, OnSpinchangeReleaseStartTimeRange)
	ON_CONTROL(TSBXN_CHANGE, IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_STOP, OnSpinchangeReleaseStopTimeRange)
	ON_CONTROL(TSBXN_CHANGE, IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_START, OnSpinchangeExecutionStartTimeRange)
	ON_CONTROL(TSBXN_CHANGE, IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_STOP, OnSpinchangeExecutionStopTimeRange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySettingsPrintingPage message handlers

BOOL CTCHistorySettingsPrintingPage::OnInitDialog()
{
	INT  nProfile;
	INT  nProfiles;
	CStringArray  szProfiles;
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	for (nProfile = 0, nProfiles = (EnumPrintProfiles(szProfiles)) ? (INT)szProfiles.GetSize() : 0, Spinbox_SetRange(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW), TCHISTORYSETTINGSPRINTINGPAGE_MINIMUMITEMRANGE, TCHISTORYSETTINGSPRINTINGPAGE_MAXIMUMITEMRANGE), Spinbox_SetRange(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH), TCHISTORYSETTINGSPRINTINGPAGE_MINIMUMITEMRANGE, TCHISTORYSETTINGSPRINTINGPAGE_MAXIMUMITEMRANGE), m_wndComments.SubclassWindow(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_COMMENTSTEXT)->GetSafeHwnd()); nProfile < nProfiles; nProfile++)
	{
		SendDlgItemMessage(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_PROFILE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szProfiles.GetAt(nProfile));
		continue;
	}
	ShowJobInfo();
	return TRUE;
}

void CTCHistorySettingsPrintingPage::OnPrintItemRange()
{
	CTCHistoryPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER))
		{
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | TCHISTORY_PRINT_ITEMRANGE);
			pJobInfo->SetPrintRange(TCHISTORYSETTINGSPRINTINGPAGE_MINIMUMITEMRANGE, TCHISTORYSETTINGSPRINTINGPAGE_DEFAULTITEMRANGE);
		}
		else
		{
			pJobInfo->SetPrintRange(0, 0);
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~TCHISTORY_PRINT_ITEMRANGE);
		}
	}
	Spinbox_SetPos(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW), TCHISTORYSETTINGSPRINTINGPAGE_MINIMUMITEMRANGE);
	Spinbox_SetPos(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH), TCHISTORYSETTINGSPRINTINGPAGE_DEFAULTITEMRANGE);
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER));
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_TO_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER));
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER));
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsPrintingPage::OnPrintReleaseTimeRange()
{
	CTimeKey  tTime;
	CTCHistoryPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME))
		{
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | TCHISTORY_PRINT_RELEASETIMERANGE);
			pJobInfo->SetPrintRange(tTime, tTime.GetTime() + SECONDSPERHOUR, TRUE);
		}
		else
		{
			pJobInfo->SetPrintRange(0, 0, TRUE);
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~TCHISTORY_PRINT_RELEASETIMERANGE);
		}
	}
	Timespinbox_SetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_START), tTime);
	Timespinbox_SetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_STOP), CTimeKey(tTime.GetTime() + SECONDSPERHOUR));
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_START)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME));
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_TO_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME));
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_STOP)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME));
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_START)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsPrintingPage::OnPrintExecutionTimeRange()
{
	CTimeKey  tTime;
	CTCHistoryPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME))
		{
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | TCHISTORY_PRINT_EXECUTIONTIMERANGE);
			pJobInfo->SetPrintRange(tTime, tTime.GetTime() + SECONDSPERHOUR, FALSE);
		}
		else
		{
			pJobInfo->SetPrintRange(0, 0, FALSE);
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~TCHISTORY_PRINT_EXECUTIONTIMERANGE);
		}
	}
	Timespinbox_SetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_START), tTime);
	Timespinbox_SetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_STOP), CTimeKey(tTime.GetTime() + SECONDSPERHOUR));
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_START)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME));
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_TO_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME));
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_STOP)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME));
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_START)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsPrintingPage::OnVerificationStatus()
{
	CTCHistoryPrintJobInfo  *pJobInfo;

	for (; (pJobInfo = FindJobInfo()); )
	{
		pJobInfo->SetPrintMode((IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION)) ? ((pJobInfo->GetPrintMode() & ~TCHISTORY_PRINT_VERIFICATIONFAILURE) | TCHISTORY_PRINT_VERIFICATIONSUCCESS) : (pJobInfo->GetPrintMode() & ~(TCHISTORY_PRINT_VERIFICATIONSUCCESS | TCHISTORY_PRINT_VERIFICATIONFAILURE)));
		break;
	}
	CheckDlgButton(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION_FAILURE, FALSE);
	CheckDlgButton(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION_SUCCESS, IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION));
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION_SUCCESS)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION));
	GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION_FAILURE)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsPrintingPage::OnVerificationSuccess()
{
	CTCHistoryPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION_SUCCESS, TRUE), CheckDlgButton(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION_FAILURE, FALSE); (pJobInfo = FindJobInfo()); )
	{
		pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() & ~TCHISTORY_PRINT_VERIFICATIONFAILURE) | TCHISTORY_PRINT_VERIFICATIONSUCCESS);
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsPrintingPage::OnVerificationFailure()
{
	CTCHistoryPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION_SUCCESS, FALSE), CheckDlgButton(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION_FAILURE, TRUE); (pJobInfo = FindJobInfo()); )
	{
		pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() & ~TCHISTORY_PRINT_VERIFICATIONSUCCESS) | TCHISTORY_PRINT_VERIFICATIONFAILURE);
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsPrintingPage::OnSelchangeProfile()
{
	CString  szProfile;
	CTCHistoryPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_PROFILE)->GetWindowText(szProfile);
		pJobInfo->SetProfile(szProfile);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsPrintingPage::OnSpinchangeLowItemRange()
{
	CTCHistoryPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo())) pJobInfo->SetPrintRange((UINT)Spinbox_GetPos(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW)), (UINT)Spinbox_GetPos(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsPrintingPage::OnSpinchangeHighItemRange()
{
	CTCHistoryPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo())) pJobInfo->SetPrintRange((UINT)Spinbox_GetPos(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW)), (UINT)Spinbox_GetPos(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsPrintingPage::OnSpinchangeReleaseStartTimeRange()
{
	CTimeKey  tTime[2];
	CTimeKey  tRange[2];
	CTCHistoryPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (pJobInfo->GetPrintRange(tRange[0], tRange[1], TRUE), tTime[0] = Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_START)); tTime[0] > tRange[1]; )
		{
			tRange[1] = tTime[0];
			break;
		}
		pJobInfo->SetPrintRange(tTime[0], tRange[1], TRUE);
	}
	for (tTime[0] = Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_START)), tTime[1] = Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_STOP)); tTime[0] > tTime[1]; )
	{
		Timespinbox_SetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_STOP), tTime[0]);
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsPrintingPage::OnSpinchangeReleaseStopTimeRange()
{
	CTimeKey  tTime[2];
	CTimeKey  tRange[2];
	CTCHistoryPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (pJobInfo->GetPrintRange(tRange[0], tRange[1], TRUE), tTime[0] = Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_STOP)); tTime[1] < tRange[0]; )
		{
			tRange[0] = tTime[1];
			break;
		}
		pJobInfo->SetPrintRange(tRange[0], tTime[1], TRUE);
	}
	for (tTime[0] = Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_START)), tTime[1] = Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_STOP)); tTime[0] > tTime[1]; )
	{
		Timespinbox_SetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_START), tTime[1]);
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsPrintingPage::OnSpinchangeExecutionStartTimeRange()
{
	CTimeKey  tTime[2];
	CTimeKey  tRange[2];
	CTCHistoryPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (pJobInfo->GetPrintRange(tRange[0], tRange[1], FALSE), tTime[0] = Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_START)); tTime[0] > tRange[1]; )
		{
			tRange[1] = tTime[0];
			break;
		}
		pJobInfo->SetPrintRange(tTime[0], tRange[1], FALSE);
	}
	for (tTime[0] = Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_START)), tTime[1] = Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_STOP)); tTime[0] > tTime[1]; )
	{
		Timespinbox_SetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_STOP), tTime[0]);
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsPrintingPage::OnSpinchangeExecutionStopTimeRange()
{
	CTimeKey  tTime[2];
	CTimeKey  tRange[2];
	CTCHistoryPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (pJobInfo->GetPrintRange(tRange[0], tRange[1], FALSE), tTime[0] = Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_STOP)); tTime[1] < tRange[0]; )
		{
			tRange[0] = tTime[1];
			break;
		}
		pJobInfo->SetPrintRange(tRange[0], tTime[1], FALSE);
	}
	for (tTime[0] = Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_START)), tTime[1] = Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_STOP)); tTime[0] > tTime[1]; )
	{
		Timespinbox_SetTime(GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_START), tTime[1]);
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsPrintingPage::OnEditchangeComments()
{
	CString  szComments;
	CTCHistoryPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_COMMENTSTEXT)->GetWindowText(szComments);
		GetDlgItem(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_CLEARCOMMENTS)->EnableWindow(!szComments.IsEmpty());
		CheckDlgButton(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_CLEARCOMMENTS, (!szComments.IsEmpty()) ? IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_CLEARCOMMENTS) : FALSE);
		pJobInfo->SetPrintMode((IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_CLEARCOMMENTS)) ? (pJobInfo->GetPrintMode() | TCHISTORY_PRINT_CLEARCOMMENTS) : (pJobInfo->GetPrintMode() & ~TCHISTORY_PRINT_CLEARCOMMENTS));
		pJobInfo->SetComments(szComments);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistorySettingsPrintingPage::OnResetComments()
{
	UINT  nMode;
	CTCHistoryPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (IsDlgButtonChecked(IDC_TCHISTORYSETTINGS_PRINTINGPAGE_CLEARCOMMENTS)) ? (pJobInfo->GetPrintMode() | TCHISTORY_PRINT_CLEARCOMMENTS) : (pJobInfo->GetPrintMode() & ~TCHISTORY_PRINT_CLEARCOMMENTS);
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySettingsTabCtrl

IMPLEMENT_DYNCREATE(CTCHistorySettingsTabCtrl, CTabCtrl)

BEGIN_MESSAGE_MAP(CTCHistorySettingsTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CTCHistorySettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySettingsTabCtrl message handlers


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySettingsDialog

IMPLEMENT_DYNCREATE(CTCHistorySettingsDialog, CDisplayPropertySheetDialog)

CTCHistorySettingsDialog::CTCHistorySettingsDialog() : CDisplayPropertySheetDialog()
{
	AddPage(&m_pageLayout);
	AddPage(&m_pageFiltering);
	AddPage(&m_pageRetrieving);
	AddPage(&m_pagePrinting);
}

BOOL CTCHistorySettingsDialog::GetLayoutColumns(CUIntArray &nColumns) CONST
{
	return m_pageLayout.GetColumns(nColumns);
}

BOOL CTCHistorySettingsDialog::GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST
{
	return m_pageLayout.GetTitleFont(pTitleFont);
}

BOOL CTCHistorySettingsDialog::GetLayoutItemsFont(LPLOGFONT pItemsFont) CONST
{
	return m_pageLayout.GetItemsFont(pItemsFont);
}

BOOL CTCHistorySettingsDialog::GetLayoutGridBackgroundColor(COLORREF &nColor) CONST
{
	return m_pageLayout.GetGridBackgroundColor(nColor);
}

BOOL CTCHistorySettingsDialog::GetLayoutToolTipMode(BOOL &bEnable) CONST
{
	return m_pageLayout.GetToolTipMode(bEnable);
}

BOOL CTCHistorySettingsDialog::IsLayoutModified() CONST
{
	return m_pageLayout.IsModified();
}

BOOL CTCHistorySettingsDialog::GetFilterMode(UINT &nMode) CONST
{
	return m_pageFiltering.GetMode(nMode);
}

BOOL CTCHistorySettingsDialog::GetFilterComputer(CString &szComputer) CONST
{
	return m_pageFiltering.GetComputer(szComputer);
}

BOOL CTCHistorySettingsDialog::GetFilterTelecommandName(CString &szName) CONST
{
	return m_pageFiltering.GetTelecommandName(szName);
}

BOOL CTCHistorySettingsDialog::GetFilterTelecommandSequence(CString &szSequence) CONST
{
	return m_pageFiltering.GetTelecommandSequence(szSequence);
}

BOOL CTCHistorySettingsDialog::GetFilterLimitation(UINT &nCount) CONST
{
	return m_pageFiltering.GetLimitation(nCount);
}

BOOL CTCHistorySettingsDialog::GetFilterAutoload(UINT &nCount) CONST
{
	return m_pageFiltering.GetAutoload(nCount);
}

BOOL CTCHistorySettingsDialog::GetFilterSortMode(UINT &nMode) CONST
{
	return m_pageFiltering.GetSortMode(nMode);
}

BOOL CTCHistorySettingsDialog::IsFilteringModified() CONST
{
	return m_pageFiltering.IsModified();
}

BOOL CTCHistorySettingsDialog::GetRetrieveMode(UINT &nMode) CONST
{
	return m_pageRetrieving.GetMode(nMode);
}

BOOL CTCHistorySettingsDialog::GetRetrieveFileName(CString &szFileName) CONST
{
	return m_pageRetrieving.GetDataSourceFileName(szFileName);
}

BOOL CTCHistorySettingsDialog::IsRetrievingModified() CONST
{
	return m_pageRetrieving.IsModified();
}

BOOL CTCHistorySettingsDialog::GetPrintJobs(CTCHistoryPrintJobs &pPrintJobs) CONST
{
	return m_pagePrinting.GetJobs(pPrintJobs);
}

BOOL CTCHistorySettingsDialog::IsPrintingModified() CONST
{
	return m_pagePrinting.IsModified();
}

CTCHistoryOpenDialog *CTCHistorySettingsDialog::GetParentDialog() CONST
{
	return((GetParent() != (CWnd *)GetParentDisplay()) ? (CTCHistoryOpenDialog *)GetParent() : (CTCHistoryOpenDialog *)NULL);
}

CTCHistoryWnd *CTCHistorySettingsDialog::GetParentDisplay() CONST
{
	return((CTCHistoryWnd *)CDisplayPropertySheetDialog::GetParentDisplay());
}

BEGIN_MESSAGE_MAP(CTCHistorySettingsDialog, CDisplayPropertySheetDialog)
	//{{AFX_MSG_MAP(CTCHistorySettingsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySettingsDialog message handlers

BOOL CTCHistorySettingsDialog::OnInitDialog()
{
	INT  nPage;
	INT  nPages;
	CHourglassCursor  cCursor;

	CDisplayPropertySheetDialog::OnInitDialog();
	SetTitle(STRING(IDS_TCHISTORYSETTINGSDIALOG_TITLE));
	for (nPage = 0, nPages = (m_wndTabCtrl.SubclassWindow(GetTabControl()->GetSafeHwnd())) ? GetPageCount() : 0; nPage < nPages; nPage++)
	{
		SetActivePage((nPage + 1) % nPages);
		continue;
	}
	m_wndTabCtrl.SetFocus();
	return FALSE;
}

void CTCHistorySettingsDialog::OnOK()
{
	CHourglassCursor  cCursor;

	ReportEvent(((!GetParentDialog() && !GetParentDisplay()->OnCloseSettingsDialog(IDOK)) || (GetParentDialog() && !GetParentDialog()->OnCloseSettingsDialog(IDOK))) ? SYSTEM_WARNING_TCHISTORY_SETUP_FAILURE : SYSTEM_NOERROR);
	CDisplayPropertySheetDialog::OnOK();
}

void CTCHistorySettingsDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	if (!GetParentDialog()) GetParentDisplay()->OnCloseSettingsDialog(IDCANCEL);
	else  GetParentDialog()->OnCloseSettingsDialog(IDCANCEL);
	CDisplayPropertySheetDialog::OnCancel();
}

BOOL CTCHistorySettingsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSETTINGSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySettingsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSETTINGSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistoryAlertOptionsDialog dialog

IMPLEMENT_DYNCREATE(CTCHistoryAlertOptionsDialog, CDisplayDialog)

CTCHistoryAlertOptionsDialog::CTCHistoryAlertOptionsDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistoryAlertOptionsDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCHistoryAlertOptionsDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CTCHistoryAlertOptionsDialog::IDD);
}

BOOL CTCHistoryAlertOptionsDialog::Initialize()
{
	if (GetParentDisplay()->GetAlertOptions(m_nTypes[0], m_szAuditions[0], m_szNotifications[0], m_nAcknowledgeColors[0], m_bAcknowledgments[0]))
	{
		m_nTypes[1].Copy(m_nTypes[0]);
		m_szAuditions[1].Copy(m_szAuditions[0]);
		m_szNotifications[1].Copy(m_szNotifications[0]);
		m_nAcknowledgeColors[1].Copy(m_nAcknowledgeColors[0]);
		m_bAcknowledgments[1].Copy(m_bAcknowledgments[0]);
		return TRUE;
	}
	return FALSE;
}

CTCHistoryFilteringPage *CTCHistoryAlertOptionsDialog::GetParentDialog() CONST
{
	return((CTCHistoryFilteringPage *)CDisplayDialog::GetParent());
}

CTCHistoryWnd *CTCHistoryAlertOptionsDialog::GetParentDisplay() CONST
{
	return((CTCHistoryWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CTCHistoryAlertOptionsDialog::EnumTypes()
{
	if (SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_TYPE, CB_INSERTSTRING, TCHISTORY_ALERTTYPE_TELECOMMANDACCEPTANCESUCCESS, (LPARAM)STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_ALERTTYPE_TELECOMMANDACCEPTANCESUCCESS)) >= 0 && SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_TYPE, CB_INSERTSTRING, TCHISTORY_ALERTTYPE_TELECOMMANDSTARTSUCCESS, (LPARAM)STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_ALERTTYPE_TELECOMMANDSTARTSUCCESS)) >= 0 && SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_TYPE, CB_INSERTSTRING, TCHISTORY_ALERTTYPE_TELECOMMANDPROGRESSSUCCESS, (LPARAM)STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_ALERTTYPE_TELECOMMANDPROGRESSSUCCESS)) >= 0 && SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_TYPE, CB_INSERTSTRING, TCHISTORY_ALERTTYPE_TELECOMMANDCOMPLETIONSUCCESS, (LPARAM)STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_ALERTTYPE_TELECOMMANDCOMPLETIONSUCCESS)) >= 0 && SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_TYPE, CB_INSERTSTRING, TCHISTORY_ALERTTYPE_TELECOMMANDACCEPTANCEFAILURE, (LPARAM)STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_ALERTTYPE_TELECOMMANDACCEPTANCEFAILURE)) >= 0 && SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_TYPE, CB_INSERTSTRING, TCHISTORY_ALERTTYPE_TELECOMMANDSTARTFAILURE, (LPARAM)STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_ALERTTYPE_TELECOMMANDSTARTFAILURE)) >= 0 && SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_TYPE, CB_INSERTSTRING, TCHISTORY_ALERTTYPE_TELECOMMANDPROGRESSFAILURE, (LPARAM)STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_ALERTTYPE_TELECOMMANDPROGRESSFAILURE)) >= 0 && SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_TYPE, CB_INSERTSTRING, TCHISTORY_ALERTTYPE_TELECOMMANDCOMPLETIONFAILURE, (LPARAM)STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_ALERTTYPE_TELECOMMANDCOMPLETIONFAILURE)) >= 0 && SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_TYPE, CB_INSERTSTRING, TCHISTORY_ALERTTYPE_TELECOMMANDVERIFICATIONFAILURE, (LPARAM)STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_ALERTTYPE_TELECOMMANDVERIFICATIONFAILURE)) >= 0)
	{
		SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_TYPE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_TYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_ALERTTYPE_TELECOMMANDVERIFICATIONFAILURE)));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryAlertOptionsDialog::EnumAuditions()
{
	INT  nAudition;
	INT  nAuditions;
	CStringArray  szAuditions;

	for (nAudition = 0, nAuditions = (EnumAuditionProfiles(szAuditions)) ? (INT)szAuditions.GetSize() : 0; nAudition < nAuditions; nAudition++)
	{
		SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szAuditions.GetAt(nAudition));
		continue;
	}
	SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_AUDITION_NONE));
	return((SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CTCHistoryAlertOptionsDialog::EnumNotifications()
{
	INT  nNotification;
	INT  nNotifications;
	CStringArray  szNotifications;

	for (nNotification = 0, nNotifications = (EnumNotificationProfiles(szNotifications)) ? (INT)szNotifications.GetSize() : 0; nNotification < nNotifications; nNotification++)
	{
		SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szNotifications.GetAt(nNotification));
		continue;
	}
	SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_NOTIFICATION_NONE));
	return((SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CTCHistoryAlertOptionsDialog::ShowAlertDetails()
{
	INT  nPos;
	INT  nAlertType;
	CString  szAudition;
	CString  szNotification[2];

	for (szNotification[0] = ((nAlertType = FindAlertType()) >= 0) ? m_szNotifications[0].GetAt(nAlertType) : EMPTYSTRING, SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_RESETCONTENT); !szNotification[0].IsEmpty(); )
	{
		for (szNotification[1] = szNotification[0]; (nPos = szNotification[0].Find(TAB)) >= 0; )
		{
			szNotification[1] = szNotification[0].Left(nPos);
			szNotification[0] = szNotification[0].Mid(nPos + 1);
			break;
		}
		for (szNotification[0] = (nPos >= 0) ? szNotification[0] : EMPTYSTRING; SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szNotification[1]) < 0; )
		{
			SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szNotification[1]);
			break;
		}
	}
	SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_SETCURSEL);
	SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szAudition = (nAlertType >= 0 && !m_szAuditions[0].GetAt(nAlertType).IsEmpty()) ? m_szAuditions[0].GetAt(nAlertType) : STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_AUDITION_NONE))));
	SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_NOTIFICATION_NONE)), 0));
	SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)((nAlertType >= 0) ? m_nAcknowledgeColors[0].GetAt(nAlertType) : GetSysColor(COLOR_WINDOWTEXT)));
	CheckDlgButton(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_BLINK, (szAudition != STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_AUDITION_NONE) && nAlertType >= 0) ? m_bAcknowledgments[0].GetAt(nAlertType) : FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_BLINK)->EnableWindow((szAudition != STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_AUDITION_NONE)) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_COLOR_STATIC)->EnableWindow((szAudition != STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_AUDITION_NONE)) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_COLOR)->EnableWindow((szAudition != STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_AUDITION_NONE)) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_ADD)->EnableWindow(((szNotification[0] = Combobox_GetText(GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS), (INT)SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS, CB_GETCURSEL))) != STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_NOTIFICATION_NONE) && SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szNotification[0]) < 0) ? CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE) : FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCURSEL) >= 0) ? CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE) : FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCOUNT) > 0) ? CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE) : FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
}

INT CTCHistoryAlertOptionsDialog::FindAlertType() CONST
{
	INT  nType;
	INT  nTypes;
	INT  nAlertType;

	for (nType = 0, nTypes = (INT)m_nTypes[0].GetSize(), nAlertType = (INT)GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_TYPE)->SendMessage(CB_GETCURSEL); nType < nTypes; nType++)
	{
		if (m_nTypes[0].GetAt(nType) == nAlertType) break;
		continue;
	}
	return((nType < nTypes) ? nType : -1);
}

VOID CTCHistoryAlertOptionsDialog::AdjustToPrivileges()
{
	BOOL  bCheck;

	AccessControl(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION, (bCheck = CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE)));
	AccessControl(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_BLINK, bCheck);
	AccessControl(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_COLOR, bCheck);
	AccessControl(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS, bCheck);
}

BOOL CTCHistoryAlertOptionsDialog::IsModified() CONST
{
	INT  nType[2];
	INT  nTypes[2];

	for (nType[0] = 0, nTypes[0] = (m_nTypes[0].GetSize() == m_nTypes[1].GetSize()) ? (INT)m_nTypes[0].GetSize() : -1; nType[0] < nTypes[0]; nType[0]++)
	{
		for (nType[1] = 0, nTypes[1] = (INT)m_nTypes[1].GetSize(); nType[1] < nTypes[1]; nType[1]++)
		{
			if (m_nTypes[0].GetAt(nType[0]) == m_nTypes[1].GetAt(nType[1])) break;
			continue;
		}
		if (nType[1] == nTypes[1] || m_szAuditions[0].GetAt(nType[0]) != m_szAuditions[1].GetAt(nType[1]) || m_szNotifications[0].GetAt(nType[0]) != m_szNotifications[1].GetAt(nType[1]) || m_nAcknowledgeColors[0].GetAt(nType[0]) != m_nAcknowledgeColors[1].GetAt(nType[1]) || m_bAcknowledgments[0].GetAt(nType[0]) != m_bAcknowledgments[1].GetAt(nType[1])) break;
	}
	return((nType[0] != nTypes[0]) ? TRUE : FALSE);
}

void CTCHistoryAlertOptionsDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistoryAlertOptionsDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistoryAlertOptionsDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistoryAlertOptionsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_BLINK, OnAuditionBlink)
	ON_BN_CLICKED(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_ADD, OnAddNotification)
	ON_BN_CLICKED(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVE, OnRemoveNotification)
	ON_BN_CLICKED(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVEALL, OnRemoveAllNotifications)
	ON_BN_CLICKED(IDC_TCHISTORY_ALERTOPTIONS_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_TCHISTORY_ALERTOPTIONS_TYPE, OnSelchangeType)
	ON_CBN_SELCHANGE(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION, OnSelchangeAudition)
	ON_CBN_SELCHANGE(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_COLOR, OnSelchangeAuditionColor)
	ON_CBN_SELCHANGE(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS, OnSelchangeNotification)
	ON_LBN_SELCHANGE(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, OnSelchangeNotificationList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryAlertOptionsDialog message handlers

BOOL CTCHistoryAlertOptionsDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_TYPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_TYPE)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS)->EnableWindow();
	EnumTypes();
	EnumAuditions();
	EnumNotifications();
	ShowAlertDetails();
	AdjustToPrivileges();
	return TRUE;
}

void CTCHistoryAlertOptionsDialog::OnAuditionBlink()
{
	INT  nAlertType;
	CHourglassCursor  cCursor;

	for (; (nAlertType = FindAlertType()) >= 0; )
	{
		m_bAcknowledgments[0].SetAt(nAlertType, IsDlgButtonChecked(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_BLINK));
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistoryAlertOptionsDialog::OnAddNotification()
{
	INT  nIndex;
	INT  nAlertType[2];
	CString  szAudition;
	CString  szNotification;
	CHourglassCursor  cCursor;

	if ((nIndex = (INT)SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)(szNotification = Combobox_GetText(GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS), (INT)SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS, CB_GETCURSEL))))) >= 0)
	{
		for (nAlertType[0] = (INT)SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_TYPE, CB_GETCURSEL), SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_SETCURSEL, nIndex), szAudition = Combobox_GetText(GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION), (INT)SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION, CB_GETCURSEL)), szAudition = (szAudition != STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_AUDITION_NONE)) ? szAudition : EMPTYSTRING; (nAlertType[1] = FindAlertType()) >= 0; )
		{
			m_szNotifications[0].SetAt(nAlertType[1], (!m_szNotifications[0].GetAt(nAlertType[1]).IsEmpty()) ? (m_szNotifications[0].GetAt(nAlertType[1]) + TAB + szNotification) : szNotification);
			break;
		}
		if (nAlertType[1] < 0)
		{
			m_nTypes[0].Add(nAlertType[0]);
			m_szAuditions[0].Add(szAudition);
			m_szNotifications[0].Add(szNotification);
			m_nAcknowledgeColors[0].Add((DWORD)SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_COLOR, CB_GETCURSEL)));
			m_bAcknowledgments[0].Add(IsDlgButtonChecked(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_BLINK));
		}
	}
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCURSEL) >= 0) ? CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE) : FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCOUNT) > 0) ? CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE) : FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistoryAlertOptionsDialog::OnRemoveNotification()
{
	INT  nPos;
	INT  nIndex;
	INT  nAlertType;
	CString  szNotification;
	CHourglassCursor  cCursor;

	for (szNotification = Listbox_GetText(GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST), (nIndex = (INT)SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCURSEL))); SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_DELETESTRING, nIndex) >= 0; )
	{
		for (SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_SETCURSEL); (nAlertType = FindAlertType()) >= 0; )
		{
			if (m_szNotifications[0].GetAt(nAlertType) == szNotification)
			{
				if (m_szAuditions[0].GetAt(nAlertType).IsEmpty())
				{
					m_nTypes[0].RemoveAt(nAlertType);
					m_szAuditions[0].RemoveAt(nAlertType);
					m_szNotifications[0].RemoveAt(nAlertType);
					m_nAcknowledgeColors[0].RemoveAt(nAlertType);
					m_bAcknowledgments[0].RemoveAt(nAlertType);
					break;
				}
				m_szNotifications[0].SetAt(nAlertType, EMPTYSTRING);
				break;
			}
			for (; (nPos = m_szNotifications[0].GetAt(nAlertType).Find(szNotification)) >= 0; )
			{
				m_szNotifications[0].SetAt(nAlertType, (nPos + szNotification.GetLength() < m_szNotifications[0].GetAt(nAlertType).GetLength()) ? (m_szNotifications[0].GetAt(nAlertType).Left(nPos) + m_szNotifications[0].GetAt(nAlertType).Mid(nPos + szNotification.GetLength() + 1)) : m_szNotifications[0].GetAt(nAlertType).Left(max(nPos - 1, 0)));
				break;
			}
			break;
		}
		break;
	}
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_ADD)->EnableWindow(((szNotification = Combobox_GetText(GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS), (INT)SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS, CB_GETCURSEL))) != STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_NOTIFICATION_NONE) && SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szNotification) < 0) ? CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE) : FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCURSEL) >= 0) ? CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE) : FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCOUNT) > 0) ? CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE) : FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistoryAlertOptionsDialog::OnRemoveAllNotifications()
{
	INT  nAlertType;
	CString  szNotification;
	CHourglassCursor  cCursor;

	for (SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_RESETCONTENT); (nAlertType = FindAlertType()) >= 0; )
	{
		if (m_szAuditions[0].GetAt(nAlertType).IsEmpty())
		{
			m_nTypes[0].RemoveAt(nAlertType);
			m_szAuditions[0].RemoveAt(nAlertType);
			m_szNotifications[0].RemoveAt(nAlertType);
			m_nAcknowledgeColors[0].RemoveAt(nAlertType);
			m_bAcknowledgments[0].RemoveAt(nAlertType);
			break;
		}
		m_szNotifications[0].SetAt(nAlertType, EMPTYSTRING);
		break;
	}
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_ADD)->EnableWindow(((szNotification = Combobox_GetText(GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS), (INT)SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS, CB_GETCURSEL))) != STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_NOTIFICATION_NONE) && SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szNotification) < 0) ? CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE) : FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistoryAlertOptionsDialog::OnSelchangeType()
{
	ShowAlertDetails();
}

void CTCHistoryAlertOptionsDialog::OnSelchangeAudition()
{
	INT  nAlertType[2];
	CString  szAudition;

	for (nAlertType[0] = (INT)SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_TYPE, CB_GETCURSEL), GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION)->GetWindowText(szAudition); (nAlertType[1] = FindAlertType()) >= 0; )
	{
		for (m_szAuditions[0].SetAt(nAlertType[1], (szAudition != STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_AUDITION_NONE)) ? szAudition : EMPTYSTRING); szAudition == STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_AUDITION_NONE) && m_szNotifications[0].GetAt(nAlertType[1]).IsEmpty(); )
		{
			m_nTypes[0].RemoveAt(nAlertType[1]);
			m_szAuditions[0].RemoveAt(nAlertType[1]);
			m_szNotifications[0].RemoveAt(nAlertType[1]);
			m_nAcknowledgeColors[0].RemoveAt(nAlertType[1]);
			m_bAcknowledgments[0].RemoveAt(nAlertType[1]);
			break;
		}
		break;
	}
	if (nAlertType[1] < 0)
	{
		if (szAudition != STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_AUDITION_NONE))
		{
			m_nTypes[0].Add(nAlertType[0]);
			m_szAuditions[0].Add(szAudition);
			m_szNotifications[0].Add(EMPTYSTRING);
			m_nAcknowledgeColors[0].Add((DWORD)SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_COLOR, CB_GETCURSEL)));
			m_bAcknowledgments[0].Add(IsDlgButtonChecked(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_BLINK));
		}
	}
	CheckDlgButton(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_BLINK, (szAudition != STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_AUDITION_NONE)) ? IsDlgButtonChecked(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_BLINK) : FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_BLINK)->EnableWindow((szAudition != STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_AUDITION_NONE)) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_COLOR_STATIC)->EnableWindow((szAudition != STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_AUDITION_NONE)) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_COLOR)->EnableWindow((szAudition != STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_AUDITION_NONE)) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistoryAlertOptionsDialog::OnSelchangeAuditionColor()
{
	INT  nAlertType;

	for (; (nAlertType = FindAlertType()) >= 0; )
	{
		m_nAcknowledgeColors[0].SetAt(nAlertType, (DWORD)SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_COLOR, CB_GETCURSEL)));
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistoryAlertOptionsDialog::OnSelchangeNotification()
{
	CString  szNotification;

	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS)->GetWindowText(szNotification);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_ADD)->EnableWindow((szNotification != STRING(IDS_TCHISTORYALERTOPTIONSDIALOG_NOTIFICATION_NONE) && SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szNotification) < 0) ? CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE) : FALSE);
}

void CTCHistoryAlertOptionsDialog::OnSelchangeNotificationList()
{
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCURSEL) >= 0) ? CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE) : FALSE);
	GetDlgItem(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST, LB_GETCOUNT) > 0) ? CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE) : FALSE);
}

void CTCHistoryAlertOptionsDialog::OnOK()
{
	CHourglassCursor  cCursor;

	GetParentDisplay()->SetAlertOptions(m_nTypes[0], m_szAuditions[0], m_szNotifications[0], m_nAcknowledgeColors[0], m_bAcknowledgments[0]);
	CDisplayDialog::OnOK();
}

BOOL CTCHistoryAlertOptionsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYALERTOPTIONSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistoryAlertOptionsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYALERTOPTIONSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistoryItemPropertiesParametersCalibrationPage property page

IMPLEMENT_DYNCREATE(CTCHistoryItemPropertiesParametersCalibrationPage, CLocalePropertyPage)

CTCHistoryItemPropertiesParametersCalibrationPage::CTCHistoryItemPropertiesParametersCalibrationPage() : CLocalePropertyPage(CTCHistoryItemPropertiesParametersCalibrationPage::IDD)
{
	//{{AFX_DATA_INIT(CTCHistoryItemPropertiesParametersCalibrationPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CTCHistoryItemPropertiesParametersCalibrationPage::ShowParameterInfo(CONST CDatabaseTCParameter *pDatabaseTCParameter)
{
	INT  nIndex;
	CString  szName;
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;

	for (SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_NAME, CB_RESETCONTENT), m_nCalTableIDs.RemoveAll(); pDatabaseTCParameter != (CONST CDatabaseTCParameter *) NULL; )
	{
		if ((m_nCalTableType = (pDatabaseTCParameter->GetAttributes() & (TCPARAMETER_CALIBRATION_NUMERICAL | TCPARAMETER_CALIBRATION_STATUS))) == TCPARAMETER_CALIBRATION_NUMERICAL)
		{
			if ((pDatabaseTCNumCalTable = GetDatabase()->GetTCNumCalTables()->GetAt((nIndex = pDatabaseTCParameter->GetCalTableRef()))) != (CDatabaseTCNumCalTable *)NULL)
			{
				for (szName.Format(STRING(IDS_TCHISTORYITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TABLE_FORMAT), (LPCTSTR)pDatabaseTCNumCalTable->GetDescription(), (LPCTSTR)pDatabaseTCNumCalTable->GetName()); pDatabaseTCNumCalTable->GetDescription().IsEmpty(); )
				{
					szName = pDatabaseTCNumCalTable->GetName();
					break;
				}
				SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szName);
				m_nCalTableIDs.Add(nIndex);
			}
		}
		if (pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS)
		{
			if ((pDatabaseTCTxtCalTable = GetDatabase()->GetTCTxtCalTables()->GetAt((nIndex = pDatabaseTCParameter->GetCalTableRef()))))
			{
				for (szName.Format(STRING(IDS_TCHISTORYITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TABLE_FORMAT), (LPCTSTR)pDatabaseTCTxtCalTable->GetDescription(), (LPCTSTR)pDatabaseTCTxtCalTable->GetName()); pDatabaseTCTxtCalTable->GetDescription().IsEmpty(); )
				{
					szName = pDatabaseTCTxtCalTable->GetName();
					break;
				}
				SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szName);
				m_nCalTableIDs.Add(nIndex);
			}
		}
		break;
	}
	SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_NAME, CB_SETCURSEL);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_NAME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_NAME)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	ShowCalibrationInfo();
}

VOID CTCHistoryItemPropertiesParametersCalibrationPage::ShowCalibrationInfo()
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
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;
	CDatabaseTCNumCalPoint  *pDatabaseTCNumCalPoint;
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;
	CDatabaseTCTxtCalPoint  *pDatabaseTCTxtCalPoint;

	SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_DELETEALLITEMS);
	if ((nIndex = (INT)SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCURSEL)) >= 0)
	{
		if ((pDatabaseTCNumCalTable = (m_nCalTableType == TCPARAMETER_CALIBRATION_NUMERICAL) ? GetDatabase()->GetTCNumCalTables()->GetAt(m_nCalTableIDs.GetAt(nIndex)) : (CDatabaseTCNumCalTable *)NULL))
		{
			for (nItem = 0, nItems = (INT)pDatabaseTCNumCalTable->GetSize(); nItem < nItems; nItem++)
			{
				if ((pDatabaseTCNumCalPoint = pDatabaseTCNumCalTable->GetAt(nItem)))
				{
					for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
					{
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER); )
						{
							szItem = cStringTools.ConvertIntToString(nItem + 1);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X); )
						{
							szItem = cStringTools.ConvertFloatToTruncatedString(pDatabaseTCNumCalPoint->GetX());
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y); )
						{
							szItem = cStringTools.ConvertFloatToString(pDatabaseTCNumCalPoint->GetY());
							break;
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS), nItem, szItem);
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS), nItem, nColumn, szItem);
					}
				}
			}
			GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(pDatabaseTCNumCalTable->GetName());
			GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(STRING(IDS_TCHISTORYITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TYPE_NUMERICAL));
			GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow((GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow((GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow();
			GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow();
			return;
		}
		if ((pDatabaseTCTxtCalTable = (m_nCalTableType == TCPARAMETER_CALIBRATION_STATUS) ? GetDatabase()->GetTCTxtCalTables()->GetAt(m_nCalTableIDs.GetAt(nIndex)) : (CDatabaseTCTxtCalTable *)NULL))
		{
			for (nItem = 0, nItems = (INT)pDatabaseTCTxtCalTable->GetSize(); nItem < nItems; nItem++)
			{
				if ((pDatabaseTCTxtCalPoint = pDatabaseTCTxtCalTable->GetAt(nItem)))
				{
					for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
					{
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER); )
						{
							szItem = cStringTools.ConvertIntToString(nItem + 1);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X); )
						{
							if (pDatabaseTCTxtCalPoint->GetRange(fCalPtX, fCalPtY, szCalText) || pDatabaseTCTxtCalPoint->GetPoint(fCalPtX, szCalText))
							{
								for (szCalPtX = szItem = cStringTools.ConvertFloatToTruncatedString(fCalPtX, -1), szCalPtY = cStringTools.ConvertFloatToTruncatedString(fCalPtY, -1); fCalPtX != fCalPtY; )
								{
									szItem.Format(STRING(IDS_TCHISTORYITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINT_RANGE), (LPCTSTR)szCalPtX, (LPCTSTR)szCalPtY);
									break;
								}
								break;
							}
							szItem.Empty();
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y); )
						{
							szItem = (pDatabaseTCTxtCalPoint->GetPoint(fCalPtX, szCalText) || pDatabaseTCTxtCalPoint->GetRange(fCalPtX, fCalPtY, szCalText)) ? (LPCTSTR)szCalText : EMPTYSTRING;
							break;
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS), nItem, szItem);
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS), nItem, nColumn, szItem);
					}
				}
			}
			GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(pDatabaseTCTxtCalTable->GetName());
			GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(STRING(IDS_TCHISTORYITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TYPE_STATUS));
			GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow((GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow((GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow();
			GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow();
			return;
		}
	}
	SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow(FALSE);
}

BOOL CTCHistoryItemPropertiesParametersCalibrationPage::GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST
{
	szX = Listview_GetText(GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS), Listview_GetCurText(GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS)), FindColumnIndex(STRING(IDS_TCHISTORYITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X)));
	szY = Listview_GetText(GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS), Listview_GetCurText(GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS)), FindColumnIndex(STRING(IDS_TCHISTORYITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y)));
	return((!szX.IsEmpty() && !szY.IsEmpty()) ? TRUE : FALSE);
}

CTCHistoryItemPropertiesParametersFolder *CTCHistoryItemPropertiesParametersCalibrationPage::GetParent() CONST
{
	return((CTCHistoryItemPropertiesParametersFolder *)CLocalePropertyPage::GetParent());
}

INT CTCHistoryItemPropertiesParametersCalibrationPage::FindColumnIndex(LPCTSTR pszColumn) CONST
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

void CTCHistoryItemPropertiesParametersCalibrationPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistoryItemPropertiesParametersCalibrationPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCHistoryItemPropertiesParametersCalibrationPage::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_nCalTableIDs.RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCHistoryItemPropertiesParametersCalibrationPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CTCHistoryItemPropertiesParametersCalibrationPage)
	ON_CBN_SELCHANGE(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_NAME, OnSelchangeName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryItemPropertiesParametersCalibrationPage message handlers

BOOL CTCHistoryItemPropertiesParametersCalibrationPage::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	m_szColumns.Add(STRING(IDS_TCHISTORYITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER));
	m_szColumns.Add(STRING(IDS_TCHISTORYITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X));
	m_szColumns.Add(STRING(IDS_TCHISTORYITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y));
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS)->GetClientRect(rColumns);
	SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = (rColumns.Width() - GetSystemMetrics(SM_CXVSCROLL)) / 5; nColumn < nColumns; nWidth = (++nColumn > 0) ? (2 * (rColumns.Width() - GetSystemMetrics(SM_CXVSCROLL)) / 5) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	return TRUE;
}

BOOL CTCHistoryItemPropertiesParametersCalibrationPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CString  szX;
	CString  szY;
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS)
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

void CTCHistoryItemPropertiesParametersCalibrationPage::OnSelchangeName()
{
	ShowCalibrationInfo();
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistoryItemPropertiesParametersFolderTabCtrl

IMPLEMENT_DYNCREATE(CTCHistoryItemPropertiesParametersFolderTabCtrl, CTabCtrl)

CTCHistoryItemPropertiesParametersFolder *CTCHistoryItemPropertiesParametersFolderTabCtrl::GetParent() CONST
{
	return((CTCHistoryItemPropertiesParametersFolder *)CTabCtrl::GetParent());
}

BEGIN_MESSAGE_MAP(CTCHistoryItemPropertiesParametersFolderTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CTCHistoryItemPropertiesParametersFolderTabCtrl)
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryItemPropertiesParametersFolderTabCtrl message handlers

UINT CTCHistoryItemPropertiesParametersFolderTabCtrl::OnGetDlgCode()
{
	return CTabCtrl::OnGetDlgCode() | DLGC_WANTTAB;
}

void CTCHistoryItemPropertiesParametersFolderTabCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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
// CTCHistoryItemPropertiesParametersFolder

IMPLEMENT_DYNCREATE(CTCHistoryItemPropertiesParametersFolder, CLocalePropertySheetDialog)

CTCHistoryItemPropertiesParametersFolder::CTCHistoryItemPropertiesParametersFolder() : CLocalePropertySheetDialog()
{
	AddPage(&m_pageCalibration);
}

BOOL CTCHistoryItemPropertiesParametersFolder::Create(CWnd *pParentWnd, CONST RECT &rect)
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

VOID CTCHistoryItemPropertiesParametersFolder::ShowParameterInfo(CONST CDatabaseTCParameter *pDatabaseTCParameter)
{
	m_pageCalibration.ShowParameterInfo(pDatabaseTCParameter);
}

BOOL CTCHistoryItemPropertiesParametersFolder::GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST
{
	return m_pageCalibration.GetSelectedCalibrationPoint(szX, szY);
}

CTCHistoryItemPropertiesParametersDialog *CTCHistoryItemPropertiesParametersFolder::GetParent() CONST
{
	return((CTCHistoryItemPropertiesParametersDialog *)CLocalePropertySheetDialog::GetParent());
}

BEGIN_MESSAGE_MAP(CTCHistoryItemPropertiesParametersFolder, CLocalePropertySheetDialog)
	//{{AFX_MSG_MAP(CTCHistoryItemPropertiesParametersFolder)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryItemPropertiesParametersFolder message handlers

void CTCHistoryItemPropertiesParametersFolder::OnSetFocus(CWnd *pOldWnd)
{
	if (IsWindow(m_wndTabCtrl.GetSafeHwnd()))
	{
		m_wndTabCtrl.SetFocus();
		return;
	}
	CLocalePropertySheetDialog::OnSetFocus(pOldWnd);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistoryItemPropertiesParametersDialog dialog

IMPLEMENT_DYNCREATE(CTCHistoryItemPropertiesParametersDialog, CDisplayDialog)

CTCHistoryItemPropertiesParametersDialog::CTCHistoryItemPropertiesParametersDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistoryItemPropertiesParametersDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCHistoryItemPropertiesParametersDialog::Create(CWnd *pParentWnd, LPCTSTR pszParameter)
{
	m_szParameter = pszParameter;
	return CDisplayDialog::Create(pParentWnd, CTCHistoryItemPropertiesParametersDialog::IDD);
}

VOID CTCHistoryItemPropertiesParametersDialog::SetSelectedCalibrationPoint(LPCTSTR pszX, LPCTSTR pszY)
{
	m_szX = pszX;
	m_szY = pszY;
}

BOOL CTCHistoryItemPropertiesParametersDialog::GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST
{
	szX = m_szX;
	szY = m_szY;
	return((!szX.IsEmpty() && !szY.IsEmpty()) ? TRUE : FALSE);
}

CDisplayDialog *CTCHistoryItemPropertiesParametersDialog::GetParent() CONST
{
	return((CDisplayDialog *)CDisplayDialog::GetParent());
}

BOOL CTCHistoryItemPropertiesParametersDialog::EnumParameters()
{
	CString  szParameter;
	CDatabaseTCParameter  *pParameter;

	if ((pParameter = GetDatabase()->GetTCParameters()->GetAt(GetDatabase()->GetTCParameters()->Find(m_szParameter))))
	{
		if (pParameter->GetAttributes() & (TCPARAMETER_CALIBRATION_NUMERICAL | TCPARAMETER_CALIBRATION_STATUS))
		{
			szParameter.Format(STRING(IDS_TCHISTORYITEMPROPERTIESPARAMETERSDIALOG_FORMAT), (LPCTSTR)pParameter->GetTag(), (LPCTSTR)pParameter->GetDescription());
			SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_ITEM, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szParameter);
		}
	}
	szParameter.Format(STRING(IDS_TCHISTORYITEMPROPERTIESPARAMETERSDIALOG_FORMAT), (LPCTSTR)m_szParameter, EMPTYSTRING);
	SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_ITEM, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_ITEM, CB_FINDSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter), 0));
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_DETAILS)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_ITEM_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_ITEM)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	m_wndFolderCtrl.EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CTCHistoryItemPropertiesParametersDialog::ShowParameterInfo()
{
	CString  szParameter[2];
	CDatabaseTCParameter  *pParameter;

	for (GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_ITEM)->GetWindowText(szParameter[0]), szParameter[1].Format(STRING(IDS_TCHISTORYITEMPROPERTIESPARAMETERSDIALOG_FORMAT), EMPTYSTRING, EMPTYSTRING), szParameter[0] = (szParameter[0].Find(szParameter[1]) >= 0) ? szParameter[0].Left(szParameter[0].Find(szParameter[1])) : szParameter[0]; (pParameter = GetDatabase()->GetTCParameters()->GetAt(GetDatabase()->GetTCParameters()->Find(szParameter[0]))); )
	{
		m_wndFolderCtrl.ShowParameterInfo(pParameter);
		return;
	}
	m_wndFolderCtrl.ShowParameterInfo();
}

CRect CTCHistoryItemPropertiesParametersDialog::CalcFolderSize() CONST
{
	CRect  rFolder;

	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_FOLDER)->GetWindowRect(rFolder);
	ScreenToClient(rFolder);
	return rFolder;
}

void CTCHistoryItemPropertiesParametersDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistoryItemPropertiesParametersDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistoryItemPropertiesParametersDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistoryItemPropertiesParametersDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_ITEM, OnSelchangeParameter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryItemPropertiesParametersDialog message handlers

BOOL CTCHistoryItemPropertiesParametersDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	for (CDisplayDialog::OnInitDialog(); m_wndFolderCtrl.Create(this, CalcFolderSize()) && SetChildSheet(&m_wndFolderCtrl, GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_FOLDER - 1)); )
	{
		if (EnumParameters()) ShowParameterInfo();
		break;
	}
	return TRUE;
}

void CTCHistoryItemPropertiesParametersDialog::OnSelchangeParameter()
{
	ShowParameterInfo();
}

void CTCHistoryItemPropertiesParametersDialog::OnOK()
{
	CHourglassCursor  cCursor;

	m_wndFolderCtrl.GetSelectedCalibrationPoint(m_szX, m_szY);
	CDisplayDialog::OnOK();
}

BOOL CTCHistoryItemPropertiesParametersDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYITEMPROPERTIESPARAMETERSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistoryItemPropertiesParametersDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYITEMPROPERTIESPARAMETERSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistoryItemPropertiesDialog dialog

IMPLEMENT_DYNCREATE(CTCHistoryItemPropertiesDialog, CDisplayDialog)

CTCHistoryItemPropertiesDialog::CTCHistoryItemPropertiesDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistoryItemPropertiesDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCHistoryItemPropertiesDialog::Create(CWnd *pParentWnd, CONST CTCHistoryItem *pItem)
{
	return((m_cItem.Copy(pItem)) ? CDisplayDialog::Create(pParentWnd, CTCHistoryItemPropertiesDialog::IDD) : -1);
}

CTCHistoryWnd *CTCHistoryItemPropertiesDialog::GetParentDisplay() CONST
{
	return((CTCHistoryWnd *)CDisplayDialog::GetParentDisplay());
}

VOID CTCHistoryItemPropertiesDialog::ShowProperties()
{
	BOOL  bAfterDispatch;
	DWORD  dwReleaseOffset;
	CString  szReleaseDelay;
	CString  szExecutionTime;
	CTimeTag  tReleaseTime[2];
	CTimeTag  tExecutionTime;
	CTimeSpan  tReleaseInterval;

	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_NAME)->SetWindowText(m_cItem.GetName());
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_DESCRIPTION)->SetWindowText(m_cItem.GetDescription());
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME)->SetWindowText((m_cItem.GetReleaseTime() > 0) ? m_cItem.GetReleaseTime().FormatGmt() : STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_RELEASETIME_NONE));
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->SetWindowText((!m_cItem.GetReleaseTimeWindow(dwReleaseOffset, tReleaseInterval, bAfterDispatch)) ? ((m_cItem.GetReleaseTimeWindow(tReleaseTime[0], tReleaseInterval) && tReleaseInterval > 0) ? CTimeTag(tReleaseTime[0].GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds()).FormatGmt() : ((m_cItem.GetReleaseTimeWindow(tReleaseTime[0], tReleaseTime[1]) && tReleaseTime[1] > 0) ? tReleaseTime[1].FormatGmt() : STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_RELEASETIME_NONE))) : ((m_cItem.GetReleaseTime() > 0 && tReleaseInterval > 0) ? CTimeTag(m_cItem.GetReleaseTime().GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds()).FormatGmt() : STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_RELEASETIME_NONE)));
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME)->SetWindowText((m_cItem.GetTransmissionTime() > 0) ? m_cItem.GetTransmissionTime().FormatGmt() : STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_TRANSMISSIONTIME_NONE));
	for (szReleaseDelay.Format(STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_TRANSMISSIONDELAY_FORMAT), max((double)(m_cItem.GetTransmissionTime().GetTime() - m_cItem.GetReleaseTime().GetTime()) / 1000000.0, 0.0)); m_cItem.GetReleaseTime() <= 0 || m_cItem.GetTransmissionTime() <= 0; )
	{
		szReleaseDelay.Empty();
		break;
	}
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_DELAY)->SetWindowText(szReleaseDelay);
	Timespinbox_SetTime(GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION_TIMETAG_TIME), (m_cItem.GetExecutionTime(tExecutionTime)) ? CTimeKey(tExecutionTime.GetTimeInSeconds()) : CTime::GetCurrentTime().GetTime());
	CheckDlgButton(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_OVERRIDEPTV, (m_cItem.GetType() == TCHISTORYITEM_TYPE_FUNCTION && (m_cItem.GetFlags() & TCHISTORYITEM_CHECKFLAG_OVERRIDEPTV)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_OVERRIDEPEV, (m_cItem.GetType() == TCHISTORYITEM_TYPE_FUNCTION && (m_cItem.GetFlags() & TCHISTORYITEM_CHECKFLAG_OVERRIDEPEV)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_OVERRIDECEV, (m_cItem.GetType() == TCHISTORYITEM_TYPE_FUNCTION && (m_cItem.GetFlags() & TCHISTORYITEM_CHECKFLAG_OVERRIDECEV)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_DISABLEPTV, (m_cItem.GetType() == TCHISTORYITEM_TYPE_FUNCTION && (m_cItem.GetFlags() & TCHISTORYITEM_CHECKFLAG_DISABLEPTV)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_DISABLEPEV, (m_cItem.GetType() == TCHISTORYITEM_TYPE_FUNCTION && (m_cItem.GetFlags() & TCHISTORYITEM_CHECKFLAG_DISABLEPEV)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_DISABLECEV, (m_cItem.GetType() == TCHISTORYITEM_TYPE_FUNCTION && (m_cItem.GetFlags() & TCHISTORYITEM_CHECKFLAG_DISABLECEV)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_PREAUTHORIZED, (m_cItem.GetType() == TCHISTORYITEM_TYPE_FUNCTION && (m_cItem.GetFlags() & TCHISTORYITEM_CHECKFLAG_PREAUTHORIZED)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION_IMMEDIATELY, (m_cItem.GetType() == TCHISTORYITEM_TYPE_FUNCTION && (m_cItem.GetFlags() & TCHISTORYITEM_EXECUTIONFLAG_IMMEDIATE)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION_TIMETAG, (m_cItem.GetType() == TCHISTORYITEM_TYPE_FUNCTION && (m_cItem.GetFlags() & TCHISTORYITEM_EXECUTIONFLAG_TIMETAGGED)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION_FIRSTSTEP, (m_cItem.GetType() == TCHISTORYITEM_TYPE_FUNCTION && (m_cItem.GetFlags() & TCHISTORYITEM_EXECUTIONFLAG_1STSTEP)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION_SECONDSTEP, (m_cItem.GetType() == TCHISTORYITEM_TYPE_FUNCTION && (m_cItem.GetFlags() & TCHISTORYITEM_EXECUTIONFLAG_2NDSTEP)) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_OVERRIDEPTV)->EnableWindow(m_cItem.GetType() == TCHISTORYITEM_TYPE_FUNCTION);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_OVERRIDEPEV)->EnableWindow(m_cItem.GetType() == TCHISTORYITEM_TYPE_FUNCTION);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_OVERRIDECEV)->EnableWindow(m_cItem.GetType() == TCHISTORYITEM_TYPE_FUNCTION);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_DISABLEPTV)->EnableWindow(m_cItem.GetType() == TCHISTORYITEM_TYPE_FUNCTION);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_DISABLEPEV)->EnableWindow(m_cItem.GetType() == TCHISTORYITEM_TYPE_FUNCTION);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_DISABLECEV)->EnableWindow(m_cItem.GetType() == TCHISTORYITEM_TYPE_FUNCTION);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_PREAUTHORIZED)->EnableWindow(m_cItem.GetType() == TCHISTORYITEM_TYPE_FUNCTION);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME_STATIC)->EnableWindow((GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME_STATIC)->ShowWindow((GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->EnableWindow((GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->ShowWindow((GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_UNLIMITED)->EnableWindow((!GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->GetWindowTextLength()) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_UNLIMITED)->ShowWindow((!GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->GetWindowTextLength()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_DELAY_STATIC)->EnableWindow((GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_DELAY)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_DELAY_STATIC)->ShowWindow((GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_DELAY)->GetWindowTextLength() > 0) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_DELAY)->EnableWindow((GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_DELAY)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_DELAY)->ShowWindow((GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_DELAY)->GetWindowTextLength() > 0) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION_IMMEDIATELY)->EnableWindow(m_cItem.GetType() == TCHISTORYITEM_TYPE_FUNCTION);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION_TIMETAG)->EnableWindow(m_cItem.GetType() == TCHISTORYITEM_TYPE_FUNCTION);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION_FIRSTSTEP)->EnableWindow(m_cItem.GetType() == TCHISTORYITEM_TYPE_FUNCTION);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION_SECONDSTEP)->EnableWindow(m_cItem.GetType() == TCHISTORYITEM_TYPE_FUNCTION);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION_TIMETAG_TIME)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION_TIMETAG));
	ShowParameters();
	ShowRawData();
}

VOID CTCHistoryItemPropertiesDialog::ShowParameters()
{
	INT  nItem;
	INT  nItems;
	INT  nCount;
	INT  nColumn;
	INT  nColumns;
	INT  nElement;
	INT  nElements;
	INT  nParameter;
	INT  nParameters;
	INT  nBlockItem;
	INT  nBlockItems;
	UINT  nOolStatus;
	CString  szItem;
	CStringArray  szSets;
	CStringTools  cStringTools;
	CDatabaseTCPacket  cPacket;
	CDatabaseTCFunction  *pFunction;
	CDatabaseTCFunctions  pBlockedItems;
	CDatabaseTCParameter  *pParameter;
	CDatabaseTCPacketParameter  *pPacketParameter;
	CDatabaseTCFunctionElement  *pFunctionElement;

	SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_LIST, LVM_DELETEALLITEMS);
	for (nParameter = 0, nParameters = (m_cItem.GetTCPacket(&cPacket)) ? (INT)cPacket.GetSize() : -1, nCount = 0; nParameter < nParameters; nParameter++)
	{
		if ((pPacketParameter = cPacket.GetAt(nParameter)) != (CDatabaseTCPacketParameter *)NULL)
		{
			for (nColumn = 0, nColumns = ((pPacketParameter->GetAttributes() & TCPARAMETER_TYPE_CONSTANT) != TCPARAMETER_TYPE_CONSTANT || IsDlgButtonChecked(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_SHOWALL)) ? (INT)m_szColumns.GetSize() : 0; nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TAG); )
				{
					szItem = pPacketParameter->GetTag();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_DESCRIPTION); )
				{
					szItem = pPacketParameter->GetDescription();
					break;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TYPE))
				{
					szItem = ((pPacketParameter->GetAttributes() & TCPARAMETER_CALIBRATION_NONE) || (pPacketParameter->GetAttributes() & TCPARAMETER_CALIBRATION_DISABLED)) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUETYPE_RAW) : EMPTYSTRING;
					szItem = ((pPacketParameter->GetAttributes() & TCPARAMETER_CALIBRATION_ENABLED) && ((pParameter = GetDatabase()->GetTCParameters()->GetAt(GetDatabase()->GetTCParameters()->Find(pPacketParameter->GetTag())))) && (pParameter->GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL)) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUETYPE_NUMERICAL) : szItem;
					szItem = ((pPacketParameter->GetAttributes() & TCPARAMETER_CALIBRATION_ENABLED) && ((pParameter = GetDatabase()->GetTCParameters()->GetAt(GetDatabase()->GetTCParameters()->Find(pPacketParameter->GetTag())))) && (pParameter->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS)) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUETYPE_STATUS) : szItem;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_BITOFFSET); )
				{
					szItem = cStringTools.ConvertIntToString(8 * pPacketParameter->GetBytePos() + pPacketParameter->GetBitPos());
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_BITLENGTH); )
				{
					szItem = cStringTools.ConvertIntToString(pPacketParameter->GetWidth());
					break;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_CODING))
				{
					szItem = (pPacketParameter->GetAttributes() & TCPARAMETER_CODING_BITPATTERN) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUECODING_BITPATTERN) : EMPTYSTRING;
					szItem = (pPacketParameter->GetAttributes() & TCPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUECODING_SIGNEDINTEGER) : szItem;
					szItem = (pPacketParameter->GetAttributes() & TCPARAMETER_CODING_UNSIGNEDINTEGER) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUECODING_UNSIGNEDINTEGER) : szItem;
					szItem = (pPacketParameter->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUECODING_FLOATINGPOINT) : szItem;
					szItem = (pPacketParameter->GetAttributes() & TCPARAMETER_CODING_TIME) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUECODING_DATETIME) : szItem;
					szItem = (pPacketParameter->GetAttributes() & TCPARAMETER_CODING_TEXTSTRING) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUECODING_STRING) : szItem;
					szItem = ((pPacketParameter->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME | TCPARAMETER_CODING_TEXTSTRING)) == 0) ? (((pPacketParameter->GetAttributes() & TCPARAMETER_RADIX_DECIMAL) || (pPacketParameter->GetAttributes() & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_DECIMAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUECODING_UNSIGNEDINTEGER) : STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUECODING_BITPATTERN)) : szItem;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_RADIX))
				{
					szItem = (pPacketParameter->GetAttributes() & TCPARAMETER_RADIX_BINARY) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUERADIX_BINARY) : EMPTYSTRING;
					szItem = (pPacketParameter->GetAttributes() & TCPARAMETER_RADIX_OCTAL) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUERADIX_OCTAL) : szItem;
					szItem = (pPacketParameter->GetAttributes() & TCPARAMETER_RADIX_DECIMAL) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUERADIX_DECIMAL) : szItem;
					szItem = (pPacketParameter->GetAttributes() & TCPARAMETER_RADIX_HEXADECIMAL) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUERADIX_HEXADECIMAL) : szItem;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_FLAG); )
				{
					szItem = ((pPacketParameter->GetAttributes() & (TCPARAMETER_TYPE_CONSTANT | TCPARAMETER_VTYPE_AUTO)) == TCPARAMETER_TYPE_CONSTANT) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUEFLAG_FIXED) : (((pPacketParameter->GetAttributes() & TCPARAMETER_VTYPE_AUTO) != TCPARAMETER_VTYPE_AUTO) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUEFLAG_VARIABLE) : STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUEFLAG_AUTOMATIC));
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_VALUE); )
				{
					szItem = pPacketParameter->GetConstValueAsText();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_LIMITCHECK); )
				{
					if (GetTCService()->CheckTCPacketParameterOolStatus(pPacketParameter, nOolStatus))
					{
						if (nOolStatus == TCPARAMETER_STATUS_NOLIMIT)
						{
							szItem = STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_LIMITCHECK_NOLIMIT);
							break;
						}
						if (nOolStatus == TCPARAMETER_STATUS_SOFTLIMIT)
						{
							szItem = STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_LIMITCHECK_SOFTLIMIT);
							break;
						}
						if (nOolStatus == TCPARAMETER_STATUS_HARDLIMIT)
						{
							szItem = STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_LIMITCHECK_HARDLIMIT);
							break;
						}
						if (nOolStatus == TCPARAMETER_STATUS_DELTALIMIT)
						{
							szItem = STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_LIMITCHECK_DELTALIMIT);
							break;
						}
						if (nOolStatus == TCPARAMETER_STATUS_VALUELIMIT)
						{
							szItem = STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_LIMITCHECK_VALUELIMIT);
							break;
						}
						szItem = (!pPacketParameter->GetConstValueAsText().IsEmpty()) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_LIMITCHECK_NONE) : ((pPacketParameter->GetAttributes() & TCPARAMETER_CODING_TIME) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_LIMITCHECK_NOTIME) : EMPTYSTRING);
						break;
					}
					szItem = STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_LIMITCHECK_FAILURE);
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_LIST), nCount, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_LIST), nCount, nColumn, szItem);
				nCount = (nColumn == nColumns - 1) ? (nCount + 1) : nCount;
			}
		}
	}
	for (nBlockItem = -1, nBlockItems = m_cItem.GetReleaseBlockedItems(pBlockedItems); nBlockItem < nBlockItems; nBlockItem++)
	{
		for (nElement = 0, nElements = ((pFunction = pBlockedItems.GetAt(nBlockItem))) ? (INT)pFunction->GetSize() : (INT)m_cItem.GetSize(); nElement < nElements; nElement++)
		{
			if ((pFunctionElement = (nBlockItem >= 0) ? pFunction->GetAt(nElement) : m_cItem.GetAt(nElement)) != (CDatabaseTCFunctionElement *)NULL)
			{
				for (nItem = 0, nItems = (INT)SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_LIST, LVM_GETITEMCOUNT); nItem < nItems; nItem++)
				{
					if (_ttoi(Listview_GetText(GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_LIST), nItem, FindColumnIndex(STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_BITOFFSET)))) > 8 * pFunctionElement->GetBytePos() + pFunctionElement->GetBitPos()) break;
					continue;
				}
				for (nColumn = 0, nColumns = ((pFunctionElement->GetAttributes() & TCPARAMETER_TYPE_CONSTANT) != TCPARAMETER_TYPE_CONSTANT || IsDlgButtonChecked(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_SHOWALL)) ? (INT)m_szColumns.GetSize() : 0; nColumn < nColumns; nColumn++)
				{
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TAG); )
					{
						szItem = pFunctionElement->GetName();
						break;
					}
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_DESCRIPTION); )
					{
						szItem = pFunctionElement->GetDescription();
						break;
					}
					if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TYPE))
					{
						szItem = ((pFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_NONE) || (pFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_DISABLED)) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUETYPE_RAW) : EMPTYSTRING;
						szItem = ((pFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_ENABLED) && ((pParameter = GetDatabase()->GetTCParameters()->GetAt(GetDatabase()->GetTCParameters()->Find(pFunctionElement->GetName())))) && (pParameter->GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL)) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUETYPE_NUMERICAL) : szItem;
						szItem = ((pFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_ENABLED) && ((pParameter = GetDatabase()->GetTCParameters()->GetAt(GetDatabase()->GetTCParameters()->Find(pFunctionElement->GetName())))) && (pParameter->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS)) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUETYPE_STATUS) : szItem;
					}
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_BITOFFSET); )
					{
						szItem = cStringTools.ConvertIntToString(8 * pFunctionElement->GetBytePos() + pFunctionElement->GetBitPos());
						break;
					}
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_BITLENGTH); )
					{
						szItem = cStringTools.ConvertIntToString(pFunctionElement->GetWidth());
						break;
					}
					if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_CODING))
					{
						szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_CODING_BITPATTERN) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUECODING_BITPATTERN) : EMPTYSTRING;
						szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUECODING_SIGNEDINTEGER) : szItem;
						szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_CODING_UNSIGNEDINTEGER) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUECODING_UNSIGNEDINTEGER) : szItem;
						szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUECODING_FLOATINGPOINT) : szItem;
						szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_CODING_TIME) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUECODING_DATETIME) : szItem;
						szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_CODING_TEXTSTRING) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUECODING_STRING) : szItem;
						szItem = ((pFunctionElement->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME | TCPARAMETER_CODING_TEXTSTRING)) == 0) ? (((pFunctionElement->GetAttributes() & TCPARAMETER_RADIX_DECIMAL) || (pFunctionElement->GetAttributes() & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_DECIMAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUECODING_UNSIGNEDINTEGER) : STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUECODING_BITPATTERN)) : szItem;
					}
					if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_RADIX))
					{
						szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_RADIX_BINARY) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUERADIX_BINARY) : EMPTYSTRING;
						szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_RADIX_OCTAL) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUERADIX_OCTAL) : szItem;
						szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_RADIX_DECIMAL) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUERADIX_DECIMAL) : szItem;
						szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_RADIX_HEXADECIMAL) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUERADIX_HEXADECIMAL) : szItem;
					}
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_FLAG); )
					{
						szItem = ((pFunctionElement->GetAttributes() & (TCPARAMETER_TYPE_CONSTANT | TCPARAMETER_VTYPE_AUTO)) == TCPARAMETER_TYPE_CONSTANT) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUEFLAG_FIXED) : (((pFunctionElement->GetAttributes() & TCPARAMETER_VTYPE_AUTO) != TCPARAMETER_VTYPE_AUTO) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUEFLAG_VARIABLE) : STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUEFLAG_AUTOMATIC));
						break;
					}
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_VALUE); )
					{
						szItem = pFunctionElement->GetConstValueAsText();
						break;
					}
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_LIMITCHECK); )
					{
						if (GetTCService()->CheckTCFunctionElementOolStatus(pFunctionElement, nOolStatus))
						{
							if (nOolStatus == TCPARAMETER_STATUS_NOLIMIT)
							{
								szItem = STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_LIMITCHECK_NOLIMIT);
								break;
							}
							if (nOolStatus == TCPARAMETER_STATUS_SOFTLIMIT)
							{
								szItem = STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_LIMITCHECK_SOFTLIMIT);
								break;
							}
							if (nOolStatus == TCPARAMETER_STATUS_HARDLIMIT)
							{
								szItem = STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_LIMITCHECK_HARDLIMIT);
								break;
							}
							if (nOolStatus == TCPARAMETER_STATUS_DELTALIMIT)
							{
								szItem = STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_LIMITCHECK_DELTALIMIT);
								break;
							}
							if (nOolStatus == TCPARAMETER_STATUS_VALUELIMIT)
							{
								szItem = STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_LIMITCHECK_VALUELIMIT);
								break;
							}
							szItem = (!pFunctionElement->GetConstValueAsText().IsEmpty()) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_LIMITCHECK_NONE) : ((pFunctionElement->GetAttributes() & TCPARAMETER_CODING_TIME) ? STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_LIMITCHECK_NOTIME) : EMPTYSTRING);
							break;
						}
						szItem = STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_LIMITCHECK_FAILURE);
						break;
					}
					if (!nColumn)
					{
						Listview_InsertText(GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_LIST), nItem, szItem);
						continue;
					}
					Listview_SetText(GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_LIST), nItem, nColumn, szItem);
				}
			}
		}
	}
	for (GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS)->EnableWindow((nParameters > 0 || nElements > 0) ? TRUE : FALSE), GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_SHOWALL)->EnableWindow((nParameters > 0 || nElements > 0) ? TRUE : FALSE); SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_LIST, LVM_GETITEMCOUNT) > 0; )
	{
		Listview_SetCurText(GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_LIST), 0);
		GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_LIST)->EnableWindow();
		return;
	}
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_REMARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_REMARK)->EnableWindow(FALSE);
}

VOID CTCHistoryItemPropertiesDialog::ShowRawData()
{
	INT  nByte;
	INT  nBytes;
	CString  szRawData[2];
	CByteArray  nRawData[2];
	CStringTools  cStringTools;
	CDatabaseTCPacket  cPacket;
	CTCPacket  cTCPacket;

	if (m_cItem.GetTCPacket(&cPacket))
	{
		szRawData[0].Format(STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_RAWDATA_FORMAT), (LPCTSTR)cPacket.GetDescription(), (LPCTSTR)cPacket.GetTag());
		szRawData[1].Format(STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_RAWDATA_SIMPLEFORMAT), (LPCTSTR)cPacket.GetTag());
		GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_RAWDATA)->SetWindowText((!cPacket.GetDescription().IsEmpty()) ? szRawData[0] : szRawData[1]);
	}
	for (nByte = 0, nBytes = (m_cItem.GetTCPacket(nRawData[0]) > 0 && cTCPacket.Unmap(nRawData[0])) ? cTCPacket.GetData(nRawData[1]) : 0, szRawData[0].Empty(); nByte < nBytes; nByte++)
	{
		szRawData[0] += (nByte > 0 && nByte % 2 == 0) ? CString(SPACE) : CString(EMPTYSTRING);
		szRawData[0] += cStringTools.ConvertIntToPaddedString(nRawData[1].GetAt(nByte), 2, 16);
	}
	for (; !szRawData[0].IsEmpty(); )
	{
		GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_RAWDATA_AREA)->SetWindowText(szRawData[0]);
		break;
	}
}

INT CTCHistoryItemPropertiesDialog::FindColumnIndex(LPCTSTR pszColumn) CONST
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

void CTCHistoryItemPropertiesDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistoryItemPropertiesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCHistoryItemPropertiesDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCHistoryItemPropertiesDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistoryItemPropertiesDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_SHOWALL, OnShowAllParameters)
	ON_BN_CLICKED(IDC_TCHISTORY_ITEMPROPERTIES_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryItemPropertiesDialog message handlers

BOOL CTCHistoryItemPropertiesDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CFont  cFont;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	m_szColumns.Add(STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TAG));
	m_szColumns.Add(STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_DESCRIPTION));
	m_szColumns.Add(STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TYPE));
	m_szColumns.Add(STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_BITOFFSET));
	m_szColumns.Add(STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_BITLENGTH));
	m_szColumns.Add(STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_CODING));
	m_szColumns.Add(STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_RADIX));
	m_szColumns.Add(STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_FLAG));
	m_szColumns.Add(STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_VALUE));
	m_szColumns.Add(STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_LIMITCHECK));
	for (GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_LIST)->GetClientRect(rColumns); cFont.CreateStockObject(ANSI_FIXED_FONT); )
	{
		GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_RAWDATA_AREA)->SetFont(&cFont);
		break;
	}
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_LIST), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TAG)) ? (rColumns.Width() / 5) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_DESCRIPTION)) ? (2 * rColumns.Width() / 5) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TYPE) || m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_FLAG)) ? (rColumns.Width() / 7) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_BITOFFSET) || m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_BITLENGTH)) ? (rColumns.Width() / 9) : (9 * rColumns.Width() / 35)))));
		continue;
	}
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_NAME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_RAWDATA)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_RAWDATA_AREA)->EnableWindow();
	AccessControl(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_OVERRIDEPTV, FALSE);
	AccessControl(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_OVERRIDEPEV, FALSE);
	AccessControl(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_OVERRIDECEV, FALSE);
	AccessControl(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_DISABLEPTV, FALSE);
	AccessControl(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_DISABLEPEV, FALSE);
	AccessControl(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_DISABLECEV, FALSE);
	AccessControl(IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_PREAUTHORIZED, FALSE);
	AccessControl(IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION_IMMEDIATELY, FALSE);
	AccessControl(IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION_TIMETAG, FALSE);
	AccessControl(IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION_TIMETAG_TIME, FALSE);
	AccessControl(IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION_FIRSTSTEP, FALSE);
	AccessControl(IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION_SECONDSTEP, FALSE);
	ShowProperties();
	return TRUE;
}

BOOL CTCHistoryItemPropertiesDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CTCHistoryItemPropertiesParametersDialog  cParametersDialog;
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_LIST)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED))
		{
			GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_REMARK)->ShowWindow((Listview_GetText(GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_LIST), pNotifyListView->iItem, FindColumnIndex(STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TYPE))) != STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUETYPE_RAW)) ? SW_SHOW : SW_HIDE);
			GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_REMARK)->EnableWindow((Listview_GetText(GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_LIST), pNotifyListView->iItem, FindColumnIndex(STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TYPE))) != STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUETYPE_RAW)) ? TRUE : FALSE);
			GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_LIST)->SetFocus();
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK  &&  Listview_GetText(GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_LIST), pNotifyListView->iItem, FindColumnIndex(STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TYPE))) != STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUETYPE_RAW)) cParametersDialog.Create(this, Listview_GetText(GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_LIST), pNotifyListView->iItem, FindColumnIndex(STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TAG))));
	}
	return CDisplayDialog::OnNotify(wParam, lParam, pResult);
}

void CTCHistoryItemPropertiesDialog::OnShowAllParameters()
{
	CHourglassCursor  cCursor;

	ShowParameters();
}

void CTCHistoryItemPropertiesDialog::OnOK()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnOK();
}

BOOL CTCHistoryItemPropertiesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYITEMPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistoryItemPropertiesDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYITEMPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistoryComposedItemPropertiesDialog dialog

IMPLEMENT_DYNCREATE(CTCHistoryComposedItemPropertiesDialog, CDisplayDialog)

CTCHistoryComposedItemPropertiesDialog::CTCHistoryComposedItemPropertiesDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistoryComposedItemPropertiesDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCHistoryComposedItemPropertiesDialog::Create(CWnd *pParentWnd, CONST CTCHistoryItems &pItems)
{
	INT  nItem[2];
	INT  nItems[2];
	CTCHistoryItem  *pItem[3];

	for (nItem[0] = 0, nItems[0] = (INT)pItems.GetSize(), m_pItems.RemoveAll(); nItem[0] < nItems[0]; nItem[0]++)
	{
		if ((pItem[0] = pItems.GetAt(nItem[0])))
		{
			if ((pItem[1] = new CTCHistoryItem))
			{
				if (pItem[1]->Copy(pItem[0]))
				{
					for (nItem[1] = 0, nItems[1] = (INT)m_pItems.GetSize(); nItem[1] < nItems[1]; nItem[1]++)
					{
						if ((pItem[2] = m_pItems.GetAt(nItem[1])) && pItem[1]->GetMembershipID() < pItem[2]->GetMembershipID()) break;
						continue;
					}
					m_pItems.InsertAt(nItem[1], pItem[1], 1);
					continue;
				}
				delete pItem[1];
			}
		}
	}
	return CDisplayDialog::Create(pParentWnd, CTCHistoryComposedItemPropertiesDialog::IDD);
}

CTCHistoryWnd *CTCHistoryComposedItemPropertiesDialog::GetParentDisplay() CONST
{
	return((CTCHistoryWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CTCHistoryComposedItemPropertiesDialog::EnumEntries()
{
	INT  nEntry;
	INT  nEntries;
	INT  nDigits;
	CString  szEntry[2];
	CStringTools  cStringTools;
	CTCHistoryItem  *pItem;

	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY)->GetWindowText(szEntry[0]);
	for (nEntry = 0, nEntries = (INT)m_pItems.GetSize(), m_szName.Empty(), m_szDescription.Empty(), m_pParameters.RemoveAll(), nDigits = cStringTools.ConvertIntToString(nEntries).GetLength(); nEntry < nEntries; nEntry++)
	{
		if ((pItem = (CTCHistoryItem *)m_pItems.GetAt(nEntry)) != (CTCHistoryItem *)NULL)
		{
			for (szEntry[1].Format(STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_ENTRY_FORMAT), (LPCTSTR)cStringTools.ConvertIntToPaddedString(nEntry + 1, nDigits), (LPCTSTR)pItem->GetName(), (LPCTSTR)pItem->GetDescription()); SendDlgItemMessage(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szEntry[1]) < 0; )
			{
				SendDlgItemMessage(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY, CB_INSERTSTRING, nEntry, (LPARAM)(LPCTSTR)szEntry[1]);
				break;
			}
			if (!nEntry)
			{
				m_szName = pItem->GetMembership();
				m_szDescription = pItem->GetMembershipDescription();
				pItem->GetMembershipParameters(m_pParameters);
			}
		}
	}
	while (nEntries < SendDlgItemMessage(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY, CB_GETCOUNT))
	{
		SendDlgItemMessage(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY, CB_DELETESTRING, nEntries);
		continue;
	}
	SendDlgItemMessage(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szEntry[0]), 0));
	return((SendDlgItemMessage(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CTCHistoryComposedItemPropertiesDialog::ShowProperties()
{
	BOOL  bAfterDispatch;
	DWORD  dwReleaseOffset;
	CString  szReleaseDelay;
	CTimeTag  tReleaseTime[2];
	CTimeTag  tExecutionTime;
	CTimeSpan  tReleaseInterval;
	CTCHistoryItem  *pItem;

	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_NAME)->SetWindowText(m_szName);
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_DESCRIPTION)->SetWindowText(m_szDescription);
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SHOWFORMALLIST)->EnableWindow((m_pParameters.GetSize() > 0) ? TRUE : FALSE);
	for (CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SHOWFORMALLIST, FALSE); (pItem = m_pItems.GetAt((INT)SendDlgItemMessage(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY, CB_GETCURSEL))); )
	{
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME)->SetWindowText((pItem->GetReleaseTime() > 0) ? pItem->GetReleaseTime().FormatGmt() : STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_RELEASETIME_NONE));
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->SetWindowText((!pItem->GetReleaseTimeWindow(dwReleaseOffset, tReleaseInterval, bAfterDispatch)) ? ((pItem->GetReleaseTimeWindow(tReleaseTime[0], tReleaseInterval) && tReleaseInterval > 0) ? CTimeTag(tReleaseTime[0].GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds()).FormatGmt() : ((pItem->GetReleaseTimeWindow(tReleaseTime[0], tReleaseTime[1]) && tReleaseTime[1] > 0) ? tReleaseTime[1].FormatGmt() : STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_RELEASETIME_NONE))) : ((pItem->GetReleaseTime() > 0 && tReleaseInterval > 0) ? CTimeTag(pItem->GetReleaseTime().GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds()).FormatGmt() : STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_RELEASETIME_NONE)));
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME)->SetWindowText((pItem->GetTransmissionTime() > 0) ? pItem->GetTransmissionTime().FormatGmt() : STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_TRANSMISSIONTIME_NONE));
		for (szReleaseDelay.Format(STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_TRANSMISSIONDELAY_FORMAT), max((double)(pItem->GetTransmissionTime().GetTime() - pItem->GetReleaseTime().GetTime()) / 1000000.0, 0.0)); pItem->GetReleaseTime() <= 0 || pItem->GetTransmissionTime() <= 0; )
		{
			szReleaseDelay.Empty();
			break;
		}
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY)->SetWindowText(szReleaseDelay);
		Timespinbox_SetTime(GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_TIMETAG_TIME), (pItem->GetExecutionTime(tExecutionTime)) ? CTimeKey(tExecutionTime.GetTimeInSeconds()) : CTime::GetCurrentTime().GetTime());
		CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDEPTV, (pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION && (pItem->GetFlags() & TCHISTORYITEM_CHECKFLAG_OVERRIDEPTV)) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDEPEV, (pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION && (pItem->GetFlags() & TCHISTORYITEM_CHECKFLAG_OVERRIDEPEV)) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDECEV, (pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION && (pItem->GetFlags() & TCHISTORYITEM_CHECKFLAG_OVERRIDECEV)) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLEPTV, (pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION && (pItem->GetFlags() & TCHISTORYITEM_CHECKFLAG_DISABLEPTV)) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLEPEV, (pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION && (pItem->GetFlags() & TCHISTORYITEM_CHECKFLAG_DISABLEPEV)) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLECEV, (pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION && (pItem->GetFlags() & TCHISTORYITEM_CHECKFLAG_DISABLECEV)) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_PREAUTHORIZED, (pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION && (pItem->GetFlags() & TCHISTORYITEM_CHECKFLAG_PREAUTHORIZED)) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_IMMEDIATELY, (pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION && (pItem->GetFlags() & TCHISTORYITEM_EXECUTIONFLAG_IMMEDIATE)) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_TIMETAG, (pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION && (pItem->GetFlags() & TCHISTORYITEM_EXECUTIONFLAG_TIMETAGGED)) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_FIRSTSTEP, (pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION && (pItem->GetFlags() & TCHISTORYITEM_EXECUTIONFLAG_1STSTEP)) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_SECONDSTEP, (pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION && (pItem->GetFlags() & TCHISTORYITEM_EXECUTIONFLAG_2NDSTEP)) ? TRUE : FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDEPTV)->EnableWindow(pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDEPEV)->EnableWindow(pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDECEV)->EnableWindow(pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLEPTV)->EnableWindow(pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLEPEV)->EnableWindow(pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLECEV)->EnableWindow(pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_PREAUTHORIZED)->EnableWindow(pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME)->EnableWindow();
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME_NONE)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME_NONE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME_STATIC)->EnableWindow((GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME_STATIC)->ShowWindow((GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->EnableWindow((GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->ShowWindow((GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME_NONE)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME_NONE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_UNLIMITED)->EnableWindow((!GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->GetWindowTextLength()) ? TRUE : FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_UNLIMITED)->ShowWindow((!GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->GetWindowTextLength()) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME_STATIC)->EnableWindow((pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION) ? TRUE : FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME_STATIC)->ShowWindow((pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME)->EnableWindow();
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME_NONE)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME_NONE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_EXECUTIONTIME_STATIC)->EnableWindow((pItem->GetType() == TCHISTORYITEM_TYPE_PROCEDURE) ? TRUE : FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_EXECUTIONTIME_STATIC)->ShowWindow((pItem->GetType() == TCHISTORYITEM_TYPE_PROCEDURE) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY_STATIC)->EnableWindow((GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY)->GetWindowTextLength() > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY_STATIC)->ShowWindow((GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY)->GetWindowTextLength() > 0) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY)->EnableWindow((GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY)->GetWindowTextLength() > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY)->ShowWindow((GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY)->GetWindowTextLength() > 0) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY_NONE)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY_NONE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION)->EnableWindow((pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION) ? TRUE : FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_IMMEDIATELY)->EnableWindow((pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION) ? TRUE : FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_TIMETAG)->EnableWindow((pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION) ? TRUE : FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_TIMETAG_TIME)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_TIMETAG));
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_FIRSTSTEP)->EnableWindow((pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION) ? TRUE : FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_SECONDSTEP)->EnableWindow((pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION) ? TRUE : FALSE);
		break;
	}
	if (SendDlgItemMessage(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY, CB_GETCURSEL) < 0)
	{
		CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDEPTV, FALSE);
		CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDEPEV, FALSE);
		CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDECEV, FALSE);
		CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLEPTV, FALSE);
		CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLEPEV, FALSE);
		CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLECEV, FALSE);
		CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_PREAUTHORIZED, FALSE);
		CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_IMMEDIATELY, FALSE);
		CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_TIMETAG, FALSE);
		CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_FIRSTSTEP, FALSE);
		CheckDlgButton(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_SECONDSTEP, FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDEPTV)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDEPEV)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDECEV)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLEPTV)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLEPEV)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLECEV)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_PREAUTHORIZED)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME_NONE)->EnableWindow();
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME_NONE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME_NONE)->EnableWindow();
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME_NONE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_UNLIMITED)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_UNLIMITED)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME_NONE)->EnableWindow();
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME_NONE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY_NONE)->EnableWindow();
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY_NONE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_IMMEDIATELY)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_TIMETAG)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_TIMETAG_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_FIRSTSTEP)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_SECONDSTEP)->EnableWindow(FALSE);
	}
	ShowParameters();
	ShowRawData();
}

VOID CTCHistoryComposedItemPropertiesDialog::ShowParameters()
{
	INT  nItem;
	INT  nItems;
	INT  nCount;
	INT  nColumn;
	INT  nColumns;
	INT  nElement;
	INT  nElements;
	INT  nParameter;
	INT  nParameters;
	INT  nBlockItem;
	INT  nBlockItems;
	UINT  nOolStatus;
	CString  szItem;
	CStringArray  szSets;
	CStringTools  cStringTools;
	CDatabaseTCPacket  cPacket;
	CDatabaseTCFunction  *pFunction;
	CDatabaseTCFunctions  pBlockedItems;
	CDatabaseTCParameter  *pParameter;
	CDatabaseTCPacketParameter  *pPacketParameter;
	CDatabaseTCFunctionElement  *pFunctionElement;
	CTCHistoryItem  *pItem;

	SendDlgItemMessage(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST, LVM_DELETEALLITEMS);
	for (nParameter = nParameters = 0, nElement = nElements = 0; IsDlgButtonChecked(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SHOWFORMALLIST); )
	{
		for (nParameter = 0, nParameters = (INT)m_pParameters.GetSize(); nParameter < nParameters; nParameter++)
		{
			if ((pParameter = m_pParameters.GetAt(nParameter)) != (CDatabaseTCParameter *)NULL)
			{
				for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
				{
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TAG); )
					{
						szItem = pParameter->GetTag();
						break;
					}
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_DESCRIPTION); )
					{
						szItem = pParameter->GetDescription();
						break;
					}
					if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TYPE))
					{
						szItem = ((pParameter->GetAttributes() & (TCPARAMETER_CALIBRATION_NUMERICAL | TCPARAMETER_CALIBRATION_STATUS)) == 0) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUETYPE_RAW) : EMPTYSTRING;
						szItem = (pParameter->GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUETYPE_NUMERICAL) : szItem;
						szItem = (pParameter->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUETYPE_STATUS) : szItem;
					}
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_BITOFFSET); )
					{
						szItem = EMPTYSTRING;
						break;
					}
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_BITLENGTH); )
					{
						szItem = cStringTools.ConvertIntToString(pParameter->GetWidth());
						break;
					}
					if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_CODING))
					{
						szItem = (pParameter->GetAttributes() & TCPARAMETER_CODING_BITPATTERN) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUECODING_BITPATTERN) : EMPTYSTRING;
						szItem = (pParameter->GetAttributes() & TCPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUECODING_SIGNEDINTEGER) : szItem;
						szItem = (pParameter->GetAttributes() & TCPARAMETER_CODING_UNSIGNEDINTEGER) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUECODING_UNSIGNEDINTEGER) : szItem;
						szItem = (pParameter->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUECODING_FLOATINGPOINT) : szItem;
						szItem = ((pParameter->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT)) == 0) ? ((pParameter->GetAttributes() & TCPARAMETER_RADIX_DECIMAL) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUECODING_UNSIGNEDINTEGER) : STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUECODING_BITPATTERN)) : szItem;
					}
					if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_RADIX))
					{
						szItem = (pParameter->GetAttributes() & TCPARAMETER_RADIX_BINARY) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUERADIX_BINARY) : EMPTYSTRING;
						szItem = (pParameter->GetAttributes() & TCPARAMETER_RADIX_OCTAL) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUERADIX_OCTAL) : szItem;
						szItem = (pParameter->GetAttributes() & TCPARAMETER_RADIX_DECIMAL) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUERADIX_DECIMAL) : szItem;
						szItem = (pParameter->GetAttributes() & TCPARAMETER_RADIX_HEXADECIMAL) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUERADIX_HEXADECIMAL) : szItem;
					}
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_FLAG); )
					{
						szItem = STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUEFLAG_VARIABLE);
						break;
					}
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_VALUE); )
					{
						szItem = pParameter->GetConstValueAsText();
						break;
					}
					for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_LIMITCHECK); )
					{
						if (GetTCService()->CheckTCParameterOolStatus(pParameter, nOolStatus))
						{
							if (nOolStatus == TCPARAMETER_STATUS_NOLIMIT)
							{
								szItem = STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_NOLIMIT);
								break;
							}
							if (nOolStatus == TCPARAMETER_STATUS_SOFTLIMIT)
							{
								szItem = STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_SOFTLIMIT);
								break;
							}
							if (nOolStatus == TCPARAMETER_STATUS_HARDLIMIT)
							{
								szItem = STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_HARDLIMIT);
								break;
							}
							if (nOolStatus == TCPARAMETER_STATUS_DELTALIMIT)
							{
								szItem = STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_DELTALIMIT);
								break;
							}
							if (nOolStatus == TCPARAMETER_STATUS_VALUELIMIT)
							{
								szItem = STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_VALUELIMIT);
								break;
							}
							szItem = (!pParameter->GetConstValueAsText().IsEmpty()) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_NONE) : ((pParameter->GetAttributes() & TCPARAMETER_CODING_TIME) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_NOTIME) : EMPTYSTRING);
							break;
						}
						szItem = STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_FAILURE);
						break;
					}
					if (!nColumn)
					{
						Listview_InsertText(GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST), nParameter, szItem);
						continue;
					}
					Listview_SetText(GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST), nParameter, nColumn, szItem);
				}
			}
		}
		break;
	}
	if (!IsDlgButtonChecked(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SHOWFORMALLIST))
	{
		if ((pItem = m_pItems.GetAt((INT)SendDlgItemMessage(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY, CB_GETCURSEL))))
		{
			for (nParameter = 0, nParameters = (pItem->GetTCPacket(&cPacket)) ? (INT)cPacket.GetSize() : -1, nCount = 0; nParameter < nParameters; nParameter++)
			{
				if ((pPacketParameter = cPacket.GetAt(nParameter)) != (CDatabaseTCPacketParameter *)NULL)
				{
					for (nColumn = 0, nColumns = ((pPacketParameter->GetAttributes() & TCPARAMETER_TYPE_CONSTANT) != TCPARAMETER_TYPE_CONSTANT || IsDlgButtonChecked(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SHOWALL)) ? (INT)m_szColumns.GetSize() : 0; nColumn < nColumns; nColumn++)
					{
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TAG); )
						{
							szItem = pPacketParameter->GetTag();
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_DESCRIPTION); )
						{
							szItem = pPacketParameter->GetDescription();
							break;
						}
						if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TYPE))
						{
							szItem = ((pPacketParameter->GetAttributes() & TCPARAMETER_CALIBRATION_NONE) || (pPacketParameter->GetAttributes() & TCPARAMETER_CALIBRATION_DISABLED)) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUETYPE_RAW) : EMPTYSTRING;
							szItem = ((pPacketParameter->GetAttributes() & TCPARAMETER_CALIBRATION_ENABLED) && ((pParameter = GetDatabase()->GetTCParameters()->GetAt(GetDatabase()->GetTCParameters()->Find(pPacketParameter->GetTag())))) && (pParameter->GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL)) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUETYPE_NUMERICAL) : szItem;
							szItem = ((pPacketParameter->GetAttributes() & TCPARAMETER_CALIBRATION_ENABLED) && ((pParameter = GetDatabase()->GetTCParameters()->GetAt(GetDatabase()->GetTCParameters()->Find(pPacketParameter->GetTag())))) && (pParameter->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS)) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUETYPE_STATUS) : szItem;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_BITOFFSET); )
						{
							szItem = cStringTools.ConvertIntToString(8 * pPacketParameter->GetBytePos() + pPacketParameter->GetBitPos());
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_BITLENGTH); )
						{
							szItem = cStringTools.ConvertIntToString(pPacketParameter->GetWidth());
							break;
						}
						if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_CODING))
						{
							szItem = (pPacketParameter->GetAttributes() & TCPARAMETER_CODING_BITPATTERN) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUECODING_BITPATTERN) : EMPTYSTRING;
							szItem = (pPacketParameter->GetAttributes() & TCPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUECODING_SIGNEDINTEGER) : szItem;
							szItem = (pPacketParameter->GetAttributes() & TCPARAMETER_CODING_UNSIGNEDINTEGER) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUECODING_UNSIGNEDINTEGER) : szItem;
							szItem = (pPacketParameter->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUECODING_FLOATINGPOINT) : szItem;
							szItem = (pPacketParameter->GetAttributes() & TCPARAMETER_CODING_TIME) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUECODING_DATETIME) : szItem;
							szItem = (pPacketParameter->GetAttributes() & TCPARAMETER_CODING_TEXTSTRING) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUECODING_STRING) : szItem;
							szItem = ((pPacketParameter->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME | TCPARAMETER_CODING_TEXTSTRING)) == 0) ? (((pPacketParameter->GetAttributes() & TCPARAMETER_RADIX_DECIMAL) || (pPacketParameter->GetAttributes() & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_DECIMAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUECODING_UNSIGNEDINTEGER) : STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUECODING_BITPATTERN)) : szItem;
						}
						if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_RADIX))
						{
							szItem = (pPacketParameter->GetAttributes() & TCPARAMETER_RADIX_BINARY) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUERADIX_BINARY) : EMPTYSTRING;
							szItem = (pPacketParameter->GetAttributes() & TCPARAMETER_RADIX_OCTAL) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUERADIX_OCTAL) : szItem;
							szItem = (pPacketParameter->GetAttributes() & TCPARAMETER_RADIX_DECIMAL) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUERADIX_DECIMAL) : szItem;
							szItem = (pPacketParameter->GetAttributes() & TCPARAMETER_RADIX_HEXADECIMAL) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUERADIX_HEXADECIMAL) : szItem;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_FLAG); )
						{
							szItem = ((pPacketParameter->GetAttributes() & (TCPARAMETER_TYPE_CONSTANT | TCPARAMETER_VTYPE_AUTO)) == TCPARAMETER_TYPE_CONSTANT) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUEFLAG_FIXED) : (((pPacketParameter->GetAttributes() & TCPARAMETER_VTYPE_AUTO) != TCPARAMETER_VTYPE_AUTO) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUEFLAG_VARIABLE) : STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUEFLAG_AUTOMATIC));
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_VALUE); )
						{
							szItem = pPacketParameter->GetConstValueAsText();
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_LIMITCHECK); )
						{
							if (GetTCService()->CheckTCPacketParameterOolStatus(pPacketParameter, nOolStatus))
							{
								if (nOolStatus == TCPARAMETER_STATUS_NOLIMIT)
								{
									szItem = STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_NOLIMIT);
									break;
								}
								if (nOolStatus == TCPARAMETER_STATUS_SOFTLIMIT)
								{
									szItem = STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_SOFTLIMIT);
									break;
								}
								if (nOolStatus == TCPARAMETER_STATUS_HARDLIMIT)
								{
									szItem = STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_HARDLIMIT);
									break;
								}
								if (nOolStatus == TCPARAMETER_STATUS_DELTALIMIT)
								{
									szItem = STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_DELTALIMIT);
									break;
								}
								if (nOolStatus == TCPARAMETER_STATUS_VALUELIMIT)
								{
									szItem = STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_VALUELIMIT);
									break;
								}
								szItem = (!pPacketParameter->GetConstValueAsText().IsEmpty()) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_NONE) : ((pPacketParameter->GetAttributes() & TCPARAMETER_CODING_TIME) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_NOTIME) : EMPTYSTRING);
								break;
							}
							szItem = STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_FAILURE);
							break;
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST), nCount, szItem);
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST), nCount, nColumn, szItem);
						nCount = (nColumn == nColumns - 1) ? (nCount + 1) : nCount;
					}
				}
			}
			for (nBlockItem = -1, nBlockItems = pItem->GetReleaseBlockedItems(pBlockedItems); nBlockItem < nBlockItems; nBlockItem++)
			{
				for (nElement = 0, nElements = ((pFunction = pBlockedItems.GetAt(nBlockItem))) ? (INT)pFunction->GetSize() : (INT)pItem->GetSize(); nElement < nElements; nElement++)
				{
					if ((pFunctionElement = (nBlockItem >= 0) ? pFunction->GetAt(nElement) : pItem->GetAt(nElement)) != (CDatabaseTCFunctionElement *)NULL)
					{
						for (nItem = 0, nItems = (INT)SendDlgItemMessage(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST, LVM_GETITEMCOUNT); nItem < nItems; nItem++)
						{
							if (_ttoi(Listview_GetText(GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST), nItem, FindColumnIndex(STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_BITOFFSET)))) > 8 * pFunctionElement->GetBytePos() + pFunctionElement->GetBitPos()) break;
							continue;
						}
						for (nColumn = 0, nColumns = ((pFunctionElement->GetAttributes() & TCPARAMETER_TYPE_CONSTANT) != TCPARAMETER_TYPE_CONSTANT || IsDlgButtonChecked(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SHOWALL)) ? (INT)m_szColumns.GetSize() : 0; nColumn < nColumns; nColumn++)
						{
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TAG); )
							{
								szItem = pFunctionElement->GetName();
								break;
							}
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_DESCRIPTION); )
							{
								szItem = pFunctionElement->GetDescription();
								break;
							}
							if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TYPE))
							{
								szItem = ((pFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_NONE) || (pFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_DISABLED)) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUETYPE_RAW) : EMPTYSTRING;
								szItem = ((pFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_ENABLED) && ((pParameter = GetDatabase()->GetTCParameters()->GetAt(GetDatabase()->GetTCParameters()->Find(pFunctionElement->GetName())))) && (pParameter->GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL)) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUETYPE_NUMERICAL) : szItem;
								szItem = ((pFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_ENABLED) && ((pParameter = GetDatabase()->GetTCParameters()->GetAt(GetDatabase()->GetTCParameters()->Find(pFunctionElement->GetName())))) && (pParameter->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS)) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUETYPE_STATUS) : szItem;
							}
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_BITOFFSET); )
							{
								szItem = cStringTools.ConvertIntToString(8 * pFunctionElement->GetBytePos() + pFunctionElement->GetBitPos());
								break;
							}
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_BITLENGTH); )
							{
								szItem = cStringTools.ConvertIntToString(pFunctionElement->GetWidth());
								break;
							}
							if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_CODING))
							{
								szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_CODING_BITPATTERN) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUECODING_BITPATTERN) : EMPTYSTRING;
								szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUECODING_SIGNEDINTEGER) : szItem;
								szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_CODING_UNSIGNEDINTEGER) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUECODING_UNSIGNEDINTEGER) : szItem;
								szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUECODING_FLOATINGPOINT) : szItem;
								szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_CODING_TIME) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUECODING_DATETIME) : szItem;
								szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_CODING_TEXTSTRING) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUECODING_STRING) : szItem;
								szItem = ((pFunctionElement->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME | TCPARAMETER_CODING_TEXTSTRING)) == 0) ? (((pFunctionElement->GetAttributes() & TCPARAMETER_RADIX_DECIMAL) || (pFunctionElement->GetAttributes() & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_DECIMAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUECODING_UNSIGNEDINTEGER) : STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUECODING_BITPATTERN)) : szItem;
							}
							if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_RADIX))
							{
								szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_RADIX_BINARY) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUERADIX_BINARY) : EMPTYSTRING;
								szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_RADIX_OCTAL) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUERADIX_OCTAL) : szItem;
								szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_RADIX_DECIMAL) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUERADIX_DECIMAL) : szItem;
								szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_RADIX_HEXADECIMAL) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUERADIX_HEXADECIMAL) : szItem;
							}
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_FLAG); )
							{
								szItem = ((pFunctionElement->GetAttributes() & (TCPARAMETER_TYPE_CONSTANT | TCPARAMETER_VTYPE_AUTO)) == TCPARAMETER_TYPE_CONSTANT) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUEFLAG_FIXED) : (((pFunctionElement->GetAttributes() & TCPARAMETER_VTYPE_AUTO) != TCPARAMETER_VTYPE_AUTO) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUEFLAG_VARIABLE) : STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUEFLAG_AUTOMATIC));
								break;
							}
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_VALUE); )
							{
								szItem = pFunctionElement->GetConstValueAsText();
								break;
							}
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_LIMITCHECK); )
							{
								if (GetTCService()->CheckTCFunctionElementOolStatus(pFunctionElement, nOolStatus))
								{
									if (nOolStatus == TCPARAMETER_STATUS_NOLIMIT)
									{
										szItem = STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_NOLIMIT);
										break;
									}
									if (nOolStatus == TCPARAMETER_STATUS_SOFTLIMIT)
									{
										szItem = STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_SOFTLIMIT);
										break;
									}
									if (nOolStatus == TCPARAMETER_STATUS_HARDLIMIT)
									{
										szItem = STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_HARDLIMIT);
										break;
									}
									if (nOolStatus == TCPARAMETER_STATUS_DELTALIMIT)
									{
										szItem = STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_DELTALIMIT);
										break;
									}
									if (nOolStatus == TCPARAMETER_STATUS_VALUELIMIT)
									{
										szItem = STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_VALUELIMIT);
										break;
									}
									szItem = (!pFunctionElement->GetConstValueAsText().IsEmpty()) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_NONE) : ((pFunctionElement->GetAttributes() & TCPARAMETER_CODING_TIME) ? STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_NOTIME) : EMPTYSTRING);
									break;
								}
								szItem = STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_LIMITCHECK_FAILURE);
								break;
							}
							if (!nColumn)
							{
								Listview_InsertText(GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST), nItem, szItem);
								continue;
							}
							Listview_SetText(GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST), nItem, nColumn, szItem);
						}
					}
				}
			}
		}
	}
	for (GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS)->EnableWindow((nParameters > 0 || nElements > 0) ? TRUE : FALSE), GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SHOWALL)->EnableWindow((nParameters > 0 || nElements > 0) ? TRUE : FALSE); SendDlgItemMessage(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST, LVM_GETITEMCOUNT) > 0; )
	{
		Listview_SetCurText(GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST), 0);
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST)->EnableWindow();
		return;
	}
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_REMARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_REMARK)->EnableWindow(FALSE);
}

VOID CTCHistoryComposedItemPropertiesDialog::ShowRawData()
{
	INT  nByte;
	INT  nBytes;
	CString  szRawData[2];
	CByteArray  nRawData[2];
	CStringTools  cStringTools;
	CDatabaseTCPacket  cPacket;
	CTCHistoryItem  *pItem;
	CTCPacket  cTCPacket;

	if ((pItem = m_pItems.GetAt((INT)SendDlgItemMessage(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY, CB_GETCURSEL))) && pItem->GetType() == TCHISTORYITEM_TYPE_FUNCTION)
	{
		for (pItem->GetTCPacket(&cPacket), szRawData[0].Format(STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_RAWDATA_FORMAT), (LPCTSTR)cPacket.GetDescription(), (LPCTSTR)cPacket.GetTag()), szRawData[1].Format(STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_RAWDATA_SIMPLEFORMAT), (LPCTSTR)cPacket.GetTag()); !cPacket.GetTag().IsEmpty() || !cPacket.GetDescription().IsEmpty(); )
		{
			GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_RAWDATA)->SetWindowText((!cPacket.GetDescription().IsEmpty()) ? szRawData[0] : szRawData[1]);
			break;
		}
		for (nByte = 0, nBytes = (pItem->GetTCPacket(nRawData[0]) > 0 && cTCPacket.Unmap(nRawData[0])) ? cTCPacket.GetData(nRawData[1]) : 0, szRawData[0].Empty(); nByte < nBytes; nByte++)
		{
			szRawData[0] += (nByte > 0 && nByte % 2 == 0) ? CString(SPACE) : CString(EMPTYSTRING);
			szRawData[0] += cStringTools.ConvertIntToPaddedString(nRawData[1].GetAt(nByte), 2, 16);
		}
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_RAWDATA_AREA)->SetWindowText((szRawData[0].IsEmpty()) ? m_szRawData[1] : szRawData[0]);
		return;
	}
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_RAWDATA)->SetWindowText(m_szRawData[0]);
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_RAWDATA_AREA)->SetWindowText(m_szRawData[1]);
}

INT CTCHistoryComposedItemPropertiesDialog::FindColumnIndex(LPCTSTR pszColumn) CONST
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

void CTCHistoryComposedItemPropertiesDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistoryComposedItemPropertiesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCHistoryComposedItemPropertiesDialog::PostNcDestroy()
{
	m_pItems.RemoveAll();
	m_szColumns.RemoveAll();
	m_pParameters.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCHistoryComposedItemPropertiesDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistoryComposedItemPropertiesDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SHOWALL, OnShowAllParameters)
	ON_BN_CLICKED(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SHOWFORMALLIST, OnShowFormalParameters)
	ON_CBN_SELCHANGE(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY, OnSelchangeEntry)
	ON_BN_CLICKED(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryComposedItemPropertiesDialog message handlers

BOOL CTCHistoryComposedItemPropertiesDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CFont  cFont;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_NAME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_DESCRIPTION)->EnableWindow();
	m_szColumns.Add(STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TAG));
	m_szColumns.Add(STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_DESCRIPTION));
	m_szColumns.Add(STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TYPE));
	m_szColumns.Add(STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_BITOFFSET));
	m_szColumns.Add(STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_BITLENGTH));
	m_szColumns.Add(STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_CODING));
	m_szColumns.Add(STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_RADIX));
	m_szColumns.Add(STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_FLAG));
	m_szColumns.Add(STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_VALUE));
	m_szColumns.Add(STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_LIMITCHECK));
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST)->GetClientRect(rColumns);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TAG)) ? (rColumns.Width() / 5) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_DESCRIPTION)) ? (2 * rColumns.Width() / 5) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TYPE) || m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_FLAG)) ? (rColumns.Width() / 7) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_BITOFFSET) || m_szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_BITLENGTH)) ? (rColumns.Width() / 9) : (9 * rColumns.Width() / 35)))));
		continue;
	}
	for (GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_RAWDATA)->GetWindowText(m_szRawData[0]), GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_RAWDATA_AREA)->GetWindowText(m_szRawData[1]), EnumEntries(); cFont.CreateStockObject(ANSI_FIXED_FONT); )
	{
		GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_RAWDATA_AREA)->SetFont(&cFont);
		break;
	}
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_NAME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PROPERTIES)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_RAWDATA)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_RAWDATA_AREA)->EnableWindow();
	AccessControl(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDEPTV, FALSE);
	AccessControl(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDEPEV, FALSE);
	AccessControl(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDECEV, FALSE);
	AccessControl(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLEPTV, FALSE);
	AccessControl(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLEPEV, FALSE);
	AccessControl(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLECEV, FALSE);
	AccessControl(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_PREAUTHORIZED, FALSE);
	AccessControl(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_IMMEDIATELY, FALSE);
	AccessControl(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_TIMETAG, FALSE);
	AccessControl(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_TIMETAG_TIME, FALSE);
	AccessControl(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_FIRSTSTEP, FALSE);
	AccessControl(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_SECONDSTEP, FALSE);
	ShowProperties();
	return TRUE;
}

BOOL CTCHistoryComposedItemPropertiesDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CTCHistoryItemPropertiesParametersDialog  cParametersDialog;
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED))
		{
			GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_REMARK)->ShowWindow((Listview_GetText(GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST), pNotifyListView->iItem, FindColumnIndex(STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TYPE))) != STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUETYPE_RAW) && !IsDlgButtonChecked(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SHOWFORMALLIST)) ? SW_SHOW : SW_HIDE);
			GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_REMARK)->EnableWindow((Listview_GetText(GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST), pNotifyListView->iItem, FindColumnIndex(STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TYPE))) != STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERVALUETYPE_RAW) && !IsDlgButtonChecked(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SHOWFORMALLIST)) ? TRUE : FALSE);
			GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST)->SetFocus();
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK  &&  Listview_GetText(GetDlgItem(IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_LIST), pNotifyListView->iItem, FindColumnIndex(STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TYPE))) != STRING(IDS_TCHISTORYITEMPROPERTIESDIALOG_PARAMETERVALUETYPE_RAW) && !IsDlgButtonChecked(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SHOWFORMALLIST)) cParametersDialog.Create(this, Listview_GetText(GetDlgItem(IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST), pNotifyListView->iItem, FindColumnIndex(STRING(IDS_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_PARAMETERSTITLEITEM_TAG))));
	}
	return CDisplayDialog::OnNotify(wParam, lParam, pResult);
}

void CTCHistoryComposedItemPropertiesDialog::OnSelchangeEntry()
{
	ShowProperties();
}

void CTCHistoryComposedItemPropertiesDialog::OnShowAllParameters()
{
	CHourglassCursor  cCursor;

	ShowParameters();
}

void CTCHistoryComposedItemPropertiesDialog::OnShowFormalParameters()
{
	CHourglassCursor  cCursor;

	ShowParameters();
}

void CTCHistoryComposedItemPropertiesDialog::OnOK()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnOK();
}

BOOL CTCHistoryComposedItemPropertiesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistoryComposedItemPropertiesDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYCOMPOSEDITEMPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistoryRetrieveDialog dialog

IMPLEMENT_DYNCREATE(CTCHistoryRetrieveDialog, CDisplayDialog)

CTCHistoryRetrieveDialog::CTCHistoryRetrieveDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistoryRetrieveDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCHistoryRetrieveDialog::Create(CWnd *pParentWnd)
{
	CString  szTitle;
	CTCHistoryWnd  *pTCHistoryWnd;

	return Create(pParentWnd, ((pTCHistoryWnd = (CTCHistoryWnd *)pParentWnd) && pTCHistoryWnd->GetLayout(szTitle)) ? szTitle : STRING(IDS_WINDOW_UNKNOWNTITLE));
}
INT CTCHistoryRetrieveDialog::Create(CWnd *pParentWnd, LPCTSTR pszTitle)
{
	m_szTitle = pszTitle;
	return CDisplayDialog::Create(pParentWnd, CTCHistoryRetrieveDialog::IDD);
}

BOOL CTCHistoryRetrieveDialog::GetMode(UINT &nMode) CONST
{
	GetRetrieveInfo(nMode);
	nMode &= TCHISTORY_RETRIEVE_BYRELEASETIME | TCHISTORY_RETRIEVE_BYEXECUTIONTIME;
	nMode |= (IsDlgButtonChecked(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYTIME) || IsDlgButtonChecked(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYEND)) ? ((!IsDlgButtonChecked(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYTIME)) ? TCHISTORY_RETRIEVE_STOPBYEND : TCHISTORY_RETRIEVE_STOPBYTIME) : 0;
	nMode |= (IsDlgButtonChecked(IDC_TCHISTORY_RETRIEVE_HISTORY_AUTOMATIC)) ? TCHISTORY_RETRIEVE_AUTOFORWARD : ((IsDlgButtonChecked(IDC_TCHISTORY_RETRIEVE_HISTORY_PSEUDOREALTIME)) ? TCHISTORY_RETRIEVE_PSEUDOREALTIME : TCHISTORY_RETRIEVE_MANUALFORWARD);
	return TRUE;
}

BOOL CTCHistoryRetrieveDialog::GetSpeed(UINT &nSpeed) CONST
{
	nSpeed = (!IsDlgButtonChecked(IDC_TCHISTORY_RETRIEVE_HISTORY_AUTOMATIC)) ? (UINT)((GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_SPEED)->SendMessage(TBM_GETRANGEMIN) + GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_SPEED)->SendMessage(TBM_GETRANGEMAX)) / 2) : (UINT)GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_SPEED)->SendMessage(TBM_GETPOS);
	return((IsDlgButtonChecked(IDC_TCHISTORY_RETRIEVE_HISTORY_AUTOMATIC)) ? TRUE : FALSE);
}

BOOL CTCHistoryRetrieveDialog::GetStartTime(CTimeKey &tTimeKey) CONST
{
	CTimeKey  tTime;

	for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STARTTIME)), tTimeKey = 0; tTime > 0; )
	{
		tTimeKey = tTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryRetrieveDialog::GetStopTime(CTimeKey &tTimeKey) CONST
{
	CTimeKey  tTime;

	for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPTIME)), tTimeKey = 0; IsDlgButtonChecked(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYTIME) && tTime > 0; )
	{
		tTimeKey = tTime;
		return TRUE;
	}
	return FALSE;
}

CTCHistoryOpenDialog *CTCHistoryRetrieveDialog::GetParentDialog() CONST
{
	return((GetParent() != (CWnd *)GetParentDisplay()) ? (CTCHistoryOpenDialog *)GetParent() : (CTCHistoryOpenDialog *)NULL);
}

CTCHistoryWnd *CTCHistoryRetrieveDialog::GetParentDisplay() CONST
{
	return((CTCHistoryWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CTCHistoryRetrieveDialog::SetRetrieveInfo()
{
	UINT  nMode;
	UINT  nSpeed;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;

	if (GetRetrieveInfo(nMode, nSpeed, tStartTime, tStopTime))
	{
		Timespinbox_SetTime(GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STARTTIME), (tStartTime > 0 || GetTMService()->GetRecentTMHistoryTimeKey(tStartTime)) ? tStartTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPTIME), (tStopTime.GetTime() > 0) ? tStopTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetRange(GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPTIME), Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STARTTIME)), MAX_TIMEKEY);
		SendDlgItemMessage(IDC_TCHISTORY_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, (nMode & ~(TCHISTORY_RETRIEVE_BYRELEASETIME | TCHISTORY_RETRIEVE_BYEXECUTIONTIME)) ? ((nMode & TCHISTORY_RETRIEVE_AUTOFORWARD) ? nSpeed : 0) : ((SendDlgItemMessage(IDC_TCHISTORY_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMIN) + SendDlgItemMessage(IDC_TCHISTORY_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMAX)) / 2));
		CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYTIME, ((nMode & TCHISTORY_RETRIEVE_STOPBYTIME) && (nMode & TCHISTORY_RETRIEVE_MANUALFORWARD) == 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYEND, (((nMode & ~(TCHISTORY_RETRIEVE_BYRELEASETIME | TCHISTORY_RETRIEVE_BYEXECUTIONTIME)) == 0 || (nMode & TCHISTORY_RETRIEVE_STOPBYEND)) && (nMode & TCHISTORY_RETRIEVE_MANUALFORWARD) == 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_AUTOMATIC, ((nMode & TCHISTORY_RETRIEVE_AUTOFORWARD) || (nMode & ~(TCHISTORY_RETRIEVE_BYRELEASETIME | TCHISTORY_RETRIEVE_BYEXECUTIONTIME)) == 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_MANUAL, (nMode & TCHISTORY_RETRIEVE_MANUALFORWARD) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_PSEUDOREALTIME, (nMode & TCHISTORY_RETRIEVE_PSEUDOREALTIME) ? TRUE : FALSE);
		GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY)->EnableWindow();
		GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_START_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STARTTIME)->EnableWindow();
		GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_TCHISTORY_RETRIEVE_HISTORY_MANUAL));
		GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow(!IsDlgButtonChecked(IDC_TCHISTORY_RETRIEVE_HISTORY_MANUAL));
		GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYTIME));
		GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow(!IsDlgButtonChecked(IDC_TCHISTORY_RETRIEVE_HISTORY_MANUAL));
		GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_PLAYBACKMODE)->EnableWindow();
		GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_AUTOMATIC)->EnableWindow();
		GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_PSEUDOREALTIME)->EnableWindow();
		GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_MANUAL)->EnableWindow();
		GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORY_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_SPEED)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORY_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_SLOW)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORY_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_FAST)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORY_RETRIEVE_HISTORY_AUTOMATIC));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryRetrieveDialog::GetRetrieveInfo(UINT &nMode) CONST
{
	UINT  nSpeed;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;

	return GetRetrieveInfo(nMode, nSpeed, tStartTime, tStopTime);
}
BOOL CTCHistoryRetrieveDialog::GetRetrieveInfo(UINT &nMode, UINT &nSpeed, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	CTCHistoryWnd  *pTCHistoryWnd;
	CTCHistoryOpenDialog  *pDialog;

	if ((pDialog = GetParentDialog()))
	{
		for (pDialog->GetRetrieveMode(nMode), nSpeed = 0, tStartTime = tStopTime = 0; nMode; )
		{
			pDialog->GetRetrieveSpeed(nSpeed);
			pDialog->GetRetrieveStartTime(tStartTime);
			pDialog->GetRetrieveStopTime(tStopTime);
			break;
		}
		return TRUE;
	}
	if ((pTCHistoryWnd = GetParentDisplay()))
	{
		for (pTCHistoryWnd->GetRetrieveMode(nMode), nSpeed = 0, tStartTime = tStopTime = 0; nMode; )
		{
			pTCHistoryWnd->GetRetrieveSpeed(nSpeed);
			pTCHistoryWnd->GetRetrieveStartTime(tStartTime);
			pTCHistoryWnd->GetRetrieveStopTime(tStopTime);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

void CTCHistoryRetrieveDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistoryRetrieveDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistoryRetrieveDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistoryRetrieveDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYTIME, OnRetrieveByTime)
	ON_BN_CLICKED(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYEND, OnRetrieveByEnd)
	ON_BN_CLICKED(IDC_TCHISTORY_RETRIEVE_HISTORY_AUTOMATIC, OnRetrieveAutomatic)
	ON_BN_CLICKED(IDC_TCHISTORY_RETRIEVE_HISTORY_PSEUDOREALTIME, OnRetrievePseudoRealtime)
	ON_BN_CLICKED(IDC_TCHISTORY_RETRIEVE_HISTORY_MANUAL, OnRetrieveManual)
	ON_BN_CLICKED(IDC_TCHISTORY_RETRIEVE_HELP, OnHelp)
	ON_CONTROL(TSBXN_CHANGE, IDC_TCHISTORY_RETRIEVE_HISTORY_STARTTIME, OnSpinchangeRetrieveStartTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryRetrieveDialog message handlers

BOOL CTCHistoryRetrieveDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	for (CDisplayDialog::OnInitDialog(), SendDlgItemMessage(IDC_TCHISTORY_RETRIEVE_HISTORY_SPEED, TBM_SETRANGE, TRUE, MAKELPARAM(0, 10)), GetDlgItem(IDC_TCHISTORY_RETRIEVE_TITLE)->SetWindowText(m_szTitle); SetRetrieveInfo(); )
	{
		GetDlgItem(IDC_TCHISTORY_RETRIEVE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_TCHISTORY_RETRIEVE_TITLE_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCHISTORY_RETRIEVE_TITLE)->EnableWindow();
		GetDlgItem(IDC_TCHISTORY_RETRIEVE_TYPE_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCHISTORY_RETRIEVE_TYPE)->EnableWindow();
		GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STARTTIME)->SetFocus();
		GetDlgItem(IDOK)->EnableWindow();
		return FALSE;
	}
	return TRUE;
}

void CTCHistoryRetrieveDialog::OnRetrieveByTime()
{
	CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYTIME, TRUE);
	CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPTIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPTIME)->SetFocus();
}

void CTCHistoryRetrieveDialog::OnRetrieveByEnd()
{
	CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYEND, TRUE);
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(FALSE);
}

void CTCHistoryRetrieveDialog::OnRetrieveAutomatic()
{
	SendDlgItemMessage(IDC_TCHISTORY_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, (SendDlgItemMessage(IDC_TCHISTORY_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMIN) + SendDlgItemMessage(IDC_TCHISTORY_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMAX)) / 2);
	CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYEND, TRUE);
	CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_AUTOMATIC, TRUE);
	CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_PSEUDOREALTIME, FALSE);
	CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_MANUAL, FALSE);
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYTIME));
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_SPEED)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_SLOW)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_FAST)->EnableWindow();
}

void CTCHistoryRetrieveDialog::OnRetrievePseudoRealtime()
{
	SendDlgItemMessage(IDC_TCHISTORY_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, 0);
	CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYEND, TRUE);
	CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_AUTOMATIC, FALSE);
	CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_PSEUDOREALTIME, TRUE);
	CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_MANUAL, FALSE);
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYTIME));
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_SPEED)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_SLOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_FAST)->EnableWindow(FALSE);
}

void CTCHistoryRetrieveDialog::OnRetrieveManual()
{
	SendDlgItemMessage(IDC_TCHISTORY_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, 0);
	CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_AUTOMATIC, FALSE);
	CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_PSEUDOREALTIME, FALSE);
	CheckDlgButton(IDC_TCHISTORY_RETRIEVE_HISTORY_MANUAL, TRUE);
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_SPEED)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_SLOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_FAST)->EnableWindow(FALSE);
}

void CTCHistoryRetrieveDialog::OnSpinchangeRetrieveStartTime()
{
	Timespinbox_SetRange(GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STOPTIME), Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORY_RETRIEVE_HISTORY_STARTTIME)), MAX_TIMEKEY);
}

void CTCHistoryRetrieveDialog::OnOK()
{
	CString  szLayout;
	CTCHistoryWnd  *pTCHistoryWnd;
	CTCHistoryOpenDialog  *pDialog;
	CHourglassCursor  cCursor;

	for (; !GetParentDialog(); )
	{
		if (!IsDlgButtonChecked(IDC_TCHISTORY_RETRIEVE_HISTORY_AUTOMATIC) && !IsDlgButtonChecked(IDC_TCHISTORY_RETRIEVE_HISTORY_PSEUDOREALTIME) && !IsDlgButtonChecked(IDC_TCHISTORY_RETRIEVE_HISTORY_MANUAL))
		{
			if ((pTCHistoryWnd = (GetParentDisplay()->GetLayout(szLayout)) ? GetParentDisplay()->Find(GetParentDisplay()->GetType(), DISPLAY_MODE_REALTIME, szLayout) : (CTCHistoryWnd *)NULL))
			{
				for (GetDisplayArea()->ActivateDisplay(pTCHistoryWnd); pTCHistoryWnd != GetParentDisplay(); )
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
	CDisplayDialog::OnOK();
}

void CTCHistoryRetrieveDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	if (!GetParentDialog()) GetParentDisplay()->OnCloseRetrieveDialog(IDCANCEL);
	else  GetParentDialog()->OnCloseRetrieveDialog(IDCANCEL);
	CDisplayDialog::OnCancel();
}

BOOL CTCHistoryRetrieveDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYRETRIEVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistoryRetrieveDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYRETRIEVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchNumberDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchNumberDialog, CDisplayDialog)

CTCHistorySearchNumberDialog::CTCHistorySearchNumberDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchNumberDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchNumberDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchNumberDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchNumberDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

void CTCHistorySearchNumberDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchNumberDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchNumberDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchNumberDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHNUMBER_GOTO, OnGotoNumber)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHNUMBER_CLOSE, OnClose)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHNUMBER_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchNumberDialog message handlers

BOOL CTCHistorySearchNumberDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	Spinbox_SetRange(GetDlgItem(IDC_TCHISTORY_SEARCHNUMBER_NUMBER), 1, INT_MAX);
	GetDlgItem(IDC_TCHISTORY_SEARCHNUMBER_NUMBER_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHNUMBER_NUMBER)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHNUMBER_GOTO)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHNUMBER_COMMENT_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHNUMBER_COMMENT)->EnableWindow();
	return TRUE;
}

void CTCHistorySearchNumberDialog::OnGotoNumber()
{
	CHourglassCursor  cCursor;

	if (!GetParent()->SearchTelecommandByNumber((INT)Spinbox_GetPos(GetDlgItem(IDC_TCHISTORY_SEARCHNUMBER_NUMBER))))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_NUMBER_NOTHING);
		return;
	}
}

void CTCHistorySearchNumberDialog::OnClose()
{
	CHourglassCursor  cCursor;

	EndDialog(IDOK);
}

void CTCHistorySearchNumberDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchNumberDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchNumberDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchNameDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchNameDialog, CDisplayDialog)

CTCHistorySearchNameDialog::CTCHistorySearchNameDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchNameDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchNameDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchNameDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchNameDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

void CTCHistorySearchNameDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchNameDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchNameDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchNameDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHNAME_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHNAME_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_TCHISTORY_SEARCHNAME_NAME, OnSelchangeName)
	ON_CBN_EDITCHANGE(IDC_TCHISTORY_SEARCHNAME_NAME, OnEditchangeName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchNameDialog message handlers

BOOL CTCHistorySearchNameDialog::OnInitDialog()
{
	INT  nItem;
	INT  nItems;
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	for (nItem = 0, nItems = (INT)m_szNames.GetSize(); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_TCHISTORY_SEARCHNAME_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szNames.GetAt(nItem));
		continue;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHNAME_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHNAME_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_TCHISTORY_SEARCHNAME_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHNAME_NAME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHNAME_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHNAME_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHNAME_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHNAME_ALL)->EnableWindow();
	return TRUE;
}

void CTCHistorySearchNameDialog::OnFindTelecommand()
{
	CString  szName;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_TCHISTORY_SEARCHNAME_NAME)->GetWindowText(szName);
	if (SendDlgItemMessage(IDC_TCHISTORY_SEARCHNAME_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szName) == CB_ERR)
	{
		SendDlgItemMessage(IDC_TCHISTORY_SEARCHNAME_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szName);
		m_szNames.Add(szName);
	}
	if (!GetParent()->SearchTelecommandByName(szName, IsDlgButtonChecked(IDC_TCHISTORY_SEARCHNAME_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHNAME_ALL)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_NAME_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHNAME_ALL, FALSE);
}

void CTCHistorySearchNameDialog::OnSelchangeName()
{
	GetDlgItem(IDC_TCHISTORY_SEARCHNAME_FIND)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_SEARCHNAME_NAME, CB_GETCURSEL) != CB_ERR) ? TRUE : FALSE);
}

void CTCHistorySearchNameDialog::OnEditchangeName()
{
	GetDlgItem(IDC_TCHISTORY_SEARCHNAME_FIND)->EnableWindow((GetDlgItem(IDC_TCHISTORY_SEARCHNAME_NAME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CTCHistorySearchNameDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchNameDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchNameDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchComputerDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchComputerDialog, CDisplayDialog)

CTCHistorySearchComputerDialog::CTCHistorySearchComputerDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchComputerDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchComputerDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchComputerDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchComputerDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

void CTCHistorySearchComputerDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchComputerDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchComputerDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchComputerDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHCOMPUTER_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHCOMPUTER_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_TCHISTORY_SEARCHCOMPUTER_NAME, OnSelchangeComputer)
	ON_CBN_EDITCHANGE(IDC_TCHISTORY_SEARCHCOMPUTER_NAME, OnEditchangeComputer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchComputerDialog message handlers

BOOL CTCHistorySearchComputerDialog::OnInitDialog()
{
	INT  nItem;
	INT  nItems;
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	for (nItem = 0, nItems = (INT)m_szComputers.GetSize(); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_TCHISTORY_SEARCHCOMPUTER_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szComputers.GetAt(nItem));
		continue;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHCOMPUTER_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHCOMPUTER_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_TCHISTORY_SEARCHCOMPUTER_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCOMPUTER_NAME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCOMPUTER_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCOMPUTER_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCOMPUTER_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCOMPUTER_ALL)->EnableWindow();
	return TRUE;
}

void CTCHistorySearchComputerDialog::OnFindTelecommand()
{
	CString  szComputer;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_TCHISTORY_SEARCHCOMPUTER_NAME)->GetWindowText(szComputer);
	if (SendDlgItemMessage(IDC_TCHISTORY_SEARCHCOMPUTER_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szComputer) == CB_ERR)
	{
		SendDlgItemMessage(IDC_TCHISTORY_SEARCHCOMPUTER_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szComputer);
		m_szComputers.Add(szComputer);
	}
	if (!GetParent()->SearchTelecommandByComputer(szComputer, IsDlgButtonChecked(IDC_TCHISTORY_SEARCHCOMPUTER_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHCOMPUTER_ALL)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_COMPUTER_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHCOMPUTER_ALL, FALSE);
}

void CTCHistorySearchComputerDialog::OnSelchangeComputer()
{
	GetDlgItem(IDC_TCHISTORY_SEARCHCOMPUTER_FIND)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_SEARCHCOMPUTER_NAME, CB_GETCURSEL) != CB_ERR) ? TRUE : FALSE);
}

void CTCHistorySearchComputerDialog::OnEditchangeComputer()
{
	GetDlgItem(IDC_TCHISTORY_SEARCHCOMPUTER_FIND)->EnableWindow((GetDlgItem(IDC_TCHISTORY_SEARCHCOMPUTER_NAME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CTCHistorySearchComputerDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchComputerDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchComputerDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchCommandSourceDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchCommandSourceDialog, CDisplayDialog)

CTCHistorySearchCommandSourceDialog::CTCHistorySearchCommandSourceDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchCommandSourceDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchCommandSourceDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchCommandSourceDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchCommandSourceDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

VOID CTCHistorySearchCommandSourceDialog::EnumCommandSources()
{
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHCOMMANDSOURCE_TYPE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_COMMANDSOURCE_MANUALSTACK));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHCOMMANDSOURCE_TYPE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_COMMANDSOURCE_AUTOMATICSTACK));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHCOMMANDSOURCE_TYPE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_COMMANDSOURCE_PROCEDURESMONITOR));
	GetDlgItem(IDC_TCHISTORY_SEARCHCOMPUTER_FIND)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_SEARCHCOMMANDSOURCE_TYPE, CB_SETCURSEL) >= 0) ? TRUE : FALSE);
}

void CTCHistorySearchCommandSourceDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchCommandSourceDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchCommandSourceDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchCommandSourceDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHCOMMANDSOURCE_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHCOMMANDSOURCE_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchCommandSourceDialog message handlers

BOOL CTCHistorySearchCommandSourceDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHCOMMANDSOURCE_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHCOMMANDSOURCE_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_TCHISTORY_SEARCHCOMMANDSOURCE_TYPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCOMMANDSOURCE_TYPE)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCOMMANDSOURCE_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCOMMANDSOURCE_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCOMMANDSOURCE_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCOMMANDSOURCE_ALL)->EnableWindow();
	EnumCommandSources();
	return TRUE;
}

void CTCHistorySearchCommandSourceDialog::OnFindTelecommand()
{
	CString  szCommandSource;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_TCHISTORY_SEARCHCOMMANDSOURCE_TYPE)->GetWindowText(szCommandSource);
	if (!GetParent()->SearchTelecommandByCommandSource((szCommandSource == STRING(IDS_TCHISTORYSEARCHDIALOG_COMMANDSOURCE_MANUALSTACK)) ? TCITEM_SOURCETYPE_MANUALSTACK : ((szCommandSource == STRING(IDS_TCHISTORYSEARCHDIALOG_COMMANDSOURCE_AUTOMATICSTACK)) ? TCITEM_SOURCETYPE_AUTOMATICSTACK : ((szCommandSource == STRING(IDS_TCHISTORYSEARCHDIALOG_COMMANDSOURCE_PROCEDURESMONITOR)) ? TCITEM_SOURCETYPE_PROCEDURESMONITOR : TCITEM_SOURCETYPE_NONE)), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHCOMMANDSOURCE_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHCOMMANDSOURCE_ALL)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_COMMANDSOURCE_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHCOMMANDSOURCE_ALL, FALSE);
}

void CTCHistorySearchCommandSourceDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchCommandSourceDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchCommandSourceDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchDescriptionDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchDescriptionDialog, CDisplayDialog)

CTCHistorySearchDescriptionDialog::CTCHistorySearchDescriptionDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchDescriptionDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchDescriptionDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchDescriptionDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchDescriptionDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

void CTCHistorySearchDescriptionDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchDescriptionDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchDescriptionDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchDescriptionDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHDESCRIPTION_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHDESCRIPTION_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_TCHISTORY_SEARCHDESCRIPTION_TEXT, OnSelchangeDescription)
	ON_CBN_EDITCHANGE(IDC_TCHISTORY_SEARCHDESCRIPTION_TEXT, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchDescriptionDialog message handlers

BOOL CTCHistorySearchDescriptionDialog::OnInitDialog()
{
	INT  nItem;
	INT  nItems;
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	for (nItem = 0, nItems = (INT)m_szDescriptions.GetSize(); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_TCHISTORY_SEARCHDESCRIPTION_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szDescriptions.GetAt(nItem));
		continue;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHDESCRIPTION_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHDESCRIPTION_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_TCHISTORY_SEARCHDESCRIPTION_TEXT_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHDESCRIPTION_TEXT)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHDESCRIPTION_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHDESCRIPTION_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHDESCRIPTION_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHDESCRIPTION_ALL)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHDESCRIPTION_CASE)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHDESCRIPTION_WORD)->EnableWindow();
	return TRUE;
}

void CTCHistorySearchDescriptionDialog::OnSelchangeDescription()
{
	GetDlgItem(IDC_TCHISTORY_SEARCHDESCRIPTION_FIND)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_SEARCHDESCRIPTION_TEXT, CB_GETCURSEL) != CB_ERR) ? TRUE : FALSE);
}

void CTCHistorySearchDescriptionDialog::OnEditchangeDescription()
{
	GetDlgItem(IDC_TCHISTORY_SEARCHDESCRIPTION_FIND)->EnableWindow((GetDlgItem(IDC_TCHISTORY_SEARCHDESCRIPTION_TEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CTCHistorySearchDescriptionDialog::OnFindTelecommand()
{
	CString  szDescription;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_TCHISTORY_SEARCHDESCRIPTION_TEXT)->GetWindowText(szDescription);
	if (SendDlgItemMessage(IDC_TCHISTORY_SEARCHDESCRIPTION_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDescription) == CB_ERR)
	{
		SendDlgItemMessage(IDC_TCHISTORY_SEARCHDESCRIPTION_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szDescription);
		m_szDescriptions.Add(szDescription);
	}
	if (!GetParent()->SearchTelecommandByDescription(szDescription, IsDlgButtonChecked(IDC_TCHISTORY_SEARCHDESCRIPTION_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHDESCRIPTION_ALL), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHDESCRIPTION_CASE), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHDESCRIPTION_WORD)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_DESCRIPTION_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHDESCRIPTION_ALL, FALSE);
}

void CTCHistorySearchDescriptionDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchDescriptionDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchDescriptionDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchCategoryDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchCategoryDialog, CDisplayDialog)

CTCHistorySearchCategoryDialog::CTCHistorySearchCategoryDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchCategoryDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchCategoryDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchCategoryDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchCategoryDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

VOID CTCHistorySearchCategoryDialog::EnumCategories()
{
	INT  nCategory;
	INT  nCategories;
	CStringArray  szCategories;
	CLongUIntArray  nCategoryIDs;

	for (nCategory = 0, nCategories = GetDatabase()->EnumTCFunctionHazardousFlags(szCategories, nCategoryIDs), SendDlgItemMessage(IDC_TCHISTORY_SEARCHCATEGORY_CATEGORY, CB_RESETCONTENT); nCategory < nCategories; nCategory++)
	{
		SendDlgItemMessage(IDC_TCHISTORY_SEARCHCATEGORY_CATEGORY, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szCategories.GetAt(nCategory));
		continue;
	}
	GetDlgItem(IDC_TCHISTORY_SEARCHCATEGORY_FIND)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_SEARCHCATEGORY_CATEGORY, CB_SETCURSEL) >= 0) ? TRUE : FALSE);
}

void CTCHistorySearchCategoryDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchCategoryDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchCategoryDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchCategoryDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHCATEGORY_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHCATEGORY_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchCategoryDialog message handlers

BOOL CTCHistorySearchCategoryDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHCATEGORY_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHCATEGORY_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_TCHISTORY_SEARCHCATEGORY_CATEGORY_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCATEGORY_CATEGORY)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCATEGORY_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCATEGORY_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCATEGORY_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCATEGORY_ALL)->EnableWindow();
	EnumCategories();
	return TRUE;
}

void CTCHistorySearchCategoryDialog::OnFindTelecommand()
{
	CString  szCategory;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_TCHISTORY_SEARCHCATEGORY_CATEGORY)->GetWindowText(szCategory);
	if (!GetParent()->SearchTelecommandByCategory(szCategory, IsDlgButtonChecked(IDC_TCHISTORY_SEARCHCATEGORY_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHCATEGORY_ALL)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_CATEGORY_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHCATEGORY_ALL, FALSE);
}

void CTCHistorySearchCategoryDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchCategoryDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchCategoryDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchSubSystemDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchSubSystemDialog, CDisplayDialog)

CTCHistorySearchSubSystemDialog::CTCHistorySearchSubSystemDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchSubSystemDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchSubSystemDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchSubSystemDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchSubSystemDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

void CTCHistorySearchSubSystemDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchSubSystemDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchSubSystemDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchSubSystemDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHSUBSYSTEM_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHSUBSYSTEM_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_TCHISTORY_SEARCHSUBSYSTEM_NAME, OnSelchangeSubSystem)
	ON_CBN_EDITCHANGE(IDC_TCHISTORY_SEARCHSUBSYSTEM_NAME, OnEditchangeSubSystem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchSubSystemDialog message handlers

BOOL CTCHistorySearchSubSystemDialog::OnInitDialog()
{
	INT  nItem;
	INT  nItems;
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	for (nItem = 0, nItems = (INT)m_szSubSystems.GetSize(); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_TCHISTORY_SEARCHSUBSYSTEM_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szSubSystems.GetAt(nItem));
		continue;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHSUBSYSTEM_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHSUBSYSTEM_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_TCHISTORY_SEARCHSUBSYSTEM_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHSUBSYSTEM_NAME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHSUBSYSTEM_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHSUBSYSTEM_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHSUBSYSTEM_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHSUBSYSTEM_ALL)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHSUBSYSTEM_CASE)->EnableWindow();
	return TRUE;
}

void CTCHistorySearchSubSystemDialog::OnSelchangeSubSystem()
{
	GetDlgItem(IDC_TCHISTORY_SEARCHSUBSYSTEM_FIND)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_SEARCHSUBSYSTEM_NAME, CB_GETCURSEL) != CB_ERR) ? TRUE : FALSE);
}

void CTCHistorySearchSubSystemDialog::OnEditchangeSubSystem()
{
	GetDlgItem(IDC_TCHISTORY_SEARCHSUBSYSTEM_FIND)->EnableWindow((GetDlgItem(IDC_TCHISTORY_SEARCHSUBSYSTEM_NAME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CTCHistorySearchSubSystemDialog::OnFindTelecommand()
{
	CString  szSubSystem;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_TCHISTORY_SEARCHSUBSYSTEM_NAME)->GetWindowText(szSubSystem);
	if (SendDlgItemMessage(IDC_TCHISTORY_SEARCHSUBSYSTEM_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szSubSystem) == CB_ERR)
	{
		SendDlgItemMessage(IDC_TCHISTORY_SEARCHSUBSYSTEM_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szSubSystem);
		m_szSubSystems.Add(szSubSystem);
	}
	if (!GetParent()->SearchTelecommandBySubSystem(szSubSystem, IsDlgButtonChecked(IDC_TCHISTORY_SEARCHSUBSYSTEM_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHSUBSYSTEM_ALL), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHSUBSYSTEM_CASE)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_SUBSYSTEM_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHSUBSYSTEM_ALL, FALSE);
}

void CTCHistorySearchSubSystemDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchSubSystemDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchSubSystemDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchArgumentsDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchArgumentsDialog, CDisplayDialog)

CTCHistorySearchArgumentsDialog::CTCHistorySearchArgumentsDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchArgumentsDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchArgumentsDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchArgumentsDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchArgumentsDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

void CTCHistorySearchArgumentsDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchArgumentsDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchArgumentsDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchArgumentsDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHARGUMENTS_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHARGUMENTS_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_TCHISTORY_SEARCHARGUMENTS_ARGUMENT, OnSelchangeArgument)
	ON_CBN_EDITCHANGE(IDC_TCHISTORY_SEARCHARGUMENTS_ARGUMENT, OnEditchangeArgument)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchArgumentsDialog message handlers

BOOL CTCHistorySearchArgumentsDialog::OnInitDialog()
{
	INT  nItem;
	INT  nItems;
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	for (nItem = 0, nItems = (INT)m_szArguments.GetSize(); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_TCHISTORY_SEARCHARGUMENTS_ARGUMENT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szArguments.GetAt(nItem));
		continue;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHARGUMENTS_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHARGUMENTS_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_TCHISTORY_SEARCHARGUMENTS_ARGUMENT_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHARGUMENTS_ARGUMENT)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHARGUMENTS_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHARGUMENTS_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHARGUMENTS_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHARGUMENTS_ALL)->EnableWindow();
	return TRUE;
}

void CTCHistorySearchArgumentsDialog::OnSelchangeArgument()
{
	GetDlgItem(IDC_TCHISTORY_SEARCHARGUMENTS_FIND)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_SEARCHARGUMENTS_ARGUMENT, CB_GETCURSEL) != CB_ERR) ? TRUE : FALSE);
}

void CTCHistorySearchArgumentsDialog::OnEditchangeArgument()
{
	GetDlgItem(IDC_TCHISTORY_SEARCHARGUMENTS_FIND)->EnableWindow((GetDlgItem(IDC_TCHISTORY_SEARCHARGUMENTS_ARGUMENT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CTCHistorySearchArgumentsDialog::OnFindTelecommand()
{
	CString  szArgument;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_TCHISTORY_SEARCHARGUMENTS_ARGUMENT)->GetWindowText(szArgument);
	if (SendDlgItemMessage(IDC_TCHISTORY_SEARCHARGUMENTS_ARGUMENT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szArgument) == CB_ERR)
	{
		SendDlgItemMessage(IDC_TCHISTORY_SEARCHARGUMENTS_ARGUMENT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szArgument);
		m_szArguments.Add(szArgument);
	}
	if (!GetParent()->SearchTelecommandByArgument(szArgument, IsDlgButtonChecked(IDC_TCHISTORY_SEARCHARGUMENTS_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHARGUMENTS_ALL)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_ARGUMENT_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHARGUMENTS_ALL, FALSE);
}

void CTCHistorySearchArgumentsDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchArgumentsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchArgumentsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchFlagsDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchFlagsDialog, CDisplayDialog)

CTCHistorySearchFlagsDialog::CTCHistorySearchFlagsDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchFlagsDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchFlagsDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchFlagsDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchFlagsDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

void CTCHistorySearchFlagsDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchFlagsDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchFlagsDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchFlagsDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHFLAGS_FLAG_INTERLOCKING, OnInterlockingFlag)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHFLAGS_FLAG_INTERLOCKED, OnInterlockedFlag)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHFLAGS_FLAG_GROUPED, OnGroupedFlag)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHFLAGS_FLAG_BLOCKED, OnBlockedFlag)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHFLAGS_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHFLAGS_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchFlagsDialog message handlers

BOOL CTCHistorySearchFlagsDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHFLAGS_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHFLAGS_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_TCHISTORY_SEARCHFLAGS_FLAG_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHFLAGS_FLAG_INTERLOCKING)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHFLAGS_FLAG_INTERLOCKED)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHFLAGS_FLAG_GROUPED)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHFLAGS_FLAG_BLOCKED)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHFLAGS_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHFLAGS_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHFLAGS_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHFLAGS_ALL)->EnableWindow();
	return TRUE;
}

void CTCHistorySearchFlagsDialog::OnInterlockingFlag()
{
	GetDlgItem(IDC_TCHISTORY_SEARCHFLAGS_FIND)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORY_SEARCHFLAGS_FLAG_INTERLOCKING) || IsDlgButtonChecked(IDC_TCHISTORY_SEARCHFLAGS_FLAG_INTERLOCKED) || IsDlgButtonChecked(IDC_TCHISTORY_SEARCHFLAGS_FLAG_GROUPED) || IsDlgButtonChecked(IDC_TCHISTORY_SEARCHFLAGS_FLAG_BLOCKED));
}

void CTCHistorySearchFlagsDialog::OnInterlockedFlag()
{
	GetDlgItem(IDC_TCHISTORY_SEARCHFLAGS_FIND)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORY_SEARCHFLAGS_FLAG_INTERLOCKING) || IsDlgButtonChecked(IDC_TCHISTORY_SEARCHFLAGS_FLAG_INTERLOCKED) || IsDlgButtonChecked(IDC_TCHISTORY_SEARCHFLAGS_FLAG_GROUPED) || IsDlgButtonChecked(IDC_TCHISTORY_SEARCHFLAGS_FLAG_BLOCKED));
}

void CTCHistorySearchFlagsDialog::OnGroupedFlag()
{
	GetDlgItem(IDC_TCHISTORY_SEARCHFLAGS_FIND)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORY_SEARCHFLAGS_FLAG_INTERLOCKING) || IsDlgButtonChecked(IDC_TCHISTORY_SEARCHFLAGS_FLAG_INTERLOCKED) || IsDlgButtonChecked(IDC_TCHISTORY_SEARCHFLAGS_FLAG_GROUPED) || IsDlgButtonChecked(IDC_TCHISTORY_SEARCHFLAGS_FLAG_BLOCKED));
}

void CTCHistorySearchFlagsDialog::OnBlockedFlag()
{
	GetDlgItem(IDC_TCHISTORY_SEARCHFLAGS_FIND)->EnableWindow(IsDlgButtonChecked(IDC_TCHISTORY_SEARCHFLAGS_FLAG_INTERLOCKING) || IsDlgButtonChecked(IDC_TCHISTORY_SEARCHFLAGS_FLAG_INTERLOCKED) || IsDlgButtonChecked(IDC_TCHISTORY_SEARCHFLAGS_FLAG_GROUPED) || IsDlgButtonChecked(IDC_TCHISTORY_SEARCHFLAGS_FLAG_BLOCKED));
}

void CTCHistorySearchFlagsDialog::OnFindTelecommand()
{
	CHourglassCursor  cCursor;

	if (!GetParent()->SearchTelecommandByFlags(IsDlgButtonChecked(IDC_TCHISTORY_SEARCHFLAGS_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHFLAGS_ALL), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHFLAGS_FLAG_INTERLOCKING), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHFLAGS_FLAG_INTERLOCKED), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHFLAGS_FLAG_GROUPED), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHFLAGS_FLAG_BLOCKED)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_FLAGS_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHFLAGS_ALL, FALSE);
}

void CTCHistorySearchFlagsDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchFlagsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchFlagsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchTCPacketDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchTCPacketDialog, CDisplayDialog)

CTCHistorySearchTCPacketDialog::CTCHistorySearchTCPacketDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchTCPacketDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchTCPacketDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchTCPacketDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchTCPacketDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

VOID CTCHistorySearchTCPacketDialog::EnumTCPackets()
{
	INT  nPacket;
	INT  nPackets;
	CString  szPacket;
	CDatabaseTCPacket  *pPacket;

	SendDlgItemMessage(IDC_TCHISTORY_SEARCHTCPACKET_TAG, CB_RESETCONTENT);
	for (nPacket = 0, nPackets = (INT)GetDatabase()->GetTCPackets()->GetSize(); nPacket < nPackets; nPacket++)
	{
		if ((pPacket = GetDatabase()->GetTCPackets()->GetAt(nPacket)) != (CDatabaseTCPacket *)NULL)
		{
			szPacket.Format(STRING(IDS_TCHISTORYSEARCHDIALOG_TCPACKET_FORMAT), (LPCTSTR)pPacket->GetTag(), (LPCTSTR)pPacket->GetDescription());
			SendDlgItemMessage(IDC_TCHISTORY_SEARCHTCPACKET_TAG, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szPacket);
		}
	}
	GetDlgItem(IDC_TCHISTORY_SEARCHTCPACKET_FIND)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_SEARCHTCPACKET_TAG, CB_SETCURSEL) >= 0) ? TRUE : FALSE);
}

void CTCHistorySearchTCPacketDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchTCPacketDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchTCPacketDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchTCPacketDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHTCPACKET_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHTCPACKET_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchTCPacketDialog message handlers

BOOL CTCHistorySearchTCPacketDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHTCPACKET_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHTCPACKET_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_TCHISTORY_SEARCHTCPACKET_TAG_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHTCPACKET_TAG)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHTCPACKET_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHTCPACKET_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHTCPACKET_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHTCPACKET_ALL)->EnableWindow();
	EnumTCPackets();
	return TRUE;
}

void CTCHistorySearchTCPacketDialog::OnFindTelecommand()
{
	INT  nPos;
	CString  szPacket;
	CString  szFormat;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_TCHISTORY_SEARCHTCPACKET_TAG)->GetWindowText(szPacket), szFormat.Format(STRING(IDS_TCHISTORYSEARCHDIALOG_TCPACKET_FORMAT), EMPTYSTRING, EMPTYSTRING); (nPos = szPacket.Find(szFormat)) >= 0; )
	{
		szPacket = szPacket.Left(nPos);
		break;
	}
	if (!GetParent()->SearchTelecommandByTCPacket(szPacket, IsDlgButtonChecked(IDC_TCHISTORY_SEARCHTCPACKET_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHTCPACKET_ALL)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_TCPACKET_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHTCPACKET_ALL, FALSE);
}

void CTCHistorySearchTCPacketDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchTCPacketDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchTCPacketDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchDispatchTimeDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchDispatchTimeDialog, CDisplayDialog)

CTCHistorySearchDispatchTimeDialog::CTCHistorySearchDispatchTimeDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchDispatchTimeDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchDispatchTimeDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchDispatchTimeDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchDispatchTimeDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

void CTCHistorySearchDispatchTimeDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchDispatchTimeDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchDispatchTimeDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchDispatchTimeDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHDISPATCHTIME_DIRECTION_UP, OnDirectionUp)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHDISPATCHTIME_DIRECTION_DOWN, OnDirectionDown)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHDISPATCHTIME_MATCH, OnMatchTime)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHDISPATCHTIME_INTERVAL, OnIntervalTime)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHDISPATCHTIME_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHDISPATCHTIME_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchDispatchTimeDialog message handlers

BOOL CTCHistorySearchDispatchTimeDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHDISPATCHTIME_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHDISPATCHTIME_MATCH, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHDISPATCHTIME_DIRECTION_DOWN, TRUE);
	Spinbox_SetRange(GetDlgItem(IDC_TCHISTORY_SEARCHDISPATCHTIME_INTERVAL_TIME), TCHISTORYSEARCHDISPATCHTIME_MINIMUMINTERVAL, TCHISTORYSEARCHDISPATCHTIME_MAXIMUMINTERVAL);
	GetDlgItem(IDC_TCHISTORY_SEARCHDISPATCHTIME_TIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHDISPATCHTIME_TIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHDISPATCHTIME_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHDISPATCHTIME_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHDISPATCHTIME_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHDISPATCHTIME_ALL)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHDISPATCHTIME_MATCH)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHDISPATCHTIME_INTERVAL)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHDISPATCHTIME_FIND)->EnableWindow();
	return TRUE;
}

void CTCHistorySearchDispatchTimeDialog::OnDirectionUp()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHDISPATCHTIME_DIRECTION_UP, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHDISPATCHTIME_DIRECTION_DOWN, FALSE);
}

void CTCHistorySearchDispatchTimeDialog::OnDirectionDown()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHDISPATCHTIME_DIRECTION_UP, FALSE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHDISPATCHTIME_DIRECTION_DOWN, TRUE);
}

void CTCHistorySearchDispatchTimeDialog::OnMatchTime()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHDISPATCHTIME_MATCH, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHDISPATCHTIME_INTERVAL, FALSE);
	GetDlgItem(IDC_TCHISTORY_SEARCHDISPATCHTIME_INTERVAL_TIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_SEARCHDISPATCHTIME_INTERVAL_STATIC)->EnableWindow(FALSE);
}

void CTCHistorySearchDispatchTimeDialog::OnIntervalTime()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHDISPATCHTIME_MATCH, FALSE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHDISPATCHTIME_INTERVAL, TRUE);
	Spinbox_SetPos(GetDlgItem(IDC_TCHISTORY_SEARCHDISPATCHTIME_INTERVAL_TIME), TCHISTORYSEARCHDISPATCHTIME_DEFAULTINTERVAL);
	GetDlgItem(IDC_TCHISTORY_SEARCHDISPATCHTIME_INTERVAL_TIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHDISPATCHTIME_INTERVAL_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHDISPATCHTIME_INTERVAL_TIME)->SetFocus();
}

void CTCHistorySearchDispatchTimeDialog::OnFindTelecommand()
{
	CHourglassCursor  cCursor;

	if (!GetParent()->SearchTelecommandByDispatchTime(Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORY_SEARCHDISPATCHTIME_TIME)), (IsDlgButtonChecked(IDC_TCHISTORY_SEARCHDISPATCHTIME_INTERVAL)) ? Spinbox_GetPos(GetDlgItem(IDC_TCHISTORY_SEARCHDISPATCHTIME_INTERVAL_TIME)) : 0, IsDlgButtonChecked(IDC_TCHISTORY_SEARCHDISPATCHTIME_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHDISPATCHTIME_ALL), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHDISPATCHTIME_MATCH)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_DISPATCHTIME_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHDISPATCHTIME_ALL, FALSE);
}

void CTCHistorySearchDispatchTimeDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchDispatchTimeDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchDispatchTimeDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchReleaseTimeDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchReleaseTimeDialog, CDisplayDialog)

CTCHistorySearchReleaseTimeDialog::CTCHistorySearchReleaseTimeDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchReleaseTimeDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchReleaseTimeDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchReleaseTimeDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchReleaseTimeDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

void CTCHistorySearchReleaseTimeDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchReleaseTimeDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchReleaseTimeDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchReleaseTimeDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHRELEASETIME_DIRECTION_UP, OnDirectionUp)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHRELEASETIME_DIRECTION_DOWN, OnDirectionDown)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHRELEASETIME_MATCH, OnMatchTime)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHRELEASETIME_INTERVAL, OnIntervalTime)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHRELEASETIME_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHRELEASETIME_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchReleaseTimeDialog message handlers

BOOL CTCHistorySearchReleaseTimeDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIME_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIME_MATCH, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIME_DIRECTION_DOWN, TRUE);
	Spinbox_SetRange(GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIME_INTERVAL_TIME), TCHISTORYSEARCHRELEASETIME_MINIMUMINTERVAL, TCHISTORYSEARCHRELEASETIME_MAXIMUMINTERVAL);
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIME_TIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIME_TIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIME_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIME_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIME_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIME_ALL)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIME_MATCH)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIME_INTERVAL)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIME_FIND)->EnableWindow();
	return TRUE;
}

void CTCHistorySearchReleaseTimeDialog::OnDirectionUp()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIME_DIRECTION_UP, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIME_DIRECTION_DOWN, FALSE);
}

void CTCHistorySearchReleaseTimeDialog::OnDirectionDown()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIME_DIRECTION_UP, FALSE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIME_DIRECTION_DOWN, TRUE);
}

void CTCHistorySearchReleaseTimeDialog::OnMatchTime()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIME_MATCH, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIME_INTERVAL, FALSE);
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIME_INTERVAL_TIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIME_INTERVAL_STATIC)->EnableWindow(FALSE);
}

void CTCHistorySearchReleaseTimeDialog::OnIntervalTime()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIME_MATCH, FALSE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIME_INTERVAL, TRUE);
	Spinbox_SetPos(GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIME_INTERVAL_TIME), TCHISTORYSEARCHRELEASETIME_DEFAULTINTERVAL);
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIME_INTERVAL_TIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIME_INTERVAL_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIME_INTERVAL_TIME)->SetFocus();
}

void CTCHistorySearchReleaseTimeDialog::OnFindTelecommand()
{
	CHourglassCursor  cCursor;

	if (!GetParent()->SearchTelecommandByReleaseTime(Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIME_TIME)), (IsDlgButtonChecked(IDC_TCHISTORY_SEARCHRELEASETIME_INTERVAL)) ? Spinbox_GetPos(GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIME_INTERVAL_TIME)) : 0, IsDlgButtonChecked(IDC_TCHISTORY_SEARCHRELEASETIME_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHRELEASETIME_ALL), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHRELEASETIME_MATCH)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_RELEASETIME_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIME_ALL, FALSE);
}

void CTCHistorySearchReleaseTimeDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchReleaseTimeDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchReleaseTimeDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchReleaseTimeOffsetDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchReleaseTimeOffsetDialog, CDisplayDialog)

CTCHistorySearchReleaseTimeOffsetDialog::CTCHistorySearchReleaseTimeOffsetDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchReleaseTimeOffsetDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchReleaseTimeOffsetDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchReleaseTimeOffsetDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchReleaseTimeOffsetDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

void CTCHistorySearchReleaseTimeOffsetDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchReleaseTimeOffsetDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchReleaseTimeOffsetDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchReleaseTimeOffsetDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_DIRECTION_UP, OnDirectionUp)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_DIRECTION_DOWN, OnDirectionDown)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_MATCH, OnMatchTimeOffset)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_INTERVAL, OnIntervalTimeOffset)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchReleaseTimeOffsetDialog message handlers

BOOL CTCHistorySearchReleaseTimeOffsetDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_MATCH, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_DIRECTION_DOWN, TRUE);
	Timespinbox_SetTime(GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_OFFSET), CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY)));
	Spinbox_SetRange(GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_INTERVAL_TIME), TCHISTORYSEARCHRELEASETIMEOFFSET_MINIMUMINTERVAL, TCHISTORYSEARCHRELEASETIMEOFFSET_MAXIMUMINTERVAL);
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_OFFSET_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_OFFSET)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_ALL)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_MATCH)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_INTERVAL)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_FIND)->EnableWindow();
	return TRUE;
}

void CTCHistorySearchReleaseTimeOffsetDialog::OnDirectionUp()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_DIRECTION_UP, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_DIRECTION_DOWN, FALSE);
}

void CTCHistorySearchReleaseTimeOffsetDialog::OnDirectionDown()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_DIRECTION_UP, FALSE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_DIRECTION_DOWN, TRUE);
}

void CTCHistorySearchReleaseTimeOffsetDialog::OnMatchTimeOffset()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_MATCH, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_INTERVAL, FALSE);
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_INTERVAL_TIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_INTERVAL_STATIC)->EnableWindow(FALSE);
}

void CTCHistorySearchReleaseTimeOffsetDialog::OnIntervalTimeOffset()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_MATCH, FALSE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_INTERVAL, TRUE);
	Spinbox_SetPos(GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_INTERVAL_TIME), TCHISTORYSEARCHRELEASETIMEOFFSET_DEFAULTINTERVAL);
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_INTERVAL_TIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_INTERVAL_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_INTERVAL_TIME)->SetFocus();
}

void CTCHistorySearchReleaseTimeOffsetDialog::OnFindTelecommand()
{
	CHourglassCursor  cCursor;

	if (!GetParent()->SearchTelecommandByReleaseTimeOffset((DWORD)(1000 * (Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_OFFSET)).GetTime() % SECONDSPERDAY)), (IsDlgButtonChecked(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_INTERVAL)) ? Spinbox_GetPos(GetDlgItem(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_INTERVAL_TIME)) : 0, IsDlgButtonChecked(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_ALL), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_MATCH)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_RELEASETIMEOFFSET_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_ALL, FALSE);
}

void CTCHistorySearchReleaseTimeOffsetDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchReleaseTimeOffsetDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchReleaseTimeOffsetDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchTransmissionTimeDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchTransmissionTimeDialog, CDisplayDialog)

CTCHistorySearchTransmissionTimeDialog::CTCHistorySearchTransmissionTimeDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchTransmissionTimeDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchTransmissionTimeDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchTransmissionTimeDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchTransmissionTimeDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

void CTCHistorySearchTransmissionTimeDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchTransmissionTimeDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchTransmissionTimeDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchTransmissionTimeDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_DIRECTION_UP, OnDirectionUp)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_DIRECTION_DOWN, OnDirectionDown)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_MATCH, OnMatchTime)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_INTERVAL, OnIntervalTime)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchTransmissionTimeDialog message handlers

BOOL CTCHistorySearchTransmissionTimeDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_MATCH, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_DIRECTION_DOWN, TRUE);
	Spinbox_SetRange(GetDlgItem(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_INTERVAL_TIME), TCHISTORYSEARCHTRANSMISSIONTIME_MINIMUMINTERVAL, TCHISTORYSEARCHRELEASETIME_MAXIMUMINTERVAL);
	GetDlgItem(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_TIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_TIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_ALL)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_MATCH)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_INTERVAL)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_FIND)->EnableWindow();
	return TRUE;
}

void CTCHistorySearchTransmissionTimeDialog::OnDirectionUp()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_DIRECTION_UP, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_DIRECTION_DOWN, FALSE);
}

void CTCHistorySearchTransmissionTimeDialog::OnDirectionDown()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_DIRECTION_UP, FALSE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_DIRECTION_DOWN, TRUE);
}

void CTCHistorySearchTransmissionTimeDialog::OnMatchTime()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_MATCH, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_INTERVAL, FALSE);
	GetDlgItem(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_INTERVAL_TIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_INTERVAL_STATIC)->EnableWindow(FALSE);
}

void CTCHistorySearchTransmissionTimeDialog::OnIntervalTime()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_MATCH, FALSE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_INTERVAL, TRUE);
	Spinbox_SetPos(GetDlgItem(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_INTERVAL_TIME), TCHISTORYSEARCHTRANSMISSIONTIME_DEFAULTINTERVAL);
	GetDlgItem(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_INTERVAL_TIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_INTERVAL_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_INTERVAL_TIME)->SetFocus();
}

void CTCHistorySearchTransmissionTimeDialog::OnFindTelecommand()
{
	CHourglassCursor  cCursor;

	if (!GetParent()->SearchTelecommandByTransmissionTime(Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_TIME)), (IsDlgButtonChecked(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_INTERVAL)) ? Spinbox_GetPos(GetDlgItem(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_INTERVAL_TIME)) : 0, IsDlgButtonChecked(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_ALL), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_MATCH)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_TRANSMISSIONTIME_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_ALL, FALSE);
}

void CTCHistorySearchTransmissionTimeDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchTransmissionTimeDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchTransmissionTimeDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchExecutionTimeDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchExecutionTimeDialog, CDisplayDialog)

CTCHistorySearchExecutionTimeDialog::CTCHistorySearchExecutionTimeDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchExecutionTimeDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchExecutionTimeDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchExecutionTimeDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchExecutionTimeDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

void CTCHistorySearchExecutionTimeDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchExecutionTimeDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchExecutionTimeDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchExecutionTimeDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHEXECUTIONTIME_DIRECTION_UP, OnDirectionUp)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHEXECUTIONTIME_DIRECTION_DOWN, OnDirectionDown)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHEXECUTIONTIME_MATCH, OnMatchTime)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHEXECUTIONTIME_INTERVAL, OnIntervalTime)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHEXECUTIONTIME_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHEXECUTIONTIME_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchExecutionTimeDialog message handlers

BOOL CTCHistorySearchExecutionTimeDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIME_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIME_MATCH, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIME_DIRECTION_DOWN, TRUE);
	Spinbox_SetRange(GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIME_INTERVAL_TIME), TCHISTORYSEARCHEXECUTIONTIME_MINIMUMINTERVAL, TCHISTORYSEARCHEXECUTIONTIME_MAXIMUMINTERVAL);
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIME_TIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIME_TIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIME_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIME_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIME_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIME_ALL)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIME_MATCH)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIME_INTERVAL)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIME_FIND)->EnableWindow();
	return TRUE;
}

void CTCHistorySearchExecutionTimeDialog::OnDirectionUp()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIME_DIRECTION_UP, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIME_DIRECTION_DOWN, FALSE);
}

void CTCHistorySearchExecutionTimeDialog::OnDirectionDown()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIME_DIRECTION_UP, FALSE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIME_DIRECTION_DOWN, TRUE);
}

void CTCHistorySearchExecutionTimeDialog::OnMatchTime()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIME_MATCH, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIME_INTERVAL, FALSE);
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIME_INTERVAL_TIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIME_INTERVAL_STATIC)->EnableWindow(FALSE);
}

void CTCHistorySearchExecutionTimeDialog::OnIntervalTime()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIME_MATCH, FALSE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIME_INTERVAL, TRUE);
	Spinbox_SetPos(GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIME_INTERVAL_TIME), TCHISTORYSEARCHEXECUTIONTIME_DEFAULTINTERVAL);
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIME_INTERVAL_TIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIME_INTERVAL_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIME_INTERVAL_TIME)->SetFocus();
}

void CTCHistorySearchExecutionTimeDialog::OnFindTelecommand()
{
	CHourglassCursor  cCursor;

	if (!GetParent()->SearchTelecommandByExecutionTime(Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIME_TIME)), (IsDlgButtonChecked(IDC_TCHISTORY_SEARCHEXECUTIONTIME_INTERVAL)) ? Spinbox_GetPos(GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIME_INTERVAL_TIME)) : 0, IsDlgButtonChecked(IDC_TCHISTORY_SEARCHEXECUTIONTIME_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHEXECUTIONTIME_ALL), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHEXECUTIONTIME_MATCH)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_EXECUTIONTIME_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIME_ALL, FALSE);
}

void CTCHistorySearchExecutionTimeDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchExecutionTimeDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchExecutionTimeDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchExecutionTimeOffsetDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchExecutionTimeOffsetDialog, CDisplayDialog)

CTCHistorySearchExecutionTimeOffsetDialog::CTCHistorySearchExecutionTimeOffsetDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchExecutionTimeOffsetDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchExecutionTimeOffsetDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchExecutionTimeOffsetDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchExecutionTimeOffsetDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

void CTCHistorySearchExecutionTimeOffsetDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchExecutionTimeOffsetDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchExecutionTimeOffsetDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchExecutionTimeOffsetDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_DIRECTION_UP, OnDirectionUp)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_DIRECTION_DOWN, OnDirectionDown)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_MATCH, OnMatchTimeOffset)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_INTERVAL, OnIntervalTimeOffset)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchExecutionTimeOffsetDialog message handlers

BOOL CTCHistorySearchExecutionTimeOffsetDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_MATCH, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_DIRECTION_DOWN, TRUE);
	Timespinbox_SetRange(GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_OFFSET), CTimeKey(TCHISTORYSEARCHEXECUTIONTIMEOFFSET_MINIMUMOFFSET), CTimeKey(TCHISTORYSEARCHEXECUTIONTIMEOFFSET_MAXIMUMOFFSET));
	Timespinbox_SetTime(GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_OFFSET), CTimeKey(TCHISTORYSEARCHEXECUTIONTIMEOFFSET_DEFAULTOFFSET));
	Spinbox_SetRange(GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_INTERVAL_TIME), TCHISTORYSEARCHEXECUTIONTIMEOFFSET_MINIMUMINTERVAL, TCHISTORYSEARCHEXECUTIONTIMEOFFSET_MAXIMUMINTERVAL);
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_OFFSET_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_OFFSET)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_ALL)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_MATCH)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_INTERVAL)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_FIND)->EnableWindow();
	return TRUE;
}

void CTCHistorySearchExecutionTimeOffsetDialog::OnDirectionUp()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_DIRECTION_UP, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_DIRECTION_DOWN, FALSE);
}

void CTCHistorySearchExecutionTimeOffsetDialog::OnDirectionDown()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_DIRECTION_UP, FALSE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_DIRECTION_DOWN, TRUE);
}

void CTCHistorySearchExecutionTimeOffsetDialog::OnMatchTimeOffset()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_MATCH, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_INTERVAL, FALSE);
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_INTERVAL_TIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_INTERVAL_STATIC)->EnableWindow(FALSE);
}

void CTCHistorySearchExecutionTimeOffsetDialog::OnIntervalTimeOffset()
{
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_MATCH, FALSE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_INTERVAL, TRUE);
	Spinbox_SetPos(GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_INTERVAL_TIME), TCHISTORYSEARCHEXECUTIONTIMEOFFSET_DEFAULTINTERVAL);
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_INTERVAL_TIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_INTERVAL_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_INTERVAL_TIME)->SetFocus();
}

void CTCHistorySearchExecutionTimeOffsetDialog::OnFindTelecommand()
{
	CHourglassCursor  cCursor;

	if (!GetParent()->SearchTelecommandByExecutionTimeOffset(Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_OFFSET)).GetTime(), (IsDlgButtonChecked(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_INTERVAL)) ? Spinbox_GetPos(GetDlgItem(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_INTERVAL_TIME)) : 0, IsDlgButtonChecked(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_ALL), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_MATCH)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_EXECUTIONTIMEOFFSET_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_ALL, FALSE);
}

void CTCHistorySearchExecutionTimeOffsetDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchExecutionTimeOffsetDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchExecutionTimeOffsetDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchAuthorizationDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchAuthorizationDialog, CDisplayDialog)

CTCHistorySearchAuthorizationDialog::CTCHistorySearchAuthorizationDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchAuthorizationDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchAuthorizationDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchAuthorizationDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchAuthorizationDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

VOID CTCHistorySearchAuthorizationDialog::EnumAuthorizations()
{
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHAUTHORIZATION_TYPE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_AUTHORIZATION_MANUAL));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHAUTHORIZATION_TYPE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_AUTHORIZATION_AUTOMATIC));
	GetDlgItem(IDC_TCHISTORY_SEARCHAUTHORIZATION_FIND)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_SEARCHAUTHORIZATION_TYPE, CB_SETCURSEL) >= 0) ? TRUE : FALSE);
}

void CTCHistorySearchAuthorizationDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchAuthorizationDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchAuthorizationDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchAuthorizationDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHAUTHORIZATION_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHAUTHORIZATION_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchAuthorizationDialog message handlers

BOOL CTCHistorySearchAuthorizationDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHAUTHORIZATION_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHAUTHORIZATION_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_TCHISTORY_SEARCHAUTHORIZATION_TYPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHAUTHORIZATION_TYPE)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHAUTHORIZATION_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHAUTHORIZATION_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHAUTHORIZATION_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHAUTHORIZATION_ALL)->EnableWindow();
	EnumAuthorizations();
	return TRUE;
}

void CTCHistorySearchAuthorizationDialog::OnFindTelecommand()
{
	CString  szAuthorization;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_TCHISTORY_SEARCHAUTHORIZATION_TYPE)->GetWindowText(szAuthorization);
	if (!GetParent()->SearchTelecommandByAuthorization((szAuthorization == STRING(IDS_TCHISTORYSEARCHDIALOG_AUTHORIZATION_AUTOMATIC)) ? TCHISTORYITEM_CHECKFLAG_PREAUTHORIZED : 0, IsDlgButtonChecked(IDC_TCHISTORY_SEARCHAUTHORIZATION_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHAUTHORIZATION_ALL)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_AUTHORIZATION_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHAUTHORIZATION_ALL, FALSE);
}

void CTCHistorySearchAuthorizationDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchAuthorizationDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchAuthorizationDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchPTVTimeWindowDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchPTVTimeWindowDialog, CDisplayDialog)

CTCHistorySearchPTVTimeWindowDialog::CTCHistorySearchPTVTimeWindowDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchPTVTimeWindowDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchPTVTimeWindowDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchPTVTimeWindowDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchPTVTimeWindowDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

void CTCHistorySearchPTVTimeWindowDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchPTVTimeWindowDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchPTVTimeWindowDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchPTVTimeWindowDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchPTVTimeWindowDialog message handlers

BOOL CTCHistorySearchPTVTimeWindowDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_TIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_TIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_ALL)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_FIND)->EnableWindow();
	return TRUE;
}

void CTCHistorySearchPTVTimeWindowDialog::OnFindTelecommand()
{
	CHourglassCursor  cCursor;

	if (!GetParent()->SearchTelecommandByPTVTimeWindow(Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_TIME)), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_ALL)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_PTVTIMEWINDOW_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_ALL, FALSE);
}

void CTCHistorySearchPTVTimeWindowDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchPTVTimeWindowDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchPTVTimeWindowDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchPTVCheckDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchPTVCheckDialog, CDisplayDialog)

CTCHistorySearchPTVCheckDialog::CTCHistorySearchPTVCheckDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchPTVCheckDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchPTVCheckDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchPTVCheckDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchPTVCheckDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

VOID CTCHistorySearchPTVCheckDialog::EnumCheckFlags()
{
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHPTVCHECK_CHECK, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_PTVCHECK_ON));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHPTVCHECK_CHECK, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_PTVCHECK_OFF));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHPTVCHECK_CHECK, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_PTVCHECK_DISABLED));
	GetDlgItem(IDC_TCHISTORY_SEARCHPTVCHECK_FIND)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_SEARCHPTVCHECK_CHECK, CB_SETCURSEL) >= 0) ? TRUE : FALSE);
}

void CTCHistorySearchPTVCheckDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchPTVCheckDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchPTVCheckDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchPTVCheckDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHPTVCHECK_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHPTVCHECK_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchPTVCheckDialog message handlers

BOOL CTCHistorySearchPTVCheckDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHPTVCHECK_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHPTVCHECK_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_TCHISTORY_SEARCHPTVCHECK_CHECK_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPTVCHECK_CHECK)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPTVCHECK_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPTVCHECK_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPTVCHECK_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPTVCHECK_ALL)->EnableWindow();
	EnumCheckFlags();
	return TRUE;
}

void CTCHistorySearchPTVCheckDialog::OnFindTelecommand()
{
	CString  szCheck;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_TCHISTORY_SEARCHPTVCHECK_CHECK)->GetWindowText(szCheck);
	if (!GetParent()->SearchTelecommandByPTVCheck((szCheck == STRING(IDS_TCHISTORYSEARCHDIALOG_PTVCHECK_OFF)) ? TCHISTORYITEM_CHECKFLAG_OVERRIDEPTV : ((szCheck == STRING(IDS_TCHISTORYSEARCHDIALOG_PTVCHECK_DISABLED)) ? TCHISTORYITEM_CHECKFLAG_DISABLEPTV : 0), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHPTVCHECK_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHPTVCHECK_ALL)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_PTVCHECK_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHPTVCHECK_ALL, FALSE);
}

void CTCHistorySearchPTVCheckDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchPTVCheckDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchPTVCheckDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchPTVResultDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchPTVResultDialog, CDisplayDialog)

CTCHistorySearchPTVResultDialog::CTCHistorySearchPTVResultDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchPTVResultDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchPTVResultDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchPTVResultDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchPTVResultDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

VOID CTCHistorySearchPTVResultDialog::EnumCheckResults()
{
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHPTVRESULT_RESULT, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_PTVRESULT_GO));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHPTVRESULT_RESULT, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_PTVRESULT_WAIT));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHPTVRESULT_RESULT, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_PTVRESULT_FAIL));
	GetDlgItem(IDC_TCHISTORY_SEARCHPTVRESULT_FIND)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_SEARCHPTVRESULT_RESULT, CB_SETCURSEL) >= 0) ? TRUE : FALSE);
}

void CTCHistorySearchPTVResultDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchPTVResultDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchPTVResultDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchPTVResultDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHPTVRESULT_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHPTVRESULT_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchPTVResultDialog message handlers

BOOL CTCHistorySearchPTVResultDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHPTVRESULT_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHPTVRESULT_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_TCHISTORY_SEARCHPTVRESULT_RESULT_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPTVRESULT_RESULT)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPTVRESULT_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPTVRESULT_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPTVRESULT_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPTVRESULT_ALL)->EnableWindow();
	EnumCheckResults();
	return TRUE;
}

void CTCHistorySearchPTVResultDialog::OnFindTelecommand()
{
	CString  szResult;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_TCHISTORY_SEARCHPTVRESULT_RESULT)->GetWindowText(szResult);
	if (!GetParent()->SearchTelecommandByPTVResult((szResult == STRING(IDS_TCHISTORYSEARCHDIALOG_PTVRESULT_GO)) ? TCHISTORYITEM_RESULT_PTV_GO : ((szResult == STRING(IDS_TCHISTORYSEARCHDIALOG_PTVRESULT_WAIT)) ? TCHISTORYITEM_RESULT_PTV_WAIT : ((szResult == STRING(IDS_TCHISTORYSEARCHDIALOG_PTVRESULT_FAIL)) ? TCHISTORYITEM_RESULT_PTV_FAIL : 0)), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHPTVRESULT_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHPTVRESULT_ALL)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_PTVRESULT_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHPTVRESULT_ALL, FALSE);
}

void CTCHistorySearchPTVResultDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchPTVResultDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchPTVResultDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchPEVCheckDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchPEVCheckDialog, CDisplayDialog)

CTCHistorySearchPEVCheckDialog::CTCHistorySearchPEVCheckDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchPEVCheckDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchPEVCheckDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchPEVCheckDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchPEVCheckDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

VOID CTCHistorySearchPEVCheckDialog::EnumCheckFlags()
{
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHPEVCHECK_CHECK, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_PEVCHECK_NONE));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHPEVCHECK_CHECK, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_PEVCHECK_ON));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHPEVCHECK_CHECK, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_PEVCHECK_OFF));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHPEVCHECK_CHECK, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_PEVCHECK_DISABLED));
	GetDlgItem(IDC_TCHISTORY_SEARCHPEVCHECK_FIND)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_SEARCHPEVCHECK_CHECK, CB_SETCURSEL) >= 0) ? TRUE : FALSE);
}

void CTCHistorySearchPEVCheckDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchPEVCheckDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchPEVCheckDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchPEVCheckDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHPEVCHECK_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHPEVCHECK_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchPEVCheckDialog message handlers

BOOL CTCHistorySearchPEVCheckDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHPEVCHECK_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHPEVCHECK_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_TCHISTORY_SEARCHPEVCHECK_CHECK_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPEVCHECK_CHECK)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPEVCHECK_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPEVCHECK_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPEVCHECK_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPEVCHECK_ALL)->EnableWindow();
	EnumCheckFlags();
	return TRUE;
}

void CTCHistorySearchPEVCheckDialog::OnFindTelecommand()
{
	CString  szCheck;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_TCHISTORY_SEARCHPEVCHECK_CHECK)->GetWindowText(szCheck);
	if (!GetParent()->SearchTelecommandByPEVCheck((szCheck == STRING(IDS_TCHISTORYSEARCHDIALOG_PEVCHECK_NONE)) ? ~(TCHISTORYITEM_CHECKFLAG_OVERRIDEPEV | TCHISTORYITEM_CHECKFLAG_DISABLEPEV) : ((szCheck == STRING(IDS_TCHISTORYSEARCHDIALOG_PEVCHECK_OFF)) ? TCHISTORYITEM_CHECKFLAG_OVERRIDEPEV : ((szCheck == STRING(IDS_TCHISTORYSEARCHDIALOG_PEVCHECK_DISABLED)) ? TCHISTORYITEM_CHECKFLAG_DISABLEPEV : 0)), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHPEVCHECK_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHPEVCHECK_ALL)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_PEVCHECK_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHPEVCHECK_ALL, FALSE);
}

void CTCHistorySearchPEVCheckDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchPEVCheckDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchPEVCheckDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchPEVResultDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchPEVResultDialog, CDisplayDialog)

CTCHistorySearchPEVResultDialog::CTCHistorySearchPEVResultDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchPEVResultDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchPEVResultDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchPEVResultDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchPEVResultDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

VOID CTCHistorySearchPEVResultDialog::EnumCheckResults()
{
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHPEVRESULT_RESULT, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_PEVRESULT_GO));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHPEVRESULT_RESULT, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_PEVRESULT_NOGO));
	GetDlgItem(IDC_TCHISTORY_SEARCHPEVRESULT_FIND)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_SEARCHPEVRESULT_RESULT, CB_SETCURSEL) >= 0) ? TRUE : FALSE);
}

void CTCHistorySearchPEVResultDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchPEVResultDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchPEVResultDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchPEVResultDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHPEVRESULT_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHPEVRESULT_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchPEVResultDialog message handlers

BOOL CTCHistorySearchPEVResultDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHPEVRESULT_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHPEVRESULT_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_TCHISTORY_SEARCHPEVRESULT_RESULT_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPEVRESULT_RESULT)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPEVRESULT_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPEVRESULT_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPEVRESULT_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHPEVRESULT_ALL)->EnableWindow();
	EnumCheckResults();
	return TRUE;
}

void CTCHistorySearchPEVResultDialog::OnFindTelecommand()
{
	CString  szResult;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_TCHISTORY_SEARCHPEVRESULT_RESULT)->GetWindowText(szResult);
	if (!GetParent()->SearchTelecommandByPEVResult((szResult == STRING(IDS_TCHISTORYSEARCHDIALOG_PEVRESULT_GO)) ? TCHISTORYITEM_RESULT_PEV_GO : ((szResult == STRING(IDS_TCHISTORYSEARCHDIALOG_PEVRESULT_NOGO)) ? TCHISTORYITEM_RESULT_PEV_NOGO : 0), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHPEVRESULT_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHPEVRESULT_ALL)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_PEVRESULT_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHPEVRESULT_ALL, FALSE);
}

void CTCHistorySearchPEVResultDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchPEVResultDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchPEVResultDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchCEVTimeWindowDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchCEVTimeWindowDialog, CDisplayDialog)

CTCHistorySearchCEVTimeWindowDialog::CTCHistorySearchCEVTimeWindowDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchCEVTimeWindowDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchCEVTimeWindowDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchCEVTimeWindowDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchCEVTimeWindowDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

void CTCHistorySearchCEVTimeWindowDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchCEVTimeWindowDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchCEVTimeWindowDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchCEVTimeWindowDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchCEVTimeWindowDialog message handlers

BOOL CTCHistorySearchCEVTimeWindowDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_TIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_TIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_ALL)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_FIND)->EnableWindow();
	return TRUE;
}

void CTCHistorySearchCEVTimeWindowDialog::OnFindTelecommand()
{
	CHourglassCursor  cCursor;

	if (!GetParent()->SearchTelecommandByCEVTimeWindow(Timespinbox_GetTime(GetDlgItem(IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_TIME)), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_ALL)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_CEVTIMEWINDOW_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_ALL, FALSE);
}

void CTCHistorySearchCEVTimeWindowDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchCEVTimeWindowDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchCEVTimeWindowDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchCEVCheckDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchCEVCheckDialog, CDisplayDialog)

CTCHistorySearchCEVCheckDialog::CTCHistorySearchCEVCheckDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchCEVCheckDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchCEVCheckDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchCEVCheckDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchCEVCheckDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

VOID CTCHistorySearchCEVCheckDialog::EnumCheckFlags()
{
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHCEVCHECK_CHECK, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_CEVCHECK_NONE));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHCEVCHECK_CHECK, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_CEVCHECK_ON));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHCEVCHECK_CHECK, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_CEVCHECK_OFF));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHCEVCHECK_CHECK, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_CEVCHECK_DISABLED));
	GetDlgItem(IDC_TCHISTORY_SEARCHCEVCHECK_FIND)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_SEARCHCEVCHECK_CHECK, CB_SETCURSEL) >= 0) ? TRUE : FALSE);
}

void CTCHistorySearchCEVCheckDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchCEVCheckDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchCEVCheckDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchCEVCheckDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHCEVCHECK_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHCEVCHECK_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchCEVCheckDialog message handlers

BOOL CTCHistorySearchCEVCheckDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHCEVCHECK_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHCEVCHECK_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_TCHISTORY_SEARCHCEVCHECK_CHECK_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCEVCHECK_CHECK)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCEVCHECK_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCEVCHECK_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCEVCHECK_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCEVCHECK_ALL)->EnableWindow();
	EnumCheckFlags();
	return TRUE;
}

void CTCHistorySearchCEVCheckDialog::OnFindTelecommand()
{
	CString  szCheck;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_TCHISTORY_SEARCHCEVCHECK_CHECK)->GetWindowText(szCheck);
	if (!GetParent()->SearchTelecommandByCEVCheck((szCheck == STRING(IDS_TCHISTORYSEARCHDIALOG_CEVCHECK_NONE)) ? ~(TCHISTORYITEM_CHECKFLAG_OVERRIDECEV | TCHISTORYITEM_CHECKFLAG_DISABLECEV) : ((szCheck == STRING(IDS_TCHISTORYSEARCHDIALOG_CEVCHECK_OFF)) ? TCHISTORYITEM_CHECKFLAG_OVERRIDECEV : ((szCheck == STRING(IDS_TCHISTORYSEARCHDIALOG_CEVCHECK_DISABLED)) ? TCHISTORYITEM_CHECKFLAG_DISABLECEV : 0)), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHCEVCHECK_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHCEVCHECK_ALL)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_CEVCHECK_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHCEVCHECK_ALL, FALSE);
}

void CTCHistorySearchCEVCheckDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchCEVCheckDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchCEVCheckDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchCEVResultDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchCEVResultDialog, CDisplayDialog)

CTCHistorySearchCEVResultDialog::CTCHistorySearchCEVResultDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchCEVResultDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchCEVResultDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchCEVResultDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchCEVResultDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

VOID CTCHistorySearchCEVResultDialog::EnumCheckResults()
{
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHCEVRESULT_RESULT, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_CEVRESULT_IDLE));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHCEVRESULT_RESULT, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_CEVRESULT_PENDING));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHCEVRESULT_RESULT, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_CEVRESULT_PASSED));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHCEVRESULT_RESULT, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_CEVRESULT_FAILED));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHCEVRESULT_RESULT, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_CEVRESULT_UNKNOWN));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHCEVRESULT_RESULT, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_CEVRESULT_UNVERIFIED));
	GetDlgItem(IDC_TCHISTORY_SEARCHCEVRESULT_FIND)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_SEARCHCEVRESULT_RESULT, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCHISTORY_SEARCHCEVRESULT_RESULT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_CEVRESULT_PASSED))) >= 0) ? TRUE : FALSE);
}

void CTCHistorySearchCEVResultDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchCEVResultDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchCEVResultDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchCEVResultDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHCEVRESULT_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHCEVRESULT_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchCEVResultDialog message handlers

BOOL CTCHistorySearchCEVResultDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHCEVRESULT_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHCEVRESULT_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_TCHISTORY_SEARCHCEVRESULT_RESULT_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCEVRESULT_RESULT)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCEVRESULT_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCEVRESULT_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCEVRESULT_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHCEVRESULT_ALL)->EnableWindow();
	EnumCheckResults();
	return TRUE;
}

void CTCHistorySearchCEVResultDialog::OnFindTelecommand()
{
	CString  szResult;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_TCHISTORY_SEARCHCEVRESULT_RESULT)->GetWindowText(szResult);
	if (!GetParent()->SearchTelecommandByCEVResult((szResult == STRING(IDS_TCHISTORYSEARCHDIALOG_CEVRESULT_IDLE)) ? TCHISTORYITEM_RESULT_CEV_IDLE : ((szResult == STRING(IDS_TCHISTORYSEARCHDIALOG_CEVRESULT_PENDING)) ? TCHISTORYITEM_RESULT_CEV_PENDING : ((szResult == STRING(IDS_TCHISTORYSEARCHDIALOG_CEVRESULT_PASSED)) ? TCHISTORYITEM_RESULT_CEV_PASSED : ((szResult == STRING(IDS_TCHISTORYSEARCHDIALOG_CEVRESULT_FAILED)) ? TCHISTORYITEM_RESULT_CEV_FAILED : ((szResult == STRING(IDS_TCHISTORYSEARCHDIALOG_CEVRESULT_UNKNOWN)) ? TCHISTORYITEM_RESULT_CEV_UNKNOWN : ((szResult == STRING(IDS_TCHISTORYSEARCHDIALOG_CEVRESULT_UNVERIFIED)) ? TCHISTORYITEM_RESULT_CEV_UNVERIFIED : 0))))), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHCEVRESULT_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHCEVRESULT_ALL)))
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_CEVRESULT_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHCEVRESULT_ALL, FALSE);
}

void CTCHistorySearchCEVResultDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchCEVResultDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchCEVResultDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchStatusDialog dialog

IMPLEMENT_DYNCREATE(CTCHistorySearchStatusDialog, CDisplayDialog)

CTCHistorySearchStatusDialog::CTCHistorySearchStatusDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistorySearchStatusDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCHistorySearchStatusDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCHistorySearchStatusDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCHistoryView *CTCHistorySearchStatusDialog::GetParent() CONST
{
	return((CTCHistoryView *)CDisplayDialog::GetParent());
}

VOID CTCHistorySearchStatusDialog::EnumStatus()
{
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHSTATUS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_STATUS_RELEASED));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHSTATUS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_STATUS_NOTRELEASED));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHSTATUS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_STATUS_FAILEDRELEASE));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHSTATUS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_STATUS_SENT));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHSTATUS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_STATUS_FAILEDSEND));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHSTATUS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_STATUS_UPLINKED));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHSTATUS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_STATUS_FAILEDUPLINK));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHSTATUS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_STATUS_EXECUTED));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHSTATUS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_STATUS_NOTEXECUTED));
	SendDlgItemMessage(IDC_TCHISTORY_SEARCHSTATUS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TCHISTORYSEARCHDIALOG_STATUS_FAILEDEXECUTION));
	GetDlgItem(IDC_TCHISTORY_SEARCHSTATUS_FIND)->EnableWindow((SendDlgItemMessage(IDC_TCHISTORY_SEARCHSTATUS_STATUS, CB_SETCURSEL) >= 0) ? TRUE : FALSE);
}

void CTCHistorySearchStatusDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistorySearchStatusDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistorySearchStatusDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistorySearchStatusDialog)
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHSTATUS_FIND, OnFindTelecommand)
	ON_BN_CLICKED(IDC_TCHISTORY_SEARCHSTATUS_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchStatusDialog message handlers

BOOL CTCHistorySearchStatusDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); TRUE; )
	{
		MoveWindow(rDialog[0].left + 10 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHSTATUS_ALL, TRUE);
	CheckDlgButton(IDC_TCHISTORY_SEARCHSTATUS_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_TCHISTORY_SEARCHSTATUS_STATUS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHSTATUS_STATUS)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHSTATUS_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHSTATUS_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHSTATUS_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_SEARCHSTATUS_ALL)->EnableWindow();
	EnumStatus();
	return TRUE;
}

void CTCHistorySearchStatusDialog::OnFindTelecommand()
{
	CString  szStatus;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_TCHISTORY_SEARCHSTATUS_STATUS)->GetWindowText(szStatus); !GetParent()->SearchTelecommandByStatus(szStatus, IsDlgButtonChecked(IDC_TCHISTORY_SEARCHSTATUS_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCHISTORY_SEARCHSTATUS_ALL)); )
	{
		ReportEvent(USER_INFORMATIONAL_TCHISTORY_SEARCH_STATUS_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_TCHISTORY_SEARCHSTATUS_ALL, FALSE);
}

void CTCHistorySearchStatusDialog::OnDestroy()
{
	GetParent()->SelectTelecommand(-1);
	CDisplayDialog::OnDestroy();
}

BOOL CTCHistorySearchStatusDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistorySearchStatusDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistoryOpenDialog dialog

IMPLEMENT_DYNCREATE(CTCHistoryOpenDialog, CDisplayDialog)

CTCHistoryOpenDialog::CTCHistoryOpenDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCHistoryOpenDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCHistoryOpenDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CTCHistoryOpenDialog::IDD);
}

BOOL CTCHistoryOpenDialog::Initialize()
{
	m_nFilterMode[0] = 0;
	m_nFilterMode[1] = 0;
	m_nFilterAutoload = 0;
	m_nFilterLimitation = 0;
	m_nRetrieveMode = 0;
	m_nRetrieveSpeed = 0;
	m_tRetrieveStartTime = 0;
	m_tRetrieveStopTime = 0;
	m_tRetrieveInterval = 0;
	m_bLayoutToolTips = FALSE;
	m_nLayoutGridBackgroundColor = 0;
	ZeroMemory(&m_fntLayoutTitle, sizeof(LOGFONT));
	ZeroMemory(&m_fntLayoutItems, sizeof(LOGFONT));
	return TRUE;
}

CString CTCHistoryOpenDialog::GetTitle() CONST
{
	CString  szTitle[2];

	if (GetType() == TCHISTORY_TYPE_GLOBAL)
	{
		szTitle[0] = STRING(IDS_DISPLAY_TITLE_GLOBALTCHISTORY);
		return szTitle[0];
	}
	if (GetType() == TCHISTORY_TYPE_NORMAL)
	{
		GetDlgItem(IDC_TCHISTORY_OPEN_DISPLAY)->GetWindowText(szTitle[0]);
		szTitle[1].Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_DISPLAY_TITLE_TCHISTORY), (LPCTSTR)szTitle[0]);
		return szTitle[1];
	}
	return STRING(IDS_DISPLAY_TITLE_TCHISTORY);
}

UINT CTCHistoryOpenDialog::GetType() CONST
{
	return((IsDlgButtonChecked(IDC_TCHISTORY_OPEN_MODE_REALTIME)) ? TCHISTORY_TYPE_GLOBAL : TCHISTORY_TYPE_NORMAL);
}

UINT CTCHistoryOpenDialog::GetMode() CONST
{
	return((IsDlgButtonChecked(IDC_TCHISTORY_OPEN_MODE_REALTIME) || IsDlgButtonChecked(IDC_TCHISTORY_OPEN_MODE_HISTORY)) ? (IsDlgButtonChecked(IDC_TCHISTORY_OPEN_MODE_REALTIME)*DISPLAY_MODE_REALTIME + IsDlgButtonChecked(IDC_TCHISTORY_OPEN_MODE_HISTORY)*DISPLAY_MODE_HISTORY) : -1);
}

BOOL CTCHistoryOpenDialog::GetLayout(CString &szLayout) CONST
{
	if (GetType() == TCHISTORY_TYPE_GLOBAL)
	{
		szLayout = STRING(IDS_DISPLAY_TITLE_GLOBALTCHISTORY);
		return TRUE;
	}
	if (GetType() == TCHISTORY_TYPE_NORMAL)
	{
		GetDlgItem(IDC_TCHISTORY_OPEN_DISPLAY)->GetWindowText(szLayout);
		return((szLayout.GetLength() > 0) ? TRUE : FALSE);
	}
	return FALSE;
}
BOOL CTCHistoryOpenDialog::GetLayout(CString &szLayout, CUIntArray &nColumns) CONST
{
	for (nColumns.RemoveAll(); GetLayout(szLayout); )
	{
		if (m_nLayoutColumns.GetSize() > 0)
		{
			nColumns.Copy(m_nLayoutColumns);
			return TRUE;
		}
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_NUMBER) nColumns.Add(TCHISTORY_TITLEITEM_NUMBER);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_NAME) nColumns.Add(TCHISTORY_TITLEITEM_NAME);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_COMPUTER) nColumns.Add(TCHISTORY_TITLEITEM_COMPUTER);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_COMMANDSOURCE) nColumns.Add(TCHISTORY_TITLEITEM_COMMANDSOURCE);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_DESCRIPTION) nColumns.Add(TCHISTORY_TITLEITEM_DESCRIPTION);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_CATEGORY) nColumns.Add(TCHISTORY_TITLEITEM_CATEGORY);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_SUBSYSTEM) nColumns.Add(TCHISTORY_TITLEITEM_SUBSYSTEM);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_ARGUMENTS) nColumns.Add(TCHISTORY_TITLEITEM_ARGUMENTS);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_FLAGS) nColumns.Add(TCHISTORY_TITLEITEM_FLAGS);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_TCPACKET) nColumns.Add(TCHISTORY_TITLEITEM_TCPACKET);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_DISPATCHTIME) nColumns.Add(TCHISTORY_TITLEITEM_DISPATCHTIME);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_RELEASETIME) nColumns.Add(TCHISTORY_TITLEITEM_RELEASETIME);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_RELEASETIMEOFFSET) nColumns.Add(TCHISTORY_TITLEITEM_RELEASETIMEOFFSET);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_TRANSMISSIONTIME) nColumns.Add(TCHISTORY_TITLEITEM_TRANSMISSIONTIME);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_EXECUTIONTIME) nColumns.Add(TCHISTORY_TITLEITEM_EXECUTIONTIME);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_EXECUTIONTIMEOFFSET) nColumns.Add(TCHISTORY_TITLEITEM_EXECUTIONTIMEOFFSET);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_AUTHORIZATION) nColumns.Add(TCHISTORY_TITLEITEM_AUTHORIZATION);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_PTVTIMEWINDOW) nColumns.Add(TCHISTORY_TITLEITEM_PTVTIMEWINDOW);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_PTVCHECKS) nColumns.Add(TCHISTORY_TITLEITEM_PTVCHECKS);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_PTVRESULT) nColumns.Add(TCHISTORY_TITLEITEM_PTVRESULT);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_PEVCHECKS) nColumns.Add(TCHISTORY_TITLEITEM_PEVCHECKS);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_PEVRESULT) nColumns.Add(TCHISTORY_TITLEITEM_PEVRESULT);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_CEVTIMEWINDOW) nColumns.Add(TCHISTORY_TITLEITEM_CEVTIMEWINDOW);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_CEVCHECKS) nColumns.Add(TCHISTORY_TITLEITEM_CEVCHECKS);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_CEVRESULT) nColumns.Add(TCHISTORY_TITLEITEM_CEVRESULT);
		if (TCHISTORY_TITLEITEMS_DEFAULT & TCHISTORY_TITLEITEM_STATUS) nColumns.Add(TCHISTORY_TITLEITEM_STATUS);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryOpenDialog::GetLayoutListTitleFont(LPLOGFONT pTitleFont) CONST
{
	if (IsLayoutModified())
	{
		CopyMemory(pTitleFont, &m_fntLayoutTitle, sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryOpenDialog::GetLayoutListItemsFont(LPLOGFONT pItemsFont) CONST
{
	if (IsLayoutModified())
	{
		CopyMemory(pItemsFont, &m_fntLayoutItems, sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryOpenDialog::GetLayoutGridBackgroundColor(COLORREF &nColor) CONST
{
	if (IsLayoutModified())
	{
		nColor = m_nLayoutGridBackgroundColor;
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryOpenDialog::GetLayoutToolTipMode(BOOL &bEnable) CONST
{
	if (IsLayoutModified())
	{
		bEnable = m_bLayoutToolTips;
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryOpenDialog::IsLayoutModified() CONST
{
	LOGFONT  fntSample = { 0 };

	return((m_nLayoutColumns.GetSize() > 0 || memcmp(&m_fntLayoutTitle, &fntSample, sizeof(LOGFONT)) || memcmp(&m_fntLayoutItems, &fntSample, sizeof(LOGFONT)) || m_nLayoutGridBackgroundColor != 0 || m_bLayoutToolTips) ? TRUE : FALSE);
}

BOOL CTCHistoryOpenDialog::GetFilterMode(UINT &nMode) CONST
{
	if (IsFilteringModified())
	{
		nMode = m_nFilterMode[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryOpenDialog::GetFilterComputer(CString &szComputer) CONST
{
	if (IsFilteringModified())
	{
		szComputer = m_szFilterComputer;
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryOpenDialog::GetFilterTelecommandName(CString &szName) CONST
{
	if (IsFilteringModified())
	{
		szName = m_szFilterTelecommand[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryOpenDialog::GetFilterTelecommandSequence(CString &szSequence) CONST
{
	if (IsFilteringModified())
	{
		szSequence = m_szFilterTelecommand[1];
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryOpenDialog::GetFilterLimitation(UINT &nCount) CONST
{
	if (IsFilteringModified())
	{
		nCount = m_nFilterLimitation;
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryOpenDialog::GetFilterAutoload(UINT &nCount) CONST
{
	if (IsFilteringModified())
	{
		nCount = m_nFilterAutoload;
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryOpenDialog::GetFilterSortMode(UINT &nMode) CONST
{
	if (IsFilteringModified())
	{
		nMode = m_nFilterMode[1];
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryOpenDialog::IsFilteringModified() CONST
{
	return((m_nFilterMode[0] != 0 || m_nFilterMode[1] != 0 || !m_szFilterComputer.IsEmpty() || !m_szFilterTelecommand[0].IsEmpty() || !m_szFilterTelecommand[1].IsEmpty() || m_nFilterLimitation != 0 || m_nFilterAutoload != 0) ? TRUE : FALSE);
}

BOOL CTCHistoryOpenDialog::GetRetrieveMode(UINT &nMode) CONST
{
	nMode = m_nRetrieveMode;
	return TRUE;
}

BOOL CTCHistoryOpenDialog::GetRetrieveSpeed(UINT &nSpeed) CONST
{
	nSpeed = m_nRetrieveSpeed;
	return((m_nRetrieveMode & TCHISTORY_RETRIEVE_AUTOFORWARD) ? TRUE : FALSE);
}

BOOL CTCHistoryOpenDialog::GetRetrieveInterval(CTimeSpan &tInterval) CONST
{
	tInterval = m_tRetrieveInterval;
	return(((m_nRetrieveMode & TCHISTORY_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & TCHISTORY_RETRIEVE_MANUALFORWARD)) ? TRUE : FALSE);
}

BOOL CTCHistoryOpenDialog::GetRetrieveStartTime(CTimeKey &tTimeKey) CONST
{
	tTimeKey = m_tRetrieveStartTime;
	return(((m_nRetrieveMode & TCHISTORY_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & TCHISTORY_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & TCHISTORY_RETRIEVE_MANUALFORWARD)) ? TRUE : FALSE);
}

BOOL CTCHistoryOpenDialog::GetRetrieveStopTime(CTimeKey &tTimeKey) CONST
{
	tTimeKey = m_tRetrieveStopTime;
	return((((m_nRetrieveMode & TCHISTORY_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & TCHISTORY_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & TCHISTORY_RETRIEVE_MANUALFORWARD)) && (m_nRetrieveMode & TCHISTORY_RETRIEVE_STOPBYTIME)) ? TRUE : FALSE);
}

BOOL CTCHistoryOpenDialog::GetRetrieveFileName(CString &szFileName) CONST
{
	szFileName = ((m_nRetrieveMode & TCHISTORY_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & TCHISTORY_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & TCHISTORY_RETRIEVE_MANUALFORWARD)) ? (LPCTSTR)m_szRetrieveFileName : EMPTYSTRING;
	return !szFileName.IsEmpty();
}

BOOL CTCHistoryOpenDialog::IsRetrievingModified() CONST
{
	return((m_nRetrieveMode != 0) ? TRUE : FALSE);
}

BOOL CTCHistoryOpenDialog::GetPrintJobs(CTCHistoryPrintJobs &pPrintJobs) CONST
{
	CByteArray  nPrintInfo;

	return((IsPrintingModified()) ? pPrintJobs.Copy(&m_pPrintJobs) : pPrintJobs.Unmap(nPrintInfo));
}

BOOL CTCHistoryOpenDialog::IsPrintingModified() CONST
{
	return((m_pPrintJobs.GetSize() > 0) ? TRUE : FALSE);
}

CTCHistoryWnd *CTCHistoryOpenDialog::GetParent() CONST
{
	return((CTCHistoryWnd *)CDisplayDialog::GetParent());
}

VOID CTCHistoryOpenDialog::EnumLayouts()
{
	INT  nLayout;
	INT  nLayouts;
	CString  szTitle;
	CString  szLayout;
	CPtrArray  pLayouts;
	CDisplayWnd  *pDisplayWnd;

	for (nLayout = 0, nLayouts = (IsDlgButtonChecked(IDC_TCHISTORY_OPEN_MODE_HISTORY)) ? GetDisplayArea()->EnumDisplays(pLayouts) : 0, SendDlgItemMessage(IDC_TCHISTORY_OPEN_DISPLAY, CB_RESETCONTENT); nLayout < nLayouts; nLayout++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pLayouts.GetAt(nLayout)) && LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_TCHISTORY  &&  pDisplayWnd->GetScope() == DISPLAY_SCOPE_LOCAL)
		{
			for (szTitle.Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_DISPLAY_TITLE_TCHISTORY), EMPTYSTRING), pDisplayWnd->GetWindowText(szLayout); szLayout.Left(szTitle.GetLength()) == szTitle; )
			{
				SendDlgItemMessage(IDC_TCHISTORY_OPEN_DISPLAY, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szLayout.Mid(szTitle.GetLength()));
				break;
			}
		}
	}
}

BOOL CTCHistoryOpenDialog::Check(BOOL bModified) CONST
{
	CString  szTitle;

	return((GetLayout(szTitle) && (IsDlgButtonChecked(IDC_TCHISTORY_OPEN_MODE_REALTIME) || (IsDlgButtonChecked(IDC_TCHISTORY_OPEN_MODE_HISTORY) && !szTitle.IsEmpty() && (GetParent()->Find(MAKELONG(DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP, GetType()), GetMode(), szTitle) || IsRetrievingModified())))) ? TRUE : FALSE);
}

void CTCHistoryOpenDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCHistoryOpenDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCHistoryOpenDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCHistoryOpenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCHISTORY_OPEN_SETTINGS, OnSettings)
	ON_BN_CLICKED(IDC_TCHISTORY_OPEN_TYPE_NORMAL, OnTypeNormal)
	ON_BN_CLICKED(IDC_TCHISTORY_OPEN_MODE_REALTIME, OnRealtimeMode)
	ON_BN_CLICKED(IDC_TCHISTORY_OPEN_MODE_HISTORY, OnHistoryMode)
	ON_BN_CLICKED(IDC_TCHISTORY_OPEN_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_TCHISTORY_OPEN_DISPLAY, OnEditchangeTitle)
	ON_CBN_SELCHANGE(IDC_TCHISTORY_OPEN_DISPLAY, OnSelchangeTitle)
	ON_CBN_DBLCLK(IDC_TCHISTORY_OPEN_DISPLAY, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryOpenDialog message handlers

BOOL CTCHistoryOpenDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	CheckRadioButton(IDC_TCHISTORY_OPEN_TYPE_NORMAL, IDC_TCHISTORY_OPEN_TYPE_NORMAL, IDC_TCHISTORY_OPEN_TYPE_NORMAL);
	CheckDlgButton(IDC_TCHISTORY_OPEN_MODE_REALTIME, TRUE);
	CheckDlgButton(IDC_TCHISTORY_OPEN_MODE_HISTORY, FALSE);
	GetDlgItem(IDC_TCHISTORY_OPEN_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_OPEN_DISPLAY_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_OPEN_DISPLAY)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_OPEN_TYPE)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_OPEN_TYPE_NORMAL)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_OPEN_MODE)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_OPEN_MODE_REALTIME)->EnableWindow();
	GetDlgItem(IDC_TCHISTORY_OPEN_MODE_HISTORY)->EnableWindow();
	EnumLayouts();
	return TRUE;
}

void CTCHistoryOpenDialog::OnSettings()
{
	ReportEvent((m_dlgSettings.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CTCHistoryOpenDialog::OnTypeNormal()
{
	GetDlgItem(IDC_TCHISTORY_OPEN_DISPLAY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistoryOpenDialog::OnEditchangeTitle()
{
	CString  szTitle;

	GetDlgItem(IDC_TCHISTORY_OPEN_DISPLAY)->GetWindowText(szTitle);
	GetDlgItem(IDC_TCHISTORY_OPEN_SETTINGS)->EnableWindow((!GetParent()->Find(MAKELONG(DISPLAY_TYPE_TCHISTORY, GetType()), GetMode(), szTitle)) ? !szTitle.IsEmpty() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistoryOpenDialog::OnSelchangeTitle()
{
	CString  szTitle;

	GetDlgItem(IDC_TCHISTORY_OPEN_SETTINGS)->EnableWindow((!GetParent()->Find(MAKELONG(DISPLAY_TYPE_TCHISTORY, GetType()), GetMode(), (szTitle = Combobox_GetText(GetDlgItem(IDC_TCHISTORY_OPEN_DISPLAY), (INT)SendDlgItemMessage(IDC_TCHISTORY_OPEN_DISPLAY, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCHISTORY_OPEN_DISPLAY, CB_GETCURSEL)))))) ? !szTitle.IsEmpty() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistoryOpenDialog::OnRealtimeMode()
{
	SendDlgItemMessage(IDC_TCHISTORY_OPEN_DISPLAY, CB_RESETCONTENT);
	GetDlgItem(IDC_TCHISTORY_OPEN_DISPLAY_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_OPEN_DISPLAY)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCHISTORY_OPEN_SETTINGS)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCHistoryOpenDialog::OnHistoryMode()
{
	CString  szTitle;

	if (IsDlgButtonChecked(IDC_TCHISTORY_OPEN_MODE_HISTORY))
	{
		if (!GetDlgItem(IDC_TCHISTORY_OPEN_DISPLAY)->GetWindowTextLength() && !SendDlgItemMessage(IDC_TCHISTORY_OPEN_DISPLAY, CB_GETCOUNT))
		{
			GetDlgItem(IDC_TCHISTORY_OPEN_DISPLAY_STATIC)->EnableWindow();
			GetDlgItem(IDC_TCHISTORY_OPEN_DISPLAY)->EnableWindow();
			GetDlgItem(IDC_TCHISTORY_OPEN_SETTINGS)->EnableWindow(FALSE);
			EnumLayouts();
		}
		if (!IsWindow(m_dlgRetrievals.GetSafeHwnd()))
		{
			ReportEvent((m_dlgRetrievals.Create(this, (GetLayout(szTitle)) ? szTitle : STRING(IDS_WINDOW_UNKNOWNTITLE)) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
			GetDlgItem(IDC_TCHISTORY_OPEN_DISPLAY)->SetFocus();
		}
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

BOOL CTCHistoryOpenDialog::OnCloseSettingsDialog(UINT nCode)
{
	if (nCode == IDOK)
	{
		if (m_dlgSettings.IsLayoutModified())
		{
			m_dlgSettings.GetLayoutColumns(m_nLayoutColumns);
			m_dlgSettings.GetLayoutTitleFont(&m_fntLayoutTitle);
			m_dlgSettings.GetLayoutItemsFont(&m_fntLayoutItems);
			m_dlgSettings.GetLayoutToolTipMode(m_bLayoutToolTips);
			m_dlgSettings.GetLayoutGridBackgroundColor(m_nLayoutGridBackgroundColor);
		}
		if (m_dlgSettings.IsFilteringModified())
		{
			m_dlgSettings.GetFilterMode(m_nFilterMode[0]);
			m_dlgSettings.GetFilterComputer(m_szFilterComputer);
			m_dlgSettings.GetFilterTelecommandName(m_szFilterTelecommand[0]);
			m_dlgSettings.GetFilterTelecommandSequence(m_szFilterTelecommand[1]);
			m_dlgSettings.GetFilterLimitation(m_nFilterLimitation);
			m_dlgSettings.GetFilterAutoload(m_nFilterAutoload);
			m_dlgSettings.GetFilterSortMode(m_nFilterMode[1]);
		}
		if (m_dlgSettings.IsRetrievingModified())
		{
			m_dlgSettings.GetRetrieveMode(m_nRetrieveMode);
			m_dlgSettings.GetRetrieveFileName(m_szRetrieveFileName);
		}
		if (m_dlgSettings.IsPrintingModified()) m_dlgSettings.GetPrintJobs(m_pPrintJobs);
	}
	return TRUE;
}

BOOL CTCHistoryOpenDialog::OnCloseRetrieveDialog(UINT nCode)
{
	if (nCode == IDOK)
	{
		m_dlgRetrievals.GetMode(m_nRetrieveMode);
		m_dlgRetrievals.GetSpeed(m_nRetrieveSpeed);
		m_dlgRetrievals.GetStartTime(m_tRetrieveStartTime);
		m_dlgRetrievals.GetStopTime(m_tRetrieveStopTime);
	}
	if (nCode != IDOK || !m_nRetrieveMode)
	{
		CheckDlgButton(IDC_TCHISTORY_OPEN_MODE_REALTIME, TRUE);
		CheckDlgButton(IDC_TCHISTORY_OPEN_MODE_HISTORY, FALSE);
		SendDlgItemMessage(IDC_TCHISTORY_OPEN_DISPLAY, CB_RESETCONTENT);
		GetDlgItem(IDC_TCHISTORY_OPEN_DISPLAY_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_OPEN_DISPLAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCHISTORY_OPEN_SETTINGS)->EnableWindow(FALSE);
	}
	return TRUE;
}

void CTCHistoryOpenDialog::OnOK()
{
	CString  szTitle;
	CTCHistoryWnd  *pTCHistoryWnd[2];
	CHourglassCursor  cCursor;

	if ((pTCHistoryWnd[0] = GetParent()))
	{
		for (GetLayout(szTitle); (pTCHistoryWnd[1] = pTCHistoryWnd[0]->Find(MAKELONG(DISPLAY_TYPE_TCHISTORY, GetType()), GetMode(), szTitle)); )
		{
			GetDisplayArea()->ActivateDisplay(pTCHistoryWnd[1]);
			EndDialog(IDCANCEL);
			return;
		}
		if (!pTCHistoryWnd[0]->OnCloseOpenDialog(IDOK))
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

void CTCHistoryOpenDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	GetParent()->OnCloseOpenDialog(IDCANCEL);
	CDisplayDialog::OnCancel();
}

BOOL CTCHistoryOpenDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCHistoryOpenDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCHISTORYOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistoryRetrieveThread

IMPLEMENT_DYNCREATE(CTCHistoryRetrieveThread, CThread)

CTCHistoryRetrieveThread::CTCHistoryRetrieveThread() : CThread()
{
	m_nMode = 0;
	m_nSpeed = 0;
	m_tStartTime = 0;
	m_tStopTime = 0;
	m_pbFlag = (LPLONG)NULL;
	m_bInit[0] = (HANDLE)NULL;
	m_bInit[1] = (HANDLE)NULL;
	m_hAction[TCHISTORYRETRIEVETHREAD_ACTION_STOP] = (HANDLE)NULL;
	m_hAction[TCHISTORYRETRIEVETHREAD_ACTION_AUTOFORWARD] = (HANDLE)NULL;
	m_hAction[TCHISTORYRETRIEVETHREAD_ACTION_MANUALFORWARD] = (HANDLE)NULL;
	m_hAction[TCHISTORYRETRIEVETHREAD_ACTION_PSEUDOREALTIME] = (HANDLE)NULL;
}

BOOL CTCHistoryRetrieveThread::Start(CTCHistoryWnd *pParentWnd, HANDLE bInit, HANDLE bContinue, LPCTSTR pszFileName, UINT nMode, UINT nSpeed, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, LONG *pbFlag, HANDLE bRetrieveStop, HANDLE bRetrieveAutoForward, HANDLE bRetrieveManualForward, HANDLE bRetrievePseudoRealtime)
{
	m_nMode = nMode;
	m_nSpeed = nSpeed;
	m_pbFlag = pbFlag;
	m_bInit[0] = bInit;
	m_bInit[1] = bContinue;
	m_tStartTime = tStartTime;
	m_tStopTime = tStopTime;
	m_szFileName = pszFileName;
	m_hAction[TCHISTORYRETRIEVETHREAD_ACTION_STOP] = bRetrieveStop;
	m_hAction[TCHISTORYRETRIEVETHREAD_ACTION_AUTOFORWARD] = bRetrieveAutoForward;
	m_hAction[TCHISTORYRETRIEVETHREAD_ACTION_MANUALFORWARD] = bRetrieveManualForward;
	m_hAction[TCHISTORYRETRIEVETHREAD_ACTION_PSEUDOREALTIME] = bRetrievePseudoRealtime;
	return((ResetEvent(bInit)) ? CreateThread(pParentWnd, THREAD_PRIORITY_BELOW_NORMAL) : FALSE);
}

BOOL CTCHistoryRetrieveThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

int CTCHistoryRetrieveThread::Run()
{
	UINT  nAction;
	UINT  nResult;
	DWORD  dwResult;
	TIMETAG  tTime;
	CTimeKey  tTimeKey;
	CTimeTag  tTimeTag[2];
	CTCHistoryWnd  *pTCHistoryWnd = (CTCHistoryWnd *)GetThreadInfo();

	StartRetrieving();
	if (m_cTCEnvironment.Create(GetDatabase()))
	{
		if (m_cTCProcessEngine.Open(GetDatabase(), GetAccountSpacecraftName(), GetRetrieveFileName(), &m_cTCEnvironment))
		{
			for (BeginWaitCursor(), pTCHistoryWnd->SetRetrieveMode((m_nMode = m_nMode & ~(TCHISTORY_RETRIEVE_STOPPED | TCHISTORY_RETRIEVE_RELATIVE))), pTCHistoryWnd->Reset(&m_cTCEnvironment), SignalObjectAndWait(m_bInit[0], m_bInit[1], INFINITE, FALSE), nResult = m_cTCProcessEngine.ProcessTCData(GetDatabase(), &m_cTCEnvironment, (tTimeKey = GetRetrieveStartTime())), nAction = 0; (dwResult = Wait(0)) == WAIT_TIMEOUT && !pTCHistoryWnd->IsInitialized(); )
			{
				SwitchToThread();
				continue;
			}
			for (; dwResult == WAIT_TIMEOUT; BeginWaitCursor())
			{
				if ((GetRetrieveMode() & TCHISTORY_RETRIEVE_AUTOFORWARD) && !(GetRetrieveMode() & TCHISTORY_RETRIEVE_STOPPED))
				{
					for (; (nResult & HISTORYFILE_SUCCESS) && !(GetRetrieveMode() & TCHISTORY_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT && ((!(GetRetrieveMode() & TCHISTORY_RETRIEVE_EXACTTIME) && !pTCHistoryWnd->Update(tTimeKey, &m_cTCEnvironment, nResult)) || ((GetRetrieveMode() & TCHISTORY_RETRIEVE_EXACTTIME) && tTimeKey < GetRetrieveStartTime())); )
					{
						if (!((nResult = m_cTCProcessEngine.ReplayTCData(GetDatabase(), &m_cTCEnvironment, tTimeKey)) & HISTORYFILE_SUCCESS)) break;
						if (!(nResult & HISTORYFILE_TCUNIT) && !(nResult & HISTORYFILE_TCPARAMETERS))
						{
							ReportEvent(USER_INFORMATIONAL_TELECOMMANDHISTORYFILE_READ_NOTHING);
							pTCHistoryWnd->SetRetrieveMode(pTCHistoryWnd->GetRetrieveMode() | TCHISTORY_RETRIEVE_STOPPED);
							pTCHistoryWnd->UpdateBars();
							break;
						}
						if ((GetRetrieveMode() & TCHISTORY_RETRIEVE_STOPBYTIME) && GetRetrieveStopTime() < tTimeKey)
						{
							pTCHistoryWnd->SetRetrieveMode(pTCHistoryWnd->GetRetrieveMode() | TCHISTORY_RETRIEVE_STOPPED);
							pTCHistoryWnd->UpdateBars();
							break;
						}
					}
					EndWaitCursor();
					if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TCUNIT) || (nResult & HISTORYFILE_TCPARAMETERS))) || (GetRetrieveMode() & TCHISTORY_RETRIEVE_RELATIVE)) && (!(GetRetrieveMode() & TCHISTORY_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey) && dwResult == WAIT_TIMEOUT)
					{
						if ((!(GetRetrieveMode() & TCHISTORY_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & TCHISTORY_RETRIEVE_EXACTTIME) || pTCHistoryWnd->Update(tTimeKey, &m_cTCEnvironment, (nResult = (nResult | HISTORYFILE_SUCCESS | HISTORYFILE_TCPARAMETERS) & ~HISTORYFILE_TCUNIT) & (HISTORYFILE_SUCCESS | HISTORYFILE_TCPARAMETERS)) || TRUE)) || (GetRetrieveMode() & TCHISTORY_RETRIEVE_RELATIVE))
						{
							for (; (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 10 * (10 - GetRetrieveSpeed())*(10 - GetRetrieveSpeed()))) == WAIT_TIMEOUT; )
							{
								if (((nResult = m_cTCProcessEngine.ReplayTCData(GetDatabase(), &m_cTCEnvironment, tTimeKey)) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TCUNIT) || (nResult & HISTORYFILE_TCPARAMETERS)))
								{
									if (!(GetRetrieveMode() & TCHISTORY_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey)
									{
										pTCHistoryWnd->Update(tTimeKey, &m_cTCEnvironment, nResult);
										continue;
									}
								}
								if (nResult & HISTORYFILE_SUCCESS)
								{
									ReportEvent((GetRetrieveMode() & TCHISTORY_RETRIEVE_STOPBYEND) ? USER_INFORMATIONAL_TELECOMMANDHISTORYFILE_READ_NOTHING : USER_NOERROR);
									pTCHistoryWnd->SetRetrieveMode(pTCHistoryWnd->GetRetrieveMode() | TCHISTORY_RETRIEVE_STOPPED);
									pTCHistoryWnd->UpdateBars();
								}
								break;
							}
						}
					}
					if (!(nResult & HISTORYFILE_SUCCESS))
					{
						ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELECOMMANDHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELECOMMANDHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELECOMMANDHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELECOMMANDHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELECOMMANDHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
						pTCHistoryWnd->SetRetrieveMode(pTCHistoryWnd->GetRetrieveMode() | TCHISTORY_RETRIEVE_STOPPED);
						pTCHistoryWnd->Reset(&m_cTCEnvironment);
						pTCHistoryWnd->UpdateBars();
						break;
					}
				}
				if ((GetRetrieveMode() & TCHISTORY_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & TCHISTORY_RETRIEVE_STOPPED))
				{
					for (; (nResult & HISTORYFILE_SUCCESS) && !(GetRetrieveMode() & TCHISTORY_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT && ((!(GetRetrieveMode() & TCHISTORY_RETRIEVE_EXACTTIME) && !pTCHistoryWnd->Update(tTimeKey, &m_cTCEnvironment, nResult)) || ((GetRetrieveMode() & TCHISTORY_RETRIEVE_EXACTTIME) && tTimeKey < GetRetrieveStartTime())); )
					{
						if (!((nResult = m_cTCProcessEngine.ReplayTCData(GetDatabase(), &m_cTCEnvironment, tTimeKey)) & HISTORYFILE_SUCCESS)) break;
						if (!(nResult & HISTORYFILE_TCUNIT) && !(nResult & HISTORYFILE_TCPARAMETERS))
						{
							ReportEvent(USER_INFORMATIONAL_TELECOMMANDHISTORYFILE_READ_NOTHING);
							pTCHistoryWnd->SetRetrieveMode(pTCHistoryWnd->GetRetrieveMode() | TCHISTORY_RETRIEVE_STOPPED);
							pTCHistoryWnd->UpdateBars();
							break;
						}
					}
					EndWaitCursor();
					if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TCUNIT) || (nResult & HISTORYFILE_TCPARAMETERS))) || (GetRetrieveMode() & TCHISTORY_RETRIEVE_RELATIVE)) && dwResult == WAIT_TIMEOUT)
					{
						if ((!(GetRetrieveMode() & TCHISTORY_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & TCHISTORY_RETRIEVE_EXACTTIME) || pTCHistoryWnd->Update(tTimeKey, &m_cTCEnvironment, (nResult = (nResult | HISTORYFILE_SUCCESS | HISTORYFILE_TCPARAMETERS) & ~HISTORYFILE_TCUNIT) & (HISTORYFILE_SUCCESS | HISTORYFILE_TCPARAMETERS)) || TRUE)) || (GetRetrieveMode() & TCHISTORY_RETRIEVE_RELATIVE))
						{
							for (; (dwResult = (!(GetRetrieveMode() & TCHISTORY_RETRIEVE_RELATIVE) || nAction != TCHISTORYRETRIEVETHREAD_ACTION_MANUALFORWARD) ? Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, INFINITE) : (WAIT_OBJECT_0 + nAction + 1)) == WAIT_OBJECT_0 + TCHISTORYRETRIEVETHREAD_ACTION_MANUALFORWARD + 1; EndWaitCursor())
							{
								for (BeginWaitCursor(TRUE); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT; )
								{
									if (((nResult = m_cTCProcessEngine.ReplayTCData(GetDatabase(), &m_cTCEnvironment, tTimeKey)) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TCUNIT) || (nResult & HISTORYFILE_TCPARAMETERS)))
									{
										if (pTCHistoryWnd->Update(tTimeKey, &m_cTCEnvironment, nResult)) break;
										continue;
									}
									if (nResult & HISTORYFILE_SUCCESS)
									{
										if (!(nResult & HISTORYFILE_TCUNIT) && !(nResult & HISTORYFILE_TCPARAMETERS))
										{
											ReportEvent(USER_INFORMATIONAL_TELECOMMANDHISTORYFILE_READ_NOTHING);
											pTCHistoryWnd->SetRetrieveMode(pTCHistoryWnd->GetRetrieveMode() | TCHISTORY_RETRIEVE_STOPPED);
											pTCHistoryWnd->UpdateBars();
										}
									}
									break;
								}
								if (!(nResult & HISTORYFILE_SUCCESS) || (!(nResult & HISTORYFILE_TCUNIT) && !(nResult & HISTORYFILE_TCPARAMETERS)) || dwResult == WAIT_OBJECT_0)
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
						ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELECOMMANDHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELECOMMANDHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELECOMMANDHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELECOMMANDHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELECOMMANDHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
						pTCHistoryWnd->SetRetrieveMode(pTCHistoryWnd->GetRetrieveMode() | TCHISTORY_RETRIEVE_STOPPED);
						pTCHistoryWnd->Reset(&m_cTCEnvironment);
						pTCHistoryWnd->UpdateBars();
						break;
					}
				}
				if ((GetRetrieveMode() & TCHISTORY_RETRIEVE_PSEUDOREALTIME) && !(GetRetrieveMode() & TCHISTORY_RETRIEVE_STOPPED))
				{
					for (; (nResult & HISTORYFILE_SUCCESS) && !(GetRetrieveMode() & TCHISTORY_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT && ((!(GetRetrieveMode() & TCHISTORY_RETRIEVE_EXACTTIME) && !pTCHistoryWnd->Update(tTimeKey, &m_cTCEnvironment, nResult)) || ((GetRetrieveMode() & TCHISTORY_RETRIEVE_EXACTTIME) && tTimeKey < GetRetrieveStartTime())); )
					{
						if (!((nResult = m_cTCProcessEngine.ReplayTCData(GetDatabase(), &m_cTCEnvironment, tTimeKey)) & HISTORYFILE_SUCCESS)) break;
						if (!(nResult & HISTORYFILE_TCUNIT) && !(nResult & HISTORYFILE_TCPARAMETERS))
						{
							ReportEvent(USER_INFORMATIONAL_TELECOMMANDHISTORYFILE_READ_NOTHING);
							pTCHistoryWnd->SetRetrieveMode(pTCHistoryWnd->GetRetrieveMode() | TCHISTORY_RETRIEVE_STOPPED);
							pTCHistoryWnd->UpdateBars();
							break;
						}
						if ((GetRetrieveMode() & TCHISTORY_RETRIEVE_STOPBYTIME) && GetRetrieveStopTime() < tTimeKey)
						{
							pTCHistoryWnd->SetRetrieveMode(pTCHistoryWnd->GetRetrieveMode() | TCHISTORY_RETRIEVE_STOPPED);
							pTCHistoryWnd->UpdateBars();
							break;
						}
					}
					EndWaitCursor();
					if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TCUNIT) || (nResult & HISTORYFILE_TCPARAMETERS))) || (GetRetrieveMode() & TCHISTORY_RETRIEVE_RELATIVE)) && (!(GetRetrieveMode() & TCHISTORY_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey) && dwResult == WAIT_TIMEOUT)
					{
						if ((!(GetRetrieveMode() & TCHISTORY_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & TCHISTORY_RETRIEVE_EXACTTIME) || pTCHistoryWnd->Update(tTimeKey, &m_cTCEnvironment, (nResult = (nResult | HISTORYFILE_SUCCESS | HISTORYFILE_TCPARAMETERS) & ~HISTORYFILE_TCUNIT) & (HISTORYFILE_SUCCESS | HISTORYFILE_TCPARAMETERS)) || TRUE)) || (GetRetrieveMode() & TCHISTORY_RETRIEVE_RELATIVE))
						{
							for (tTimeTag[0] = ((nResult & HISTORYFILE_TCUNIT) || (nResult & HISTORYFILE_TCPARAMETERS)) ? ((nResult & HISTORYFILE_TCUNIT) ? m_cTCEnvironment.GetTCUnit()->GetTimeTag() : CTimeTag(tTimeKey)) : CTimeTag(tTimeKey), tTimeTag[1] = CTimeTag(), tTime = CTimeTag().GetTime(); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT; tTime = CTimeTag().GetTime())
							{
								if (((nResult = m_cTCProcessEngine.ReplayTCData(GetDatabase(), &m_cTCEnvironment, tTimeKey)) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TCUNIT) || (nResult & HISTORYFILE_TCPARAMETERS)))
								{
									if ((dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, (((nResult & HISTORYFILE_TCUNIT) && tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + m_cTCEnvironment.GetTCUnit()->GetTimeTag().GetTime() > tTime) || ((nResult & HISTORYFILE_TCPARAMETERS) && tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + CTimeTag(tTimeKey).GetTime() > tTime)) ? ((nResult & HISTORYFILE_TCUNIT) ? (DWORD)((tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + m_cTCEnvironment.GetTCUnit()->GetTimeTag().GetTime() - tTime) / 1000) : (DWORD)((tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + CTimeTag(tTimeKey).GetTime() - tTime) / 1000)) : 0)) != WAIT_TIMEOUT) break;
									if ((!(GetRetrieveMode() & TCHISTORY_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey) && ((nResult & HISTORYFILE_SYNCHRONIZE) || !tTimeTag[0].GetTime()))
									{
										tTimeTag[0] = (nResult & HISTORYFILE_TCUNIT) ? m_cTCEnvironment.GetTCUnit()->GetTimeTag() : CTimeTag(tTimeKey);
										tTimeTag[1] = tTime = CTimeTag().GetTime();
									}
									if (!(GetRetrieveMode() & TCHISTORY_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey)
									{
										pTCHistoryWnd->Update(tTimeKey, &m_cTCEnvironment, nResult);
										continue;
									}
								}
								if (nResult & HISTORYFILE_SUCCESS)
								{
									ReportEvent((GetRetrieveMode() & TCHISTORY_RETRIEVE_STOPBYEND) ? USER_INFORMATIONAL_TELECOMMANDHISTORYFILE_READ_NOTHING : USER_NOERROR);
									pTCHistoryWnd->SetRetrieveMode(pTCHistoryWnd->GetRetrieveMode() | TCHISTORY_RETRIEVE_STOPPED);
									pTCHistoryWnd->UpdateBars();
								}
								break;
							}
						}
					}
					if (!(nResult & HISTORYFILE_SUCCESS))
					{
						ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELECOMMANDHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
						pTCHistoryWnd->SetRetrieveMode(pTCHistoryWnd->GetRetrieveMode() | TCHISTORY_RETRIEVE_STOPPED);
						pTCHistoryWnd->Reset(&m_cTCEnvironment);
						pTCHistoryWnd->UpdateBars();
						break;
					}
				}
				if ((GetRetrieveMode() & TCHISTORY_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & TCHISTORY_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & TCHISTORY_RETRIEVE_PSEUDOREALTIME))
				{
					while ((dwResult = ((dwResult < WAIT_OBJECT_0 + TCHISTORYRETRIEVETHREAD_ACTION_AUTOFORWARD + 1 || dwResult > WAIT_OBJECT_0 + TCHISTORYRETRIEVETHREAD_ACTION_PSEUDOREALTIME + 1) && dwResult != WAIT_OBJECT_0) ? Wait(m_hAction, TCHISTORYRETRIEVETHREAD_ACTION_TYPES, FALSE, INFINITE, FALSE) : dwResult) == WAIT_OBJECT_0 + TCHISTORYRETRIEVETHREAD_ACTION_STOP + 1)
					{
						m_nMode = (GetRetrieveMode() & (TCHISTORY_RETRIEVE_STOPBYTIME | TCHISTORY_RETRIEVE_STOPBYEND)) | TCHISTORY_RETRIEVE_STOPPED | TCHISTORY_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (TCHISTORY_RETRIEVE_STOPBYTIME | TCHISTORY_RETRIEVE_STOPBYEND)) == 0) ? TCHISTORY_RETRIEVE_STOPBYEND : 0;
						pTCHistoryWnd->SetRetrieveMode(m_nMode);
						pTCHistoryWnd->UpdateBars();
					}
					if (dwResult == WAIT_OBJECT_0 + TCHISTORYRETRIEVETHREAD_ACTION_AUTOFORWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (TCHISTORY_RETRIEVE_STOPBYTIME | TCHISTORY_RETRIEVE_STOPBYEND)) | TCHISTORY_RETRIEVE_AUTOFORWARD | TCHISTORY_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (TCHISTORY_RETRIEVE_STOPBYTIME | TCHISTORY_RETRIEVE_STOPBYEND)) == 0) ? TCHISTORY_RETRIEVE_STOPBYEND : 0;
						nAction = TCHISTORYRETRIEVETHREAD_ACTION_AUTOFORWARD;
						pTCHistoryWnd->SetRetrieveMode(m_nMode);
						pTCHistoryWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + TCHISTORYRETRIEVETHREAD_ACTION_MANUALFORWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (TCHISTORY_RETRIEVE_STOPBYTIME | TCHISTORY_RETRIEVE_STOPBYEND)) | TCHISTORY_RETRIEVE_MANUALFORWARD | TCHISTORY_RETRIEVE_RELATIVE;
						nAction = TCHISTORYRETRIEVETHREAD_ACTION_MANUALFORWARD;
						pTCHistoryWnd->SetRetrieveMode(m_nMode);
						pTCHistoryWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + TCHISTORYRETRIEVETHREAD_ACTION_PSEUDOREALTIME + 1)
					{
						m_nMode = (GetRetrieveMode() & (TCHISTORY_RETRIEVE_STOPBYTIME | TCHISTORY_RETRIEVE_STOPBYEND)) | TCHISTORY_RETRIEVE_PSEUDOREALTIME | TCHISTORY_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (TCHISTORY_RETRIEVE_STOPBYTIME | TCHISTORY_RETRIEVE_STOPBYEND)) == 0) ? TCHISTORY_RETRIEVE_STOPBYEND : 0;
						nAction = TCHISTORYRETRIEVETHREAD_ACTION_PSEUDOREALTIME;
						pTCHistoryWnd->SetRetrieveMode(m_nMode);
						pTCHistoryWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
				}
				break;
			}
			m_cTCProcessEngine.Close();
		}
		else
		{
			SignalObjectAndWait(m_bInit[0], m_bInit[1], INFINITE, FALSE);
			ReportEvent(SYSTEM_WARNING_TELECOMMANDHISTORYFILE_FAILURE);
		}
		m_cTCEnvironment.Destroy();
	}
	else
	{
		SignalObjectAndWait(m_bInit[0], m_bInit[1], INFINITE, FALSE);
		ReportEvent(SYSTEM_WARNING_TELECOMMANDHISTORYFILE_FAILURE);
	}
	StopRetrieving();
	EndWaitCursor();
	return 0;
}

VOID CTCHistoryRetrieveThread::StartRetrieving()
{
	InterlockedExchange(m_pbFlag, TRUE);
}

VOID CTCHistoryRetrieveThread::StopRetrieving()
{
	InterlockedExchange(m_pbFlag, FALSE);
}

UINT CTCHistoryRetrieveThread::GetRetrieveMode() CONST
{
	return((IsThreadActive()) ? m_nMode : 0);
}

UINT CTCHistoryRetrieveThread::GetRetrieveSpeed() CONST
{
	return((IsThreadActive()) ? m_nSpeed : 0);
}

CTimeKey CTCHistoryRetrieveThread::GetRetrieveStartTime() CONST
{
	return((IsThreadActive()) ? m_tStartTime : 0);
}

CTimeKey CTCHistoryRetrieveThread::GetRetrieveStopTime() CONST
{
	return((IsThreadActive()) ? m_tStopTime : 0);
}

CString CTCHistoryRetrieveThread::GetRetrieveFileName() CONST
{
	return((IsThreadActive()) ? (LPCTSTR)m_szFileName : EMPTYSTRING);
}

VOID CTCHistoryRetrieveThread::BeginWaitCursor(BOOL bForced)
{
	POINT  ptCursor;
	CTCHistoryWnd  *pTCHistoryWnd;
	CHourglassCursor  cCursor;

	for (GetCursorPos(&ptCursor), InterlockedExchange(m_pbFlag, MAKELONG(TRUE, ((m_nMode & TCHISTORY_RETRIEVE_RELATIVE) != TCHISTORY_RETRIEVE_RELATIVE || bForced) ? TRUE : FALSE)), SetCursorPos(ptCursor.x, ptCursor.y); (pTCHistoryWnd = (CTCHistoryWnd *)GetThreadInfo()); )
	{
		pTCHistoryWnd->UpdateBars();
		break;
	}
}

VOID CTCHistoryRetrieveThread::EndWaitCursor()
{
	POINT  ptCursor;
	CTCHistoryWnd  *pTCHistoryWnd;
	CHourglassCursor  cCursor;

	for (GetCursorPos(&ptCursor), InterlockedExchange(m_pbFlag, LOWORD(*m_pbFlag)), SetCursorPos(ptCursor.x, ptCursor.y); (pTCHistoryWnd = (CTCHistoryWnd *)GetThreadInfo()); )
	{
		pTCHistoryWnd->UpdateBars();
		break;
	}
}

BEGIN_MESSAGE_MAP(CTCHistoryRetrieveThread, CThread)
	//{{AFX_MSG_MAP(CTCHistoryRetrieveThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryRetrieveThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CTCHistoryToolBar

IMPLEMENT_DYNCREATE(CTCHistoryToolBar, CDisplayToolBar)

CTCHistoryToolBar::CTCHistoryToolBar() : CDisplayToolBar()
{
	return;
}

BEGIN_MESSAGE_MAP(CTCHistoryToolBar, CDisplayToolBar)
	//{{AFX_MSG_MAP(CTCHistoryToolBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryToolBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CTCHistoryStatusBar

IMPLEMENT_DYNCREATE(CTCHistoryStatusBar, CDisplayStatusBar)

CTCHistoryStatusBar::CTCHistoryStatusBar() : CDisplayStatusBar()
{
	return;
}

BOOL CTCHistoryStatusBar::SetIndicators(CONST UINT *pPanesID, INT nCount)
{
	INT  nIndex;
	CRect  rPane;
	CString  szPane;
	CToolInfo  cToolInfo;
	CDisplayLock  cLock(this);

	if (CDisplayStatusBar::SetIndicators(pPanesID, nCount))
	{
		if (CommandToIndex(ID_TCHISTORY_STATUSBAR_MESSAGEPANE) >= 0)
		{
			szPane.Format(STRING(IDS_TCHISTORY_STATUSBAR_DATAMESSAGES), (UINT)-1);
			SetPaneInfo(CommandToIndex(ID_TCHISTORY_STATUSBAR_MESSAGEPANE), ID_TCHISTORY_STATUSBAR_MESSAGEPANE, SBPS_NOBORDERS | SBPS_STRETCH, CalcPaneWidth(szPane));
		}
		if (!IsWindow(m_wndToolTip.GetSafeHwnd()))
		{
			m_wndToolTip.Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
			SetClassLongPtr(m_wndToolTip.GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip.GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
		}
		if (IsWindow(m_wndToolTip.GetSafeHwnd()))
		{
			if ((nIndex = CommandToIndex(ID_TCHISTORY_STATUSBAR_MODEPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_TCHISTORY_STATUSBAR_MODEPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_TCHISTORY_STATUSBAR_MODEPANE);
					break;
				}
			}
			if ((nIndex = CommandToIndex(ID_TCHISTORY_STATUSBAR_TYPEPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_TCHISTORY_STATUSBAR_TYPEPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_TCHISTORY_STATUSBAR_TYPEPANE);
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

CTCHistoryWnd *CTCHistoryStatusBar::GetParent() CONST
{
	return((CTCHistoryWnd *)CDisplayStatusBar::GetParent());
}

BEGIN_MESSAGE_MAP(CTCHistoryStatusBar, CDisplayStatusBar)
	//{{AFX_MSG_MAP(CTCHistoryStatusBar)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryStatusBar message handlers

void CTCHistoryStatusBar::OnPaint()
{
	INT  nIndex;
	RECT  rPane;
	CToolInfo  cToolInfo;

	for (CDisplayStatusBar::OnPaint(); IsWindow(m_wndToolTip.GetSafeHwnd()); )
	{
		if ((nIndex = CommandToIndex(ID_TCHISTORY_STATUSBAR_MODEPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_TCHISTORY_STATUSBAR_MODEPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		if ((nIndex = CommandToIndex(ID_TCHISTORY_STATUSBAR_TYPEPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_TCHISTORY_STATUSBAR_TYPEPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		break;
	}
}

void CTCHistoryStatusBar::OnMouseMove(UINT nFlags, CPoint point)
{
	MSG  sMsg;

	if (IsWindow(m_wndToolTip.GetSafeHwnd()))
	{
		CopyMemory(&sMsg, GetCurrentMessage(), sizeof(MSG));
		m_wndToolTip.RelayEvent(&sMsg);
	}
	CDisplayStatusBar::OnMouseMove(nFlags, point);
}

BOOL CTCHistoryStatusBar::OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult)
{
	TOOLTIPTEXT  *pToolTipInfo = (TOOLTIPTEXT *)pNotifyInfo;

	switch (pNotifyInfo->idFrom)
	{
	case ID_TCHISTORY_STATUSBAR_MODEPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_TCHISTORY_STATUSBAR_MODEPANE);
	return TRUE;
	}
	case ID_TCHISTORY_STATUSBAR_TYPEPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_TCHISTORY_STATUSBAR_TYPEPANE);
	return TRUE;
	}
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistoryToolTip

IMPLEMENT_DYNCREATE(CTCHistoryToolTip, CDisplayToolTip)

CTCHistoryToolTip::CTCHistoryToolTip() : CDisplayToolTip()
{
	return;
}

BEGIN_MESSAGE_MAP(CTCHistoryToolTip, CDisplayToolTip)
	//{{AFX_MSG_MAP(CTCHistoryToolTip)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryToolTip message handlers


/////////////////////////////////////////////////////////////////////////////
// CTCHistoryView

IMPLEMENT_DYNCREATE(CTCHistoryView, CTextView)

CTCHistoryView::CTCHistoryView() : CTextView()
{
	m_nSearchIndex = -1;
	m_nFilterMode[0] = 0;
	m_nFilterMode[1] = 0;
	m_nFilterAutoload = 0;
	m_nFilterLimitation = 0;
	m_nClipboardFormat = 0;
	m_bProperties = FALSE;
	m_bFullViewMode = FALSE;
	m_sizeAlertSymbols.cx = 0;
	m_sizeAlertSymbols.cy = 0;
	m_sizeFlagSymbols.cx = 0;
	m_sizeFlagSymbols.cy = 0;
	m_sizeResultSymbols.cx = 0;
	m_sizeResultSymbols.cy = 0;
	m_sizeCheckFlagSymbols.cx = 0;
	m_sizeCheckFlagSymbols.cy = 0;
	m_nBackgroundColor[0] = VGA_COLOR_GRAY;
	m_nBackgroundColor[1] = GetSysColor(COLOR_WINDOW);
	m_nStatusColors.SetAtGrow(TCHISTORYITEM_STATUSCOLOR_NONE, GetSysColor(COLOR_WINDOW));
	m_nStatusColors.SetAtGrow(TCHISTORYITEM_STATUSCOLOR_IDLE, RGB(0, 64, 255));
	m_nStatusColors.SetAtGrow(TCHISTORYITEM_STATUSCOLOR_PENDING, VGA_COLOR_YELLOW);
	m_nStatusColors.SetAtGrow(TCHISTORYITEM_STATUSCOLOR_PASSED, VGA_COLOR_GREEN);
	m_nStatusColors.SetAtGrow(TCHISTORYITEM_STATUSCOLOR_NOTPASSED, VGA_COLOR_RED);
	m_hToolTipCursor = (HCURSOR)NULL;
	m_bToolTips = TRUE;
}

BOOL CTCHistoryView::Create(CWnd *pParentWnd, DWORD dwStyle)
{
	if (CTextView::Create(pParentWnd, CRect(0, 0, 0, 0), dwStyle))
	{
		SetTextSpacings(1, 1);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryView::SetLayout(LPCTSTR pszLayout)
{
	return SetLayout(pszLayout, TCHISTORY_TITLEITEMS_DEFAULT);
}
BOOL CTCHistoryView::SetLayout(LPCTSTR pszLayout, UINT nColumns)
{
	CUIntArray  nTitleItems;

	nTitleItems.Add(TCHISTORY_TITLEITEM_NUMBER);
	if (nColumns & TCHISTORY_TITLEITEM_NAME) nTitleItems.Add(TCHISTORY_TITLEITEM_NAME);
	if (nColumns & TCHISTORY_TITLEITEM_COMPUTER) nTitleItems.Add(TCHISTORY_TITLEITEM_COMPUTER);
	if (nColumns & TCHISTORY_TITLEITEM_COMMANDSOURCE) nTitleItems.Add(TCHISTORY_TITLEITEM_COMMANDSOURCE);
	if (nColumns & TCHISTORY_TITLEITEM_DESCRIPTION) nTitleItems.Add(TCHISTORY_TITLEITEM_DESCRIPTION);
	if (nColumns & TCHISTORY_TITLEITEM_CATEGORY) nTitleItems.Add(TCHISTORY_TITLEITEM_CATEGORY);
	if (nColumns & TCHISTORY_TITLEITEM_SUBSYSTEM) nTitleItems.Add(TCHISTORY_TITLEITEM_SUBSYSTEM);
	if (nColumns & TCHISTORY_TITLEITEM_ARGUMENTS) nTitleItems.Add(TCHISTORY_TITLEITEM_ARGUMENTS);
	if (nColumns & TCHISTORY_TITLEITEM_FLAGS) nTitleItems.Add(TCHISTORY_TITLEITEM_FLAGS);
	if (nColumns & TCHISTORY_TITLEITEM_TCPACKET) nTitleItems.Add(TCHISTORY_TITLEITEM_TCPACKET);
	if (nColumns & TCHISTORY_TITLEITEM_DISPATCHTIME) nTitleItems.Add(TCHISTORY_TITLEITEM_DISPATCHTIME);
	if (nColumns & TCHISTORY_TITLEITEM_RELEASETIME) nTitleItems.Add(TCHISTORY_TITLEITEM_RELEASETIME);
	if (nColumns & TCHISTORY_TITLEITEM_RELEASETIMEOFFSET) nTitleItems.Add(TCHISTORY_TITLEITEM_RELEASETIMEOFFSET);
	if (nColumns & TCHISTORY_TITLEITEM_TRANSMISSIONTIME) nTitleItems.Add(TCHISTORY_TITLEITEM_TRANSMISSIONTIME);
	if (nColumns & TCHISTORY_TITLEITEM_EXECUTIONTIME) nTitleItems.Add(TCHISTORY_TITLEITEM_EXECUTIONTIME);
	if (nColumns & TCHISTORY_TITLEITEM_EXECUTIONTIMEOFFSET) nTitleItems.Add(TCHISTORY_TITLEITEM_EXECUTIONTIMEOFFSET);
	if (nColumns & TCHISTORY_TITLEITEM_AUTHORIZATION) nTitleItems.Add(TCHISTORY_TITLEITEM_AUTHORIZATION);
	if (nColumns & TCHISTORY_TITLEITEM_PTVTIMEWINDOW) nTitleItems.Add(TCHISTORY_TITLEITEM_PTVTIMEWINDOW);
	if (nColumns & TCHISTORY_TITLEITEM_PTVCHECKS) nTitleItems.Add(TCHISTORY_TITLEITEM_PTVCHECKS);
	if (nColumns & TCHISTORY_TITLEITEM_PTVRESULT) nTitleItems.Add(TCHISTORY_TITLEITEM_PTVRESULT);
	if (nColumns & TCHISTORY_TITLEITEM_PEVCHECKS) nTitleItems.Add(TCHISTORY_TITLEITEM_PEVCHECKS);
	if (nColumns & TCHISTORY_TITLEITEM_PEVRESULT) nTitleItems.Add(TCHISTORY_TITLEITEM_PEVRESULT);
	if (nColumns & TCHISTORY_TITLEITEM_CEVTIMEWINDOW) nTitleItems.Add(TCHISTORY_TITLEITEM_CEVTIMEWINDOW);
	if (nColumns & TCHISTORY_TITLEITEM_CEVCHECKS) nTitleItems.Add(TCHISTORY_TITLEITEM_CEVCHECKS);
	if (nColumns & TCHISTORY_TITLEITEM_CEVRESULT) nTitleItems.Add(TCHISTORY_TITLEITEM_CEVRESULT);
	if (nColumns & TCHISTORY_TITLEITEM_STATUS) nTitleItems.Add(TCHISTORY_TITLEITEM_STATUS);
	return SetLayout(pszLayout, nTitleItems);
}
BOOL CTCHistoryView::SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns)
{
	CUIntArray  nWidths;

	return((CalcColumnsWidth(nColumns, nWidths)) ? SetLayout(pszLayout, nColumns, nWidths) : FALSE);
}
BOOL CTCHistoryView::SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths)
{
	INT  nIndex;
	INT  nCount;
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	for (nIndex = 0, nCount = (LookupColumnsName(nColumns, szColumns) && SetColumns(szColumns, nWidths)) ? (INT)nColumns.GetSize() : -1, m_szLayout = pszLayout; nIndex < nCount; nIndex++)
	{
		SetColumnColor(nIndex, LookupColumnColor(nColumns.GetAt(nIndex)), IsWindow(GetSafeHwnd()));
		continue;
	}
	return((nIndex == nCount) ? TRUE : FALSE);
}

BOOL CTCHistoryView::GetLayout(CString &szLayout) CONST
{
	CUIntArray  nColumns;

	return GetLayout(szLayout, nColumns);
}
BOOL CTCHistoryView::GetLayout(CString &szLayout, CUIntArray &nColumns) CONST
{
	CUIntArray  nWidths;

	return GetLayout(szLayout, nColumns, nWidths);
}
BOOL CTCHistoryView::GetLayout(CString &szLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST
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

BOOL CTCHistoryView::SetListTitleFont(CFont *pFont)
{
	return CTextView::SetTitleFont(pFont);
}
BOOL CTCHistoryView::SetListTitleFont(CONST LOGFONT *plfFont)
{
	return CTextView::SetTitleFont(plfFont);
}

BOOL CTCHistoryView::GetListTitleFont(CFont *pFont) CONST
{
	return CTextView::GetTitleFont(pFont);
}
BOOL CTCHistoryView::GetListTitleFont(LOGFONT *plfFont) CONST
{
	return CTextView::GetTitleFont(plfFont);
}

BOOL CTCHistoryView::SetListItemsFont(CFont *pFont)
{
	LOGFONT  lfFont;

	return((pFont->GetLogFont(&lfFont) > 0) ? SetListItemsFont(&lfFont) : FALSE);
}
BOOL CTCHistoryView::SetListItemsFont(CONST LOGFONT *plfFont)
{
	CTextViewLock  cLock(this);

	if (CTextView::SetTextFont(plfFont))
	{
		SetTextSpacings(max(LOWORD(GetTextSpacings()), 1), max(HIWORD(GetTextSpacings()), 1));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryView::GetListItemsFont(CFont *pFont) CONST
{
	return CTextView::GetTextFont(pFont);
}
BOOL CTCHistoryView::GetListItemsFont(LOGFONT *plfFont) CONST
{
	return CTextView::GetTextFont(plfFont);
}

BOOL CTCHistoryView::SetGridBackgroundColor(COLORREF nColor)
{
	m_nBackgroundColor[0] = nColor;
	return TRUE;
}

BOOL CTCHistoryView::GetGridBackgroundColor(COLORREF &nColor) CONST
{
	nColor = m_nBackgroundColor[0];
	return TRUE;
}

BOOL CTCHistoryView::EnableFullViewMode(BOOL bEnable)
{
	INT  nColumn;
	INT  nColumns;
	CString  szColumn;
	CTextViewLock  cLock(this);

	for (nColumn = 0, nColumns = (INT)m_wndHeaderCtrl.m_szColumnsText.GetSize(), m_bFullViewMode = bEnable; nColumn < nColumns; nColumn++)
	{
		m_wndContentCtrl.m_nColumnsFormat.SetAtGrow(nColumn, (LookupColumnName((szColumn = m_wndHeaderCtrl.m_szColumnsText.GetAt(nColumn))) == TCHISTORY_TITLEITEM_NUMBER || LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_FLAGS || LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_PTVCHECKS || LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_PTVRESULT || LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_PEVCHECKS || LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_PEVRESULT || LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_CEVCHECKS || LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_CEVRESULT || !bEnable) ? (GetColumnFormat(nColumn) | DT_SINGLELINE | DT_END_ELLIPSIS) : (GetColumnFormat(nColumn) & ~(DT_SINGLELINE | DT_END_ELLIPSIS)));
		m_wndContentCtrl.m_bColumnsFormat.SetAtGrow(nColumn, TRUE);
	}
	RecalcContent();
	return TRUE;
}

BOOL CTCHistoryView::IsFullViewModeEnabled() CONST
{
	return m_bFullViewMode;
}

BOOL CTCHistoryView::EnableToolTipMode(BOOL bEnable)
{
	m_bToolTips = bEnable;
	return TRUE;
}

BOOL CTCHistoryView::IsToolTipModeEnabled() CONST
{
	return m_bToolTips;
}

BOOL CTCHistoryView::SetFilterMode(UINT nMode)
{
	m_nFilterMode[0] = nMode;
	return TRUE;
}

BOOL CTCHistoryView::GetFilterMode(UINT &nMode) CONST
{
	nMode = m_nFilterMode[0];
	return TRUE;
}

BOOL CTCHistoryView::SetFilterComputer(LPCTSTR pszComputer)
{
	CTextViewLock  cLock(this);

	m_szFilterComputer = pszComputer;
	return TRUE;
}

BOOL CTCHistoryView::GetFilterComputer(CString &szComputer) CONST
{
	CTextViewLock  cLock(this);

	szComputer = m_szFilterComputer;
	return TRUE;
}

BOOL CTCHistoryView::SetFilterTelecommandName(LPCTSTR pszName)
{
	CTextViewLock  cLock(this);

	m_szFilterTelecommand[0] = pszName;
	return TRUE;
}

BOOL CTCHistoryView::GetFilterTelecommandName(CString &szName) CONST
{
	CTextViewLock  cLock(this);

	szName = m_szFilterTelecommand[0];
	return TRUE;
}

BOOL CTCHistoryView::SetFilterTelecommandSequence(LPCTSTR pszSequence)
{
	CTextViewLock  cLock(this);

	m_szFilterTelecommand[1] = pszSequence;
	return TRUE;
}

BOOL CTCHistoryView::GetFilterTelecommandSequence(CString &szSequence) CONST
{
	CTextViewLock  cLock(this);

	szSequence = m_szFilterTelecommand[1];
	return TRUE;
}

BOOL CTCHistoryView::SetFilterLimitation(UINT nCount)
{
	m_nFilterLimitation = nCount;
	return TRUE;
}

BOOL CTCHistoryView::GetFilterLimitation(UINT &nCount) CONST
{
	nCount = m_nFilterLimitation;
	return TRUE;
}

BOOL CTCHistoryView::SetFilterAutoload(UINT nCount)
{
	m_nFilterAutoload = nCount;
	return TRUE;
}

BOOL CTCHistoryView::GetFilterAutoload(UINT &nCount) CONST
{
	nCount = m_nFilterAutoload;
	return TRUE;
}

BOOL CTCHistoryView::SetFilterSortMode(UINT nMode)
{
	m_nFilterMode[1] = nMode;
	return TRUE;
}

BOOL CTCHistoryView::GetFilterSortMode(UINT &nMode) CONST
{
	nMode = m_nFilterMode[1];
	return TRUE;
}

BOOL CTCHistoryView::StartMonitoring()
{
	return TRUE;
}

BOOL CTCHistoryView::ResetMonitoring(CTCEnvironment *pTCEnvironment)
{
	CTextViewLock  cLock(this);

	m_pItems[0].RemoveAll();
	m_pItems[1].RemoveAll();
	DeleteAllText();
	return TRUE;
}

BOOL CTCHistoryView::StopMonitoring()
{
	return TRUE;
}

BOOL CTCHistoryView::SetTelecommands(CONST CTCItems &pItems)
{
	INT  nItem;
	INT  nItems;
	CTCItem  *pItem;
	CByteArray  nAlertsInfo;
	CTCHistoryItem  *pHistoryItem;
	CTextViewLock  cLock(this);

	for (nItem = 0, nItems = (INT)pItems.GetSize(), m_pItems[1].RemoveAll(); nItem < nItems; nItem++)
	{
		if ((pItem = pItems.GetAt(nItem)) && pItem->GetProperties(nAlertsInfo) >= 0)
		{
			if ((pHistoryItem = new CTCHistoryItem) != (CTCHistoryItem *)NULL)
			{
				if (pHistoryItem->CTCItem::Copy(pItem) && pHistoryItem->SetAlerts(nAlertsInfo) >= 0 && m_pItems[1].Add(pHistoryItem) >= 0) continue;
				delete pHistoryItem;
			}
		}
		break;
	}
	UpdateContent(TRUE);
	return((nItem == nItems) ? TRUE : FALSE);
}

BOOL CTCHistoryView::GetTelecommands(CTCItems &pItems) CONST
{
	INT  nItem;
	INT  nItems;
	CTCItem  *pItem;
	CByteArray  nAlertsInfo;
	CTCHistoryItem  *pHistoryItem;
	CTextViewLock  cLock(this);

	for (nItem = 0, nItems = (INT)m_pItems[1].GetSize(), pItems.RemoveAll(); nItem < nItems; nItem++)
	{
		if ((pHistoryItem = m_pItems[1].GetAt(nItem)) && pHistoryItem->GetAlerts(nAlertsInfo))
		{
			if ((pItem = new CTCItem) != (CTCItem *)NULL)
			{
				if (pItem->Copy(pHistoryItem))
				{
					pItem->SetProperties(nAlertsInfo);
					if (pItems.Add(pItem) >= 0) continue;
				}
				delete pItem;
			}
			break;
		}
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

BOOL CTCHistoryView::UpdateTelecommands(CONST CTCItems &pItems)
{
	INT  nItem[3];
	INT  nItems[3];
	INT  nIndex[2];
	CTCItem  *pItem;
	CTimeTag  tExecutionTime[2];
	CTCHistoryItem  *pHistoryItem[2];
	CTextViewLock  cLock(this);

	for (nItem[0] = 0, nItems[0] = (INT)pItems.GetSize(), nIndex[0] = -1; nItem[0] < nItems[0]; nItem[0]++)
	{
		if ((pItem = pItems.GetAt(nItem[0])) && (pItem->GetType() == TCITEM_TYPE_FUNCTION || pItem->GetType() == TCITEM_TYPE_PROCEDURE))
		{
			if ((pHistoryItem[0] = m_pItems[0].GetAt((nIndex[1] = m_pItems[0].Find(pItem)))))
			{
				if (!CheckTelecommandFilter(pItem))
				{
					m_pItems[0].RemoveAt(nIndex[1]);
					delete pHistoryItem[0];
					continue;
				}
				if ((((m_nFilterMode[1] & TCHISTORY_SORTMODE_BYRELEASETIME) || ((m_nFilterMode[1] & TCHISTORY_SORTMODE_BYEXECUTIONTIME) && (!pItem->GetExecutionTime(tExecutionTime[0]) || !pHistoryItem[0]->GetExecutionTime(tExecutionTime[1])))) && pItem->GetReleaseTime() == pHistoryItem[0]->GetReleaseTime()) || ((m_nFilterMode[1] & TCHISTORY_SORTMODE_BYEXECUTIONTIME) && pItem->GetExecutionTime(tExecutionTime[0]) && pHistoryItem[0]->GetExecutionTime(tExecutionTime[1]) && tExecutionTime[0] == tExecutionTime[1]))
				{
					if (AdjustTelecommandAlerts(pItem, pHistoryItem[0])) continue;
					break;
				}
				m_pItems[0].RemoveAt(nIndex[1]);
				delete pHistoryItem[0];
			}
			if (CheckTelecommandFilter(pItem))
			{
				if ((pHistoryItem[0] = new CTCHistoryItem))
				{
					if (AdjustTelecommandAlerts(pItem, pHistoryItem[0]))
					{
						for (nItem[2] = 0, nItems[2] = (INT)m_pItems[0].GetSize(); nItem[2] < nItems[2]; nItem[2]++)
						{
							if ((pHistoryItem[1] = m_pItems[0].GetAt(nItem[2])))
							{
								if (m_nFilterMode[1] & TCHISTORY_SORTMODE_BYLATESTFIRST)
								{
									if (m_nFilterMode[1] & TCHISTORY_SORTMODE_BYRELEASETIME)
									{
										if (abs(pHistoryItem[0]->GetReleaseTime().GetTime()) >= abs(pHistoryItem[1]->GetReleaseTime().GetTime())) break;
										continue;
									}
									if (pHistoryItem[0]->GetExecutionTime(tExecutionTime[0]))
									{
										if (pHistoryItem[1]->GetExecutionTime(tExecutionTime[1]))
										{
											if (tExecutionTime[0] >= tExecutionTime[1]) break;
											continue;
										}
										if (tExecutionTime[0] >= abs(pHistoryItem[1]->GetReleaseTime().GetTime())) break;
										continue;
									}
									if (pHistoryItem[1]->GetExecutionTime(tExecutionTime[1]))
									{
										if (tExecutionTime[1] <= abs(pHistoryItem[0]->GetReleaseTime().GetTime())) break;
										continue;
									}
									if (abs(pHistoryItem[0]->GetReleaseTime().GetTime()) >= abs(pHistoryItem[1]->GetReleaseTime().GetTime())) break;
									continue;
								}
								if (m_nFilterMode[1] & TCHISTORY_SORTMODE_BYRELEASETIME)
								{
									if (abs(pHistoryItem[0]->GetReleaseTime().GetTime()) < abs(pHistoryItem[1]->GetReleaseTime().GetTime())) break;
									continue;
								}
								if (pHistoryItem[0]->GetExecutionTime(tExecutionTime[0]))
								{
									if (pHistoryItem[1]->GetExecutionTime(tExecutionTime[1]))
									{
										if (tExecutionTime[0] < tExecutionTime[1]) break;
										continue;
									}
									if (tExecutionTime[0] < abs(pHistoryItem[1]->GetReleaseTime().GetTime())) break;
									continue;
								}
								if (pHistoryItem[1]->GetExecutionTime(tExecutionTime[1]))
								{
									if (tExecutionTime[1] > abs(pHistoryItem[0]->GetReleaseTime().GetTime())) break;
									continue;
								}
								if (abs(pHistoryItem[0]->GetReleaseTime().GetTime()) < abs(pHistoryItem[1]->GetReleaseTime().GetTime())) break;
							}
						}
						m_pItems[0].InsertAt((nIndex[0] = nItem[2]), pHistoryItem[0], 1);
						continue;
					}
					delete pHistoryItem[0];
				}
				break;
			}
		}
	}
	for (nItem[1] = 0, nItems[1] = (INT)pItems.GetSize(); nItem[1] < nItems[1]; nItem[1]++)
	{
		if ((pItem = pItems.GetAt(nItem[1])) && (pItem->GetType() == TCITEM_TYPE_FUNCTION || pItem->GetType() == TCITEM_TYPE_PROCEDURE))
		{
			if ((pHistoryItem[0] = m_pItems[1].GetAt((nIndex[1] = m_pItems[1].Find(pItem)))) != (CTCHistoryItem *)NULL)
			{
				if ((((m_nFilterMode[1] & TCHISTORY_SORTMODE_BYRELEASETIME) || ((m_nFilterMode[1] & TCHISTORY_SORTMODE_BYEXECUTIONTIME) && (!pItem->GetExecutionTime(tExecutionTime[0]) || !pHistoryItem[0]->GetExecutionTime(tExecutionTime[1])))) && pItem->GetReleaseTime() == pHistoryItem[0]->GetReleaseTime()) || ((m_nFilterMode[1] & TCHISTORY_SORTMODE_BYEXECUTIONTIME) && pItem->GetExecutionTime(tExecutionTime[0]) && pHistoryItem[0]->GetExecutionTime(tExecutionTime[1]) && tExecutionTime[0] == tExecutionTime[1]))
				{
					if (AdjustTelecommandAlerts(pItem, pHistoryItem[0], FALSE)) continue;
					break;
				}
				m_pItems[1].RemoveAt(nIndex[1]);
				delete pHistoryItem[0];
			}
			if ((pHistoryItem[0] = new CTCHistoryItem))
			{
				if (AdjustTelecommandAlerts(pItem, pHistoryItem[0], FALSE))
				{
					for (nItem[2] = 0, nItems[2] = (INT)m_pItems[1].GetSize(); nItem[2] < nItems[2]; nItem[2]++)
					{
						if ((pHistoryItem[1] = m_pItems[1].GetAt(nItem[2])))
						{
							if (m_nFilterMode[1] & TCHISTORY_SORTMODE_BYRELEASETIME)
							{
								if (abs(pHistoryItem[0]->GetReleaseTime().GetTime()) < abs(pHistoryItem[1]->GetReleaseTime().GetTime())) break;
								continue;
							}
							if (pHistoryItem[0]->GetExecutionTime(tExecutionTime[0]))
							{
								if (pHistoryItem[1]->GetExecutionTime(tExecutionTime[1]))
								{
									if (tExecutionTime[0] < tExecutionTime[1]) break;
									continue;
								}
								if (tExecutionTime[0] < abs(pHistoryItem[1]->GetReleaseTime().GetTime())) break;
								continue;
							}
							if (pHistoryItem[1]->GetExecutionTime(tExecutionTime[1]))
							{
								if (tExecutionTime[1] > abs(pHistoryItem[0]->GetReleaseTime().GetTime())) break;
								continue;
							}
							if (abs(pHistoryItem[0]->GetReleaseTime().GetTime()) < abs(pHistoryItem[1]->GetReleaseTime().GetTime())) break;
						}
					}
					m_pItems[1].InsertAt(nItem[2], pHistoryItem[0], 1);
					continue;
				}
				delete pHistoryItem[0];
			}
			break;
		}
	}
	for (UpdateContent(); nIndex[0] >= 0; )
	{
		ScrollTo(nIndex[0]);
		break;
	}
	return((nItem[0] == nItems[0] && nItem[1] == nItems[1]) ? TRUE : FALSE);
}

BOOL CTCHistoryView::SetCurTelecommand(INT nIndex)
{
	CTextViewLock  cLock(this);

	return ActivateTelecommand(nIndex);
}

INT CTCHistoryView::GetCurTelecommand() CONST
{
	INT  nItem;
	INT  nItems;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nItem = 0, nItems = (INT)m_pItems[0].GetSize(); nItem < nItems; nItem++)
	{
		if ((pItem = m_pItems[0].GetAt(nItem)) && pItem->IsSelected()) break;
		continue;
	}
	return((nItem < nItems) ? nItem : -1);
}

BOOL CTCHistoryView::FindTelecommand(CONST CTCItem *pItem) CONST
{
	CTextViewLock  cLock(this);

	return((m_pItems[0].Find(pItem) >= 0) ? TRUE : FALSE);
}

BOOL CTCHistoryView::SelectTelecommand(INT nIndex)
{
	CTextViewLock  cLock(this);

	if (m_nSearchIndex != nIndex)
	{
		ScrollTo((m_nSearchIndex = nIndex));
		UpdateContent(FALSE);
		RecalcLayout();
	}
	return TRUE;
}

BOOL CTCHistoryView::HasSelectedTelecommands() CONST
{
	INT  nItem;
	INT  nItems;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nItem = 0, nItems = (INT)m_pItems[0].GetSize(); nItem < nItems; nItem++)
	{
		if ((pItem = m_pItems[0].GetAt(nItem)) && pItem->IsSelected()) break;
		continue;
	}
	return((nItem < nItems) ? TRUE : FALSE);
}

UINT CTCHistoryView::GetTelecommandCount() CONST
{
	CTextViewLock  cLock(this);

	return((UINT)m_pItems[0].GetSize());
}

BOOL CTCHistoryView::ShowTelecommandProperties()
{
	INT  nItem;
	INT  nItems;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nItem = 0, nItems = (INT)m_pItems[0].GetSize(); nItem < nItems; nItem++)
	{
		if ((pItem = m_pItems[0].GetAt(nItem)) && pItem->IsSelected()) break;
		continue;
	}
	cLock.Release();
	return((nItem < nItems) ? ShowTelecommandProperties(nItem) : FALSE);
}

BOOL CTCHistoryView::CanShowTelecommandProperties() CONST
{
	INT  nItem;
	INT  nItems;
	BOOL  bSelected;
	CString  szMembership;
	CTimeTag  tMembership;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nItem = 0, nItems = (INT)m_pItems[0].GetSize(), bSelected = FALSE; nItem < nItems; nItem++)
	{
		if ((pItem = m_pItems[0].GetAt(nItem)) != (CTCHistoryItem *)NULL  &&  pItem->IsSelected())
		{
			if ((((pItem->GetMembership().IsEmpty() && !bSelected) || pItem->GetLoadTime() == tMembership) && pItem->GetMembership() == szMembership) || !bSelected)
			{
				szMembership = (!bSelected) ? pItem->GetMembership() : szMembership;
				tMembership = (!bSelected) ? pItem->GetLoadTime() : tMembership;
				bSelected = TRUE;
				continue;
			}
			break;
		}
	}
	return((nItem == nItems) ? bSelected : FALSE);
}

BOOL CTCHistoryView::IsShowingTelecommandProperties() CONST
{
	return m_bProperties;
}

BOOL CTCHistoryView::DoAcknowledgeTelecommand()
{
	INT  nItem;
	INT  nItems;
	CTCItem  *pItem;
	CTCItems  pItems;
	CTCHistoryItem  *pHistoryItem;
	CTextViewLock  cLock(this);

	for (nItem = 0, nItems = (INT)m_pItems[0].GetSize(); nItem < nItems; nItem++)
	{
		if ((pHistoryItem = m_pItems[0].GetAt(nItem)) && pHistoryItem->IsSelected() && pHistoryItem->IsAlerted() != TCHISTORYITEM_ALERTTYPE_NONE)
		{
			if ((pItem = new CTCItem) && pItem->Copy(pHistoryItem) && pItems.Add(pItem) >= 0) continue;
			pItems.RemoveAll();
			delete pItem;
			break;
		}
	}
	if (GetParent()->GetScope() == DISPLAY_SCOPE_GLOBAL)
	{
		GetTCService()->AcknowledgeTelecommands(pItems);
		return TRUE;
	}
	for (nItem = 0, nItems = (INT)pItems.GetSize(); nItem < nItems; nItem++)
	{
		pItem->SetFlags(pItem->GetFlags() | TCITEM_ACKNOWLEDGEFLAG_ALL);
		continue;
	}
	UpdateTelecommands(pItems);
	return TRUE;
}

BOOL CTCHistoryView::CanAcknowledgeTelecommand() CONST
{
	INT  nItem;
	INT  nItems;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nItem = 0, nItems = (INT)m_pItems[0].GetSize(); nItem < nItems; nItem++)
	{
		if ((pItem = m_pItems[0].GetAt(nItem)) && pItem->IsSelected() && pItem->IsAlerted() != TCHISTORYITEM_ALERTTYPE_NONE) break;
		continue;
	}
	return((nItem < nItems) ? TRUE : FALSE);
}

BOOL CTCHistoryView::DoCopyTelecommand()
{
	CTextViewLock  cLock(this);

	return CopyToClipboard();
}

BOOL CTCHistoryView::CanCopyTelecommand() CONST
{
	CTextViewLock  cLock(this);

	return(GetClipboardFormat() != 0 && HasSelectedTelecommands());
}

BOOL CTCHistoryView::SearchTelecommandByNumber(INT nNumber)
{
	CTextViewLock  cLock(this);

	if (nNumber <= m_pItems[0].GetSize())
	{
		SelectTelecommand(nNumber - 1);
		return TRUE;
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByName(LPCTSTR pszName, BOOL bDown, BOOL bAll)
{
	INT  nIndex;
	INT  nCount;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) && pItem->GetName() == pszName)
		{
			SelectTelecommand(nIndex);
			return TRUE;
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByComputer(LPCTSTR pszComputer, BOOL bDown, BOOL bAll)
{
	INT  nIndex;
	INT  nCount;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) && !pItem->GetComputerName().CompareNoCase(pszComputer))
		{
			SelectTelecommand(nIndex);
			return TRUE;
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByCommandSource(UINT nSourceType, BOOL bDown, BOOL bAll)
{
	INT  nIndex;
	INT  nCount;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) && pItem->GetSourceType() == nSourceType)
		{
			SelectTelecommand(nIndex);
			return TRUE;
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByDescription(LPCTSTR pszDescription, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	INT  nIndex;
	INT  nCount;
	CString  szInfo[2];
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0, szInfo[0] = pszDescription; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) != (CTCHistoryItem *)NULL)
		{
			for (szInfo[1] = pItem->GetDescription(); !bCase; )
			{
				szInfo[0].MakeUpper();
				szInfo[1].MakeUpper();
				break;
			}
			if ((!bWord  &&  szInfo[1].Find(szInfo[0]) >= 0) || (bWord && (!szInfo[1].Find(szInfo[0] + SPACE) || szInfo[1].Find(SPACE + szInfo[0] + SPACE) > 0)))
			{
				SelectTelecommand(nIndex);
				return TRUE;
			}
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByCategory(LPCTSTR pszCategory, BOOL bDown, BOOL bAll)
{
	INT  nIndex;
	INT  nCount;
	ULONGLONG  nCategory;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0, nCategory = GetDatabase()->TranslateTCFunctionHazardousFlag(pszCategory, FALSE); (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) && (pItem->GetAttributes() & nCategory))
		{
			SelectTelecommand(nIndex);
			return TRUE;
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandBySubSystem(LPCTSTR pszSubSystem, BOOL bDown, BOOL bAll, BOOL bCase)
{
	INT  nIndex;
	INT  nCount;
	CString  szSubSystem[2];
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0, szSubSystem[0] = pszSubSystem; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) != (CTCHistoryItem *)NULL)
		{
			for (szSubSystem[1] = pItem->GetDestinationSubSystem(); !bCase; )
			{
				szSubSystem[0].MakeUpper();
				szSubSystem[1].MakeUpper();
				break;
			}
			if (szSubSystem[0] == szSubSystem[1])
			{
				SelectTelecommand(nIndex);
				return TRUE;
			}
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByArgument(LPCTSTR pszArgument, BOOL bDown, BOOL bAll)
{
	INT  nIndex;
	INT  nCount;
	INT  nElement;
	INT  nElements;
	INT  nParameter;
	INT  nParameters;
	CTCHistoryItem  *pItem;
	CDatabaseTCPacket  cPacket;
	CDatabaseTCFunctionElement  *pFunctionElement;
	CDatabaseTCPacketParameter  *pPacketParameter;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = (CTCHistoryItem *)m_pItems[0].GetAt(nIndex)) != (CTCHistoryItem *)NULL)
		{
			for (nElement = 0, nElements = (INT)pItem->GetSize(); nElement < nElements; nElement++)
			{
				if ((pFunctionElement = pItem->GetAt(nElement)) && pFunctionElement->GetName() == pszArgument) break;
				continue;
			}
			for (nParameter = 0, nParameters = (pItem->GetTCPacket(&cPacket)) ? (INT)cPacket.GetSize() : 0; nParameter < nParameters; nParameter++)
			{
				if ((pPacketParameter = cPacket.GetAt(nParameter)) && pPacketParameter->GetTag() == pszArgument) break;
				continue;
			}
			if (nElement < nElements || nParameter < nParameters)
			{
				SelectTelecommand(nIndex);
				return TRUE;
			}
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByFlags(BOOL bDown, BOOL bAll, BOOL bInterlocking, BOOL bInterlocked, BOOL bGrouped, BOOL bBlocked)
{
	INT  nIndex;
	INT  nCount;
	BOOL  bInterlock;
	CString  szInterlock;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) && ((bInterlocking  &&  !pItem->GetInterlock().IsEmpty()) || (!bInterlocking  &&  pItem->GetInterlock().IsEmpty())) && ((bInterlocked  &&  pItem->GetReleaseInterlock(szInterlock, bInterlock)) || (!bInterlocked  &&  !pItem->GetReleaseInterlock(szInterlock, bInterlock))) && ((bGrouped && (pItem->GetFlags() & TCHISTORYITEM_LINKAGEFLAG_GROUPED)) || (!bGrouped && (pItem->GetFlags() & TCHISTORYITEM_LINKAGEFLAG_GROUPED) != TCHISTORYITEM_LINKAGEFLAG_GROUPED)) && ((bBlocked && (pItem->GetFlags() & TCHISTORYITEM_LINKAGEFLAG_BLOCKED)) || (!bBlocked && (pItem->GetFlags() & TCHISTORYITEM_LINKAGEFLAG_BLOCKED) != TCHISTORYITEM_LINKAGEFLAG_BLOCKED)))
		{
			SelectTelecommand(nIndex);
			return TRUE;
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByTCPacket(LPCTSTR pszPacket, BOOL bDown, BOOL bAll)
{
	INT  nIndex;
	INT  nCount;
	CTCHistoryItem  *pItem;
	CDatabaseTCPacket  *pPacket;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pPacket = ((pItem = m_pItems[0].GetAt(nIndex))) ? GetDatabase()->GetTCPackets()->GetAt(pItem->GetTCPacketRef()) : (CDatabaseTCPacket *)NULL) && pPacket->GetTag() == pszPacket)
		{
			SelectTelecommand(nIndex);
			return TRUE;
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByDispatchTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch)
{
	INT  nIndex;
	INT  nCount;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) && pItem->GetDispatchTime() > 0)
		{
			if (bMatch  &&  pItem->GetDispatchTime().GetTimeInSeconds() == tTime.GetTime())
			{
				SelectTelecommand(nIndex);
				return TRUE;
			}
			if (!bMatch  &&  pItem->GetDispatchTime().GetTimeInSeconds() - tInterval.GetTotalSeconds() <= tTime.GetTime() && pItem->GetDispatchTime().GetTimeInSeconds() + tInterval.GetTotalSeconds() >= tTime.GetTime())
			{
				SelectTelecommand(nIndex);
				return TRUE;
			}
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByReleaseTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch)
{
	INT  nIndex;
	INT  nCount;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) && pItem->GetReleaseTime() > 0)
		{
			if (bMatch  &&  pItem->GetReleaseTime().GetTimeInSeconds() == tTime.GetTime())
			{
				SelectTelecommand(nIndex);
				return TRUE;
			}
			if (!bMatch  &&  pItem->GetReleaseTime().GetTimeInSeconds() - tInterval.GetTotalSeconds() <= tTime.GetTime() && pItem->GetReleaseTime().GetTimeInSeconds() + tInterval.GetTotalSeconds() >= tTime.GetTime())
			{
				SelectTelecommand(nIndex);
				return TRUE;
			}
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByReleaseTimeOffset(DWORD dwOffset, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch)
{
	INT  nIndex;
	INT  nCount;
	BOOL  bAfterDispatch;
	DWORD  dwReleaseOffset;
	CTimeSpan  tReleaseInterval;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) && pItem->GetReleaseTimeWindow(dwReleaseOffset, tReleaseInterval, bAfterDispatch) && ((bMatch  &&  dwReleaseOffset == dwOffset) || (!bMatch  &&  max(1000 * (TIMETAG)dwReleaseOffset - 1000000 * tInterval.GetTotalSeconds(), 0) <= 1000 * (TIMETAG)dwOffset  &&  dwReleaseOffset + 1000 * (DWORD)tInterval.GetTotalSeconds() >= dwOffset)))
		{
			SelectTelecommand(nIndex);
			return TRUE;
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByTransmissionTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch)
{
	INT  nIndex;
	INT  nCount;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) && pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE  &&  pItem->GetTransmissionTime() > 0)
		{
			if (bMatch  &&  pItem->GetTransmissionTime().GetTimeInSeconds() == tTime.GetTime())
			{
				SelectTelecommand(nIndex);
				return TRUE;
			}
			if (!bMatch  &&  pItem->GetTransmissionTime().GetTimeInSeconds() - tInterval.GetTotalSeconds() <= tTime.GetTime() && pItem->GetTransmissionTime().GetTimeInSeconds() + tInterval.GetTotalSeconds() >= tTime.GetTime())
			{
				SelectTelecommand(nIndex);
				return TRUE;
			}
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByExecutionTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch)
{
	INT  nIndex;
	INT  nCount;
	UINT  nExecutionOBRT;
	CTimeTag  tExecutionTime;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) && (pItem->GetExecutionTime(tExecutionTime) || (pItem->GetExecutionOBRT(nExecutionOBRT) && GetTCService()->ConvertOBRTToTime(nExecutionOBRT, tExecutionTime))))
		{
			if (bMatch  &&  tExecutionTime.GetTimeInSeconds() == tTime.GetTime())
			{
				SelectTelecommand(nIndex);
				return TRUE;
			}
			if (!bMatch  &&  tExecutionTime.GetTimeInSeconds() - tInterval.GetTotalSeconds() <= tTime.GetTime() && tExecutionTime.GetTimeInSeconds() + tInterval.GetTotalSeconds() >= tTime.GetTime())
			{
				SelectTelecommand(nIndex);
				return TRUE;
			}
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByExecutionTimeOffset(CONST CTimeSpan &tOffset, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch)
{
	INT  nIndex;
	INT  nCount;
	BOOL  bEarlierExecution;
	DWORD  dwExecutionOffset;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) && pItem->GetExecutionTimeOffset(dwExecutionOffset, bEarlierExecution) && ((bMatch  &&  dwExecutionOffset / 1000 == abs(tOffset.GetTotalSeconds()) && ((!bEarlierExecution  &&  tOffset >= 0) || (bEarlierExecution  &&  tOffset < 0))) || (!bMatch  &&  dwExecutionOffset / 1000 - tInterval.GetTotalSeconds() <= tOffset.GetTotalSeconds() && dwExecutionOffset / 1000 + tInterval.GetTotalSeconds() >= tOffset.GetTotalSeconds())))
		{
			SelectTelecommand(nIndex);
			return TRUE;
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByAuthorization(UINT nAuthorization, BOOL bDown, BOOL bAll)
{
	INT  nIndex;
	INT  nCount;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) && (pItem->GetFlags() & TCHISTORYITEM_CHECKFLAG_PREAUTHORIZED) == (nAuthorization & TCHISTORYITEM_CHECKFLAG_PREAUTHORIZED))
		{
			SelectTelecommand(nIndex);
			return TRUE;
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByPTVTimeWindow(CONST CTimeKey &tTime, BOOL bDown, BOOL bAll)
{
	INT  nIndex;
	INT  nCount;
	BOOL  bAfterDispatch;
	DWORD  dwReleaseOffset;
	CTimeTag  tReleaseTime[2];
	CTimeSpan  tReleaseInterval;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) != (CTCHistoryItem *)NULL)
		{
			if (pItem->GetReleaseTimeWindow(tReleaseTime[0], tReleaseTime[1]))
			{
				if ((tReleaseTime[0] > 0 && tReleaseTime[1] > 0 && tTime.GetTime() >= tReleaseTime[0].GetTimeInSeconds() && tTime.GetTime() <= tReleaseTime[1].GetTimeInSeconds()) || (tReleaseTime[0] == 0 && tTime.GetTime() <= tReleaseTime[1].GetTimeInSeconds()) || (tReleaseTime[1] == 0 && tTime.GetTime() >= tReleaseTime[0].GetTimeInSeconds()))
				{
					SelectTelecommand(nIndex);
					return TRUE;
				}
			}
			if (pItem->GetReleaseTimeWindow(tReleaseTime[0], tReleaseInterval))
			{
				if ((tReleaseTime[0] > 0 && tReleaseInterval > 0 && tTime.GetTime() >= tReleaseTime[0].GetTimeInSeconds() && tTime.GetTime() <= tReleaseTime[0].GetTimeInSeconds() + tReleaseInterval.GetTotalSeconds()) || (tReleaseInterval == 0 && tTime.GetTime() >= tReleaseTime[0].GetTimeInSeconds()))
				{
					SelectTelecommand(nIndex);
					return TRUE;
				}
			}
			if (pItem->GetReleaseTimeWindow(dwReleaseOffset, tReleaseInterval, bAfterDispatch) && pItem->GetReleaseTime() > 0)
			{
				if ((tReleaseInterval > 0 && tTime.GetTime() >= pItem->GetReleaseTime().GetTimeInSeconds() && tTime.GetTime() <= pItem->GetReleaseTime().GetTimeInSeconds() + tReleaseInterval.GetTotalSeconds()) || (tReleaseInterval == 0 && tTime.GetTime() >= pItem->GetReleaseTime().GetTimeInSeconds()))
				{
					SelectTelecommand(nIndex);
					return TRUE;
				}
			}
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByPTVCheck(UINT nCheck, BOOL bDown, BOOL bAll)
{
	INT  nIndex;
	INT  nCount;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) && (pItem->GetFlags() & (TCHISTORYITEM_CHECKFLAG_OVERRIDEPTV | TCHISTORYITEM_CHECKFLAG_DISABLEPTV)) == (nCheck & (TCHISTORYITEM_CHECKFLAG_OVERRIDEPTV | TCHISTORYITEM_CHECKFLAG_DISABLEPTV)))
		{
			SelectTelecommand(nIndex);
			return TRUE;
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByPTVResult(UINT nResult, BOOL bDown, BOOL bAll)
{
	INT  nIndex;
	INT  nCount;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) && (pItem->GetResult() & (TCHISTORYITEM_RESULT_PTV_GO | TCHISTORYITEM_RESULT_PTV_WAIT | TCHISTORYITEM_RESULT_PTV_FAIL)) == (nResult & (TCHISTORYITEM_RESULT_PTV_GO | TCHISTORYITEM_RESULT_PTV_WAIT | TCHISTORYITEM_RESULT_PTV_FAIL)))
		{
			SelectTelecommand(nIndex);
			return TRUE;
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByPEVCheck(UINT nCheck, BOOL bDown, BOOL bAll)
{
	INT  nIndex;
	INT  nCount;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) && ((nCheck != ~(TCHISTORYITEM_CHECKFLAG_OVERRIDEPEV | TCHISTORYITEM_CHECKFLAG_DISABLEPEV) && pItem->GetPreExeGroupRef() >= 0 && ((pItem->GetFlags() & (TCHISTORYITEM_CHECKFLAG_OVERRIDEPEV | TCHISTORYITEM_CHECKFLAG_DISABLEPEV)) == (nCheck & (TCHISTORYITEM_CHECKFLAG_OVERRIDEPEV | TCHISTORYITEM_CHECKFLAG_DISABLEPEV)))) || (nCheck == ~(TCHISTORYITEM_CHECKFLAG_OVERRIDEPEV | TCHISTORYITEM_CHECKFLAG_DISABLEPEV) && pItem->GetPreExeGroupRef() < 0)))
		{
			SelectTelecommand(nIndex);
			return TRUE;
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByPEVResult(UINT nResult, BOOL bDown, BOOL bAll)
{
	INT  nIndex;
	INT  nCount;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) && pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE && (pItem->GetResult() & (TCHISTORYITEM_RESULT_PEV_GO | TCHISTORYITEM_RESULT_PEV_NOGO)) == (nResult & (TCHISTORYITEM_RESULT_PEV_GO | TCHISTORYITEM_RESULT_PEV_NOGO)))
		{
			SelectTelecommand(nIndex);
			return TRUE;
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByCEVTimeWindow(CONST CTimeKey &tTime, BOOL bDown, BOOL bAll)
{
	INT  nIndex;
	INT  nCount;
	CTCHistoryItem  *pItem;
	CTimeSpan  tTimeWindow[2];
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) && pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE && (pItem->GetFlags() & (TCHISTORYITEM_CHECKFLAG_OVERRIDECEV | TCHISTORYITEM_CHECKFLAG_DISABLECEV)) == 0 && pItem->GetVerificationTime() > 0)
		{
			for (tTimeWindow[0] = pItem->CalcVerificationTimeWindowSize(0, (GetTCService()->GetCommandHandlerVerificationUncertaintyTimeWindow(tTimeWindow[1])) ? tTimeWindow[1] : 0); tTime.GetTime() >= pItem->GetVerificationTime().GetTimeInSeconds() && tTime.GetTime() <= pItem->GetVerificationTime().GetTimeInSeconds() + tTimeWindow[0].GetTotalSeconds(); )
			{
				SelectTelecommand(nIndex);
				return TRUE;
			}
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByCEVCheck(UINT nCheck, BOOL bDown, BOOL bAll)
{
	INT  nIndex;
	INT  nCount;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) && ((nCheck != ~(TCHISTORYITEM_CHECKFLAG_OVERRIDECEV | TCHISTORYITEM_CHECKFLAG_DISABLECEV) && pItem->GetExeVerGroupRef() >= 0 && ((pItem->GetFlags() & (TCHISTORYITEM_CHECKFLAG_OVERRIDECEV | TCHISTORYITEM_CHECKFLAG_DISABLECEV)) == (nCheck & (TCHISTORYITEM_CHECKFLAG_OVERRIDECEV | TCHISTORYITEM_CHECKFLAG_DISABLECEV)))) || (nCheck == ~(TCHISTORYITEM_CHECKFLAG_OVERRIDECEV | TCHISTORYITEM_CHECKFLAG_DISABLECEV) && pItem->GetExeVerGroupRef() < 0)))
		{
			SelectTelecommand(nIndex);
			return TRUE;
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByCEVResult(UINT nResult, BOOL bDown, BOOL bAll)
{
	INT  nIndex;
	INT  nCount;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) && pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE && (pItem->GetResult() & (TCHISTORYITEM_RESULT_CEV_IDLE | TCHISTORYITEM_RESULT_CEV_PENDING | TCHISTORYITEM_RESULT_CEV_PASSED | TCHISTORYITEM_RESULT_CEV_FAILED | TCHISTORYITEM_RESULT_CEV_UNKNOWN | TCHISTORYITEM_RESULT_CEV_UNVERIFIED)) == (nResult & (TCHISTORYITEM_RESULT_CEV_IDLE | TCHISTORYITEM_RESULT_CEV_PENDING | TCHISTORYITEM_RESULT_CEV_PASSED | TCHISTORYITEM_RESULT_CEV_FAILED | TCHISTORYITEM_RESULT_CEV_UNKNOWN | TCHISTORYITEM_RESULT_CEV_UNVERIFIED)))
		{
			SelectTelecommand(nIndex);
			return TRUE;
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::SearchTelecommandByStatus(LPCTSTR pszStatus, BOOL bDown, BOOL bAll)
{
	INT  nIndex;
	INT  nCount;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	for (nIndex = ((nIndex = m_nSearchIndex) >= 0 && !bAll) ? ((!bDown) ? (nIndex - 1) : (nIndex + 1)) : ((!bDown) ? (GetTelecommandCount() - 1) : 0), nCount = (bDown) ? GetTelecommandCount() : 0; (bDown && nIndex < nCount) || (!bDown && nIndex >= nCount); nIndex = (bDown) ? (nIndex + 1) : (nIndex - 1))
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)) && ((pItem->GetStatus() == TCHISTORYITEM_STATUS_RELEASED  &&  pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE  &&  !lstrcmp(pszStatus, STRING(IDS_TCHISTORY_LIST_STATUS_RELEASED))) || (pItem->GetStatus() == TCHISTORYITEM_STATUS_NOTRELEASED  &&  pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE  &&  !lstrcmp(pszStatus, STRING(IDS_TCHISTORY_LIST_STATUS_NOTRELEASED))) || (pItem->GetStatus() == TCHISTORYITEM_STATUS_FAILEDRELEASE  &&  pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE  &&  !lstrcmp(pszStatus, STRING(IDS_TCHISTORY_LIST_STATUS_FAILEDRELEASE))) || (pItem->GetStatus() == TCHISTORYITEM_STATUS_SENT  &&  pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE  &&  !lstrcmp(pszStatus, STRING(IDS_TCHISTORY_LIST_STATUS_SENT))) || (pItem->GetStatus() == TCHISTORYITEM_STATUS_FAILEDSEND  &&  pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE  &&  !lstrcmp(pszStatus, STRING(IDS_TCHISTORY_LIST_STATUS_FAILEDSEND))) || (pItem->GetStatus() == TCHISTORYITEM_STATUS_UPLINKED  &&  pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE  &&  !lstrcmp(pszStatus, STRING(IDS_TCHISTORY_LIST_STATUS_UPLINKED))) || (pItem->GetStatus() == TCHISTORYITEM_STATUS_FAILEDUPLINK  &&  pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE  &&  !lstrcmp(pszStatus, STRING(IDS_TCHISTORY_LIST_STATUS_FAILEDUPLINK))) || (pItem->GetStatus() == TCHISTORYITEM_STATUS_EXECUTED  &&  pItem->GetType() == TCHISTORYITEM_TYPE_PROCEDURE  &&  !lstrcmp(pszStatus, STRING(IDS_TCHISTORY_LIST_STATUS_EXECUTED))) || (pItem->GetStatus() == TCHISTORYITEM_STATUS_NOTEXECUTED  &&  pItem->GetType() == TCHISTORYITEM_TYPE_PROCEDURE  &&  !lstrcmp(pszStatus, STRING(IDS_TCHISTORY_LIST_STATUS_NOTEXECUTED))) || (pItem->GetStatus() == TCHISTORYITEM_STATUS_FAILEDEXECUTION  &&  pItem->GetType() == TCHISTORYITEM_TYPE_PROCEDURE  &&  !lstrcmp(pszStatus, STRING(IDS_TCHISTORY_LIST_STATUS_FAILEDEXECUTION)))))
		{
			SelectTelecommand(nIndex);
			return TRUE;
		}
	}
	SelectTelecommand(-1);
	return FALSE;
}

BOOL CTCHistoryView::GetPrintProperties(CONST CTCHistoryPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST
{
	INT  nItem;
	INT  nItems;
	UINT  nMode;
	UINT  nRange[2];
	CString  szItem;
	CTimeKey  tRange[2];
	CTimeTag  tExecutionTime;
	CTCHistoryItem  *pItem;
	CTextViewAttribute  *pAttribute;
	CTextViewLock  cLock(this);

	for (nItem = 0, nItems = (GetColumns(szColumns) && GetTitleFont(pTitleFont) && GetTextFont(pItemsFont)) ? (INT)m_pItems[0].GetSize() : -1, szContents.RemoveAll(), pAttributes.RemoveAll(), pSymbols.RemoveAll(), nSymbolIDs.RemoveAll(); nItem < nItems; nItem++)
	{
		if ((pItem = m_pItems[0].GetAt(nItem)) && (((nMode = pJobInfo->GetPrintMode()) & (TCHISTORY_PRINT_VERIFICATIONSUCCESS | TCHISTORY_PRINT_VERIFICATIONFAILURE)) == 0 || ((nMode & TCHISTORY_PRINT_VERIFICATIONSUCCESS) && (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_PASSED)) || ((nMode & TCHISTORY_PRINT_VERIFICATIONFAILURE) && (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_PASSED) != TCHISTORYITEM_RESULT_CEV_PASSED)) && (!pJobInfo->GetPrintRange(nRange[0], nRange[1]) || (nItem + 1 >= (INT)nRange[0] && nItem + 1 <= (INT)nRange[1])) && (!pJobInfo->GetPrintRange(tRange[0], tRange[1], TRUE) || (pItem->GetReleaseTime().GetTimeInSeconds() >= tRange[0].GetTime() && pItem->GetReleaseTime().GetTimeInSeconds() <= tRange[1].GetTime())) && (!pJobInfo->GetPrintRange(tRange[0], tRange[1], FALSE) || (pItem->GetExecutionTime(tExecutionTime) && tExecutionTime.GetTimeInSeconds() >= tRange[0].GetTime() && tExecutionTime.GetTimeInSeconds() <= tRange[1].GetTime())))
		{
			if ((pAttribute = new CTextViewAttribute))
			{
				if (GetText(nItem, szItem, pAttribute))
				{
					pAttributes.Add(pAttribute);
					szContents.Add(szItem);
					continue;
				}
				delete pAttribute;
			}
			break;
		}
	}
	pSymbols.Add(m_pFlagSymbols[TCHISTORYVIEW_COMMANDFLAGSYMBOL_INTERLOCK]);
	pSymbols.Add(m_pFlagSymbols[TCHISTORYVIEW_COMMANDFLAGSYMBOL_INTERLOCKIDLE]);
	pSymbols.Add(m_pFlagSymbols[TCHISTORYVIEW_COMMANDFLAGSYMBOL_INTERLOCKPENDING]);
	pSymbols.Add(m_pFlagSymbols[TCHISTORYVIEW_COMMANDFLAGSYMBOL_INTERLOCKSUCCESS]);
	pSymbols.Add(m_pFlagSymbols[TCHISTORYVIEW_COMMANDFLAGSYMBOL_INTERLOCKFAILURE]);
	pSymbols.Add(m_pFlagSymbols[TCHISTORYVIEW_COMMANDFLAGSYMBOL_GROUPED]);
	pSymbols.Add(m_pFlagSymbols[TCHISTORYVIEW_COMMANDFLAGSYMBOL_BLOCKED]);
	pSymbols.Add(m_pCheckFlagSymbols[TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOL_NONE]);
	pSymbols.Add(m_pCheckFlagSymbols[TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOL_ON]);
	pSymbols.Add(m_pCheckFlagSymbols[TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOL_OFF]);
	pSymbols.Add(m_pCheckFlagSymbols[TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOL_DISABLED]);
	pSymbols.Add(m_pResultSymbols[TCHISTORYVIEW_COMMANDRESULTSYMBOL_PTV_GO]);
	pSymbols.Add(m_pResultSymbols[TCHISTORYVIEW_COMMANDRESULTSYMBOL_PTV_WAIT]);
	pSymbols.Add(m_pResultSymbols[TCHISTORYVIEW_COMMANDRESULTSYMBOL_PTV_FAIL]);
	pSymbols.Add(m_pResultSymbols[TCHISTORYVIEW_COMMANDRESULTSYMBOL_PEV_GO]);
	pSymbols.Add(m_pResultSymbols[TCHISTORYVIEW_COMMANDRESULTSYMBOL_PEV_NOGO]);
	pSymbols.Add(m_pResultSymbols[TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_IDLE]);
	pSymbols.Add(m_pResultSymbols[TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_PENDING]);
	pSymbols.Add(m_pResultSymbols[TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_PASSED]);
	pSymbols.Add(m_pResultSymbols[TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_FAILED]);
	pSymbols.Add(m_pResultSymbols[TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_UNKNOWN]);
	pSymbols.Add(m_pResultSymbols[TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_UNVERIFIED]);
	pSymbols.Add(m_pAlertSymbols[TCHISTORYVIEW_COMMANDALERTSYMBOL_INFORMATION]);
	pSymbols.Add(m_pAlertSymbols[TCHISTORYVIEW_COMMANDALERTSYMBOL_WARNING]);
	pSymbols.Add(m_pAlertSymbols[TCHISTORYVIEW_COMMANDALERTSYMBOL_ERROR]);
	nSymbolIDs.Add(IDP_TCHISTORYINTERLOCK);
	nSymbolIDs.Add(IDP_TCHISTORYINTERLOCKIDLE);
	nSymbolIDs.Add(IDP_TCHISTORYINTERLOCKPENDING);
	nSymbolIDs.Add(IDP_TCHISTORYINTERLOCKSUCCESS);
	nSymbolIDs.Add(IDP_TCHISTORYINTERLOCKFAILURE);
	nSymbolIDs.Add(IDP_TCHISTORYGROUPED);
	nSymbolIDs.Add(IDP_TCHISTORYBLOCKED);
	nSymbolIDs.Add(IDP_TCHISTORYCHECKSNONE);
	nSymbolIDs.Add(IDP_TCHISTORYCHECKSON);
	nSymbolIDs.Add(IDP_TCHISTORYCHECKSOFF);
	nSymbolIDs.Add(IDP_TCHISTORYCHECKSDISABLED);
	nSymbolIDs.Add(IDP_TCHISTORYPTVGO);
	nSymbolIDs.Add(IDP_TCHISTORYPTVWAIT);
	nSymbolIDs.Add(IDP_TCHISTORYPTVFAIL);
	nSymbolIDs.Add(IDP_TCHISTORYPEVGO);
	nSymbolIDs.Add(IDP_TCHISTORYPEVNOGO);
	nSymbolIDs.Add(IDP_TCHISTORYCEVIDLE);
	nSymbolIDs.Add(IDP_TCHISTORYCEVPENDING);
	nSymbolIDs.Add(IDP_TCHISTORYCEVPASSED);
	nSymbolIDs.Add(IDP_TCHISTORYCEVFAILED);
	nSymbolIDs.Add(IDP_TCHISTORYCEVUNKNOWN);
	nSymbolIDs.Add(IDP_TCHISTORYCEVUNVERIFIED);
	nSymbolIDs.Add(IDP_TCHISTORYINFORMATION);
	nSymbolIDs.Add(IDP_TCHISTORYWARNING);
	nSymbolIDs.Add(IDP_TCHISTORYERROR);
	return((nItem == nItems) ? TRUE : FALSE);
}

VOID CTCHistoryView::UpdateContent(BOOL bFilter, BOOL bRedraw)
{
	INT  nRow;
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nCount;
	INT  nColumn;
	INT  nDigits;
	UINT  nFormat;
	CPoint  ptToolTip;
	CString  szText;
	CString  szNumber;
	CString  szColumn;
	CString  szToolTip[3];
	CTimeTag  tExecutionTime[2];
	CStringTools  cStringTools;
	CTCHistoryItem  *pItem[3];
	CTextViewAttribute  cAttribute;
	CDatabaseTCFunctions  pBlockedItems;
	CTextViewLock  cLock(this);

	if (bFilter)
	{
		for (nItem = 0, nItems = (INT)m_pItems[1].GetSize(), m_pItems[0].RemoveAll(); nItem < nItems; nItem++)
		{
			if ((pItem[0] = m_pItems[1].GetAt(nItem)) && CheckTelecommandFilter(pItem[0]))
			{
				for (nIndex = 0, nCount = (INT)m_pItems[0].GetSize(); nIndex < nCount; nIndex++)
				{
					if ((pItem[1] = m_pItems[0].GetAt(nIndex)))
					{
						if (m_nFilterMode[1] & TCHISTORY_SORTMODE_BYLATESTFIRST)
						{
							if (m_nFilterMode[1] & TCHISTORY_SORTMODE_BYRELEASETIME)
							{
								if (abs(pItem[0]->GetReleaseTime().GetTime()) >= abs(pItem[1]->GetReleaseTime().GetTime())) break;
								continue;
							}
							if (pItem[0]->GetExecutionTime(tExecutionTime[0]))
							{
								if (pItem[1]->GetExecutionTime(tExecutionTime[1]))
								{
									if (tExecutionTime[0] >= tExecutionTime[1]) break;
									continue;
								}
								if (tExecutionTime[0] >= abs(pItem[1]->GetReleaseTime().GetTime())) break;
								continue;
							}
							if (pItem[1]->GetExecutionTime(tExecutionTime[1]))
							{
								if (tExecutionTime[1] <= abs(pItem[0]->GetReleaseTime().GetTime())) break;
								continue;
							}
							if (abs(pItem[0]->GetReleaseTime().GetTime()) >= abs(pItem[1]->GetReleaseTime().GetTime())) break;
							continue;
						}
						if (m_nFilterMode[1] & TCHISTORY_SORTMODE_BYRELEASETIME)
						{
							if (abs(pItem[0]->GetReleaseTime().GetTime()) < abs(pItem[1]->GetReleaseTime().GetTime())) break;
							continue;
						}
						if (pItem[0]->GetExecutionTime(tExecutionTime[0]))
						{
							if (pItem[1]->GetExecutionTime(tExecutionTime[1]))
							{
								if (tExecutionTime[0] < tExecutionTime[1]) break;
								continue;
							}
							if (tExecutionTime[0] < abs(pItem[1]->GetReleaseTime().GetTime())) break;
							continue;
						}
						if (pItem[1]->GetExecutionTime(tExecutionTime[1]))
						{
							if (tExecutionTime[1] > abs(pItem[0]->GetReleaseTime().GetTime())) break;
							continue;
						}
						if (abs(pItem[0]->GetReleaseTime().GetTime()) < abs(pItem[1]->GetReleaseTime().GetTime())) break;
					}
				}
				if ((pItem[2] = new CTCHistoryItem))
				{
					if (pItem[2]->Copy(pItem[0]))
					{
						m_pItems[0].InsertAt(nIndex, pItem[2], 1);
						continue;
					}
					delete pItem[2];
				}
			}
		}
	}
	for (nItem = 0, nItems = ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYLIMITENTRIES) && m_nFilterLimitation < (UINT)m_pItems[0].GetSize()) ? (INT)(m_pItems[0].GetSize() - m_nFilterLimitation) : 0; nItem < nItems; nItem++)
	{
		if ((pItem[0] = m_pItems[0].GetAt((nIndex = (m_nFilterMode[1] & TCHISTORY_SORTMODE_BYLATESTFIRST) ? (INT)(m_pItems[0].GetSize() - nItem - 1) : nItem))))
		{
			m_pItems[0].RemoveAt(nIndex);
			delete pItem[0];
			nItems--;
			nItem--;
		}
	}
	for (nItem = 0, nItems = (INT)m_pItems[0].GetSize(), nCount = GetTextCount(), nColumn = FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_NUMBER)), nDigits = cStringTools.ConvertLongIntToString(m_pItems[0].GetSize()).GetLength(), nDigits = max(nDigits, 3); nItem < nItems; nItem++)
	{
		for (szNumber = cStringTools.ConvertIntToPaddedString(nItem + 1, nDigits), szNumber += (m_nSearchIndex == nItem) ? STRING(IDS_TCHISTORY_LIST_FIND_SYMBOL) : EMPTYSTRING; (pItem[0] = m_pItems[0].GetAt(nItem)) && TranslateTelecommand(pItem[0], &cAttribute); )
		{
			for (nFormat = GetColumnFormat((nIndex = FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_DESCRIPTION)))); pItem[0]->GetReleaseBlockedItems(pBlockedItems) > 0 && (nFormat & DT_SINGLELINE) && !m_bFullViewMode; )
			{
				cAttribute.SetColumnFormat(nIndex, nFormat & ~DT_SINGLELINE);
				break;
			}
			for (szText = szNumber + TranslateTelecommand(pItem[0]); nItem >= nCount; )
			{
				InsertText(nItem, szText, &cAttribute, (nItem == nItems - 1) ? bRedraw : FALSE);
				break;
			}
			if (nItem < nCount)
			{
				SetText(nItem, szText, &cAttribute, (nItem == nItems - 1) ? bRedraw : FALSE);
				break;
			}
			break;
		}
	}
	for (nItem = (INT)m_pItems[0].GetSize(), nItems = nCount; nItem < nItems; nItem++)
	{
		DeleteText(nItem, (nItem == nItems - 1) ? bRedraw : FALSE);
		nItems--;
		nItem--;
	}
	if (bRedraw)
	{
		if (m_wndToolTip.IsVisibleAtPoint(ptToolTip))
		{
			if ((pItem[0] = (FindTextFromPoint(ptToolTip, nRow, nColumn, TRUE) && GetText(nRow, nColumn, szToolTip[2])) ? m_pItems[0].GetAt(nRow) : (CTCHistoryItem *)NULL))
			{
				for (szToolTip[0] = ConstructToolTipTitle(ptToolTip, szToolTip[2], LookupColumnName((szColumn = m_wndHeaderCtrl.m_szColumnsText.GetAt(nColumn)))), szToolTip[1] = ConstructToolTipText(pItem[0], ptToolTip, szToolTip[2], LookupColumnName(szColumn)); !szToolTip[0].IsEmpty() || !szToolTip[1].IsEmpty(); )
				{
					m_wndToolTip.Update(szToolTip[0], szToolTip[1]);
					break;
				}
			}
		}
		DrawContent();
	}
}

VOID CTCHistoryView::RefreshContent()
{
	CTextViewLock  cLock(this);

	EnableFullViewMode(m_bFullViewMode);
	UpdateContent();
}

VOID CTCHistoryView::DrawContent()
{
	CTextView::DrawContent();
}
VOID CTCHistoryView::DrawContent(CDC *pDC)
{
	INT  nItem;
	INT  nItems;
	INT  nWidth;
	INT  nHeight;
	CRect  rArea;
	CRect  rText[2];
	CRect  rContent;

	for (nItem = FindFirstVisibleText(), nItems = FindLastVisibleText() + 1, nItems = min(GetTextCount() - 1, nItems), m_wndContentCtrl.GetClientRect(rContent), rText[0] = m_wndContentCtrl.CalcTextRect(GetTextCount() - 1), nWidth = rContent.Width(), nHeight = m_wndContentCtrl.CalcTextLines(SPACE); nItem >= 0 && nItem <= nItems; nItem++)
	{
		DrawBackground(pDC, GetTextCount() + GetTextCount() % 2 + nItem % 2, -1, (rText[0].right < rContent.right) ? CRect(rText[0].right + m_wndContentCtrl.m_wTextIndent[1], max(rText[1].top - m_wndContentCtrl.m_wTextSpacing[0], rContent.top), rContent.right, (rText[1] = m_wndContentCtrl.CalcTextRect(nItem)).bottom + m_wndContentCtrl.m_wTextSpacing[1]) : CRect(0, 0, 0, 0));
		DrawText(pDC, nItem, m_wndContentCtrl.m_szContentText.GetAt(nItem));
	}
	for (rArea.SetRect(rContent.left, (GetTextCount() > 0) ? min(max(rText[0].bottom + m_wndContentCtrl.m_wTextSpacing[1], rContent.top), rContent.bottom) : rContent.top, rContent.right, rContent.bottom), nItem = GetTextCount(); rArea.top < rContent.bottom; rArea.DeflateRect(0, nHeight, 0, 0), nItem++)
	{
		DrawBackground(pDC, nItem, -1, CRect(rArea.left, rArea.top, rArea.right, rArea.top + nHeight));
		continue;
	}
}

VOID CTCHistoryView::DrawText(INT nItem, LPCTSTR pszText)
{
	CTextView::DrawText(nItem, pszText);
}
VOID CTCHistoryView::DrawText(CDC *pDC, INT nItem, LPCTSTR pszText)
{
	CTextView::DrawText(pDC, nItem, pszText);
}
VOID CTCHistoryView::DrawText(INT nItem, INT nColumn, LPCTSTR pszText)
{
	CTextView::DrawText(nItem, nColumn, pszText);
}
VOID CTCHistoryView::DrawText(CDC *pDC, INT nItem, INT nColumn, LPCTSTR pszText)
{
	CDC  cDC;
	INT  nPos;
	INT  nIndex;
	INT  nCount;
	BOOL  bText;
	BOOL  bState;
	UINT  nFormat;
	UINT  nSymbol[4];
	CRect  rText[3];
	CFont  cTextFont;
	CFont  *pOldFont;
	CSize  sizeSymbol;
	CSize  sizeBitmap;
	CPoint  ptBitmap;
	CString  szStage;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	COLORREF  nColor[2];
	CStringArray  szStages;
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
					for (cDC.SetBkMode(TRANSPARENT), cDC.SetTextColor(nColor[0]), DrawBackground(&cDC, nItem, nColumn, CRect(m_wndContentCtrl.m_wTextIndent[0] - rText[1].left, 0, sizeBitmap.cx, sizeBitmap.cy)), bText = FALSE; (pOldFont = (nColumn != FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_FLAGS)) && nColumn != FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_PTVCHECKS)) && nColumn != FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_PTVRESULT)) && nColumn != FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_PEVCHECKS)) && nColumn != FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_PEVRESULT)) && nColumn != FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_CEVCHECKS)) && nColumn != FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_CEVRESULT))) ? ((GetColumnFont(nItem, nColumn, &cTextFont)) ? cDC.SelectObject(&cTextFont) : cDC.SelectObject(&m_wndContentCtrl.m_cFont)) : (CFont *)NULL); )
					{
						cDC.DrawText(((nPos = (nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_NUMBER))) ? (INT)_tcscspn(pszText, CString(GetSymbolDelimiter())) : -1) >= 0) ? CString(pszText).Left(nPos) : pszText, CRect(m_wndContentCtrl.m_wTextIndent[0], m_wndContentCtrl.m_wTextSpacing[0], sizeBitmap.cx - m_wndContentCtrl.m_wTextIndent[0], sizeBitmap.cy - m_wndContentCtrl.m_wTextSpacing[0]), nFormat);
						cDC.SelectObject(pOldFont);
						bText = TRUE;
						break;
					}
					if (nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_NUMBER)) || !bText)
					{
						for (sizeSymbol.cx = sizeSymbol.cy = 0, nColor[1] = cDC.GetNearestColor(VGA_COLOR_WHITE), cTextFont.DeleteObject(); (pOldFont = (GetColumnFont(nItem, nColumn, &cTextFont)) ? cDC.SelectObject(&cTextFont) : cDC.SelectObject(&m_wndContentCtrl.m_cFont)); )
						{
							sizeSymbol.cx = sizeSymbol.cy = cDC.GetTextExtent(SPACE).cy;
							m_sizeCheckFlagSymbols = sizeSymbol;
							m_sizeResultSymbols = sizeSymbol;
							m_sizeAlertSymbols = sizeSymbol;
							m_sizeFlagSymbols = sizeSymbol;
							cDC.SelectObject(pOldFont);
							cTextFont.DeleteObject();
							break;
						}
						if (nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_NUMBER)))
						{
							for (nSymbol[0] = (!_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_ALERT_INFORMATION))) ? ((!_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_ALERT_WARNING))) ? ((_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_ALERT_ERROR))) ? TCHISTORYVIEW_COMMANDALERTSYMBOL_ERROR : -1) : TCHISTORYVIEW_COMMANDALERTSYMBOL_WARNING) : TCHISTORYVIEW_COMMANDALERTSYMBOL_INFORMATION; nSymbol[0] != (UINT)-1; )
							{
								if (bState) m_pAlertSymbols[nSymbol[0]]->TransparentBlt(cDC.GetSafeHdc(), m_wndContentCtrl.m_wTextIndent[0] + CalcTelecommandSymbolPosition(nItem, nColumn, pszText).left - rText[1].left, m_wndContentCtrl.m_wTextSpacing[0], sizeSymbol.cx, sizeSymbol.cy, nColor[1]);
								break;
							}
						}
						if (nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_FLAGS)))
						{
							for (nIndex = 0, nCount = sizeof(nSymbol) / sizeof(UINT), nSymbol[0] = (_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCK))) ? TCHISTORYVIEW_COMMANDFLAGSYMBOL_INTERLOCK : -1, nSymbol[1] = (_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKIDLE))) ? TCHISTORYVIEW_COMMANDFLAGSYMBOL_INTERLOCKIDLE : ((_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKPENDING))) ? TCHISTORYVIEW_COMMANDFLAGSYMBOL_INTERLOCKPENDING : ((_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKSUCCESS))) ? TCHISTORYVIEW_COMMANDFLAGSYMBOL_INTERLOCKSUCCESS : ((_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKFAILURE))) ? TCHISTORYVIEW_COMMANDFLAGSYMBOL_INTERLOCKFAILURE : -1))), nSymbol[2] = (_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_FLAGS_GROUPED))) ? TCHISTORYVIEW_COMMANDFLAGSYMBOL_GROUPED : -1, nSymbol[3] = (_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_FLAGS_BLOCKED))) ? TCHISTORYVIEW_COMMANDFLAGSYMBOL_BLOCKED : -1; nIndex < nCount; nIndex++)
							{
								if (bState  &&  nSymbol[nIndex] != (UINT)-1) m_pFlagSymbols[nSymbol[nIndex]]->TransparentBlt(cDC.GetSafeHdc(), m_wndContentCtrl.m_wTextIndent[0] + CalcTelecommandSymbolPosition(nItem, nColumn, nCount, nIndex).left - rText[1].left, m_wndContentCtrl.m_wTextSpacing[0], sizeSymbol.cx, sizeSymbol.cy, nColor[1]);
								continue;
							}
						}
						else if (nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_PTVCHECKS)))
						{
							nSymbol[0] = (!_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_PTVCHECKS_DISABLED))) ? ((_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_PTVCHECKS_ON))) ? TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOL_ON : TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOL_OFF) : TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOL_DISABLED;
							if (bState) m_pCheckFlagSymbols[nSymbol[0]]->TransparentBlt(cDC.GetSafeHdc(), m_wndContentCtrl.m_wTextIndent[0] + CalcTelecommandSymbolPosition(nItem, nColumn, 1, 0).left - rText[1].left, m_wndContentCtrl.m_wTextSpacing[0], sizeSymbol.cx, sizeSymbol.cy, nColor[1]);
						}
						else if (nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_PTVRESULT)))
						{
							for (nSymbol[0] = (_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_PTVRESULT_GO))) ? TCHISTORYVIEW_COMMANDRESULTSYMBOL_PTV_GO : -1, nSymbol[0] = (_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_PTVRESULT_WAIT))) ? TCHISTORYVIEW_COMMANDRESULTSYMBOL_PTV_WAIT : nSymbol[0], nSymbol[0] = (_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_PTVRESULT_FAIL))) ? TCHISTORYVIEW_COMMANDRESULTSYMBOL_PTV_FAIL : nSymbol[0]; nSymbol[0] != (UINT)-1; )
							{
								if (bState) m_pResultSymbols[nSymbol[0]]->TransparentBlt(cDC.GetSafeHdc(), m_wndContentCtrl.m_wTextIndent[0] + CalcTelecommandSymbolPosition(nItem, nColumn, 1, 0).left - rText[1].left, m_wndContentCtrl.m_wTextSpacing[0], sizeSymbol.cx, sizeSymbol.cy, nColor[1]);
								break;
							}
						}
						else if (nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_PEVCHECKS)))
						{
							nSymbol[0] = (!_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_PEVCHECKS_NONE))) ? ((!_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_PEVCHECKS_DISABLED))) ? ((_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_PEVCHECKS_ON))) ? TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOL_ON : TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOL_OFF) : TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOL_DISABLED) : TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOL_NONE;
							if (bState) m_pCheckFlagSymbols[nSymbol[0]]->TransparentBlt(cDC.GetSafeHdc(), m_wndContentCtrl.m_wTextIndent[0] + CalcTelecommandSymbolPosition(nItem, nColumn, 1, 0).left - rText[1].left, m_wndContentCtrl.m_wTextSpacing[0], sizeSymbol.cx, sizeSymbol.cy, nColor[1]);
						}
						else if (nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_PEVRESULT)))
						{
							for (nSymbol[0] = (_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_PEVRESULT_GO))) ? TCHISTORYVIEW_COMMANDRESULTSYMBOL_PEV_GO : -1, nSymbol[0] = (_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_PEVRESULT_NOGO))) ? TCHISTORYVIEW_COMMANDRESULTSYMBOL_PEV_NOGO : nSymbol[0]; nSymbol[0] != (UINT)-1; )
							{
								if (bState) m_pResultSymbols[nSymbol[0]]->TransparentBlt(cDC.GetSafeHdc(), m_wndContentCtrl.m_wTextIndent[0] + CalcTelecommandSymbolPosition(nItem, nColumn, 1, 0).left - rText[1].left, m_wndContentCtrl.m_wTextSpacing[0], sizeSymbol.cx, sizeSymbol.cy, nColor[1]);
								break;
							}
						}
						else if (nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_CEVCHECKS)))
						{
							nSymbol[0] = (!_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_CEVCHECKS_NONE))) ? ((!_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_CEVCHECKS_DISABLED))) ? ((_tcsstr(pszText, STRING(IDS_TCHISTORY_LIST_CEVCHECKS_ON))) ? TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOL_ON : TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOL_OFF) : TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOL_DISABLED) : TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOL_NONE;
							if (bState) m_pCheckFlagSymbols[nSymbol[0]]->TransparentBlt(cDC.GetSafeHdc(), m_wndContentCtrl.m_wTextIndent[0] + CalcTelecommandSymbolPosition(nItem, nColumn, 1, 0).left - rText[1].left, m_wndContentCtrl.m_wTextSpacing[0], sizeSymbol.cx, sizeSymbol.cy, nColor[1]);
						}
						else if (nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_CEVRESULT)))
						{
							for (nSymbol[0] = (!lstrcmp(pszText, STRING(IDS_TCHISTORY_LIST_CEVRESULT_IDLE))) ? TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_IDLE : -1, nSymbol[0] = (!lstrcmp(pszText, STRING(IDS_TCHISTORY_LIST_CEVRESULT_PENDING))) ? TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_PENDING : nSymbol[0], nSymbol[0] = (!lstrcmp(pszText, STRING(IDS_TCHISTORY_LIST_CEVRESULT_PASSED))) ? TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_PASSED : nSymbol[0], nSymbol[0] = (!lstrcmp(pszText, STRING(IDS_TCHISTORY_LIST_CEVRESULT_FAILED))) ? TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_FAILED : nSymbol[0], nSymbol[0] = (!lstrcmp(pszText, STRING(IDS_TCHISTORY_LIST_CEVRESULT_UNKNOWN))) ? TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_UNKNOWN : nSymbol[0], nSymbol[0] = (!lstrcmp(pszText, STRING(IDS_TCHISTORY_LIST_CEVRESULT_UNVERIFIED))) ? TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_UNVERIFIED : nSymbol[0]; nSymbol[0] != (UINT)-1; )
							{
								if (bState) m_pResultSymbols[nSymbol[0]]->TransparentBlt(cDC.GetSafeHdc(), m_wndContentCtrl.m_wTextIndent[0] + CalcTelecommandSymbolPosition(nItem, nColumn, 1, 0).left - rText[1].left, m_wndContentCtrl.m_wTextSpacing[0], sizeSymbol.cx, sizeSymbol.cy, nColor[1]);
								break;
							}
							for (szStage = pszText, szStages.RemoveAll(); !szStage.IsEmpty() && nSymbol[0] == (UINT)-1; szStage = (nPos >= 0) ? (szStage.Mid(nPos + lstrlen(STRING(IDS_TCHISTORY_LIST_CEVRESULT_SEPARATOR)))) : EMPTYSTRING)
							{
								if ((nPos = szStage.Find(STRING(IDS_TCHISTORY_LIST_CEVRESULT_SEPARATOR))) >= 0)
								{
									szStages.Add(szStage.Left(nPos));
									continue;
								}
								szStages.Add(szStage);
							}
							for (nIndex = 0, nCount = (INT)szStages.GetSize(); nIndex < nCount; nIndex++)
							{
								for (nSymbol[0] = (szStages.GetAt(nIndex).Find(STRING(IDS_TCHISTORY_LIST_CEVRESULT_IDLE)) >= 0) ? TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_IDLE : -1, nSymbol[0] = (szStages.GetAt(nIndex).Find(STRING(IDS_TCHISTORY_LIST_CEVRESULT_PENDING)) >= 0) ? TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_PENDING : nSymbol[0], nSymbol[0] = (szStages.GetAt(nIndex).Find(STRING(IDS_TCHISTORY_LIST_CEVRESULT_PASSED)) >= 0) ? TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_PASSED : nSymbol[0], nSymbol[0] = (szStages.GetAt(nIndex).Find(STRING(IDS_TCHISTORY_LIST_CEVRESULT_FAILED)) >= 0) ? TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_FAILED : nSymbol[0], nSymbol[0] = (szStages.GetAt(nIndex).Find(STRING(IDS_TCHISTORY_LIST_CEVRESULT_UNKNOWN)) >= 0) ? TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_UNKNOWN : nSymbol[0], nSymbol[0] = (szStages.GetAt(nIndex).Find(STRING(IDS_TCHISTORY_LIST_CEVRESULT_UNVERIFIED)) >= 0) ? TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_UNVERIFIED : nSymbol[0]; nSymbol[0] != (UINT)-1; )
								{
									if (bState) m_pResultSymbols[nSymbol[0]]->TransparentBlt(cDC.GetSafeHdc(), m_wndContentCtrl.m_wTextIndent[0] + CalcTelecommandSymbolPosition(nItem, nColumn, nCount, nIndex).left - rText[1].left, m_wndContentCtrl.m_wTextSpacing[0], sizeSymbol.cx, sizeSymbol.cy, nColor[1]);
									break;
								}
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

BOOL CTCHistoryView::DrawBackground(CDC *pDC, INT nItem, INT nColumn, CONST RECT &rItem)
{
	CDC  cDC[2];
	INT  nWidth;
	INT  nHeight;
	BOOL  bBackground;
	CBitmap  cBitmap[2];
	CBitmap  *pOldBitmap[2];
	CTCHistoryItem  *pItem;
	BLENDFUNCTION  sBlend;

	if (cDC[0].CreateCompatibleDC(pDC))
	{
		if (cDC[1].CreateCompatibleDC(pDC))
		{
			if (cBitmap[0].CreateCompatibleBitmap(pDC, (nWidth = rItem.right - rItem.left), (nHeight = rItem.bottom - rItem.top)))
			{
				if (cBitmap[1].CreateCompatibleBitmap(pDC, nWidth, nHeight))
				{
					if ((pOldBitmap[0] = cDC[0].SelectObject(&cBitmap[0])))
					{
						if ((pOldBitmap[1] = cDC[1].SelectObject(&cBitmap[1])))
						{
							for (sBlend.BlendFlags = 0, sBlend.BlendOp = AC_SRC_OVER, sBlend.AlphaFormat = 0, sBlend.SourceConstantAlpha = TCHISTORYVIEW_COLUMNTRANSPARENCY; nWidth > 0 && nHeight > 0; )
							{
								for (cDC[0].FillSolidRect(0, 0, nWidth, nHeight, m_nBackgroundColor[nItem % 2]), cDC[1].FillSolidRect(0, 0, nWidth, nHeight, VGA_COLOR_WHITE), cDC[1].AlphaBlend(0, 0, nWidth, nHeight, &cDC[0], 0, 0, nWidth, nHeight, sBlend); (pItem = m_pItems[0].GetAt(nItem)) && (pItem->GetStatus() == TCHISTORYITEM_STATUS_RELEASED || pItem->GetStatus() == TCHISTORYITEM_STATUS_NOTRELEASED || pItem->GetStatus() == TCHISTORYITEM_STATUS_FAILEDRELEASE || pItem->GetStatus() == TCHISTORYITEM_STATUS_SENT || pItem->GetStatus() == TCHISTORYITEM_STATUS_FAILEDSEND || pItem->GetStatus() == TCHISTORYITEM_STATUS_UPLINKED || pItem->GetStatus() == TCHISTORYITEM_STATUS_FAILEDUPLINK); )
								{
									cDC[0].FillSolidRect(0, 0, nWidth, nHeight, LookupStatusColor(pItem->GetResult(), pItem->GetStatus()));
									cDC[1].AlphaBlend(0, 0, nWidth, nHeight, &cDC[0], 0, 0, nWidth, nHeight, sBlend);
									break;
								}
								for (sBlend.SourceConstantAlpha = 0xFF - 2 * sBlend.SourceConstantAlpha; (pItem = m_pItems[0].GetAt(nItem)) && pItem->IsSelected(); )
								{
									for (cDC[0].SetTextColor(pDC->GetTextColor()); (bBackground = CTextView::DrawBackground(&cDC[0], -(nItem + 1), nColumn, CRect(0, 0, nWidth, nHeight))); )
									{
										cDC[1].AlphaBlend(0, 0, nWidth, nHeight, &cDC[0], 0, 0, nWidth, nHeight, sBlend);
										break;
									}
									for (pDC->SetTextColor(cDC[0].GetTextColor()); !bBackground; )
									{
										cDC[1].BitBlt(0, 0, nWidth, nHeight, &cDC[0], 0, 0, SRCCOPY);
										break;
									}
									break;
								}
								pDC->BitBlt(rItem.left, rItem.top, nWidth, nHeight, &cDC[1], 0, 0, SRCCOPY);
								break;
							}
							cDC[0].SelectObject(pOldBitmap[0]);
							cDC[1].SelectObject(pOldBitmap[1]);
							cBitmap[0].DeleteObject();
							cBitmap[1].DeleteObject();
							cDC[0].DeleteDC();
							cDC[1].DeleteDC();
							return TRUE;
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
	return FALSE;
}

CTCHistoryWnd *CTCHistoryView::GetParent() CONST
{
	return((CTCHistoryWnd *)CTextView::GetParent());
}

BOOL CTCHistoryView::ShowTelecommandProperties(INT nIndex)
{
	CTCHistoryItem  *pItem;
	CTCHistoryItems  pItems;
	CTCHistoryItemPropertiesDialog  cTCFunctionPropertiesDialog;
	CTCHistoryComposedItemPropertiesDialog  cTCSequencePropertiesDialog;

	if (Lock())
	{
		if ((pItem = m_pItems[0].GetAt(nIndex)))
		{
			if (m_pItems[0].Collect(nIndex, pItems) > 0)
			{
				for (m_bProperties = TRUE, Unlock(); pItems.GetSize() == 1; )
				{
					cTCFunctionPropertiesDialog.Create(GetParent(), pItems.GetAt((INT)pItems.GetUpperBound()));
					break;
				}
				for (; pItems.GetSize() > 1; )
				{
					cTCSequencePropertiesDialog.Create(GetParent(), pItems);
					break;
				}
				m_bProperties = FALSE;
				return TRUE;
			}
		}
		Unlock();
	}
	return FALSE;
}

BOOL CTCHistoryView::ActivateTelecommand(INT nIndex, BOOL bActivate, BOOL bRedraw)
{
	INT  nItem[2];
	INT  nItems[2];
	BOOL  bKeys;
	BOOL  bSelected;
	CPtrArray  pItems;
	CTCHistoryItem  *pItem[2];

	if ((pItem[0] = m_pItems[0].GetAt(nIndex)) || nIndex < 0)
	{
		for (nItem[1] = 0, nItems[1] = ((bKeys = (!HIBYTE(GetKeyState(VK_SHIFT)) && !HIBYTE(GetKeyState(VK_CONTROL)))) || nIndex < 0) ? (INT)m_pItems[0].GetSize() : 0, bSelected = (nIndex >= 0) ? pItem[0]->IsSelected() : FALSE; nItem[1] < nItems[1]; nItem[1]++)
		{
			if ((pItem[1] = m_pItems[0].GetAt(nItem[1])))
			{
				if (nIndex < 0 || bKeys)
				{
					pItem[1]->Select(FALSE);
					continue;
				}
			}
		}
		for (nItem[1] = 0, nItems[1] = (HIBYTE(GetKeyState(VK_SHIFT))) ? (INT)m_pItems[0].GetSize() : -1; nItem[1] < nItems[1]; nItem[1]++)
		{
			if ((pItem[1] = m_pItems[0].GetAt(nItem[1])) && pItem[1]->IsSelected()) break;
			continue;
		}
		for (nItem[0] = min(nIndex, (nItem[1] = (nItem[1] == nItems[1] || nItems[1] < 0) ? nIndex : nItem[1])), nItems[0] = max(nIndex, nItem[1]); nItem[0] <= nItems[0] && nItem[0] < m_pItems[0].GetSize() && nIndex >= 0; nItem[0]++)
		{
			for (nItem[1] = 0, nItems[1] = ((pItem[0] = m_pItems[0].GetAt(nItem[0]))) ? m_pItems[0].Collect(nItem[0], pItems) : 0; nItem[1] < nItems[1]; nItem[1]++)
			{
				if ((pItem[1] = (CTCHistoryItem *)pItems.GetAt(nItem[1])))
				{
					pItem[1]->Select((bActivate) ? !bSelected : FALSE);
					continue;
				}
			}
		}
		if (bRedraw) DrawContent();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryView::IsActivatedTelecommand(INT nIndex) CONST
{
	CTCHistoryItem  *pItem;

	return(((pItem = m_pItems[0].GetAt(nIndex)) && pItem->IsSelected()) ? TRUE : FALSE);
}

BOOL CTCHistoryView::UpdateTelecommand(CTCHistoryItem *pItem)
{
	UINT  nResult;
	CTimeTag  tTime;
	CTimeTag  tExecutionTime;
	CTimeSpan  tTimeWindow[3];
	CStringArray  szParameters;

	for (tTimeWindow[0] = pItem->CalcVerificationTimeWindowOffset(0), tTimeWindow[1] = pItem->CalcVerificationTimeWindowSize(0, (GetTCService()->GetCommandHandlerVerificationUncertaintyTimeWindow(tTimeWindow[2])) ? tTimeWindow[2] : 0); (pItem->GetStatus() == TCHISTORYITEM_STATUS_RELEASED || pItem->GetStatus() == TCHISTORYITEM_STATUS_SENT || pItem->GetStatus() == TCHISTORYITEM_STATUS_UPLINKED) && pItem->GetExecutionTime(tExecutionTime) && tExecutionTime.GetTime() + 1000000 * (tTimeWindow[0].GetTotalSeconds() + tTimeWindow[1].GetTotalSeconds()) >= tTime.GetTime(); )
	{
		for (nResult = pItem->GetResult(); (pItem->GetFlags() & (TCHISTORYITEM_CHECKFLAG_OVERRIDEPEV | TCHISTORYITEM_CHECKFLAG_DISABLEPEV)) == 0; )
		{
			for (pItem->SetResult(pItem->GetResult() & ~(TCHISTORYITEM_FAILURE_PEV_TELEMETRY | TCHISTORYITEM_FAILURE_PEV_2NDSTEP | TCHISTORYITEM_FAILURE_PEV_PARAMETERS)); (pItem->GetFlags() & TCHISTORYITEM_EXECUTIONFLAG_2NDSTEP) && !GetTCService()->CheckTCOnBoardBufferQueue(pItem); )
			{
				pItem->SetResult(pItem->GetResult() | TCHISTORYITEM_FAILURE_PEV_2NDSTEP);
				break;
			}
			if (pItem->GetPreExeGroupRef() >= 0)
			{
				if (!GetTCService()->CheckTCFunctionPreexecutionParameterGroup(pItem->GetPreExeGroupRef(), szParameters))
				{
					pItem->SetVerificationStageParameters(TCVERIFICATIONSTAGE_NONE, szParameters);
					pItem->SetResult(pItem->GetResult() | TCHISTORYITEM_FAILURE_PEV_PARAMETERS);
				}
				for (; GetTMService()->CheckTMStreamInterruption(); )
				{
					pItem->SetResult(pItem->GetResult() | TCHISTORYITEM_FAILURE_PEV_TELEMETRY);
					break;
				}
			}
			if (pItem->GetResult() & (TCHISTORYITEM_FAILURE_PEV_TELEMETRY | TCHISTORYITEM_FAILURE_PEV_CORRELATION | TCHISTORYITEM_FAILURE_PEV_2NDSTEP | TCHISTORYITEM_FAILURE_PEV_PARAMETERS))
			{
				pItem->SetResult((pItem->GetResult() & ~TCHISTORYITEM_RESULT_PEV_GO) | TCHISTORYITEM_RESULT_PEV_NOGO);
				return((pItem->GetResult() != nResult) ? TRUE : FALSE);
			}
			break;
		}
		pItem->SetVerificationStageParameters(TCVERIFICATIONSTAGE_NONE, szParameters);
		pItem->SetResult((pItem->GetResult() & ~(TCHISTORYITEM_RESULT_PEV_NOGO | TCHISTORYITEM_FAILURE_PEV_TELEMETRY | TCHISTORYITEM_FAILURE_PEV_CORRELATION | TCHISTORYITEM_FAILURE_PEV_2NDSTEP | TCHISTORYITEM_FAILURE_PEV_PARAMETERS)) | TCHISTORYITEM_RESULT_PEV_GO);
		return((pItem->GetResult() != nResult) ? TRUE : FALSE);
	}
	return FALSE;
}

CString CTCHistoryView::TranslateTelecommand(CONST CTCHistoryItem *pItem) CONST
{
	INT  nColumn;
	INT  nColumns;
	INT  nCategory;
	INT  nCategories;
	INT  nSubSystem;
	INT  nSubSystems;
	INT  nBlockItem;
	INT  nBlockItems;
	INT  nArgument[2];
	INT  nArguments[2];
	INT  nArgumentsCount;
	BOOL  bAfterDispatch;
	BOOL  bBlockItemPrefix;
	BOOL  bEarlierExecution;
	UINT  nExecutionOBRT;
	UINT  nVerificationState;
	UINT  nVerificationReason;
	DWORD  dwExecutionOffset;
	DWORD  dwReleaseOffset;
	CString  szItem;
	CString  szName;
	CString  szFlags;
	CString  szAlert;
	CString  szStatus;
	CString  szColumn;
	CString  szCategory;
	CString  szArgument;
	CString  szTCPacket;
	CString  szSubSystem;
	CString  szChecks[3];
	CString  szResult[3];
	CString  szSourceType;
	CString  szAuthorization;
	CString  szDispatchTime;
	CString  szReleaseTime[4];
	CString  szExecutionTime[4];
	CString  szTransmissionTime;
	CString  szVerificationTime;
	CString  szVerificationState;
	CTimeTag  tReleaseTime[2];
	CTimeTag  tTransmissionTime;
	CTimeTag  tExecutionTime;
	CTimeSpan  tTimeWindow;
	CTimeSpan  tReleaseInterval;
	CTCInterlock  cInterlock[2];
	CStringArray  szCategories;
	CStringArray  szSubSystems;
	CStringTools  cStringTools;
	CLongUIntArray  nCategoryIDs;
	CDatabaseTCPacket  cPacket;
	CDatabaseTCFunction  *pFunction;
	CDatabaseTCFunctions  pBlockedItems;
	CDatabaseTCFunctionElement  *pFunctionElement;
	CDatabaseTCPacketParameter  *pPacketParameter;

	for (nColumn = 0, nColumns = (INT)m_wndHeaderCtrl.m_szColumnsText.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (LookupColumnName((szColumn = m_wndHeaderCtrl.m_szColumnsText.GetAt(nColumn))) == TCHISTORY_TITLEITEM_NUMBER)
		{
			szAlert = (pItem->IsAlerted() == TCHISTORYITEM_ALERTTYPE_INFORMATION) ? (CString(GetSymbolDelimiter()) + STRING(IDS_TCHISTORY_LIST_ALERT_INFORMATION)) : EMPTYSTRING;
			szAlert = (pItem->IsAlerted() == TCHISTORYITEM_ALERTTYPE_WARNING) ? (CString(GetSymbolDelimiter()) + STRING(IDS_TCHISTORY_LIST_ALERT_WARNING)) : szAlert;
			szAlert = (pItem->IsAlerted() == TCHISTORYITEM_ALERTTYPE_ERROR) ? (CString(GetSymbolDelimiter()) + STRING(IDS_TCHISTORY_LIST_ALERT_ERROR)) : szAlert;
			szItem += (nColumn > 0) ? (GetColumnDelimiter() + szAlert) : szAlert;
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_NAME)
		{
			szName.Format(STRING(IDS_TCHISTORY_LIST_NAME_FORMAT), (LPCTSTR)pItem->GetName(), (LPCTSTR)pItem->GetMembership());
			szName = (pItem->GetMembership().IsEmpty()) ? pItem->GetName() : szName;
			szItem += (nColumn > 0) ? (GetColumnDelimiter() + szName) : szName;
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_COMPUTER)
		{
			szItem += (nColumn > 0) ? (GetColumnDelimiter() + pItem->GetComputerName()) : pItem->GetComputerName();
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_COMMANDSOURCE)
		{
			szSourceType = (pItem->GetSourceType() == TCITEM_SOURCETYPE_MANUALSTACK) ? STRING(IDS_TCHISTORY_LIST_COMMANDSOURCE_MANUALSTACK) : EMPTYSTRING;
			szSourceType = (pItem->GetSourceType() == TCITEM_SOURCETYPE_AUTOMATICSTACK) ? STRING(IDS_TCHISTORY_LIST_COMMANDSOURCE_AUTOMATICSTACK) : szSourceType;
			szSourceType = (pItem->GetSourceType() == TCITEM_SOURCETYPE_PROCEDURESMONITOR) ? STRING(IDS_TCHISTORY_LIST_COMMANDSOURCE_PROCEDURESMONITOR) : szSourceType;
			szSourceType = (pItem->GetSourceType() == TCITEM_SOURCETYPE_ALLSOURCES) ? STRING(IDS_TCHISTORY_LIST_COMMANDSOURCE_ALLSOURCES) : szSourceType;
			szItem += (nColumn > 0) ? (GetColumnDelimiter() + szSourceType) : szSourceType;
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_DESCRIPTION)
		{
			for (nBlockItem = 0, nBlockItems = pItem->GetReleaseBlockedItems(pBlockedItems), bBlockItemPrefix = TRUE; nBlockItem < nBlockItems; nBlockItem++)
			{
				if ((pFunction = pBlockedItems.GetAt(nBlockItem)) && !pFunction->GetDescription().IsEmpty())
				{
					if (_istspace(pFunction->GetDescription().GetAt(0)))
					{
						bBlockItemPrefix = FALSE;
						break;
					}
				}
			}
			for (nBlockItem = 0, szItem += (nColumn > 0) ? (GetColumnDelimiter() + pItem->GetDescription()) : pItem->GetDescription(); nBlockItem < nBlockItems; nBlockItem++)
			{
				if ((pFunction = pBlockedItems.GetAt(nBlockItem)) != (CDatabaseTCFunction *)NULL  &&  !pFunction->GetDescription().IsEmpty())
				{
					for (szItem += (!nBlockItem) ? STRING(IDS_TCHISTORY_LIST_DESCRIPTION_BLOCKTITLESIGN) : EMPTYSTRING; !bBlockItemPrefix; )
					{
						szItem += EOL + pFunction->GetDescription();
						break;
					}
					szItem += (bBlockItemPrefix) ? (EOL + CString(STRING(IDS_TCHISTORY_LIST_DESCRIPTION_BLOCKITEMPREFIX)) + pFunction->GetDescription()) : EMPTYSTRING;
				}
			}
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_CATEGORY)
		{
			for (nCategory = 0, nCategories = GetDatabase()->EnumTCFunctionHazardousFlags(szCategories, nCategoryIDs), szCategory.Empty(); nCategory < nCategories; nCategory++)
			{
				if (pItem->GetAttributes() & nCategoryIDs.GetAt(nCategory))
				{
					szCategory = szCategories.GetAt(nCategory);
					break;
				}
			}
			szItem += (nColumn > 0) ? (CString(GetColumnDelimiter()) + szCategory) : szCategory;
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_SUBSYSTEM)
		{
			for (szItem += (nColumn > 0) ? (GetColumnDelimiter() + pItem->GetDestinationSubSystem()) : pItem->GetDestinationSubSystem(); pItem->GetTCPacket(&cPacket); )
			{
				for (nSubSystem = 0, nSubSystems = GetTCService()->EnumTCSubSystems(szSubSystems, FALSE); nSubSystem < nSubSystems; nSubSystem++)
				{
					if (GetTCService()->TranslateTCSubSystemToID(szSubSystems.GetAt(nSubSystem)) == cPacket.GetAPID()) break;
					continue;
				}
				for (szSubSystem.Format(STRING(IDS_TCHISTORY_LIST_SUBSYSTEM_FORMAT), (LPCTSTR)cStringTools.ConvertUIntToPaddedString(cPacket.GetAPID(), max(cStringTools.ConvertUIntToString((szSubSystems.GetSize() > 0) ? GetTCService()->TranslateTCSubSystemToID(szSubSystems.GetAt(szSubSystems.GetUpperBound())) : 0, 16).GetLength(), 3), 16)); nSubSystem < nSubSystems; )
				{
					szItem += szSubSystem;
					break;
				}
				break;
			}
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_ARGUMENTS)
		{
			for (nArgument[1] = 0, nArguments[1] = (((pItem->GetFlags() & TCHISTORYITEM_LINKAGEFLAG_BLOCKED) != TCHISTORYITEM_LINKAGEFLAG_BLOCKED || !pItem->GetReleaseBlockID()) && pItem->GetTCPacket(&cPacket)) ? (INT)cPacket.GetSize() : 0, nArgumentsCount = 0; nArgument[1] < nArguments[1]; nArgument[1]++)
			{
				if ((pPacketParameter = cPacket.GetAt(nArgument[1])) && (pPacketParameter->GetAttributes() & TCPARAMETER_VTYPE_AUTO) != TCPARAMETER_VTYPE_AUTO && (pPacketParameter->GetAttributes() & TCPARAMETER_TYPE_CONSTANT) == 0)
				{
					szArgument.Format(STRING(IDS_TCHISTORY_LIST_ARGUMENTS_FORMAT), (LPCTSTR)pPacketParameter->GetTag(), (LPCTSTR)pPacketParameter->GetConstValueAsText());
					szItem += (nColumn > 0) ? ((nArgumentsCount > 0) ? (STRING(IDS_TCHISTORY_LIST_ARGUMENTS_SEPARATOR) + szArgument) : (GetColumnDelimiter() + szArgument)) : ((nArgumentsCount > 0) ? (STRING(IDS_TCHISTORY_LIST_ARGUMENTS_SEPARATOR) + szArgument) : szArgument);
					nArgumentsCount++;
				}
			}
			for (nBlockItem = -1, nBlockItems = pItem->GetReleaseBlockedItems(pBlockedItems); nBlockItem < nBlockItems; nBlockItem++)
			{
				for (nArgument[0] = 0, nArguments[0] = ((pFunction = pBlockedItems.GetAt(nBlockItem))) ? (INT)pFunction->GetSize() : (INT)pItem->GetSize(); nArgument[0] < nArguments[0]; nArgument[0]++)
				{
					if ((pFunctionElement = (nBlockItem >= 0) ? pFunction->GetAt(nArgument[0]) : pItem->GetAt(nArgument[0])) && (pFunctionElement->GetAttributes() & TCPARAMETER_VTYPE_AUTO) != TCPARAMETER_VTYPE_AUTO && (pFunctionElement->GetAttributes() & TCPARAMETER_TYPE_CONSTANT) == 0)
					{
						szArgument.Format(STRING(IDS_TCHISTORY_LIST_ARGUMENTS_FORMAT), (LPCTSTR)pFunctionElement->GetName(), (LPCTSTR)pFunctionElement->GetConstValueAsText());
						szItem += (nColumn > 0) ? ((nArgumentsCount > 0) ? (STRING(IDS_TCHISTORY_LIST_ARGUMENTS_SEPARATOR) + szArgument) : (GetColumnDelimiter() + szArgument)) : ((nArgumentsCount > 0) ? (STRING(IDS_TCHISTORY_LIST_ARGUMENTS_SEPARATOR) + szArgument) : szArgument);
						nArgumentsCount++;
					}
				}
			}
			szItem += (nColumn > 0) ? ((!nArgumentsCount) ? ((nArguments[0] + nArguments[1] == 0) ? (CString(GetColumnDelimiter()) + STRING(IDS_TCHISTORY_LIST_ARGUMENTS_NONE)) : CString(GetColumnDelimiter())) : EMPTYSTRING) : ((nArguments[0] + nArguments[1] == 0) ? STRING(IDS_TCHISTORY_LIST_ARGUMENTS_NONE) : EMPTYSTRING);
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_FLAGS)
		{
			szFlags.Format(STRING(IDS_TCHISTORY_LIST_FLAGS_FORMAT), (pItem->GetInterlock(&cInterlock[0])) ? STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCK) : EMPTYSTRING, (pItem->GetReleaseInterlock(&cInterlock[1])) ? ((cInterlock[1].GetState() == TCINTERLOCK_STATE_IDLE) ? STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKIDLE) : ((cInterlock[1].GetState() == TCINTERLOCK_STATE_PENDING) ? STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKPENDING) : ((cInterlock[1].GetState() == TCINTERLOCK_STATE_SUCCESS) ? STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKSUCCESS) : STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKFAILURE)))) : EMPTYSTRING, (pItem->GetFlags() & TCHISTORYITEM_LINKAGEFLAG_GROUPED) ? STRING(IDS_TCHISTORY_LIST_FLAGS_GROUPED) : EMPTYSTRING, (pItem->GetFlags() & TCHISTORYITEM_LINKAGEFLAG_BLOCKED) ? STRING(IDS_TCHISTORY_LIST_FLAGS_BLOCKED) : EMPTYSTRING);
			szItem += (nColumn > 0) ? (GetColumnDelimiter() + szFlags) : szFlags;
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_TCPACKET)
		{
			szTCPacket = (pItem->GetTCPacket(&cPacket)) ? cPacket.GetTag() : EMPTYSTRING;
			szItem += (nColumn > 0) ? (((pItem->GetFlags() & TCHISTORYITEM_LINKAGEFLAG_BLOCKED) && pItem->GetReleaseBlockID() > 0) ? (CString(GetColumnDelimiter()) + STRING(IDS_TCHISTORY_LIST_TCPACKET_BLOCKED)) : (GetColumnDelimiter() + szTCPacket)) : (((pItem->GetFlags() & TCHISTORYITEM_LINKAGEFLAG_BLOCKED) && pItem->GetReleaseBlockID() > 0) ? STRING(IDS_TCHISTORY_LIST_TCPACKET_BLOCKED) : szTCPacket);
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_DISPATCHTIME)
		{
			szDispatchTime = (pItem->GetDispatchTime() > 0) ? pItem->GetDispatchTime().FormatGmt(STRING(IDS_TCHISTORY_LIST_DISPATCHTIME_FORMAT)) : STRING(IDS_TCHISTORY_LIST_DISPATCHTIME_NONE);
			szItem += (nColumn > 0) ? (GetColumnDelimiter() + szDispatchTime) : szDispatchTime;
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_RELEASETIME)
		{
			for (szReleaseTime[0] = STRING(IDS_TCHISTORY_LIST_RELEASETIME_FAILEDFORMAT); (tReleaseTime[0] = pItem->GetReleaseTime()) > 0; )
			{
				szReleaseTime[0] = tReleaseTime[0].FormatGmt(STRING(IDS_TCHISTORY_LIST_RELEASETIME_FORMAT));
				break;
			}
			if (!tReleaseTime[0].GetTime() && !pItem->GetReleaseTimeWindow(dwReleaseOffset, tReleaseInterval, bAfterDispatch)) szReleaseTime[0] = (!pItem->GetReleaseBlockID() || pItem->GetReleaseBlockID() == (UINT)-1) ? (((pItem->GetFlags() & TCHISTORYITEM_EXECUTIONFLAG_TIMETAGGED) != TCHISTORYITEM_EXECUTIONFLAG_TIMETAGGED) ? STRING(IDS_TCHISTORY_LIST_RELEASETIME_IMMEDIATE) : STRING(IDS_TCHISTORY_LIST_RELEASETIME_ASPOSSIBLE)) : STRING(IDS_TCHISTORY_LIST_RELEASETIME_WITHPREVIOUS);
			szItem += (nColumn > 0) ? (GetColumnDelimiter() + szReleaseTime[0]) : szReleaseTime[0];
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_RELEASETIMEOFFSET)
		{
			for (szReleaseTime[0].Empty(); pItem->GetReleaseTimeWindow(dwReleaseOffset, tReleaseInterval, bAfterDispatch); )
			{
				szReleaseTime[0] = (!pItem->GetReleaseBlockID() || pItem->GetReleaseBlockID() == (UINT)-1) ? CTimeSpan(dwReleaseOffset / 1000).Format((dwReleaseOffset >= 1000 * SECONDSPERDAY) ? STRING(IDS_TCHISTORY_LIST_RELEASETIME_LONGOFFSETFORMAT) : STRING(IDS_TCHISTORY_LIST_RELEASETIME_OFFSETFORMAT)) : CTimeSpan(0).Format(STRING(IDS_TCHISTORY_LIST_RELEASETIME_OFFSETFORMAT));
				szReleaseTime[1].Format(STRING(IDS_TCHISTORY_LIST_RELEASETIME_AFTERDISPATCH), (LPCTSTR)szReleaseTime[0]);
				szReleaseTime[2].Format(STRING(IDS_TCHISTORY_LIST_RELEASETIME_AFTERPREVIOUS), (LPCTSTR)szReleaseTime[0]);
				szReleaseTime[3].Format(STRING(IDS_TCHISTORY_LIST_RELEASETIME_AFTERBEGIN), (LPCTSTR)szReleaseTime[0]);
				szReleaseTime[0] = ((pItem->GetAttributes() & TCFUNCTION_DISPFLAG_AUTHORIZATION) == 0) ? (((pItem->GetFlags() & TCHISTORYITEM_RELEASEFLAG_AFTERPREVIOUS) || (pItem->GetReleaseBlockID() > 0 && pItem->GetReleaseBlockID() != (UINT)-1)) ? ((!pItem->GetMembership().IsEmpty() && !pItem->GetMembershipID()) ? szReleaseTime[0] : szReleaseTime[2]) : ((!pItem->GetMembership().IsEmpty() && !pItem->GetMembershipID()) ? szReleaseTime[0] : szReleaseTime[3])) : szReleaseTime[1];
				break;
			}
			szItem += (nColumn > 0) ? (GetColumnDelimiter() + szReleaseTime[0]) : szReleaseTime[0];
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_TRANSMISSIONTIME)
		{
			for (szTransmissionTime.Empty(); (tTransmissionTime = (pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE) ? pItem->GetTransmissionTime() : 0) > 0; )
			{
				szTransmissionTime = tTransmissionTime.FormatGmt((pItem->GetStatus() == TCHISTORYITEM_STATUS_UPLINKED) ? STRING(IDS_TCHISTORY_LIST_TRANSMISSIONTIME_FORMAT) : STRING(IDS_TCHISTORY_LIST_TRANSMISSIONTIME_FAILEDFORMAT));
				break;
			}
			szTransmissionTime = (pItem->GetStatus() != TCHISTORYITEM_STATUS_UPLINKED || tTransmissionTime <= 0) ? STRING(IDS_TCHISTORY_LIST_TRANSMISSIONTIME_NONE) : szTransmissionTime;
			szItem += (nColumn > 0) ? (GetColumnDelimiter() + szTransmissionTime) : szTransmissionTime;
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_EXECUTIONTIME)
		{
			szExecutionTime[0] = (pItem->GetExecutionTime(tExecutionTime)) ? tExecutionTime.FormatGmt(STRING(IDS_TCHISTORY_LIST_EXECUTIONTIME_FORMAT)) : EMPTYSTRING;
			szExecutionTime[0] = (pItem->GetExecutionOBRT(nExecutionOBRT)) ? (cStringTools.ConvertUIntToPaddedString(nExecutionOBRT, 2 * sizeof(nExecutionOBRT), 16) + STRING(IDS_TCHISTORY_LIST_EXECUTIONTIME_OBRTFORMAT)) : szExecutionTime[0];
			szExecutionTime[0] = (!pItem->GetExecutionTimeOffset(dwExecutionOffset, bEarlierExecution) && szExecutionTime[0].IsEmpty()) ? STRING(IDS_TCHISTORY_LIST_EXECUTIONTIME_IMMEDIATE) : szExecutionTime[0];
			szItem += (nColumn > 0) ? (GetColumnDelimiter() + szExecutionTime[0]) : szExecutionTime[0];
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_EXECUTIONTIMEOFFSET)
		{
			for (szExecutionTime[0].Empty(); pItem->GetExecutionTimeOffset(dwExecutionOffset, bEarlierExecution); )
			{
				szExecutionTime[0] = CTimeSpan((bEarlierExecution) ? -(TIMEKEY)(dwExecutionOffset / 1000) : (TIMEKEY)(dwExecutionOffset / 1000)).Format((dwExecutionOffset >= 1000 * SECONDSPERDAY) ? STRING(IDS_TCHISTORY_LIST_EXECUTIONTIME_LONGOFFSETFORMAT) : STRING(IDS_TCHISTORY_LIST_EXECUTIONTIME_OFFSETFORMAT));
				szExecutionTime[1].Format(STRING(IDS_TCHISTORY_LIST_EXECUTIONTIME_AFTERDISPATCH), (LPCTSTR)szExecutionTime[0]);
				szExecutionTime[2].Format(STRING(IDS_TCHISTORY_LIST_EXECUTIONTIME_AFTERPREVIOUS), (LPCTSTR)szExecutionTime[0]);
				szExecutionTime[3].Format(STRING(IDS_TCHISTORY_LIST_EXECUTIONTIME_AFTERBEGIN), (LPCTSTR)szExecutionTime[0]);
				szExecutionTime[0] = ((pItem->GetAttributes() & TCFUNCTION_DISPFLAG_AUTHORIZATION) == 0) ? ((pItem->GetFlags() & TCHISTORYITEM_EXECUTIONFLAG_AFTERPREVIOUS) ? ((!pItem->GetMembership().IsEmpty() && !pItem->GetMembershipID()) ? szExecutionTime[0] : szExecutionTime[2]) : ((!pItem->GetMembership().IsEmpty() && !pItem->GetMembershipID()) ? szExecutionTime[0] : szExecutionTime[3])) : szExecutionTime[1];
				break;
			}
			szItem += (nColumn > 0) ? (GetColumnDelimiter() + szExecutionTime[0]) : szExecutionTime[0];
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_AUTHORIZATION)
		{
			szAuthorization = (pItem->GetFlags() & TCHISTORYITEM_CHECKFLAG_PREAUTHORIZED) ? STRING(IDS_TCHISTORY_LIST_AUTHORIZATION_AUTOMATIC) : STRING(IDS_TCHISTORY_LIST_AUTHORIZATION_MANUAL);
			szItem += (nColumn > 0) ? (GetColumnDelimiter() + szAuthorization) : szAuthorization;
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_PTVTIMEWINDOW)
		{
			for (szReleaseTime[0].Empty(); (tReleaseTime[0] = pItem->GetReleaseTime()) > 0; )
			{
				if (pItem->GetReleaseTimeWindow(dwReleaseOffset, tReleaseInterval, bAfterDispatch))
				{
					szReleaseTime[0].Format(STRING(IDS_TCHISTORY_LIST_PTVTIMEWINDOW_FORMAT), (LPCTSTR)tReleaseTime[0].FormatGmt(STRING(IDS_TCHISTORY_LIST_RELEASETIME_FORMAT)), (LPCTSTR)cStringTools.ConvertLongIntToStructuredString(tReleaseInterval.GetTotalSeconds()));
					szReleaseTime[1].Format(STRING(IDS_TCHISTORY_LIST_PTVTIMEWINDOW_UNLIMITEDTIMEFORMAT), (LPCTSTR)tReleaseTime[0].FormatGmt(STRING(IDS_TCHISTORY_LIST_RELEASETIME_FORMAT)));
					szReleaseTime[0] = (tReleaseInterval > 0) ? szReleaseTime[0] : szReleaseTime[1];
				}
				break;
			}
			if (pItem->GetReleaseTimeWindow(tReleaseTime[0], tReleaseTime[1]))
			{
				szReleaseTime[0].Format(STRING(IDS_TCHISTORY_LIST_PTVTIMEWINDOW_FORMAT), (LPCTSTR)tReleaseTime[0].FormatGmt(STRING(IDS_TCHISTORY_LIST_RELEASETIME_FORMAT)), (LPCTSTR)cStringTools.ConvertLongIntToStructuredString(tReleaseTime[1].GetTimeInSeconds() - tReleaseTime[0].GetTimeInSeconds()));
				szReleaseTime[1].Format(STRING(IDS_TCHISTORY_LIST_PTVTIMEWINDOW_IMMEDIATETIMEFORMAT), (LPCTSTR)tReleaseTime[1].FormatGmt(STRING(IDS_TCHISTORY_LIST_RELEASETIME_FORMAT)));
				szReleaseTime[2].Format(STRING(IDS_TCHISTORY_LIST_PTVTIMEWINDOW_UNLIMITEDTIMEFORMAT), (LPCTSTR)tReleaseTime[0].FormatGmt(STRING(IDS_TCHISTORY_LIST_RELEASETIME_FORMAT)));
				szReleaseTime[0] = (tReleaseTime[0] > 0) ? ((tReleaseTime[1] > 0) ? szReleaseTime[0] : szReleaseTime[2]) : szReleaseTime[1];
			}
			else if (pItem->GetReleaseTimeWindow(tReleaseTime[0], tReleaseInterval))
			{
				szReleaseTime[0].Format(STRING(IDS_TCHISTORY_LIST_PTVTIMEWINDOW_FORMAT), (LPCTSTR)tReleaseTime[0].FormatGmt(STRING(IDS_TCHISTORY_LIST_RELEASETIME_FORMAT)), (LPCTSTR)cStringTools.ConvertLongIntToStructuredString(tReleaseInterval.GetTotalSeconds()));
				szReleaseTime[1].Format(STRING(IDS_TCHISTORY_LIST_PTVTIMEWINDOW_IMMEDIATEOFFSETFORMAT), (LPCTSTR)cStringTools.ConvertLongIntToStructuredString(tReleaseInterval.GetTotalSeconds()));
				szReleaseTime[2].Format(STRING(IDS_TCHISTORY_LIST_PTVTIMEWINDOW_UNLIMITEDTIMEFORMAT), (LPCTSTR)tReleaseTime[0].FormatGmt(STRING(IDS_TCHISTORY_LIST_RELEASETIME_FORMAT)));
				szReleaseTime[0] = (tReleaseTime[0] > 0) ? ((tReleaseInterval > 0) ? szReleaseTime[0] : szReleaseTime[2]) : szReleaseTime[1];
			}
			for (; !pItem->GetReleaseTimeWindow(dwReleaseOffset, tReleaseInterval, bAfterDispatch) && !pItem->GetReleaseTimeWindow(tReleaseTime[0], tReleaseTime[1]) && !pItem->GetReleaseTimeWindow(tReleaseTime[0], tReleaseInterval); )
			{
				szReleaseTime[0] = (pItem->GetDispatchTime() > 0) ? STRING(IDS_TCHISTORY_LIST_PTVTIMEWINDOW_UNLIMITEDFORMAT) : STRING(IDS_TCHISTORY_LIST_PTVTIMEWINDOW_NONE);
				break;
			}
			szItem += (nColumn > 0) ? (GetColumnDelimiter() + szReleaseTime[0]) : szReleaseTime[0];
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_PTVCHECKS)
		{
			szChecks[0] = ((pItem->GetFlags() & TCHISTORYITEM_CHECKFLAG_DISABLEPTV) != TCHISTORYITEM_CHECKFLAG_DISABLEPTV) ? ((pItem->GetFlags() & TCHISTORYITEM_CHECKFLAG_OVERRIDEPTV) ? STRING(IDS_TCHISTORY_LIST_PTVCHECKS_OFF) : STRING(IDS_TCHISTORY_LIST_PTVCHECKS_ON)) : STRING(IDS_TCHISTORY_LIST_PTVCHECKS_DISABLED);
			szItem += (nColumn > 0) ? (GetColumnDelimiter() + szChecks[0]) : szChecks[0];
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_PTVRESULT)
		{
			szResult[0] = (pItem->GetResult() & TCHISTORYITEM_RESULT_PTV_GO) ? STRING(IDS_TCHISTORY_LIST_PTVRESULT_GO) : EMPTYSTRING;
			szResult[0] = (pItem->GetResult() & TCHISTORYITEM_RESULT_PTV_WAIT) ? STRING(IDS_TCHISTORY_LIST_PTVRESULT_WAIT) : szResult[0];
			szResult[0] = (pItem->GetResult() & TCHISTORYITEM_RESULT_PTV_FAIL) ? STRING(IDS_TCHISTORY_LIST_PTVRESULT_FAIL) : szResult[0];
			szItem += (nColumn > 0) ? (GetColumnDelimiter() + szResult[0]) : szResult[0];
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_PEVCHECKS)
		{
			szChecks[1] = (pItem->GetType() == TCHISTORYITEM_TYPE_PROCEDURE || pItem->GetPreExeGroupRef() >= 0) ? (((pItem->GetFlags() & TCHISTORYITEM_CHECKFLAG_DISABLEPEV) != TCHISTORYITEM_CHECKFLAG_DISABLEPEV) ? ((pItem->GetFlags() & TCHISTORYITEM_CHECKFLAG_OVERRIDEPEV) ? STRING(IDS_TCHISTORY_LIST_PEVCHECKS_OFF) : STRING(IDS_TCHISTORY_LIST_PEVCHECKS_ON)) : STRING(IDS_TCHISTORY_LIST_PEVCHECKS_DISABLED)) : STRING(IDS_TCHISTORY_LIST_PEVCHECKS_NONE);
			szItem += (nColumn > 0) ? (GetColumnDelimiter() + szChecks[1]) : szChecks[1];
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_PEVRESULT)
		{
			szResult[1] = (pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE && (pItem->GetResult() & TCHISTORYITEM_RESULT_PEV_GO)) ? STRING(IDS_TCHISTORY_LIST_PEVRESULT_GO) : EMPTYSTRING;
			szResult[1] = (pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE && (pItem->GetResult() & TCHISTORYITEM_RESULT_PEV_NOGO)) ? STRING(IDS_TCHISTORY_LIST_PEVRESULT_NOGO) : szResult[1];
			szItem += (nColumn > 0) ? (GetColumnDelimiter() + szResult[1]) : szResult[1];
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_CEVTIMEWINDOW)
		{
			for (szVerificationTime.Empty(); (pItem->GetFlags() & (TCHISTORYITEM_CHECKFLAG_OVERRIDECEV | TCHISTORYITEM_CHECKFLAG_DISABLECEV)) == 0 && pItem->GetVerificationTime() > 0; )
			{
				szVerificationTime.Format(STRING(IDS_TCHISTORY_LIST_CEVTIMEWINDOW_FORMAT), (LPCTSTR)pItem->GetVerificationTime().FormatGmt(STRING(IDS_TCHISTORY_LIST_VERIFICATIONTIME_FORMAT)), (LPCTSTR)cStringTools.ConvertLongIntToStructuredString(pItem->CalcVerificationTimeWindowSize(0, (GetTCService()->GetCommandHandlerVerificationUncertaintyTimeWindow(tTimeWindow)) ? tTimeWindow : 0).GetTotalSeconds()));
				break;
			}
			szVerificationTime = (pItem->GetDispatchTime() == 0 && szVerificationTime.IsEmpty()) ? STRING(IDS_TCHISTORY_LIST_CEVTIMEWINDOW_NONE) : szVerificationTime;
			szItem += (nColumn > 0) ? (GetColumnDelimiter() + szVerificationTime) : szVerificationTime;
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_CEVCHECKS)
		{
			szChecks[2] = (pItem->GetType() == TCHISTORYITEM_TYPE_PROCEDURE || pItem->GetExeVerGroupRef() >= 0) ? (((pItem->GetFlags() & TCHISTORYITEM_CHECKFLAG_DISABLECEV) != TCHISTORYITEM_CHECKFLAG_DISABLECEV) ? ((pItem->GetFlags() & TCHISTORYITEM_CHECKFLAG_OVERRIDECEV) ? STRING(IDS_TCHISTORY_LIST_CEVCHECKS_OFF) : STRING(IDS_TCHISTORY_LIST_CEVCHECKS_ON)) : STRING(IDS_TCHISTORY_LIST_CEVCHECKS_DISABLED)) : STRING(IDS_TCHISTORY_LIST_CEVCHECKS_NONE);
			szItem += (nColumn > 0) ? (GetColumnDelimiter() + szChecks[2]) : szChecks[2];
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_CEVRESULT)
		{
			for (szResult[2].Empty(); pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE; )
			{
				if (pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE), nVerificationState, nVerificationReason))
				{
					szVerificationState.Format(STRING(IDS_TCHISTORY_LIST_CEVRESULT_FORMAT), MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE), (nVerificationState == TCHISTORYITEM_RESULT_CEV_IDLE) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_IDLE) : ((nVerificationState == TCHISTORYITEM_RESULT_CEV_PENDING) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_PENDING) : ((nVerificationState == TCHISTORYITEM_RESULT_CEV_PASSED) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_PASSED) : ((nVerificationState == TCHISTORYITEM_RESULT_CEV_FAILED) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_FAILED) : ((nVerificationState == TCHISTORYITEM_RESULT_CEV_UNKNOWN) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_UNKNOWN) : ((nVerificationState == TCHISTORYITEM_RESULT_CEV_UNVERIFIED) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_UNVERIFIED) : EMPTYSTRING))))));
					szResult[2] += (!szResult[2].IsEmpty()) ? (STRING(IDS_TCHISTORY_LIST_CEVRESULT_SEPARATOR) + szVerificationState) : szVerificationState;
				}
				if (pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START), nVerificationState, nVerificationReason))
				{
					szVerificationState.Format(STRING(IDS_TCHISTORY_LIST_CEVRESULT_FORMAT), MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START), (nVerificationState == TCHISTORYITEM_RESULT_CEV_IDLE) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_IDLE) : ((nVerificationState == TCHISTORYITEM_RESULT_CEV_PENDING) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_PENDING) : ((nVerificationState == TCHISTORYITEM_RESULT_CEV_PASSED) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_PASSED) : ((nVerificationState == TCHISTORYITEM_RESULT_CEV_FAILED) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_FAILED) : ((nVerificationState == TCHISTORYITEM_RESULT_CEV_UNKNOWN) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_UNKNOWN) : ((nVerificationState == TCHISTORYITEM_RESULT_CEV_UNVERIFIED) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_UNVERIFIED) : EMPTYSTRING))))));
					szResult[2] += (!szResult[2].IsEmpty()) ? (STRING(IDS_TCHISTORY_LIST_CEVRESULT_SEPARATOR) + szVerificationState) : szVerificationState;
				}
				if (pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS), nVerificationState, nVerificationReason))
				{
					szVerificationState.Format(STRING(IDS_TCHISTORY_LIST_CEVRESULT_FORMAT), MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS), (nVerificationState == TCHISTORYITEM_RESULT_CEV_IDLE) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_IDLE) : ((nVerificationState == TCHISTORYITEM_RESULT_CEV_PENDING) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_PENDING) : ((nVerificationState == TCHISTORYITEM_RESULT_CEV_PASSED) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_PASSED) : ((nVerificationState == TCHISTORYITEM_RESULT_CEV_FAILED) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_FAILED) : ((nVerificationState == TCHISTORYITEM_RESULT_CEV_UNKNOWN) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_UNKNOWN) : ((nVerificationState == TCHISTORYITEM_RESULT_CEV_UNVERIFIED) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_UNVERIFIED) : EMPTYSTRING))))));
					szResult[2] += (!szResult[2].IsEmpty()) ? (STRING(IDS_TCHISTORY_LIST_CEVRESULT_SEPARATOR) + szVerificationState) : szVerificationState;
				}
				if (pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION), nVerificationState, nVerificationReason))
				{
					szVerificationState.Format(STRING(IDS_TCHISTORY_LIST_CEVRESULT_FORMAT), MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION), (nVerificationState == TCHISTORYITEM_RESULT_CEV_IDLE) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_IDLE) : ((nVerificationState == TCHISTORYITEM_RESULT_CEV_PENDING) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_PENDING) : ((nVerificationState == TCHISTORYITEM_RESULT_CEV_PASSED) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_PASSED) : ((nVerificationState == TCHISTORYITEM_RESULT_CEV_FAILED) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_FAILED) : ((nVerificationState == TCHISTORYITEM_RESULT_CEV_UNKNOWN) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_UNKNOWN) : ((nVerificationState == TCHISTORYITEM_RESULT_CEV_UNVERIFIED) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_UNVERIFIED) : EMPTYSTRING))))));
					szResult[2] += (!szResult[2].IsEmpty()) ? (STRING(IDS_TCHISTORY_LIST_CEVRESULT_SEPARATOR) + szVerificationState) : szVerificationState;
				}
				if (szResult[2].IsEmpty())
				{
					szResult[2] = (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_IDLE) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_IDLE) : EMPTYSTRING;
					szResult[2] = (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_PENDING) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_PENDING) : szResult[2];
					szResult[2] = (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_PASSED) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_PASSED) : szResult[2];
					szResult[2] = (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_FAILED) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_FAILED) : szResult[2];
					szResult[2] = (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_UNKNOWN) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_UNKNOWN) : szResult[2];
					szResult[2] = (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_UNVERIFIED) ? STRING(IDS_TCHISTORY_LIST_CEVRESULT_UNVERIFIED) : szResult[2];
				}
				break;
			}
			szItem += (nColumn > 0) ? (GetColumnDelimiter() + szResult[2]) : szResult[2];
			continue;
		}
		if (LookupColumnName(szColumn) == TCHISTORY_TITLEITEM_STATUS)
		{
			szStatus = (pItem->GetStatus() == TCHISTORYITEM_STATUS_RELEASED) ? ((pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE) ? STRING(IDS_TCHISTORY_LIST_STATUS_RELEASED) : STRING(IDS_TCHISTORY_LIST_STATUS_EXECUTED)) : EMPTYSTRING;
			szStatus = (pItem->GetStatus() == TCHISTORYITEM_STATUS_NOTRELEASED) ? ((pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE) ? STRING(IDS_TCHISTORY_LIST_STATUS_NOTRELEASED) : STRING(IDS_TCHISTORY_LIST_STATUS_NOTEXECUTED)) : szStatus;
			szStatus = (pItem->GetStatus() == TCHISTORYITEM_STATUS_FAILEDRELEASE) ? ((pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE) ? STRING(IDS_TCHISTORY_LIST_STATUS_FAILEDRELEASE) : STRING(IDS_TCHISTORY_LIST_STATUS_FAILEDEXECUTION)) : szStatus;
			szStatus = (pItem->GetStatus() == TCHISTORYITEM_STATUS_SENT) ? ((pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE) ? STRING(IDS_TCHISTORY_LIST_STATUS_SENT) : STRING(IDS_TCHISTORY_LIST_STATUS_EXECUTED)) : szStatus;
			szStatus = (pItem->GetStatus() == TCHISTORYITEM_STATUS_FAILEDSEND) ? ((pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE) ? STRING(IDS_TCHISTORY_LIST_STATUS_FAILEDSEND) : STRING(IDS_TCHISTORY_LIST_STATUS_FAILEDEXECUTION)) : szStatus;
			szStatus = (pItem->GetStatus() == TCHISTORYITEM_STATUS_UPLINKED) ? ((pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE) ? STRING(IDS_TCHISTORY_LIST_STATUS_UPLINKED) : STRING(IDS_TCHISTORY_LIST_STATUS_EXECUTED)) : szStatus;
			szStatus = (pItem->GetStatus() == TCHISTORYITEM_STATUS_FAILEDUPLINK) ? ((pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE) ? STRING(IDS_TCHISTORY_LIST_STATUS_FAILEDUPLINK) : STRING(IDS_TCHISTORY_LIST_STATUS_FAILEDEXECUTION)) : szStatus;
			if ((pItem->GetStatus() == TCHISTORYITEM_STATUS_RELEASED || pItem->GetStatus() == TCHISTORYITEM_STATUS_SENT || pItem->GetStatus() == TCHISTORYITEM_STATUS_UPLINKED) && pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE && (pItem->GetFlags() & (TCHISTORYITEM_CHECKFLAG_OVERRIDECEV | TCHISTORYITEM_CHECKFLAG_DISABLECEV)) == 0 && pItem->GetExeVerGroupRef() >= 0)
			{
				szStatus += (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_PENDING) ? (CString(STRING(IDS_TCHISTORY_LIST_STATUS_SEPARATOR)) + CString(STRING(IDS_TCHISTORY_LIST_STATUS_VERIFYING))) : EMPTYSTRING;
				szStatus += (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_PASSED) ? (CString(STRING(IDS_TCHISTORY_LIST_STATUS_SEPARATOR)) + CString(STRING(IDS_TCHISTORY_LIST_STATUS_SUCCESSFUL))) : EMPTYSTRING;
				szStatus += (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_FAILED) ? (CString(STRING(IDS_TCHISTORY_LIST_STATUS_SEPARATOR)) + CString(STRING(IDS_TCHISTORY_LIST_STATUS_FAILED))) : EMPTYSTRING;
				szStatus += (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_UNKNOWN) ? (CString(STRING(IDS_TCHISTORY_LIST_STATUS_SEPARATOR)) + CString(STRING(IDS_TCHISTORY_LIST_STATUS_UNKNOWN))) : EMPTYSTRING;
				szStatus += (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_UNVERIFIED) ? (CString(STRING(IDS_TCHISTORY_LIST_STATUS_SEPARATOR)) + CString(STRING(IDS_TCHISTORY_LIST_STATUS_UNVERIFIED))) : EMPTYSTRING;
			}
			szStatus += (pItem->GetStatus() == TCHISTORYITEM_STATUS_NOTRELEASED  &&  pItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE  &&  pItem->GetAuthorizationStatus() == TCHISTORYITEM_AUTHORIZATIONSTATUS_DENIED) ? (CString(SPACE) + STRING(IDS_TCHISTORY_LIST_STATUS_DENIED)) : EMPTYSTRING;
			szItem += (nColumn > 0) ? (GetColumnDelimiter() + szStatus) : szStatus;
			continue;
		}
	}
	return szItem;
}
BOOL CTCHistoryView::TranslateTelecommand(CONST CTCHistoryItem *pItem, CTextViewAttribute *pAttribute) CONST
{
	INT  nColumn;
	INT  nColumns;
	INT  nColumnID;
	BOOL  bAlertFlag;
	CTextViewAttribute  cAttribute;

	for (nColumn = 0, nColumns = (INT)m_wndHeaderCtrl.m_szColumnsText.GetSize(), pAttribute->Copy(&cAttribute); nColumn < nColumns; nColumn++)
	{
		pAttribute->SetColumnColor(nColumn, LookupColumnColor(nColumn));
		continue;
	}
	for (nColumnID = (pItem->IsAlerted() != TCHISTORYITEM_ALERTTYPE_NONE); nColumnID & TCHISTORY_TITLEITEMS_ALL; nColumnID <<= 1)
	{
		if (pItem->IsAlerted(nColumnID) != TCHISTORYITEM_ALERTTYPE_NONE  &&  FindColumnIndex(LookupColumnName(nColumnID)) < 0)
		{
			pAttribute->SetColumnBlinking(-1, TRUE);
			return TRUE;
		}
	}
	for (nColumn = 0, nColumns = (pItem->IsAlerted() != TCHISTORYITEM_ALERTTYPE_NONE) ? (INT)m_wndHeaderCtrl.m_szColumnsText.GetSize() : 0, bAlertFlag = FALSE; nColumn < nColumns; nColumn++)
	{
		if (pItem->IsAlerted(LookupColumnName(m_wndHeaderCtrl.m_szColumnsText.GetAt(nColumn))) != TCHISTORYITEM_ALERTTYPE_NONE)
		{
			pAttribute->SetColumnBlinking(nColumn, TRUE);
			bAlertFlag = TRUE;
			continue;
		}
		pAttribute->SetColumnBlinking(nColumn, FALSE);
	}
	if (pItem->IsAlerted() != TCHISTORYITEM_ALERTTYPE_NONE  &&  !bAlertFlag) pAttribute->SetColumnBlinking(-1, TRUE);
	return TRUE;
}

BOOL CTCHistoryView::AdjustTelecommandAlerts(CONST CTCItem *pAlertItem, CTCHistoryItem *pItem, BOOL bAlert) CONST
{
	UINT  nState[2];
	UINT  nReason[2];
	UINT  nResult[2];
	CTimeTag  tAcknowledgeTime;
	CTCHistoryItem  cItem;

	if (pAlertItem->GetFlags() & TCITEM_ACKNOWLEDGEFLAG_ALL)
	{
		for (cItem.CTCItem::Copy(pAlertItem); (nResult[0] = (pAlertItem->GetResult() & (TCITEM_RESULT_CEV_FAILED | TCITEM_RESULT_CEV_UNVERIFIED))) && nResult[0] != (nResult[1] = (pItem->GetResult() & (TCHISTORYITEM_RESULT_CEV_FAILED | TCHISTORYITEM_RESULT_CEV_UNVERIFIED))) && bAlert; )
		{
			GetParent()->Alert(&cItem);
			break;
		}
		for (tAcknowledgeTime = pItem->GetAcknowledgeTime(); pItem->CTCItem::Copy(pAlertItem); )
		{
			for (pItem->SetFlags(pItem->GetFlags() & ~TCHISTORYITEM_ACKNOWLEDGEFLAG_ALL); pItem->GetAcknowledgeTime() != tAcknowledgeTime || tAcknowledgeTime == 0; )
			{
				pItem->Alert(TCHISTORYITEM_ALERTTYPE_ANY);
				break;
			}
			return TRUE;
		}
		return FALSE;
	}
	for (cItem.CTCItem::Copy(pAlertItem); pAlertItem->GetFlags() & TCITEM_ACKNOWLEDGEFLAG_ACCEPTANCE; )
	{
		if (pAlertItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE), nState[0], nReason[0]) && nState[0] == TCITEM_RESULT_CEV_PASSED && (!pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE), nState[1], nReason[1]) || nState[1] != TCHISTORYITEM_RESULT_CEV_PASSED))
		{
			for (pItem->Alert(TCHISTORYITEM_ALERTTYPE_INFORMATION, TCHISTORY_TITLEITEM_CEVRESULT, STRING(IDS_TCHISTORY_MESSAGE_VERIFICATIONSTAGE_ACCEPTANCE_SUCCESS), FALSE); bAlert; )
			{
				GetParent()->Alert(&cItem, TCVERIFICATIONSTAGE_ACCEPTANCE);
				break;
			}
		}
		break;
	}
	if (pAlertItem->GetFlags() & TCITEM_ACKNOWLEDGEFLAG_START)
	{
		if (pAlertItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START), nState[0], nReason[0]) && nState[0] == TCITEM_RESULT_CEV_PASSED && (!pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START), nState[1], nReason[1]) || nState[1] != TCHISTORYITEM_RESULT_CEV_PASSED))
		{
			for (pItem->Alert(TCHISTORYITEM_ALERTTYPE_INFORMATION, TCHISTORY_TITLEITEM_CEVRESULT, STRING(IDS_TCHISTORY_MESSAGE_VERIFICATIONSTAGE_START_SUCCESS), FALSE); bAlert; )
			{
				GetParent()->Alert(&cItem, TCVERIFICATIONSTAGE_START);
				break;
			}
		}
	}
	if (pAlertItem->GetFlags() & TCITEM_ACKNOWLEDGEFLAG_PROGRESS)
	{
		if (pAlertItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS), nState[0], nReason[0]) && nState[0] == TCITEM_RESULT_CEV_PASSED && (!pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS), nState[1], nReason[1]) || nState[1] != TCHISTORYITEM_RESULT_CEV_PASSED))
		{
			for (pItem->Alert(TCHISTORYITEM_ALERTTYPE_INFORMATION, TCHISTORY_TITLEITEM_CEVRESULT, STRING(IDS_TCHISTORY_MESSAGE_VERIFICATIONSTAGE_PROGRESS_SUCCESS), FALSE); bAlert; )
			{
				GetParent()->Alert(&cItem, TCVERIFICATIONSTAGE_PROGRESS);
				break;
			}
		}
	}
	if (pAlertItem->GetFlags() & TCITEM_ACKNOWLEDGEFLAG_COMPLETION)
	{
		if (pAlertItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION), nState[0], nReason[0]) && nState[0] == TCITEM_RESULT_CEV_PASSED && (!pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION), nState[1], nReason[1]) || nState[1] != TCHISTORYITEM_RESULT_CEV_PASSED))
		{
			for (pItem->Alert(TCHISTORYITEM_ALERTTYPE_INFORMATION, TCHISTORY_TITLEITEM_CEVRESULT, STRING(IDS_TCHISTORY_MESSAGE_VERIFICATIONSTAGE_COMPLETION_SUCCESS), FALSE); bAlert; )
			{
				GetParent()->Alert(&cItem, TCVERIFICATIONSTAGE_COMPLETION);
				break;
			}
		}
	}
	if ((pAlertItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE), nState[0], nReason[0]) && nState[0] == TCITEM_RESULT_CEV_FAILED) && (!pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE), nState[1], nReason[1]) || nState[1] != TCHISTORYITEM_RESULT_CEV_FAILED) && bAlert) GetParent()->Alert(&cItem, TCVERIFICATIONSTAGE_ACCEPTANCE);
	if ((pAlertItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START), nState[0], nReason[0]) && nState[0] == TCITEM_RESULT_CEV_FAILED) && (!pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START), nState[1], nReason[1]) || nState[1] != TCHISTORYITEM_RESULT_CEV_FAILED) && bAlert) GetParent()->Alert(&cItem, TCVERIFICATIONSTAGE_START);
	if ((pAlertItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS), nState[0], nReason[0]) && nState[0] == TCITEM_RESULT_CEV_FAILED) && (!pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS), nState[1], nReason[1]) || nState[1] != TCHISTORYITEM_RESULT_CEV_FAILED) && bAlert) GetParent()->Alert(&cItem, TCVERIFICATIONSTAGE_PROGRESS);
	if ((pAlertItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION), nState[0], nReason[0]) && nState[0] == TCITEM_RESULT_CEV_FAILED) && (!pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION), nState[1], nReason[1]) || nState[1] != TCHISTORYITEM_RESULT_CEV_FAILED) && bAlert) GetParent()->Alert(&cItem, TCVERIFICATIONSTAGE_COMPLETION);
	if ((nResult[0] = (pAlertItem->GetResult() & (TCITEM_RESULT_CEV_FAILED | TCITEM_RESULT_CEV_UNVERIFIED))) && nResult[0] != (nResult[1] = (pItem->GetResult() & (TCHISTORYITEM_RESULT_CEV_FAILED | TCHISTORYITEM_RESULT_CEV_UNVERIFIED))) && bAlert) GetParent()->Alert(&cItem);
	if (pAlertItem->GetStatus() != TCITEM_STATUS_RELEASED  &&  pAlertItem->GetStatus() != TCITEM_STATUS_SENT  &&  pAlertItem->GetStatus() != TCITEM_STATUS_UPLINKED  &&  pAlertItem->GetStatus() != TCITEM_STATUS_EXECUTED)
	{
		if (((nResult[0] = (pAlertItem->GetResult() & TCITEM_RESULT_PTV_FAIL)) && nResult[0] != (nResult[1] = (pItem->GetResult() & TCHISTORYITEM_RESULT_PTV_FAIL))) || ((nResult[0] = (pAlertItem->GetResult() & TCITEM_RESULT_PEV_NOGO)) && nResult[0] != (nResult[1] = (pItem->GetResult() & TCHISTORYITEM_RESULT_PEV_NOGO)))) pItem->Alert(TCHISTORYITEM_ALERTTYPE_ERROR, TCHISTORY_TITLEITEM_TRANSMISSIONTIME, (pAlertItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE) ? STRING(IDS_TCHISTORY_MESSAGE_RELEASE_FAILURE) : STRING(IDS_TCHISTORY_MESSAGE_EXECUTION_FAILURE));
		if ((nResult[0] = (pAlertItem->GetResult() & TCITEM_RESULT_PTV_FAIL)) && nResult[0] != (nResult[1] = (pItem->GetResult() & TCHISTORYITEM_RESULT_PTV_FAIL))) pItem->Alert(TCHISTORYITEM_ALERTTYPE_ERROR, TCHISTORY_TITLEITEM_PTVRESULT, (pAlertItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE) ? STRING(IDS_TCHISTORY_MESSAGE_RELEASE_FAILURE) : STRING(IDS_TCHISTORY_MESSAGE_EXECUTION_FAILURE));
		if ((nResult[0] = (pAlertItem->GetResult() & TCITEM_RESULT_PEV_NOGO)) && nResult[0] != (nResult[1] = (pItem->GetResult() & TCHISTORYITEM_RESULT_PEV_NOGO))) pItem->Alert(TCHISTORYITEM_ALERTTYPE_ERROR, TCHISTORY_TITLEITEM_PEVRESULT, (pAlertItem->GetType() != TCHISTORYITEM_TYPE_PROCEDURE) ? STRING(IDS_TCHISTORY_MESSAGE_RELEASE_FAILURE) : STRING(IDS_TCHISTORY_MESSAGE_EXECUTION_FAILURE));
	}
	if ((nResult[0] = (pAlertItem->GetResult() & TCITEM_RESULT_CEV_FAILED)) && nResult[0] != (nResult[1] = (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_FAILED))) pItem->Alert(TCHISTORYITEM_ALERTTYPE_ERROR, TCHISTORY_TITLEITEM_CEVRESULT, STRING(IDS_TCHISTORY_MESSAGE_VERIFICATION_FAILURE), FALSE);
	if (((nResult[0] = (pAlertItem->GetResult() & TCITEM_RESULT_CEV_UNKNOWN)) && nResult[0] != (nResult[1] = (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_UNKNOWN))) || ((nResult[0] = (pAlertItem->GetResult() & TCITEM_RESULT_CEV_UNVERIFIED)) && nResult[0] != (nResult[1] = (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_UNVERIFIED)))) pItem->Alert(TCHISTORYITEM_ALERTTYPE_ERROR, TCHISTORY_TITLEITEM_CEVRESULT, STRING(IDS_TCHISTORY_MESSAGE_VERIFICATION_ILLEGAL), FALSE);
	return pItem->CTCItem::Copy(pAlertItem);
}

BOOL CTCHistoryView::CheckTelecommandFilter(CONST CTCItem *pItem) CONST
{
	BOOL  bStage;
	UINT  nState;
	UINT  nReason;

	if (pItem->GetStatus() == TCITEM_STATUS_RELEASED || pItem->GetStatus() == TCITEM_STATUS_NOTRELEASED || pItem->GetStatus() == TCITEM_STATUS_FAILEDRELEASE || pItem->GetStatus() == TCITEM_STATUS_SENT || pItem->GetStatus() == TCITEM_STATUS_FAILEDSEND || pItem->GetStatus() == TCITEM_STATUS_UPLINKED || pItem->GetStatus() == TCITEM_STATUS_FAILEDUPLINK)
	{
		if ((pItem->GetFlags() & TCITEM_LINKAGEFLAG_BLOCKED) != TCITEM_LINKAGEFLAG_BLOCKED || !pItem->GetReleaseBlockID())
		{
			if ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYCOMPUTER) && pItem->GetComputerName().CompareNoCase(m_szFilterComputer)) return FALSE;
			if (((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYMANUALSTACK) && pItem->GetSourceType() != TCITEM_SOURCETYPE_MANUALSTACK) || ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYAUTOMATICSTACK) && pItem->GetSourceType() != TCITEM_SOURCETYPE_AUTOMATICSTACK) || ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYPROCEDURESMONITOR) && pItem->GetSourceType() != TCITEM_SOURCETYPE_PROCEDURESMONITOR)) return FALSE;
			if (((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYTELECOMMAND) && pItem->GetType() != TCITEM_TYPE_FUNCTION) || ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYTELECOMMANDITEM) && pItem->GetName() != m_szFilterTelecommand[0]) || ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYTELECOMMANDSEQUENCE) && pItem->GetMembership() != m_szFilterTelecommand[1])) return FALSE;
			if (((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYTELECOMMANDTYPEIMMEDIATE) && (pItem->GetFlags() & TCITEM_EXECUTIONFLAG_IMMEDIATE) != TCITEM_EXECUTIONFLAG_IMMEDIATE) || ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYTELECOMMANDTYPETIMETAGGED) && (pItem->GetFlags() & TCITEM_EXECUTIONFLAG_TIMETAGGED) != TCITEM_EXECUTIONFLAG_TIMETAGGED) || ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE1STSTEP) && (pItem->GetFlags() & TCITEM_EXECUTIONFLAG_1STSTEP) != TCITEM_EXECUTIONFLAG_1STSTEP) || ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE2NDSTEP) && (pItem->GetFlags() & TCITEM_EXECUTIONFLAG_2NDSTEP) != TCITEM_EXECUTIONFLAG_2NDSTEP)) return FALSE;
			if (((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONPASSED) && (pItem->GetResult() & (TCHISTORYITEM_RESULT_PTV_GO | TCHISTORYITEM_RESULT_PEV_GO)) != (TCHISTORYITEM_RESULT_PTV_GO | TCHISTORYITEM_RESULT_PEV_GO)) || ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONFAILED) && (pItem->GetResult() & (TCHISTORYITEM_RESULT_PTV_GO | TCHISTORYITEM_RESULT_PEV_GO)) == (TCHISTORYITEM_RESULT_PTV_GO | TCHISTORYITEM_RESULT_PEV_GO))) return FALSE;
			if ((((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEPASSED) || (m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTPASSED) || (m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSPASSED) || (m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONPASSED)) && (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_PASSED) != TCHISTORYITEM_RESULT_CEV_PASSED) || (((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEFAILED) || (m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTFAILED) || (m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSFAILED) || (m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONFAILED)) && (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_FAILED) != TCHISTORYITEM_RESULT_CEV_FAILED) || (((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNKNOWN) || (m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNKNOWN) || (m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNKNOWN) || (m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNKNOWN)) && (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_UNKNOWN) != TCHISTORYITEM_RESULT_CEV_UNKNOWN) || (((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNVERIFIED) || (m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNVERIFIED) || (m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNVERIFIED) || (m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNVERIFIED)) && (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_UNVERIFIED) != TCHISTORYITEM_RESULT_CEV_UNVERIFIED)) return FALSE;
			for (bStage = pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE), nState, nReason); ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEPASSED) && (!bStage || nState != TCHISTORYITEM_RESULT_CEV_PASSED)) || ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEFAILED) && (!bStage || nState != TCHISTORYITEM_RESULT_CEV_FAILED)) || ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNKNOWN) && (!bStage || nState != TCHISTORYITEM_RESULT_CEV_UNKNOWN)) || ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNVERIFIED) && (!bStage || nState != TCHISTORYITEM_RESULT_CEV_UNVERIFIED)); ) return FALSE;
			for (bStage = pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START), nState, nReason); ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTPASSED) && (!bStage || nState != TCHISTORYITEM_RESULT_CEV_PASSED)) || ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTFAILED) && (!bStage || nState != TCHISTORYITEM_RESULT_CEV_FAILED)) || ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNKNOWN) && (!bStage || nState != TCHISTORYITEM_RESULT_CEV_UNKNOWN)) || ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNVERIFIED) && (!bStage || nState != TCHISTORYITEM_RESULT_CEV_UNVERIFIED)); ) return FALSE;
			for (bStage = pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS), nState, nReason); ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSPASSED) && (!bStage || nState != TCHISTORYITEM_RESULT_CEV_PASSED)) || ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSFAILED) && (!bStage || nState != TCHISTORYITEM_RESULT_CEV_FAILED)) || ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNKNOWN) && (!bStage || nState != TCHISTORYITEM_RESULT_CEV_UNKNOWN)) || ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNVERIFIED) && (!bStage || nState != TCHISTORYITEM_RESULT_CEV_UNVERIFIED)); ) return FALSE;
			for (bStage = pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION), nState, nReason); ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONPASSED) && (!bStage || nState != TCHISTORYITEM_RESULT_CEV_PASSED)) || ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONFAILED) && (!bStage || nState != TCHISTORYITEM_RESULT_CEV_FAILED)) || ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNKNOWN) && (!bStage || nState != TCHISTORYITEM_RESULT_CEV_UNKNOWN)) || ((m_nFilterMode[0] & TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNVERIFIED) && (!bStage || nState != TCHISTORYITEM_RESULT_CEV_UNVERIFIED)); ) return FALSE;
			return TRUE;
		}
	}
	return FALSE;
}

CString CTCHistoryView::LookupColumnName(UINT nColumn) CONST
{
	if (nColumn == TCHISTORY_TITLEITEM_NUMBER) return STRING(IDS_TCHISTORY_TITLEITEM_NUMBER);
	if (nColumn == TCHISTORY_TITLEITEM_NAME) return STRING(IDS_TCHISTORY_TITLEITEM_NAME);
	if (nColumn == TCHISTORY_TITLEITEM_COMPUTER) return STRING(IDS_TCHISTORY_TITLEITEM_COMPUTER);
	if (nColumn == TCHISTORY_TITLEITEM_COMMANDSOURCE) return STRING(IDS_TCHISTORY_TITLEITEM_COMMANDSOURCE);
	if (nColumn == TCHISTORY_TITLEITEM_DESCRIPTION) return STRING(IDS_TCHISTORY_TITLEITEM_DESCRIPTION);
	if (nColumn == TCHISTORY_TITLEITEM_CATEGORY) return STRING(IDS_TCHISTORY_TITLEITEM_CATEGORY);
	if (nColumn == TCHISTORY_TITLEITEM_SUBSYSTEM) return STRING(IDS_TCHISTORY_TITLEITEM_SUBSYSTEM);
	if (nColumn == TCHISTORY_TITLEITEM_ARGUMENTS) return STRING(IDS_TCHISTORY_TITLEITEM_ARGUMENTS);
	if (nColumn == TCHISTORY_TITLEITEM_FLAGS) return STRING(IDS_TCHISTORY_TITLEITEM_FLAGS);
	if (nColumn == TCHISTORY_TITLEITEM_TCPACKET) return STRING(IDS_TCHISTORY_TITLEITEM_TCPACKET);
	if (nColumn == TCHISTORY_TITLEITEM_DISPATCHTIME) return STRING(IDS_TCHISTORY_TITLEITEM_DISPATCHTIME);
	if (nColumn == TCHISTORY_TITLEITEM_RELEASETIME) return STRING(IDS_TCHISTORY_TITLEITEM_RELEASETIME);
	if (nColumn == TCHISTORY_TITLEITEM_RELEASETIMEOFFSET) return STRING(IDS_TCHISTORY_TITLEITEM_RELEASETIMEOFFSET);
	if (nColumn == TCHISTORY_TITLEITEM_TRANSMISSIONTIME) return STRING(IDS_TCHISTORY_TITLEITEM_TRANSMISSIONTIME);
	if (nColumn == TCHISTORY_TITLEITEM_EXECUTIONTIME) return STRING(IDS_TCHISTORY_TITLEITEM_EXECUTIONTIME);
	if (nColumn == TCHISTORY_TITLEITEM_EXECUTIONTIMEOFFSET) return STRING(IDS_TCHISTORY_TITLEITEM_EXECUTIONTIMEOFFSET);
	if (nColumn == TCHISTORY_TITLEITEM_AUTHORIZATION) return STRING(IDS_TCHISTORY_TITLEITEM_AUTHORIZATION);
	if (nColumn == TCHISTORY_TITLEITEM_PTVTIMEWINDOW) return STRING(IDS_TCHISTORY_TITLEITEM_PTVTIMEWINDOW);
	if (nColumn == TCHISTORY_TITLEITEM_PTVCHECKS) return STRING(IDS_TCHISTORY_TITLEITEM_PTVCHECKS);
	if (nColumn == TCHISTORY_TITLEITEM_PTVRESULT) return STRING(IDS_TCHISTORY_TITLEITEM_PTVRESULT);
	if (nColumn == TCHISTORY_TITLEITEM_PEVCHECKS) return STRING(IDS_TCHISTORY_TITLEITEM_PEVCHECKS);
	if (nColumn == TCHISTORY_TITLEITEM_PEVRESULT) return STRING(IDS_TCHISTORY_TITLEITEM_PEVRESULT);
	if (nColumn == TCHISTORY_TITLEITEM_CEVTIMEWINDOW) return STRING(IDS_TCHISTORY_TITLEITEM_CEVTIMEWINDOW);
	if (nColumn == TCHISTORY_TITLEITEM_CEVCHECKS) return STRING(IDS_TCHISTORY_TITLEITEM_CEVCHECKS);
	if (nColumn == TCHISTORY_TITLEITEM_CEVRESULT) return STRING(IDS_TCHISTORY_TITLEITEM_CEVRESULT);
	if (nColumn == TCHISTORY_TITLEITEM_STATUS) return STRING(IDS_TCHISTORY_TITLEITEM_STATUS);
	return EMPTYSTRING;
}
UINT CTCHistoryView::LookupColumnName(LPCTSTR pszColumn) CONST
{
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_NUMBER))) return TCHISTORY_TITLEITEM_NUMBER;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_NAME))) return TCHISTORY_TITLEITEM_NAME;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_COMPUTER))) return TCHISTORY_TITLEITEM_COMPUTER;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_COMMANDSOURCE))) return TCHISTORY_TITLEITEM_COMMANDSOURCE;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_DESCRIPTION))) return TCHISTORY_TITLEITEM_DESCRIPTION;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_CATEGORY))) return TCHISTORY_TITLEITEM_CATEGORY;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_SUBSYSTEM))) return TCHISTORY_TITLEITEM_SUBSYSTEM;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_ARGUMENTS))) return TCHISTORY_TITLEITEM_ARGUMENTS;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_FLAGS))) return TCHISTORY_TITLEITEM_FLAGS;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_TCPACKET))) return TCHISTORY_TITLEITEM_TCPACKET;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_DISPATCHTIME))) return TCHISTORY_TITLEITEM_DISPATCHTIME;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_RELEASETIME))) return TCHISTORY_TITLEITEM_RELEASETIME;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_RELEASETIMEOFFSET))) return TCHISTORY_TITLEITEM_RELEASETIMEOFFSET;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_TRANSMISSIONTIME))) return TCHISTORY_TITLEITEM_TRANSMISSIONTIME;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_EXECUTIONTIME))) return TCHISTORY_TITLEITEM_EXECUTIONTIME;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_EXECUTIONTIMEOFFSET))) return TCHISTORY_TITLEITEM_EXECUTIONTIMEOFFSET;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_AUTHORIZATION))) return TCHISTORY_TITLEITEM_AUTHORIZATION;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_PTVTIMEWINDOW))) return TCHISTORY_TITLEITEM_PTVTIMEWINDOW;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_PTVCHECKS))) return TCHISTORY_TITLEITEM_PTVCHECKS;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_PTVRESULT))) return TCHISTORY_TITLEITEM_PTVRESULT;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_PEVCHECKS))) return TCHISTORY_TITLEITEM_PEVCHECKS;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_PEVRESULT))) return TCHISTORY_TITLEITEM_PEVRESULT;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_CEVTIMEWINDOW))) return TCHISTORY_TITLEITEM_CEVTIMEWINDOW;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_CEVCHECKS))) return TCHISTORY_TITLEITEM_CEVCHECKS;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_CEVRESULT))) return TCHISTORY_TITLEITEM_CEVRESULT;
	if (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_STATUS))) return TCHISTORY_TITLEITEM_STATUS;
	return 0;
}

INT CTCHistoryView::LookupColumnsName(CONST CUIntArray &nColumns, CStringArray &szColumns) CONST
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

COLORREF CTCHistoryView::LookupColumnColor(UINT nColumn) CONST
{
	if (nColumn == TCHISTORY_TITLEITEM_NUMBER) return GetDatabase()->GetTCHistoryNumberColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_NAME) return GetDatabase()->GetTCHistoryNameColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_COMPUTER) return GetDatabase()->GetTCHistoryComputerColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_COMMANDSOURCE) return GetDatabase()->GetTCHistoryCommandSourceColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_DESCRIPTION) return GetDatabase()->GetTCHistoryDescriptionColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_CATEGORY) return GetDatabase()->GetTCHistoryCategoryColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_SUBSYSTEM) return GetDatabase()->GetTCHistorySubSystemColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_ARGUMENTS) return GetDatabase()->GetTCHistoryArgumentsColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_FLAGS) return GetDatabase()->GetTCHistoryFlagsColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_TCPACKET) return GetDatabase()->GetTCHistoryTCPacketColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_DISPATCHTIME) return GetDatabase()->GetTCHistoryDispatchTimeColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_RELEASETIME) return GetDatabase()->GetTCHistoryReleaseTimeColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_RELEASETIMEOFFSET) return GetDatabase()->GetTCHistoryReleaseTimeOffsetColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_TRANSMISSIONTIME) return GetDatabase()->GetTCHistoryTransmissionTimeColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_EXECUTIONTIME) return GetDatabase()->GetTCHistoryExcutionTimeColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_EXECUTIONTIMEOFFSET) return GetDatabase()->GetTCHistoryExcutionTimeOffsetColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_AUTHORIZATION) return GetDatabase()->GetTCHistoryAuthorizationColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_PTVTIMEWINDOW) return GetDatabase()->GetTCHistoryPTVTimeWindowColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_PTVCHECKS) return GetDatabase()->GetTCHistoryPTVChecksColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_PTVRESULT) return GetDatabase()->GetTCHistoryPTVResultColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_PEVCHECKS) return GetDatabase()->GetTCHistoryPEVChecksColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_PEVRESULT) return GetDatabase()->GetTCHistoryPEVResultColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_CEVTIMEWINDOW) return GetDatabase()->GetTCHistoryCEVTimeWindowColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_CEVCHECKS) return GetDatabase()->GetTCHistoryCEVChecksColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_CEVRESULT) return GetDatabase()->GetTCHistoryCEVResultColumnColor();
	if (nColumn == TCHISTORY_TITLEITEM_STATUS) return GetDatabase()->GetTCHistoryStatusColumnColor();
	return GetSysColor(COLOR_WINDOWTEXT);
}

COLORREF CTCHistoryView::LookupStatusColor(UINT nResult, UINT nStatus) CONST
{
	return((nStatus == TCHISTORYITEM_STATUS_RELEASED || nStatus == TCHISTORYITEM_STATUS_NOTRELEASED || nStatus == TCHISTORYITEM_STATUS_FAILEDRELEASE || nStatus == TCHISTORYITEM_STATUS_SENT || nStatus == TCHISTORYITEM_STATUS_FAILEDSEND || nStatus == TCHISTORYITEM_STATUS_UPLINKED || nStatus == TCHISTORYITEM_STATUS_FAILEDUPLINK) ? ((nStatus == TCHISTORYITEM_STATUS_RELEASED || nStatus == TCHISTORYITEM_STATUS_SENT || nStatus == TCHISTORYITEM_STATUS_UPLINKED) ? ((nResult & TCHISTORYITEM_RESULT_CEV_PASSED) ? m_nStatusColors.GetAt(TCHISTORYITEM_STATUSCOLOR_PASSED) : ((nResult & TCHISTORYITEM_RESULT_CEV_PENDING) ? m_nStatusColors.GetAt(TCHISTORYITEM_STATUSCOLOR_PENDING) : ((nResult & TCHISTORYITEM_RESULT_CEV_IDLE) ? m_nStatusColors.GetAt(TCHISTORYITEM_STATUSCOLOR_IDLE) : (((nResult & TCHISTORYITEM_RESULT_CEV_FAILED) || (nResult & TCHISTORYITEM_RESULT_CEV_UNKNOWN) || (nResult & TCHISTORYITEM_RESULT_CEV_UNVERIFIED)) ? m_nStatusColors.GetAt(TCHISTORYITEM_STATUSCOLOR_NOTPASSED) : m_nStatusColors.GetAt(TCHISTORYITEM_STATUSCOLOR_NONE))))) : m_nStatusColors.GetAt(TCHISTORYITEM_STATUSCOLOR_NOTPASSED)) : m_nStatusColors.GetAt(TCHISTORYITEM_STATUSCOLOR_NONE));
}

INT CTCHistoryView::FindColumnIndex(LPCTSTR pszColumn) CONST
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

INT CTCHistoryView::CalcColumnWidth(LPCTSTR pszColumn)
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
				nWidth = (nColumn == TCHISTORY_TITLEITEM_NUMBER) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryNumberColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_NAME) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryNameColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_COMPUTER) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryComputerColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_COMMANDSOURCE) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryCommandSourceColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_DESCRIPTION) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryDescriptionColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_CATEGORY) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryCategoryColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_SUBSYSTEM) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistorySubSystemColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_ARGUMENTS) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryArgumentsColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_FLAGS) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryFlagsColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_TCPACKET) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryTCPacketColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_DISPATCHTIME) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryDispatchTimeColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_RELEASETIME) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryReleaseTimeColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_RELEASETIMEOFFSET) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryReleaseTimeOffsetColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_TRANSMISSIONTIME) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryTransmissionTimeColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_EXECUTIONTIME) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryExecutionTimeColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_EXECUTIONTIMEOFFSET) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryExecutionTimeOffsetColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_AUTHORIZATION) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryAuthorizationColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_PTVTIMEWINDOW) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryPTVTimeWindowColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_PTVCHECKS) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryPTVChecksColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_PTVRESULT) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryPTVResultColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_PEVCHECKS) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryPEVChecksColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_PEVRESULT) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryPEVResultColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_CEVTIMEWINDOW) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryCEVTimeWindowColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_CEVCHECKS) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryCEVChecksColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_CEVRESULT) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryCEVResultColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCHISTORY_TITLEITEM_STATUS) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCHistoryStatusColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
			}
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
		return nWidth;
	}
	return 0;
}

INT CTCHistoryView::CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths)
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

CRect CTCHistoryView::CalcTelecommandSymbolPosition(INT nRow, INT nColumn, LPCTSTR pszText) CONST
{
	INT  nPos;
	CRect  rText;
	CRect  rSymbol;
	CFont  *pOldFont;
	CString  szText;
	CClientDC  cDC(NULL);

	for (szText = ((nPos = (szText = pszText).Find(GetSymbolDelimiter())) >= 0) ? szText.Left(nPos) : szText, rText = m_wndContentCtrl.CalcTextRect(nRow, nColumn), rSymbol.SetRectEmpty(); (pOldFont = (nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_NUMBER)) && !rText.IsRectEmpty()) ? cDC.SelectObject((CFont *)&m_wndContentCtrl.m_cFont) : (CFont *)NULL); )
	{
		rSymbol.SetRect(rText.left + cDC.GetTextExtent(szText + SPACE).cx, rText.top, rText.left + cDC.GetTextExtent(szText + SPACE).cx + m_sizeAlertSymbols.cx, rText.top + m_sizeAlertSymbols.cy);
		rSymbol.SetRect(min(max(rText.left, rSymbol.left), rText.right), rSymbol.top, max(min(rText.right, rSymbol.right), rText.left), rSymbol.bottom);
		rSymbol.InflateRect(0, 0, 1, 1);
		cDC.SelectObject(pOldFont);
		break;
	}
	return rSymbol;
}
CRect CTCHistoryView::CalcTelecommandSymbolPosition(INT nRow, INT nColumn, INT nCount, INT nIndex) CONST
{
	CRect  rText;
	CRect  rSymbol;
	CSize  sizeSymbol;

	for (rText = m_wndContentCtrl.CalcTextRect(nRow, nColumn), sizeSymbol = (nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_FLAGS))) ? m_sizeFlagSymbols : CSize(0, 0), sizeSymbol = (nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_PTVCHECKS)) || nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_PEVCHECKS)) || nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_CEVCHECKS))) ? m_sizeCheckFlagSymbols : sizeSymbol, sizeSymbol = (nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_PTVRESULT)) || nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_PEVRESULT)) || nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_CEVRESULT))) ? m_sizeResultSymbols : sizeSymbol, rSymbol.SetRectEmpty(); sizeSymbol.cx > 0 && sizeSymbol.cy > 0 && !rText.IsRectEmpty(); )
	{
		rSymbol.SetRect(rText.left + (rText.Width() - (nCount*((m_wndContentCtrl.m_wTextIndent[0] + m_wndContentCtrl.m_wTextIndent[1]) / 4 + sizeSymbol.cx))) / 2 + nIndex*((m_wndContentCtrl.m_wTextIndent[0] + m_wndContentCtrl.m_wTextIndent[1]) / 4 + sizeSymbol.cx), rText.top, rText.left + (rText.Width() - (nCount*((m_wndContentCtrl.m_wTextIndent[0] + m_wndContentCtrl.m_wTextIndent[1]) / 4 + sizeSymbol.cx))) / 2 + nIndex*((m_wndContentCtrl.m_wTextIndent[0] + m_wndContentCtrl.m_wTextIndent[1]) / 4 + sizeSymbol.cx) + sizeSymbol.cx, rText.top + sizeSymbol.cy);
		rSymbol.SetRect(min(max(rText.left, rSymbol.left), rText.right), rSymbol.top, max(min(rText.right, rSymbol.right), rText.left), rSymbol.bottom);
		rSymbol.InflateRect(0, 0, 1, 1);
		break;
	}
	return rSymbol;
}

TCHAR CTCHistoryView::GetSymbolDelimiter()
{
	return SPACE[0];
}

CString CTCHistoryView::ConstructToolTipTitle(CONST POINT &ptTip, LPCTSTR pszTip, UINT nTip) CONST
{
	INT  nRow;
	INT  nColumn;
	CString  szTitle;

	switch (nTip)
	{
	case TCHISTORY_TITLEITEM_NUMBER:
	{ if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_ALERT_INFORMATION)))
	{
		szTitle = STRING(IDS_TCHISTORY_TOOLTIP_ALERTINFORMATION);
		break;
	}
	if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_ALERT_WARNING)))
	{
		szTitle = STRING(IDS_TCHISTORY_TOOLTIP_ALERTWARNING);
		break;
	}
	if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_ALERT_ERROR)))
	{
		szTitle = STRING(IDS_TCHISTORY_TOOLTIP_ALERTERROR);
		break;
	}
	break;
	}
	case TCHISTORY_TITLEITEM_FLAGS:
	{ if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCK)))
	{
		if (FindTextFromPoint(ptTip, nRow, nColumn) && CalcTelecommandSymbolPosition(nRow, nColumn, 4, 0).PtInRect(ptTip))
		{
			szTitle = STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKTITLE);
			break;
		}
	}
	if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKIDLE)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKPENDING)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKSUCCESS)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKFAILURE)))
	{
		if (FindTextFromPoint(ptTip, nRow, nColumn) && CalcTelecommandSymbolPosition(nRow, nColumn, 4, 1).PtInRect(ptTip))
		{
			szTitle = STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKEDTITLE);
			break;
		}
	}
	if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_FLAGS_GROUPED)))
	{
		if (FindTextFromPoint(ptTip, nRow, nColumn) && CalcTelecommandSymbolPosition(nRow, nColumn, 4, 2).PtInRect(ptTip))
		{
			szTitle = STRING(IDS_TCHISTORY_TOOLTIP_GROUPEDTITLE);
			break;
		}
	}
	if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_FLAGS_BLOCKED)))
	{
		if (FindTextFromPoint(ptTip, nRow, nColumn) && CalcTelecommandSymbolPosition(nRow, nColumn, 4, 3).PtInRect(ptTip))
		{
			szTitle = STRING(IDS_TCHISTORY_TOOLTIP_BLOCKEDTITLE);
			break;
		}
	}
	break;
	}
	case TCHISTORY_TITLEITEM_PTVCHECKS:
	{ if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PTVCHECKS_ON)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PTVCHECKS_OFF)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PTVCHECKS_DISABLED)))
	{
		szTitle = STRING(IDS_TCHISTORY_TOOLTIP_PTVCHECKSTITLE);
		break;
	}
	break;
	}
	case TCHISTORY_TITLEITEM_PEVCHECKS:
	{ if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PEVCHECKS_NONE)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PEVCHECKS_ON)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PEVCHECKS_OFF)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PEVCHECKS_DISABLED)))
	{
		szTitle = STRING(IDS_TCHISTORY_TOOLTIP_PEVCHECKSTITLE);
		break;
	}
	break;
	}
	case TCHISTORY_TITLEITEM_CEVCHECKS:
	{ if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_CEVCHECKS_NONE)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_CEVCHECKS_ON)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_CEVCHECKS_OFF)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_CEVCHECKS_DISABLED)))
	{
		szTitle = STRING(IDS_TCHISTORY_TOOLTIP_CEVCHECKSTITLE);
		break;
	}
	break;
	}
	case TCHISTORY_TITLEITEM_PTVRESULT:
	{ if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PTVRESULT_GO)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PTVRESULT_WAIT)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PTVRESULT_FAIL)))
	{
		szTitle = STRING(IDS_TCHISTORY_TOOLTIP_PTVRESULTTITLE);
		break;
	}
	break;
	}
	case TCHISTORY_TITLEITEM_PEVRESULT:
	{ if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PEVRESULT_GO)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PEVRESULT_NOGO)))
	{
		szTitle = STRING(IDS_TCHISTORY_TOOLTIP_PEVRESULTTITLE);
		break;
	}
	break;
	}
	case TCHISTORY_TITLEITEM_CEVRESULT:
	{ if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_CEVRESULT_IDLE)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_CEVRESULT_PENDING)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_CEVRESULT_PASSED)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_CEVRESULT_FAILED)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_CEVRESULT_UNKNOWN)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_CEVRESULT_UNVERIFIED)))
	{
		szTitle = STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTTITLE);
		break;
	}
	break;
	}
	}
	return szTitle;
}

CString CTCHistoryView::ConstructToolTipText(CONST CTCHistoryItem *pItem, CONST POINT &ptTip, LPCTSTR pszTip, UINT nTip) CONST
{
	INT  nPos;
	INT  nRow;
	INT  nColumn;
	INT  nIndex;
	INT  nCount;
	INT  nParameter;
	INT  nParameters;
	UINT  nStageID;
	UINT  nStage;
	UINT  nScope;
	UINT  nState;
	UINT  nReason;
	BOOL  bSuccess;
	CString  szText;
	CString  szAlert;
	CString  szStages;
	CString  szCheckState[2];
	CString  szCheckResult[6];
	CString  szCheckReason[2];
	CString  szInterlockName;
	CString  szInterlockStage;
	CString  szInterlockState;
	CString  szInterlockScope[2];
	CTimeSpan  tTimeWindow;
	CStringArray  szStageIDs;
	CStringArray  szParameters;
	CStringTools  cStringTools;
	CTCInterlock  cInterlock[2];
	CDatabaseTCPreExeGroup  *pTCPreExeGroup;
	CDatabaseTCExeVerGroup  *pTCExeVerGroup;
	CDatabaseTCPreExeGroupParameter  *pTCPreExeGroupParameter;
	CDatabaseTCExeVerGroupParameter  *pTCExeVerGroupParameter;

	switch (nTip)
	{
	case TCHISTORY_TITLEITEM_NUMBER:
	{ if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_ALERT_INFORMATION)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_ALERT_WARNING)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_ALERT_ERROR)))
	{
		for (pItem->IsAlerted(-1, szText); (nCount = pItem->GetAlertCount(TCHISTORYITEM_ALERTTYPE_ERROR)) > 1; )
		{
			szAlert.Format(STRING(IDS_TCHISTORY_TOOLTIP_ALERTCOUNT), nCount);
			szText += CString(EOL) + szAlert;
			break;
		}
	}
	break;
	}
	case TCHISTORY_TITLEITEM_FLAGS:
	{ if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCK)))
	{
		if (FindTextFromPoint(ptTip, nRow, nColumn) && CalcTelecommandSymbolPosition(nRow, nColumn, 4, 0).PtInRect(ptTip))
		{
			if (pItem->GetInterlock(&cInterlock[0]) && !pItem->GetInterlock().Compare(cInterlock[0].GetName()))
			{
				szInterlockScope[0] = (TCINTERLOCKSCOPEFROMCODE((nScope = cInterlock[0].GetScope())) == TCINTERLOCK_SCOPE_GLOBAL) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSCOPEGLOBAL) : EMPTYSTRING;
				szInterlockScope[0] = (TCINTERLOCKSCOPEFROMCODE(nScope) == TCINTERLOCK_SCOPE_LOCAL) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSCOPELOCAL) : szInterlockScope[0];
				szInterlockScope[0] = (TCINTERLOCKSCOPEFROMCODE(nScope) == TCINTERLOCK_SCOPE_LOCALNOWAIT) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSCOPELOCALNOWAIT) : szInterlockScope[0];
				szInterlockScope[0] = (TCINTERLOCKSCOPEFROMCODE(nScope) == TCINTERLOCK_SCOPE_LOCALSUBSYSTEM) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSCOPESUBSYSTEM) : szInterlockScope[0];
				szInterlockScope[0] = (TCINTERLOCKSCOPEFROMCODE(nScope) == TCINTERLOCK_SCOPE_LOCALSUBSYSTEMNOWAIT) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSCOPESUBSYSTEMNOWAIT) : szInterlockScope[0];
				szInterlockScope[0] = (TCINTERLOCKSCOPEFROMCODE(nScope) == TCINTERLOCK_SCOPE_COMMANDS) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSCOPECOMMANDS) : szInterlockScope[0];
				szInterlockScope[1].Format(szInterlockScope[0], (LPCTSTR)GetTCService()->TranslateIDToTCSubSystem(TCINTERLOCKAPIDFROMCODE(nScope)));
				szInterlockStage = ((nStage = cInterlock[0].GetStage()) == TCINTERLOCK_STAGE_RECEPTION) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSTAGERECEPTION) : EMPTYSTRING;
				szInterlockStage = (nStage == TCINTERLOCK_STAGE_TRANSMISSION) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSTAGETRANSMISSION) : szInterlockStage;
				szInterlockStage = (nStage == TCINTERLOCK_STAGE_ACCEPTANCE) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSTAGEACCEPTANCE) : szInterlockStage;
				szInterlockStage = (nStage == TCINTERLOCK_STAGE_START) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSTAGESTART) : szInterlockStage;
				szInterlockStage = (nStage == TCINTERLOCK_STAGE_PROGRESS) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSTAGEPROGRESS) : szInterlockStage;
				szInterlockStage = (nStage == TCINTERLOCK_STAGE_COMPLETION) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSTAGECOMPLETION) : szInterlockStage;
				szText.Format(STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKTEXT), (LPCTSTR)pItem->GetInterlock(), (LPCTSTR)szInterlockScope[1], (LPCTSTR)szInterlockStage);
			}
			break;
		}
	}
	if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKIDLE)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKPENDING)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKSUCCESS)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKFAILURE)))
	{
		if (FindTextFromPoint(ptTip, nRow, nColumn) && CalcTelecommandSymbolPosition(nRow, nColumn, 4, 1).PtInRect(ptTip))
		{
			if (pItem->GetReleaseInterlock(&cInterlock[1]) && pItem->GetReleaseInterlock(szInterlockName, bSuccess) && szInterlockName == cInterlock[1].GetName())
			{
				szInterlockState = ((nState = cInterlock[1].GetState()) == TCINTERLOCK_STATE_IDLE) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSTATEIDLE) : EMPTYSTRING;
				szInterlockState = (nState == TCINTERLOCK_STATE_PENDING) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSTATEPENDING) : szInterlockState;
				szInterlockState = (nState == TCINTERLOCK_STATE_SUCCESS) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSTATESUCCESS) : szInterlockState;
				szInterlockState = (nState == TCINTERLOCK_STATE_FAILURE) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSTATEFAILURE) : szInterlockState;
				szInterlockScope[0] = (TCINTERLOCKSCOPEFROMCODE((nScope = cInterlock[1].GetScope())) == TCINTERLOCK_SCOPE_GLOBAL) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSCOPEGLOBAL) : EMPTYSTRING;
				szInterlockScope[0] = (TCINTERLOCKSCOPEFROMCODE(nScope) == TCINTERLOCK_SCOPE_LOCAL) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSCOPELOCAL) : szInterlockScope[0];
				szInterlockScope[0] = (TCINTERLOCKSCOPEFROMCODE(nScope) == TCINTERLOCK_SCOPE_LOCALNOWAIT) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSCOPELOCALNOWAIT) : szInterlockScope[0];
				szInterlockScope[0] = (TCINTERLOCKSCOPEFROMCODE(nScope) == TCINTERLOCK_SCOPE_LOCALSUBSYSTEM) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSCOPESUBSYSTEM) : szInterlockScope[0];
				szInterlockScope[0] = (TCINTERLOCKSCOPEFROMCODE(nScope) == TCINTERLOCK_SCOPE_LOCALSUBSYSTEMNOWAIT) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSCOPESUBSYSTEMNOWAIT) : szInterlockScope[0];
				szInterlockScope[0] = (TCINTERLOCKSCOPEFROMCODE(nScope) == TCINTERLOCK_SCOPE_COMMANDS) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSCOPECOMMANDS) : szInterlockScope[0];
				szInterlockScope[1].Format(szInterlockScope[0], (LPCTSTR)GetTCService()->TranslateIDToTCSubSystem(TCINTERLOCKAPIDFROMCODE(nScope)));
				szInterlockStage = ((nStage = cInterlock[1].GetStage()) == TCINTERLOCK_STAGE_RECEPTION) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSTAGERECEPTION) : EMPTYSTRING;
				szInterlockStage = (nStage == TCINTERLOCK_STAGE_TRANSMISSION) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSTAGETRANSMISSION) : szInterlockStage;
				szInterlockStage = (nStage == TCINTERLOCK_STAGE_ACCEPTANCE) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSTAGEACCEPTANCE) : szInterlockStage;
				szInterlockStage = (nStage == TCINTERLOCK_STAGE_START) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSTAGESTART) : szInterlockStage;
				szInterlockStage = (nStage == TCINTERLOCK_STAGE_PROGRESS) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSTAGEPROGRESS) : szInterlockStage;
				szInterlockStage = (nStage == TCINTERLOCK_STAGE_COMPLETION) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKSTAGECOMPLETION) : szInterlockStage;
				szText.Format(STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKEDTEXT), (LPCTSTR)szInterlockName, (bSuccess) ? STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKWAITSTATESUCCESS) : STRING(IDS_TCHISTORY_TOOLTIP_INTERLOCKWAITSTATEFAILURE), (LPCTSTR)szInterlockState, (LPCTSTR)szInterlockScope[1], (LPCTSTR)szInterlockStage);
			}
			break;
		}
	}
	if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_FLAGS_GROUPED)))
	{
		if (FindTextFromPoint(ptTip, nRow, nColumn) && CalcTelecommandSymbolPosition(nRow, nColumn, 4, 2).PtInRect(ptTip))
		{
			szText = STRING(IDS_TCHISTORY_TOOLTIP_GROUPEDTEXT);
			break;
		}
	}
	if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_FLAGS_BLOCKED)))
	{
		if (FindTextFromPoint(ptTip, nRow, nColumn) && CalcTelecommandSymbolPosition(nRow, nColumn, 4, 3).PtInRect(ptTip))
		{
			szText = STRING(IDS_TCHISTORY_TOOLTIP_BLOCKEDTEXT);
			break;
		}
	}
	break;
	}
	case TCHISTORY_TITLEITEM_PTVCHECKS:
	{ if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PTVCHECKS_ON)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PTVCHECKS_OFF)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PTVCHECKS_DISABLED)))
	{
		szCheckState[0] = (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PTVCHECKS_OFF))) ? STRING(IDS_TCHISTORY_TOOLTIP_PTVCHECKSSTATEOFF) : STRING(IDS_TCHISTORY_TOOLTIP_PTVCHECKSSTATEON);
		szCheckState[0] = (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PTVCHECKS_DISABLED))) ? STRING(IDS_TCHISTORY_TOOLTIP_PTVCHECKSSTATEDISABLED) : szCheckState[0];
		szCheckState[1].Format(STRING(IDS_TCHISTORY_TOOLTIP_PTVCHECKSTEXT), (LPCTSTR)szCheckState[0]);
		szText = szCheckState[1];
	}
	break;
	}
	case TCHISTORY_TITLEITEM_PEVCHECKS:
	{ if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PEVCHECKS_NONE)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PEVCHECKS_ON)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PEVCHECKS_OFF)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PEVCHECKS_DISABLED)))
	{
		szCheckState[0] = (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PEVCHECKS_NONE))) ? STRING(IDS_TCHISTORY_TOOLTIP_PEVCHECKSSTATENONE) : STRING(IDS_TCHISTORY_TOOLTIP_PEVCHECKSSTATEON);
		szCheckState[0] = (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PEVCHECKS_OFF))) ? STRING(IDS_TCHISTORY_TOOLTIP_PEVCHECKSSTATEOFF) : szCheckState[0];
		szCheckState[0] = (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PEVCHECKS_DISABLED))) ? STRING(IDS_TCHISTORY_TOOLTIP_PEVCHECKSSTATEDISABLED) : szCheckState[0];
		if ((pTCPreExeGroup = GetDatabase()->GetTCPreExeGroups()->GetAt(pItem->GetPreExeGroupRef())))
		{
			szText.Format(szCheckState[0], (LPCTSTR)pTCPreExeGroup->GetID());
			break;
		}
		for (nPos = (szCheckState[0] == STRING(IDS_TCHISTORY_TOOLTIP_PEVCHECKSSTATEON)) ? (szCheckState[0].GetLength() - 1) : -1; nPos >= 0; nPos--)
		{
			if (_istspace(szCheckState[0].GetAt(nPos)))
			{
				szCheckState[0] = szCheckState[0].Left(nPos);
				break;
			}
		}
		szText = szCheckState[0];
	}
	break;
	}
	case TCHISTORY_TITLEITEM_CEVCHECKS:
	{ if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_CEVCHECKS_NONE)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_CEVCHECKS_ON)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_CEVCHECKS_OFF)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_CEVCHECKS_DISABLED)))
	{
		szCheckState[0] = (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_CEVCHECKS_NONE))) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVCHECKSSTATENONE) : STRING(IDS_TCHISTORY_TOOLTIP_CEVCHECKSSTATEON);
		szCheckState[0] = (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_CEVCHECKS_OFF))) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVCHECKSSTATEOFF) : szCheckState[0];
		szCheckState[0] = (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_CEVCHECKS_DISABLED))) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVCHECKSSTATEDISABLED) : szCheckState[0];
		if ((pTCExeVerGroup = GetDatabase()->GetTCExeVerGroups()->GetAt(pItem->GetExeVerGroupRef())))
		{
			szText.Format(szCheckState[0], (LPCTSTR)pTCExeVerGroup->GetName());
			break;
		}
		for (nPos = (szCheckState[0] == STRING(IDS_TCHISTORY_TOOLTIP_CEVCHECKSSTATEON)) ? (szCheckState[0].GetLength() - 1) : -1; nPos >= 0; nPos--)
		{
			if (_istspace(szCheckState[0].GetAt(nPos)))
			{
				szCheckState[0] = szCheckState[0].Left(nPos);
				break;
			}
		}
		szText = szCheckState[0];
	}
	break;
	}
	case TCHISTORY_TITLEITEM_PTVRESULT:
	{ if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PTVRESULT_GO)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PTVRESULT_WAIT)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PTVRESULT_FAIL)))
	{
		szCheckResult[0] = (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PTVRESULT_GO))) ? STRING(IDS_TCHISTORY_TOOLTIP_PTVRESULTSTATEGO) : STRING(IDS_TCHISTORY_TOOLTIP_PTVRESULTSTATEFAIL);
		szCheckResult[0] = (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PTVRESULT_WAIT))) ? STRING(IDS_TCHISTORY_TOOLTIP_PTVRESULTSTATEWAIT) : szCheckResult[0];
		szCheckReason[0] = (pItem->GetResult() & TCHISTORYITEM_FAILURE_PTV_UPLINK) ? STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONUPLINK) : EMPTYSTRING;
		szCheckReason[0] = (pItem->GetResult() & TCHISTORYITEM_FAILURE_PTV_RELEASETIMEWINDOW) ? ((!szCheckReason[0].IsEmpty()) ? (szCheckReason[0] + STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONSEPARATOR) + STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONRELEASETIMEWINDOW)) : STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONRELEASETIMEWINDOW)) : szCheckReason[0];
		szCheckReason[0] = (pItem->GetResult() & TCHISTORYITEM_FAILURE_PTV_EXECUTIONTIME) ? ((!szCheckReason[0].IsEmpty()) ? (szCheckReason[0] + STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONSEPARATOR) + STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONEXECUTIONTIME)) : STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONEXECUTIONTIME)) : szCheckReason[0];
		szCheckReason[0] = (pItem->GetResult() & TCHISTORYITEM_FAILURE_PTV_INTERLOCK) ? ((!szCheckReason[0].IsEmpty()) ? (szCheckReason[0] + STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONSEPARATOR) + STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONINTERLOCK)) : STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONINTERLOCK)) : szCheckReason[0];
		szCheckReason[0] = (pItem->GetResult() & TCHISTORYITEM_FAILURE_PTV_SUBSYSTEM) ? ((!szCheckReason[0].IsEmpty()) ? (szCheckReason[0] + STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONSEPARATOR) + STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONSUBSYSTEM)) : STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONSUBSYSTEM)) : szCheckReason[0];
		szCheckReason[0] = (pItem->GetResult() & TCHISTORYITEM_FAILURE_PTV_ONBOARDBUFFER) ? ((!szCheckReason[0].IsEmpty()) ? (szCheckReason[0] + STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONSEPARATOR) + STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONONBOARDBUFFER)) : STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONONBOARDBUFFER)) : szCheckReason[0];
		szCheckReason[0] = (pItem->GetResult() & TCHISTORYITEM_FAILURE_PTV_ENCODING) ? ((!szCheckReason[0].IsEmpty()) ? (szCheckReason[0] + STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONSEPARATOR) + STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONENCODING)) : STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONENCODING)) : szCheckReason[0];
		szCheckReason[0] = (pItem->GetAuthorizationStatus() == TCHISTORYITEM_AUTHORIZATIONSTATUS_DENIED) ? ((!szCheckReason[0].IsEmpty()) ? (szCheckReason[0] + STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONSEPARATOR) + STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONAUTHORIZATION)) : STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONAUTHORIZATION)) : szCheckReason[0];
		szCheckResult[1].Format(STRING(IDS_TCHISTORY_TOOLTIP_PTVRESULTTEXT), (LPCTSTR)szCheckResult[0]);
		szCheckReason[1].Format(STRING(IDS_TCHISTORY_TOOLTIP_PTVREASONTEXT), (LPCTSTR)szCheckReason[0]);
		szText = (!szCheckReason[0].IsEmpty()) ? (szCheckResult[1] + EOL + szCheckReason[1]) : szCheckResult[1];
	}
	break;
	}
	case TCHISTORY_TITLEITEM_PEVRESULT:
	{ if (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PEVRESULT_GO)) || _tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PEVRESULT_NOGO)))
	{
		for (szCheckResult[0] = (_tcsstr(pszTip, STRING(IDS_TCHISTORY_LIST_PEVRESULT_NOGO))) ? STRING(IDS_TCHISTORY_TOOLTIP_PEVRESULTSTATENOGO) : STRING(IDS_TCHISTORY_TOOLTIP_PEVRESULTSTATEGO), szCheckResult[1].Format(STRING(IDS_TCHISTORY_TOOLTIP_PEVRESULTTEXT), (LPCTSTR)szCheckResult[0]), szCheckReason[0].Empty(); (pTCPreExeGroup = ((pItem->GetResult() & TCHISTORYITEM_FAILURE_PEV_PARAMETERS) && pItem->GetVerificationStageParameters(TCVERIFICATIONSTAGE_NONE, szParameters) > 0) ? GetDatabase()->GetTCPreExeGroups()->GetAt(pItem->GetPreExeGroupRef()) : (CDatabaseTCPreExeGroup *)NULL); )
		{
			for (nParameter = 0, nParameters = (INT)szParameters.GetSize(); nParameter < nParameters; nParameter++)
			{
				if ((pTCPreExeGroupParameter = pTCPreExeGroup->GetAt(pTCPreExeGroup->Find(szParameters.GetAt(nParameter)))))
				{
					szCheckReason[1].Format(STRING(IDS_TCHISTORY_TOOLTIP_PEVREASONPARAMETERFORMAT), (LPCTSTR)pTCPreExeGroupParameter->GetTag());
					szCheckReason[0] += (!szCheckReason[0].IsEmpty()) ? (STRING(IDS_TCHISTORY_TOOLTIP_PEVREASONPARAMETERSEPARATOR) + szCheckReason[1]) : szCheckReason[1];
					if (szCheckReason[0].GetLength() > lstrlen(STRING(IDS_TCHISTORY_TOOLTIP_PEVREASONPARAMETERS)))
					{
						szCheckReason[0] += STRING(IDS_TCHISTORY_TOOLTIP_PEVREASONPARAMETERELLIPSIS);
						break;
					}
					continue;
				}
				szParameters.RemoveAt(nParameter);
				nParameters--;
				nParameter--;
			}
			szCheckReason[1].Format((szParameters.GetSize() > 0) ? ((szParameters.GetSize() > 1) ? STRING(IDS_TCHISTORY_TOOLTIP_PEVREASONPARAMETERS) : STRING(IDS_TCHISTORY_TOOLTIP_PEVREASONPARAMETER)) : STRING(IDS_TCHISTORY_TOOLTIP_PEVREASONEXPRESSION), (LPCTSTR)szCheckReason[0], (LPCTSTR)pTCPreExeGroup->GetID());
			break;
		}
		szCheckReason[1] = (pItem->GetResult() & TCHISTORYITEM_FAILURE_PEV_2NDSTEP) ? ((!szCheckReason[1].IsEmpty()) ? (szCheckReason[1] + EOL + STRING(IDS_TCHISTORY_TOOLTIP_PEVREASONEXTRA2NDSTEP)) : STRING(IDS_TCHISTORY_TOOLTIP_PEVREASON2NDSTEP)) : szCheckReason[1];
		szCheckReason[1] = (pItem->GetResult() & TCHISTORYITEM_FAILURE_PEV_TELEMETRY) ? ((!szCheckReason[1].IsEmpty()) ? (szCheckReason[1] + EOL + STRING(IDS_TCHISTORY_TOOLTIP_PEVREASONEXTRATELEMETRY)) : STRING(IDS_TCHISTORY_TOOLTIP_PEVREASONTELEMETRY)) : szCheckReason[1];
		szCheckReason[1] = (pItem->GetResult() & TCHISTORYITEM_FAILURE_PEV_CORRELATION) ? ((!szCheckReason[1].IsEmpty()) ? (szCheckReason[1] + EOL + STRING(IDS_TCHISTORY_TOOLTIP_PEVREASONEXTRACORRELATION)) : STRING(IDS_TCHISTORY_TOOLTIP_PEVREASONCORRELATION)) : szCheckReason[1];
		szText = (!szCheckReason[1].IsEmpty()) ? (szCheckResult[1] + EOL + szCheckReason[1]) : szCheckResult[1];
	}
	break;
	}
	case TCHISTORY_TITLEITEM_CEVRESULT:
	{ if (!lstrcmp(pszTip, STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEIDLE)) || !lstrcmp(pszTip, STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEPENDING)) || !lstrcmp(pszTip, STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEPASSED)) || !lstrcmp(pszTip, STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEFAILED)) || !lstrcmp(pszTip, STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEUNKNOWN)) || !lstrcmp(pszTip, STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEUNVERIFIED)))
	{
		szCheckResult[0] = (!lstrcmp(pszTip, STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEIDLE))) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEIDLE) : EMPTYSTRING;
		szCheckResult[0] = (!lstrcmp(pszTip, STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEPENDING))) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEPENDING) : szCheckResult[0];
		szCheckResult[0] = (!lstrcmp(pszTip, STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEPASSED))) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEPASSED) : szCheckResult[0];
		szCheckResult[0] = (!lstrcmp(pszTip, STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEFAILED))) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEFAILED) : szCheckResult[0];
		szCheckResult[0] = (!lstrcmp(pszTip, STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEUNKNOWN))) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEUNKNOWN) : szCheckResult[0];
		szCheckResult[0] = (!lstrcmp(pszTip, STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEUNVERIFIED))) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEUNVERIFIED) : szCheckResult[0];
		szCheckResult[1].Format(STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTVERIFICATIONTIME), (LPCTSTR)pItem->GetVerificationTime().FormatGmt(STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTTIMEFORMAT)), (LPCTSTR)cStringTools.ConvertLongIntToStructuredString(pItem->CalcVerificationTimeWindowSize(0, (GetTCService()->GetCommandHandlerVerificationUncertaintyTimeWindow(tTimeWindow)) ? tTimeWindow : 0).GetTotalSeconds()));
		for (szCheckResult[2].Format(STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTOVERALLSTATE), (LPCTSTR)szCheckResult[0]); !lstrcmp(pszTip, STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEIDLE)); )
		{
			szCheckResult[2] += CString(EOL) + szCheckResult[1];
			break;
		}
		szText = szCheckResult[2];
		break;
	}
	for (szStages = (FindTextFromPoint(ptTip, nRow, nColumn)) ? pszTip : EMPTYSTRING, szStageIDs.RemoveAll(); !szStages.IsEmpty(); szStages = (nPos >= 0) ? (szStages.Mid(nPos + lstrlen(STRING(IDS_TCHISTORY_LIST_CEVRESULT_SEPARATOR)))) : EMPTYSTRING)
	{
		if ((nPos = szStages.Find(STRING(IDS_TCHISTORY_LIST_CEVRESULT_SEPARATOR))) >= 0)
		{
			szStageIDs.Add(szStages.Left(nPos));
			continue;
		}
		szStageIDs.Add(szStages);
	}
	for (nIndex = 0, nCount = (INT)szStageIDs.GetSize(); nIndex < nCount; nIndex++)
	{
		if (CalcTelecommandSymbolPosition(nRow, nColumn, nCount, nIndex).PtInRect(ptTip))
		{
			szCheckResult[0] = (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_IDLE) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEIDLE) : EMPTYSTRING;
			szCheckResult[0] = (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_PENDING) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEPENDING) : szCheckResult[0];
			szCheckResult[0] = (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_PASSED) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEPASSED) : szCheckResult[0];
			szCheckResult[0] = (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_FAILED) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEFAILED) : szCheckResult[0];
			szCheckResult[0] = (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_UNKNOWN) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEUNKNOWN) : szCheckResult[0];
			szCheckResult[0] = (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_UNVERIFIED) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEUNVERIFIED) : szCheckResult[0];
			szCheckResult[1] = ((nStageID = (UINT)_ttoi(szStageIDs.GetAt(nIndex))) == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE)) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTAGEACCEPTANCE) : EMPTYSTRING;
			szCheckResult[1] = (nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START)) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTAGESTART) : szCheckResult[1];
			szCheckResult[1] = (nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS)) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTAGEPROGRESS) : szCheckResult[1];
			szCheckResult[1] = (nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION)) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTAGECOMPLETION) : szCheckResult[1];
			szCheckResult[2] = (szStageIDs.GetAt(nIndex).Find(STRING(IDS_TCHISTORY_LIST_CEVRESULT_IDLE)) >= 0) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEIDLE) : EMPTYSTRING;
			szCheckResult[2] = (szStageIDs.GetAt(nIndex).Find(STRING(IDS_TCHISTORY_LIST_CEVRESULT_PENDING)) >= 0) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEPENDING) : szCheckResult[2];
			szCheckResult[2] = (szStageIDs.GetAt(nIndex).Find(STRING(IDS_TCHISTORY_LIST_CEVRESULT_PASSED)) >= 0) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEPASSED) : szCheckResult[2];
			szCheckResult[2] = (szStageIDs.GetAt(nIndex).Find(STRING(IDS_TCHISTORY_LIST_CEVRESULT_FAILED)) >= 0) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEFAILED) : szCheckResult[2];
			szCheckResult[2] = (szStageIDs.GetAt(nIndex).Find(STRING(IDS_TCHISTORY_LIST_CEVRESULT_UNKNOWN)) >= 0) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEUNKNOWN) : szCheckResult[2];
			szCheckResult[2] = (szStageIDs.GetAt(nIndex).Find(STRING(IDS_TCHISTORY_LIST_CEVRESULT_UNVERIFIED)) >= 0) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATEUNVERIFIED) : szCheckResult[2];
			for (szCheckResult[3].Format(STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTOVERALLSTATE), (LPCTSTR)szCheckResult[0]), szCheckResult[4].Format(STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTAGE), (LPCTSTR)szCheckResult[1]), szCheckResult[5].Format(STRING(IDS_TCHISTORY_TOOLTIP_CEVRESULTSTATE), (LPCTSTR)szCheckResult[2]), szCheckReason[0].Empty(); (pTCExeVerGroup = (pItem->GetVerificationStageState(nStageID, nState, nReason) && (nReason & TCHISTORYITEM_FAILURE_CEV_PARAMETERS) && pItem->GetVerificationStageParameters(nStageID, szParameters) > 0) ? GetDatabase()->GetTCExeVerGroups()->GetAt(pItem->GetExeVerGroupRef()) : (CDatabaseTCExeVerGroup *)NULL); )
			{
				for (nParameter = 0, nParameters = (INT)szParameters.GetSize(); nParameter < nParameters; nParameter++)
				{
					if ((pTCExeVerGroupParameter = pTCExeVerGroup->GetAt(pTCExeVerGroup->Find(szParameters.GetAt(nParameter), MAKETCEXEVERSTAGEFROMID(nStageID)))))
					{
						szCheckReason[1].Format(STRING(IDS_TCHISTORY_TOOLTIP_CEVREASONPARAMETERFORMAT), (LPCTSTR)pTCExeVerGroupParameter->GetTag());
						szCheckReason[0] += (!szCheckReason[0].IsEmpty()) ? (STRING(IDS_TCHISTORY_TOOLTIP_CEVREASONPARAMETERSEPARATOR) + szCheckReason[1]) : szCheckReason[1];
						if (szCheckReason[0].GetLength() > lstrlen(STRING(IDS_TCHISTORY_TOOLTIP_CEVREASONPARAMETERS)))
						{
							szCheckReason[0] += STRING(IDS_TCHISTORY_TOOLTIP_CEVREASONPARAMETERELLIPSIS);
							break;
						}
						continue;
					}
					szParameters.RemoveAt(nParameter);
					nParameters--;
					nParameter--;
				}
				szCheckReason[1].Format((szParameters.GetSize() > 0) ? ((szParameters.GetSize() > 1) ? STRING(IDS_TCHISTORY_TOOLTIP_CEVREASONPARAMETERS) : STRING(IDS_TCHISTORY_TOOLTIP_CEVREASONPARAMETER)) : STRING(IDS_TCHISTORY_TOOLTIP_CEVREASONEXPRESSION), (LPCTSTR)szCheckReason[0], (LPCTSTR)pTCExeVerGroup->GetID());
				break;
			}
			szText = (!szCheckReason[1].IsEmpty()) ? (szCheckResult[3] + EOL + szCheckResult[4] + EOL + szCheckResult[5] + EOL + szCheckReason[1]) : (szCheckResult[3] + EOL + szCheckResult[4] + EOL + szCheckResult[5]);
			break;
		}
	}
	break;
	}
	default: break;
	}
	return szText;
}

BOOL CTCHistoryView::SetClipboardFormat(UINT nFormat)
{
	return(((m_nClipboardFormat = nFormat) > 0) ? TRUE : FALSE);
}

UINT CTCHistoryView::GetClipboardFormat() CONST
{
	return m_nClipboardFormat;
}

BOOL CTCHistoryView::CopyToClipboard()
{
	INT  nItem[2];
	INT  nItems[2];
	LPBYTE  pData;
	HGLOBAL  hData;
	CTCItems  pItems;
	CByteArray  nItemsData;
	CTCHistoryItem  *pItem[2];

	for (nItem[0] = 0, nItems[0] = (INT)m_pItems[0].GetSize(); nItem[0] < nItems[0]; nItem[0]++)
	{
		if ((pItem[0] = m_pItems[0].GetAt(nItem[0])) && pItem[0]->IsSelected())
		{
			if ((pItem[1] = new CTCHistoryItem))
			{
				if (pItem[1]->Copy(pItem[0]))
				{
					for (nItem[1] = 0, nItems[1] = (INT)pItems.GetSize(); nItem[1] < nItems[1]; nItem[1]++)
					{
						if (pItems.GetAt(nItem[1])->GetReleaseTime() >= pItem[1]->GetReleaseTime()) break;
						continue;
					}
					pItems.InsertAt(nItem[1], pItem[1], 1);
					continue;
				}
				delete pItem[1];
			}
			break;
		}
	}
	if (OpenClipboard())
	{
		if (EmptyClipboard())
		{
			if (pItems.GetSize() > 0 && pItems.Map(nItemsData))
			{
				if ((hData = GlobalAlloc(GHND, nItemsData.GetSize())) != (HGLOBAL)NULL)
				{
					if ((pData = (LPBYTE)GlobalLock(hData)) != (LPBYTE)NULL)
					{
						CopyMemory(pData, nItemsData.GetData(), nItemsData.GetSize());
						SetClipboardData(GetClipboardFormat(), hData);
						GlobalUnlock(hData);
						CloseClipboard();
						return TRUE;
					}
					GlobalFree(hData);
				}
			}
		}
		CloseClipboard();
	}
	return FALSE;
}

BOOL CTCHistoryView::LoadTelecommandSymbols()
{
	INT  nSymbol[4];
	INT  nSymbols[4];
	ULONG  cbSymbol;
	HRSRC  hResource;
	LPVOID  pResource;
	HMODULE  hModule;
	HGLOBAL  hMemResource[2];
	LPSTREAM  pIStream;

	for (nSymbol[0] = 0, nSymbols[0] = TCHISTORYVIEW_COMMANDFLAGSYMBOLS; nSymbol[0] < nSymbols[0]; nSymbol[0]++)
	{
		if ((hResource = FindResource((hModule = GetModuleHandle((LPCTSTR)NULL)), (nSymbol[0] == TCHISTORYVIEW_COMMANDFLAGSYMBOL_INTERLOCK) ? MAKEINTRESOURCE(IDP_TCHISTORYINTERLOCK) : ((nSymbol[0] == TCHISTORYVIEW_COMMANDFLAGSYMBOL_INTERLOCKIDLE) ? MAKEINTRESOURCE(IDP_TCHISTORYINTERLOCKIDLE) : ((nSymbol[0] == TCHISTORYVIEW_COMMANDFLAGSYMBOL_INTERLOCKPENDING) ? MAKEINTRESOURCE(IDP_TCHISTORYINTERLOCKPENDING) : ((nSymbol[0] == TCHISTORYVIEW_COMMANDFLAGSYMBOL_INTERLOCKSUCCESS) ? MAKEINTRESOURCE(IDP_TCHISTORYINTERLOCKSUCCESS) : ((nSymbol[0] == TCHISTORYVIEW_COMMANDFLAGSYMBOL_INTERLOCKFAILURE) ? MAKEINTRESOURCE(IDP_TCHISTORYINTERLOCKFAILURE) : ((nSymbol[0] == TCHISTORYVIEW_COMMANDFLAGSYMBOL_GROUPED) ? MAKEINTRESOURCE(IDP_TCHISTORYGROUPED) : MAKEINTRESOURCE(IDP_TCHISTORYBLOCKED)))))), STRING(IDS_RESOURCETYPE_PICTURE))))
		{
			if ((hMemResource[0] = LoadResource(hModule, hResource)))
			{
				if ((pResource = LockResource(hMemResource[0])))
				{
					if ((hMemResource[1] = GlobalAlloc(GMEM_MOVEABLE, 0)))
					{
						if (SUCCEEDED(CreateStreamOnHGlobal(hMemResource[1], TRUE, &pIStream)))
						{
							if (SUCCEEDED(pIStream->Write(pResource, SizeofResource(hModule, hResource), &cbSymbol)))
							{
								if ((m_pFlagSymbols[nSymbol[0]] = new CImage) != (CImage *)NULL)
								{
									if (SUCCEEDED(m_pFlagSymbols[nSymbol[0]]->Load(pIStream)))
									{
										pIStream->Release();
										continue;
									}
									delete m_pFlagSymbols[nSymbol[0]];
									m_pFlagSymbols[nSymbol[0]] = (CImage *)NULL;
								}
							}
							pIStream->Release();
						}
					}
				}
			}
		}
		while (nSymbol[0] > 0)
		{
			delete m_pFlagSymbols[--nSymbol[0]];
			m_pFlagSymbols[nSymbol[0]] = (CImage *)NULL;
		}
		break;
	}
	for (nSymbol[1] = 0, nSymbols[1] = TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOLS; nSymbol[1] < nSymbols[1]; nSymbol[1]++)
	{
		if ((hResource = FindResource((hModule = GetModuleHandle((LPCTSTR)NULL)), (nSymbol[1] == TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOL_NONE) ? MAKEINTRESOURCE(IDP_TCHISTORYCHECKSNONE) : ((nSymbol[1] == TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOL_ON) ? MAKEINTRESOURCE(IDP_TCHISTORYCHECKSON) : ((nSymbol[1] == TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOL_OFF) ? MAKEINTRESOURCE(IDP_TCHISTORYCHECKSOFF) : MAKEINTRESOURCE(IDP_TCHISTORYCHECKSDISABLED))), STRING(IDS_RESOURCETYPE_PICTURE))))
		{
			if ((hMemResource[0] = LoadResource(hModule, hResource)))
			{
				if ((pResource = LockResource(hMemResource[0])))
				{
					if ((hMemResource[1] = GlobalAlloc(GMEM_MOVEABLE, 0)))
					{
						if (SUCCEEDED(CreateStreamOnHGlobal(hMemResource[1], TRUE, &pIStream)))
						{
							if (SUCCEEDED(pIStream->Write(pResource, SizeofResource(hModule, hResource), &cbSymbol)))
							{
								if ((m_pCheckFlagSymbols[nSymbol[1]] = new CImage) != (CImage *)NULL)
								{
									if (SUCCEEDED(m_pCheckFlagSymbols[nSymbol[1]]->Load(pIStream)))
									{
										pIStream->Release();
										continue;
									}
									delete m_pCheckFlagSymbols[nSymbol[1]];
									m_pCheckFlagSymbols[nSymbol[1]] = (CImage *)NULL;
								}
							}
							pIStream->Release();
						}
					}
				}
			}
		}
		while (nSymbol[1] > 0)
		{
			delete m_pCheckFlagSymbols[--nSymbol[1]];
			m_pCheckFlagSymbols[nSymbol[1]] = (CImage *)NULL;
		}
		break;
	}
	for (nSymbol[2] = 0, nSymbols[2] = TCHISTORYVIEW_COMMANDRESULTSYMBOLS; nSymbol[2] < nSymbols[2]; nSymbol[2]++)
	{
		if ((hResource = FindResource((hModule = GetModuleHandle((LPCTSTR)NULL)), (nSymbol[2] == TCHISTORYVIEW_COMMANDRESULTSYMBOL_PTV_GO) ? MAKEINTRESOURCE(IDP_TCHISTORYPTVGO) : ((nSymbol[2] == TCHISTORYVIEW_COMMANDRESULTSYMBOL_PTV_WAIT) ? MAKEINTRESOURCE(IDP_TCHISTORYPTVWAIT) : ((nSymbol[2] == TCHISTORYVIEW_COMMANDRESULTSYMBOL_PTV_FAIL) ? MAKEINTRESOURCE(IDP_TCHISTORYPTVFAIL) : ((nSymbol[2] == TCHISTORYVIEW_COMMANDRESULTSYMBOL_PEV_GO) ? MAKEINTRESOURCE(IDP_TCHISTORYPEVGO) : ((nSymbol[2] == TCHISTORYVIEW_COMMANDRESULTSYMBOL_PEV_NOGO) ? MAKEINTRESOURCE(IDP_TCHISTORYPEVNOGO) : ((nSymbol[2] == TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_IDLE) ? MAKEINTRESOURCE(IDP_TCHISTORYCEVIDLE) : ((nSymbol[2] == TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_PENDING) ? MAKEINTRESOURCE(IDP_TCHISTORYCEVPENDING) : ((nSymbol[2] == TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_PASSED) ? MAKEINTRESOURCE(IDP_TCHISTORYCEVPASSED) : ((nSymbol[2] == TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_FAILED) ? MAKEINTRESOURCE(IDP_TCHISTORYCEVFAILED) : ((nSymbol[2] == TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_UNKNOWN) ? MAKEINTRESOURCE(IDP_TCHISTORYCEVUNKNOWN) : MAKEINTRESOURCE(IDP_TCHISTORYCEVUNVERIFIED)))))))))), STRING(IDS_RESOURCETYPE_PICTURE))))
		{
			if ((hMemResource[0] = LoadResource(hModule, hResource)))
			{
				if ((pResource = LockResource(hMemResource[0])))
				{
					if ((hMemResource[1] = GlobalAlloc(GMEM_MOVEABLE, 0)))
					{
						if (SUCCEEDED(CreateStreamOnHGlobal(hMemResource[1], TRUE, &pIStream)))
						{
							if (SUCCEEDED(pIStream->Write(pResource, SizeofResource(hModule, hResource), &cbSymbol)))
							{
								if ((m_pResultSymbols[nSymbol[2]] = new CImage) != (CImage *)NULL)
								{
									if (SUCCEEDED(m_pResultSymbols[nSymbol[2]]->Load(pIStream)))
									{
										pIStream->Release();
										continue;
									}
									delete m_pResultSymbols[nSymbol[2]];
									m_pResultSymbols[nSymbol[2]] = (CImage *)NULL;
								}
							}
							pIStream->Release();
						}
					}
				}
			}
		}
		while (nSymbol[2] > 0)
		{
			delete m_pResultSymbols[--nSymbol[2]];
			m_pResultSymbols[nSymbol[2]] = (CImage *)NULL;
		}
		break;
	}
	for (nSymbol[3] = 0, nSymbols[3] = TCHISTORYVIEW_COMMANDALERTSYMBOLS; nSymbol[3] < nSymbols[3]; nSymbol[3]++)
	{
		if ((hResource = FindResource((hModule = GetModuleHandle((LPCTSTR)NULL)), (nSymbol[3] == TCHISTORYVIEW_COMMANDALERTSYMBOL_INFORMATION) ? MAKEINTRESOURCE(IDP_TCHISTORYINFORMATION) : ((nSymbol[3] == TCHISTORYVIEW_COMMANDALERTSYMBOL_WARNING) ? MAKEINTRESOURCE(IDP_TCHISTORYWARNING) : MAKEINTRESOURCE(IDP_TCHISTORYERROR)), STRING(IDS_RESOURCETYPE_PICTURE))))
		{
			if ((hMemResource[0] = LoadResource(hModule, hResource)))
			{
				if ((pResource = LockResource(hMemResource[0])))
				{
					if ((hMemResource[1] = GlobalAlloc(GMEM_MOVEABLE, 0)))
					{
						if (SUCCEEDED(CreateStreamOnHGlobal(hMemResource[1], TRUE, &pIStream)))
						{
							if (SUCCEEDED(pIStream->Write(pResource, SizeofResource(hModule, hResource), &cbSymbol)))
							{
								if ((m_pAlertSymbols[nSymbol[3]] = new CImage) != (CImage *)NULL)
								{
									if (SUCCEEDED(m_pAlertSymbols[nSymbol[3]]->Load(pIStream)))
									{
										pIStream->Release();
										continue;
									}
									delete m_pAlertSymbols[nSymbol[3]];
									m_pAlertSymbols[nSymbol[3]] = (CImage *)NULL;
								}
							}
							pIStream->Release();
						}
					}
				}
			}
		}
		while (nSymbol[3] > 0)
		{
			delete m_pAlertSymbols[--nSymbol[3]];
			m_pAlertSymbols[nSymbol[3]] = (CImage *)NULL;
		}
		break;
	}
	return((nSymbol[0] == nSymbols[0] && nSymbol[1] == nSymbols[1] && nSymbol[2] == nSymbols[2] && nSymbol[3] == nSymbols[3]) ? TRUE : FALSE);
}

VOID CTCHistoryView::FreeTelecommandSymbols()
{
	INT  nSymbol;
	INT  nSymbols;

	for (nSymbol = 0, nSymbols = TCHISTORYVIEW_COMMANDFLAGSYMBOLS; nSymbol < nSymbols; nSymbol++)
	{
		if (m_pFlagSymbols[nSymbol] != (CImage *)NULL)
		{
			m_pFlagSymbols[nSymbol]->Destroy();
			delete m_pFlagSymbols[nSymbol];
		}
	}
	for (nSymbol = 0, nSymbols = TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOLS; nSymbol < nSymbols; nSymbol++)
	{
		if (m_pCheckFlagSymbols[nSymbol] != (CImage *)NULL)
		{
			m_pCheckFlagSymbols[nSymbol]->Destroy();
			delete m_pCheckFlagSymbols[nSymbol];
		}
	}
	for (nSymbol = 0, nSymbols = TCHISTORYVIEW_COMMANDRESULTSYMBOLS; nSymbol < nSymbols; nSymbol++)
	{
		if (m_pResultSymbols[nSymbol] != (CImage *)NULL)
		{
			m_pResultSymbols[nSymbol]->Destroy();
			delete m_pResultSymbols[nSymbol];
		}
	}
	for (nSymbol = 0, nSymbols = TCHISTORYVIEW_COMMANDALERTSYMBOLS; nSymbol < nSymbols; nSymbol++)
	{
		if (m_pAlertSymbols[nSymbol] != (CImage *)NULL)
		{
			m_pAlertSymbols[nSymbol]->Destroy();
			delete m_pAlertSymbols[nSymbol];
		}
	}
}

BOOL CTCHistoryView::LoadToolTipCursor()
{
	return(((m_hToolTipCursor = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_TOOLTIPCURSOR), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR))) ? TRUE : FALSE);
}

HCURSOR CTCHistoryView::GetToolTipCursor() CONST
{
	return((!m_hToolTipCursor) ? (HCURSOR)(DWORD_PTR)GetClassLongPtr(GetSafeHwnd(), GCLP_HCURSOR) : m_hToolTipCursor);
}

BOOL CTCHistoryView::FreeToolTipCursor()
{
	if (m_hToolTipCursor)
	{
		DestroyCursor(m_hToolTipCursor);
		m_hToolTipCursor = (HCURSOR)NULL;
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryView::SetLayoutInfo(CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo)
{
	SetScrollInfo(pHorzScrollInfo, pVertScrollInfo);
	return TRUE;
}

BOOL CTCHistoryView::GetLayoutInfo(SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST
{
	GetScrollInfo(pHorzScrollInfo, pVertScrollInfo);
	return TRUE;
}

VOID CTCHistoryView::RecalcLayout()
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

BOOL CTCHistoryView::Lock()
{
	CTCHistoryWnd  *pParentWnd;

	return(((pParentWnd = GetParent())) ? (pParentWnd->Lock() && CTextView::Lock()) : CTextView::Lock());
}

BOOL CTCHistoryView::Unlock()
{
	CTCHistoryWnd  *pParentWnd;

	return(((pParentWnd = GetParent())) ? (CTextView::Unlock() && pParentWnd->Unlock()) : CTextView::Unlock());
}

BEGIN_MESSAGE_MAP(CTCHistoryView, CTextView)
	//{{AFX_MSG_MAP(CTCHistoryView)
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryView message handlers

int CTCHistoryView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CTextViewLock  cLock(this);

	if (CTextView::OnCreate(lpCreateStruct) != -1 && LoadTelecommandSymbols() && LoadToolTipCursor())
	{
		SetTimer(TCHISTORYVIEW_COMMANDUPDATE_TIMERID, TCHISTORYVIEW_COMMANDUPDATE_TIMEOUT, NULL);
		SetClipboardFormat(RegisterClipboardFormat(STRING(IDS_TELECOMMAND_CLIPBOARD_FORMAT)));
		return 0;
	}
	return -1;
}

BOOL CTCHistoryView::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	INT  nPos;
	INT  nRow;
	INT  nIndex;
	INT  nCount;
	INT  nColumn;
	CPoint  ptCursor;
	CString  szText;
	CString  szStage;
	CStringArray  szStages;
	CTextViewLock  cLock(this);

	for (GetCursorPos(&ptCursor), m_wndContentCtrl.ScreenToClient(&ptCursor); IsToolTipModeEnabled() && FindTextFromPoint(ptCursor, nRow, nColumn, TRUE) && GetText(nRow, nColumn, szText); )
	{
		if (nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_NUMBER)))
		{
			if (_tcsstr(szText, STRING(IDS_TCHISTORY_LIST_ALERT_INFORMATION)) || _tcsstr(szText, STRING(IDS_TCHISTORY_LIST_ALERT_WARNING)) || _tcsstr(szText, STRING(IDS_TCHISTORY_LIST_ALERT_ERROR)))
			{
				if (CalcTelecommandSymbolPosition(nRow, nColumn, szText).PtInRect(ptCursor))
				{
					SetCursor(GetToolTipCursor());
					return TRUE;
				}
			}
			break;
		}
		if (nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_FLAGS)))
		{
			if (_tcsstr(szText, STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCK)))
			{
				if (CalcTelecommandSymbolPosition(nRow, nColumn, 4, 0).PtInRect(ptCursor))
				{
					SetCursor(GetToolTipCursor());
					return TRUE;
				}
			}
			if (_tcsstr(szText, STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKIDLE)) || _tcsstr(szText, STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKPENDING)) || _tcsstr(szText, STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKSUCCESS)) || _tcsstr(szText, STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKFAILURE)))
			{
				if (CalcTelecommandSymbolPosition(nRow, nColumn, 4, 1).PtInRect(ptCursor))
				{
					SetCursor(GetToolTipCursor());
					return TRUE;
				}
			}
			if (_tcsstr(szText, STRING(IDS_TCHISTORY_LIST_FLAGS_GROUPED)))
			{
				if (CalcTelecommandSymbolPosition(nRow, nColumn, 4, 2).PtInRect(ptCursor))
				{
					SetCursor(GetToolTipCursor());
					return TRUE;
				}
			}
			if (_tcsstr(szText, STRING(IDS_TCHISTORY_LIST_FLAGS_BLOCKED)))
			{
				if (CalcTelecommandSymbolPosition(nRow, nColumn, 4, 3).PtInRect(ptCursor))
				{
					SetCursor(GetToolTipCursor());
					return TRUE;
				}
			}
			break;
		}
		if (nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_PTVCHECKS)))
		{
			if (_tcsstr(szText, STRING(IDS_TCHISTORY_LIST_PTVCHECKS_ON)) || _tcsstr(szText, STRING(IDS_TCHISTORY_LIST_PTVCHECKS_OFF)) || _tcsstr(szText, STRING(IDS_TCHISTORY_LIST_PTVCHECKS_DISABLED)))
			{
				if (CalcTelecommandSymbolPosition(nRow, nColumn, 1, 0).PtInRect(ptCursor))
				{
					SetCursor(GetToolTipCursor());
					return TRUE;
				}
			}
			break;
		}
		if (nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_PEVCHECKS)))
		{
			if (_tcsstr(szText, STRING(IDS_TCHISTORY_LIST_PEVCHECKS_NONE)) || _tcsstr(szText, STRING(IDS_TCHISTORY_LIST_PEVCHECKS_ON)) || _tcsstr(szText, STRING(IDS_TCHISTORY_LIST_PEVCHECKS_OFF)) || _tcsstr(szText, STRING(IDS_TCHISTORY_LIST_PEVCHECKS_DISABLED)))
			{
				if (CalcTelecommandSymbolPosition(nRow, nColumn, 1, 0).PtInRect(ptCursor))
				{
					SetCursor(GetToolTipCursor());
					return TRUE;
				}
			}
			break;
		}
		if (nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_CEVCHECKS)))
		{
			if (_tcsstr(szText, STRING(IDS_TCHISTORY_LIST_CEVCHECKS_NONE)) || _tcsstr(szText, STRING(IDS_TCHISTORY_LIST_CEVCHECKS_ON)) || _tcsstr(szText, STRING(IDS_TCHISTORY_LIST_CEVCHECKS_OFF)) || _tcsstr(szText, STRING(IDS_TCHISTORY_LIST_CEVCHECKS_DISABLED)))
			{
				if (CalcTelecommandSymbolPosition(nRow, nColumn, 1, 0).PtInRect(ptCursor))
				{
					SetCursor(GetToolTipCursor());
					return TRUE;
				}
			}
			break;
		}
		if (nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_PTVRESULT)))
		{
			if (_tcsstr(szText, STRING(IDS_TCHISTORY_LIST_PTVRESULT_GO)) || _tcsstr(szText, STRING(IDS_TCHISTORY_LIST_PTVRESULT_WAIT)) || _tcsstr(szText, STRING(IDS_TCHISTORY_LIST_PTVRESULT_FAIL)))
			{
				if (CalcTelecommandSymbolPosition(nRow, nColumn, 1, 0).PtInRect(ptCursor))
				{
					SetCursor(GetToolTipCursor());
					return TRUE;
				}
			}
			break;
		}
		if (nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_PEVRESULT)))
		{
			if (_tcsstr(szText, STRING(IDS_TCHISTORY_LIST_PEVRESULT_GO)) || _tcsstr(szText, STRING(IDS_TCHISTORY_LIST_PEVRESULT_NOGO)))
			{
				if (CalcTelecommandSymbolPosition(nRow, nColumn, 1, 0).PtInRect(ptCursor))
				{
					SetCursor(GetToolTipCursor());
					return TRUE;
				}
			}
			break;
		}
		if (nColumn == FindColumnIndex(STRING(IDS_TCHISTORY_TITLEITEM_CEVRESULT)))
		{
			if (szText == STRING(IDS_TCHISTORY_LIST_CEVRESULT_IDLE) || szText == STRING(IDS_TCHISTORY_LIST_CEVRESULT_PENDING) || szText == STRING(IDS_TCHISTORY_LIST_CEVRESULT_PASSED) || szText == STRING(IDS_TCHISTORY_LIST_CEVRESULT_FAILED) || szText == STRING(IDS_TCHISTORY_LIST_CEVRESULT_UNKNOWN) || szText == STRING(IDS_TCHISTORY_LIST_CEVRESULT_UNVERIFIED))
			{
				if (CalcTelecommandSymbolPosition(nRow, nColumn, 1, 0).PtInRect(ptCursor))
				{
					SetCursor(GetToolTipCursor());
					return TRUE;
				}
				break;
			}
			for (szStage = szText, szStages.RemoveAll(); !szStage.IsEmpty(); szStage = (nPos >= 0) ? (szStage.Mid(nPos + lstrlen(STRING(IDS_TCHISTORY_LIST_CEVRESULT_SEPARATOR)))) : EMPTYSTRING)
			{
				if ((nPos = szStage.Find(STRING(IDS_TCHISTORY_LIST_CEVRESULT_SEPARATOR))) >= 0)
				{
					szStages.Add(szStage.Left(nPos));
					continue;
				}
				szStages.Add(szStage);
			}
			for (nIndex = 0, nCount = (INT)szStages.GetSize(); nIndex < nCount; nIndex++)
			{
				if (CalcTelecommandSymbolPosition(nRow, nColumn, nCount, nIndex).PtInRect(ptCursor))
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

BOOL CTCHistoryView::OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	INT  nRow;
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nColumn;
	INT  nHeight;
	CRect  rContent;
	CFont  cFont[2];
	CPoint  ptMenu;
	CPoint  ptToolTip;
	LOGFONT  lfFont[2];
	CString  szColumn;
	CString  szToolTip[3];
	CLocaleMenu  cMenu;
	CMFCPopupMenu  *pFloatingMenu;
	CTCHistoryItem  *pItem;
	CTextViewLock  cLock(this);

	if (message == WM_KEYDOWN)
	{
		if (wParam == VK_UP || wParam == VK_DOWN)
		{
			for (nItem = 0, nItems = (INT)m_pItems[0].GetSize(); nItem < nItems; nItem++)
			{
				if ((pItem = m_pItems[0].GetAt(nItem)) && pItem->IsSelected()) break;
				continue;
			}
			if (wParam == VK_UP  &&  nItem > 0)
			{
				ActivateTelecommand((nItem = nItem - 1));
				ScrollTo(nItem);
				return TRUE;
			}
			if (wParam == VK_DOWN && (nItem < nItems - 1 || nItem == nItems))
			{
				ActivateTelecommand((nItem = (nItem < nItems - 1) ? (nItem + 1) : 0));
				ScrollTo(nItem);
				return TRUE;
			}
		}
		if (wParam == VK_PRIOR || wParam == VK_NEXT)
		{
			for (nItem = nIndex = GetCurTelecommand(), nItems = GetTelecommandCount(), m_wndContentCtrl.GetClientRect(rContent), nHeight = (nItems > 0) ? ((nItem > 0) ? (m_wndContentCtrl.m_nContentTextPos.GetAt(nItem) - m_wndContentCtrl.m_nContentTextPos.GetAt(nItem - 1)) : m_wndContentCtrl.m_nContentTextPos.GetAt(0)) : 0; nItem >= 0 && nItem < nItems; nItem = (wParam == VK_NEXT) ? (nItem + 1) : (nItem - 1))
			{
				if (abs((INT)(m_wndContentCtrl.m_nContentTextPos.GetAt(nIndex) - m_wndContentCtrl.m_nContentTextPos.GetAt(nItem))) >= rContent.Height() - nHeight) break;
				continue;
			}
			if ((nItem = (nIndex >= 0) ? max(min(nItem, nItems - 1), 0) : ((wParam == VK_PRIOR) ? (nItems - 1) : 0)) != nIndex)
			{
				ActivateTelecommand(nItem);
				ScrollTo(nItem);
			}
			return TRUE;
		}
		if (wParam == VK_RETURN)
		{
			for (cLock.Release(); GetCurTelecommand() >= 0; )
			{
				ShowTelecommandProperties();
				break;
			}
			return FALSE;
		}
		if (wParam == VK_ESCAPE)
		{
			ActivateTelecommand(-1);
			return FALSE;
		}
		if (wParam == VK_TAB) GetParent()->SetFocus();
		return FALSE;
	}
	if (message == WM_LBUTTONDOWN)
	{
		if (ActivateTelecommand(FindTextFromPoint(CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)))))
		{
			m_wndContentCtrl.SetFocus();
			return TRUE;
		}
		return FALSE;
	}
	if (message == WM_LBUTTONDBLCLK)
	{
		for (cLock.Release(); IsActivatedTelecommand((nIndex = FindTextFromPoint(CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))))) || ActivateTelecommand(nIndex); )
		{
			ShowTelecommandProperties();
			break;
		}
		return FALSE;
	}
	if (message == WM_RBUTTONDOWN)
	{
		if (GetCursor() != GetToolTipCursor() && (((pItem = m_pItems[0].GetAt(FindTextFromPoint((ptMenu = CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)))))) && pItem->IsSelected()) || ((nIndex = FindTextFromPoint((ptMenu = CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))))) >= 0 && ActivateTelecommand(nIndex))))
		{
			for (m_wndContentCtrl.ClientToScreen(&ptMenu), cLock.Release(); (pFloatingMenu = (cMenu.LoadMenu(IDR_TCHISTORYFLOATINGMENU)) ? new CMFCPopupMenu : (CMFCPopupMenu *)NULL); )
			{
				pFloatingMenu->Create(GetParentFrame(), ptMenu.x, ptMenu.y, cMenu.Detach());
				return FALSE;
			}
		}
		if ((pItem = (GetCursor() == GetToolTipCursor() && FindTextFromPoint((ptToolTip = CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))), nRow, nColumn, TRUE) && GetText(nRow, nColumn, szToolTip[2])) ? m_pItems[0].GetAt(nRow) : (CTCHistoryItem *)NULL))
		{
			for (szToolTip[0] = ConstructToolTipTitle(ptToolTip, szToolTip[2], LookupColumnName((szColumn = m_wndHeaderCtrl.m_szColumnsText.GetAt(nColumn)))), szToolTip[1] = ConstructToolTipText(pItem, ptToolTip, szToolTip[2], LookupColumnName(szColumn)); !szToolTip[0].IsEmpty() || !szToolTip[1].IsEmpty(); )
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
	if (message == WM_SETFOCUS || message == WM_KILLFOCUS)
	{
		for (nItem = 0, nItems = (INT)m_pItems[0].GetSize(), m_wndContentCtrl.m_bFocused = (message == WM_SETFOCUS) ? TRUE : FALSE; nItem < nItems; nItem++)
		{
			if ((pItem = m_pItems[0].GetAt(nItem)) && pItem->IsSelected())
			{
				DrawText(nItem, m_wndContentCtrl.m_szContentText.GetAt(nItem));
				continue;
			}
		}
	}
	if (message == WM_RBUTTONUP) m_wndToolTip.Destroy();
	return FALSE;
}

BOOL CTCHistoryView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CString  szColumn;
	CStringArray  szColumns;
	NMHEADER  *pNotifyInfo = (NMHEADER *)lParam;

	if (pNotifyInfo->hdr.code == HDN_ITEMCLICK)
	{
		for (szColumn = (GetColumns(szColumns) && pNotifyInfo->iItem < szColumns.GetSize()) ? szColumns.GetAt(pNotifyInfo->iItem) : EMPTYSTRING; !szColumn.IsEmpty(); )
		{
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_NUMBER))
			{
				ReportEvent((!m_dlgSearchNumber.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_NAME))
			{
				ReportEvent((!m_dlgSearchName.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_COMPUTER))
			{
				ReportEvent((!m_dlgSearchComputer.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_COMMANDSOURCE))
			{
				ReportEvent((!m_dlgSearchCommandSource.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_DESCRIPTION))
			{
				ReportEvent((!m_dlgSearchDescription.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_CATEGORY))
			{
				ReportEvent((!m_dlgSearchCategory.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_SUBSYSTEM))
			{
				ReportEvent((!m_dlgSearchSubSystem.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_ARGUMENTS))
			{
				ReportEvent((!m_dlgSearchArguments.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_FLAGS))
			{
				ReportEvent((!m_dlgSearchFlags.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_TCPACKET))
			{
				ReportEvent((!m_dlgSearchTCPacket.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_DISPATCHTIME))
			{
				ReportEvent((!m_dlgSearchDispatchTime.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_RELEASETIME))
			{
				ReportEvent((!m_dlgSearchReleaseTime.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_RELEASETIMEOFFSET))
			{
				ReportEvent((!m_dlgSearchReleaseTimeOffset.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_TRANSMISSIONTIME))
			{
				ReportEvent((!m_dlgSearchTransmissionTime.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_EXECUTIONTIME))
			{
				ReportEvent((!m_dlgSearchExecutionTime.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_EXECUTIONTIMEOFFSET))
			{
				ReportEvent((!m_dlgSearchExecutionTimeOffset.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_AUTHORIZATION))
			{
				ReportEvent((!m_dlgSearchAuthorization.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_PTVTIMEWINDOW))
			{
				ReportEvent((!m_dlgSearchPTVTimeWindow.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_PTVCHECKS))
			{
				ReportEvent((!m_dlgSearchPTVCheck.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_PTVRESULT))
			{
				ReportEvent((!m_dlgSearchPTVResult.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_PEVCHECKS))
			{
				ReportEvent((!m_dlgSearchPEVCheck.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_PEVRESULT))
			{
				ReportEvent((!m_dlgSearchPEVResult.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_CEVTIMEWINDOW))
			{
				ReportEvent((!m_dlgSearchCEVTimeWindow.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_CEVCHECKS))
			{
				ReportEvent((!m_dlgSearchCEVCheck.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_CEVRESULT))
			{
				ReportEvent((!m_dlgSearchCEVResult.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			if (szColumn == STRING(IDS_TCHISTORY_TITLEITEM_STATUS))
			{
				ReportEvent((!m_dlgSearchStatus.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
				break;
			}
			break;
		}
	}
	return CTextView::OnNotify(wParam, lParam, pResult);
}

void CTCHistoryView::OnTimer(UINT_PTR nEventID)
{
	INT  nItem;
	INT  nItems;
	BOOL  bUpdate;
	CTCHistoryItem  *pItem[2];
	CTextViewLock  cLock(this);

	if (nEventID == TCHISTORYVIEW_COMMANDUPDATE_TIMERID)
	{
		for (nItem = 0, nItems = (INT)m_pItems[1].GetSize(), bUpdate = FALSE; nItem < nItems; nItem++)
		{
			if ((pItem[1] = ((pItem[0] = m_pItems[1].GetAt(nItem)) && UpdateTelecommand(pItem[0])) ? m_pItems[0].GetAt(m_pItems[0].Find(pItem[0])) : (CTCHistoryItem *)NULL))
			{
				bUpdate |= pItem[1]->CTCItem::Copy(pItem[0]);
				continue;
			}
		}
		if (bUpdate) UpdateContent();
		return;
	}
	CTextView::OnTimer(nEventID);
}

void CTCHistoryView::OnDestroy()
{
	CTextViewLock  cLock(this);

	FreeToolTipCursor();
	FreeTelecommandSymbols();
	KillTimer(TCHISTORYVIEW_COMMANDUPDATE_TIMERID);
	CTextView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CTCHistoryWnd

IMPLEMENT_DYNAMIC(CTCHistoryWnd, CDisplayWnd)

CTCHistoryWnd::CTCHistoryWnd() : CDisplayWnd()
{
	CComputerToken  cComputerToken;

	SetType(DISPLAY_TYPE_TCHISTORY);
	SetFilterMode(TCHISTORY_FILTERMODE_BYCOMPUTER);
	SetFilterComputer(cComputerToken.GetComputerName());
	SetFilterSortMode(TCHISTORY_SORTMODE_BYRELEASETIME | TCHISTORY_SORTMODE_BYLATESTFIRST);
	SetRetrieveMode();
	SetRetrieveSpeed();
	SetRetrieveStartTime();
	SetRetrieveStopTime();
	SetUpdateInfo();
}

BOOL CTCHistoryWnd::Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault)
{
	if (CDisplayWnd::Create(pParentWnd, (!AfxIsValidString(pszTitle) || (!_tcsstr(pszTitle, STRING(IDS_DISPLAY_TITLE_GLOBALTCHISTORY)) && !_tcsstr(pszTitle, STRING(IDS_DISPLAY_TITLE_TCHISTORY)))) ? ((pDefaultInfo->nScope == DISPLAY_SCOPE_GLOBAL) ? STRING(IDS_DISPLAY_TITLE_GLOBALTCHISTORY) : STRING(IDS_DISPLAY_TITLE_TCHISTORY)) : pszTitle, pDefaultInfo->rWnd, IDR_TCHISTORYFRAME))
	{
		if (((pDefaultInfo->nScope == DISPLAY_SCOPE_GLOBAL  &&  SetType(MAKELONG(DISPLAY_TYPE_TCHISTORY, TCHISTORY_TYPE_GLOBAL))) || (pDefaultInfo->nScope == DISPLAY_SCOPE_LOCAL  &&  SetType(MAKELONG(DISPLAY_TYPE_TCHISTORY, TCHISTORY_TYPE_NORMAL)))) && SetScope(pDefaultInfo->nScope) && SetMode(pDefaultInfo->nMode) && Customize(bDefault)) return TRUE;
		DestroyWindow();
	}
	return FALSE;
}

BOOL CTCHistoryWnd::SetLayout(LPCTSTR pszLayout)
{
	return m_wndView.SetLayout(pszLayout);
}
BOOL CTCHistoryWnd::SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns)
{
	return m_wndView.SetLayout(pszLayout, nColumns);
}
BOOL CTCHistoryWnd::SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths)
{
	return m_wndView.SetLayout(pszLayout, nColumns, nWidths);
}

BOOL CTCHistoryWnd::GetLayout(CString &szLayout) CONST
{
	return m_wndView.GetLayout(szLayout);
}
BOOL CTCHistoryWnd::GetLayout(CString &szLayout, CUIntArray &nColumns) CONST
{
	return m_wndView.GetLayout(szLayout, nColumns);
}
BOOL CTCHistoryWnd::GetLayout(CString &szLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST
{
	return m_wndView.GetLayout(szLayout, nColumns, nWidths);
}

BOOL CTCHistoryWnd::SetListTitleFont(CFont *pFont)
{
	return m_wndView.SetListTitleFont(pFont);
}
BOOL CTCHistoryWnd::SetListTitleFont(CONST LOGFONT *plfFont)
{
	return m_wndView.SetListTitleFont(plfFont);
}

BOOL CTCHistoryWnd::GetListTitleFont(CFont *pFont) CONST
{
	return m_wndView.GetListTitleFont(pFont);
}
BOOL CTCHistoryWnd::GetListTitleFont(LOGFONT *plfFont) CONST
{
	return m_wndView.GetListTitleFont(plfFont);
}

BOOL CTCHistoryWnd::SetListItemsFont(CFont *pFont)
{
	return m_wndView.SetListItemsFont(pFont);
}
BOOL CTCHistoryWnd::SetListItemsFont(CONST LOGFONT *plfFont)
{
	return m_wndView.SetListItemsFont(plfFont);
}

BOOL CTCHistoryWnd::GetListItemsFont(CFont *pFont) CONST
{
	return m_wndView.GetListItemsFont(pFont);
}
BOOL CTCHistoryWnd::GetListItemsFont(LOGFONT *plfFont) CONST
{
	return m_wndView.GetListItemsFont(plfFont);
}

BOOL CTCHistoryWnd::SetGridBackgroundColor(COLORREF nColor)
{
	return m_wndView.SetGridBackgroundColor(nColor);
}

BOOL CTCHistoryWnd::GetGridBackgroundColor(COLORREF &nColor) CONST
{
	return m_wndView.GetGridBackgroundColor(nColor);
}

BOOL CTCHistoryWnd::EnableFullViewMode(BOOL bEnable)
{
	return m_wndView.EnableFullViewMode(bEnable);
}

BOOL CTCHistoryWnd::IsFullViewModeEnabled() CONST
{
	return m_wndView.IsFullViewModeEnabled();
}

BOOL CTCHistoryWnd::EnableToolTipMode(BOOL bEnable)
{
	return m_wndView.EnableToolTipMode(bEnable);
}

BOOL CTCHistoryWnd::IsToolTipModeEnabled() CONST
{
	return m_wndView.IsToolTipModeEnabled();
}

BOOL CTCHistoryWnd::SetFilterMode(UINT nMode)
{
	return m_wndView.SetFilterMode(nMode);
}

BOOL CTCHistoryWnd::GetFilterMode(UINT &nMode) CONST
{
	return m_wndView.GetFilterMode(nMode);
}

BOOL CTCHistoryWnd::SetFilterComputer(LPCTSTR pszComputer)
{
	return m_wndView.SetFilterComputer(pszComputer);
}

BOOL CTCHistoryWnd::GetFilterComputer(CString &szComputer) CONST
{
	return m_wndView.GetFilterComputer(szComputer);
}

BOOL CTCHistoryWnd::SetFilterTelecommandName(LPCTSTR pszName)
{
	return m_wndView.SetFilterTelecommandName(pszName);
}

BOOL CTCHistoryWnd::GetFilterTelecommandName(CString &szName) CONST
{
	return m_wndView.GetFilterTelecommandName(szName);
}

BOOL CTCHistoryWnd::SetFilterTelecommandSequence(LPCTSTR pszSequence)
{
	return m_wndView.SetFilterTelecommandSequence(pszSequence);
}

BOOL CTCHistoryWnd::GetFilterTelecommandSequence(CString &szSequence) CONST
{
	return m_wndView.GetFilterTelecommandSequence(szSequence);
}

BOOL CTCHistoryWnd::SetFilterLimitation(UINT nCount)
{
	return m_wndView.SetFilterLimitation(nCount);
}

BOOL CTCHistoryWnd::GetFilterLimitation(UINT &nCount) CONST
{
	return m_wndView.GetFilterLimitation(nCount);
}

BOOL CTCHistoryWnd::SetFilterAutoload(UINT nCount)
{
	return m_wndView.SetFilterAutoload(nCount);
}

BOOL CTCHistoryWnd::GetFilterAutoload(UINT &nCount) CONST
{
	return m_wndView.GetFilterAutoload(nCount);
}

BOOL CTCHistoryWnd::SetFilterSortMode(UINT nMode)
{
	return m_wndView.SetFilterSortMode(nMode);
}

BOOL CTCHistoryWnd::GetFilterSortMode(UINT &nMode) CONST
{
	return m_wndView.GetFilterSortMode(nMode);
}

BOOL CTCHistoryWnd::StartMonitoring()
{
	return m_wndView.StartMonitoring();
}

BOOL CTCHistoryWnd::StopMonitoring()
{
	return m_wndView.StopMonitoring();
}

BOOL CTCHistoryWnd::SetTelecommands(CONST CTCItems &pItems)
{
	if (m_wndView.SetTelecommands(pItems))
	{
		UpdateBars();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryWnd::GetTelecommands(CTCItems &pItems) CONST
{
	return m_wndView.GetTelecommands(pItems);
}

BOOL CTCHistoryWnd::UpdateTelecommands(CONST CTCItems &pItems)
{
	if (m_wndView.UpdateTelecommands(pItems))
	{
		UpdateBars();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryWnd::SetCurTelecommand(INT nIndex)
{
	return m_wndView.SetCurTelecommand(nIndex);
}

INT CTCHistoryWnd::GetCurTelecommand() CONST
{
	return m_wndView.GetCurTelecommand();
}

BOOL CTCHistoryWnd::FindTelecommand(CONST CTCItem *pItem) CONST
{
	return m_wndView.FindTelecommand(pItem);
}

BOOL CTCHistoryWnd::SelectTelecommand(INT nIndex)
{
	return m_wndView.SelectTelecommand(nIndex);
}

BOOL CTCHistoryWnd::HasSelectedTelecommands() CONST
{
	return m_wndView.HasSelectedTelecommands();
}

UINT CTCHistoryWnd::GetTelecommandCount() CONST
{
	return m_wndView.GetTelecommandCount();
}

BOOL CTCHistoryWnd::ShowTelecommandProperties()
{
	return m_wndView.ShowTelecommandProperties();
}

BOOL CTCHistoryWnd::CanShowTelecommandProperties() CONST
{
	return m_wndView.CanShowTelecommandProperties();
}

BOOL CTCHistoryWnd::IsShowingTelecommandProperties() CONST
{
	return m_wndView.IsShowingTelecommandProperties();
}

BOOL CTCHistoryWnd::Start()
{
	StartRetrieveData();
	Initialize(TRUE);
	UpdateAllPanes();
	return TRUE;
}

BOOL CTCHistoryWnd::Prepare(BOOL bDialog)
{
	INT  nResult;

	if (bDialog)
	{
		if ((nResult = m_dlgOpen.Create(this)) == IDCANCEL || nResult <= 0) MDIDestroy();
		return((nResult == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
	}
	return TRUE;
}

BOOL CTCHistoryWnd::Check() CONST
{
	return CheckAccountPrivilege(PRIVILEGE_TCHISTORY_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE);
}

VOID CTCHistoryWnd::Update()
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
BOOL CTCHistoryWnd::Update(CONST CTimeKey &tTimeKey, CTCEnvironment *pTCEnvironment, UINT nFlags)
{
	CTCItem  *pItem;
	CTCItems  pItems;
	CTimeTag  tExecutionTime;
	CTCServiceLock  cLock(this);

	if ((nFlags & HISTORYFILE_TCUNIT) || !nFlags)
	{
		if ((pItem = new CTCItem) != (CTCItem *)NULL)
		{
			if (GetTCService()->Initialize(pTCEnvironment, pItem))
			{
				if ((((m_nRetrieveMode & TCHISTORY_RETRIEVE_BYRELEASETIME) || !pItem->GetExecutionTime(tExecutionTime)) && pItem->GetReleaseTime().GetTimeInSeconds() < m_tRetrieveStartTime.GetTime()) || ((m_nRetrieveMode & TCHISTORY_RETRIEVE_BYEXECUTIONTIME) && pItem->GetExecutionTime(tExecutionTime) && tExecutionTime.GetTimeInSeconds() < m_tRetrieveStartTime.GetTime()))
				{
					delete pItem;
					return TRUE;
				}
				if (pItems.Add(pItem) >= 0)
				{
					for (UpdateTelecommands(pItems); FindTelecommand(pItem); )
					{
						SetUpdateInfo(pItem->GetName(), tTimeKey);
						return TRUE;
					}
					return FALSE;
				}
			}
			delete pItem;
		}
		return FALSE;
	}
	return TRUE;
}

VOID CTCHistoryWnd::Reset(CTCEnvironment *pTCEnvironment)
{
	CTCServiceLock  cLock(this);

	if (IsInitialized())
	{
		if (AfxIsValidAddress(pTCEnvironment, sizeof(CTCEnvironment))) pTCEnvironment->Reset();
		m_wndView.ResetMonitoring(pTCEnvironment);
		SetUpdateInfo();
	}
}

BOOL CTCHistoryWnd::Stop()
{
	Initialize(FALSE);
	StopRetrieveData();
	return TRUE;
}

BOOL CTCHistoryWnd::SaveInfo(INT nPage, INT nDisplay, LPCTSTR pszTitle, CONST PDISPLAYINFO pDisplayInfo)
{
	UINT  nSpeed;
	UINT  nLimit;
	UINT  nMode[3];
	UINT  nAutoload;
	CString  szName;
	CString  szFileName;
	CString  szComputer;
	CString  szTelecommand[2];
	LOGFONT  sFontInfo[2];
	COLORREF  nColor;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CUIntArray  nColumns;
	CUIntArray  nWidths;
	CUIntArray  nTypes;
	CByteArray  bAcks;
	CByteArray  nPrintInfo;
	CDWordArray  nColors;
	CStringArray  szAuditions;
	CStringArray  szNotifications;
	CProfile  cProfile;

	return((CDisplayWnd::SaveInfo(nPage, nDisplay, pszTitle, pDisplayInfo) && ((nPage > 0 && pDisplayInfo->nScope == DISPLAY_SCOPE_GLOBAL) || (GetLayout(szName, nColumns, nWidths) && GetListTitleFont(&sFontInfo[0]) && GetListItemsFont(&sFontInfo[1]) && GetGridBackgroundColor(nColor) && GetFilterMode(nMode[1]) && GetFilterComputer(szComputer) && GetFilterTelecommandName(szTelecommand[0]) && GetFilterTelecommandSequence(szTelecommand[1]) && GetFilterLimitation(nLimit) && GetFilterAutoload(nAutoload) && GetFilterSortMode(nMode[2]) && GetRetrieveMode(nMode[0]) && GetRetrieveSpeed(nSpeed) && GetRetrieveStartTime(tStartTime) && GetRetrieveStopTime(tStopTime) && GetRetrieveFileName(szFileName) && GetAlertOptions(nTypes, szAuditions, szNotifications, nColors, bAcks) && GetPrintJobs(nPrintInfo) && cProfile.SetTCHistoryLayoutName(nPage, nDisplay, szName) && cProfile.SetTCHistoryLayoutInfo(nPage, nDisplay, nColumns, nWidths, nColor, IsToolTipModeEnabled()) && cProfile.SetTCHistoryFontsInfo(nPage, nDisplay, &sFontInfo[0], &sFontInfo[1]) && cProfile.SetTCHistoryFilterInfo(nPage, nDisplay, nMode[1], szComputer, szTelecommand[0], szTelecommand[1], nLimit, nAutoload, nMode[2]) && cProfile.SetTCHistoryModeInfo(nPage, nDisplay, nMode[0], nSpeed, tStartTime, tStopTime) && cProfile.SetTCHistoryRetrieveFileName(nPage, nDisplay, szFileName) && cProfile.SetTCHistoryAlertInfo(nPage, nDisplay, nTypes, szAuditions, szNotifications, nColors, bAcks) && cProfile.SetTCHistoryPrintInfo(nPage, nDisplay, nPrintInfo)))) ? TRUE : FALSE);
}

BOOL CTCHistoryWnd::LoadInfo(INT nPage, INT nDisplay, CString &szTitle, PDISPLAYINFO pDisplayInfo)
{
	UINT  nSpeed;
	UINT  nLimit;
	UINT  nMode[3];
	UINT  nAutoload;
	BOOL  bToolTips;
	CString  szName;
	CString  szFileName;
	CString  szComputer;
	CString  szTelecommand[2];
	LOGFONT  sFontInfo[2];
	COLORREF  nColor;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CUIntArray  nColumns;
	CUIntArray  nWidths;
	CUIntArray  nTypes;
	CByteArray  bAcks;
	CByteArray  nPrintInfo;
	CDWordArray  nColors;
	CStringArray  szAuditions;
	CStringArray  szNotifications;
	CProfile  cProfile;

	return((CDisplayWnd::LoadInfo(nPage, nDisplay, szTitle, pDisplayInfo) && ((nPage > 0 && pDisplayInfo->nScope == DISPLAY_SCOPE_GLOBAL) || (cProfile.GetTCHistoryLayoutName(nPage, nDisplay, szName) && cProfile.GetTCHistoryLayoutInfo(nPage, nDisplay, nColumns, nWidths, nColor, bToolTips) && cProfile.GetTCHistoryFontsInfo(nPage, nDisplay, &sFontInfo[0], &sFontInfo[1]) && cProfile.GetTCHistoryFilterInfo(nPage, nDisplay, nMode[1], szComputer, szTelecommand[0], szTelecommand[1], nLimit, nAutoload, nMode[2]) && cProfile.GetTCHistoryModeInfo(nPage, nDisplay, nMode[0], nSpeed, tStartTime, tStopTime) && cProfile.GetTCHistoryRetrieveFileName(nPage, nDisplay, szFileName) && cProfile.GetTCHistoryAlertInfo(nPage, nDisplay, nTypes, szAuditions, szNotifications, nColors, bAcks) && cProfile.GetTCHistoryPrintInfo(nPage, nDisplay, nPrintInfo) && SetLayout(szName, nColumns, nWidths) && SetListTitleFont(&sFontInfo[0]) && SetListItemsFont(&sFontInfo[1]) && SetFilterMode(nMode[1]) && SetFilterComputer(szComputer) && SetFilterTelecommandName(szTelecommand[0]) && SetFilterTelecommandSequence(szTelecommand[1]) && SetFilterLimitation(nLimit) && SetFilterAutoload(nAutoload) && SetFilterSortMode(nMode[2]) && SetRetrieveMode(nMode[0]) && SetRetrieveSpeed(nSpeed) && SetRetrieveStartTime(tStartTime) && SetRetrieveStopTime(tStopTime) && SetRetrieveFileName(szFileName) && SetAlertOptions(nTypes, szAuditions, szNotifications, nColors, bAcks) && SetPrintJobs(nPrintInfo) && EnableToolTipMode(bToolTips)))) ? TRUE : FALSE);
}

BOOL CTCHistoryWnd::SetLayoutInfo(LPCVOID pData)
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
			for (nColumns.SetSize(sData.cbColumns[0] / sizeof(UINT)), nWidths.SetSize(sData.cbColumns[1] / sizeof(UINT)), CopyMemory(nColumns.GetData(), (LPBYTE)pData + (cbData = sizeof(DATA)), sData.cbColumns[0]), CopyMemory(nWidths.GetData(), (LPBYTE)pData + (cbData = cbData + sData.cbColumns[0]), sData.cbColumns[1]); SetLayoutInfo(nColumns, nWidths, &sData.sFont[0], &sData.sFont[1], &sData.sScrollInfo[0], &sData.sScrollInfo[1]); ) return TRUE;
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

INT CTCHistoryWnd::GetLayoutInfo(LPVOID *pData) CONST
{
	INT  cbData;
	DATA  sData;
	LPVOID  pBlock;
	CUIntArray  nColumns;
	CUIntArray  nWidths;
	CTCServiceLock  cLock(this);

	if (GetScope() == DISPLAY_SCOPE_GLOBAL)
	{
		if (GetLayoutInfo(nColumns, nWidths, &sData.sFont[0], &sData.sFont[1], &sData.sScrollInfo[0], &sData.sScrollInfo[1]))
		{
			for (sData.cbColumns[0] = (INT)(nColumns.GetSize()*sizeof(UINT)), sData.cbColumns[1] = (INT)(nWidths.GetSize()*sizeof(UINT)), sData.cbSize = sizeof(DATA) + sData.cbColumns[0] + sData.cbColumns[1]; (pBlock = (AfxIsValidAddress(pData, sizeof(DATA))) ? (LPVOID)GlobalReAlloc(*pData, sData.cbSize, GMEM_MOVEABLE | GMEM_ZEROINIT) : (LPVOID)NULL); )
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

BOOL CTCHistoryWnd::QueryDefaultInfo(PDISPLAYINFO pDefaultInfo) CONST
{
	pDefaultInfo->ptWnd.x = 0;
	pDefaultInfo->ptWnd.y = 0;
	pDefaultInfo->nNumber = -1;
	pDefaultInfo->rWnd = rectDefault;
	pDefaultInfo->nScope = DISPLAY_SCOPE_LOCAL;
	pDefaultInfo->nMode = DISPLAY_MODE_REALTIME;
	pDefaultInfo->pData = (LPVOID)NULL;
	pDefaultInfo->nShow = SW_SHOWNORMAL;
	pDefaultInfo->bShow = TRUE;
	return TRUE;
}

BOOL CTCHistoryWnd::QueryDefaultMenu(CLocaleMenu &cMenu, CImageList &cImages, CUIntArray &nImageIDs) CONST
{
	INT  nIndex;
	INT  nCount;
	INT  iImage;
	UINT  nButtonID;
	UINT  nButtonStyle;
	CBitmap  cBitmap[2];
	BITMAP  sBitmap;

	for (cImages.DeleteImageList(), nImageIDs.RemoveAll(); cBitmap[0].LoadBitmap(IDB_TCHISTORYFRAMESMALLIMAGES) && cBitmap[1].LoadBitmap(IDB_TCHISTORYFRAMEEXTRAIMAGES) && cBitmap[0].GetBitmap(&sBitmap); )
	{
		for (nIndex = 0, nCount = (cImages.Create(sBitmap.bmHeight, sBitmap.bmHeight, ILC_COLOR32, sBitmap.bmWidth / sBitmap.bmHeight, 1) && cImages.Add(&cBitmap[0], RGB(0, 0, 0)) >= 0) ? m_wndToolBar.GetCount() : 0; nIndex < nCount; nIndex++)
		{
			for (m_wndToolBar.GetButtonInfo(nIndex, nButtonID, nButtonStyle, iImage); nButtonID != 0 && nButtonID != (UINT)-1; )
			{
				nImageIDs.Add(nButtonID);
				break;
			}
		}
		if (nCount > 0 && cImages.Add(&cBitmap[1], RGB(0, 0, 0)) >= 0) nImageIDs.Add(IDM_TCHISTORYCOPY);
		cBitmap[0].DeleteObject();
		cBitmap[1].DeleteObject();
		break;
	}
	return cMenu.LoadMenu(IDR_TCHISTORYFRAME);
}

VOID CTCHistoryWnd::UpdateBars()
{
	CTCServiceLock  cLock(this);

	UpdateMessagePane();
	UpdateModePane();
	UpdateTypePane();
}

BOOL CTCHistoryWnd::Print(PRINTDLG *pPrintInfo)
{
	INT  nJob;
	INT  nJobs;
	CTCHistoryPrintJobs  pJobs;
	CTCHistoryPrintJobInfo  *pJobInfo;
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
		if (pJobInfo->GetPrintMode() & TCHISTORY_PRINT_CLEARCOMMENTS)
		{
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~TCHISTORY_PRINT_CLEARCOMMENTS);
			pJobInfo->SetComments(EMPTYSTRING);
			SetPrintJobs(pJobs);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryWnd::CanPrint() CONST
{
	return((GetTelecommandCount() > 0) ? TRUE : FALSE);
}

BOOL CTCHistoryWnd::ProcessRealtimeData()
{
	return((GetScope() == DISPLAY_SCOPE_GLOBAL) ? TRUE : FALSE);
}

BOOL CTCHistoryWnd::StartRetrieveData(UINT nMode, UINT nSpeed, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	SetRetrieveMode(nMode);
	SetRetrieveSpeed(nSpeed);
	SetRetrieveStartTime(tStartTime);
	SetRetrieveStopTime(tStopTime);
	return StartRetrieveData();
}
BOOL CTCHistoryWnd::StartRetrieveData()
{
	CString  szTag;
	CTimeTag  tTag;
	CEvent  bInit[2];

	if (GetScope() == DISPLAY_SCOPE_LOCAL)
	{
		if (GetMode() == DISPLAY_MODE_HISTORY  &&  !IsRetrievingData())
		{
			if (m_cRetrieveThread.Start(this, bInit[0], bInit[1], GetRetrieveFileName(), GetRetrieveMode(), GetRetrieveSpeed(), GetRetrieveStartTime(), GetRetrieveStopTime(), &m_bRetrieveFlag, m_cRetrieveStop, m_cRetrieveAutoForward, m_cRetrieveManualForward, m_cRetrievePseudoRealtime) && UpdateAllPanes())
			{
				for (WaitForSingleObject(bInit[0], INFINITE); Initialize(szTag, tTag); )
				{
					SetUpdateInfo();
					SetEvent(bInit[1]);
					return TRUE;
				}
				SetEvent(bInit[1]);
			}
			ReportEvent(SYSTEM_WARNING_TCHISTORY_RETRIEVE_FAILURE);
		}
		return FALSE;
	}
	return RetrieveAutoData();
}

LONG CTCHistoryWnd::IsRetrievingData() CONST
{
	LONG  bFlag;

	InterlockedExchange(&bFlag, m_bRetrieveFlag);
	return((m_cRetrieveThread.IsThreadActive()) ? bFlag : FALSE);
}

BOOL CTCHistoryWnd::RetrieveMoreData(UINT nAction)
{
	if (IsRetrievingData())
	{
		if (nAction == TCHISTORY_RETRIEVE_STOPPED)
		{
			SetRetrieveMode(GetRetrieveMode() | nAction);
			m_cRetrieveStop.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == TCHISTORY_RETRIEVE_AUTOFORWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (TCHISTORY_RETRIEVE_EXACTTIME | TCHISTORY_RETRIEVE_STOPBYTIME | TCHISTORY_RETRIEVE_STOPBYEND)) | nAction);
			m_cRetrieveAutoForward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == TCHISTORY_RETRIEVE_MANUALFORWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (TCHISTORY_RETRIEVE_EXACTTIME | TCHISTORY_RETRIEVE_STOPBYTIME | TCHISTORY_RETRIEVE_STOPBYEND)) | nAction);
			m_cRetrieveManualForward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == TCHISTORY_RETRIEVE_PSEUDOREALTIME)
		{
			SetRetrieveMode((GetRetrieveMode() & (TCHISTORY_RETRIEVE_EXACTTIME | TCHISTORY_RETRIEVE_STOPBYTIME | TCHISTORY_RETRIEVE_STOPBYEND)) | nAction);
			m_cRetrievePseudoRealtime.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTCHistoryWnd::RetrieveAutoData()
{
	INT  nItem;
	INT  nItems;
	UINT  nCount;
	CTCItem  *pItem;
	CTCItems  pItems[2];
	CTimeKey  tTimeKey;
	CByteArray  nData;
	CHistoryFile  cFile;
	CTCEnvironment  cTCEnvironment;
	CTCServiceLock  cLock(this);

	if (GetMode() == DISPLAY_MODE_REALTIME)
	{
		if (cTCEnvironment.Create(GetDatabase(), FALSE))
		{
			if (GetFilterAutoload(nCount) && nCount > GetTelecommandCount() && m_wndView.GetTelecommands(pItems[0]))
			{
				if (cFile.Open(GetRetrieveFileName(), GetAccountSpacecraftName(), HISTORYFILE_TYPE_RETRIEVE, CFile::modeRead))
				{
					for (nItem = 0, nItems = (cFile.SeekFromEnd(10 * nCount) && cFile.CLogFile::Read(tTimeKey, nData)) ? nCount : 0; nItems > 0; nItem++)
					{
						if ((!nItem && ((cFile.Read(tTimeKey, &cTCEnvironment) & (HISTORYFILE_SUCCESS | HISTORYFILE_TCUNIT)) == (HISTORYFILE_SUCCESS | HISTORYFILE_TCUNIT))) || (nItem > 0 && ((cFile.ReadNext(tTimeKey, &cTCEnvironment) & (HISTORYFILE_SUCCESS | HISTORYFILE_TCUNIT)) == (HISTORYFILE_SUCCESS | HISTORYFILE_TCUNIT))))
						{
							if ((pItem = new CTCItem) != (CTCItem *)NULL)
							{
								if (GetTCService()->Initialize(&cTCEnvironment, pItem))
								{
									if (pItems[0].Find(pItem) >= 0)
									{
										delete pItem;
										continue;
									}
									if (pItems[1].Add(pItem) >= 0) continue;
								}
								delete pItem;
							}
						}
						break;
					}
					for (; pItems[1].GetSize() > 0; )
					{
						m_wndView.UpdateTelecommands(pItems[1]);
						break;
					}
					for (m_wndView.GetTelecommands(pItems[1]); nItems < pItems[1].GetSize(); )
					{
						if ((pItem = pItems[1].GetAt(0)) && pItems[0].Find(pItem) < 0)
						{
							pItems[1].RemoveAt(0);
							delete pItem;
							continue;
						}
						break;
					}
					if (m_wndView.SetTelecommands(pItems[1]))
					{
						cTCEnvironment.Destroy();
						cFile.Close();
						return TRUE;
					}
					cFile.Close();
				}
				cTCEnvironment.Destroy();
				return FALSE;
			}
			if (GetFilterAutoload(nCount) && nCount <= GetTelecommandCount())
			{
				cTCEnvironment.Destroy();
				return TRUE;
			}
			cTCEnvironment.Destroy();
		}
	}
	return FALSE;
}

BOOL CTCHistoryWnd::StopRetrieveData()
{
	return(((IsRetrievingData() && m_cRetrieveThread.Stop()) || !IsRetrievingData()) ? TRUE : FALSE);
}

BOOL CTCHistoryWnd::SetRetrieveMode(UINT nMode)
{
	CTCServiceLock  cLock(this);

	m_nRetrieveMode = nMode;
	m_bRetrieveFlag = MAKELONG((nMode) ? LOWORD(m_bRetrieveFlag) : FALSE, (nMode) ? HIWORD(m_bRetrieveFlag) : FALSE);
	return TRUE;
}

BOOL CTCHistoryWnd::GetRetrieveMode(UINT &nMode) CONST
{
	nMode = m_nRetrieveMode;
	return TRUE;
}
UINT CTCHistoryWnd::GetRetrieveMode() CONST
{
	return m_nRetrieveMode;
}

BOOL CTCHistoryWnd::SetRetrieveSpeed(UINT nSpeed)
{
	m_nRetrieveSpeed = nSpeed;
	return TRUE;
}

BOOL CTCHistoryWnd::GetRetrieveSpeed(UINT &nSpeed) CONST
{
	nSpeed = m_nRetrieveSpeed;
	return TRUE;
}
UINT CTCHistoryWnd::GetRetrieveSpeed() CONST
{
	return m_nRetrieveSpeed;
}

BOOL CTCHistoryWnd::SetRetrieveStartTime(CONST CTimeKey &tStartTime)
{
	CTCServiceLock  cLock(this);

	m_tRetrieveStartTime = tStartTime;
	return TRUE;
}

BOOL CTCHistoryWnd::GetRetrieveStartTime(CTimeKey &tStartTime) CONST
{
	CTCServiceLock  cLock(this);

	tStartTime = m_tRetrieveStartTime;
	return TRUE;
}
CTimeKey CTCHistoryWnd::GetRetrieveStartTime() CONST
{
	CTCServiceLock  cLock(this);

	return m_tRetrieveStartTime;
}

BOOL CTCHistoryWnd::SetRetrieveStopTime(CONST CTimeKey &tStopTime)
{
	CTCServiceLock  cLock(this);

	m_tRetrieveStopTime = tStopTime;
	return TRUE;
}

BOOL CTCHistoryWnd::GetRetrieveStopTime(CTimeKey &tStopTime) CONST
{
	CTCServiceLock  cLock(this);

	tStopTime = m_tRetrieveStopTime;
	return TRUE;
}
CTimeKey CTCHistoryWnd::GetRetrieveStopTime() CONST
{
	CTCServiceLock  cLock(this);

	return m_tRetrieveStopTime;
}

BOOL CTCHistoryWnd::SetRetrieveFileName(LPCTSTR pszFileName)
{
	CTCServiceLock  cLock(this);

	m_szRetrieveFileName = pszFileName;
	return TRUE;
}

BOOL CTCHistoryWnd::GetRetrieveFileName(CString &szFileName) CONST
{
	CTCServiceLock  cLock(this);

	szFileName = GetRetrieveFileName();
	return TRUE;
}
CString CTCHistoryWnd::GetRetrieveFileName() CONST
{
	CString  szFileName;
	CHistoryStoreFile  cFile;
	CHistoryStoreFiles  pFiles;
	CTCServiceLock  cLock(this);

	if (GetTCService()->GetTCHistoryFiles(HISTORYFILE_TYPE_RETRIEVE, pFiles) > 0)
	{
		if (pFiles.Find(m_szRetrieveFileName) >= 0)
		{
			szFileName = m_szRetrieveFileName;
			return szFileName;
		}
		if (GetTCService()->GetDefaultTCHistoryFile(HISTORYFILE_TYPE_RETRIEVE, cFile))
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

BOOL CTCHistoryWnd::DoAcknowledgeTelecommand()
{
	if (m_wndView.DoAcknowledgeTelecommand())
	{
		UpdateBars();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryWnd::CanAcknowledgeTelecommand() CONST
{
	return m_wndView.CanAcknowledgeTelecommand();
}

BOOL CTCHistoryWnd::DoCopyTelecommand()
{
	if (m_wndView.DoCopyTelecommand())
	{
		UpdateBars();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryWnd::CanCopyTelecommand() CONST
{
	return m_wndView.CanCopyTelecommand();
}

BOOL CTCHistoryWnd::SetAlertOptions(CONST CUIntArray &nTypes, CONST CStringArray &szAuditions, CONST CStringArray &szNotifications, CONST CDWordArray &nAcknowledgeColors, CONST CByteArray &bAcknowledgments)
{
	CTCServiceLock  cLock(this);

	m_nAlertTypes.Copy(nTypes);
	m_szAlertAuditions.Copy(szAuditions);
	m_szAlertNotifications.Copy(szNotifications);
	m_nAlertAcknowledgeColors.Copy(nAcknowledgeColors);
	m_bAlertAcknowledgments.Copy(bAcknowledgments);
	return TRUE;
}

BOOL CTCHistoryWnd::GetAlertOptions(CUIntArray &nTypes, CStringArray &szAuditions, CStringArray &szNotifications, CDWordArray &nAcknowledgeColors, CByteArray &bAcknowledgments) CONST
{
	CTCServiceLock  cLock(this);

	nTypes.Copy(m_nAlertTypes);
	szAuditions.Copy(m_szAlertAuditions);
	szNotifications.Copy(m_szAlertNotifications);
	nAcknowledgeColors.Copy(m_nAlertAcknowledgeColors);
	bAcknowledgments.Copy(m_bAlertAcknowledgments);
	return TRUE;
}

BOOL CTCHistoryWnd::Alert(CONST CTCHistoryItem *pItem, UINT nStage)
{
	INT  nPos;
	INT  nType;
	INT  nTypes;
	UINT  nState;
	UINT  nReason;
	WORD  wVoiceGender;
	WORD  wVoiceAge;
	DWORD  dwVolume;
	DWORD  dwPitch;
	DWORD  dwPlayback;
	CString  szAdapter;
	CString  szSpeaker;
	CString  szMessage[2];
	CString  szNotifications;
	CStringTools  cStringTools;
	CEventObject  *pEvent;
	CAuditionProfiles  pAuditionProfiles;
	CAuditionProfileInfo  *pAuditionProfileInfo;
	CTCServiceLock  cLock(this);

	for (nType = 0, nTypes = (INT)m_nAlertTypes.GetSize(), szMessage[0].Format(STRING(IDS_TCHISTORY_ALERTMESSAGE_MEMBERSHIPFORMAT), (LPCTSTR)pItem->GetName(), (LPCTSTR)pItem->GetMembership(), (LPCTSTR)cStringTools.ConvertUIntToPaddedString(pItem->GetMembershipID(), max(cStringTools.ConvertUIntToString(pItem->GetMembershipSize()).GetLength(), 3))); nType < nTypes; nType++)
	{
		if ((m_nAlertTypes.GetAt(nType) == TCHISTORY_ALERTTYPE_TELECOMMANDACCEPTANCESUCCESS || m_nAlertTypes.GetAt(nType) == TCHISTORY_ALERTTYPE_TELECOMMANDACCEPTANCEFAILURE) && (nStage & TCVERIFICATIONSTAGE_ACCEPTANCE) && pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE), nState, nReason) && (nState == TCHISTORYITEM_RESULT_CEV_PASSED || nState == TCHISTORYITEM_RESULT_CEV_FAILED))
		{
			szMessage[1].Format((nState == TCHISTORYITEM_RESULT_CEV_PASSED) ? STRING(IDS_TCHISTORY_ALERTMESSAGE_TELECOMMANDACCEPTANCESUCCESSFORMAT) : STRING(IDS_TCHISTORY_ALERTMESSAGE_TELECOMMANDACCEPTANCEFAILUREFORMAT), (pItem->GetMembership().IsEmpty()) ? (LPCTSTR)pItem->GetName() : (LPCTSTR)szMessage[0]);
			break;
		}
		if ((m_nAlertTypes.GetAt(nType) == TCHISTORY_ALERTTYPE_TELECOMMANDSTARTSUCCESS || m_nAlertTypes.GetAt(nType) == TCHISTORY_ALERTTYPE_TELECOMMANDSTARTFAILURE) && (nStage & TCVERIFICATIONSTAGE_START) && pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START), nState, nReason) && (nState == TCHISTORYITEM_RESULT_CEV_PASSED || nState == TCHISTORYITEM_RESULT_CEV_FAILED))
		{
			szMessage[1].Format((nState == TCHISTORYITEM_RESULT_CEV_PASSED) ? STRING(IDS_TCHISTORY_ALERTMESSAGE_TELECOMMANDSTARTSUCCESSFORMAT) : STRING(IDS_TCHISTORY_ALERTMESSAGE_TELECOMMANDSTARTFAILUREFORMAT), (pItem->GetMembership().IsEmpty()) ? (LPCTSTR)pItem->GetName() : (LPCTSTR)szMessage[0]);
			break;
		}
		if ((m_nAlertTypes.GetAt(nType) == TCHISTORY_ALERTTYPE_TELECOMMANDPROGRESSSUCCESS || m_nAlertTypes.GetAt(nType) == TCHISTORY_ALERTTYPE_TELECOMMANDPROGRESSFAILURE) && (nStage & TCVERIFICATIONSTAGE_PROGRESS) && pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS), nState, nReason) && (nState == TCHISTORYITEM_RESULT_CEV_PASSED || nState == TCHISTORYITEM_RESULT_CEV_FAILED))
		{
			szMessage[1].Format((nState == TCHISTORYITEM_RESULT_CEV_PASSED) ? STRING(IDS_TCHISTORY_ALERTMESSAGE_TELECOMMANDPROGRESSSUCCESSFORMAT) : STRING(IDS_TCHISTORY_ALERTMESSAGE_TELECOMMANDPROGRESSFAILUREFORMAT), (pItem->GetMembership().IsEmpty()) ? (LPCTSTR)pItem->GetName() : (LPCTSTR)szMessage[0]);
			break;
		}
		if ((m_nAlertTypes.GetAt(nType) == TCHISTORY_ALERTTYPE_TELECOMMANDCOMPLETIONSUCCESS || m_nAlertTypes.GetAt(nType) == TCHISTORY_ALERTTYPE_TELECOMMANDCOMPLETIONFAILURE) && (nStage & TCVERIFICATIONSTAGE_COMPLETION) && pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION), nState, nReason) && (nState == TCHISTORYITEM_RESULT_CEV_PASSED || nState == TCHISTORYITEM_RESULT_CEV_FAILED))
		{
			szMessage[1].Format((nState == TCHISTORYITEM_RESULT_CEV_PASSED) ? STRING(IDS_TCHISTORY_ALERTMESSAGE_TELECOMMANDCOMPLETIONSUCCESSFORMAT) : STRING(IDS_TCHISTORY_ALERTMESSAGE_TELECOMMANDCOMPLETIONFAILUREFORMAT), (pItem->GetMembership().IsEmpty()) ? (LPCTSTR)pItem->GetName() : (LPCTSTR)szMessage[0]);
			break;
		}
		if (m_nAlertTypes.GetAt(nType) == TCHISTORY_ALERTTYPE_TELECOMMANDVERIFICATIONFAILURE  &&  !nStage && ((pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_FAILED) || (pItem->GetResult() & TCHISTORYITEM_RESULT_CEV_UNVERIFIED)))
		{
			szMessage[1].Format(STRING(IDS_TCHISTORY_ALERTMESSAGE_TELECOMMANDVERIFICATIONFAILUREFORMAT), (pItem->GetMembership().IsEmpty()) ? (LPCTSTR)pItem->GetName() : (LPCTSTR)szMessage[0]);
			break;
		}
	}
	if (nType < nTypes)
	{
		if ((pAuditionProfileInfo = (GetAuditionProfiles(pAuditionProfiles)) ? pAuditionProfiles.GetAt(pAuditionProfiles.Find(m_szAlertAuditions.GetAt(nType))) : (CAuditionProfileInfo *)NULL))
		{
			for (pAuditionProfileInfo->GetAdapterInfo(szAdapter, dwVolume, dwPitch, dwPlayback), pAuditionProfileInfo->GetVoiceSound(szSpeaker, wVoiceGender, wVoiceAge); (pEvent = new CEventObject); )
			{
				pEvent->SetCategory(EVENT_CATEGORY_SYSTEM);
				pEvent->SetType(STRING(IDS_TCHISTORY_ALERTTYPE_DEFAULT));
				pEvent->SetSubtype(STRING(IDS_TCHISTORY_ALERTSUBTYPE_DEFAULT));
				pEvent->SetAudition(pAuditionProfileInfo->GetAudition());
				pEvent->SetAudioInfo(szAdapter, dwVolume, dwPitch, dwPlayback);
				pEvent->SetAuditBeep(pAuditionProfileInfo->GetBeepSound());
				pEvent->SetAuditWave(pAuditionProfileInfo->GetWaveSound());
				pEvent->SetAuditVoice(szSpeaker, wVoiceGender, wVoiceAge);
				pEvent->SetAuditTime(CTime::GetCurrentTime().GetTime());
				pEvent->SetAuditColor(m_nAlertAcknowledgeColors.GetAt(nType));
				pEvent->Acknowledge(!m_bAlertAcknowledgments.GetAt(nType));
				pEvent->SetUser(GetAccountUserName());
				pEvent->SetMessage(szMessage[1]);
				pEvent->Show(TRUE);
				ReportEvent(pEvent);
				break;
			}
		}
		for (szNotifications = m_szAlertNotifications.GetAt(nType); !szNotifications.IsEmpty(); szNotifications = (nPos >= 0) ? szNotifications.Mid(nPos + 1) : EMPTYSTRING)
		{
			DoNotification(((nPos = szNotifications.Find(TAB)) >= 0) ? szNotifications.Left(nPos) : szNotifications, szMessage[1]);
			continue;
		}
	}
	return TRUE;
}

BOOL CTCHistoryWnd::SetPrintJobs(CONST CTCHistoryPrintJobs &pPrintJobs)
{
	CTCServiceLock  cLock(this);

	return m_pPrintJobs.Copy(&pPrintJobs);
}

BOOL CTCHistoryWnd::GetPrintJobs(CTCHistoryPrintJobs &pPrintJobs) CONST
{
	CTCServiceLock  cLock(this);

	return pPrintJobs.Copy(&m_pPrintJobs);
}

BOOL CTCHistoryWnd::Print(CONST CTCHistoryPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo)
{
	CDC  cDC;
	BOOL  bMetric;
	RECT  rtMargin[2];
	SIZE  ptPaperSize;
	CString  szLayout;
	LOGFONT  lfFont[2];
	DEVMODE  *pDevMode;
	DEVNAMES  *pDevNames;
	CPtrArray  pSymbols;
	CUIntArray  nSymbolIDs;
	CStringArray  szColumns;
	CStringArray  szContents;
	CPrintProfiles  cPrintProfiles;
	CPrintProfileInfo  *pPrintProfileInfo;
	CTextViewAttributes  pAttributes;

	if ((pPrintProfileInfo = (GetPrintProfiles(cPrintProfiles)) ? cPrintProfiles.GetAt(cPrintProfiles.Find(pJobInfo->GetProfile())) : (CPrintProfileInfo *)NULL) && pPrintProfileInfo->GetPaperInfo(ptPaperSize, rtMargin[0], rtMargin[1], bMetric))
	{
		if (GetLayout(szLayout) && GetPrintProperties(pJobInfo, szColumns, szContents, pAttributes, &lfFont[0], &lfFont[1], pSymbols, nSymbolIDs))
		{
			if (!AfxIsValidAddress(pPrintInfo, sizeof(PRINTDLG)))
			{
				if (CreatePrinterDC(pPrintProfileInfo, cDC))
				{
					if (PrintJob(cDC, pJobInfo, pPrintProfileInfo->GetPrinterName(), 0, 0, rtMargin[0], bMetric, szLayout, szColumns, szContents, pAttributes, &lfFont[0], &lfFont[1], pSymbols, nSymbolIDs))
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
						if (PrintJob(cDC, pJobInfo, (LPCTSTR)pDevMode->dmDeviceName, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nFromPage : 0, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nToPage : 0, rtMargin[0], bMetric, szLayout, szColumns, szContents, pAttributes, &lfFont[0], &lfFont[1], pSymbols, nSymbolIDs))
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

CTCHistoryWnd *CTCHistoryWnd::Find(INT nType, UINT nMode, LPCTSTR pszName) CONST
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szLayout;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTCHistoryWnd  *pTCHistoryWnd;

	for (nDisplay = 0, nDisplays = GetDisplayArea()->EnumDisplays(pDisplays), pTCHistoryWnd = (CTCHistoryWnd *)NULL; nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_TCHISTORY  &&  HIWORD(pDisplayWnd->GetType()) == HIWORD(nType) && pDisplayWnd->GetMode() == nMode)
		{
			if ((pTCHistoryWnd = (CTCHistoryWnd *)pDisplayWnd)->GetLayout(szLayout) && szLayout == pszName) break;
			continue;
		}
	}
	return((nDisplay < nDisplays) ? pTCHistoryWnd : (CTCHistoryWnd *)NULL);
}

VOID CTCHistoryWnd::SetUpdateInfo()
{
	CTCServiceLock  cLock(this);

	m_szTCUnit.Empty();
	m_tTCUnit = 0;
	UpdateMessagePane();
}
VOID CTCHistoryWnd::SetUpdateInfo(LPCTSTR pszTag, CONST CTimeTag &tTag)
{
	CTCServiceLock  cLock(this);

	m_szTCUnit = pszTag;
	m_tTCUnit = tTag;
	UpdateMessagePane();
}

BOOL CTCHistoryWnd::GetUpdateInfo(CString &szTag, CTimeTag &tTag) CONST
{
	CTCServiceLock  cLock(this);

	szTag = m_szTCUnit;
	tTag = m_tTCUnit;
	return TRUE;
}

BOOL CTCHistoryWnd::CreateToolBar()
{
	if (m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndToolBar.LoadToolBar(IDB_TCHISTORYFRAMELARGEIMAGES, 0, IDB_TCHISTORYFRAMESMALLIMAGES, TRUE))
	{
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCHISTORYSETTINGS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCHISTORYDETAILS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCHISTORYACKNOWLEDGE), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCHISTORYRETRIEVALS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCHISTORYRETRIEVESTOP), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCHISTORYRETRIEVEPSEUDOREALTIME), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCHISTORYRETRIEVEFORWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCHISTORYRETRIEVESTEPFORWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCHISTORYFULLVIEWMODE), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCHISTORYPRINT), TBBS_DISABLED);
		DockPane(&m_wndToolBar);
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryWnd::CreateStatusBar()
{
	if (m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndStatusBar.SetIndicators(nTCHistoryStatusBarIndicators, 1))
	{
		m_wndStatusBar.EnableToolTips();
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryWnd::CreateView()
{
	if (m_wndView.Create(this, TVS_HEADER | TVS_TOP | TVS_BUTTONS | TVS_HSCROLL | TVS_VSCROLL | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE))
	{
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryWnd::Customize(BOOL bDefault)
{
	CString  szName;
	LOGFONT  sFontInfo[2];
	CUIntArray  nColumns;
	CUIntArray  nWidths;
	CByteArray  nPrintInfo;
	CTCHistoryPrintJobs  pPrintJobs;

	return((((!bDefault &&  GetLayout(szName, nColumns, nWidths) && GetListTitleFont(&sFontInfo[0]) && GetListItemsFont(&sFontInfo[1]) && (SetLayout((szName = (HIWORD(GetType()) == TCHISTORY_TYPE_GLOBAL) ? STRING(IDS_DISPLAY_TITLE_GLOBALTCHISTORY) : (LPCTSTR)szName), nColumns, nWidths) || SetLayout(szName)) && SetListTitleFont(&sFontInfo[0]) && SetListItemsFont(&sFontInfo[1])) || (bDefault  &&  GetLayout(szName) && SetLayout(szName))) && ((!bDefault  &&  GetPrintJobs(nPrintInfo) && nPrintInfo.GetSize() > 0) || SetPrintJobs(nPrintInfo))) ? TRUE : FALSE);
}

BOOL CTCHistoryWnd::UpdateAllPanes()
{
	INT  nPane;
	INT  nPanes;

	for (nPane = 0, nPanes = sizeof(nTCHistoryStatusBarIndicators) / sizeof(UINT); nPane < nPanes; nPane++)
	{
		if (m_wndStatusBar.CommandToIndex(nTCHistoryStatusBarIndicators[nPane]) != nPane) break;
		continue;
	}
	if (nPane < nPanes)
	{
		if (m_wndStatusBar.SetIndicators(nTCHistoryStatusBarIndicators, sizeof(nTCHistoryStatusBarIndicators) / sizeof(UINT)))
		{
			UpdateBars();
			return TRUE;
		}
		return FALSE;
	}
	UpdateBars();
	return TRUE;
}

VOID CTCHistoryWnd::UpdateMessagePane()
{
	UINT  nCount;
	CTimeTag  tTag;
	CString  szTag;
	CString  szMessage[2];

	if (GetMode() == DISPLAY_MODE_HISTORY  &&  GetUpdateInfo(szTag, tTag))
	{
		szMessage[0].Format((szTag.IsEmpty()) ? ((tTag > 0) ? STRING(IDS_TCHISTORY_STATUSBAR_FULLUPDATEMESSAGE) : ((IsRetrievingData() && HIWORD(IsRetrievingData())) ? STRING(IDS_TCHISTORY_STATUSBAR_RETRIEVEMESSAGE) : STRING(IDS_TCHISTORY_STATUSBAR_NODATAMESSAGE))) : STRING(IDS_TCHISTORY_STATUSBAR_UPDATEMESSAGE), (LPCTSTR)tTag.FormatGmt(), (LPCTSTR)szTag);
		szMessage[1].Format(((nCount = GetTelecommandCount()) > 0) ? ((nCount > 1) ? STRING(IDS_TCHISTORY_STATUSBAR_DATAMESSAGES) : STRING(IDS_TCHISTORY_STATUSBAR_DATAMESSAGE)) : STRING(IDS_TCHISTORY_STATUSBAR_NODATAMESSAGE), nCount);
		m_wndStatusBar.SetPaneText(ID_TCHISTORY_STATUSBAR_MESSAGEPANE, (szMessage[0] != STRING(IDS_TCHISTORY_STATUSBAR_NODATAMESSAGE)) ? ((szMessage[0] != STRING(IDS_TCHISTORY_STATUSBAR_RETRIEVEMESSAGE)) ? (szMessage[0] + szMessage[1]) : szMessage[0]) : szMessage[1]);
		return;
	}
	szMessage[1].Format(((nCount = GetTelecommandCount()) > 0) ? ((nCount > 1) ? STRING(IDS_TCHISTORY_STATUSBAR_DATAMESSAGES) : STRING(IDS_TCHISTORY_STATUSBAR_DATAMESSAGE)) : STRING(IDS_TCHISTORY_STATUSBAR_NODATAMESSAGE), nCount);
	m_wndStatusBar.SetPaneText(ID_TCHISTORY_STATUSBAR_MESSAGEPANE, szMessage[1]);
}

VOID CTCHistoryWnd::UpdateModePane()
{
	m_wndStatusBar.SetPaneText(ID_TCHISTORY_STATUSBAR_MODEPANE, (GetMode() == DISPLAY_MODE_HISTORY) ? (((GetRetrieveMode() & TCHISTORY_RETRIEVE_AUTOFORWARD) && !(GetRetrieveMode() & TCHISTORY_RETRIEVE_STOPPED)) ? STRING(IDS_TCHISTORY_STATUSBAR_AUTOFORWARDMODE) : (((GetRetrieveMode() & TCHISTORY_RETRIEVE_PSEUDOREALTIME) && !(GetRetrieveMode() & TCHISTORY_RETRIEVE_STOPPED)) ? STRING(IDS_TCHISTORY_STATUSBAR_PSEUDOREALTIMEMODE) : STRING(IDS_TCHISTORY_STATUSBAR_NORMALMODE))) : STRING(IDS_DISPLAY_MODE_REALTIME));
	m_wndToolBar.EnableButton(IDM_TCHISTORYRETRIEVESTOP, (IsRetrievingData() && ((GetRetrieveMode() & TCHISTORY_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & TCHISTORY_RETRIEVE_PSEUDOREALTIME) || HIWORD(IsRetrievingData())) && !(GetRetrieveMode() & TCHISTORY_RETRIEVE_STOPPED)) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_TCHISTORYRETRIEVEFORWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & TCHISTORY_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & TCHISTORY_RETRIEVE_STOPPED))) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_TCHISTORYRETRIEVESTEPFORWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & TCHISTORY_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & TCHISTORY_RETRIEVE_STOPPED))) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_TCHISTORYRETRIEVEPSEUDOREALTIME, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & TCHISTORY_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & TCHISTORY_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

VOID CTCHistoryWnd::UpdateTypePane()
{
	CString  szType;

	switch (HIWORD(GetType()))
	{
	case TCHISTORY_TYPE_GLOBAL:
	{ szType = STRING(IDS_TCHISTORY_STATUSBAR_TYPEGLOBAL);
	break;
	}
	case TCHISTORY_TYPE_NORMAL:
	{ szType = STRING(IDS_TCHISTORY_STATUSBAR_TYPENORMAL);
	break;
	}
	}
	m_wndStatusBar.SetPaneText(ID_TCHISTORY_STATUSBAR_TYPEPANE, szType);
}

VOID CTCHistoryWnd::UpdateContents(BOOL bFilter)
{
	m_wndView.UpdateContent(bFilter);
}

BOOL CTCHistoryWnd::SetPrintJobs(CONST CByteArray &nPrintInfo)
{
	CTCHistoryPrintJobs  pPrintJobs;

	return((pPrintJobs.Unmap(nPrintInfo)) ? SetPrintJobs(pPrintJobs) : FALSE);
}

BOOL CTCHistoryWnd::GetPrintJobs(CByteArray &nPrintInfo) CONST
{
	CTCHistoryPrintJobs  pPrintJobs;

	return((GetPrintJobs(pPrintJobs)) ? pPrintJobs.Map(nPrintInfo) : FALSE);
}

BOOL CTCHistoryWnd::GetPrintProperties(CONST CTCHistoryPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST
{
	return m_wndView.GetPrintProperties(pJobInfo, szColumns, szContents, pAttributes, pTitleFont, pItemsFont, pSymbols, nSymbolIDs);
}

BOOL CTCHistoryWnd::StartPrintJob(CDC &cDC)
{
	DOCINFO  sJobInfo;
	CString  szLayout;
	CString  szJobTitle;

	for (GetLayout(szLayout), sJobInfo.fwType = 0, sJobInfo.cbSize = sizeof(DOCINFO), sJobInfo.lpszDocName = (LPTSTR)EMPTYSTRING, sJobInfo.lpszOutput = (LPCTSTR)NULL, sJobInfo.lpszDatatype = (LPCTSTR)NULL, szJobTitle.Format(STRING(IDS_PRINTJOB_DEFAULTTITLE), (LPCTSTR)GetAppTitle(), (LPCTSTR)GetAccountSpacecraftName(), (LPCTSTR)GetPrintDocSubTitle(szLayout), STRING(IDS_DISPLAY_TITLE_TCHISTORY)); szJobTitle.GetLength() >= 0; )
	{
		sJobInfo.lpszDocName = (LPTSTR)(LPCTSTR)szJobTitle;
		break;
	}
	return((cDC.StartDoc(&sJobInfo) >= 0) ? TRUE : FALSE);
}

BOOL CTCHistoryWnd::PrintJob(CDC &cDC, CONST CTCHistoryPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, LPCTSTR pszLayout, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST CTextViewAttributes &pAttributes, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CONST CPtrArray &pSymbols, CONST CUIntArray &nSymbolIDs)
{
	INT  nID;
	INT  nPos;
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
	UINT  nFormat;
	BOOL  bOverlap;
	BOOL  bOutput;
	CRgn  rgnArea;
	CRect  rArea;
	CRect  rCalc;
	CRect  rClip;
	CRect  rItem;
	CFont  *pOldFont;
	CFont  cFont[TCHISTORY_PRINTFONTS];
	CSize  sizeSymbol;
	CString  szColumn;
	COLORREF  nColor;
	COLORREF  nOldColor;
	CTimeKey  tPrint;
	CPtrArray  pFonts;
	CUIntArray  nTabs;
	TEXTMETRIC  tmFont;
	CStringArray  szColumnsText;
	CTextViewAttribute  *pAttribute;

	for (nPage = nPages = 0; (!nPages || nPage <= nPages) && (nPages > 0 || (nPages = (CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(rArea) != ERROR && rgnArea.CreateRectRgnIndirect(rArea) && CalcPrintDocTitleFont(cDC, rArea, cFont[TCHISTORY_PRINTFONT_TITLE]) && CalcPrintDocSubTitleFont(cDC, rArea, cFont[TCHISTORY_PRINTFONT_SUBTITLE]) && CalcPrintDocDetailsFont(cDC, rArea, cFont[TCHISTORY_PRINTFONT_DETAILS]) && CalcPrintDocCommentsFont(cDC, rArea, cFont[TCHISTORY_PRINTFONT_COMMENTS]) && CalcPrintDocListItemsFonts(cDC, rArea, szColumns, szContents, pTitleFont, pItemsFont, cFont[TCHISTORY_PRINTFONT_LISTITEMSTITLE], cFont[TCHISTORY_PRINTFONT_LISTITEMS]) && CalcPrintDocNoticeFonts(cDC, rArea, cFont[TCHISTORY_PRINTFONT_NOTICE], cFont[TCHISTORY_PRINTFONT_LOGO]) && CalcPrintDocFooterFont(cDC, rArea, cFont[TCHISTORY_PRINTFONT_FOOTER]) && CalcPrintDocTitleWidth(cDC, rArea, szColumns, szContents, &cFont[TCHISTORY_PRINTFONT_LISTITEMSTITLE], &cFont[TCHISTORY_PRINTFONT_LISTITEMS], nTabs) == szColumns.GetSize()) ? nPages : -1) == 0); )
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
					if ((pOldFont = cDC.SelectObject((CFont *)pFonts.GetAt(TCHISTORY_PRINTFONT_LISTITEMS))))
					{
						if ((nSpacing = (cDC.GetTextMetrics(&tmFont)) ? max(tmFont.tmHeight / 10, 1) : -1) >= 0)
						{
							for (rCalc.SetRect(rCalc.left, (!nColumn) ? (rCalc.top + nSpacing) : rCalc.top, rCalc.right, (!nColumn) ? (rCalc.top + nSpacing + tmFont.tmHeight*((rClip.bottom - (rCalc.top + nSpacing)) / tmFont.tmHeight)) : (rCalc.top + tmFont.tmHeight*((rClip.bottom - rCalc.top) / tmFont.tmHeight))), nFormat = DT_LEFT | DT_NOPREFIX | DT_WORDBREAK, nColor = cDC.GetTextColor(); (pAttribute = pAttributes.GetAt(nLine)); )
							{
								pAttribute->GetColumnFormat(nColumn, nFormat);
								pAttribute->GetColumnColor(nColumn, nColor);
								break;
							}
							for (szColumn = (!szColumnsText.GetAt(nColumn).IsEmpty()) ? (((nPos = (szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORY_TITLEITEM_NUMBER)) ? szColumnsText.GetAt(nColumn).Find(CTCHistoryView::GetSymbolDelimiter()) : -1) >= 0) ? (szColumnsText.GetAt(nColumn).Left(nPos)) : (szColumnsText.GetAt(nColumn) + SPACE)) : EMPTYSTRING, nFormat = (nPages > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage >= nFromPage && nPage <= nToPage))) ? nFormat : (nFormat | DT_CALCRECT), nOldColor = cDC.SetTextColor((cDC.GetDeviceCaps(NUMCOLORS) > 2) ? nColor : cDC.GetTextColor()), sizeSymbol.cx = sizeSymbol.cy = tmFont.tmHeight, nHeight[1] = (szColumns.GetAt(nColumn) != STRING(IDS_TCHISTORY_TITLEITEM_FLAGS) && szColumns.GetAt(nColumn) != STRING(IDS_TCHISTORY_TITLEITEM_PTVCHECKS) && szColumns.GetAt(nColumn) != STRING(IDS_TCHISTORY_TITLEITEM_PTVRESULT) && szColumns.GetAt(nColumn) != STRING(IDS_TCHISTORY_TITLEITEM_PEVCHECKS) && szColumns.GetAt(nColumn) != STRING(IDS_TCHISTORY_TITLEITEM_PEVRESULT) && szColumns.GetAt(nColumn) != STRING(IDS_TCHISTORY_TITLEITEM_CEVCHECKS) && szColumns.GetAt(nColumn) != STRING(IDS_TCHISTORY_TITLEITEM_CEVRESULT)) ? cDC.DrawText(szColumn, (rItem = CRect((nColumn > 0) ? (rCalc.left + nTabs.GetAt(nColumn - 1)) : rCalc.left, rCalc.top, rCalc.left + nTabs.GetAt(nColumn), rCalc.bottom)), nFormat) : sizeSymbol.cy; szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORY_TITLEITEM_NUMBER); )
							{
								DrawPrintDocSymbol(cDC, ((nFormat & DT_CALCRECT) != DT_CALCRECT  &&  rItem.top + sizeSymbol.cy <= rCalc.bottom) ? (rItem = CRect(rItem.left + cDC.GetTextExtent(szColumn).cx + sizeSymbol.cx / 2, rItem.top, rItem.left + cDC.GetTextExtent(szColumn).cx + sizeSymbol.cx / 2 + sizeSymbol.cx, rItem.top + sizeSymbol.cy)) : CRect(0, 0, 0, 0), (szColumnsText.GetAt(nColumn).Find(STRING(IDS_TCHISTORY_LIST_ALERT_INFORMATION)) >= 0) ? IDP_TCHISTORYINFORMATION : ((szColumnsText.GetAt(nColumn).Find(STRING(IDS_TCHISTORY_LIST_ALERT_WARNING)) >= 0) ? IDP_TCHISTORYWARNING : ((szColumnsText.GetAt(nColumn).Find(STRING(IDS_TCHISTORY_LIST_ALERT_ERROR)) >= 0) ? IDP_TCHISTORYERROR : -1)), pSymbols, nSymbolIDs);
								break;
							}
							if (szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORY_TITLEITEM_FLAGS))
							{
								for (rItem.SetRect((nColumn > 0) ? (rCalc.left + nTabs.GetAt(nColumn - 1)) : rCalc.left, rCalc.top, (nColumn > 0) ? (rCalc.left + nTabs.GetAt(nColumn - 1) + sizeSymbol.cx) : (rCalc.left + sizeSymbol.cx), rCalc.top + sizeSymbol.cy); (nFormat & DT_CALCRECT) != DT_CALCRECT && rItem.bottom <= rCalc.bottom; )
								{
									DrawPrintDocSymbol(cDC, rItem, (szColumn.Find(STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCK)) >= 0) ? IDP_TCHISTORYINTERLOCK : -1, pSymbols, nSymbolIDs);
									DrawPrintDocSymbol(cDC, rItem + CPoint(3 * rItem.Width() / 2, 0), (szColumn.Find(STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKIDLE)) >= 0) ? IDP_TCHISTORYINTERLOCKIDLE : ((szColumn.Find(STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKPENDING)) >= 0) ? IDP_TCHISTORYINTERLOCKPENDING : ((szColumn.Find(STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKSUCCESS)) >= 0) ? IDP_TCHISTORYINTERLOCKSUCCESS : ((szColumn.Find(STRING(IDS_TCHISTORY_LIST_FLAGS_INTERLOCKFAILURE)) >= 0) ? IDP_TCHISTORYINTERLOCKFAILURE : -1))), pSymbols, nSymbolIDs);
									DrawPrintDocSymbol(cDC, rItem + CPoint(6 * rItem.Width() / 2, 0), (szColumn.Find(STRING(IDS_TCHISTORY_LIST_FLAGS_GROUPED)) >= 0) ? IDP_TCHISTORYGROUPED : -1, pSymbols, nSymbolIDs);
									DrawPrintDocSymbol(cDC, rItem + CPoint(9 * rItem.Width() / 2, 0), (szColumn.Find(STRING(IDS_TCHISTORY_LIST_FLAGS_BLOCKED)) >= 0) ? IDP_TCHISTORYBLOCKED : -1, pSymbols, nSymbolIDs);
									break;
								}
							}
							if (szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORY_TITLEITEM_PTVCHECKS))
							{
								for (nID = (szColumn.IsEmpty()) ? IDP_TCHISTORYCHECKSNONE : -1, nID = (szColumn.Find(STRING(IDS_TCHISTORY_LIST_PTVCHECKS_ON)) >= 0) ? IDP_TCHISTORYCHECKSON : nID, nID = (szColumn.Find(STRING(IDS_TCHISTORY_LIST_PTVCHECKS_OFF)) >= 0) ? IDP_TCHISTORYCHECKSOFF : nID, nID = (szColumn.Find(STRING(IDS_TCHISTORY_LIST_PTVCHECKS_DISABLED)) >= 0) ? IDP_TCHISTORYCHECKSDISABLED : nID, rItem.SetRect((nColumn > 0) ? (rCalc.left + nTabs.GetAt(nColumn - 1)) : rCalc.left, rCalc.top, rCalc.left + nTabs.GetAt(nColumn), rCalc.top + sizeSymbol.cy), rItem.DeflateRect((rItem.Width() - rItem.Height()) / 2, 0); (nFormat & DT_CALCRECT) != DT_CALCRECT && rItem.bottom <= rCalc.bottom; )
								{
									DrawPrintDocSymbol(cDC, rItem, nID, pSymbols, nSymbolIDs);
									break;
								}
							}
							if (szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORY_TITLEITEM_PTVRESULT))
							{
								for (nID = (szColumn.Find(STRING(IDS_TCHISTORY_LIST_PTVRESULT_GO)) >= 0) ? IDP_TCHISTORYPTVGO : -1, nID = (szColumn.Find(STRING(IDS_TCHISTORY_LIST_PTVRESULT_WAIT)) >= 0) ? IDP_TCHISTORYPTVWAIT : nID, nID = (szColumn.Find(STRING(IDS_TCHISTORY_LIST_PTVRESULT_FAIL)) >= 0) ? IDP_TCHISTORYPTVFAIL : nID, rItem.SetRect((nColumn > 0) ? (rCalc.left + nTabs.GetAt(nColumn - 1)) : rCalc.left, rCalc.top, rCalc.left + nTabs.GetAt(nColumn), rCalc.top + sizeSymbol.cy), rItem.DeflateRect((rItem.Width() - rItem.Height()) / 2, 0); (nFormat & DT_CALCRECT) != DT_CALCRECT && rItem.bottom <= rCalc.bottom; )
								{
									DrawPrintDocSymbol(cDC, rItem, nID, pSymbols, nSymbolIDs);
									break;
								}
							}
							if (szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORY_TITLEITEM_PEVCHECKS))
							{
								for (nID = (szColumn.Find(STRING(IDS_TCHISTORY_LIST_PEVCHECKS_NONE)) >= 0) ? IDP_TCHISTORYCHECKSNONE : -1, nID = (szColumn.Find(STRING(IDS_TCHISTORY_LIST_PEVCHECKS_ON)) >= 0) ? IDP_TCHISTORYCHECKSON : nID, nID = (szColumn.Find(STRING(IDS_TCHISTORY_LIST_PEVCHECKS_OFF)) >= 0) ? IDP_TCHISTORYCHECKSOFF : nID, nID = (szColumn.Find(STRING(IDS_TCHISTORY_LIST_PEVCHECKS_DISABLED)) >= 0) ? IDP_TCHISTORYCHECKSDISABLED : nID, rItem.SetRect((nColumn > 0) ? (rCalc.left + nTabs.GetAt(nColumn - 1)) : rCalc.left, rCalc.top, rCalc.left + nTabs.GetAt(nColumn), rCalc.top + sizeSymbol.cy), rItem.DeflateRect((rItem.Width() - rItem.Height()) / 2, 0); (nFormat & DT_CALCRECT) != DT_CALCRECT && rItem.bottom <= rCalc.bottom; )
								{
									DrawPrintDocSymbol(cDC, rItem, nID, pSymbols, nSymbolIDs);
									break;
								}
							}
							if (szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORY_TITLEITEM_PEVRESULT))
							{
								for (nID = (szColumn.Find(STRING(IDS_TCHISTORY_LIST_PEVRESULT_GO)) >= 0) ? IDP_TCHISTORYPEVGO : -1, nID = (szColumn.Find(STRING(IDS_TCHISTORY_LIST_PEVRESULT_NOGO)) >= 0) ? IDP_TCHISTORYPEVNOGO : nID, rItem.SetRect((nColumn > 0) ? (rCalc.left + nTabs.GetAt(nColumn - 1)) : rCalc.left, rCalc.top, rCalc.left + nTabs.GetAt(nColumn), rCalc.top + sizeSymbol.cy), rItem.DeflateRect((rItem.Width() - rItem.Height()) / 2, 0); (nFormat & DT_CALCRECT) != DT_CALCRECT && rItem.bottom <= rCalc.bottom; )
								{
									DrawPrintDocSymbol(cDC, rItem, nID, pSymbols, nSymbolIDs);
									break;
								}
							}
							if (szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORY_TITLEITEM_CEVCHECKS))
							{
								for (nID = (szColumn.Find(STRING(IDS_TCHISTORY_LIST_CEVCHECKS_NONE))) ? IDP_TCHISTORYCHECKSNONE : -1, nID = (szColumn.Find(STRING(IDS_TCHISTORY_LIST_CEVCHECKS_ON)) >= 0) ? IDP_TCHISTORYCHECKSON : nID, nID = (szColumn.Find(STRING(IDS_TCHISTORY_LIST_CEVCHECKS_OFF)) >= 0) ? IDP_TCHISTORYCHECKSOFF : nID, nID = (szColumn.Find(STRING(IDS_TCHISTORY_LIST_CEVCHECKS_DISABLED)) >= 0) ? IDP_TCHISTORYCHECKSDISABLED : nID, rItem.SetRect((nColumn > 0) ? (rCalc.left + nTabs.GetAt(nColumn - 1)) : rCalc.left, rCalc.top, rCalc.left + nTabs.GetAt(nColumn), rCalc.top + sizeSymbol.cy), rItem.DeflateRect((rItem.Width() - rItem.Height()) / 2, 0); (nFormat & DT_CALCRECT) != DT_CALCRECT && rItem.bottom <= rCalc.bottom; )
								{
									DrawPrintDocSymbol(cDC, rItem, nID, pSymbols, nSymbolIDs);
									break;
								}
							}
							if (szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORY_TITLEITEM_CEVRESULT))
							{
								for (nID = (szColumn.Find(STRING(IDS_TCHISTORY_LIST_CEVRESULT_IDLE)) >= 0) ? IDP_TCHISTORYCEVIDLE : -1, nID = (szColumn.Find(STRING(IDS_TCHISTORY_LIST_CEVRESULT_PENDING)) >= 0) ? IDP_TCHISTORYCEVPENDING : nID, nID = (szColumn.Find(STRING(IDS_TCHISTORY_LIST_CEVRESULT_PASSED)) >= 0) ? IDP_TCHISTORYCEVPASSED : nID, nID = (szColumn.Find(STRING(IDS_TCHISTORY_LIST_CEVRESULT_FAILED)) >= 0) ? IDP_TCHISTORYCEVFAILED : nID, nID = (szColumn.Find(STRING(IDS_TCHISTORY_LIST_CEVRESULT_UNKNOWN)) >= 0) ? IDP_TCHISTORYCEVUNKNOWN : nID, nID = (szColumn.Find(STRING(IDS_TCHISTORY_LIST_CEVRESULT_UNVERIFIED)) >= 0) ? IDP_TCHISTORYCEVUNVERIFIED : nID, rItem.SetRect((nColumn > 0) ? (rCalc.left + nTabs.GetAt(nColumn - 1)) : rCalc.left, rCalc.top, rCalc.left + nTabs.GetAt(nColumn), rCalc.top + sizeSymbol.cy), rItem.DeflateRect((rItem.Width() - rItem.Height()) / 2, 0); (nFormat & DT_CALCRECT) != DT_CALCRECT && rItem.bottom <= rCalc.bottom; )
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
					if (nPages > 0 && (nPage == nPages || (nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage  &&  nPage == nToPage)))
					{
						nPages = nPage;
						nLines = nLine;
						nColumns = nColumn;
						break;
					}
					if (bOutput && (!nPages || ((!nPage || (nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage && (nPage < nFromPage || nPage > nToPage)) || cDC.EndPage() >= 0) && ((nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage && (nPage < nFromPage - 1 || nPage >= nToPage)) || (((((nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage) && nPage > 0) || (nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage  &&  nPage != nFromPage - 1)) || StartPrintJob(cDC)) && cDC.StartPage() >= 0)))))
					{
						if (cDC.SelectClipRgn(&rgnArea) != ERROR  &&  DrawPrintDocPage(cDC, pJobInfo, tPrint, pszPrinterName, rtMargin, bMetric, pszLayout, szColumns, pFonts, nTabs, nPages, (nPages > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage >= nFromPage - 1 && nPage < nToPage))) ? (nPage + 1) : 0, rClip) && cDC.IntersectClipRect(rClip) != ERROR)
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
			if (nLine == nLines  &&  !nPages)
			{
				nPages = nPage;
				nPage -= nPage;
				if ((nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || nPages >= nFromPage) && nPages > 0) continue;
				nPages = nPage = 0;
			}
			if (nLine < nLines)
			{
				if (nPages > 0) cDC.AbortDoc();
				nPages = -1;
				break;
			}
		}
		break;
	}
	return(((!nPages || (nPages > 0 && ((nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage  &&  nPage < nFromPage) || (cDC.EndPage() >= 0 && EndPrintJob(cDC))))) && nPage == nPages) ? TRUE : FALSE);
}

BOOL CTCHistoryWnd::EndPrintJob(CDC &cDC)
{
	return((cDC.EndDoc() >= 0) ? TRUE : FALSE);
}

BOOL CTCHistoryWnd::DrawPrintDocPage(CDC &cDC, CONST CTCHistoryPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, LPCTSTR pszLayout, CONST CStringArray &szColumns, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nPages, INT nPage, LPRECT prClip)
{
	return((CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(prClip) != ERROR  &&  DrawPrintDocTitle(cDC, prClip, GetPrintDocTitle(), (CFont *)pFonts.GetAt(TCHISTORY_PRINTFONT_TITLE), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocSubTitle(cDC, prClip, GetPrintDocSubTitle(pszLayout), (CFont *)pFonts.GetAt(TCHISTORY_PRINTFONT_SUBTITLE), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocDetails(cDC, prClip, GetPrintDocDetails(pJobInfo), (CFont *)pFonts.GetAt(TCHISTORY_PRINTFONT_DETAILS), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocComments(cDC, prClip, GetPrintDocComments(pJobInfo), (CFont *)pFonts.GetAt(TCHISTORY_PRINTFONT_COMMENTS), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocListItemsTitle(cDC, prClip, szColumns, (CFont *)pFonts.GetAt(TCHISTORY_PRINTFONT_LISTITEMSTITLE), nTabs, (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocNotice(cDC, prClip, GetPrintDocNotice(), (CFont *)pFonts.GetAt(TCHISTORY_PRINTFONT_NOTICE), (CFont *)pFonts.GetAt(TCHISTORY_PRINTFONT_LOGO), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocFooter(cDC, prClip, GetPrintDocFooter(tTime, pszPrinterName, nPages, nPage), (CFont *)pFonts.GetAt(TCHISTORY_PRINTFONT_FOOTER), (nPage <= 0) ? TRUE : FALSE)) ? TRUE : FALSE);
}

BOOL CTCHistoryWnd::DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc)
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

BOOL CTCHistoryWnd::DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszLayout, CFont *pFont, BOOL bCalc)
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

BOOL CTCHistoryWnd::DrawPrintDocDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszDetails, CFont *pFont, BOOL bCalc)
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

BOOL CTCHistoryWnd::DrawPrintDocComments(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszComments, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
		cDC.DrawText(pszComments, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
		prClip->top += 2 * cDC.GetTextExtent(SPACE).cy;
		prClip->top += rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCHistoryWnd::DrawPrintDocListItemsTitle(CDC &cDC, LPRECT prClip, CONST CStringArray &szColumns, CFont *pFont, CONST CUIntArray &nTabs, BOOL bCalc)
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

BOOL CTCHistoryWnd::DrawPrintDocSymbol(CDC &cDC, LPRECT prClip, UINT nSymbolID, CONST CPtrArray &pSymbols, CONST CUIntArray &nSymbolIDs)
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

BOOL CTCHistoryWnd::DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc)
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

BOOL CTCHistoryWnd::DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc)
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

CString CTCHistoryWnd::GetPrintDocTitle() CONST
{
	CString  szTitle;

	szTitle.Format(STRING(IDS_TCHISTORY_PRINTDOCUMENT_TITLE), (LPCTSTR)GetAccountSpacecraftName());
	return szTitle;
}

CString CTCHistoryWnd::GetPrintDocSubTitle(LPCTSTR pszLayout) CONST
{
	return pszLayout;
}

CString CTCHistoryWnd::GetPrintDocDetails(CONST CTCHistoryPrintJobInfo *pJobInfo) CONST
{
	INT  nDigits;
	UINT  nRange[2];
	CString  szDetails;
	CString  szRange[3];
	CTimeKey  tRange[2][2];
	CStringTools  cStringTools;

	pJobInfo->GetPrintRange(nRange[0], nRange[1]);
	pJobInfo->GetPrintRange(tRange[0][0], tRange[0][1], TRUE);
	pJobInfo->GetPrintRange(tRange[1][0], tRange[1][1], FALSE);
	nDigits = max(cStringTools.ConvertUIntToString(nRange[1]).GetLength(), 3);
	szRange[0].Format(STRING(IDS_TCHISTORY_PRINTDOCUMENT_ITEMRANGESUBTITLE), (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nRange[0], nDigits), (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nRange[1], nDigits));
	szRange[1].Format(STRING(IDS_TCHISTORY_PRINTDOCUMENT_RELEASETIMERANGESUBTITLE), (LPCTSTR)tRange[0][0].FormatGmt(), (LPCTSTR)tRange[0][1].FormatGmt());
	szRange[2].Format(STRING(IDS_TCHISTORY_PRINTDOCUMENT_EXECUTIONTIMERANGESUBTITLE), (LPCTSTR)tRange[1][0].FormatGmt(), (LPCTSTR)tRange[1][1].FormatGmt());
	szDetails = (pJobInfo->GetPrintMode() & (TCHISTORY_PRINT_VERIFICATIONSUCCESS | TCHISTORY_PRINT_VERIFICATIONFAILURE | TCHISTORY_PRINT_ITEMRANGE | TCHISTORY_PRINT_RELEASETIMERANGE | TCHISTORY_PRINT_EXECUTIONTIMERANGE)) ? STRING(IDS_TCHISTORY_PRINTDOCUMENT_SUBTITLE) : EMPTYSTRING;
	szDetails += (pJobInfo->GetPrintMode() & TCHISTORY_PRINT_VERIFICATIONSUCCESS) ? (CString(CR) + CString(EOL) + CString(STRING(IDS_TCHISTORY_PRINTDOCUMENT_VERIFICATIONSUCCESS))) : EMPTYSTRING;
	szDetails += (pJobInfo->GetPrintMode() & TCHISTORY_PRINT_VERIFICATIONFAILURE) ? (CString(CR) + CString(EOL) + CString(STRING(IDS_TCHISTORY_PRINTDOCUMENT_VERIFICATIONFAILURE))) : EMPTYSTRING;
	szDetails += (pJobInfo->GetPrintMode() & TCHISTORY_PRINT_ITEMRANGE) ? (CString(CR) + CString(EOL) + szRange[0]) : EMPTYSTRING;
	szDetails += (pJobInfo->GetPrintMode() & TCHISTORY_PRINT_RELEASETIMERANGE) ? (CString(CR) + CString(EOL) + szRange[1]) : EMPTYSTRING;
	szDetails += (pJobInfo->GetPrintMode() & TCHISTORY_PRINT_EXECUTIONTIMERANGE) ? (CString(CR) + CString(EOL) + szRange[2]) : EMPTYSTRING;
	return szDetails;
}

CString CTCHistoryWnd::GetPrintDocComments(CONST CTCHistoryPrintJobInfo *pJobInfo) CONST
{
	return pJobInfo->GetComments();
}

CString CTCHistoryWnd::GetPrintDocListItemsTitle(CONST CStringArray &szColumns) CONST
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

CString CTCHistoryWnd::GetPrintDocNotice() CONST
{
	CVersionInfo  cVersionInfo;

	return cVersionInfo.QueryComments();
}

CString CTCHistoryWnd::GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST
{
	CString  szFooter;

	szFooter.Format(STRING(IDS_TCHISTORY_PRINTDOCUMENT_FOOTER), (LPCTSTR)tTime.Format(IDS_TIMEKEY_DATEFORMAT), (LPCTSTR)tTime.Format(IDS_TIMEKEY_TIMEFORMAT), pszPrinterName, nPage, nPages);
	return szFooter;
}

INT CTCHistoryWnd::ExtractPrintDocText(LPCTSTR pszText, CStringArray &szColumnsText) CONST
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

BOOL CTCHistoryWnd::CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 48, (INT)((-5.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CTCHistoryWnd::CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 64, (INT)((-4.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CTCHistoryWnd::CalcPrintDocDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 76, (INT)((-3.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CTCHistoryWnd::CalcPrintDocCommentsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 76, (INT)((-3.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CTCHistoryWnd::CalcPrintDocListItemsFonts(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CFont &cTitleFont, CFont &cItemsFont) CONST
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

BOOL CTCHistoryWnd::CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL) && cLogoFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, STRING(IDS_FONTFACE_COMPANYLOGO));
}

BOOL CTCHistoryWnd::CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 80, (INT)((-3.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

INT CTCHistoryWnd::CalcPrintDocTitleWidth(CDC &cDC, LPCTSTR pszColumn, CFont *pTitleFont) CONST
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
INT CTCHistoryWnd::CalcPrintDocTitleWidth(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CFont *pTitleFont, CFont *pItemsFont, CUIntArray &nTabs) CONST
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
		for (nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont), nWidth[1] = CalcPrintDocColumnWidth(cDC, rArea, szColumns.GetAt(nColumn), szLines, pItemsFont); szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORY_TITLEITEM_NUMBER); )
		{
			nWidth[1] += 3 * sizeSymbol.cx / 2;
			break;
		}
		for (; szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORY_TITLEITEM_ARGUMENTS); )
		{
			nWidth[1] = min(3 * nWidth[0], nWidth[1]);
			break;
		}
		for (; szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORY_TITLEITEM_FLAGS); )
		{
			nWidth[1] = (sizeSymbol.cx > 0) ? (11 * sizeSymbol.cx / 2) : nWidth[1];
			break;
		}
		for (; szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORY_TITLEITEM_PTVCHECKS) || szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORY_TITLEITEM_PTVRESULT) || szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORY_TITLEITEM_PEVCHECKS) || szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORY_TITLEITEM_PEVRESULT) || szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORY_TITLEITEM_CEVCHECKS) || szColumns.GetAt(nColumn) == STRING(IDS_TCHISTORY_TITLEITEM_CEVRESULT); )
		{
			nWidth[1] = sizeSymbol.cx;
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

INT CTCHistoryWnd::CalcPrintDocColumnWidth(CDC &cDC, CONST RECT &rArea, LPCTSTR pszColumn, CStringArray &szContents, CFont *pItemsFont) CONST
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
				for (rColumn.SetRect(0, 0, cDC.GetTextExtent((szLine = (!lstrcmp(pszColumn, STRING(IDS_TCHISTORY_TITLEITEM_NUMBER)) && szContents.GetAt(nLine).Left(nPos).Find(CTCHistoryView::GetSymbolDelimiter()) >= 0) ? szContents.GetAt(nLine).Left(nPos).Left(szContents.GetAt(nLine).Left(nPos).Find(CTCHistoryView::GetSymbolDelimiter())) : szContents.GetAt(nLine).Left(nPos))).cx, 0); rColumn.Width() > rArea.right - rArea.left; )
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

BOOL CTCHistoryWnd::CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST
{
	CRect  rClip;

	rClip.SetRect(0, 0, cDC.GetDeviceCaps(HORZRES), cDC.GetDeviceCaps(VERTRES));
	rClip.DeflateRect((bMetric) ? (rtMargin.left*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.left*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.top*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.top*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000, (bMetric) ? (rtMargin.right*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.right*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.bottom*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.bottom*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000);
	return((cDC.IntersectClipRect(rClip) != ERROR) ? TRUE : FALSE);
}

BOOL CTCHistoryWnd::SetLayoutInfo(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo)
{
	CString  szLayout;

	return((GetLayout(szLayout)) ? (m_wndView.SetLayout(szLayout, nColumns, nWidths) && m_wndView.SetTitleFont(pTitleFont) && m_wndView.SetTextFont(pItemsFont) && m_wndView.SetLayoutInfo(pHorzScrollInfo, pVertScrollInfo)) : FALSE);
}

BOOL CTCHistoryWnd::GetLayoutInfo(CUIntArray &nColumns, CUIntArray &nWidths, LOGFONT *pTitleFont, LOGFONT *pItemsFont, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST
{
	CString  szLayout;

	return((m_wndView.GetLayout(szLayout, nColumns, nWidths) && m_wndView.GetTitleFont(pTitleFont) && m_wndView.GetTextFont(pItemsFont) && m_wndView.GetLayoutInfo(pHorzScrollInfo, pVertScrollInfo)) ? TRUE : FALSE);
}

BOOL CTCHistoryWnd::Lock()
{
	return((GetTCService()->Lock() && CDisplayWnd::Lock()) ? TRUE : FALSE);
}

BOOL CTCHistoryWnd::Unlock()
{
	return((CDisplayWnd::Unlock() && GetTCService()->Unlock()) ? TRUE : FALSE);
}

BEGIN_MESSAGE_MAP(CTCHistoryWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CTCHistoryWnd)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_WM_DESTROY()
	ON_COMMAND(IDM_TCHISTORYSETTINGS, OnSettings)
	ON_COMMAND(IDM_TCHISTORYDETAILS, OnDetails)
	ON_COMMAND(IDM_TCHISTORYACKNOWLEDGE, OnAcknowledge)
	ON_COMMAND(IDM_TCHISTORYCOPY, OnCopy)
	ON_COMMAND(IDM_TCHISTORYRETRIEVALS, OnRetrievals)
	ON_COMMAND(IDM_TCHISTORYRETRIEVESTOP, OnRetrieveStop)
	ON_COMMAND(IDM_TCHISTORYRETRIEVEFORWARD, OnRetrieveAutoForward)
	ON_COMMAND(IDM_TCHISTORYRETRIEVESTEPFORWARD, OnRetrieveManualForward)
	ON_COMMAND(IDM_TCHISTORYRETRIEVEPSEUDOREALTIME, OnRetrievePseudoRealtime)
	ON_COMMAND(IDM_TCHISTORYFULLVIEWMODE, OnFullViewMode)
	ON_COMMAND(IDM_TCHISTORYPRINT, OnPrint)
	ON_UPDATE_COMMAND_UI(IDM_TCHISTORYSETTINGS, OnUpdateSettings)
	ON_UPDATE_COMMAND_UI(IDM_TCHISTORYDETAILS, OnUpdateDetails)
	ON_UPDATE_COMMAND_UI(IDM_TCHISTORYACKNOWLEDGE, OnUpdateAcknowledge)
	ON_UPDATE_COMMAND_UI(IDM_TCHISTORYCOPY, OnUpdateCopy)
	ON_UPDATE_COMMAND_UI(IDM_TCHISTORYRETRIEVALS, OnUpdateRetrievals)
	ON_UPDATE_COMMAND_UI(IDM_TCHISTORYRETRIEVESTOP, OnUpdateRetrieveStop)
	ON_UPDATE_COMMAND_UI(IDM_TCHISTORYRETRIEVEFORWARD, OnUpdateRetrieveAutoForward)
	ON_UPDATE_COMMAND_UI(IDM_TCHISTORYRETRIEVESTEPFORWARD, OnUpdateRetrieveManualForward)
	ON_UPDATE_COMMAND_UI(IDM_TCHISTORYRETRIEVEPSEUDOREALTIME, OnUpdateRetrievePseudoRealtime)
	ON_UPDATE_COMMAND_UI(IDM_TCHISTORYFULLVIEWMODE, OnUpdateFullViewMode)
	ON_UPDATE_COMMAND_UI(IDM_TCHISTORYPRINT, OnUpdatePrint)
	ON_UPDATE_COMMAND_UI(ID_TCHISTORY_STATUSBAR_MESSAGEPANE, OnUpdateStatusBarMessagePane)
	ON_UPDATE_COMMAND_UI(ID_TCHISTORY_STATUSBAR_MODEPANE, OnUpdateStatusBarModePane)
	ON_UPDATE_COMMAND_UI(ID_TCHISTORY_STATUSBAR_TYPEPANE, OnUpdateStatusBarTypePane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryWnd message handlers

int CTCHistoryWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDisplayWnd::OnCreate(lpCreateStruct) != -1)
	{
		for (EnableDocking(CBRS_ALIGN_TOP); CreateToolBar() && CreateStatusBar() && CreateView() && LoadAccelTable(MAKEINTRESOURCE(IDR_TCHISTORYFRAME)); )
		{
			UpdateBars();
			return 0;
		}
	}
	return -1;
}

void CTCHistoryWnd::OnGetMinMaxInfo(MINMAXINFO *lpMMI)
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

void CTCHistoryWnd::OnSize(UINT nType, int cx, int cy)
{
	CDisplayWnd::OnSize(nType, cx, cy);
	m_wndView.RecalcLayout();
}

BOOL CTCHistoryWnd::OnEraseBkgnd(CDC *pDC)
{
	if (!IsInitialized())
	{
		m_wndView.UpdateWindow();
		m_wndToolBar.UpdateWindow();
		m_wndStatusBar.UpdateWindow();
	}
	return TRUE;
}

void CTCHistoryWnd::OnSetFocus(CWnd *pOldWnd)
{
	if (IsWindow(pOldWnd->GetSafeHwnd()) && m_wndView.IsChild(pOldWnd))
	{
		GetParent()->SetFocus();
		return;
	}
	if (GetTelecommandCount() > 0)
	{
		m_wndView.SetCurTelecommand(max(GetCurTelecommand(), 0));
		m_wndView.SetFocus();
		return;
	}
	CDisplayWnd::OnSetFocus(pOldWnd);
}

BOOL CTCHistoryWnd::OnCloseOpenDialog(UINT nCode)
{
	UINT  nMode;
	UINT  nSort;
	UINT  nSpeed;
	UINT  nCount[2];
	BOOL  bToolTips;
	LOGFONT  fntTitle;
	LOGFONT  fntItems;
	CString  szName;
	CString  szLayout;
	CString  szComputer;
	CString  szFileName;
	CString  szSequence;
	COLORREF  nColor;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CUIntArray  nTitleItems;
	CTCHistoryPrintJobs  pJobs;

	if (nCode == IDOK)
	{
		for (SetMode(m_dlgOpen.GetMode()), SetType(MAKELONG(DISPLAY_TYPE_TCHISTORY, m_dlgOpen.GetType())), SetWindowText(m_dlgOpen.GetTitle()); m_dlgOpen.IsLayoutModified(); )
		{
			m_dlgOpen.GetLayout(szLayout, nTitleItems);
			m_dlgOpen.GetLayoutListTitleFont(&fntTitle);
			m_dlgOpen.GetLayoutListItemsFont(&fntItems);
			m_dlgOpen.GetLayoutToolTipMode(bToolTips);
			m_dlgOpen.GetLayoutGridBackgroundColor(nColor);
			if (!SetLayout(szLayout, nTitleItems) || !SetListTitleFont(&fntTitle) || !SetListItemsFont(&fntItems) || !SetGridBackgroundColor(nColor) || !EnableToolTipMode(bToolTips)) return FALSE;
			break;
		}
		if (!m_dlgOpen.IsLayoutModified())
		{
			m_dlgOpen.GetLayout(szLayout);
			if (!SetLayout(szLayout)) return FALSE;
		}
		if (m_dlgOpen.IsFilteringModified())
		{
			m_dlgOpen.GetFilterMode(nMode);
			m_dlgOpen.GetFilterComputer(szComputer);
			m_dlgOpen.GetFilterTelecommandName(szName);
			m_dlgOpen.GetFilterTelecommandSequence(szSequence);
			m_dlgOpen.GetFilterLimitation(nCount[0]);
			m_dlgOpen.GetFilterAutoload(nCount[1]);
			m_dlgOpen.GetFilterSortMode(nSort);
			if (!SetFilterMode(nMode) || !SetFilterComputer(szComputer) || !SetFilterTelecommandName(szName) || !SetFilterTelecommandSequence(szSequence) || !SetFilterLimitation(nCount[0]) || !SetFilterAutoload(nCount[1]) || !SetFilterSortMode(nSort)) return FALSE;
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
			SetRetrieveStartTime(tStartTime);
			SetRetrieveStopTime(tStopTime);
			UpdateAllPanes();
			return Start();
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CTCHistoryWnd::OnCloseSettingsDialog(UINT nCode)
{
	UINT  nMode;
	UINT  nSortMode;
	UINT  nCount[2];
	BOOL  bToolTips;
	LOGFONT  fntTitle;
	LOGFONT  fntItems;
	CString  szName;
	CString  szLayout;
	CString  szComputer;
	CString  szFileName;
	CString  szSequence;
	COLORREF  nColor;
	CUIntArray  nColumns;
	CTCHistoryPrintJobs  pJobs;

	if (nCode == IDOK)
	{
		for (GetLayout(szLayout); m_dlgSettings.IsLayoutModified(); )
		{
			m_dlgSettings.GetLayoutColumns(nColumns);
			m_dlgSettings.GetLayoutTitleFont(&fntTitle);
			m_dlgSettings.GetLayoutItemsFont(&fntItems);
			m_dlgSettings.GetLayoutToolTipMode(bToolTips);
			m_dlgSettings.GetLayoutGridBackgroundColor(nColor);
			if (!SetLayout(szLayout, nColumns) || !SetListTitleFont(&fntTitle) || !SetListItemsFont(&fntItems) || !SetGridBackgroundColor(nColor) || !EnableToolTipMode(bToolTips)) return FALSE;
			break;
		}
		if (m_dlgSettings.IsFilteringModified())
		{
			m_dlgSettings.GetFilterMode(nMode);
			m_dlgSettings.GetFilterComputer(szComputer);
			m_dlgSettings.GetFilterTelecommandName(szName);
			m_dlgSettings.GetFilterTelecommandSequence(szSequence);
			m_dlgSettings.GetFilterLimitation(nCount[0]);
			m_dlgSettings.GetFilterAutoload(nCount[1]);
			m_dlgSettings.GetFilterSortMode(nSortMode);
			if (!SetFilterMode(nMode) || !SetFilterComputer(szComputer) || !SetFilterTelecommandName(szName) || !SetFilterTelecommandSequence(szSequence) || !SetFilterLimitation(nCount[0]) || !SetFilterAutoload(nCount[1]) || !SetFilterSortMode(nSortMode)) return FALSE;
		}
		if (m_dlgSettings.IsRetrievingModified())
		{
			m_dlgSettings.GetRetrieveMode(nMode);
			m_dlgSettings.GetRetrieveFileName(szFileName);
			if (!SetRetrieveMode(nMode) || !SetRetrieveFileName(szFileName)) return FALSE;
		}
		if (m_dlgSettings.IsPrintingModified())
		{
			m_dlgSettings.GetPrintJobs(pJobs);
			if (!SetPrintJobs(pJobs)) return FALSE;
		}
		UpdateContents(m_dlgSettings.IsFilteringModified());
		UpdateAllPanes();
	}
	return TRUE;
}

BOOL CTCHistoryWnd::OnCloseRetrieveDialog(UINT nCode)
{
	UINT  nMode[2];
	UINT  nSpeed[2];
	CTimeKey  tStartTime[2];
	CTimeKey  tStopTime[2];

	if (nCode == IDOK)
	{
		nMode[0] = GetRetrieveMode();
		nSpeed[0] = GetRetrieveSpeed();
		tStartTime[0] = GetRetrieveStartTime();
		tStopTime[0] = GetRetrieveStopTime();
		for (m_dlgRetrievals.GetMode(nMode[1]); nMode[1] & ~(TCHISTORY_RETRIEVE_BYRELEASETIME | TCHISTORY_RETRIEVE_BYEXECUTIONTIME); )
		{
			m_dlgRetrievals.GetSpeed(nSpeed[1]);
			m_dlgRetrievals.GetStartTime(tStartTime[1]);
			m_dlgRetrievals.GetStopTime(tStopTime[1]);
			if (SetMode(DISPLAY_MODE_HISTORY) && (!IsRetrievingData() || StopRetrieveData()) && StartRetrieveData(nMode[1], nSpeed[1], tStartTime[1], tStopTime[1]))
			{
				UpdateAllPanes();
				return TRUE;
			}
			SetMode(((nMode[0] & ~(TCHISTORY_RETRIEVE_BYRELEASETIME | TCHISTORY_RETRIEVE_BYEXECUTIONTIME)) == 0) ? DISPLAY_MODE_REALTIME : DISPLAY_MODE_HISTORY);
			SetRetrieveMode(nMode[0]);
			SetRetrieveSpeed(nSpeed[0]);
			SetRetrieveStartTime(tStartTime[0]);
			SetRetrieveStopTime(tStopTime[0]);
			UpdateAllPanes();
			return FALSE;
		}
		StopRetrieveData();
		SetRetrieveMode();
		SetRetrieveSpeed();
		SetRetrieveStartTime();
		SetRetrieveStopTime();
		SetMode(DISPLAY_MODE_REALTIME);
		ProcessRealtimeData();
		UpdateAllPanes();
	}
	return TRUE;
}

void CTCHistoryWnd::OnSettings()
{
	ReportEvent((m_dlgSettings.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CTCHistoryWnd::OnDetails()
{
	CHourglassCursor  cCursor;

	ShowTelecommandProperties();
}

void CTCHistoryWnd::OnAcknowledge()
{
	CHourglassCursor  cCursor;

	DoAcknowledgeTelecommand();
}

void CTCHistoryWnd::OnCopy()
{
	CHourglassCursor  cCursor;

	DoCopyTelecommand();
}

void CTCHistoryWnd::OnRetrievals()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgRetrievals.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CTCHistoryWnd::OnRetrieveStop()
{
	RetrieveMoreData(TCHISTORY_RETRIEVE_STOPPED);
}

void CTCHistoryWnd::OnRetrieveAutoForward()
{
	RetrieveMoreData(TCHISTORY_RETRIEVE_AUTOFORWARD);
}

void CTCHistoryWnd::OnRetrieveManualForward()
{
	RetrieveMoreData(TCHISTORY_RETRIEVE_MANUALFORWARD);
}

void CTCHistoryWnd::OnRetrievePseudoRealtime()
{
	RetrieveMoreData(TCHISTORY_RETRIEVE_PSEUDOREALTIME);
}

void CTCHistoryWnd::OnFullViewMode()
{
	CHourglassCursor  cCursor;

	EnableFullViewMode(!IsFullViewModeEnabled());
}

void CTCHistoryWnd::OnPrint()
{
	CHourglassCursor  cCursor;

	ReportEvent((!Print()) ? SYSTEM_WARNING_DISPLAY_PRINT_FAILURE : SYSTEM_NOERROR);
}

void CTCHistoryWnd::OnDestroy()
{
	CHourglassCursor  cCursor;

	Stop();
	CDisplayWnd::OnDestroy();
}

void CTCHistoryWnd::OnUpdateSettings(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized());
	pCmdUI->SetCheck(IsWindow(m_dlgSettings.GetSafeHwnd()));
}

void CTCHistoryWnd::OnUpdateDetails(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized() && CanShowTelecommandProperties());
	pCmdUI->SetCheck(IsShowingTelecommandProperties());
}

void CTCHistoryWnd::OnUpdateAcknowledge(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized() && CanAcknowledgeTelecommand() && CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE));
}

void CTCHistoryWnd::OnUpdateCopy(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized() && CanCopyTelecommand() && CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE));
}

void CTCHistoryWnd::OnUpdateRetrievals(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && GetScope() == DISPLAY_SCOPE_LOCAL) ? TRUE : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgRetrievals.GetSafeHwnd()));
}

void CTCHistoryWnd::OnUpdateRetrieveStop(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && ((GetRetrieveMode() & TCHISTORY_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & TCHISTORY_RETRIEVE_PSEUDOREALTIME) || HIWORD(IsRetrievingData())) && !(GetRetrieveMode() & TCHISTORY_RETRIEVE_STOPPED)) ? TRUE : FALSE);
}

void CTCHistoryWnd::OnUpdateRetrieveAutoForward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & TCHISTORY_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & TCHISTORY_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CTCHistoryWnd::OnUpdateRetrieveManualForward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & TCHISTORY_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & TCHISTORY_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CTCHistoryWnd::OnUpdateRetrievePseudoRealtime(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & TCHISTORY_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & TCHISTORY_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CTCHistoryWnd::OnUpdateFullViewMode(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized());
	pCmdUI->SetCheck(IsFullViewModeEnabled());
}

void CTCHistoryWnd::OnUpdatePrint(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && IsDefaultPrinterAvailable() && CanPrint()) ? TRUE : FALSE);
}

void CTCHistoryWnd::OnUpdateStatusBarMessagePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CTCHistoryWnd::OnUpdateStatusBarModePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CTCHistoryWnd::OnUpdateStatusBarTypePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}
