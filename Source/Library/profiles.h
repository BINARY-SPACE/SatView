// PROFILES.H : Profiles Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the profiles related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1997/10/21 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __PROFILES_H__
#define __PROFILES_H__

#include "mutex.h"
#include "timekey.h"


/////////////////////////////////////////////////////////////////////////////
// CPrintProfileInfo

// Specify the default print settings
#define PRINTINFO_DEFAULT_PAPERSIZE   CSize(0,0)
#define PRINTINFO_DEFAULT_METRICMARGIN   CRect(150,150,150,150)
#define PRINTINFO_DEFAULT_INCHMARGIN   CRect(500,500,500,500)
#define PRINTINFO_DEFAULT_PAPERFRAME   CRect(0,0,0,0)

class AFX_EXT_CLASS CPrintProfileInfo : public CObject
{
	// Construction
public:
	CPrintProfileInfo();
	~CPrintProfileInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbDevMode;
		INT  cbDevNames;
		RECT  rtPaperMargin[2];
		SIZE  sizePaperArea;
		BOOL  bPaperMeasure;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	HANDLE  m_hDevMode;
	HANDLE  m_hDevNames;
	RECT  m_rtPaperMargin[2];
	SIZE  m_sizePaperArea;
	BOOL  m_bPaperMeasure;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	BOOL SetDeviceInfo(HANDLE hDevNames, HANDLE hDevMode);
	BOOL GetDeviceInfo(HANDLE &hDevNames, HANDLE &hDevMode) CONST;
	VOID SetPaperInfo(CONST SIZE &sizePaperArea, CONST RECT &rtPaperMargin, CONST RECT &rtPaperFrame, BOOL bPaperMeasure);
	BOOL GetPaperInfo(SIZE &sizePaperArea, RECT &rtPaperMargin, RECT &rtPaperFrame, BOOL &bPaperMeasure) CONST;

	CString GetPrinterName() CONST;
	CString GetPaperForm() CONST;
	CString GetPaperSource() CONST;
	INT GetPaperOrientation() CONST;
	CSize GetPaperResolution() CONST;
	INT GetCopies() CONST;

	BOOL Copy(CONST CPrintProfileInfo *pProfileInfo);
	BOOL Compare(CONST CPrintProfileInfo *pProfileInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPrintProfiles

class AFX_EXT_CLASS CPrintProfiles : public CMutexArray
{
	// Construction
public:
	CPrintProfiles();
	~CPrintProfiles();

	// Attributes
public:

	// Operations
public:
	INT Add(CPrintProfileInfo *pProfileInfo);

	INT Find(LPCTSTR pszName) CONST;
	INT Enum(CStringArray &szNames) CONST;

	CPrintProfileInfo *GetAt(INT nIndex) CONST;
	CPrintProfileInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CPrintProfiles *pProfiles);
	BOOL Compare(CONST CPrintProfiles *pProfiles) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAuditionProfileInfo

// Specify the default audition settings
#define AUDITIONINFO_DEFAULT_VOLUME   0x80008000
#define AUDITIONINFO_DEFAULT_PITCH   0x00010000
#define AUDITIONINFO_DEFAULT_PLAYBACKRATE   0x00010000

class AFX_EXT_CLASS CAuditionProfileInfo : public CObject
{
	// Construction
public:
	CAuditionProfileInfo();
	~CAuditionProfileInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbAdapter;
		INT  cbSpeaker;
		INT  cbSound;
		INT  nAudition;
		DWORD  dwVolume;
		DWORD  dwPitch;
		DWORD  dwPlaybackRate;
		DWORD  dwFrequency;
		DWORD  dwVoice;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szAdapter;
	CString  m_szSpeaker;
	CString  m_szSound;
	DWORD  m_dwVolume;
	DWORD  m_dwPitch;
	DWORD  m_dwPlaybackRate;
	DWORD  m_dwFrequency;
	DWORD  m_dwVoice;
	INT  m_nAudition;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetAdapterInfo(LPCTSTR pszAdapter, DWORD dwVolume, DWORD dwPitch, DWORD dwPlaybackRate);
	BOOL GetAdapterInfo(CString &szAdapter, DWORD &dwVolume, DWORD &dwPitch, DWORD &dwPlaybackRate) CONST;
	VOID SetAudition(INT nAudition);
	INT GetAudition() CONST;
	VOID SetBeepSound(DWORD dwFrequency);
	DWORD GetBeepSound() CONST;
	VOID SetWaveSound(LPCTSTR pszSound);
	CString GetWaveSound() CONST;
	VOID SetVoiceSound(LPCTSTR pszSpeaker, WORD wGender, WORD wAge);
	BOOL GetVoiceSound(CString &szSpeaker, WORD &wGender, WORD &wAge) CONST;

	VOID Copy(CONST CAuditionProfileInfo *pProfileInfo);
	BOOL Compare(CONST CAuditionProfileInfo *pProfileInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAuditionProfiles

class AFX_EXT_CLASS CAuditionProfiles : public CMutexArray
{
	// Construction
public:
	CAuditionProfiles();
	~CAuditionProfiles();

	// Attributes
public:

	// Operations
public:
	INT Add(CAuditionProfileInfo *pProfileInfo);

	INT Find(LPCTSTR pszName) CONST;
	INT Enum(CStringArray &szNames) CONST;

	CAuditionProfileInfo *GetAt(INT nIndex) CONST;
	CAuditionProfileInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CAuditionProfiles *pProfiles);
	BOOL Compare(CONST CAuditionProfiles *pProfiles) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CNotificationProfileInfo

// Specify the notification types
#define NOTIFICATIONINFO_TYPE_NONE   0
#define NOTIFICATIONINFO_TYPE_EMAIL   1
#define NOTIFICATIONINFO_TYPE_FAX   2
#define NOTIFICATIONINFO_TYPE_PHONECALL   3
#define NOTIFICATIONINFO_TYPE_PAGERCALL   4
#define NOTIFICATIONINFO_TYPE_VOIPCALL   5
#define NOTIFICATIONINFO_TYPE_FTPMESSAGE   6
#define NOTIFICATIONINFO_TYPE_PRINTERMESSAGE   7
// Specify the notification options
#define NOTIFICATIONINFO_OPTION_AUDIT_NOTHING   0
#define NOTIFICATIONINFO_OPTION_AUDIT_EVERYTHING   1
#define NOTIFICATIONINFO_OPTION_AUDIT_FAILURES   2
// Specify the notification priority
#define NOTIFICATIONINFO_PRIORITY_DEFAULT  0
#define NOTIFICATIONINFO_PRIORITY_LOW   1
#define NOTIFICATIONINFO_PRIORITY_NORMAL   2
#define NOTIFICATIONINFO_PRIORITY_HIGH   3

class AFX_EXT_CLASS CNotificationProfileInfo : public CObject
{
	// Construction
public:
	CNotificationProfileInfo();
	~CNotificationProfileInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbModem;
		INT  cbText[3];
		INT  cbSpeaker;
		INT  cbRecipients;
		INT  cbFTPUserNames[2];
		INT  cbFTPAddresses;
		INT  cbFTPPasswords;
		INT  cbAttachments;
		UINT  nType;
		UINT  nOptions;
		UINT  nPriority;
		UINT  nFTPPort;
		UINT  nRetry[2];
		WORD  wVoice[2];
		BOOL  bConversation;
		LOGFONT  lfFonts[3];
		COLORREF  nFontColors[3];
		TIMEKEY  tAbortInterval;
		TIMEKEY  tRetryInterval;
		TIMEKEY  tRetryTime;
	} DATA, *PDATA, *LPDATA;
private:
	UINT  m_nType;
	UINT  m_nOptions;
	UINT  m_nPriority;
	UINT  m_nFTPPort;
	UINT  m_nRetry[2];
	WORD  m_wVoice[2];
	BOOL  m_bConversation;
	CString  m_szName;
	CString  m_szModem;
	CString  m_szText[3];
	CString  m_szSpeaker;
	CStringArray  m_szRecipients;
	CStringArray  m_szAttachments;
	CStringArray  m_szFTPUserNames[2];
	CStringArray  m_szFTPAddresses;
	CStringArray  m_szFTPPasswords;
	CTimeSpan  m_tAbortInterval;
	CTimeSpan  m_tRetryInterval;
	CTimeKey  m_tRetryTime;
	COLORREF  m_nFontColors[3];
	LOGFONT  m_lfFonts[3];

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetType(UINT nType);
	UINT GetType() CONST;
	VOID SetOptions(UINT nOptions);
	UINT GetOptions() CONST;
	VOID SetProlog(LPCTSTR pszText);
	CString GetProlog() CONST;
	VOID SetMessage(LPCTSTR pszText);
	CString GetMessage() CONST;
	VOID SetEpilog(LPCTSTR pszText);
	CString GetEpilog() CONST;
	VOID SetAttachments(CONST CStringArray &szAttachments);
	INT GetAttachments(CStringArray &szAttachments) CONST;
	VOID SetRecipients(CONST CStringArray &szRecipients);
	INT GetRecipients(CStringArray &szRecipients) CONST;
	VOID SetPriority(UINT nPriority);
	UINT GetPriority() CONST;

	VOID SetModemInfo(LPCTSTR pszModem);
	BOOL GetModemInfo(CString &szModem) CONST;
	VOID SetVoiceInfo(LPCTSTR pszSpeaker, WORD wGender, WORD wAge, BOOL bConversation = FALSE);
	BOOL GetVoiceInfo(CString &szSpeaker, WORD &wGender, WORD &wAge, BOOL &bConversation) CONST;
	VOID SetFontInfo(CONST LOGFONT *plfPrologText, COLORREF nPrologTextColor, CONST LOGFONT *plfMessageText, COLORREF nMessageTextColor, CONST LOGFONT *plfEpilogText, COLORREF nEpilogTextColor);
	BOOL GetFontInfo(LOGFONT *plfPrologText, COLORREF &nPrologTextColor, LOGFONT *plfMessageText, COLORREF &nMessageTextColor, LOGFONT *plfEpilogText, COLORREF &nEpilogTextColor) CONST;
	VOID SetFTPInfo(CONST CStringArray &szUsers, CONST CStringArray &szLogins, CONST CStringArray &szAddresses, CONST CStringArray &szPasswords, UINT nPort);
	INT GetFTPInfo(CStringArray &szUsers, CStringArray &szLogins, CStringArray &szAddresses, CStringArray &szPasswords, UINT &nPort) CONST;
	VOID SetBehaviorInfo(UINT nRetryCount, CONST CTimeSpan &tRetryInterval, CONST CTimeSpan &tAbortInterval);
	BOOL GetBehaviorInfo(UINT &nRetryCount, CTimeSpan &tRetryInterval, CTimeSpan &tAbortInterval) CONST;
	VOID SetRetryTime(CONST CTimeKey &tTime);
	CTimeKey GetRetryTime() CONST;
	VOID SetRetryCount(UINT nCount);
	UINT GetRetryCount() CONST;

	VOID Copy(CONST CNotificationProfileInfo *pProfileInfo, BOOL bData = FALSE);
	BOOL Compare(CONST CNotificationProfileInfo *pProfileInfo, BOOL bData = FALSE) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CNotificationProfiles

class AFX_EXT_CLASS CNotificationProfiles : public CMutexArray
{
	// Construction
public:
	CNotificationProfiles();
	~CNotificationProfiles();

	// Attributes
public:

	// Operations
public:
	INT Add(CNotificationProfileInfo *pProfileInfo);

	INT Find(LPCTSTR pszName) CONST;
	INT Enum(CStringArray &szNames) CONST;

	CNotificationProfileInfo *GetAt(INT nIndex) CONST;
	CNotificationProfileInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CNotificationProfiles *pProfiles, BOOL bData = FALSE);
	BOOL Compare(CONST CNotificationProfiles *pProfiles, BOOL bData = FALSE) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////


#endif // __PROFILES_H__
