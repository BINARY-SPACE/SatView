// EVENT.H : Event Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the event related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1993/10/24 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __EVENT_H__
#define __EVENT_H__

#include "audio.h"
#include "mutex.h"
#include "timekey.h"


/////////////////////////////////////////////////////////////////////////////
// CEventObject

// Specify the event category related identifiers
#define EVENT_CATEGORY_NONE   0
#define FIRSTEVENTCATEGORY   (1<<0)
#define EVENT_CATEGORY_SYSTEM   FIRSTEVENTCATEGORY
#define EVENT_CATEGORY_SPACECRAFT   (FIRSTEVENTCATEGORY<<1)
#define EVENT_CATEGORY_USER   (FIRSTEVENTCATEGORY<<2)
#define LASTEVENTCATEGORY   (FIRSTEVENTCATEGORY<<2)
#define EVENT_CATEGORY_ALL   (EVENT_CATEGORY_SYSTEM | EVENT_CATEGORY_SPACECRAFT | EVENT_CATEGORY_USER)
#define EVENT_CATEGORIES   3
// Specify the event type related identifiers
#define EVENT_TYPE_NONE   0
#define FIRSTEVENTTYPE   (1<<EVENT_CATEGORIES)
#define EVENT_TYPE_SUCCESS   FIRSTEVENTTYPE
#define EVENT_TYPE_INFORMATIONAL   (FIRSTEVENTTYPE<<1)
#define EVENT_TYPE_WARNING   (FIRSTEVENTTYPE<<2)
#define EVENT_TYPE_ERROR   (FIRSTEVENTTYPE<<3)
#define EVENT_TYPE_SCHEDULED   (FIRSTEVENTTYPE<<4)
#define LASTEVENTTYPE   (FIRSTEVENTTYPE<<4)
#define EVENT_TYPES   5

class AFX_EXT_CLASS CEventObject : public CObject
{
	// Construction
public:
	CEventObject();
	CEventObject(CONST EVENT_DESCRIPTOR sEvent);

	// Attributes
private:
	typedef struct tagData {
		INT  cbSize;
		INT  cbType;
		INT  cbUser;
		INT  cbSound;
		INT  cbAdapter;
		INT  cbSpeaker;
		INT  cbMessage;
		INT  cbComments;
		INT  cbProcedure;
		INT  cbNotification;
		INT  cbNotificationRecipients;
		UINT  nCategory;
		UINT  nAudition;
		UINT  nAuditCycles;
		UINT  nNotificationType;
		DWORD  dwAuditVoice;
		DWORD  dwAudioPitch;
		DWORD  dwAudioVolume;
		DWORD  dwAudioPlayback;
		DWORD  dwAudioFrequency;
		TIMEKEY  tAuditStartTime;
		TIMEKEY  tAuditStopTime;
		TIMEKEY  tAuditPeriod;
		COLORREF  nAuditColor;
		BOOL  bAcknowledged;
	} DATA, *PDATA, *LPDATA;
private:
	UINT  m_nCategory;
	UINT  m_nAudition;
	UINT  m_nAuditCycles;
	UINT  m_nNotificationType;
	DWORD  m_dwAuditVoice;
	DWORD  m_dwAudioPitch;
	DWORD  m_dwAudioVolume;
	DWORD  m_dwAudioPlayback;
	DWORD  m_dwAudioFrequency;
	CTimeKey  m_tAuditStartTime;
	CTimeKey  m_tAuditStopTime;
	CTimeSpan  m_tAuditPeriod;
	COLORREF  m_nAuditColor;
	CString  m_szType;
	CString  m_szUser;
	CString  m_szSound;
	CString  m_szAdapter;
	CString  m_szSpeaker;
	CString  m_szMessage;
	CString  m_szComments;
	CString  m_szProcedure;
	CString  m_szNotification;
	CStringArray  m_szNotificationRecipients;
	BOOL  m_bAcknowledged;
	BOOL  m_bVisible;

	// Operations
public:
	VOID SetCategory(UINT nCategory);
	UINT GetCategory() CONST;
	VOID SetType(LPCTSTR pszType);
	CString GetType() CONST;
	VOID SetSubtype(LPCTSTR pszSubtype);
	CString GetSubtype() CONST;
	VOID SetUser(LPCTSTR pszUser);
	CString GetUser() CONST;
	VOID SetMessage(LPCTSTR pszMessage);
	CString GetMessage() CONST;
	VOID SetComments(LPCTSTR pszComments);
	CString GetComments() CONST;
	VOID SetProcedure(LPCTSTR pszProcedure);
	CString GetProcedure() CONST;
	VOID SetNotification(UINT nType, LPCTSTR pszNotification);
	BOOL GetNotification(UINT &nType, CString &szNotification) CONST;
	VOID SetNotificationRecipients(CONST CStringArray &szRecipients);
	INT GetNotificationRecipients(CStringArray &szRecipients) CONST;
	VOID SetAudioInfo(LPCTSTR pszAdapter, DWORD dwVolume, DWORD dwPitch, DWORD dwPlayback);
	BOOL GetAudioInfo(CString &szAdapter, DWORD &dwVolume, DWORD &dwPitch, DWORD &dwPlayback) CONST;
	VOID SetAudition(UINT nAudition);
	UINT GetAudition() CONST;
	VOID SetAuditBeep(DWORD dwFrequency);
	DWORD GetAuditBeep() CONST;
	VOID SetAuditWave(LPCTSTR pszSound);
	CString GetAuditWave() CONST;
	VOID SetAuditVoice(LPCTSTR pszSpeaker, WORD wGender, WORD wAge);
	BOOL GetAuditVoice(CString &szSpeaker, WORD &wGender, WORD &wAge) CONST;
	VOID SetAuditColor(COLORREF nColor);
	COLORREF GetAuditColor() CONST;
	VOID SetAuditTime(CONST CTimeKey &tTime);
	CTimeKey GetAuditTime() CONST;
	VOID SetAuditPeriod(CONST CTimeSpan &tPeriod, CONST CTimeKey &tTime, UINT nCycles);
	BOOL GetAuditPeriod(CTimeSpan &tPeriod, CTimeKey &tTime, UINT &nCycles) CONST;

	VOID Acknowledge(BOOL bAcknowledge = TRUE);
	BOOL IsAcknowledged() CONST;
	VOID Show(BOOL bVisible = TRUE);
	BOOL IsVisible() CONST;

	VOID Copy(CONST CEventObject *pEvent);
	BOOL Compare(CONST CEventObject *pEvent) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventList

class AFX_EXT_CLASS CEventList : public CMutexArray
{
	// Construction
public:
	CEventList();
	~CEventList();

	// Attributes
private:
	INT  m_nIndex;
	UINT  m_nAlarms;
	BOOL  m_bAudioSound;
	CPtrArray  m_pAudioList;
	CAudioDevice  m_cAudioDevice;
	CTimeKey  m_tScheduleOffset;

	// Operations
public:
	INT Add(CEventObject *pEvent, BOOL bScheduled = FALSE);
	BOOL Remove(INT nIndex);

	INT Find(CONST CEventObject *pEvent) CONST;

	CEventObject *GetAt(INT nIndex) CONST;
	CEventObject *operator[](INT nIndex) CONST;

	BOOL Schedule(CEventObject *pScheduledEvent);
	VOID SetScheduleOffset(CONST CTimeKey &tOffset);
	CTimeKey GetScheduleOffset() CONST;
	VOID SetScheduleIndex(INT nIndex);
	INT GetScheduleIndex() CONST;

	BOOL Acknowledge();
	BOOL Acknowledge(CEventObject *pEvent);
	BOOL IsAcknowledged() CONST;

	BOOL EnableSound(BOOL bEnable = TRUE);
	BOOL IsSoundEnabled() CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CEventList *pEventList);
	BOOL Compare(CONST CEventList *pEventList) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bScheduled = FALSE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL StartSound(CONST CEventObject *pEvent);
	BOOL StopSound(CONST CEventObject *pEvent);
	BOOL InsertIntoSoundList(CONST CEventObject *pEvent);
	BOOL RemoveFromSoundList(CONST CEventObject *pEvent);
	CONST CEventObject *FindFromSoundList() CONST;
	BOOL IsSoundListEmpty() CONST;

	INT FindIndex(CONST CTimeKey &tTime, BOOL bScheduled, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////


#endif // __EVENT_H__
