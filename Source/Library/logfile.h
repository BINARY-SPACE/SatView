// LOGFILE.H : Logfile Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the logfile related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1995/01/08 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __LOGFILE_H__
#define __LOGFILE_H__

#include "tools.h"
#include "timekey.h"


/////////////////////////////////////////////////////////////////////////////
// CLogFile

// Specify the logfile policy flags
#define LOGFILE_POLICY_CYCLICMODE   (1<<0)
#define LOGFILE_POLICY_NONCYCLICMODE   (1<<1)
#define LOGFILE_POLICY_RETENTIONBYITEM   (1<<2)
#define LOGFILE_POLICY_RETENTIONBYSIZE   (1<<3)
#define LOGFILE_POLICY_RETENTIONBYTIME   (1<<4)
#define LOGFILE_POLICY_DISABLED   (1<<5)
#define LOGFILE_POLICY_RESET   (1<<6)
// Specify the default logfile settings
#define LOGFILE_DEFAULT_RECORDSIZE   1024
#define LOGFILE_DEFAULT_SIZE   (1024*LOGFILE_DEFAULT_RECORDSIZE)
#define LOGFILE_DEFAULT_VERSION   MAKELONG(1,0)

class AFX_EXT_CLASS CLogFile : public CFileEx
{
	// Construction
public:
	CLogFile();
	~CLogFile();

	// Attributes
private:
	typedef struct tagHEADERDATA {
		UINT  nPolicy;
		INT  cbRecord;
		INT  nItemCount;
		INT  nRetention;
		TIMEKEY  tRetention;
		DWORDLONG  fRetention;
		DWORDLONG  fPosition;
		DWORDLONG  fFirstPosition;
		DWORDLONG  fLastPosition;
	} HEADERDATA, *PHEADERDATA, *LPHEADERDATA;

	typedef struct tagHEADER {
		TCHAR  szText[(LOGFILE_DEFAULT_RECORDSIZE - sizeof(HEADERDATA)) / sizeof(TCHAR)];
		HEADERDATA  sData;
	} HEADER, *PHEADER, *LPHEADER;

	typedef struct tagRECORDHEADER {
		TIMEKEY  tTimeKey;
		DWORDLONG  fPosition;
	} RECORDHEADER, *PRECORDHEADER, *LPRECORDHEADER;

	typedef struct tagRECORDDATAHEADER {
		TIMEKEY  tTimeKey;
		INT  nCount;
		INT  cbInfo;
	} RECORDDATAHEADER, *PRECORDDATAHEADER, *LPRECORDDATAHEADER;
protected:
	UINT  m_nPolicy;
	INT  m_cbRecord;
	INT  m_nItemCount;
	INT  m_nRetention;
	CString  m_szText;
	DWORDLONG  m_fPosition;
	DWORDLONG  m_fFirstPosition;
	DWORDLONG  m_fLastPosition;
	DWORDLONG  m_fWatchPosition;
	DWORDLONG  m_fRetention;
	CTimeSpan  m_tRetention;
private:
	HANDLE  m_hWatchEvent;
private:
	UINT  m_nLocks;
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	BOOL Open(LPCTSTR pszFileName, LPCTSTR pszSpacecraft, LPCTSTR pszType, UINT nFlags, BOOL bWait = TRUE);
	BOOL Open(LPCTSTR pszFileName, LPCTSTR pszSpacecraft, LPCTSTR pszType, LPCTSTR pszAlernateType, UINT nFlags, BOOL bWait = TRUE);
	BOOL Initialize(LPCTSTR pszSpacecraft, LPCTSTR pszType);
	BOOL Compress(BOOL bEnable = TRUE);
	BOOL Reset();
	VOID Close();

	BOOL SetMode(UINT nMode);
	BOOL GetMode(UINT &nMode) CONST;
	BOOL SetPolicy(UINT nPolicy);
	BOOL GetPolicy(UINT &nPolicy) CONST;
	BOOL SetRecordSize(INT cbRecord);
	BOOL GetRecordSize(INT &cbRecord) CONST;
	BOOL SetTime(CONST FILETIME *pTime);
	BOOL GetTime(LPFILETIME pTime) CONST;
	BOOL SetSize(DWORDLONG fSize);
	DWORDLONG GetSize() CONST;
	BOOL IsEmpty() CONST;

	BOOL SetType(LPCTSTR pszType);
	BOOL GetType(CString &szType) CONST;
	BOOL SetSpacecraft(LPCTSTR pszSpacecraft);
	BOOL GetSpacecraft(CString &szSpacecraft) CONST;
	BOOL SetCopyrightProduct(LPCTSTR pszProduct);
	BOOL GetCopyrightProduct(CString &szProductName) CONST;
	BOOL SetCopyrightVersion(DWORD dwVersion);
	BOOL GetCopyrightVersion(DWORD &dwVersion) CONST;
	BOOL SetCopyrightCompany(LPCTSTR pszCompany);
	BOOL GetCopyrightCompany(CString &szCompany) CONST;
	BOOL SetCopyrightTrademark(LPCTSTR pszTrademark);
	BOOL GetCopyrightTrademark(CString &szTrademark) CONST;
	BOOL SetCopyrightCreationTime(CONST CTimeKey &tTime);
	BOOL GetCopyrightCreationTime(CTimeKey &tTime) CONST;
	BOOL SetRetentionByItem(INT nRetention);
	BOOL GetRetentionByItem(INT &nRetention) CONST;
	BOOL SetRetentionBySize(DWORDLONG fRetention);
	BOOL GetRetentionBySize(DWORDLONG &fRetention) CONST;
	BOOL SetRetentionByTime(CONST CTimeSpan &tRetention);
	BOOL GetRetentionByTime(CTimeSpan &tRetention) CONST;

	BOOL Write(CONST CTimeKey &tTimeKey, CONST CByteArray &nInfo);
	BOOL Read(CTimeKey &tTimeKey, CByteArray &nInfo) CONST;

	BOOL SeekToFirst() CONST;
	BOOL SeekToLast() CONST;
	BOOL SeekTo(CONST CTimeKey &tTimeKey, BOOL bNotBefore = FALSE) CONST;
	BOOL SeekFromPosition(DWORDLONG fStartPosition, INT nCount) CONST;
	BOOL SeekFromEnd(INT nCount) CONST;

	HANDLE BeginWatch();
	BOOL IsWatched() CONST;
	BOOL Watch(CByteArray &nInfo);
	BOOL EndWatch();

	BOOL Lock();
	BOOL IsLocked() CONST;
	BOOL Unlock();

public:
	static BOOL Rename(LPCTSTR pszFileName, LPCTSTR pszNewFileName, BOOL bHide = FALSE);
	static BOOL Remove(LPCTSTR pszFileName);

protected:
	BOOL SeekPosition(DWORDLONG fPosition) CONST;
	BOOL CheckPosition(DWORDLONG fPosition) CONST;
	DWORDLONG AdjustPosition(DWORDLONG fPosition) CONST;
	DWORDLONG CalculatePosition(DWORDLONG fPosition, INT cbInfo) CONST;
	DWORDLONG ProgressPosition(DWORDLONG fPosition, INT cbInfo) CONST;

	DWORDLONG FindHeaderPosition(DWORDLONG fPosition) CONST;
	BOOL IsHeaderPosition(DWORDLONG fPosition) CONST;
	BOOL IsEOFPosition(DWORDLONG fPosition) CONST;

	DWORDLONG ProgressRecordData(DWORDLONG fPosition, INT cbData) CONST;
	INT CalculateRecordDataSize(DWORDLONG fPosition) CONST;

	BOOL SaveHeader();
	BOOL LoadHeader();
	BOOL WriteHeaderInfo(LPCTSTR pszInfo, LPCTSTR pszText);
	BOOL ReadHeaderInfo(LPCTSTR pszInfo, CString &szText) CONST;
	BOOL CheckHeaderInfo(LPCTSTR pszSpacecraft, LPCTSTR pszType, LPCTSTR pszAlternateType = NULL) CONST;
	CString ConstructHeaderInfo(LPCTSTR pszSpacecraft, LPCTSTR pszType) CONST;
	BOOL WriteRecordHeader(DWORDLONG fPosition, CONST PRECORDHEADER pfHeader);
	BOOL ReadRecordHeader(DWORDLONG fPosition, PRECORDHEADER pfHeader) CONST;
	BOOL WriteRecordDataHeader(DWORDLONG fPosition, CONST PRECORDDATAHEADER pfDataHeader);
	BOOL ReadRecordDataHeader(DWORDLONG fPosition, PRECORDDATAHEADER pfDataHeader) CONST;
	BOOL Check(CTimeKey &tTimeKey, DWORDLONG fSize, INT cbInfo, BOOL &bRetention) CONST;
	BOOL Write(LPCVOID pInfo, DWORD cbInfo);
	BOOL Read(LPVOID pInfo, DWORD cbInfo) CONST;
};

/////////////////////////////////////////////////////////////////////////////


#endif // __LOGFILE_H__
