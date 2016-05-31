// ARCHIVE.H : Archiving Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the archiving related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/06/29 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __ARCHIVE_H__
#define __ARCHIVE_H__

#include "ttcprocess.h"


/////////////////////////////////////////////////////////////////////////////
// CArchivesExtractionProfileInfo

// Specify the archives extraction characters sets
#define ARCHIVESEXTRACTIONINFO_CHARSET_ASCII   0
#define ARCHIVESEXTRACTIONINFO_CHARSET_UNICODE   1
// Specify the archives extraction time formats
#define ARCHIVESEXTRACTIONINFO_TIMEFORMAT_NONE   0
#define ARCHIVESEXTRACTIONINFO_TIMEFORMAT_DEFAULT   1
#define ARCHIVESEXTRACTIONINFO_TIMEFORMAT_SHORTDEFAULT   2
#define ARCHIVESEXTRACTIONINFO_TIMEFORMAT_DATETIME   3
#define ARCHIVESEXTRACTIONINFO_TIMEFORMAT_SHORTDATETIME   4
#define ARCHIVESEXTRACTIONINFO_TIMEFORMAT_TIME   5
#define ARCHIVESEXTRACTIONINFO_TIMEFORMAT_SHORTTIME   6
#define ARCHIVESEXTRACTIONINFO_TIMEFORMAT_MILLISECONDS   7
#define ARCHIVESEXTRACTIONINFO_TIMEFORMAT_SECONDS   8
// Specify the archives extraction parameter formats
#define ARCHIVESEXTRACTIONINFO_FORMAT_DEFAULT   (1<<0)
#define ARCHIVESEXTRACTIONINFO_FORMAT_CODED   (1<<1)
#define ARCHIVESEXTRACTIONINFO_FORMAT_DECIMAL   (1<<2)
#define ARCHIVESEXTRACTIONINFO_FORMAT_BINARY   (1<<3)
#define ARCHIVESEXTRACTIONINFO_FORMAT_OCTAL   (1<<4)
#define ARCHIVESEXTRACTIONINFO_FORMAT_HEXADECIMAL   (1<<5)
#define ARCHIVESEXTRACTIONINFO_FORMAT_INVERSE   (1<<6)
#define ARCHIVESEXTRACTIONINFO_FORMAT_STATUS   (1<<7)
// Specify the archives extraction parameter triggers
#define ARCHIVESEXTRACTIONINFO_TRIGGER_DEFAULT   (1<<0)
#define ARCHIVESEXTRACTIONINFO_TRIGGER_UPDATES   (1<<0)
#define ARCHIVESEXTRACTIONINFO_TRIGGER_CHANGES   (1<<1)
// Specify the archives extraction time range modes
#define ARCHIVESEXTRACTIONINFO_RANGE_NORMAL   1
#define ARCHIVESEXTRACTIONINFO_RANGE_DAILY   2
#define ARCHIVESEXTRACTIONINFO_RANGE_COMPLETEINTERVAL   3
#define ARCHIVESEXTRACTIONINFO_RANGE_PARTIALINTERVAL   4
#define ARCHIVESEXTRACTIONINFO_RANGE_TRIGGEREDINTERVAL   5
// Specify the archives extraction execution modes
#define ARCHIVESEXTRACTIONINFO_EXECUTION_IMMEDIATELY   1
#define ARCHIVESEXTRACTIONINFO_EXECUTION_ATTIME   2
#define ARCHIVESEXTRACTIONINFO_EXECUTION_ATDAILYTIME   3
#define ARCHIVESEXTRACTIONINFO_EXECUTION_ATINTERVAL   4
#define ARCHIVESEXTRACTIONINFO_EXECUTION_ATEVENT   5
#define ARCHIVESEXTRACTIONINFO_EXECUTION_BYSCRIPT   6
// Specify the archives extraction execution status
#define ARCHIVESEXTRACTIONINFO_EXECUTIONSTATUS_RUNNING   1
#define ARCHIVESEXTRACTIONINFO_EXECUTIONSTATUS_QUEUED   2
// Specify the archives extraction automation options
#define ARCHIVESEXTRACTIONINFO_AUTOMATIONOPTION_FTPTRANSFER   (1<<0)
#define ARCHIVESEXTRACTIONINFO_AUTOMATIONOPTION_DISABLED   (1<<1)
// Specify the archives extraction audition codes
#define ARCHIVESEXTRACTIONINFO_AUDITION_NONE   0
#define ARCHIVESEXTRACTIONINFO_AUDITION_ALL   1
#define ARCHIVESEXTRACTIONINFO_AUDITION_FAILURES   2

class AFX_EXT_CLASS CArchivesExtractionProfileInfo : public CObject
{
	// Construction
public:
	CArchivesExtractionProfileInfo();
	~CArchivesExtractionProfileInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbSource;
		INT  cbFileName;
		INT  cbDirectory;
		INT  cbFTPLocation;
		INT  cbFTPUserName;
		INT  cbFTPPassword;
		INT  cbDelimiters[3];
		INT  cbParameters[3];
		INT  cbExecutionEvent;
		INT  cbAutomationScript;
		INT  cbAutomationOutput;
		UINT  nModes[2];
		UINT  nCharset;
		UINT  nTimeFormat;
		UINT  nCycleCount;
		UINT  nFTPPort;
		UINT  nFTPAudition;
		UINT  nFTPRetryCount[2];
		UINT  nAutomationOptions;
		BOOL  bFTPOption;
		BOOL  bTitleOption;
		TIMEKEY  tRange[2];
		TIMEKEY  tDailyRange[2];
		TIMEKEY  tIntervalRange[3];
		TIMEKEY  tIntervalExecution;
		TIMEKEY  tExecution[3];
		TIMEKEY  tLastExecution;
		TIMEKEY  tDailyExecution;
		TIMEKEY  tFTPRetryInterval;
		TIMEKEY  tFTPRetry;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szSource;
	CString  m_szFileName;
	CString  m_szDirectory;
	CString  m_szFTPLocation;
	CString  m_szFTPUserName;
	CString  m_szFTPPassword;
	CString  m_szDelimiters[3];
	CString  m_szExecutionEvent;
	CString  m_szAutomationScript;
	CString  m_szAutomationOutput;
	CStringArray  m_szParameters;
	CUIntArray  m_nParameterFormats;
	CUIntArray  m_nParameterTriggers;
	CTimeSpan  m_tIntervalExecution;
	CTimeSpan  m_tIntervalRange[3];
	CTimeSpan  m_tFTPRetryInterval;
	CTimeSpan  m_tDailyExecution;
	CTimeSpan  m_tDailyRange[2];
	CTimeKey  m_tLastExecution;
	CTimeKey  m_tExecution[3];
	CTimeKey  m_tRange[2];
	CTimeKey  m_tFTPRetry;
	UINT  m_nModes[2];
	UINT  m_nStatus;
	UINT  m_nCharset;
	UINT  m_nTimeFormat;
	UINT  m_nCycleCount;
	UINT  m_nFTPAudition;
	UINT  m_nFTPRetryCount[2];
	UINT  m_nFTPPort;
	UINT  m_nAutomationOptions;
	BOOL  m_bTitleOption;
	BOOL  m_bFTPOption;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetSource(LPCTSTR pszFileName);
	CString GetSource() CONST;
	VOID SetFileName(LPCTSTR pszFileName);
	CString GetFileName() CONST;
	VOID SetDirectory(LPCTSTR pszDirectory);
	CString GetDirectory() CONST;
	VOID SetCharset(UINT nCharset);
	UINT GetCharset() CONST;
	VOID SetTimeFormat(UINT nFormat);
	UINT GetTimeFormat() CONST;
	VOID SetTitleOption(BOOL bEnable);
	BOOL GetTitleOption() CONST;
	VOID SetColumnDelimiter(LPCTSTR pszDelimiter);
	CString GetColumnDelimiter() CONST;
	VOID SetRowDelimiter(LPCTSTR pszDelimiter);
	CString GetRowDelimiter() CONST;
	VOID SetTextDelimiter(LPCTSTR pszDelimiter);
	CString GetTextDelimiter() CONST;

	VOID SetParameters(CONST CStringArray &szParameters, CONST CUIntArray &nFormats, CONST CUIntArray &nTriggers);
	INT GetParameters(CStringArray &szParameters, CUIntArray &nFormats, CUIntArray &nTriggers) CONST;

	VOID SetTimeRangeMode(UINT nMode);
	UINT GetTimeRangeMode() CONST;
	VOID SetTimeRange(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime);
	BOOL GetTimeRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	VOID SetDailyTimeRange(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime);
	BOOL GetDailyTimeRange(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;
	VOID SetPeriodicalInterval(CONST CTimeSpan &tInterval);
	CTimeSpan GetPeriodicalInterval() CONST;
	VOID SetTriggeredInterval(CONST CTimeSpan &tInterval, BOOL bBefore = TRUE);
	CTimeSpan GetTriggeredInterval(BOOL bBefore = TRUE) CONST;
	VOID SetRangeInterval(CONST CTimeSpan &tInterval);
	CTimeSpan GetRangeInterval() CONST;

	VOID SetExecutionMode(UINT nMode);
	UINT GetExecutionMode() CONST;
	VOID SetExecutionStatus(UINT nStatus);
	UINT GetExecutionStatus() CONST;
	VOID SetExecutionCycle(UINT nCycle);
	UINT GetExecutionCycle() CONST;
	VOID SetExecutionTime(CONST CTimeKey &tTime);
	CTimeKey GetExecutionTime() CONST;
	VOID SetDailyExecutionTime(CONST CTimeSpan &tTime);
	CTimeSpan GetDailyExecutionTime() CONST;
	VOID SetPeriodicalExecutionTime(CONST CTimeKey &tStartTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime);
	BOOL GetPeriodicalExecutionTime(CTimeKey &tStartTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST;
	VOID SetTriggeredExecution(LPCTSTR pszEvent);
	CString GetTriggeredExecution() CONST;
	VOID SetLastExecutionTime(CONST CTimeKey &tTime);
	CTimeKey GetLastExecutionTime() CONST;

	VOID SetFTPOption(BOOL bEnabled);
	BOOL GetFTPOption() CONST;
	VOID SetFTPLocation(LPCTSTR pszLocation);
	CString GetFTPLocation() CONST;
	VOID SetFTPUserName(LPCTSTR pszName);
	CString GetFTPUserName() CONST;
	VOID SetFTPPassword(LPCTSTR pszPassword);
	CString GetFTPPassword() CONST;
	VOID SetFTPPort(UINT nPort);
	UINT GetFTPPort() CONST;
	VOID SetFTPRetryInfo(UINT nRetries, CONST CTimeSpan &tInterval);
	BOOL GetFTPRetryInfo(UINT &nRetries, CTimeSpan &tInterval) CONST;
	VOID SetFTPRetryTime(CONST CTimeKey &tTime);
	CTimeKey GetFTPRetryTime() CONST;
	VOID SetFTPRetryCount(UINT nCount);
	UINT GetFTPRetryCount() CONST;
	VOID SetFTPAudition(UINT nAudition);
	UINT GetFTPAudition() CONST;

	VOID SetAutomationScriptName(LPCTSTR pszScript);
	CString GetAutomationScriptName() CONST;
	VOID SetAutomationScriptOutput(LPCTSTR pszFileName);
	CString GetAutomationScriptOutput() CONST;
	VOID SetAutomationScriptOptions(UINT nOptions);
	UINT GetAutomationScriptOptions() CONST;

	VOID Copy(CONST CArchivesExtractionProfileInfo *pProfileInfo);
	BOOL Compare(CONST CArchivesExtractionProfileInfo *pProfileInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CArchivesExtractionProfiles

class AFX_EXT_CLASS CArchivesExtractionProfiles : public CMutexArray
{
	// Construction
public:
	CArchivesExtractionProfiles();
	~CArchivesExtractionProfiles();

	// Attributes
public:

	// Operations
public:
	INT Add(CArchivesExtractionProfileInfo *pProfileInfo);

	INT Find(LPCTSTR pszName) CONST;
	INT Enum(CStringArray &szNames) CONST;

	CArchivesExtractionProfileInfo *GetAt(INT nIndex) CONST;
	CArchivesExtractionProfileInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CArchivesExtractionProfiles *pProfiles);
	BOOL Compare(CONST CArchivesExtractionProfiles *pProfiles) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHistoryFileExtractionProfileInfo

// Specify the history file extraction options
#define HISTORYFILEEXTRACTION_OPTION_NONE   0
#define HISTORYFILEEXTRACTION_OPTION_STANDARD   (1<<0)
#define HISTORYFILEEXTRACTION_OPTION_RAW   (1<<1)
#define HISTORYFILEEXTRACTION_OPTION_STARTTIME   (1<<2)
#define HISTORYFILEEXTRACTION_OPTION_STARTFILE   (1<<3)
#define HISTORYFILEEXTRACTION_OPTION_STOPTIME   (1<<4)
#define HISTORYFILEEXTRACTION_OPTION_STOPSIZE   (1<<5)
#define HISTORYFILEEXTRACTION_OPTION_STOPDISK   (1<<6)
#define HISTORYFILEEXTRACTION_OPTION_EXECUTEANYTIME   (1<<7)
#define HISTORYFILEEXTRACTION_OPTION_EXECUTEOUTSIDETIME   (1<<8)
// Specify the history file formatting options
#define HISTORYFILEEXTRACTION_FORMAT_NONE   0
#define HISTORYFILEEXTRACTION_FORMAT_ASCII   (1<<0)
#define HISTORYFILEEXTRACTION_FORMAT_BINARY   (1<<1)
#define HISTORYFILEEXTRACTION_FORMAT_RADIX2   (1<<2)
#define HISTORYFILEEXTRACTION_FORMAT_RADIX8   (1<<3)
#define HISTORYFILEEXTRACTION_FORMAT_RADIX10   (1<<4)
#define HISTORYFILEEXTRACTION_FORMAT_RADIX16   (1<<5)
#define HISTORYFILEEXTRACTION_FORMAT_BLOCK8BITS   (1<<6)
#define HISTORYFILEEXTRACTION_FORMAT_BLOCK16BITS   (1<<7)
#define HISTORYFILEEXTRACTION_FORMAT_BLOCK32BITS   (1<<8)
#define HISTORYFILEEXTRACTION_FORMAT_BLOCK64BITS   (1<<9)
#define HISTORYFILEEXTRACTION_FORMAT_NOSEPARATOR   (1<<10)
#define HISTORYFILEEXTRACTION_FORMAT_CRSEPARATOR   (1<<11)
#define HISTORYFILEEXTRACTION_FORMAT_EOLSEPARATOR   (1<<12)
#define HISTORYFILEEXTRACTION_FORMAT_CREOLSEPARATOR   (1<<13)
#define HISTORYFILEEXTRACTION_FORMAT_USESEPARATEFILES   (1<<14)
#define HISTORYFILEEXTRACTION_FORMAT_UNICODECHARSET   (1<<15)

class AFX_EXT_CLASS CHistoryFileExtractionProfileInfo : public CObject
{
	// Construction
public:
	CHistoryFileExtractionProfileInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbFileName;
		INT  cbFilePrefix;
		INT  cbFileExtension;
		INT  cbSources;
		INT  cbFilters;
		UINT  nInterval;
		UINT  nOptions[2];
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
		TIMEKEY  tInterval;
		TIMEKEY  tExecution[2];
		DWORDLONG  dwStopSize;
	} DATA, *PDATA, *LPDATA;
private:
	UINT  m_nInterval;
	UINT  m_nOptions[2];
	CString  m_szFileName;
	CString  m_szFilePrefix;
	CString  m_szFileExtension;
	CTimeKey  m_tStopTime;
	CTimeKey  m_tStartTime;
	DWORDLONG  m_dwStopSize;
	CTimeSpan  m_tInterval;
	CTimeSpan  m_tExecution[2];
	CStringArray  m_szSources;
	CStringArray  m_szFilters;

	// Operations
public:
	VOID SetFileName(LPCTSTR pszFileName);
	CString GetFileName() CONST;
	VOID SetSources(CONST CStringArray &szSources);
	INT GetSources(CStringArray &szSources) CONST;
	VOID SetOptions(UINT nOptions);
	UINT GetOptions() CONST;
	VOID SetFormatting(UINT nOptions);
	UINT GetFormatting() CONST;
	VOID SetGapInterval(CONST CTimeSpan &tInterval);
	CTimeSpan GetGapInterval() CONST;
	VOID SetUpdateInterval(UINT nInterval);
	UINT GetUpdateInterval() CONST;

	BOOL SetStartTime(CONST CTimeKey &tTime);
	CTimeKey GetStartTime() CONST;
	BOOL SetStopTime(CONST CTimeKey &tTime);
	CTimeKey GetStopTime() CONST;
	BOOL SetStopSize(DWORDLONG dwSize);
	DWORDLONG GetStopSize() CONST;
	BOOL SetDeniedExecutionTime(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime);
	BOOL GetDeniedExecutionTime(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;
	BOOL SetFilters(CONST CStringArray &szTags);
	INT GetFilters(CStringArray &szTags) CONST;
	BOOL SetFilePrefix(LPCTSTR pszPrefix);
	CString GetFilePrefix() CONST;
	BOOL SetFileExtension(LPCTSTR pszExtension);
	CString GetFileExtension() CONST;

	VOID Copy(CONST CHistoryFileExtractionProfileInfo *pProfileInfo);
	BOOL Compare(CONST CHistoryFileExtractionProfileInfo *pProfileInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHistoryFileExtractionProfiles

class AFX_EXT_CLASS CHistoryFileExtractionProfiles : public CMutexArray
{
	// Construction
public:
	CHistoryFileExtractionProfiles();
	~CHistoryFileExtractionProfiles();

	// Attributes
public:

	// Operations
public:
	INT Add(CHistoryFileExtractionProfileInfo *pProfileInfo);

	INT Find(LPCTSTR pszName) CONST;
	INT Enum(CStringArray &szNames) CONST;

	CHistoryFileExtractionProfileInfo *GetAt(INT nIndex) CONST;
	CHistoryFileExtractionProfileInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CHistoryFileExtractionProfiles *pProfiles);
	BOOL Compare(CONST CHistoryFileExtractionProfiles *pProfiles) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHistoryFile

// Specify the history file types
#define HISTORYFILE_TYPE_ARCHIVE   0
#define HISTORYFILE_TYPE_RETRIEVE   1
// Specify the history file retrieval codes
#define HISTORYFILE_SUCCESS   (1<<0)
#define HISTORYFILE_TMUNIT   (1<<1)
#define HISTORYFILE_TCUNIT   (1<<2)
#define HISTORYFILE_TMPARAMETERS   (1<<3)
#define HISTORYFILE_TCPARAMETERS   (1<<4)
#define HISTORYFILE_SYNCHRONIZE   (1<<5)
#define HISTORYFILE_BUFFERING   (1<<6)
#define HISTORYFILE_ERROR   (1<<7)
#define HISTORYFILE_OPEN_FAILURE   (1<<8)
#define HISTORYFILE_WRITE_FAILURE   (1<<9)
#define HISTORYFILE_READ_FAILURE   (1<<10)
#define HISTORYFILE_DATA_NONE   (1<<11)
#define HISTORYFILE_DATA_MORE   (1<<12)
// Specify the default history file settings
#define HISTORYFILE_DEFAULT_UPDATEINTERVAL   1000

class AFX_EXT_CLASS CHistoryFile : public CLogFile
{
	// Construction
public:
	CHistoryFile();
	~CHistoryFile();

	// Attributes
private:
	typedef struct tagHISTORYDATAHEADER {
		BOOL  bUpdate;
		WORD  wInterval;
		WORD  wSequence;
		DWORDLONG  fPosition[3];
	} HISTORYDATAHEADER, *PHISTORYDATAHEADER, *LPHISTORYDATAHEADER;
protected:
	WORD  m_wInterval;
	WORD  m_wSequence;
	FILETIME  m_tFile;
	CTimeKey  m_tRetrieval;
	DWORDLONG  m_fArchivePosition;
	DWORDLONG  m_fRetrievePosition;
	BOOL  m_bFirstAccess;
protected:
	BOOL  m_bBuffering;
	BOOL  m_bBufferData;
	CPtrArray  m_pBufferData;
	CTimeTagArray  m_tBufferData;

	// Operations
public:
	UINT Open(LPCTSTR pszFileName, LPCTSTR pszSpacecraft, UINT nType, UINT nFlags, BOOL bWait = FALSE);
	BOOL Reset();
	VOID Close();

	UINT Write(CONST CTMEnvironment *pTMEnvironment);
	UINT Write(CONST CTCEnvironment *pTCEnvironment);
	UINT Read(CTimeKey &tTimeKey, CTMEnvironment *pTMEnvironment);
	UINT Read(CTimeKey &tTimeKey, CTCEnvironment *pTCEnvironment);
	UINT ReadNext(CTimeKey &tTimeKey, CONST CTimeSpan &tInterval, CTMEnvironment *pTMEnvironment);
	UINT ReadNext(CTimeKey &tTimeKey, CTCEnvironment *pTCEnvironment);
	UINT ReadPrev(CTimeKey &tTimeKey, CONST CTimeSpan &tInterval, CTMEnvironment *pTMEnvironment);

	BOOL Rename(LPCTSTR pszFileName, LPCTSTR pszNewFileName, BOOL bHide = FALSE);
	BOOL Remove(LPCTSTR pszFileName);

	BOOL SetUpdateInterval(WORD wInterval);
	BOOL GetUpdateInterval(WORD &wInterval) CONST;

	BOOL IsBufferEmpty() CONST;

protected:
	BOOL DoBackup(CONST CTMEnvironment *pTMEnvironment, DWORDLONG dwSize) CONST;
	BOOL DoBackup(CONST CTCEnvironment *pTCEnvironment, DWORDLONG dwSize) CONST;

private:
	BOOL TestDirectory(LPCTSTR pszFileName) CONST;

	BOOL CheckSecurity(LPCTSTR pszFileName) CONST;

	BOOL SetDataHeader(CONST PHISTORYDATAHEADER pDataHeader, CByteArray &nData) CONST;
	BOOL GetDataHeader(CONST CByteArray &nData, PHISTORYDATAHEADER pDataHeader) CONST;

	VOID ResetBuffer();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHistoryStoreFile

class AFX_EXT_CLASS CHistoryStoreFile : public CHistoryFile
{
	// Construction
public:
	CHistoryStoreFile();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName[2];
		INT  cbTempName;
		INT  cbDirectory;
		WORD  wUpdates;
		UINT  nOptions;
		UINT  nRetries[2];
		TIMEKEY  tStartTime[2];
		TIMEKEY  tStopTime[2];
		TIMEKEY  tBackupTime;
		TIMEKEY  tBackupStartTime;
		TIMEKEY  tBackupStopTime;
		TIMEKEY  tBackupInterval;
		DWORDLONG  dwBackupSize;
		DWORDLONG  dwFileSize;
	} DATA, *PDATA, *LPDATA;
private:
	WORD  m_wUpdates;
	UINT  m_nOptions;
	UINT  m_nErrorCode;
	UINT  m_nRetries[2];
	CString  m_szName[2];
	CString  m_szTempName;
	CString  m_szDirectory;
	CTimeKey  m_tStartTime;
	CTimeKey  m_tStopTime;
	CTimeKey  m_tBackupTime;
	CTimeSpan  m_tBackupStartTime;
	CTimeSpan  m_tBackupStopTime;
	CTimeSpan  m_tBackupInterval;
	CTimeSpan  m_tDailyStartTime;
	CTimeSpan  m_tDailyStopTime;
	DWORDLONG  m_dwBackupSize;
	DWORDLONG  m_dwFileSize;
private:
	CHistoryFile  m_cBackupFile;

	// Operations
public:
	UINT Open(LPCTSTR pszFileName, LPCTSTR pszSpacecraft, UINT nType, UINT nFlags, BOOL bWait = FALSE);
	VOID Close();

	VOID SetFileName(LPCTSTR pszFileName);
	CString GetFileName() CONST;
	VOID SetSecondaryFileName(LPCTSTR pszFileName);
	CString GetSecondaryFileName() CONST;

	VOID SetOptions(UINT nOptions);
	UINT GetOptions() CONST;
	VOID SetPeriod(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime);
	BOOL GetPeriod(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	VOID SetDailyPeriod(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime);
	BOOL GetDailyPeriod(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;
	VOID SetFileSize(DWORDLONG dwSize);
	DWORDLONG GetFileSize() CONST;
	VOID SetUpdateInterval(WORD wInterval);
	WORD GetUpdateInterval() CONST;

	VOID SetBackupFileName(LPCTSTR pszFileName);
	CString GetBackupFileName() CONST;
	VOID SetBackupDirectory(LPCTSTR pszDirectory);
	CString GetBackupDirectory() CONST;
	VOID SetBackupSize(DWORDLONG dwSize);
	DWORDLONG GetBackupSize() CONST;
	VOID SetBackupTime(CONST CTimeKey &tTime);
	BOOL GetBackupTime(CTimeKey &tTime) CONST;
	VOID SetBackupDailyPeriod(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime);
	BOOL GetBackupDailyPeriod(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;
	VOID SetBackupRetryInfo(UINT nRetries, CONST CTimeSpan &tInterval);
	BOOL GetBackupRetryInfo(UINT &nRetries, CTimeSpan &tInterval) CONST;
	VOID SetBackupRetryCount(UINT nCount);
	UINT GetBackupRetryCount() CONST;

	VOID SetErrorCode(UINT nCode);
	UINT GetErrorCode() CONST;

	UINT Update(LPCTSTR pszSpacecraft, UINT nType, CONST CTMEnvironment *pTMEnvironment, BOOL bBackup = FALSE);
	UINT Update(LPCTSTR pszSpacecraft, UINT nType, CONST CTCEnvironment *pTCEnvironment, BOOL bBackup = FALSE);
	UINT Update(LPCTSTR pszSpacecraft, UINT nType, BOOL bBackup = FALSE, BOOL bFlush = FALSE);

	VOID Copy(CONST CHistoryStoreFile *pFile);
	BOOL Compare(CONST CHistoryStoreFile *pFile) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	UINT DoBackup(LPCTSTR pszSpacecraft, UINT nType, CONST CTMEnvironment *pTMEnvironment, UINT nCode);
	UINT DoBackup(LPCTSTR pszSpacecraft, UINT nType, CONST CTCEnvironment *pTCEnvironment, UINT nCode);
	BOOL DoBackup(CONST CTMEnvironment *pTMEnvironment, BOOL bCheck) CONST;
	BOOL DoBackup(CONST CTCEnvironment *pTCEnvironment, BOOL bCheck) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHistoryStoreFiles

class AFX_EXT_CLASS CHistoryStoreFiles : public CPtrArray
{
	// Construction
public:
	CHistoryStoreFiles();
	~CHistoryStoreFiles();

	// Attributes
public:

	// Operations
public:
	INT Add(CHistoryStoreFile *pFile);

	INT Find(LPCTSTR pszFileName) CONST;

	CHistoryStoreFile *GetAt(INT nIndex) CONST;
	CHistoryStoreFile *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CHistoryStoreFiles *pFiles);
	BOOL Compare(CONST CHistoryStoreFiles *pFiles) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszFileName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHistoryStoreOptionInfo

// Specify the history store option types
#define HISTORYSTOREOPTION_TYPE_NONE   0
#define HISTORYSTOREOPTION_TYPE_TMPACKET   (1<<0)
#define HISTORYSTOREOPTION_TYPE_TMPARAMETER   (1<<1)

class AFX_EXT_CLASS CHistoryStoreOptionInfo : public CObject
{
	// Construction
public:
	CHistoryStoreOptionInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbTag;
		UINT  nType;
		TIMEKEY  tRetention;
	} DATA, *PDATA, *LPDATA;
private:
	UINT  m_nType;
	CString  m_szTag;
	CTimeSpan  m_tRetention;

	// Operations
public:
	VOID SetType(UINT nType);
	UINT GetType() CONST;
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetRetention(CONST CTimeSpan &tRetention);
	CTimeSpan GetRetention() CONST;

	VOID Copy(CONST CHistoryStoreOptionInfo *pOption);
	BOOL Compare(CONST CHistoryStoreOptionInfo *pOption) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHistoryStoreOptions

class AFX_EXT_CLASS CHistoryStoreOptions : public CPtrArray
{
	// Construction
public:
	CHistoryStoreOptions();
	~CHistoryStoreOptions();

	// Attributes
public:

	// Operations
public:
	INT Add(CHistoryStoreOptionInfo *pOption);

	INT Find(UINT nType, LPCTSTR pszTag) CONST;

	CHistoryStoreOptionInfo *GetAt(INT nIndex) CONST;
	CHistoryStoreOptionInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CHistoryStoreOptions *pOptions);
	BOOL Compare(CONST CHistoryStoreOptions *pOptions) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(UINT nType, LPCTSTR pszTag, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHistoryStore

// Specify the history store types
#define HISTORYSTORE_TYPE_TM   0
#define HISTORYSTORE_TYPE_TC   1
// Specify the history store options
#define HISTORYSTORE_OPTION_NONE   0
#define HISTORYSTORE_OPTION_USE   (1<<0)
#define HISTORYSTORE_OPTION_DAILYUSE   (1<<1)
#define HISTORYSTORE_OPTION_LIMITEDUSE   (1<<2)
#define HISTORYSTORE_OPTION_SECONDARY   (1<<3)
#define HISTORYSTORE_OPTION_AUDITFAILURES   (1<<4)
#define HISTORYSTORE_OPTION_SHOWSTATUS   (1<<5)
#define HISTORYSTORE_OPTION_CYCLIC   (1<<6)
#define HISTORYSTORE_OPTION_NONCYCLIC   (1<<7)
#define HISTORYSTORE_OPTION_FULLUPDATES   (1<<8)
#define HISTORYSTORE_OPTION_UNLIMITEDSIZE   (1<<9)
#define HISTORYSTORE_OPTION_LIMITEDSIZE   (1<<10)
#define HISTORYSTORE_OPTION_COMPRESSION   (1<<11)
#define HISTORYSTORE_OPTION_ANYFILES   (1<<12)
#define HISTORYSTORE_OPTION_TIMETAGGEDFILES   (1<<13)
#define HISTORYSTORE_OPTION_ENUMERATEDFILES   (1<<14)
#define HISTORYSTORE_OPTION_BACKUP   (1<<15)
#define HISTORYSTORE_OPTION_BACKUPSIMPLE   (1<<16)
#define HISTORYSTORE_OPTION_BACKUPTIMETAGGED   (1<<17)
#define HISTORYSTORE_OPTION_BACKUPENUMERATED   (1<<18)
#define HISTORYSTORE_OPTION_BACKUPBYDEFAULT   (1<<19)
#define HISTORYSTORE_OPTION_BACKUPBYSIZE   (1<<20)
#define HISTORYSTORE_OPTION_BACKUPDAILY   (1<<21)
#define HISTORYSTORE_OPTION_BACKUPTIME   (1<<22)
#define HISTORYSTORE_OPTION_BACKUPPROTECTEDDISK   (1<<23)
#define HISTORYSTORE_OPTION_BACKUPEMPTYDISK   (1<<24)
#define HISTORYSTORE_OPTION_BACKUPRETRIES   (1<<25)
#define HISTORYSTORE_OPTION_BACKUPAUDITFAILURES   (1<<26)
// Specify the history store error codes
#define HISTORYSTORE_SUCCESS   0
#define HISTORYSTORE_FAILURE   (1<<0)
#define HISTORYSTORE_FILEOPEN_FAILURE   (1<<1)
#define HISTORYSTORE_FILEUPDATE_FAILURE   (1<<2)
#define HISTORYSTORE_FILECLOSE_FAILURE   (1<<3)
#define HISTORYSTORE_SECONDARY_FAILURE   (1<<4)
#define HISTORYSTORE_BACKUP_FAILURE   (1<<5)
// Specify the history store informational code
#define HISTORYSTORE_SECONDARY_USE   (1<<0)
#define HISTORYSTORE_DATA_BUFFERED   (1<<1)
#define HISTORYSTORE_DATA_LOST   (1<<2)
#define HISTORYSTORE_BACKUP   (1<<3)

class AFX_EXT_CLASS CHistoryStore : public CObject
{
	// Construction
public:
	CHistoryStore();
	~CHistoryStore();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbFiles[2];
		INT  cbSpacecraft;
		INT  cbBrowseOptions;
		INT  cbBrowseDirectories;
		INT  cbDefaultFiles[2];
		INT  cbOptions;
	} DATA, *PDATA, *LPDATA;
private:
	UINT  m_nType;
	CString  m_szSpacecraft;
	CString  m_szDefaultFiles[2];
	CUIntArray  m_nBrowseOptions;
	CStringArray  m_szBrowseDirectories;
	CHistoryStoreFiles  m_pFiles[2];
	CHistoryStoreOptions  m_pOptions;
private:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	BOOL Open(LPCTSTR pszSpacecraft, UINT nType);
	VOID Close();

	BOOL SetHistoryFiles(UINT nType, CONST CHistoryStoreFiles &pFiles);
	INT GetHistoryFiles(UINT nType, CHistoryStoreFiles &pFiles) CONST;
	BOOL SetDefaultHistoryFile(UINT nType, CONST CHistoryStoreFile &cFile);
	BOOL GetDefaultHistoryFile(UINT nType, CHistoryStoreFile &cFile) CONST;
	BOOL SetOptions(CONST CHistoryStoreOptions &pOptions);
	BOOL GetOptions(CHistoryStoreOptions &pOptions) CONST;
	BOOL SetBrowseOptions(CONST CUIntArray &nOptions, CONST CStringArray &szDirectories);
	BOOL GetBrowseOptions(CUIntArray &nOptions, CStringArray &szDirectories) CONST;

	INT Update(CONST CTMEnvironment *pTMEnvironment, CHistoryStoreFiles &pFiles, CUIntArray &nErrors);
	INT Update(CONST CTCEnvironment *pTCEnvironment, CHistoryStoreFiles &pFiles, CUIntArray &nErrors);
	INT Update(CHistoryStoreFiles &pFiles, CUIntArray &nErrors);

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL CheckHistoryFile(LPCTSTR pszFileName) CONST;
	BOOL CheckHistoryFile(LPCTSTR pszFileName, UINT nOption, CHistoryStoreFile *pFile) CONST;

	BOOL Lock();
	BOOL Unlock();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHistoryTMProcessEngine

class AFX_EXT_CLASS CHistoryTMProcessEngine : public CTMProcessEngine
{
	// Construction
public:

	// Attributes
private:
	CString  m_szFileName;
	CHistoryFile  m_cFile;

	// Operations
public:
	BOOL Open(CONST CDatabaseEngine *pDatabase, LPCTSTR pszName, LPCTSTR pszFileName, CTMEnvironment *pTMEnvironment);
	VOID Close();

	UINT ProcessTMData(CONST CDatabaseEngine *pDatabase, CTMEnvironment *pTMEnvironment, CTimeKey &tTimeKey);
	UINT ReplayTMData(CONST CDatabaseEngine *pDatabase, CTMEnvironment *pTMEnvironment, CTimeKey &tTimeKey, CONST CTimeSpan &tInterval);
	UINT RewindTMData(CONST CDatabaseEngine *pDatabase, CTMEnvironment *pTMEnvironment, CTimeKey &tTimeKey, CONST CTimeSpan &tInterval);

	CString GetFileName() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHistoryTCProcessEngine

class AFX_EXT_CLASS CHistoryTCProcessEngine : public CTCProcessEngine
{
	// Construction
public:

	// Attributes
private:
	CString  m_szFileName;
	CHistoryFile  m_cFile;

	// Operations
public:
	BOOL Open(CONST CDatabaseEngine *pDatabase, LPCTSTR pszName, LPCTSTR pszFileName, CTCEnvironment *pTCEnvironment);
	VOID Close();

	UINT ProcessTCData(CONST CDatabaseEngine *pDatabase, CTCEnvironment *pTCEnvironment, CTimeKey &tTimeKey);
	UINT ReplayTCData(CONST CDatabaseEngine *pDatabase, CTCEnvironment *pTCEnvironment, CTimeKey &tTimeKey);

	CString GetFileName() CONST;
};

/////////////////////////////////////////////////////////////////////////////


#endif // __ARCHIVE_H__
