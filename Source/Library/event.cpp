// EVENT.CPP : Event Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the event related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1993/10/24 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CEventObject

CEventObject::CEventObject() : CObject()
{
	m_nCategory = EVENT_CATEGORY_NONE;
	m_szType.Empty();
	m_szUser.Empty();
	m_szSound.Empty();
	m_szAdapter.Empty();
	m_szSpeaker.Empty();
	m_szMessage.Empty();
	m_szComments.Empty();
	m_szProcedure.Empty();
	m_szNotification.Empty();
	m_szNotificationRecipients.RemoveAll();
	m_nNotificationType = NOTIFICATIONINFO_TYPE_NONE;
	m_nAudition = AUDIO_NO_SOUND;
	m_nAuditColor = VGA_COLOR_BLACK;
	m_tAuditStartTime = 0;
	m_tAuditStopTime = 0;
	m_tAuditPeriod = 0;
	m_nAuditCycles = 0;
	m_dwAuditVoice = 0;
	m_dwAudioPitch = 0;
	m_dwAudioVolume = 0;
	m_dwAudioPlayback = 0;
	m_dwAudioFrequency = 0;
	m_bAcknowledged = TRUE;
	m_bVisible = TRUE;
}
CEventObject::CEventObject(CONST EVENT_DESCRIPTOR sEvent) : CObject()
{
	LPTSTR  pszMessage;

	for (m_nCategory = EVENT_CATEGORY_NONE, m_szType.Empty(), m_szUser.Empty(), m_szSound.Empty(), m_szAdapter.Empty(), m_szSpeaker.Empty(), m_szMessage.Empty(), m_szComments.Empty(), m_szProcedure.Empty(), m_szNotification.Empty(), m_szNotificationRecipients.RemoveAll(), m_nNotificationType = NOTIFICATIONINFO_TYPE_NONE, m_nAudition = AUDIO_NO_SOUND, m_nAuditColor = VGA_COLOR_BLACK, m_tAuditStartTime = m_tAuditStopTime = 0, m_tAuditPeriod = 0, m_nAuditCycles = 0, m_dwAuditVoice = 0, m_dwAudioPitch = 0, m_dwAudioVolume = 0, m_dwAudioPlayback = 0, m_dwAudioFrequency = 0, m_bAcknowledged = TRUE, m_bVisible = TRUE; (sEvent.Opcode == SATVIEW_EVENTLOGPROVIDER_OPCODE_SYSTEM || sEvent.Opcode == SATVIEW_EVENTLOGPROVIDER_OPCODE_SPACECRAFT || sEvent.Opcode == SATVIEW_EVENTLOGPROVIDER_OPCODE_USER) && (sEvent.Level == (UCHAR)MSG_level_Critical || sEvent.Level == (UCHAR)MSG_level_Error || sEvent.Level == (UCHAR)MSG_level_Warning || sEvent.Level == (UCHAR)MSG_level_Informational); )
	{
		for (m_nCategory = (sEvent.Opcode == SATVIEW_EVENTLOGPROVIDER_OPCODE_SYSTEM) ? EVENT_CATEGORY_SYSTEM : ((sEvent.Opcode == SATVIEW_EVENTLOGPROVIDER_OPCODE_SPACECRAFT) ? EVENT_CATEGORY_SPACECRAFT : EVENT_CATEGORY_USER), m_szType = (sEvent.Level == (UCHAR)MSG_level_Critical || sEvent.Level == (UCHAR)MSG_level_Error) ? STRING(IDS_EVENTTYPE_ERROR) : ((sEvent.Level == (UCHAR)MSG_level_Warning) ? STRING(IDS_EVENTTYPE_WARNING) : STRING(IDS_EVENTTYPE_INFORMATIONAL)); FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_MAX_WIDTH_MASK, (LPCVOID)GetLibraryModuleInstance(), sEvent.Id, GetLanguageID(), (LPTSTR)&pszMessage, 0, (va_list *)NULL) > 0; )
		{
			m_szMessage = pszMessage;
			LocalFree(pszMessage);
			break;
		}
		break;
	}
}

VOID CEventObject::SetCategory(UINT nCategory)
{
	m_nCategory = nCategory;
}

UINT CEventObject::GetCategory() CONST
{
	return m_nCategory;
}

VOID CEventObject::SetType(LPCTSTR pszType)
{
	LPCTSTR  pPos;

	m_szType = ((pPos = _tcschr(m_szType, TAB))) ? (CString(pszType) + pPos) : (pszType + CString(TAB));
}

CString CEventObject::GetType() CONST
{
	LPCTSTR  pPos;

	return(((pPos = _tcschr(m_szType, TAB))) ? m_szType.Left(m_szType.GetLength() - lstrlen(pPos)) : m_szType);
}

VOID CEventObject::SetSubtype(LPCTSTR pszSubtype)
{
	LPCTSTR  pPos;

	m_szType = ((pPos = _tcschr(m_szType, TAB))) ? (m_szType.Left(m_szType.GetLength() - lstrlen(pPos) + 1) + pszSubtype) : (CString(TAB) + pszSubtype);
}

CString CEventObject::GetSubtype() CONST
{
	LPCTSTR  pPos;

	return(((pPos = _tcschr(m_szType, TAB))) ? m_szType.Right(lstrlen(pPos) - 1) : EMPTYSTRING);
}

VOID CEventObject::SetUser(LPCTSTR pszUser)
{
	m_szUser = pszUser;
}

CString CEventObject::GetUser() CONST
{
	return m_szUser;
}

VOID CEventObject::SetMessage(LPCTSTR pszMessage)
{
	m_szMessage = pszMessage;
}

CString CEventObject::GetMessage() CONST
{
	return m_szMessage;
}

VOID CEventObject::SetComments(LPCTSTR pszComments)
{
	m_szComments = pszComments;
}

CString CEventObject::GetComments() CONST
{
	return m_szComments;
}

VOID CEventObject::SetProcedure(LPCTSTR pszProcedure)
{
	m_szProcedure = pszProcedure;
}

CString CEventObject::GetProcedure() CONST
{
	return m_szProcedure;
}

VOID CEventObject::SetNotification(UINT nType, LPCTSTR pszNotification)
{
	m_nNotificationType = nType;
	m_szNotification = pszNotification;
}

BOOL CEventObject::GetNotification(UINT &nType, CString &szNotification) CONST
{
	nType = m_nNotificationType;
	szNotification = m_szNotification;
	return((nType != NOTIFICATIONINFO_TYPE_NONE) ? TRUE : FALSE);
}

VOID CEventObject::SetNotificationRecipients(CONST CStringArray &szRecipients)
{
	m_szNotificationRecipients.Copy(szRecipients);
}

INT CEventObject::GetNotificationRecipients(CStringArray &szRecipients) CONST
{
	szRecipients.Copy(m_szNotificationRecipients);
	return((INT)szRecipients.GetSize());
}

VOID CEventObject::SetAudioInfo(LPCTSTR pszAdapter, DWORD dwVolume, DWORD dwPitch, DWORD dwPlayback)
{
	m_szAdapter = pszAdapter;
	m_dwAudioPitch = dwPitch;
	m_dwAudioVolume = dwVolume;
	m_dwAudioPlayback = dwPlayback;
}

BOOL CEventObject::GetAudioInfo(CString &szAdapter, DWORD &dwVolume, DWORD &dwPitch, DWORD &dwPlayback) CONST
{
	szAdapter = m_szAdapter;
	dwPitch = m_dwAudioPitch;
	dwVolume = m_dwAudioVolume;
	dwPlayback = m_dwAudioPlayback;
	return !szAdapter.IsEmpty();
}

VOID CEventObject::SetAudition(UINT nAudition)
{
	if ((m_nAudition = nAudition) == AUDIO_NO_SOUND)
	{
		m_szSound.Empty();
		m_szSpeaker.Empty();
		m_dwAudioFrequency = 0;
		m_dwAuditVoice = 0;
	}
}

UINT CEventObject::GetAudition() CONST
{
	return m_nAudition;
}

VOID CEventObject::SetAuditBeep(DWORD dwFrequency)
{
	m_dwAudioFrequency = dwFrequency;
}

DWORD CEventObject::GetAuditBeep() CONST
{
	return((m_nAudition & AUDIO_BEEP_SOUND) ? m_dwAudioFrequency : 0);
}

VOID CEventObject::SetAuditWave(LPCTSTR pszSound)
{
	m_szSound = pszSound;
}

CString CEventObject::GetAuditWave() CONST
{
	return((m_nAudition & AUDIO_WAVE_SOUND) ? m_szSound : EMPTYSTRING);
}

VOID CEventObject::SetAuditVoice(LPCTSTR pszSpeaker, WORD wGender, WORD wAge)
{
	m_szSpeaker = pszSpeaker;
	m_dwAuditVoice = MAKELONG(wGender, wAge);
}

BOOL CEventObject::GetAuditVoice(CString &szSpeaker, WORD &wGender, WORD &wAge) CONST
{
	szSpeaker = m_szSpeaker;
	wAge = HIWORD(m_dwAuditVoice);
	wGender = LOWORD(m_dwAuditVoice);
	return((m_nAudition & AUDIO_VOICE_SOUND) ? TRUE : FALSE);
}

VOID CEventObject::SetAuditColor(COLORREF nColor)
{
	m_nAuditColor = nColor;
}

COLORREF CEventObject::GetAuditColor() CONST
{
	return m_nAuditColor;
}

VOID CEventObject::SetAuditTime(CONST CTimeKey &tTime)
{
	m_tAuditStartTime = tTime;
}

CTimeKey CEventObject::GetAuditTime() CONST
{
	return m_tAuditStartTime;
}

VOID CEventObject::SetAuditPeriod(CONST CTimeSpan &tPeriod, CONST CTimeKey &tTime, UINT nCycles)
{
	m_tAuditPeriod = tPeriod;
	m_tAuditStopTime = tTime;
	m_nAuditCycles = nCycles;
}

BOOL CEventObject::GetAuditPeriod(CTimeSpan &tPeriod, CTimeKey &tTime, UINT &nCycles) CONST
{
	tPeriod = m_tAuditPeriod;
	tTime = m_tAuditStopTime;
	nCycles = m_nAuditCycles;
	return((tPeriod > 0) ? TRUE : FALSE);
}

VOID CEventObject::Acknowledge(BOOL bAcknowledge)
{
	m_bAcknowledged = bAcknowledge;
}

BOOL CEventObject::IsAcknowledged() CONST
{
	return m_bAcknowledged;
}

VOID CEventObject::Show(BOOL bVisible)
{
	m_bVisible = bVisible;
}

BOOL CEventObject::IsVisible() CONST
{
	return m_bVisible;
}

VOID CEventObject::Copy(CONST CEventObject *pEvent)
{
	m_szType = pEvent->m_szType;
	m_szUser = pEvent->m_szUser;
	m_szSound = pEvent->m_szSound;
	m_szAdapter = pEvent->m_szAdapter;
	m_szSpeaker = pEvent->m_szSpeaker;
	m_szMessage = pEvent->m_szMessage;
	m_szComments = pEvent->m_szComments;
	m_szProcedure = pEvent->m_szProcedure;
	m_szNotification = pEvent->m_szNotification;
	m_szNotificationRecipients.Copy(pEvent->m_szNotificationRecipients);
	m_nCategory = pEvent->m_nCategory;
	m_nAudition = pEvent->m_nAudition;
	m_nAuditCycles = pEvent->m_nAuditCycles;
	m_dwAuditVoice = pEvent->m_dwAuditVoice;
	m_dwAudioPitch = pEvent->m_dwAudioPitch;
	m_dwAudioVolume = pEvent->m_dwAudioVolume;
	m_dwAudioPlayback = pEvent->m_dwAudioPlayback;
	m_dwAudioFrequency = pEvent->m_dwAudioFrequency;
	m_nNotificationType = pEvent->m_nNotificationType;
	m_tAuditStartTime = pEvent->m_tAuditStartTime;
	m_tAuditStopTime = pEvent->m_tAuditStopTime;
	m_tAuditPeriod = pEvent->m_tAuditPeriod;
	m_nAuditColor = pEvent->m_nAuditColor;
	m_bAcknowledged = pEvent->m_bAcknowledged;
	m_bVisible = pEvent->m_bVisible;
}

BOOL CEventObject::Compare(CONST CEventObject *pEvent) CONST
{
	INT  nRecipient[2];
	INT  nRecipients[2];

	for (nRecipient[0] = 0, nRecipients[0] = (pEvent->m_szType == m_szType && pEvent->m_szUser == m_szUser && pEvent->m_szMessage == m_szMessage && pEvent->m_szComments == m_szComments && pEvent->m_szProcedure == m_szProcedure && pEvent->m_szNotification == m_szNotification && pEvent->m_nNotificationType == m_nNotificationType && pEvent->m_nCategory == m_nCategory && pEvent->m_nAudition == m_nAudition && pEvent->m_tAuditStartTime == m_tAuditStartTime && pEvent->m_tAuditStopTime == m_tAuditStopTime && pEvent->m_tAuditPeriod == m_tAuditPeriod && pEvent->m_nAuditCycles == m_nAuditCycles && ((m_nAudition & AUDIO_NO_SOUND) || (m_nAudition & AUDIO_STANDARD_SOUND) || ((m_nAudition & AUDIO_BEEP_SOUND) && pEvent->m_dwAudioFrequency == m_dwAudioFrequency) || ((m_nAudition & AUDIO_WAVE_SOUND) && pEvent->m_szSound == m_szSound) || ((m_nAudition & AUDIO_VOICE_SOUND) && pEvent->m_szSpeaker == m_szSpeaker && pEvent->m_dwAuditVoice == m_dwAuditVoice)) && ((m_nAudition & AUDIO_NO_SOUND) || (m_nAudition & AUDIO_STANDARD_SOUND) || (pEvent->m_szAdapter == m_szAdapter && pEvent->m_dwAudioVolume == m_dwAudioVolume && pEvent->m_dwAudioPitch == m_dwAudioPitch && pEvent->m_dwAudioPlayback == m_dwAudioPlayback)) && pEvent->m_nAuditColor == m_nAuditColor && pEvent->m_szNotificationRecipients.GetSize() == m_szNotificationRecipients.GetSize() && pEvent->m_bAcknowledged == m_bAcknowledged) ? (INT)m_szNotificationRecipients.GetSize() : -1; nRecipient[0] < nRecipients[0]; nRecipient[0]++)
	{
		for (nRecipient[1] = 0, nRecipients[1] = (INT)pEvent->m_szNotificationRecipients.GetSize(); nRecipient[1] < nRecipients[0]; nRecipient[1]++)
		{
			if (!pEvent->m_szNotificationRecipients.GetAt(nRecipient[1]).CompareNoCase(m_szNotificationRecipients.GetAt(nRecipient[0]))) break;
			continue;
		}
		if (nRecipient[1] == nRecipients[1]) break;
	}
	return((nRecipient[0] == nRecipients[0]) ? TRUE : FALSE);
}

BOOL CEventObject::Map(CByteArray &nInfo) CONST
{
	DATA  sData;
	INT  cbData;
	INT  nRecipient;
	INT  nRecipients;
	CByteArray  nRecipientData;

	sData.cbType = (m_szType.GetLength() + 1)*sizeof(TCHAR);
	sData.cbUser = (m_szUser.GetLength() + 1)*sizeof(TCHAR);
	sData.cbSound = (m_szSound.GetLength() + 1)*sizeof(TCHAR);
	sData.cbAdapter = (m_szAdapter.GetLength() + 1)*sizeof(TCHAR);
	sData.cbSpeaker = (m_szSpeaker.GetLength() + 1)*sizeof(TCHAR);
	sData.cbMessage = (m_szMessage.GetLength() + 1)*sizeof(TCHAR);
	sData.cbComments = (m_szComments.GetLength() + 1)*sizeof(TCHAR);
	sData.cbProcedure = (m_szProcedure.GetLength() + 1)*sizeof(TCHAR);
	sData.cbNotification = (m_szNotification.GetLength() + 1)*sizeof(TCHAR);
	for (nRecipient = 0, nRecipients = (INT)m_szNotificationRecipients.GetSize(), sData.cbNotificationRecipients = 0; nRecipient < nRecipients; nRecipient++, sData.cbNotificationRecipients += cbData)
	{
		nRecipientData.SetSize(sData.cbNotificationRecipients + (cbData = (m_szNotificationRecipients.GetAt(nRecipient).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nRecipientData.GetData() + sData.cbNotificationRecipients, (LPCTSTR)m_szNotificationRecipients.GetAt(nRecipient), cbData);
	}
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbType + sData.cbUser + sData.cbSound + sData.cbAdapter + sData.cbSpeaker + sData.cbMessage + sData.cbComments + sData.cbProcedure + sData.cbNotification + sData.cbNotificationRecipients)), sData.nCategory = m_nCategory, sData.nAudition = m_nAudition, sData.tAuditStartTime = m_tAuditStartTime.GetTime(), sData.tAuditStopTime = m_tAuditStopTime.GetTime(), sData.tAuditPeriod = m_tAuditPeriod.GetTotalSeconds(), sData.nAuditColor = m_nAuditColor, sData.nAuditCycles = m_nAuditCycles, sData.dwAuditVoice = m_dwAuditVoice, sData.dwAudioPitch = m_dwAudioPitch, sData.dwAudioVolume = m_dwAudioVolume, sData.dwAudioPlayback = m_dwAudioPlayback, sData.dwAudioFrequency = m_dwAudioFrequency, sData.nNotificationType = m_nNotificationType, sData.bAcknowledged = m_bAcknowledged; nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szType, sData.cbType);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbType), (LPCTSTR)m_szUser, sData.cbUser);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbUser), (LPCTSTR)m_szSound, sData.cbSound);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbSound), (LPCTSTR)m_szAdapter, sData.cbAdapter);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbAdapter), (LPCTSTR)m_szSpeaker, sData.cbSpeaker);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbSpeaker), (LPCTSTR)m_szMessage, sData.cbMessage);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbMessage), (LPCTSTR)m_szComments, sData.cbComments);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbComments), (LPCTSTR)m_szProcedure, sData.cbProcedure);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbProcedure), (LPCTSTR)m_szNotification, sData.cbNotification);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbNotification), nRecipientData.GetData(), sData.cbNotificationRecipients);
		return TRUE;
	}
	return FALSE;
}

BOOL CEventObject::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;
	INT  cbData;
	INT  cbRecipient;
	INT  cbRecipients;
	CByteArray  nRecipientData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbType + sData.cbUser + sData.cbSound + sData.cbAdapter + sData.cbSpeaker + sData.cbMessage + sData.cbComments + sData.cbProcedure + sData.cbNotification + sData.cbNotificationRecipients && sData.cbType > 0 && sData.cbUser > 0 && sData.cbSound > 0 && sData.cbAdapter > 0 && sData.cbSpeaker > 0 && sData.cbMessage > 0 && sData.cbComments > 0 && sData.cbProcedure > 0 && sData.cbNotification > 0 && sData.cbNotificationRecipients >= 0; )
	{
		CopyMemory(m_szType.GetBufferSetLength(STRINGCHARS(sData.cbType)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbType));
		CopyMemory(m_szUser.GetBufferSetLength(STRINGCHARS(sData.cbUser)), nInfo.GetData() + (cbData = cbData + sData.cbType), STRINGBYTES(sData.cbUser));
		CopyMemory(m_szSound.GetBufferSetLength(STRINGCHARS(sData.cbSound)), nInfo.GetData() + (cbData = cbData + sData.cbUser), STRINGBYTES(sData.cbSound));
		CopyMemory(m_szAdapter.GetBufferSetLength(STRINGCHARS(sData.cbAdapter)), nInfo.GetData() + (cbData = cbData + sData.cbSound), STRINGBYTES(sData.cbAdapter));
		CopyMemory(m_szSpeaker.GetBufferSetLength(STRINGCHARS(sData.cbSpeaker)), nInfo.GetData() + (cbData = cbData + sData.cbAdapter), STRINGBYTES(sData.cbSpeaker));
		CopyMemory(m_szMessage.GetBufferSetLength(STRINGCHARS(sData.cbMessage)), nInfo.GetData() + (cbData = cbData + sData.cbSpeaker), STRINGBYTES(sData.cbMessage));
		CopyMemory(m_szComments.GetBufferSetLength(STRINGCHARS(sData.cbComments)), nInfo.GetData() + (cbData = cbData + sData.cbMessage), STRINGBYTES(sData.cbComments));
		CopyMemory(m_szProcedure.GetBufferSetLength(STRINGCHARS(sData.cbProcedure)), nInfo.GetData() + (cbData = cbData + sData.cbComments), STRINGBYTES(sData.cbProcedure));
		CopyMemory(m_szNotification.GetBufferSetLength(STRINGCHARS(sData.cbNotification)), nInfo.GetData() + (cbData = cbData + sData.cbProcedure), STRINGBYTES(sData.cbNotification));
		for (nRecipientData.SetSize(sData.cbNotificationRecipients), CopyMemory(nRecipientData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbNotification), sData.cbNotificationRecipients), m_nCategory = sData.nCategory, m_nAudition = sData.nAudition, m_tAuditStartTime = sData.tAuditStartTime, m_tAuditStopTime = sData.tAuditStopTime, m_tAuditPeriod = sData.tAuditPeriod, m_nAuditColor = sData.nAuditColor, m_nAuditCycles = sData.nAuditCycles, m_dwAuditVoice = sData.dwAuditVoice, m_dwAudioPitch = sData.dwAudioPitch, m_dwAudioVolume = sData.dwAudioVolume, m_dwAudioPlayback = sData.dwAudioPlayback, m_dwAudioFrequency = sData.dwAudioFrequency, m_nNotificationType = sData.nNotificationType, m_bAcknowledged = sData.bAcknowledged, m_szType.ReleaseBuffer(), m_szUser.ReleaseBuffer(), m_szSound.ReleaseBuffer(), m_szAdapter.ReleaseBuffer(), m_szSpeaker.ReleaseBuffer(), m_szMessage.ReleaseBuffer(), m_szComments.ReleaseBuffer(), m_szProcedure.ReleaseBuffer(), m_szNotification.ReleaseBuffer(), m_szNotificationRecipients.RemoveAll(), cbRecipient = cbRecipients = 0; cbRecipients < sData.cbNotificationRecipients; cbRecipients += (cbRecipient = (m_szNotificationRecipients.GetAt(m_szNotificationRecipients.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szNotificationRecipients.Add((LPCTSTR)(nRecipientData.GetData() + cbRecipients));
			continue;
		}
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CEventList

CEventList::CEventList() : CMutexArray()
{
	m_nIndex = 0;
	m_nAlarms = 0;
	m_bAudioSound = TRUE;
	m_tScheduleOffset = 0;
}

CEventList::~CEventList()
{
	RemoveAll();
}

INT CEventList::Add(CEventObject *pEvent, BOOL bScheduled)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pEvent->GetAuditTime(), bScheduled, TRUE)) >= 0)
	{
		for (m_nIndex = (!bScheduled) ? (m_nIndex + 1) : m_nIndex, InsertAt(nIndex, pEvent, 1); !bScheduled; )
		{
			StartSound(pEvent);
			break;
		}
	}
	return nIndex;
}

BOOL CEventList::Remove(INT nIndex)
{
	if (nIndex >= 0 && nIndex < GetSize())
	{
		for (; nIndex < m_nIndex; )
		{
			StopSound(GetAt(nIndex));
			m_nIndex--;
			break;
		}
		RemoveAt(nIndex);
		return TRUE;
	}
	return FALSE;
}

INT CEventList::Find(CONST CEventObject *pEvent) CONST
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = FindIndex(pEvent->GetAuditTime(), FALSE), nCount = GetScheduleIndex(); nIndex < nCount && nIndex >= 0; nIndex++)
	{
		if (pEvent->GetAuditTime() == GetAt(nIndex)->GetAuditTime())
		{
			if (!pEvent->Compare(GetAt(nIndex))) continue;
			return nIndex;
		}
		break;
	}
	for (nIndex = FindIndex(pEvent->GetAuditTime(), TRUE), nCount = (INT)GetSize(); nIndex < nCount && nIndex >= 0; nIndex++)
	{
		if (pEvent->GetAuditTime() == GetAt(nIndex)->GetAuditTime())
		{
			if (!pEvent->Compare(GetAt(nIndex))) continue;
			return nIndex;
		}
		break;
	}
	return -1;
}

CEventObject *CEventList::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CEventObject *)CMutexArray::GetAt(nIndex) : (CEventObject *)NULL);
}

CEventObject *CEventList::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CEventObject *)CMutexArray::GetAt(nIndex) : (CEventObject *)NULL);
}

BOOL CEventList::Schedule(CEventObject *pScheduledEvent)
{
	UINT  nAuditCycles;
	CTimeKey  tTimeKey;
	CTimeKey  tAuditTime[2];
	CTimeSpan  tAuditPeriod;
	CEventObject  *pEvent[2];

	if ((pEvent[0] = GetAt(m_nIndex)))
	{
		if ((tAuditTime[0] = pEvent[0]->GetAuditTime()) + m_tScheduleOffset.GetTime() <= tTimeKey  &&  Remove(m_nIndex))
		{
			if (pEvent[0]->GetAuditPeriod(tAuditPeriod, tAuditTime[1], nAuditCycles) && tAuditPeriod.GetTotalSeconds() > 0)
			{
				if ((pEvent[1] = ((tAuditTime[0].GetTime() + tAuditPeriod.GetTotalSeconds() <= tAuditTime[1].GetTime() && tTimeKey <= tAuditTime[1].GetTime() + m_tScheduleOffset.GetTime()) || !tAuditTime[1].GetTime()) ? new CEventObject : (CEventObject *)NULL))
				{
					for (pScheduledEvent->Copy(pEvent[0]), pEvent[1]->Copy(pEvent[0]), pEvent[1]->SetAuditTime(tAuditTime[0].GetTime() + ((tTimeKey.GetTime() - tAuditTime[0].GetTime()) / tAuditPeriod.GetTotalSeconds() + 1)*tAuditPeriod.GetTotalSeconds()), pEvent[1]->SetAuditPeriod(tAuditPeriod, tAuditTime[1], (nAuditCycles > 0) ? (UINT)((tAuditTime[1].GetTime() - tAuditTime[0].GetTime()) / tAuditPeriod.GetTotalSeconds()) : 0); Add(pEvent[1], TRUE) >= 0; )
					{
						delete pEvent[0];
						return TRUE;
					}
					delete pEvent[1];
				}
			}
			pScheduledEvent->Copy(pEvent[0]);
			delete pEvent[0];
			return TRUE;
		}
	}
	return FALSE;
}

VOID CEventList::SetScheduleOffset(CONST CTimeKey &tOffset)
{
	m_tScheduleOffset = tOffset;
}

CTimeKey CEventList::GetScheduleOffset() CONST
{
	return m_tScheduleOffset;
}

VOID CEventList::SetScheduleIndex(INT nIndex)
{
	m_nIndex = min(nIndex, (INT)GetSize());
}

INT CEventList::GetScheduleIndex() CONST
{
	return m_nIndex;
}

BOOL CEventList::Acknowledge()
{
	INT  nIndex;
	BOOL  bSound;
	CEventObject  *pEvent;

	if (!IsAcknowledged())
	{
		for (nIndex = 0, bSound = IsSoundEnabled(), EnableSound(FALSE); nIndex < m_nIndex; nIndex++)
		{
			if ((pEvent = GetAt(nIndex)) && !pEvent->IsAcknowledged())
			{
				Acknowledge(pEvent);
				continue;
			}
		}
		EnableSound(bSound);
		return TRUE;
	}
	return FALSE;
}
BOOL CEventList::Acknowledge(CEventObject *pEvent)
{
	if (!pEvent->IsAcknowledged() && StopSound(pEvent))
	{
		pEvent->Acknowledge();
		return TRUE;
	}
	return FALSE;
}

BOOL CEventList::IsAcknowledged() CONST
{
	return((!m_nAlarms) ? TRUE : FALSE);
}

BOOL CEventList::EnableSound(BOOL bEnable)
{
	WORD  wAge;
	WORD  wGender;
	UINT  nAudition;
	DWORD  dwPitch;
	DWORD  dwVolume;
	DWORD  dwPlayback;
	CString  szAdapter;
	CString  szSpeaker;
	CONST CEventObject  *pEvent;

	if ((pEvent = FindFromSoundList()))
	{
		if (IsSoundEnabled() && !bEnable)
		{
			m_cAudioDevice.StopSound(pEvent->GetAudition());
			m_bAudioSound = bEnable;
			return TRUE;
		}
		if (!IsSoundEnabled() && bEnable)
		{
			if ((nAudition = pEvent->GetAudition()) == AUDIO_STANDARD_SOUND)
			{
				m_cAudioDevice.StartSound(nAudition);
				m_bAudioSound = bEnable;
				return TRUE;
			}
			if (nAudition == AUDIO_BEEP_SOUND)
			{
				if (pEvent->GetAudioInfo(szAdapter, dwVolume, dwPitch, dwPlayback))
				{
					m_cAudioDevice.StartSound(szAdapter, nAudition, dwVolume, dwPitch, pEvent->GetAuditBeep());
					m_bAudioSound = bEnable;
					return TRUE;
				}
			}
			if (nAudition == AUDIO_WAVE_SOUND)
			{
				if (pEvent->GetAudioInfo(szAdapter, dwVolume, dwPitch, dwPlayback))
				{
					m_cAudioDevice.StartSound(szAdapter, nAudition, dwVolume, dwPitch, dwPlayback, pEvent->GetAuditWave());
					m_bAudioSound = bEnable;
					return TRUE;
				}
			}
			if (nAudition == AUDIO_VOICE_SOUND)
			{
				if (pEvent->GetAudioInfo(szAdapter, dwVolume, dwPitch, dwPlayback) && pEvent->GetAuditVoice(szSpeaker, wGender, wAge))
				{
					m_cAudioDevice.StartSound(szAdapter, nAudition, dwVolume, dwPitch, dwPlayback, szSpeaker, wGender, wAge, pEvent->GetMessage());
					m_bAudioSound = bEnable;
					return TRUE;
				}
			}
			return FALSE;
		}
	}
	if ((IsSoundEnabled() && !bEnable) || (!IsSoundEnabled() && bEnable))
	{
		m_bAudioSound = bEnable;
		return TRUE;
	}
	return FALSE;
}

BOOL CEventList::IsSoundEnabled() CONST
{
	return m_bAudioSound;
}

VOID CEventList::RemoveAll()
{
	INT  nEvent;
	INT  nEvents;
	BOOL  bSound;
	CEventObject  *pEvent;

	for (nEvent = 0, nEvents = (INT)GetSize(), bSound = IsSoundEnabled(), EnableSound(FALSE); nEvent < nEvents; nEvent++)
	{
		if ((pEvent = GetAt(nEvent)))
		{
			Remove(nEvent);
			delete pEvent;
			nEvents--;
			nEvent--;
		}
	}
	EnableSound(bSound);
}

BOOL CEventList::Copy(CONST CEventList *pEventList)
{
	INT  nEvent;
	INT  nEvents;
	BOOL  bSound;
	CEventObject  *pEvent;

	for (nEvent = 0, nEvents = (INT)pEventList->GetSize(), bSound = IsSoundEnabled(), EnableSound(FALSE), RemoveAll(); nEvent < nEvents; nEvent++)
	{
		if ((pEvent = new CEventObject) != (CEventObject *)NULL)
		{
			pEvent->Copy(pEventList->GetAt(nEvent));
			InsertAt(nEvent, pEvent, 1);
			continue;
		}
		break;
	}
	EnableSound(bSound);
	return((nEvent == nEvents) ? TRUE : FALSE);
}

BOOL CEventList::Compare(CONST CEventList *pEventList) CONST
{
	INT  nEvent;
	INT  nEvents;

	for (nEvent = 0, nEvents = (pEventList->GetSize() == GetSize()) ? (INT)GetSize() : -1; nEvent < nEvents; nEvent++)
	{
		if (!pEventList->GetAt(nEvent)->Compare(GetAt(nEvent))) break;
		continue;
	}
	return((nEvent == nEvents) ? TRUE : FALSE);
}

BOOL CEventList::Map(CByteArray &nInfo, BOOL bScheduled) CONST
{
	INT  nEvent;
	INT  nEvents;
	CByteArray  nEventData;
	CEventObject  *pEvent;

	for (nEvent = (bScheduled) ? GetScheduleIndex() : 0, nEvents = (!bScheduled) ? GetScheduleIndex() : (INT)GetSize(), nInfo.RemoveAll(); nEvent < nEvents; nEvent++)
	{
		if ((pEvent = GetAt(nEvent)) && pEvent->Map(nEventData) && nInfo.Append(nEventData) >= 0) continue;
		break;
	}
	return((nEvent == nEvents) ? TRUE : FALSE);
}

BOOL CEventList::Unmap(CONST CByteArray &nInfo)
{
	INT  cbEvent;
	INT  cbEvents;
	BOOL  bSound;
	CByteArray  nEventData;
	CEventObject  *pEvent;

	for (cbEvents = 0, bSound = IsSoundEnabled(), EnableSound(FALSE), RemoveAll(); cbEvents < nInfo.GetSize(); cbEvents += cbEvent)
	{
		for (CopyMemory(&cbEvent, nInfo.GetData() + cbEvents, sizeof(cbEvent)), nEventData.SetSize(max(min(cbEvent, nInfo.GetSize() - cbEvents), 0)); nEventData.GetSize() >= 0; )
		{
			CopyMemory(nEventData.GetData(), nInfo.GetData() + cbEvents, nEventData.GetSize());
			break;
		}
		if ((pEvent = new CEventObject))
		{
			if (pEvent->Unmap(nEventData) && Add(pEvent) >= 0) continue;
			delete pEvent;
		}
		break;
	}
	EnableSound(bSound);
	return((cbEvents == nInfo.GetSize()) ? TRUE : FALSE);
}

BOOL CEventList::StartSound(CONST CEventObject *pEvent)
{
	WORD  wAge;
	WORD  wGender;
	UINT  nAudition;
	DWORD  dwPitch;
	DWORD  dwVolume;
	DWORD  dwPlayback;
	CString  szAdapter;
	CString  szSpeaker;

	if (pEvent->IsAcknowledged())
	{
		for (; IsSoundEnabled() && pEvent->GetAudition() == AUDIO_STANDARD_SOUND; )
		{
			m_cAudioDevice.StartSound(pEvent->GetAudition());
			break;
		}
		return TRUE;
	}
	if ((nAudition = pEvent->GetAudition()) == AUDIO_NO_SOUND || nAudition == AUDIO_STANDARD_SOUND)
	{
		for (; IsSoundEnabled() && nAudition == AUDIO_STANDARD_SOUND; )
		{
			m_cAudioDevice.StartSound(nAudition);
			break;
		}
		m_nAlarms++;
		return TRUE;
	}
	if (InsertIntoSoundList(pEvent) && IsSoundEnabled())
	{
		if (IsSoundEnabled() && nAudition == AUDIO_BEEP_SOUND) return((pEvent->GetAudioInfo(szAdapter, dwVolume, dwPitch, dwPlayback)) ? m_cAudioDevice.StartSound(szAdapter, nAudition, dwVolume, dwPitch, pEvent->GetAuditBeep()) : FALSE);
		if (IsSoundEnabled() && nAudition == AUDIO_WAVE_SOUND) return((pEvent->GetAudioInfo(szAdapter, dwVolume, dwPitch, dwPlayback)) ? m_cAudioDevice.StartSound(szAdapter, nAudition, dwVolume, dwPitch, dwPlayback, pEvent->GetAuditWave()) : FALSE);
		if (IsSoundEnabled() && nAudition == AUDIO_VOICE_SOUND) return((pEvent->GetAudioInfo(szAdapter, dwVolume, dwPitch, dwPlayback) && pEvent->GetAuditVoice(szSpeaker, wGender, wAge)) ? m_cAudioDevice.StartSound(szAdapter, nAudition, dwVolume, dwPitch, dwPlayback, szSpeaker, wGender, wAge, pEvent->GetMessage()) : FALSE);
		return FALSE;
	}
	return TRUE;
}

BOOL CEventList::StopSound(CONST CEventObject *pEvent)
{
	WORD  wAge;
	WORD  wGender;
	UINT  nAudition;
	DWORD  dwPitch;
	DWORD  dwVolume;
	DWORD  dwPlayback;
	CString  szAdapter;
	CString  szSpeaker;

	if (!pEvent->IsAcknowledged())
	{
		if ((nAudition = pEvent->GetAudition()) != AUDIO_NO_SOUND  &&  nAudition != AUDIO_STANDARD_SOUND)
		{
			if ((nAudition = (RemoveFromSoundList(pEvent) && !IsSoundListEmpty() && IsSoundEnabled()) ? FindFromSoundList()->GetAudition() : AUDIO_NO_SOUND) == AUDIO_BEEP_SOUND) return((FindFromSoundList()->GetAudioInfo(szAdapter, dwVolume, dwPitch, dwPlayback)) ? m_cAudioDevice.StartSound(szAdapter, nAudition, dwVolume, dwPitch, FindFromSoundList()->GetAuditBeep()) : FALSE);
			if (nAudition == AUDIO_WAVE_SOUND) return((FindFromSoundList()->GetAudioInfo(szAdapter, dwVolume, dwPitch, dwPlayback)) ? m_cAudioDevice.StartSound(szAdapter, nAudition, dwVolume, dwPitch, dwPlayback, FindFromSoundList()->GetAuditWave()) : FALSE);
			if (nAudition == AUDIO_VOICE_SOUND) return((FindFromSoundList()->GetAudioInfo(szAdapter, dwVolume, dwPitch, dwPlayback) && FindFromSoundList()->GetAuditVoice(szSpeaker, wGender, wAge)) ? m_cAudioDevice.StartSound(szAdapter, nAudition, dwVolume, dwPitch, dwPlayback, szSpeaker, wGender, wAge, FindFromSoundList()->GetMessage()) : FALSE);
			return((IsSoundListEmpty()) ? m_cAudioDevice.StopSound(pEvent->GetAudition()) : FALSE);
		}
		m_nAlarms--;
		return TRUE;
	}
	return FALSE;
}

BOOL CEventList::InsertIntoSoundList(CONST CEventObject *pEvent)
{
	INT  nIndex;
	CONST CEventObject  *pAudioEvent;

	for (nIndex = (INT)m_pAudioList.GetSize() - 1; nIndex >= 0; nIndex--)
	{
		if ((pAudioEvent = (CONST CEventObject *) m_pAudioList.GetAt(nIndex)) && pAudioEvent->GetAuditTime() <= pEvent->GetAuditTime()) break;
		continue;
	}
	m_nAlarms++;
	m_pAudioList.InsertAt(nIndex + 1, (LPVOID)pEvent, 1);
	return((m_pAudioList.GetUpperBound() == nIndex + 1) ? TRUE : FALSE);
}

BOOL CEventList::RemoveFromSoundList(CONST CEventObject *pEvent)
{
	INT  nIndex;
	CONST CEventObject  *pAudioEvent;

	for (nIndex = (INT)m_pAudioList.GetSize() - 1; nIndex >= 0; nIndex--)
	{
		if ((pAudioEvent = (CONST CEventObject *) m_pAudioList.GetAt(nIndex)) == pEvent)
		{
			m_pAudioList.RemoveAt(nIndex);
			m_nAlarms--;
			break;
		}
	}
	return((nIndex >= 0) ? TRUE : FALSE);
}

CONST CEventObject *CEventList::FindFromSoundList() CONST
{
	return((m_pAudioList.GetSize() > 0) ? (CONST CEventObject *) m_pAudioList.GetAt(m_pAudioList.GetUpperBound()) : (CONST CEventObject *) NULL);
}

BOOL CEventList::IsSoundListEmpty() CONST
{
	return m_pAudioList.IsEmpty();
}

INT CEventList::FindIndex(CONST CTimeKey &tTime, BOOL bScheduled, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CEventObject  *pEvent;

	for (nMinIndex = (bScheduled) ? GetScheduleIndex() : 0, nMaxIndex = (!bScheduled) ? GetScheduleIndex() : (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pEvent = GetAt(nIndex[0]))) ? ((nIndex[1] = ((!bInsert  &&  pEvent->GetAuditTime() < tTime) || (bInsert  &&  pEvent->GetAuditTime() <= tTime))) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return(((!bInsert && ((!bScheduled  &&  nIndex[0] >= 0 && nIndex[0] < GetScheduleIndex()) || (bScheduled  &&  nIndex[0] >= GetScheduleIndex() && nIndex[0] < GetSize()))) || (bInsert && ((!bScheduled  &&  nIndex[0] <= GetScheduleIndex()) || (bScheduled  &&  nIndex[0] <= GetSize())))) ? max(nIndex[0], 0) : -1);
}
