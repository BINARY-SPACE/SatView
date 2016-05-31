// TC.H : Telecommand Data Processing Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the telecommand data processing related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2007/04/23 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __TC_H__
#define __TC_H__

#include "displays.h"


/////////////////////////////////////////////////////////////////////////////
// CTCServiceLock

class CTCServiceLock
{
	// Construction
public:
	CTCServiceLock(CONST CDisplayWnd *pDisplayWnd);
	~CTCServiceLock();

	// Attributes
private:
	CDisplayLockable  *m_pLockable;

	// Operations
public:
	VOID Release();

private:
	BOOL Lock();
	BOOL Unlock();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCChainLock

class CTCChainLock
{
	// Construction
public:
	CTCChainLock(CONST CThread *pThread);
	~CTCChainLock();

	// Attributes
private:
	CThread  *m_pThread;

	// Operations
public:
	VOID Release();

private:
	BOOL Lock();
	BOOL Unlock();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCInterlock

// Specify the telecommand interlock source types
#define TCINTERLOCK_SOURCETYPE_NONE   0
#define TCINTERLOCK_SOURCETYPE_MANUALSTACK   TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK
#define TCINTERLOCK_SOURCETYPE_AUTOMATICSTACK   TCSERVICE_COMMANDSOURCETYPE_AUTOMATICSTACK
#define TCINTERLOCK_SOURCETYPE_PROCEDURESMONITOR   TCSERVICE_COMMANDSOURCETYPE_PROCEDURESMONITOR
#ifndef RC_INVOKED
#define TCINTERLOCK_SOURCETYPE_ALLSOURCES   (TCINTERLOCK_SOURCETYPE_MANUALSTACK | TCINTERLOCK_SOURCETYPE_AUTOMATICSTACK | TCINTERLOCK_SOURCETYPE_PROCEDURESMONITOR)
#endif
// Specify the telecommand interlock scopes
#define TCINTERLOCK_SCOPE_NONE   0
#define TCINTERLOCK_SCOPE_GLOBAL   1
#define TCINTERLOCK_SCOPE_LOCAL   2
#define TCINTERLOCK_SCOPE_LOCALNOWAIT   3
#define TCINTERLOCK_SCOPE_GLOBALSUBSYSTEM   4
#define TCINTERLOCK_SCOPE_LOCALSUBSYSTEM   5
#define TCINTERLOCK_SCOPE_LOCALSUBSYSTEMNOWAIT   6
#define TCINTERLOCK_SCOPE_COMMANDS   7
#define MAKETCINTERLOCKSCOPECODE(nScope,nAPID)   (nScope | (nAPID << 4))
#define TCINTERLOCKSCOPEFROMCODE(nCode)   (nCode & 0xF)
#define TCINTERLOCKAPIDFROMCODE(nCode)   (nCode >> 4)
// Specify the telecommand interlock stages
#define TCINTERLOCK_STAGE_NONE   0
#define TCINTERLOCK_STAGE_RECEPTION   1
#define TCINTERLOCK_STAGE_TRANSMISSION   2
#define TCINTERLOCK_STAGE_ACCEPTANCE   3
#define TCINTERLOCK_STAGE_START   4
#define TCINTERLOCK_STAGE_PROGRESS   5
#define TCINTERLOCK_STAGE_COMPLETION   6
// Specify the telecommand interlock states
#define TCINTERLOCK_STATE_NONE   0
#define TCINTERLOCK_STATE_IDLE   1
#define TCINTERLOCK_STATE_PENDING   2
#define TCINTERLOCK_STATE_SUCCESS   3
#define TCINTERLOCK_STATE_FAILURE   4

class CTCInterlock : public CComputerToken
{
	// Construction
public:
	CTCInterlock();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbComputerName;
		UINT  nSourceType;
		UINT  nScope;
		UINT  nStage;
		UINT  nState;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	UINT  m_nSourceType;
	UINT  m_nScope;
	UINT  m_nStage;
	UINT  m_nState;
private:
	CUIntArray  m_nReleaseIDs;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetSourceType(UINT nType);
	UINT GetSourceType() CONST;
	VOID SetScope(UINT nScope);
	UINT GetScope() CONST;
	VOID SetStage(UINT nStage);
	UINT GetStage() CONST;
	VOID SetState(UINT nState);
	UINT GetState() CONST;

	VOID SetReleaseIDs(CONST CUIntArray &nIDs);
	INT GetReleaseIDs(CUIntArray &nIDs) CONST;

	BOOL IsAutomatic() CONST;

	VOID Copy(CONST CTCInterlock *pInterlock);
	BOOL Compare(CONST CTCInterlock *pInterlock) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	CString ConstructDefaultName(LPCTSTR pszComputerName, UINT nSourceType, UINT nScope, UINT nStage) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCInterlocks

class CTCInterlocks : public CPtrArray
{
	// Construction
public:
	CTCInterlocks();
	~CTCInterlocks();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCInterlock *pInterlock);

	INT Find(UINT nSourceType, LPCTSTR pszName) CONST;
	INT Find(LPCTSTR pszComputerName, UINT nSourceType, LPCTSTR pszName) CONST;
	INT Find(CONST CTCInterlock *pInterlock) CONST;

	CTCInterlock *GetAt(INT nIndex) CONST;
	CTCInterlock *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCInterlocks *pInterlocks);
	BOOL Compare(CONST CTCInterlocks *pInterlocks) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszComputerName, UINT nSourceType, LPCTSTR pszName, UINT nScope, UINT nStage, BOOL bInsert = FALSE) CONST;

	CString ConstructSearchName(LPCTSTR pszComputerName, UINT nSourceType, LPCTSTR pszName, UINT nScope, UINT nStage) CONST;
	CString ConstructSearchName(CONST CTCInterlock *pInterlock) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCItem

// Specify the telecommand item types
#define TCITEM_TYPE_NONE   0
#define TCITEM_TYPE_FUNCTION   1
#define TCITEM_TYPE_SEQUENCE   2
#define TCITEM_TYPE_PROCEDURE   3
// Specify the telecommand item source types
#define TCITEM_SOURCETYPE_NONE   0
#define TCITEM_SOURCETYPE_MANUALSTACK   TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK
#define TCITEM_SOURCETYPE_AUTOMATICSTACK   TCSERVICE_COMMANDSOURCETYPE_AUTOMATICSTACK
#define TCITEM_SOURCETYPE_PROCEDURESMONITOR   TCSERVICE_COMMANDSOURCETYPE_PROCEDURESMONITOR
#ifndef RC_INVOKED
#define TCITEM_SOURCETYPE_ALLSOURCES   (TCITEM_SOURCETYPE_MANUALSTACK | TCITEM_SOURCETYPE_AUTOMATICSTACK | TCITEM_SOURCETYPE_PROCEDURESMONITOR)
#endif
// Specify the telecommand item flags
#define TCITEM_CHECKFLAG_OVERRIDEPTV   TCSERVICE_COMMANDSOURCEFLAGS_PTV_OVERRIDE
#define TCITEM_CHECKFLAG_OVERRIDEPEV   TCSERVICE_COMMANDSOURCEFLAGS_PEV_OVERRIDE
#define TCITEM_CHECKFLAG_OVERRIDECEV   TCSERVICE_COMMANDSOURCEFLAGS_CEV_OVERRIDE
#define TCITEM_CHECKFLAG_DISABLEPTV   TCSERVICE_COMMANDSOURCEFLAGS_PTV_DISABLE
#define TCITEM_CHECKFLAG_DISABLEPEV   TCSERVICE_COMMANDSOURCEFLAGS_PEV_DISABLE
#define TCITEM_CHECKFLAG_DISABLECEV   TCSERVICE_COMMANDSOURCEFLAGS_CEV_DISABLE
#define TCITEM_CHECKFLAG_PREAUTHORIZED   TCSERVICE_COMMANDSOURCEFLAGS_PREAUTHORIZED
#define TCITEM_CHECKFLAG_AUTHORIZEABLE   TCSERVICE_COMMANDSOURCEFLAGS_AUTHORIZEABLE
#define TCITEM_LINKAGEFLAG_GROUPED   (TCSERVICE_COMMANDSOURCEFLAGS_AUTHORIZEABLE<<1)
#define TCITEM_LINKAGEFLAG_BLOCKED   (TCSERVICE_COMMANDSOURCEFLAGS_AUTHORIZEABLE<<2)
#define TCITEM_RELEASEFLAG_AFTERBEGIN   (TCSERVICE_COMMANDSOURCEFLAGS_AUTHORIZEABLE<<3)
#define TCITEM_RELEASEFLAG_AFTERPREVIOUS   (TCSERVICE_COMMANDSOURCEFLAGS_AUTHORIZEABLE<<4)
#define TCITEM_EXECUTIONFLAG_AFTERBEGIN   (TCSERVICE_COMMANDSOURCEFLAGS_AUTHORIZEABLE<<5)
#define TCITEM_EXECUTIONFLAG_AFTERPREVIOUS   (TCSERVICE_COMMANDSOURCEFLAGS_AUTHORIZEABLE<<6)
#define TCITEM_EXECUTIONFLAG_IMMEDIATE   (TCSERVICE_COMMANDSOURCEFLAGS_AUTHORIZEABLE<<7)
#define TCITEM_EXECUTIONFLAG_TIMETAGGED   (TCSERVICE_COMMANDSOURCEFLAGS_AUTHORIZEABLE<<8)
#define TCITEM_EXECUTIONFLAG_1STSTEP   (TCSERVICE_COMMANDSOURCEFLAGS_AUTHORIZEABLE<<9)
#define TCITEM_EXECUTIONFLAG_2NDSTEP   (TCSERVICE_COMMANDSOURCEFLAGS_AUTHORIZEABLE<<10)
#define TCITEM_DUMPFLAG_SYNCHRONIZED   (TCSERVICE_COMMANDSOURCEFLAGS_AUTHORIZEABLE<<11)
#define TCITEM_DUMPFLAG_NOTSYNCHRONIZED   (TCSERVICE_COMMANDSOURCEFLAGS_AUTHORIZEABLE<<12)
#define TCITEM_ACKNOWLEDGEFLAG_ACCEPTANCE   (TCSERVICE_COMMANDSOURCEFLAGS_AUTHORIZEABLE<<13)
#define TCITEM_ACKNOWLEDGEFLAG_START   (TCSERVICE_COMMANDSOURCEFLAGS_AUTHORIZEABLE<<14)
#define TCITEM_ACKNOWLEDGEFLAG_PROGRESS   (TCSERVICE_COMMANDSOURCEFLAGS_AUTHORIZEABLE<<15)
#define TCITEM_ACKNOWLEDGEFLAG_COMPLETION   (TCSERVICE_COMMANDSOURCEFLAGS_AUTHORIZEABLE<<16)
#define TCITEM_ACKNOWLEDGEFLAG_ALL   (TCSERVICE_COMMANDSOURCEFLAGS_AUTHORIZEABLE<<17)
// Specify the telecommand item authorization status
#define TCITEM_AUTHORIZATIONSTATUS_NONE   0
#define TCITEM_AUTHORIZATIONSTATUS_GRANTED   1
#define TCITEM_AUTHORIZATIONSTATUS_DENIED   2
// Specify the telecommand item check results
#define TCITEM_RESULT_NONE   0
#define TCITEM_RESULT_PTV_GO   (1<<0)
#define TCITEM_RESULT_PTV_WAIT   (1<<1)
#define TCITEM_RESULT_PTV_FAIL   (1<<2)
#define TCITEM_RESULT_PEV_GO   (1<<3)
#define TCITEM_RESULT_PEV_NOGO   (1<<4)
#define TCITEM_RESULT_CEV_IDLE   (1<<5)
#define TCITEM_RESULT_CEV_PENDING   (1<<6)
#define TCITEM_RESULT_CEV_PASSED   (1<<7)
#define TCITEM_RESULT_CEV_FAILED   (1<<8)
#define TCITEM_RESULT_CEV_UNKNOWN   (1<<9)
#define TCITEM_RESULT_CEV_UNVERIFIED   (1<<10)
#define TCITEM_FAILURE_PTV_UPLINK   (1<<11)
#define TCITEM_FAILURE_PTV_RELEASETIMEWINDOW   (1<<12)
#define TCITEM_FAILURE_PTV_EXECUTIONTIME   (1<<13)
#define TCITEM_FAILURE_PTV_INTERLOCK   (1<<14)
#define TCITEM_FAILURE_PTV_SUBSYSTEM   (1<<15)
#define TCITEM_FAILURE_PTV_ONBOARDBUFFER   (1<<16)
#define TCITEM_FAILURE_PTV_ENCODING   (1<<17)
#define TCITEM_FAILURE_PEV_TELEMETRY   (1<<18)
#define TCITEM_FAILURE_PEV_CORRELATION   (1<<19)
#define TCITEM_FAILURE_PEV_2NDSTEP   (1<<20)
#define TCITEM_FAILURE_PEV_PARAMETERS   (1<<21)
#define TCITEM_FAILURE_CEV_PARAMETERS   (1<<22)
// Specify the telecommand item status flags
#define TCITEM_STATUS_NONE   0
#define TCITEM_STATUS_ONSTACK   1
#define TCITEM_STATUS_ARMED   2
#define TCITEM_STATUS_DISPATCHED   3
#define TCITEM_STATUS_RELEASED   4
#define TCITEM_STATUS_NOTRELEASED   5
#define TCITEM_STATUS_FAILEDRELEASE   6
#define TCITEM_STATUS_SENT   7
#define TCITEM_STATUS_FAILEDSEND   8
#define TCITEM_STATUS_UPLINKED   9
#define TCITEM_STATUS_FAILEDUPLINK   10
#define TCITEM_STATUS_EXECUTED   TCITEM_STATUS_RELEASED
#define TCITEM_STATUS_NOTEXECUTED   TCITEM_STATUS_NOTRELEASED
#define TCITEM_STATUS_FAILEDEXECUTION   TCITEM_STATUS_FAILEDRELEASE

class CTCItem : public CComputerToken, public CDatabaseTCFunction
{
	// Construction
public:
	CTCItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbPacket;
		INT  cbFunction;
		INT  cbParameters;
		INT  cbProperties;
		INT  cbPacketData;
		INT  cbMemoryPatch;
		INT  cbComputerName;
		INT  cbReleaseBlock;
		INT  cbBlockedItems;
		INT  cbMembership[2];
		INT  cbInterlock[2][2];
		INT  cbVerificationStep;
		INT  cbVerificationThread;
		INT  cbVerificationProcedure;
		INT  cbVerificationModuleFileName;
		INT  cbVerificationStageIDs[4];
		INT  cbVerificationStageTimeWindows[3];
		INT  cbVerificationStageParameters;
		INT  cbVerificationStageStates[2];
		INT  cbVerificationStageClosures;
		TIMETAG  tKeyID;
		TIMETAG  tLoadTime;
		TIMETAG  tArmTime;
		TIMETAG  tDispatchTime;
		TIMETAG  tExecutionTime;
		TIMETAG  tReleaseTime[3];
		TIMETAG  tTransmissionTime;
		TIMETAG  tVerificationTime;
		TIMETAG  tDownloadDumpTime;
		TIMETAG  tAcknowledgeTime;
		TIMEKEY  tReleaseTimeInterval;
		DWORD  dwReleaseTimeOffset[2];
		DWORD  dwExecutionTimeOffset;
		BOOL  bReleaseTimeOffset[2];
		BOOL  bExecutionTimeOffset;
		BOOL  bEarlierExecution;
		BOOL  bReleaseInterlock;
		BOOL  bExecutionOBRT;
		UINT  nExecutionOBRT;
		UINT  nExecutionMode;
		UINT  nReleaseBlockID;
		UINT  nMembershipSize;
		UINT  nMembershipID;
		UINT  nSourceType;
		UINT  nQueuedSize;
		UINT  nResult;
		UINT  nStatus;
		UINT  nFlags;
		UINT  nType;
	} DATA, *PDATA, *LPDATA;
protected:
	CString  m_szName;
	CString  m_szReleaseBlock;
	CString  m_szInterlock[2];
	CString  m_szMembership[2];
	CString  m_szMemoryPatch;
	CString  m_szVerificationStep;
	CString  m_szVerificationThread;
	CString  m_szVerificationProcedure;
	CString  m_szVerificationModuleFileName;
	CTimeTag  m_tKeyID;
	CTimeTag  m_tLoadTime;
	CTimeTag  m_tArmTime;
	CTimeTag  m_tDispatchTime;
	CTimeTag  m_tExecutionTime;
	CTimeTag  m_tReleaseTime[3];
	CTimeTag  m_tTransmissionTime;
	CTimeTag  m_tVerificationTime;
	CTimeTag  m_tDownloadDumpTime;
	CTimeTag  m_tAcknowledgeTime;
	CTimeSpan  m_tReleaseTimeInterval;
	CByteArray  m_nProperties;
	CByteArray  m_nPacketData;
	CUIntArray  m_nReleaseIDs;
	CUIntArray  m_nVerificationStageIDs[4];
	CUIntArray  m_nVerificationStageStates[2];
	CStringArray  m_szVerificationStageParameters;
	CStringArray  m_szVerificationStageClosures;
	CTimeKeyArray  m_tVerificationStageTimeWindows[3];
	CTCInterlock  m_cInterlock[2];
	CDatabaseTCPacket  m_cPacket;
	CDatabaseTCParameters  m_pParameters;
	CDatabaseTCFunctions  m_pBlockedItems;
	HINSTANCE  m_hVerificationModule;
	HANDLE  m_hVerificationResult[2];
	DWORD  m_dwReleaseTimeOffset[2];
	DWORD  m_dwExecutionTimeOffset;
	BOOL  m_bReleaseTimeOffset[2];
	BOOL  m_bExecutionTimeOffset;
	BOOL  m_bEarlierExecution;
	BOOL  m_bReleaseInterlock;
	BOOL  m_bExecutionOBRT;
	UINT  m_nExecutionOBRT;
	UINT  m_nExecutionMode;
	UINT  m_nReleaseBlockID;
	UINT  m_nVerificationID;
	UINT  m_nAuthorizationStatus;
	UINT  m_nMembershipSize;
	UINT  m_nMembershipID;
	UINT  m_nSourceType;
	UINT  m_nQueuedSize;
	UINT  m_nResult;
	UINT  m_nStatus;
	UINT  m_nFlags;
	UINT  m_nType;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetSourceType(UINT nType);
	UINT GetSourceType() CONST;
	VOID SetType(UINT nType);
	UINT GetType() CONST;
	VOID SetFlags(UINT nFlags);
	UINT GetFlags() CONST;
	VOID SetProperties(CONST CByteArray &nData);
	BOOL GetProperties(CByteArray &nData) CONST;
	BOOL SetTCPacket(CONST CDatabaseTCPacket *pPacket);
	BOOL SetTCPacket(CONST CByteArray &nData);
	BOOL GetTCPacket(CDatabaseTCPacket *pPacket) CONST;
	INT GetTCPacket(CByteArray &nData) CONST;
	VOID SetQueuedSize(UINT nSize);
	UINT GetQueuedSize() CONST;
	VOID SetMembership(LPCTSTR pszItem);
	CString GetMembership() CONST;
	VOID SetMembershipDescription(LPCTSTR pszDescription);
	CString GetMembershipDescription() CONST;
	BOOL SetMembershipParameters(CONST CDatabaseTCParameters &pParameters);
	INT GetMembershipParameters(CDatabaseTCParameters &pParameters) CONST;
	VOID SetMembershipID(UINT nID);
	UINT GetMembershipID() CONST;
	VOID SetMembershipSize(UINT nSize);
	UINT GetMembershipSize() CONST;
	VOID SetMemoryPatch(LPCTSTR pszPatch);
	CString GetMemoryPatch() CONST;
	VOID SetInterlock(LPCTSTR pszInterlock);
	VOID SetInterlock(CONST CTCInterlock *pInterlock);
	CString GetInterlock() CONST;
	BOOL GetInterlock(CTCInterlock *pInterlock) CONST;
	VOID SetReleaseInterlock(LPCTSTR pszInterlock, BOOL bSuccess = FALSE);
	VOID SetReleaseInterlock(CONST CTCInterlock *pInterlock);
	BOOL GetReleaseInterlock(CString &szInterlock, BOOL &bSuccess) CONST;
	BOOL GetReleaseInterlock(CTCInterlock *pInterlock) CONST;
	VOID SetReleaseBlock(LPCTSTR pszBlock);
	CString GetReleaseBlock() CONST;
	VOID SetReleaseBlockID(UINT nID);
	UINT GetReleaseBlockID() CONST;
	BOOL SetReleaseBlockedItems(CONST CDatabaseTCFunctions &pItems);
	INT GetReleaseBlockedItems(CDatabaseTCFunctions &pItems) CONST;
	VOID SetReleaseTimeWindow(CONST CTimeTag &tOpenTime);
	VOID SetReleaseTimeWindow(CONST CTimeTag &tOpenTime, CONST CTimeSpan &tInterval);
	VOID SetReleaseTimeWindow(CONST CTimeTag &tOpenTime, CONST CTimeTag &tCloseTime);
	VOID SetReleaseTimeWindow(DWORD dwOffset, BOOL bAfterDispatch = TRUE);
	VOID SetReleaseTimeWindow(DWORD dwOffset, CONST CTimeSpan &tInterval, BOOL bAfterDispatch);
	BOOL GetReleaseTimeWindow(CTimeTag &tOpenTime, CTimeSpan &tInterval) CONST;
	BOOL GetReleaseTimeWindow(CTimeTag &tOpenTime, CTimeTag &tCloseTime) CONST;
	BOOL GetReleaseTimeWindow(DWORD &dwOffset, CTimeSpan &tInterval, BOOL &bAfterDispatch) CONST;
	VOID SetReleaseIDs(CONST CUIntArray &nIDs);
	INT GetReleaseIDs(CUIntArray &nIDs) CONST;
	VOID SetExecutionTime(CONST CTimeTag &tTime);
	BOOL GetExecutionTime(CTimeTag &tTime) CONST;
	VOID SetExecutionTimeOffset();
	VOID SetExecutionTimeOffset(DWORD dwOffset, BOOL bEarlier = FALSE);
	BOOL GetExecutionTimeOffset(DWORD &dwOffset, BOOL &bEarlier) CONST;
	VOID SetExecutionOBRT();
	VOID SetExecutionOBRT(UINT nOBRT);
	BOOL GetExecutionOBRT(UINT &nOBRT) CONST;
	VOID SetExecutionMode(UINT nMode);
	UINT GetExecutionMode() CONST;
	VOID SetAuthorizationStatus(UINT nStatus);
	UINT GetAuthorizationStatus() CONST;
	VOID SetVerificationProcedure(LPCTSTR pszName);
	CString GetVerificationProcedure() CONST;
	VOID SetVerificationProcessID(INT nID = -1);
	INT GetVerificationProcessID() CONST;
	VOID SetVerificationThread(LPCTSTR pszThread);
	CString GetVerificationThread() CONST;
	VOID SetVerificationStep(LPCTSTR pszStep);
	CString GetVerificationStep() CONST;
	VOID SetVerificationModuleFileName(LPCTSTR pszFileName);
	CString GetVerificationModuleFileName() CONST;
	VOID SetVerificationModule(HINSTANCE hModule = NULL);
	HINSTANCE GetVerificationModule() CONST;
	VOID SetVerificationHandles(HANDLE hSuccess = NULL, HANDLE hFailure = NULL);
	BOOL GetVerificationHandles(HANDLE &hSuccess, HANDLE &hFailure) CONST;
	INT EnumVerificationStageIDs(CUIntArray &nStageIDs) CONST;
	VOID SetVerificationTimeWindow(UINT nStageID, CONST CTimeSpan &tStartDelay, CONST CTimeSpan &tTimeWindow, CONST CTimeSpan &tUncertainty);
	BOOL GetVerificationTimeWindow(UINT nStageID, CTimeSpan &tStartDelay, CTimeSpan &tTimeWindow, CTimeSpan &tUncertainty) CONST;
	CTimeSpan CalcVerificationTimeWindowOffset(UINT nStageID = 0, CONST CTimeSpan &tDefault = -1) CONST;
	CTimeSpan CalcVerificationTimeWindowSize(UINT nStageID = 0, CONST CTimeSpan &tDefault = -1) CONST;
	VOID SetVerificationStageState(UINT nStageID = 0, UINT nState = 0, UINT nReason = 0);
	BOOL GetVerificationStageState(UINT nStageID, UINT &nState, UINT &nReason) CONST;
	VOID SetVerificationStageParameters(UINT nStageID, CONST CStringArray &szParameters);
	INT GetVerificationStageParameters(UINT nStageID, CStringArray &szParameters) CONST;
	VOID SetVerificationStageClosure(UINT nStageID, LPCTSTR pszTag);
	CString GetVerificationStageClosure(UINT nStageID) CONST;

	VOID SetLoadTime(CONST CTimeTag &tTime);
	CTimeTag GetLoadTime() CONST;
	VOID SetArmTime(CONST CTimeTag &tTime);
	CTimeTag GetArmTime() CONST;
	VOID SetDispatchTime(CONST CTimeTag &tTime);
	CTimeTag GetDispatchTime() CONST;
	VOID SetReleaseTime(CONST CTimeTag &tTime);
	CTimeTag GetReleaseTime() CONST;
	VOID SetTransmissionTime(CONST CTimeTag &tTime);
	CTimeTag GetTransmissionTime() CONST;
	VOID SetVerificationTime(CONST CTimeTag &tTime);
	CTimeTag GetVerificationTime() CONST;
	VOID SetDumpTime(CONST CTimeTag &tTime);
	CTimeTag GetDumpTime() CONST;
	VOID SetAcknowledgeTime(CONST CTimeTag &tTime);
	CTimeTag GetAcknowledgeTime() CONST;

	VOID SetResult(UINT nResult);
	UINT GetResult() CONST;
	VOID SetStatus(UINT nStatus);
	UINT GetStatus() CONST;

	BOOL Copy(CONST CTCItem *pItem);
	BOOL Compare(CONST CTCItem *pItem) CONST;
	BOOL IsIdentical(CONST CTCItem *pItem) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bAll = FALSE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bAll = FALSE);

private:
	static VOID Initialize(CTCItem *pItem);

private:
	static TIMETAG  m_tLastKeyID;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCItems

class CTCItems : public CPtrArray
{
	// Construction
public:
	CTCItems();
	~CTCItems();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCItem *pItem);

	INT Find(CONST CTCItem *pItem) CONST;
	INT Find(LPCTSTR pszComputer, UINT nSourceType, LPCTSTR pszName, LPCTSTR pszMembership, UINT nMembershipID, ULONGLONG nFlags, CONST CTimeTag &tLoadTime) CONST;
	INT Find(LPCTSTR pszName, LPCTSTR pszMembership, UINT nMembershipID, ULONGLONG nFlags, CONST CTimeTag &tLoadTime) CONST;
	INT Find(LPCTSTR pszMembership, UINT nMembershipID, CONST CTimeTag &tLoadTime) CONST;
	INT Find(LPCTSTR pszMembership, CONST CTimeTag &tLoadTime) CONST;

	INT Collect(INT nIndex, CUIntArray &nItemIDs) CONST;
	INT Collect(INT nIndex, CPtrArray &pItems) CONST;
	INT Collect(INT nIndex, CTCItems &pItems) CONST;

	CTCItem *GetAt(INT nIndex) CONST;
	CTCItem *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCItems *pItems);
	BOOL Compare(CONST CTCItems *pItems) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bAll = FALSE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bAll = FALSE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueue

// Specify the telecommand on-board buffer queue flags
#define TCONBOARDBUFFERQUEUE_FLAG_NONE   0
#define TCONBOARDBUFFERQUEUE_FLAG_ALLOWSTATUSCHANGE   (1<<0)
#define TCONBOARDBUFFERQUEUE_FLAG_ALLOWDOWNLOADALL   (1<<1)
#define TCONBOARDBUFFERQUEUE_FLAG_ALLOWDOWNLOADBYRANGE   (1<<2)
#define TCONBOARDBUFFERQUEUE_FLAG_ALLOWDOWNLOADBYTIMERANGE   (1<<3)
#define TCONBOARDBUFFERQUEUE_FLAG_ALLOWDOWNLOADBYSUBSYSTEM   (1<<4)
#define TCONBOARDBUFFERQUEUE_FLAG_ALLOWDOWNLOADBYSEQUENCECOUNTER   (1<<5)
#define TCONBOARDBUFFERQUEUE_FLAG_ALLOWDELETEALL   (1<<6)
#define TCONBOARDBUFFERQUEUE_FLAG_ALLOWDELETEBYRANGE   (1<<7)
#define TCONBOARDBUFFERQUEUE_FLAG_ALLOWDELETEBYTIMERANGE   (1<<8)
#define TCONBOARDBUFFERQUEUE_FLAG_ALLOWDELETEBYSUBSYSTEM   (1<<9)
#define TCONBOARDBUFFERQUEUE_FLAG_ALLOWDELETEBYSEQUENCECOUNTER   (1<<10)
#define TCONBOARDBUFFERQUEUE_FLAG_SYNCHRONIZEBYDOWNLOAD   (1<<11)
#define TCONBOARDBUFFERQUEUE_FLAG_CLEARDOWNLOADSTATUS   (1<<12)
// Specify the telecommand on-board buffer queue status codes
#define TCONBOARDBUFFERQUEUE_STATUS_NONE   0
#define TCONBOARDBUFFERQUEUE_STATUS_ENABLED   (1<<0)
#define TCONBOARDBUFFERQUEUE_STATUS_DISABLED   (1<<1)
// Specify the telecommand on-board buffer queue alert types
#define TCONBOARDBUFFERQUEUE_ALERTTYPE_NONE   0
#define TCONBOARDBUFFERQUEUE_ALERTTYPE_INFORMATION   1
#define TCONBOARDBUFFERQUEUE_ALERTTYPE_WARNING   2
#define TCONBOARDBUFFERQUEUE_ALERTTYPE_ERROR   3
#define TCONBOARDBUFFERQUEUE_ALERTTYPE_ANY   (-1)

class CTCOnBoardBufferQueue : public CTCItems
{
	// Construction
public:
	CTCOnBoardBufferQueue();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbType;
		INT  cbUnit;
		INT  cbItems;
		INT  cbAlerts[3];
		UINT  nFlags;
		UINT  nAPID;
		UINT  nSubScheduleID;
		UINT  nLimit;
		UINT  nCount;
		UINT  nStatus;
		TIMETAG  tTime;
		TIMEKEY  tTimeout;
	} DATA, *PDATA, *LPDATA;
protected:
	CString  m_szName;
	CString  m_szType;
	CString  m_szUnit;
	CTimeTag  m_tTime;
	CTimeSpan  m_tTimeout;
	UINT  m_nFlags;
	UINT  m_nAPID;
	UINT  m_nSubScheduleID;
	UINT  m_nLimit;
	UINT  m_nCount;
	UINT  m_nStatus;
protected:
	CUIntArray  m_nAlertTypes;
	CUIntArray  m_nAlertMessages;
	CStringArray  m_szAlertMessages;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetType(LPCTSTR pszType);
	CString GetType() CONST;
	VOID SetFlags(UINT nFlags);
	UINT GetFlags() CONST;
	VOID SetAPID(UINT nAPID);
	UINT GetAPID() CONST;
	VOID SetSubScheduleID(UINT nSubScheduleID);
	UINT GetSubScheduleID() CONST;
	VOID SetLimit(UINT nLimit);
	UINT GetLimit() CONST;
	VOID SetCount(UINT nCount);
	UINT GetCount() CONST;
	VOID SetUnit(LPCTSTR pszUnit);
	CString GetUnit() CONST;
	VOID SetTimeout(CONST CTimeSpan &tTimeout);
	CTimeSpan GetTimeout() CONST;
	VOID SetUpdateTime(CONST CTimeTag &tTime);
	CTimeTag GetUpdateTime() CONST;
	VOID SetStatus(UINT nStatus);
	UINT GetStatus() CONST;

	BOOL Alert(UINT nType, UINT nMessage, LPCTSTR pszMessage, BOOL bOverwrite = TRUE);
	BOOL Alert(UINT nType, UINT nMessage = -1, BOOL bEnable = FALSE);
	UINT IsAlerted(UINT nMessage, CString &szMessage) CONST;
	UINT IsAlerted(UINT nMessage = -1) CONST;
	INT GetAlertCount(UINT nType) CONST;

	BOOL Copy(CONST CTCOnBoardBufferQueue *pQueue);
	BOOL Compare(CONST CTCOnBoardBufferQueue *pQueue) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueues

class CTCOnBoardBufferQueues : public CPtrArray
{
	// Construction
public:
	CTCOnBoardBufferQueues();
	~CTCOnBoardBufferQueues();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCOnBoardBufferQueue *pQueue);

	INT Find(LPCTSTR pszType, LPCTSTR pszName, UINT nSubScheduleID) CONST;

	CTCOnBoardBufferQueue *GetAt(INT nIndex) CONST;
	CTCOnBoardBufferQueue *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCOnBoardBufferQueues *pQueues);
	BOOL Compare(CONST CTCOnBoardBufferQueues *pQueues) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

protected:
	INT FindIndex(LPCTSTR pszType, LPCTSTR pszName, UINT nSubScheduleID, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCUplinkDevice

// Specify the telecommand uplink device schedule options
#define TELECOMMANDUPLINKDEVICE_SCHEDULE_ALWAYS   (1<<0)
#define TELECOMMANDUPLINKDEVICE_SCHEDULE_DAILY   (1<<1)
#define TELECOMMANDUPLINKDEVICE_SCHEDULE_INTERVAL   (1<<2)
#define TELECOMMANDUPLINKDEVICE_SCHEDULE_PERIODIC   (1<<3)
#define TELECOMMANDUPLINKDEVICE_SCHEDULE_DISABLED   (1<<4)
#define TELECOMMANDUPLINKDEVICE_SCHEDULE_AUDIT   (1<<5)
// Specify the telecommand uplink device backup options
#define TELECOMMANDUPLINKDEVICE_BACKUP_CONTINOUSLY  (1<<0)
#define TELECOMMANDUPLINKDEVICE_BACKUP_RETRIES   (1<<1)
#define TELECOMMANDUPLINKDEVICE_BACKUP_USEDEVICE   (1<<2)
#define TELECOMMANDUPLINKDEVICE_BACKUP_USEANYDEVICE   (1<<3)
#define TELECOMMANDUPLINKDEVICE_BACKUP_AUDITFAILURES   (1<<4)

class CTCUplinkDevice : public CIODevice
{
	// Constrution
public:
	CTCUplinkDevice();
	CTCUplinkDevice(CTCUplinkDevice *pDevice);

	// Attributes
protected:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbDevice;
		INT  cbBackupDevice;
		TIMEKEY  tScheduleStartTime;
		TIMEKEY  tScheduleStopTime;
		TIMEKEY  tPeriodicStartTime;
		TIMEKEY  tPeriodicInterval[2];
		TIMEKEY  tDailyStartTime;
		TIMEKEY  tDailyStopTime;
		TIMEKEY  tBackupTimeout;
		UINT  nBackupOptions;
		UINT  nBackupRetry[2];
		UINT  nScheduleOptions;
	} DATA, *PDATA, *LPDATA;
protected:
	CString  m_szCommandHandler;
	UINT  m_nCommandHandlerState;
protected:
	CTimeKey  m_tScheduleStartTime;
	CTimeKey  m_tScheduleStopTime;
	CTimeKey  m_tPeriodicStartTime;
	CTimeSpan  m_tPeriodicInterval[2];
	CTimeSpan  m_tDailyStartTime;
	CTimeSpan  m_tDailyStopTime;
	CTimeSpan  m_tBackupTimeout;
	CString  m_szBackupDevice;
	UINT  m_nBackupOptions;
	UINT  m_nBackupRetry[2];
	UINT  m_nScheduleOptions;
protected:
	static UINT  m_nDeviceStatus;
	static BOOL  m_bDeviceStatus;

	// Operations
public:
	virtual BOOL Initialize(UINT nFlags = IODEVICE_TYPE_CLIENT | IODEVICE_SERVICE_TC | IODEVICE_DATASERVICE_SOURCEPACKETS, CONST CTimeSpan &tDataDrop = 0, CONST CTimeSpan &tDataDelay = 0, IODEVICESTATUSPROCEDURE pStatusProcedure = NULL, IODEVICEMESSAGEPROCEDURE pMessageProcedure = NULL);

public:
	VOID SetCommandHandler(LPCTSTR pszComputer);
	CString GetCommandHandler() CONST;
	VOID SetCommandHandlerState(UINT nState);
	UINT GetCommandHandlerState() CONST;

	VOID SetScheduleOptions(UINT nOptions);
	UINT GetScheduleOptions() CONST;
	VOID SetScheduleDaily(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime);
	BOOL GetScheduleDaily(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;
	VOID SetScheduleInterval(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime);
	BOOL GetScheduleInterval(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	VOID SetSchedulePeriodic(CONST CTimeKey &tStartTime, CONST CTimeSpan &tPeriod, CONST CTimeSpan &tInterval);
	BOOL GetSchedulePeriodic(CTimeKey &tStartTime, CTimeSpan &tPeriod, CTimeSpan &tInterval) CONST;
	VOID SetBackupDevice(LPCTSTR pszDevice);
	BOOL GetBackupDevice(CString &szDevice) CONST;
	VOID SetBackupOptions(UINT nOptions);
	UINT GetBackupOptions() CONST;
	VOID SetBackupRetries(UINT nRetries);
	BOOL GetBackupRetries(UINT &nRetries) CONST;
	VOID SetBackupRetryCount(UINT nCount);
	BOOL GetBackupRetryCount(UINT &nCount) CONST;
	VOID SetBackupTimeout(CONST CTimeSpan &tTimeout);
	BOOL GetBackupTimeout(CTimeSpan &tTimeout) CONST;

	CString GetToolTipText() CONST;

	BOOL IsStandBy(CTimeSpan &tPeriod) CONST;
	BOOL IsStandBy() CONST;

	BOOL Copy(CONST CTCUplinkDevice *pDevice);
	BOOL Compare(CONST CTCUplinkDevice *pDevice) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	static VOID CALLBACK TrackDeviceDataStatus(INT nDataID, UINT nStatus, BOOL bSuccess);
	static VOID CALLBACK UpdateDeviceStatus(LPCTSTR pszStatus, UINT nStatus);
	static VOID CALLBACK ShowDeviceMessage(LPCTSTR pszMessage, UINT nMessageType);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCUplinkDevices

class CTCUplinkDevices : public CIODevices
{
	// Construction
public:
	CTCUplinkDevices();
	~CTCUplinkDevices();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbDevice[2];
		INT  cbDevicesData;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szDevice[2];
	CStringArray  m_szDevicePathNames[2];
	CTCUplinkDevice  m_cDevice;

	// Operations
public:
	INT EnumDevices(UINT nFlags = IODEVICE_TYPE_CLIENT | IODEVICE_SERVICE_TC | IODEVICE_DATASERVICE_SOURCEPACKETS);

	INT EnumStandByDevices(CTCUplinkDevices &pDevices) CONST;
	INT EnumBackupDevices(CONST CTCUplinkDevice *pDevice, CTCUplinkDevices &pDevices) CONST;

	BOOL HasAvailableDevices(BOOL bSupported = FALSE) CONST;

	BOOL SetActiveDevice(CONST CTCUplinkDevice *pDevice);
	BOOL GetActiveDevice(CTCUplinkDevice *pDevice) CONST;
	BOOL SetDefaultDevice(CONST CTCUplinkDevice *pDevice);
	BOOL GetDefaultDevice(CTCUplinkDevice *pDevice) CONST;
	CString GetActiveDeviceBrand() CONST;
	CString GetActiveDeviceName() CONST;
	CString GetDefaultDeviceBrand() CONST;
	CString GetDefaultDeviceName() CONST;

	CTCUplinkDevice *GetAt(INT nIndex) CONST;
	CTCUplinkDevice *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCUplinkDevices *pDevices, BOOL bAll = TRUE);
	BOOL Compare(CONST CTCUplinkDevices *pDevices, BOOL bAll = TRUE) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	VOID EnumDevices(UINT nFlags, LPCTSTR pszDirectory);
	VOID EnumDevices(UINT nFlags, LPCTSTR pszDirectory, LPCTSTR pszFileName);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCLogEntry

class CTCLogEntry : public CComputerToken
{
	// Construction
public:
	CTCLogEntry();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbComputerName;
		INT  cbDescription;
		INT  cbActivity;
		INT  cbUser;
		TIMEKEY  tTime;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szDescription;
	CString  m_szActivity;
	CString  m_szUser;
	CTimeKey  m_tTime;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetActivity(LPCTSTR pszActivity);
	CString GetActivity() CONST;
	VOID SetUser(LPCTSTR pszUser);
	CString GetUser() CONST;
	VOID SetTime(CONST CTimeKey &tTime);
	CTimeKey GetTime() CONST;

	VOID Copy(CONST CTCLogEntry *pEntry);
	BOOL Compare(CONST CTCLogEntry *pEntry) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCLogEntries

class CTCLogEntries : public CPtrArray
{
	// Construction
public:
	CTCLogEntries();
	~CTCLogEntries();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCLogEntry *pEntry);

	INT Find(CONST CTCLogEntry *pEntry) CONST;

	CTCLogEntry *GetAt(INT nIndex) CONST;
	CTCLogEntry *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCLogEntries *pEntries);
	BOOL Compare(CONST CTCLogEntries *pEntries) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(CONST CTimeKey &tTime, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessCommandSourceInfo

class CTCProcessCommandSourceInfo : public CComputerToken
{
	// Construction
public:
	CTCProcessCommandSourceInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbComputerName;
		INT  cbSubSystemIDs;
		INT  cbSubSystemStatus;
		INT  cbSubSystemEvents[2];
		UINT  nSourceType;
		UINT  nTelecommandingMode;
		UINT  nTelecommandingState;
		UINT  nTelecommandingFlags;
		BOOL  bTelecommandingInterlockMode;
		BOOL  bTelecommandingReleaseWaitMode;
		BOOL  bTelecommandingAutoRejectionMode;
		TIMEKEY  tDefaultReleaseTimeWindow;
		TIMEKEY  tDispatchTimeWindow;
	} DATA, *PDATA, *LPDATA;
private:
	UINT  m_nSourceType;
	UINT  m_nTelecommandingMode;
	UINT  m_nTelecommandingState;
	UINT  m_nTelecommandingFlags;
	BOOL  m_bTelecommandingInterlockMode;
	BOOL  m_bTelecommandingReleaseWaitMode;
	BOOL  m_bTelecommandingAutoRejectionMode;
	CTimeSpan  m_tDefaultReleaseTimeWindow;
	CTimeSpan  m_tDispatchTimeWindow;
	CUIntArray  m_nSubSystemIDs;
	CUIntArray  m_nSubSystemStatus;
	CStringArray  m_szSubSystemEvents[2];

	// Operations
public:
	VOID SetSourceType(UINT nType);
	UINT GetSourceType() CONST;

	VOID SetTelecommandingMode(UINT nMode);
	UINT GetTelecommandingMode() CONST;
	VOID SetTelecommandingState(UINT nState);
	UINT GetTelecommandingState() CONST;
	VOID SetTelecommandingChecks(UINT nFlags);
	UINT GetTelecommandingChecks() CONST;
	VOID EnableTelecommandingInterlockMode(BOOL bEnable = TRUE);
	BOOL IsTelecommandingInterlockModeEnabled() CONST;
	VOID EnableTelecommandingReleaseWaitMode(BOOL bEnable = TRUE);
	BOOL IsTelecommandingReleaseWaitModeEnabled() CONST;
	VOID EnableTelecommandingAutoRejectionMode(BOOL bEnable = TRUE);
	BOOL IsTelecommandingAutoRejectionModeEnabled() CONST;

	VOID SetSubSystemChecks(CONST CUIntArray &nSubSystemIDs, CONST CStringArray &szEnablingEvents, CONST CStringArray &szDisablingEvents, CONST CUIntArray &nStatus);
	INT GetSubSystemChecks(CUIntArray &nSubSystemIDs, CStringArray &szEnablingEvents, CStringArray &szDisablingEvents, CUIntArray &nStatus) CONST;

	VOID SetDefaultReleaseTimeWindow(CONST CTimeSpan &tTimeWindow);
	CTimeSpan GetDefaultReleaseTimeWindow() CONST;
	VOID SetDispatchTimeWindow(CONST CTimeSpan &tTimeWindow);
	CTimeSpan GetDispatchTimeWindow() CONST;

	BOOL Update(LPCTSTR pszEvent);

	VOID Copy(CONST CTCProcessCommandSourceInfo *pCommandSourceInfo);
	BOOL Compare(CONST CTCProcessCommandSourceInfo *pCommandSourceInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessCommandSources

class CTCProcessCommandSources : public CPtrArray
{
	// Construction
public:
	CTCProcessCommandSources();
	~CTCProcessCommandSources();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCProcessCommandSourceInfo *pCommandSourceInfo);

	INT Find(LPCTSTR pszComputerName, UINT nSourceType) CONST;

	CTCProcessCommandSourceInfo *GetAt(INT nIndex) CONST;
	CTCProcessCommandSourceInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCProcessCommandSources *pCommandSources);
	BOOL Compare(CONST CTCProcessCommandSources *pCommandSources) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszComputerName, UINT nSourceType, BOOL bInsert = FALSE) CONST;

	CString ConstructSearchName(LPCTSTR pszComputerName, UINT nSourceType) CONST;
	CString ConstructSearchName(CONST CTCProcessCommandSourceInfo *pCommandSourceInfo) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceMessageHeader

// Specify the TCPI message identifier codes
#define TCPI_ANNOUNCECOMMANDHANDLERREQUEST   0x01
#define TCPI_ANNOUNCECOMMANDHANDLERRESPONSE   0x02
#define TCPI_SETCOMMANDHANDLERCONFIGURATIONREQUEST   0x03
#define TCPI_SETCOMMANDHANDLERCONFIGURATIONRESPONSE   0x04
#define TCPI_GETCOMMANDHANDLERCONFIGURATIONREQUEST   0x05
#define TCPI_GETCOMMANDHANDLERCONFIGURATIONRESPONSE   0x06
#define TCPI_REGISTERCOMMANDSOURCESREQUEST   0x07
#define TCPI_REGISTERCOMMANDSOURCESRESPONSE   0x08
#define TCPI_UPDATECOMMANDSOURCESREQUEST   0x09
#define TCPI_UPDATECOMMANDSOURCESRESPONSE   0x0A
#define TCPI_UPDATECOMMANDSOURCESCONTENTSREQUEST   0x0B
#define TCPI_UPDATECOMMANDSOURCESCONTENTSRESPONSE   0x0C
#define TCPI_UPDATECOMMANDUPLINKDEVICESTATE   0x0D
#define TCPI_DISPATCHTELECOMMANDSREQUEST   0x0E
#define TCPI_DISPATCHTELECOMMANDSRESPONSE   0x0F
#define TCPI_RELEASETELECOMMANDSREQUEST   0x10
#define TCPI_RELEASETELECOMMANDSRESPONSE   0x11
#define TCPI_EXECUTETELECOMMANDREQUEST   0x12
#define TCPI_EXECUTETELECOMMANDRESPONSE   0x13
#define TCPI_ACKNOWLEDGETELECOMMANDSREQUEST   0x14
#define TCPI_ACKNOWLEDGETELECOMMANDSRESPONSE   0x15
#define TCPI_DISCARDTELECOMMANDSREQUEST   0x16
#define TCPI_DISCARDTELECOMMANDSRESPONSE   0x17
// Specify the TCPI message identification length
#define TCPI_MESSAGEIDLENGTH   4
#define TCPI_MESSAGEHEADERLENGTH   8
// Specify the TCPI message fixed field codes
#define TCPI_VERSION   0x00010000

class CTCProcessInterfaceMessageHeader : public CObject
{
	// Construction
public:
	CTCProcessInterfaceMessageHeader();
	CTCProcessInterfaceMessageHeader(BYTE nID, UINT nLength);

	// Attributes
public:
#pragma pack(push,1)
	typedef struct tagTCPIMESSAGEHEADER {
		BYTE  nMessageID;
		BYTE  nMessageLength[3];
		UINT  nVersion;
	} TCPIMESSAGEHEADER, *PTCPIMESSAGEHEADER, *LPTCPIMESSAGEHEADER;
#pragma pack(pop)
protected:
	TCPIMESSAGEHEADER  m_sHeader;

	// Operations
public:
	BOOL SetMessageID(BYTE nID);
	BYTE GetMessageID() CONST;
	BOOL SetMessageLength(UINT nLength);
	UINT GetMessageLength() CONST;
	BOOL SetVersion(UINT nVersion);
	UINT GetVersion() CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceAnnounceCommandHandlerRequest

class CTCProcessInterfaceAnnounceCommandHandlerRequest : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceAnnounceCommandHandlerRequest();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPIANNOUNCECOMMANDHANDLERREQUEST {
		TCPIMESSAGEHEADER  sHeader;
		INT  cbCommandHandler;
		BOOL  bExclusive;
	} TCPIANNOUNCECOMMANDHANDLERREQUEST, *PTCPIANNOUNCECOMMANDHANDLERREQUEST, *LPTCPIANNOUNCECOMMANDHANDLERREQUEST;
#pragma pack(pop)
private:
	CString  m_szCommandHandler;
	BOOL  m_bExclusive;

	// Operations
public:
	BOOL SetCommandHandler(LPCTSTR pszCommandHandler, BOOL bExclusive = TRUE);
	CString GetCommandHandler() CONST;

	BOOL IsExclusiveCommandHandler() CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check(INT cbData) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceAnnounceCommandHandlerResponse

class CTCProcessInterfaceAnnounceCommandHandlerResponse : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceAnnounceCommandHandlerResponse();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPIANNOUNCECOMMANDHANDLERRESPONSE {
		TCPIMESSAGEHEADER  sHeader;
		INT  cbCommandHandler;
		BOOL  bExclusive;
	} TCPIANNOUNCECOMMANDHANDLERRESPONSE, *PTCPIANNOUNCECOMMANDHANDLERRESPONSE, *LPTCPIANNOUNCECOMMANDHANDLERRESPONSE;
#pragma pack(pop)
private:
	CString  m_szCommandHandler;
	BOOL  m_bExclusive;

	// Operations
public:
	BOOL SetCommandHandler(LPCTSTR pszCommandHandler, BOOL bExclusive = TRUE);
	CString GetCommandHandler() CONST;

	BOOL IsExclusiveCommandHandler() CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check(INT cbData) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceSetCommandHandlerConfigurationRequest

class CTCProcessInterfaceSetCommandHandlerConfigurationRequest : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceSetCommandHandlerConfigurationRequest();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPISETCOMMANDHANDLERCONFIGURATIONREQUEST {
		TCPIMESSAGEHEADER  sHeader;
		INT  cbCommandSources;
		INT  cbHistoryFiles[2];
		INT  cbDefaultHistoryFileName;
		TIMEKEY  tVerificationUncertaintyTimeWindow;
		TIMEKEY  tMaximumExecutionTimePeriod;
		TIMEKEY  tMaximumTimeCheckPeriod;
		TIMEKEY  tDefaultReleaseTimeWindow;
		UINT  nTelecommandingMode;
		UINT  nTelecommandingState;
		UINT  nTelecommandingFlags;
		BOOL  bTelecommandingInterlockMode;
		BOOL  bTelecommandingReleaseWaitMode;
		BOOL  bTelecommandingAutoRejectionMode;
		BOOL  bUpdate;
	} TCPISETCOMMANDHANDLERCONFIGURATIONREQUEST, *PTCPISETCOMMANDHANDLERCONFIGURATIONREQUEST, *LPSETCOMMANDHANDLERCONFIGURATIONREQUEST;
#pragma pack(pop)
private:
	CTCProcessCommandSources  m_pCommandSources;
	CTimeSpan  m_tVerificationUncertaintyTimeWindow;
	CTimeSpan  m_tMaximumExecutionTimePeriod;
	CTimeSpan  m_tMaximumTimeCheckPeriod;
	CTimeSpan  m_tDefaultReleaseTimeWindow;
	CHistoryStoreFiles  m_pHistoryFiles[2];
	CString  m_szDefaultHistoryFileName;
	UINT  m_nTelecommandingMode;
	UINT  m_nTelecommandingState;
	UINT  m_nTelecommandingFlags;
	BOOL  m_bTelecommandingInterlockMode;
	BOOL  m_bTelecommandingReleaseWaitMode;
	BOOL  m_bTelecommandingAutoRejectionMode;
	BOOL  m_bUpdate;

	// Operations
public:
	BOOL SetConfiguration(CONST CTCProcessCommandSources &pCommandSources, UINT nTelecommandingMode, UINT nTelecommandingState, UINT nTelecommandingFlags, BOOL bTelecommandingInterlockMode, BOOL bTelecommandingReleaseWaitMode, BOOL bTelecommandingAutoRejectionMode, CONST CTimeSpan &tVerificationUncertaintyTimeWindow, CONST CTimeSpan &tMaximumExecutionTimePeriod, CONST CTimeSpan &tMaximumTimeCheckPeriod, CONST CTimeSpan &tDefaultReleaseTimeWindow, CONST CHistoryStoreFiles &pHistoryArchivalFiles, CONST CHistoryStoreFiles &pHistoryRetrievalFiles, LPCTSTR pszDefaultHistoryFileName);
	BOOL GetConfiguration(CTCProcessCommandSources &pCommandSources, UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingFlags, BOOL &bTelecommandingInterlockMode, BOOL &bTelecommandingReleaseWaitMode, BOOL &bTelecommandingAutoRejectionMode, CTimeSpan &tVerificationUncertaintyTimeWindow, CTimeSpan &tMaximumExecutionTimePeriod, CTimeSpan &tMaximumTimeCheckPeriod, CTimeSpan &tDefaultReleaseTimeWindow, CHistoryStoreFiles &pHistoryArchivalFiles, CHistoryStoreFiles &pHistoryRetrievalFiles, CString &szDefaultHistoryFileName) CONST;
	BOOL EnableUpdateFlag(BOOL bEnable = TRUE);
	BOOL IsUpdateFlagEnabled() CONST;

	BOOL Reset();

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check(INT cbData) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceSetCommandHandlerConfigurationResponse

class CTCProcessInterfaceSetCommandHandlerConfigurationResponse : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceSetCommandHandlerConfigurationResponse();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPISETCOMMANDHANDLERCONFIGURATIONRESPONSE {
		TCPIMESSAGEHEADER  sHeader;
		BOOL  bResult;
	} TCPISETCOMMANDHANDLERCONFIGURATIONRESPONSE, *PTCPISETCOMMANDHANDLERCONFIGURATIONRESPONSE, *LPTCPISETCOMMANDHANDLERCONFIGURATIONRESPONSE;
#pragma pack(pop)
private:
	BOOL  m_bResult;

	// Operations
public:
	BOOL SetResult(BOOL bSuccess);
	BOOL GetResult() CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceGetCommandHandlerConfigurationRequest

class CTCProcessInterfaceGetCommandHandlerConfigurationRequest : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceGetCommandHandlerConfigurationRequest();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPIGETCOMMANDHANDLERCONFIGURATIONREQUEST {
		TCPIMESSAGEHEADER  sHeader;
		BOOL  bUpdate;
	} TCPIGETCOMMANDHANDLERCONFIGURATIONREQUEST, *PTCPIGETCOMMANDHANDLERCONFIGURATIONREQUEST, *LPGETCOMMANDHANDLERCONFIGURATIONREQUEST;
#pragma pack(pop)
private:
	BOOL  m_bUpdate;

	// Operations
public:
	BOOL EnableUpdateFlag(BOOL bEnable = TRUE);
	BOOL IsUpdateFlagEnabled() CONST;

	BOOL Reset();

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceGetCommandHandlerConfigurationResponse

class CTCProcessInterfaceGetCommandHandlerConfigurationResponse : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceGetCommandHandlerConfigurationResponse();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPIGETCOMMANDHANDLERCONFIGURATIONRESPONSE {
		TCPIMESSAGEHEADER  sHeader;
		INT  cbCommandSources;
		INT  cbItems;
		INT  cbInterlocks;
		INT  cbHistoryFiles[2];
		INT  cbDefaultHistoryFileName;
		TIMEKEY  tVerificationUncertaintyTimeWindow;
		TIMEKEY  tMaximumExecutionTimePeriod;
		TIMEKEY  tMaximumTimeCheckPeriod;
		TIMEKEY  tDefaultReleaseTimeWindow;
		UINT  nTelecommandingMode;
		UINT  nTelecommandingState;
		UINT  nTelecommandingFlags;
		BOOL  bTelecommandingInterlockMode;
		BOOL  bTelecommandingReleaseWaitMode;
		BOOL  bTelecommandingAutoRejectionMode;
		BOOL  bUpdate;
	} TCPIGETCOMMANDHANDLERCONFIGURATIONRESPONSE, *PTCPIGETCOMMANDHANDLERCONFIGURATIONRESPONSE, *LPTCPIGETCOMMANDHANDLERCONFIGURATIONRESPONSE;
#pragma pack(pop)
private:
	CTCItems  m_pItems;
	CTCInterlocks  m_pInterlocks;
	CTCProcessCommandSources  m_pCommandSources;
	CTimeSpan  m_tVerificationUncertaintyTimeWindow;
	CTimeSpan  m_tMaximumExecutionTimePeriod;
	CTimeSpan  m_tMaximumTimeCheckPeriod;
	CTimeSpan  m_tDefaultReleaseTimeWindow;
	CHistoryStoreFiles  m_pHistoryFiles[2];
	CString  m_szDefaultHistoryFileName;
	UINT  m_nTelecommandingMode;
	UINT  m_nTelecommandingState;
	UINT  m_nTelecommandingFlags;
	BOOL  m_bTelecommandingInterlockMode;
	BOOL  m_bTelecommandingReleaseWaitMode;
	BOOL  m_bTelecommandingAutoRejectionMode;
	BOOL  m_bUpdate;

	// Operations
public:
	BOOL SetConfiguration(CONST CTCProcessCommandSources &pCommandSources, UINT nTelecommandingMode, UINT nTelecommandingState, UINT nTelecommandingFlags, BOOL bTelecommandingInterlockMode, BOOL bTelecommandingReleaseWaitMode, BOOL bTelecommandingAutoRejectionMode, CONST CTimeSpan &tVerificationUncertaintyTimeWindow, CONST CTimeSpan &tMaximumExecutionTimePeriod, CONST CTimeSpan &tMaximumTimeCheckPeriod, CONST CTimeSpan &tDefaultReleaseTimeWindow, CONST CTCItems &pItems, CONST CTCInterlocks &pInterlocks, CONST CHistoryStoreFiles &pHistoryArchivalFiles, CONST CHistoryStoreFiles &pHistoryRetrievalFiles, LPCTSTR pszDefaultHistoryFileName);
	BOOL GetConfiguration(CTCProcessCommandSources &pCommandSources, UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingFlags, BOOL &bTelecommandingInterlockMode, BOOL &bTelecommandingReleaseWaitMode, BOOL &bTelecommandingAutoRejectionMode, CTimeSpan &tVerificationUncertaintyTimeWindow, CTimeSpan &tMaximumExecutionTimePeriod, CTimeSpan &tMaximumTimeCheckPeriod, CTimeSpan &tDefaultReleaseTimeWindow, CTCItems &pItems, CTCInterlocks &pInterlocks, CHistoryStoreFiles &pHistoryArchivalFiles, CHistoryStoreFiles &pHistoryRetrievalFiles, CString &szDefaultHistoryFileName) CONST;
	BOOL EnableUpdateFlag(BOOL bEnable = TRUE);
	BOOL IsUpdateFlagEnabled() CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check(INT cbData) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceRegisterCommandSourcesRequest

class CTCProcessInterfaceRegisterCommandSourcesRequest : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceRegisterCommandSourcesRequest();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPIREGISTERCOMMANDSOURCESREQUEST {
		TCPIMESSAGEHEADER  sHeader;
		INT  cbCommandSources;
		INT  cbItems[2];
		INT  cbInterlocks;
		INT  cbQueues;
		BOOL  bContents;
	} TCPIREGISTERCOMMANDSOURCESREQUEST, *PTCPIREGISTERCOMMANDSOURCESREQUEST, *LPTCPIREGISTERCOMMANDSOURCESREQUEST;
#pragma pack(pop)
private:
	CTCProcessCommandSources  m_pCommandSources;
	CTCOnBoardBufferQueues  m_pQueues;
	CTCInterlocks  m_pInterlocks;
	CTCItems  m_pItems[2];

	// Operations
public:
	BOOL SetCommandSources(CONST CTCProcessCommandSources &pCommandSources);
	BOOL SetCommandSources(CONST CTCProcessCommandSources &pCommandSources, CONST CTCItems &pItems, CONST CTCItems &pHistoricalItems, CONST CTCInterlocks &pInterlocks, CONST CTCOnBoardBufferQueues &pQueues);
	BOOL GetCommandSources(CTCProcessCommandSources &pCommandSources) CONST;
	BOOL GetCommandSources(CTCProcessCommandSources &pCommandSources, CTCItems &pItems, CTCItems &pHistoricalItems, CTCInterlocks &pInterlocks, CTCOnBoardBufferQueues &pQueues) CONST;

	BOOL Reset();

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check(INT cbData) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceRegisterCommandSourcesResponse

class CTCProcessInterfaceRegisterCommandSourcesResponse : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceRegisterCommandSourcesResponse();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPIREGISTERCOMMANDSOURCESRESPONSE {
		TCPIMESSAGEHEADER  sHeader;
		INT  cbCommandSources;
		INT  cbDevice;
		INT  cbItems[2];
		INT  cbInterlocks;
		INT  cbQueues;
	} TCPIREGISTERCOMMANDSOURCESRESPONSE, *PTCPIREGISTERCOMMANDSOURCESRESPONSE, *LPTCPIREGISTERCOMMANDSOURCESRESPONSE;
#pragma pack(pop)
private:
	CTCProcessCommandSources  m_pCommandSources;
	CTCOnBoardBufferQueues  m_pQueues;
	CTCUplinkDevice  m_cDevice;
	CTCInterlocks  m_pInterlocks;
	CTCItems  m_pItems[2];

	// Operations
public:
	BOOL SetCommandSources(CONST CTCProcessCommandSources &pCommandSources);
	INT GetCommandSources(CTCProcessCommandSources &pCommandSources) CONST;
	BOOL SetCommandingDevice(CONST CTCUplinkDevice *pDevice);
	BOOL GetCommandingDevice(CTCUplinkDevice *pDevice) CONST;
	BOOL SetTelecommands(CONST CTCItems &pItems, CONST CTCItems &pHistoricalItems);
	INT GetTelecommands(CTCItems &pItems, CTCItems &pHistoricalItems) CONST;
	BOOL SetTCInterlocks(CONST CTCInterlocks &pInterlocks);
	INT GetTCInterlocks(CTCInterlocks &pInterlocks) CONST;
	BOOL SetTCOnBoardBufferQueues(CONST CTCOnBoardBufferQueues &pQueues);
	INT GetTCOnBoardBufferQueues(CTCOnBoardBufferQueues &pQueues) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check(INT cbData) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceUpdateCommandSourcesRequest

class CTCProcessInterfaceUpdateCommandSourcesRequest : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceUpdateCommandSourcesRequest();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPIUPDATECOMMANDSOURCESREQUEST {
		TCPIMESSAGEHEADER  sHeader;
		INT  cbCommandSources;
	} TCPIUPDATECOMMANDSOURCESREQUEST, *PTCPIUPDATECOMMANDSOURCESREQUEST, *LPTCPIUPDATECOMMANDSOURCESREQUEST;
#pragma pack(pop)
private:
	CTCProcessCommandSources  m_pCommandSources;

	// Operations
public:
	BOOL SetCommandSources(CONST CTCProcessCommandSources &pCommandSources);
	INT GetCommandSources(CTCProcessCommandSources &pCommandSources) CONST;

	BOOL Reset();

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check(INT cbData) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceUpdateCommandSourcesResponse

class CTCProcessInterfaceUpdateCommandSourcesResponse : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceUpdateCommandSourcesResponse();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPIUPDATECOMMANDSOURCESRESPONSE {
		TCPIMESSAGEHEADER  sHeader;
		INT  cbCommandSources;
	} TCPIUPDATECOMMANDSOURCESRESPONSE, *PTCPIUPDATECOMMANDSOURCESRESPONSE, *LPTCPIUPDATECOMMANDSOURCESRESPONSE;
#pragma pack(pop)
private:
	CTCProcessCommandSources  m_pCommandSources;

	// Operations
public:
	BOOL SetCommandSources(CONST CTCProcessCommandSources &pCommandSources);
	INT GetCommandSources(CTCProcessCommandSources &pCommandSources) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check(INT cbData) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceUpdateCommandSourcesContentsRequest

class CTCProcessInterfaceUpdateCommandSourcesContentsRequest : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceUpdateCommandSourcesContentsRequest();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPIUPDATECOMMANDSOURCESCONTENTSREQUEST {
		TCPIMESSAGEHEADER  sHeader;
		INT  cbItems;
		INT  cbQueues;
		INT  cbInterlocks;
		BOOL  bItems[2];
		BOOL  bQueues[2];
		BOOL  bInterlocks[2];
		BOOL  bAcknowledgment;
	} TCPIUPDATECOMMANDSOURCESCONTENTSREQUEST, *PTCPIUPDATECOMMANDSOURCESCONTENTSREQUEST, *LPTCPIUPDATECOMMANDSOURCESCONTENTSREQUEST;
#pragma pack(pop)
private:
	CTCItems  m_pItems;
	CTCInterlocks  m_pInterlocks;
	CTCOnBoardBufferQueues  m_pQueues;
	BOOL  m_bItems[2];
	BOOL  m_bQueues[2];
	BOOL  m_bInterlocks[2];
	BOOL  m_bAcknowledgment;

	// Operations
public:
	BOOL SetTelecommands(CONST CTCItems &pItems, BOOL bAll = TRUE);
	INT GetTelecommands(CTCItems &pItems, BOOL &bAll) CONST;
	BOOL SetTCInterlocks(CONST CTCInterlocks &pInterlocks, BOOL bAll = TRUE);
	INT GetTCInterlocks(CTCInterlocks &pInterlocks, BOOL &bAll) CONST;
	BOOL SetTCOnBoardBufferQueues(CONST CTCOnBoardBufferQueues &pQueues, BOOL bAll = TRUE);
	INT GetTCOnBoardBufferQueues(CTCOnBoardBufferQueues &pQueues, BOOL &bAll) CONST;
	BOOL EnableAcknowledgment(BOOL bEnable = TRUE);
	BOOL IsAcknowledgmentEnabled() CONST;

	BOOL Reset();

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check(INT cbData) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceUpdateCommandSourcesContentsResponse

class CTCProcessInterfaceUpdateCommandSourcesContentsResponse : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceUpdateCommandSourcesContentsResponse();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPIUPDATECOMMANDSOURCESCONTENTSRESPONSE {
		TCPIMESSAGEHEADER  sHeader;
		BOOL  bResult;
	} TCPIUPDATECOMMANDSOURCESCONTENTSRESPONSE, *PTCPIUPDATECOMMANDSOURCESCONTENTSRESPONSE, *LPTCPIUPDATECOMMANDSOURCESCONTENTSRESPONSE;
#pragma pack(pop)
private:
	BOOL  m_bResult;

	// Operations
public:
	BOOL SetResult(BOOL bSuccess);
	BOOL GetResult() CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceUpdateCommandUplinkDeviceState

class CTCProcessInterfaceUpdateCommandUplinkDeviceState : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceUpdateCommandUplinkDeviceState();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPIUPDATECOMMANDUPLINKDEVICESTATE {
		TCPIMESSAGEHEADER  sHeader;
		INT  cbDevice;
	} TCPIUPDATECOMMANDUPLINKDEVICESTATE, *PTCPIUPDATECOMMANDUPLINKDEVICESTATE, *LPTCPIUPDATECOMMANDUPLINKDEVICESTATE;
#pragma pack(pop)
private:
	CTCUplinkDevice  m_cDevice;

	// Operations
public:
	BOOL SetCommandingDevice(CONST CTCUplinkDevice *pDevice);
	BOOL GetCommandingDevice(CTCUplinkDevice *pDevice) CONST;

	BOOL Reset();

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check(INT cbData) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceDispatchTelecommandsRequest

class CTCProcessInterfaceDispatchTelecommandsRequest : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceDispatchTelecommandsRequest();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPIDISPATCHTELECOMMANDSREQUEST {
		TCPIMESSAGEHEADER  sHeader;
		INT  cbItems;
		BOOL  bUndo;
		BOOL  bAcknowledgment;
	} TCPIDISPATCHTELECOMMANDSREQUEST, *PTCPIDISPATCHTELECOMMANDSREQUEST, *LPTCPIDISPATCHTELECOMMANDSREQUEST;
#pragma pack(pop)
private:
	CTCItems  m_pItems;
	BOOL  m_bAcknowledgment;
	BOOL  m_bUndo;

	// Operations
public:
	BOOL SetTelecommands(CONST CTCItems &pItems, BOOL bUndo);
	INT GetTelecommands(CTCItems &pItems, BOOL &bUndo) CONST;
	BOOL EnableAcknowledgment(BOOL bEnable = TRUE);
	BOOL IsAcknowledgmentEnabled() CONST;

	BOOL Reset();

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check(INT cbData) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceDispatchTelecommandsResponse

class CTCProcessInterfaceDispatchTelecommandsResponse : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceDispatchTelecommandsResponse();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPIDISPATCHTELECOMMANDSRESPONSE {
		TCPIMESSAGEHEADER  sHeader;
		BOOL  bResult;
	} TCPIDISPATCHTELECOMMANDSRESPONSE, *PTCPIDISPATCHTELECOMMANDSRESPONSE, *LPTCPIDISPATCHTELECOMMANDSRESPONSE;
#pragma pack(pop)
private:
	BOOL  m_bResult;

	// Operations
public:
	BOOL SetResult(BOOL bSuccess);
	BOOL GetResult() CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceReleaseTelecommandsRequest

class CTCProcessInterfaceReleaseTelecommandsRequest : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceReleaseTelecommandsRequest();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPIRELEASETELECOMMANDSREQUEST {
		TCPIMESSAGEHEADER  sHeader;
		INT  cbItems;
		BOOL  bAcknowledgment;
	} TCPIRELEASETELECOMMANDSREQUEST, *PTCPIRELEASETELECOMMANDSREQUEST, *LPTCPIRELEASETELECOMMANDSREQUEST;
#pragma pack(pop)
private:
	CTCItems  m_pItems;
	BOOL  m_bAcknowledgment;

	// Operations
public:
	BOOL SetTelecommands(CONST CTCItems &pItems);
	INT GetTelecommands(CTCItems &pItems) CONST;
	BOOL EnableAcknowledgment(BOOL bEnable = TRUE);
	BOOL IsAcknowledgmentEnabled() CONST;

	BOOL Reset();

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check(INT cbData) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceReleaseTelecommandsResponse

class CTCProcessInterfaceReleaseTelecommandsResponse : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceReleaseTelecommandsResponse();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPIRELEASETELECOMMANDSRESPONSE {
		TCPIMESSAGEHEADER  sHeader;
		BOOL  bResult;
	} TCPIRELEASETELECOMMANDSRESPONSE, *PTCPIRELEASETELECOMMANDSRESPONSE, *LPTCPIRELEASETELECOMMANDSRESPONSE;
#pragma pack(pop)
private:
	BOOL  m_bResult;

	// Operations
public:
	BOOL SetResult(BOOL bSuccess);
	BOOL GetResult() CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceExecuteTelecommandRequest

class CTCProcessInterfaceExecuteTelecommandRequest : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceExecuteTelecommandRequest();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPIEXECUTETELECOMMANDREQUEST {
		TCPIMESSAGEHEADER  sHeader;
		INT  cbItem;
		BOOL  bAcknowledgment;
	} TCPIEXECUTETELECOMMANDREQUEST, *PTCPIEXECUTETELECOMMANDREQUEST, *LPTCPIEXECUTETELECOMMANDREQUEST;
#pragma pack(pop)
private:
	CTCItem  m_cItem;
	BOOL  m_bAcknowledgment;

	// Operations
public:
	BOOL SetTelecommand(CONST CTCItem *pItem);
	BOOL GetTelecommand(CTCItem *pItem) CONST;
	BOOL EnableAcknowledgment(BOOL bEnable = TRUE);
	BOOL IsAcknowledgmentEnabled() CONST;

	BOOL Reset();

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check(INT cbData) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceExecuteTelecommandResponse

class CTCProcessInterfaceExecuteTelecommandResponse : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceExecuteTelecommandResponse();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPIEXECUTETELECOMMANDRESPONSE {
		TCPIMESSAGEHEADER  sHeader;
		BOOL  bResult;
	} TCPIEXECUTETELECOMMANDRESPONSE, *PTCPIEXECUTETELECOMMANDRESPONSE, *LPTCPIEXECUTETELECOMMANDRESPONSE;
#pragma pack(pop)
private:
	BOOL  m_bResult;

	// Operations
public:
	BOOL SetResult(BOOL bSuccess);
	BOOL GetResult() CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceAcknowledgeTelecommandsRequest

class CTCProcessInterfaceAcknowledgeTelecommandsRequest : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceAcknowledgeTelecommandsRequest();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPIACKNOWLEDGETELECOMMANDSREQUEST {
		TCPIMESSAGEHEADER  sHeader;
		INT  cbItems;
		BOOL  bAcknowledgment;
	} TCPIACKNOWLEDGETELECOMMANDSREQUEST, *PTCPIACKNOWLEDGETELECOMMANDSREQUEST, *LPTCPIACKNOWLEDGETELECOMMANDSREQUEST;
#pragma pack(pop)
private:
	CTCItems  m_pItems;
	BOOL  m_bAcknowledgment;

	// Operations
public:
	BOOL SetTelecommands(CONST CTCItems &pItems);
	INT GetTelecommands(CTCItems &pItems) CONST;
	BOOL EnableAcknowledgment(BOOL bEnable = TRUE);
	BOOL IsAcknowledgmentEnabled() CONST;

	BOOL Reset();

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check(INT cbData) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceAcknowledgeTelecommandsResponse

class CTCProcessInterfaceAcknowledgeTelecommandsResponse : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceAcknowledgeTelecommandsResponse();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPIACKNOWLEDGETELECOMMANDSRESPONSE {
		TCPIMESSAGEHEADER  sHeader;
		BOOL  bResult;
	} TCPIACKNOWLEDGETELECOMMANDSRESPONSE, *PTCPIACKNOWLEDGETELECOMMANDSRESPONSE, *LPTCPIACKNOWLEDGETELECOMMANDSRESPONSE;
#pragma pack(pop)
private:
	BOOL  m_bResult;

	// Operations
public:
	BOOL SetResult(BOOL bSuccess);
	BOOL GetResult() CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceDiscardTelecommandsRequest

class CTCProcessInterfaceDiscardTelecommandsRequest : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceDiscardTelecommandsRequest();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPIDISCARDTELECOMMANDSREQUEST {
		TCPIMESSAGEHEADER  sHeader;
		INT  cbItems;
		BOOL  bAcknowledgment;
	} TCPIDISCARDTELECOMMANDSREQUEST, *PTCPIDISCARDTELECOMMANDSREQUEST, *LPTCPIDISCARDTELECOMMANDSREQUEST;
#pragma pack(pop)
private:
	CTCItems  m_pItems;
	BOOL  m_bAcknowledgment;

	// Operations
public:
	BOOL SetTelecommands(CONST CTCItems &pItems);
	INT GetTelecommands(CTCItems &pItems) CONST;
	BOOL EnableAcknowledgment(BOOL bEnable = TRUE);
	BOOL IsAcknowledgmentEnabled() CONST;

	BOOL Reset();

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check(INT cbData) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceDiscardTelecommandsResponse

class CTCProcessInterfaceDiscardTelecommandsResponse : public CTCProcessInterfaceMessageHeader
{
	// Construction
public:
	CTCProcessInterfaceDiscardTelecommandsResponse();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagTCPIDISCARDTELECOMMANDSRESPONSE {
		TCPIMESSAGEHEADER  sHeader;
		BOOL  bResult;
	} TCPIDISCARDTELECOMMANDSRESPONSE, *PTCPIDISCARDTELECOMMANDSRESPONSE, *LPTCPIDISCARDTELECOMMANDSRESPONSE;
#pragma pack(pop)
private:
	BOOL  m_bResult;

	// Operations
public:
	BOOL SetResult(BOOL bSuccess);
	BOOL GetResult() CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceSocket command target

// Specify the telecommand process interface socket related timer identifiers
#define TCPROCESSINTERFACESOCKET_CONNECTION_TIMERID   10000
#define TCPROCESSINTERFACESOCKET_CONNECTION_TIMEOUT   1000

class CTCProcessInterfaceSocket : public CSocket
{
	DECLARE_DYNCREATE(CTCProcessInterfaceSocket)

	// Construction
public:
	CTCProcessInterfaceSocket(class CTCProcessInterfaceThread *pThread = NULL);
	~CTCProcessInterfaceSocket();

	// Attributes
private:
	UINT  m_nFlags;
	HANDLE  m_hIOData;
	CEvent  m_cIOData;
	CByteArray  m_nData[2];
	CTimeSpan  m_tTimeout;
	CString  m_szComputer;
	CTCProcessCommandSources  m_pCommandSources;
	UINT_PTR  m_nTimerID;
private:
	class CTCProcessInterfaceThread  *m_pTCProcessInterfaceThread;

	// Operations
public:
	BOOL Open(CTCProcessInterfaceThread *pThread, UINT nPort, HANDLE hAbort = NULL);
	VOID Close(BOOL bDetach = FALSE);

	VOID Connect(LPCTSTR pszComputer);
	BOOL Connect(LPCTSTR pszComputer, UINT nPort, CONST CTimeSpan &tTimeout = 0);
	BOOL IsConnected(CString &szComputer) CONST;
	BOOL IsConnected() CONST;

	BOOL Send(CONST CByteArray &nData);
	INT SendAndReceive(CByteArray &nData, CONST CTimeSpan &tInterval);
	INT Receive(CByteArray &nData);

public:
	BOOL SetCommandSources(CONST CTCProcessCommandSources &pCommandSources);
	BOOL GetCommandSources(CTCProcessCommandSources &pCommandSources) CONST;
	VOID SetFlags(UINT nFlags);
	UINT GetFlags() CONST;

private:
	DWORD Wait(LPHANDLE hEvents, INT nCount, DWORD dwTimeout);

	// Overrides
public:
	virtual BOOL OnMessagePending();
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceSockets

class CTCProcessInterfaceSockets : public CPtrArray
{
	// Construction
public:
	CTCProcessInterfaceSockets();
	~CTCProcessInterfaceSockets();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCProcessInterfaceSocket *pSocket);

	INT Find(LPCTSTR pszComputer) CONST;

	CTCProcessInterfaceSocket *GetAt(INT nIndex) CONST;
	CTCProcessInterfaceSocket *operator[](INT nIndex) CONST;

	VOID RemoveAll();

private:
	INT FindIndex(LPCTSTR pszComputer, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfacePipeThread thread

class CTCProcessInterfacePipeThread : public CThread
{
	DECLARE_DYNAMIC(CTCProcessInterfacePipeThread)

	// Construction
public:
	CTCProcessInterfacePipeThread();

	// Attributes
private:
	CString  m_szCommandHandler;
	BOOL  m_bExclusive;
private:
	HANDLE  m_hPipe;
	HANDLE  m_hEvent;
private:
	class CTCProcessInterfaceThread  *m_pTCProcessInterfaceThread;

	// Operations
public:
	BOOL Start(class CTCProcessInterfaceThread *pThread, LPCTSTR pszCommandHandler, BOOL bExclusive);
	BOOL Stop();

private:
	BOOL TransactMessage(CONST CByteArray &nOutData, CByteArray &nInData);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcessInterfacePipeThread)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcessInterfacePipeThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceThread thread

// Specify the telecommand process interface thread related timer identifiers
#define TCPROCESSINTERFACETHREAD_CLIENTS_TIMEOUT   1000 
#define TCPROCESSINTERFACETHREAD_UPDATECLIENTS_TIMERID   10001
#define TCPROCESSINTERFACETHREAD_UPDATECLIENTS_TIMEOUT   10000
#define TCPROCESSINTERFACETHREAD_UPDATECOMMANDS_TIMERID   10002
#define TCPROCESSINTERFACETHREAD_UPDATECOMMANDS_TIMEOUT   10000

class CTCProcessInterfaceThread : public CThread
{
	DECLARE_DYNAMIC(CTCProcessInterfaceThread)

	// Construction
public:
	CTCProcessInterfaceThread(class CTCProcessThread *pThread);

	// Attributes
private:
	CTCProcessInterfaceSocket  m_cSocket;
	CTCProcessInterfaceSockets  m_pClientSockets;
	CTCProcessInterfacePipeThread  m_cCommandHandlerThread;
private:
	CTCItems  m_pCommandHandlerItems;
	CStringArray  m_szCommandClients[2];
	CStringArray  m_szCommandHandlerClients[2];
	CTCInterlocks  m_pCommandHandlerInterlocks;
	CTCOnBoardBufferQueues  m_pCommandHandlerQueues;
	CHistoryStoreFiles  m_pCommandHandlerFiles[2];
	CTimeKeyArray  m_tCommandHandlerStartTimes;
	CTimeKeyArray  m_tCommandHandlerStopTimes;
	CUIntArray  m_nCommandHandlerAccessCodes;
	CTimeSpan  m_tCommandHandlerTimeWindow[2];
	CTimeSpan  m_tCommandHandlerTimeout;
	UINT_PTR  m_nCommandHandlerTimerID[3];
	CString  m_szCommandHandlerFileName;
	CString  m_szCommandHandler[3];
	HWND  m_hCommandHandlerWnd;
	UINT  m_nCommandHandlerPort;
	UINT  m_nCommandHandlerOptions;
	UINT  m_nCommandHandlerBufferSize;
	UINT  m_nCommandHandlerTelecommandingMode;
	UINT  m_nCommandHandlerTelecommandingState;
	UINT  m_nCommandHandlerTelecommandingFlags;
	BOOL  m_bCommandHandlerTelecommandingInterlockMode;
	BOOL  m_bCommandHandlerTelecommandingReleaseWaitMode;
	BOOL  m_bCommandHandlerTelecommandingAutoRejectionMode;
	BOOL  m_bCommandHandlerExclusive;
	BOOL  m_bCommandHandlerUpdate;
	BOOL  m_bCommandHandler[3];
	BOOL  m_bCommand[4];
private:
	CEvent  m_cUpdate;
private:
	class CTCProcessThread  *m_pTCProcessThread;

	// Operations
public:
	BOOL Start();
	BOOL Stop();

	BOOL Update(CONST CTCItems &pReleaseItems, CONST CTCItems &pVerificationItems, CONST CTCItems &pInterlockItems, CONST CTCInterlocks &pInterlocks);
	BOOL Update(LPCTSTR pszEvent);
	BOOL Update();

	BOOL AddClient(CTCProcessInterfaceSocket *pSocket);
	BOOL RemoveClient(INT nIndex);

public:
	BOOL SetCommandHandlerConfiguration(LPCTSTR pszPreferredCommandHandler, LPCTSTR pszBackupCommandHandler, BOOL bSelfCommandHandler, BOOL bAnyCommandHandler, BOOL bExclusiveCommandHandler, UINT nCommandHandlerOptions, UINT nCommandHandlerPort, UINT nCommandHandlerBufferSize, CONST CTimeSpan &tCommandHandlerTimeout, CONST CStringArray &szCommandHandlerClients, CONST CUIntArray &nCommandHandlerAccessCodes, CONST CTimeKeyArray &tCommandHandlerStartTimes, CONST CTimeKeyArray &tCommandHandlerStopTimes);
	BOOL SetCommandHandlerConfiguration(UINT nTelecommandingMode, UINT nTelecommandingState, UINT nTelecommandingFlags, BOOL bTelecommandingInterlockMode, BOOL bTelecommandingReleaseWaitMode, BOOL bTelecommandingAutoRejectionMode, CONST CTimeSpan &tVerificationUncertaintyTimeWindow, CONST CTimeSpan &tDefaultReleaseTimeWindow, CONST CHistoryStoreFiles &pHistoryArchivalFiles, CONST CHistoryStoreFiles &pHistoryRetrievalFiles, LPCTSTR pszDefaultHistoryFileName);
	BOOL SetCommandHandlerConfiguration(CONST CTCProcessCommandSources &pCommandSources, UINT nTelecommandingMode, UINT nTelecommandingState, UINT nTelecommandingFlags, BOOL bTelecommandingInterlockMode, BOOL bTelecommandingReleaseWaitMode, BOOL bTelecommandingAutoRejectionMode, CONST CTimeSpan &tVerificationUncertaintyTimeWindow, CONST CTimeSpan &tMaximumExecutionTimePeriod, CONST CTimeSpan &tMaximumTimeCheckPeriod, CONST CTimeSpan &tDefaultReleaseTimeWindow, CONST CHistoryStoreFiles &pHistoryArchivalFiles, CONST CHistoryStoreFiles &pHistoryRetrievalFiles, LPCTSTR pszDefaultHistoryFileName, BOOL bUpdate);
	BOOL SetCommandHandlerConfiguration(LPCTSTR pszOriginator, CONST CTCProcessCommandSources &pCommandSources, UINT nTelecommandingMode, UINT nTelecommandingState, UINT nTelecommandingFlags, BOOL bTelecommandingInterlockMode, BOOL bTelecommandingReleaseWaitMode, BOOL bTelecommandingAutoRejectionMode, CONST CTimeSpan &tVerificationUncertaintyTimeWindow, CONST CTimeSpan &tMaximumExecutionTimePeriod, CONST CTimeSpan &tMaximumTimeCheckPeriod, CONST CTimeSpan &tDefaultReleaseTimeWindow, CONST CHistoryStoreFiles &pHistoryArchivalFiles, CONST CHistoryStoreFiles &pHistoryRetrievalFiles, LPCTSTR pszDefaultHistoryFileName, BOOL bUpdate);
	BOOL GetCommandHandlerConfiguration(CString &szPreferredCommandHandler, CString &szBackupCommandHandler, BOOL &bSelfCommandHandler, BOOL &bAnyCommandHandler, BOOL &bExclusiveCommandHandler, UINT &nCommandHandlerOptions, UINT &nCommandHandlerPort, UINT &nCommandHandlerBufferSize, CTimeSpan &tCommandHandlerTimeout, CStringArray &szCommandHandlerClients, CUIntArray &nCommandHandlerAccessCodes, CTimeKeyArray &tCommandHandlerStartTimes, CTimeKeyArray &tCommandHandlerStopTimes) CONST;
	BOOL GetCommandHandlerConfiguration(UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingFlags, BOOL &bTelecommandingInterlockMode, BOOL &bTelecommandingReleaseWaitMode, BOOL &bTelecommandingAutoRejectionMode, CTimeSpan &tVerificationUncertaintyTimeWindow, CTimeSpan &tDefaultReleaseTimeWindow, CHistoryStoreFiles &pHistoryArchivalFiles, CHistoryStoreFiles &pHistoryRetrievalFiles, CString &szDefaultHistoryFileName) CONST;
	BOOL GetCommandHandlerConfiguration(CTCProcessCommandSources &pCommandSources, UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingFlags, BOOL &bTelecommandingInterlockMode, BOOL &bTelecommandingReleaseWaitMode, BOOL &bTelecommandingAutoRejectionMode, CTimeSpan &tVerificationUncertaintyTimeWindow, CTimeSpan &tMaximumExecutionTimePeriod, CTimeSpan &tMaximumTimeCheckPeriod, CTimeSpan &tDefaultReleaseTimeWindow, CTCItems &pItems, CTCInterlocks &pInterlocks, CHistoryStoreFiles &pHistoryArchivalFiles, CHistoryStoreFiles &pHistoryRetrievalFiles, CString &szDefaultHistoryFileName, HWND hUpdateWnd, UINT_PTR nUpdateTimerID, BOOL &bUpdate);
	BOOL GetCommandHandlerConfiguration(LPCTSTR pszOriginator, CTCProcessCommandSources &pCommandSources, UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingFlags, BOOL &bTelecommandingInterlockMode, BOOL &bTelecommandingReleaseWaitMode, BOOL &bTelecommandingAutoRejectionMode, CTimeSpan &tVerificationUncertaintyTimeWindow, CTimeSpan &tMaximumExecutionTimePeriod, CTimeSpan &tMaximumTimeCheckPeriod, CTimeSpan &tDefaultReleaseTimeWindow, CTCItems &pItems, CTCInterlocks &pInterlocks, CHistoryStoreFiles &pHistoryArchivalFiles, CHistoryStoreFiles &pHistoryRetrievalFiles, CString &szDefaultHistoryFileName, BOOL &bUpdate);
	BOOL SetCommandHandlerContents(CONST CTCItems &pItems, CONST CTCItems &pHistoricalItems, CONST CTCInterlocks &pInterlocks, CONST CTCOnBoardBufferQueues &pQueues);
	BOOL SetCommandHandlerContents(CONST CTCItems &pItems, CONST CTCInterlocks &pInterlocks, CONST CTCOnBoardBufferQueues &pQueues);
	BOOL GetCommandHandlerContents(CTCItems &pItems, CTCItems &pHistoricalItems, CTCInterlocks &pInterlocks, CTCOnBoardBufferQueues &pQueues, BOOL bAny = FALSE) CONST;
	BOOL GetCommandHandlerContents(CTCItems &pItems, CTCInterlocks &pInterlocks, CTCOnBoardBufferQueues &pQueues, BOOL bAny = FALSE) CONST;
	BOOL SetCommandHandlerState(CONST CTCUplinkDevice *pDevice);
	BOOL SetCommandHandlerState(LPCTSTR pszCommandHandler, UINT nState);
	BOOL SetCommandHandlerState(UINT nState);
	BOOL GetCommandHandlerState(CTCUplinkDevice *pDevice) CONST;
	BOOL SetCommandHandlerVerificationUncertaintyTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL GetCommandHandlerVerificationUncertaintyTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL SetCommandHandlerDefaultReleaseTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL GetCommandHandlerDefaultReleaseTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL SetCommandHandlerOptions(UINT nOptions);
	UINT GetCommandHandlerOptions() CONST;
	BOOL UpdateCommandHandler(LPCTSTR pszCommandHandler, BOOL bExclusive);
	BOOL UpdateCommandHandler(CONST CTCItems &pItems, CONST CTCInterlocks &pInterlocks);
	BOOL UpdateCommandHandler(CONST CTCItems &pItems);
	BOOL UpdateCommandHandler(CONST CTCInterlocks &pInterlocks);
	BOOL UpdateCommandHandler(UINT nFlags, BOOL bAll = FALSE);
	BOOL IsCommandHandler() CONST;

	BOOL SetCommandSources(CONST CTCProcessCommandSources &pCommandSources, BOOL bUpdate = FALSE);
	BOOL SetCommandSources(LPCTSTR pszOriginator, CONST CTCProcessCommandSources &pCommandSources, BOOL bUpdate = FALSE);
	BOOL GetCommandSources(CTCProcessCommandSources &pCommandSources) CONST;
	BOOL UpdateCommandSources();
	BOOL UpdateCommandSources(CTCProcessInterfaceSocket *pSocket);
	BOOL UpdateCommandSources(CONST CTCProcessCommandSources &pCommandSources);
	BOOL UpdateCommandSources(CONST CTCProcessCommandSources &pCommandSources, CONST CTCItems &pItems, CONST CTCItems &pHistoricalItems, CONST CTCInterlocks &pInterlocks, CONST CTCOnBoardBufferQueues &pQueues);
	BOOL UpdateCommandSources(CTCProcessCommandSources &pCommandSources, BOOL bUpdate = TRUE);
	BOOL UpdateCommandSources(CTCProcessCommandSources &pCommandSources, CTCItems &pItems, CTCItems &pHistoricalItems, CTCInterlocks &pInterlocks, CTCOnBoardBufferQueues &pQueues, BOOL bUpdate = TRUE);
	BOOL UpdateCommandSources(LPCTSTR pszOriginator, CONST CTCProcessCommandSources &pCommandSources);
	BOOL UpdateCommandSources(LPCTSTR pszOriginator, CONST CTCProcessCommandSources &pCommandSources, CONST CTCItems &pItems, CONST CTCItems &pHistoricalItems, CONST CTCInterlocks &pInterlocks, CONST CTCOnBoardBufferQueues &pQueues);

public:
	BOOL DispatchTelecommands(CONST CTCItems &pItems, BOOL bUndo);
	BOOL ReleaseTelecommands(CONST CTCItems &pItems);
	BOOL UpdateTelecommands(CONST CTCItems &pItems, BOOL bAll = TRUE);
	BOOL UpdateTelecommands(LPCTSTR pszOriginator, CONST CTCItems &pItems, BOOL bAll = TRUE);
	BOOL AcknowledgeTelecommands(CONST CTCItems &pItems);
	BOOL DiscardTelecommands(CONST CTCItems &pItems);
	BOOL ExecuteTelecommand(CONST CTCItem *pItem);
	BOOL ExecuteTelecommand(LPCTSTR pszOriginator, CONST CTCItem *pItem);

public:
	BOOL UpdateTCInterlocks(CONST CTCInterlocks &pInterlocks, BOOL bAll = TRUE);
	BOOL UpdateTCInterlocks(LPCTSTR pszOriginator, CONST CTCInterlocks &pInterlocks, BOOL bAll = TRUE);
	BOOL UpdateTCOnBoardBufferQueues(CONST CTCOnBoardBufferQueues &pQueues, BOOL bAll = TRUE);
	BOOL UpdateTCOnBoardBufferQueues(LPCTSTR pszOriginator, CONST CTCOnBoardBufferQueues &pQueues, BOOL bAll = TRUE);

private:
	BOOL AnnounceCommandHandler(LPCTSTR pszComputer, LPCTSTR pszCommandHandler, BOOL bExclusive, CONST CTimeSpan &tTimeout);
	BOOL RegisterCommandSources(LPCTSTR pszComputer, UINT nPort, CONST CTimeSpan &tTimeout, CTCProcessCommandSources &pCommandSources);
	BOOL UpdateCommandSources(CONST CTCProcessCommandSources &pBackupCommandSources, CONST CTCProcessCommandSources &pCommandSources);
	BOOL UpdateCommandingState(CONST CTCUplinkDevice *pDevice);
	BOOL UpdateCommandingClients();

private:
	BOOL IsShuttingDown() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcessInterfaceThread)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
protected:
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcessInterfaceThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessReleaseThread thread

class CTCProcessReleaseThread : public CThread
{
	DECLARE_DYNAMIC(CTCProcessReleaseThread)

	// Construction
public:
	CTCProcessReleaseThread(class CTCProcessThread *pThread);

	// Attributes
private:
	UINT  m_nState;
	CTCItems  m_pItems;
	CSocket  m_cSocket;
private:
	CEvent  m_bUpdate;
private:
	class CTCProcessThread  *m_pTCProcessThread;

	// Operations
public:
	BOOL Start();
	BOOL Stop();

	BOOL SetState(UINT nState);
	UINT GetState() CONST;

	BOOL Update(CONST CTCProcessEngine *pTCProcessEngine, CONST CTCEnvironment *pTCEnvironment, CONST CTMEnvironment *pTMEnvironment, CONST CTCItems &pItems, CONST CTCInterlocks &pInterlocks, BOOL bRemove = FALSE);
	BOOL Update(CONST CTCProcessEngine *pTCProcessEngine, CONST CTCEnvironment *pTCEnvironment, CONST CTMEnvironment *pTMEnvironment, CONST CTCInterlocks &pTCInterlocks, CTCItems &pItems);
	BOOL Update(CONST CTCProcessEngine *pTCProcessEngine, CONST CTCEnvironment *pTCEnvironment, CONST CTMEnvironment *pTMEnvironment, CONST CTCInterlocks &pTCInterlocks);
	BOOL Update(CONST CTCItems &pReleaseItems, CONST CTCInterlocks &pInterlocks, CTCItems &pItems);
	BOOL Update(CONST CTCInterlocks &pInterlocks, CTCItems &pItems);
	BOOL Update(CONST CTCInterlocks &pInterlocks);
	BOOL Update(UINT nState, CTCItems &pItems);
	BOOL Update(UINT nState);
	BOOL Update();

	BOOL Reset();

	BOOL IsEmpty() CONST;

public:
	BOOL SetContents(CONST CTCItems &pItems);
	BOOL GetContents(CTCItems &pItems) CONST;

private:
	VOID CheckPreTransmissionValidationCondition(CTCItem *pItem) CONST;
	VOID CheckPreExecutionVerificationCondition(CONST CTCProcessEngine *pTCProcessEngine, CONST CTMEnvironment *pTMEnvironment, CTCItem *pItem) CONST;
	BOOL CheckPreExecutionVerificationCondition(CONST CTCItem *pItem, CStringArray &szParameters) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcessReleaseThread)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcessReleaseThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessVerificationThread thread

class CTCProcessVerificationThread : public CThread
{
	DECLARE_DYNAMIC(CTCProcessVerificationThread)

	// Construction
public:
	CTCProcessVerificationThread(class CTCProcessThread *pThread);

	// Attributes
private:
	UINT  m_nState;
	CTCItems  m_pItems;
	CSocket  m_cSocket;
private:
	CEvent  m_bUpdate;
private:
	class CTCProcessThread  *m_pTCProcessThread;

	// Operations
public:
	BOOL Start();
	BOOL Stop();

	BOOL SetState(UINT nState);
	UINT GetState() CONST;

	BOOL Update(CONST CTCItems &pItems, BOOL bRemove = FALSE);
	BOOL Update(CONST CTCProcessEngine *pTCProcessEngine, CONST CTCEnvironment *pTCEnvironment, CONST CTMEnvironment *pTMEnvironment, CONST CTCInterlocks &pTCInterlocks, CTCItems &pItems, CTCInterlocks &pInterlocks);
	VOID Update(INT nDataID, UINT nStatus, BOOL bSuccess);
	BOOL Update();

	BOOL Acknowledge(CONST CTCItems &pItems);
	BOOL Discard(CONST CTCItems &pItems);

	BOOL Reset();

	BOOL IsEmpty() CONST;

public:
	BOOL SetContents(CONST CTCItems &pItems);
	BOOL GetContents(CTCItems &pItems) CONST;

private:
	VOID InitExecutionVerificationData(CTCItem *pItem) CONST;

	VOID CheckPreExecutionVerificationCondition(CONST CTCProcessEngine *pTCProcessEngine, CONST CTMEnvironment *pTMEnvironment, CTCItem *pItem) CONST;
	BOOL CheckPreExecutionVerificationCondition(CONST CTCItem *pItem, CStringArray &szParameters) CONST;
	BOOL CheckExecutionVerificationCondition(CONST CTCProcessEngine *pTCProcessEngine, CONST CTMEnvironment *pTMEnvironment, CONST CTCItem *pItem, UINT nStageID, CONST CTimeTag &tStageStart, CONST CTimeSpan &tUncertainty, CStringArray &szParameters) CONST;
	BOOL CheckExecutionVerificationCondition(CONST CTCItem *pItem, UINT nStageID, CONST CTimeTag &tStageStart, CONST CTimeSpan &tUncertainty, CStringArray &szParameters) CONST;

	BOOL CheckExecutionVerificationTimeWindowClosure(CONST CTMEnvironment *pTMEnvironment, CONST CTCItem *pItem, UINT nStageID) CONST;
	BOOL CheckExecutionVerificationTimeWindowClosure(CONST CTCItem *pItem, UINT nStageID) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcessVerificationThread)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcessVerificationThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessThread thread

// Specify the telecommand process device related identifiers
#define TCPROCESSTHREAD_DEVICE_TIMEOUT   1000
// Specify the telecommand process thread related timer identifiers
#define TCPROCESSTHREAD_UPDATECOMMANDS_TIMERID   10003
#define TCPROCESSTHREAD_UPDATECOMMANDS_TIMEOUT   1000
#define TCPROCESSTHREAD_UPDATEARCHIVES_TIMERID   10004
#define TCPROCESSTHREAD_UPDATEARCHIVES_TIMEOUT   1000

class CTCProcessThread : public CThread
{
	DECLARE_DYNCREATE(CTCProcessThread)

	friend class CTCService;

	// Construction
public:
	CTCProcessThread();
	~CTCProcessThread();

	// Attributes
private:
	typedef struct tagCONFIGURATIONDATA {
		INT  cbSize;
		INT  cbHistoryFiles[2];
		INT  cbDefaultHistoryFileName;
		INT  cbCommandHandler[2];
		INT  cbCommandHandlerClients;
		INT  cbCommandHandlerAccessCodes;
		INT  cbCommandHandlerStartTimes;
		INT  cbCommandHandlerStopTimes;
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
		TIMEKEY  tCommandHandlerTimeout;
		TIMEKEY  tMaximumTimeCheckPeriod;
		TIMEKEY  tMaximumExecutionTimePeriod;
		TIMEKEY  tVerificationUncertaintyTimeWindow;
		TIMEKEY  tDefaultReleaseTimeWindow;
	} CONFIGURATIONDATA, *PCONFIGURATIONDATA, *LPCONFIGURATIONDATA;
	typedef struct tagCONTENTSDATA {
		INT  cbSize;
		INT  cbItems;
		INT  cbQueues;
		INT  cbInterlocks;
		INT  cbParameters;
	} CONTENTSDATA, *PCONTENTSDATA, *LPCONTENTSDATA;
private:
	CTMEnvironment  *m_pTMEnvironment;
	CTCEnvironment  *m_pTCEnvironment;
	CTCProcessEngine  *m_pTCProcessEngine;
private:
	CTCUplinkDevice  m_cTCDevice;
	CTCUplinkDevices  m_pTCDevices;
private:
	CTCInterlocks  m_pTCInterlocks;
	CTCOnBoardBufferQueues  m_pTCOnBoardBufferQueues;
private:
	CPtrArray  m_pTCModules;
	CUIntArray  m_nTCModuleIDs;
private:
	UINT_PTR  m_nCommandUpdateTimerID;
	CEvent  m_cCommandUpdateEvent;
private:
	UINT_PTR  m_nArchiveBufferTimerID;
	CMutex  m_cArchiveBackupFiles;
	BOOL  m_bArchiveBufferFlash;
private:
	CEvent  m_cUpdate[2];
	HANDLE  m_hUpdate;
	BOOL  m_bUpdate;
private:
	BOOL  m_bTestMode;
private:
	CTCProcessReleaseThread  *m_pTCReleaseThread;
	CTCProcessInterfaceThread  *m_pTCInterfaceThread;
	CTCProcessVerificationThread  *m_pTCVerificationThread;
private:
	class CTCManualStackWnd  *m_pTCManualStackWnd;
	class CTCAutomaticStackWnd  *m_pTCAutomaticStackWnd;
	class CTCProceduresMonitorWnd  *m_pTCProceduresMonitorWnd;
	class CTCDiagnosticsOversamplingDumpWnd   *m_pTCDiagnosticsOversamplingDumpWnd;
	class CTCOnBoardBufferQueuesWnd  *m_pTCOnBoardBufferQueuesWnd;
	class CTCOnBoardMemoryImagesWnd  *m_pTCOnBoardMemoryImagesWnd;
	class CTCHistoryWnd  *m_pTCHistoryWnd;

	// Operations
public:
	BOOL Start(LPCTSTR pszName);
	BOOL Suspend();
	BOOL IsSuspended() CONST;
	BOOL Resume();
	VOID Stop();

	BOOL Initialize(CTMEnvironment *pTMEnvironment);
	BOOL Initialize(CTCParameters &pTCParameters);
	BOOL Initialize(CONST CTCItem *pItem, CTCEnvironment *pTCEnvironment);
	BOOL Initialize(CONST CTCEnvironment *pTCEnvironment, CTCItem *pItem);

	VOID Update(CONST CTMProcessEngine *pTMProcessEngine, CONST CTMEnvironment *pTMEnvironment);
	VOID Update(INT nDataID, UINT nStatus, BOOL bSuccess);
	VOID Update(LPCTSTR pszEvent);
	BOOL Update();

public:
	INT EnumTCSubSystems(CStringArray &szSubSystems, BOOL bAll = TRUE) CONST;
	UINT TranslateTCSubSystemToID(LPCTSTR pszSubSystem) CONST;
	CString TranslateIDToTCSubSystem(UINT nSubSystemID) CONST;

	BOOL SetTCUplinkDevices(CONST CTCUplinkDevices &pDevices);
	INT GetTCUplinkDevices(CTCUplinkDevices &pDevices) CONST;
	BOOL HasTCUplinkDevices(BOOL bSupported = FALSE) CONST;
	BOOL SetActiveTCUplinkDevice(CONST CTCUplinkDevice *pDevice);
	BOOL GetActiveTCUplinkDevice(CTCUplinkDevice *pDevice) CONST;
	BOOL StopActiveTCUplinkDevice(HANDLE hDevice = NULL);

	BOOL UpdateTCDisplays(BOOL bProcessData = TRUE);
	BOOL UpdateTCParameters(CONST CTCParameters &pTCParameters);
	BOOL ResetTCParameters();

public:
	BOOL SetCommandHandlerConfiguration(LPCTSTR pszPreferredCommandHandler, LPCTSTR pszBackupCommandHandler, BOOL bSelfCommandHandler, BOOL bAnyCommandHandler, BOOL bExclusiveCommandHandler, UINT nCommandHandlerOptions, UINT nCommandHandlerPort, UINT nCommandHandlerBufferSize, CONST CTimeSpan &tCommandHandlerTimeout, CONST CStringArray &szCommandHandlerClients, CONST CUIntArray &nCommandHandlerAccessCodes, CONST CTimeKeyArray &tCommandHandlerStartTimes, CONST CTimeKeyArray &tCommandHandlerStopTimes);
	BOOL SetCommandHandlerConfiguration(UINT nTelecommandingMode, UINT nTelecommandingState, UINT nTelecommandingFlags, BOOL bTelecommandingInterlockMode, BOOL bTelecommandingReleaseWaitMode, BOOL bTelecommandingAutoRejectionMode, CONST CTimeSpan &tVerificationUncertaintyTimeWindow, CONST CTimeSpan &tMaximumExecutionTimePeriod, CONST CTimeSpan &tMaximumTimeCheckPeriod, CONST CTimeSpan &tDefaultReleaseTimeWindow, CONST CHistoryStoreFiles &pHistoryArchivalFiles, CONST CHistoryStoreFiles &pHistoryRetrievalFiles, LPCTSTR pszDefaultHistoryFileName);
	BOOL SetCommandHandlerConfiguration(CONST CTCProcessCommandSources &pCommandSources, UINT nTelecommandingMode, UINT nTelecommandingState, UINT nTelecommandingFlags, BOOL bTelecommandingInterlockMode, BOOL bTelecommandingReleaseWaitMode, BOOL bTelecommandingAutoRejectionMode, CONST CTimeSpan &tVerificationUncertaintyTimeWindow, CONST CTimeSpan &tMaximumExecutionTimePeriod, CONST CTimeSpan &tMaximumTimeCheckPeriod, CONST CTimeSpan &tDefaultReleaseTimeWindow, CONST CHistoryStoreFiles &pHistoryArchivalFiles, CONST CHistoryStoreFiles &pHistoryRetrievalFiles, LPCTSTR pszDefaultHistoryFileName, BOOL bUpdate);
	BOOL GetCommandHandlerConfiguration(CString &szPreferredCommandHandler, CString &szBackupCommandHandler, BOOL &bSelfCommandHandler, BOOL &bAnyCommandHandler, BOOL &bExclusiveCommandHandler, UINT &nCommandHandlerOptions, UINT &nCommandHandlerPort, UINT &nCommandHandlerBufferSize, CTimeSpan &tCommandHandlerTimeout, CStringArray &szCommandHandlerClients, CUIntArray &nCommandHandlerAccessCodes, CTimeKeyArray &tCommandHandlerStartTimes, CTimeKeyArray &tCommandHandlerStopTimes) CONST;
	BOOL GetCommandHandlerConfiguration(UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingFlags, BOOL &bTelecommandingInterlockMode, BOOL &bTelecommandingReleaseWaitMode, BOOL &bTelecommandingAutoRejectionMode, CTimeSpan &tVerificationUncertaintyTimeWindow, CTimeSpan &tMaximumExecutionTimePeriod, CTimeSpan &tMaximumTimeCheckPeriod, CTimeSpan &tDefaultReleaseTimeWindow, CHistoryStoreFiles &pHistoryArchivalFiles, CHistoryStoreFiles &pHistoryRetrievalFiles, CString &szDefaultHistoryFileName) CONST;
	BOOL GetCommandHandlerConfiguration(CTCProcessCommandSources &pCommandSources, UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingFlags, BOOL &bTelecommandingInterlockMode, BOOL &bTelecommandingReleaseWaitMode, BOOL &bTelecommandingAutoRejectionMode, CTimeSpan &tVerificationUncertaintyTimeWindow, CTimeSpan &tMaximumExecutionTimePeriod, CTimeSpan &tMaximumTimeCheckPeriod, CTimeSpan &tDefaultReleaseTimeWindow, CTCItems &pItems, CTCInterlocks &pInterlocks, CHistoryStoreFiles &pHistoryArchivalFiles, CHistoryStoreFiles &pHistoryRetrievalFiles, CString &szDefaultHistoryFileName, HWND hUpdateWnd, UINT_PTR nUpdateTimerID, BOOL &bUpdate);
	BOOL SetCommandHandlerContents(CONST CTCItems &pItems, CONST CTCItems &pHistoricalItems, CONST CTCInterlocks &pInterlocks, CONST CTCOnBoardBufferQueues &pQueues);
	BOOL SetCommandHandlerContents(CONST CTCItems &pItems, CONST CTCInterlocks &pInterlocks, CONST CTCOnBoardBufferQueues &pQueues);
	BOOL SetCommandHandlerContents(CONST CTCItems &pItems);
	BOOL SetCommandHandlerContents(CONST CTCItems &pItems, CONST CTCInterlocks &pInterlocks);
	BOOL SetCommandHandlerContents(CONST CTCOnBoardBufferQueues &pQueues);
	BOOL GetCommandHandlerContents(CTCItems &pItems, CTCItems &pHistoricalItems, CTCInterlocks &pInterlocks, CTCOnBoardBufferQueues &pQueues, BOOL bAny = FALSE) CONST;
	BOOL GetCommandHandlerContents(CTCItems &pItems, CTCInterlocks &pInterlocks, CTCOnBoardBufferQueues &pQueues, BOOL bAny = FALSE) CONST;
	BOOL GetCommandHandlerContents(CTCItems &pItems) CONST;
	BOOL GetCommandHandlerContents(CTCInterlocks &pInterlocks) CONST;
	BOOL GetCommandHandlerContents(CTCOnBoardBufferQueues &pQueues) CONST;
	BOOL SetCommandHandlerState(CONST CTCUplinkDevice *pDevice);
	BOOL SetCommandHandlerState(UINT nState);
	BOOL GetCommandHandlerState(CTCUplinkDevice *pDevice) CONST;
	UINT GetCommandHandlerState() CONST;
	BOOL SetCommandHandlerVerificationUncertaintyTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL GetCommandHandlerVerificationUncertaintyTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL SetCommandHandlerDefaultReleaseTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL GetCommandHandlerDefaultReleaseTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL SetCommandHandlerOptions(UINT nOptions);
	UINT GetCommandHandlerOptions() CONST;
	BOOL IsCommandHandler() CONST;

	BOOL SetCommandSources(CONST CTCProcessCommandSources &pCommandSources);
	BOOL GetCommandSources(CTCProcessCommandSources &pCommandSources) CONST;
	BOOL UpdateCommandSources(LPCTSTR pszOriginator, CONST CTCProcessCommandSources &pCommandSources);
	BOOL UpdateCommandSources(LPCTSTR pszOriginator, CONST CTCProcessCommandSources &pCommandSources, CONST CTCItems &pItems, CONST CTCItems &pHistoricalItems, CONST CTCInterlocks &pInterlocks, CONST CTCOnBoardBufferQueues &pQueues);
	BOOL SetCommandSourceTelecommandingMode(LPCTSTR pszComputerName, UINT nSourceType, UINT nMode);
	UINT GetCommandSourceTelecommandingMode(LPCTSTR pszComputerName, UINT nSourceType) CONST;
	BOOL SetCommandSourceTelecommandingState(LPCTSTR pszComputerName, UINT nSourceType, UINT nState);
	UINT GetCommandSourceTelecommandingState(LPCTSTR pszComputerName, UINT nSourceType) CONST;
	BOOL SetCommandSourceTelecommandingChecks(LPCTSTR pszComputerName, UINT nSourceType, UINT nFlags);
	UINT GetCommandSourceTelecommandingChecks(LPCTSTR pszComputerName, UINT nSourceType) CONST;
	BOOL EnableCommandSourceTelecommandingInterlockMode(LPCTSTR pszComputerName, UINT nSourceType, BOOL bEnable = TRUE);
	BOOL IsCommandSourceTelecommandingInterlockModeEnabled(LPCTSTR pszComputerName, UINT nSourceType) CONST;
	BOOL EnableCommandSourceTelecommandingReleaseWaitMode(LPCTSTR pszComputerName, UINT nSourceType, BOOL bEnable = TRUE);
	BOOL IsCommandSourceTelecommandingReleaseWaitModeEnabled(LPCTSTR pszComputerName, UINT nSourceType) CONST;
	BOOL EnableCommandSourceTelecommandingAutoRejectionMode(LPCTSTR pszComputerName, UINT nSourceType, BOOL bEnable = TRUE);
	BOOL IsCommandSourceTelecommandingAutoRejectionModeEnabled(LPCTSTR pszComputerName, UINT nSourceType) CONST;
	BOOL SetCommandSourceSubSystemChecks(LPCTSTR pszComputerName, UINT nSourceType, CONST CUIntArray &nSubSystemIDs, CONST CStringArray &szEnablingEvents, CONST CStringArray &szDisablingEvents, CONST CUIntArray &nStatus);
	BOOL GetCommandSourceSubSystemChecks(LPCTSTR pszComputerName, UINT nSourceType, CUIntArray &nSubSystemIDs, CStringArray &szEnablingEvents, CStringArray &szDisablingEvents, CUIntArray &nStatus) CONST;
	BOOL IsCommandSourceSubSystemEnabled(LPCTSTR pszComputerName, UINT nSourceType, CONST CTCItem *pItem) CONST;
	BOOL SetDefaultReleaseTimeWindow(LPCTSTR pszComputerName, UINT nSourceType, CONST CTimeSpan &tTimeWindow);
	CTimeSpan GetDefaultReleaseTimeWindow(LPCTSTR pszComputerName, UINT nSourceType) CONST;
	BOOL SetDispatchTimeWindow(LPCTSTR pszComputerName, UINT nSourceType, CONST CTimeSpan &tTimeWindow);
	CTimeSpan GetDispatchTimeWindow(LPCTSTR pszComputerName, UINT nSourceType) CONST;

public:
	BOOL AuthorizeTelecommands(CTCItems &pItems);
	BOOL LoadTelecommands(CONST CTCItems &pItems);
	BOOL DispatchTelecommands(CONST CTCItems &pItems, BOOL bUndo = FALSE);
	BOOL ReleaseTelecommands(CONST CTCItems &pItems);
	BOOL UpdateTelecommands(CONST CTCItems &pItems, BOOL bAll = TRUE);
	VOID UpdateTelecommands(LPCTSTR pszOriginator, CONST CTCItems &pItems, BOOL bAll = TRUE);
	BOOL AcknowledgeTelecommands(CONST CTCItems &pItems);
	BOOL DiscardTelecommands(CONST CTCItems &pItems);
	BOOL ExecuteTelecommand(CONST CTCItem *pItem);
	BOOL ExecuteTelecommand(LPCTSTR pszOriginator, CONST CTCItem *pItem);

public:
	BOOL GenerateTCPackets(CONST CDatabaseTCFunction *pFunction, CONST CDatabaseTCPacket *pPacket, LPCTSTR pszMemoryPatch, BOOL bTimeTagged, BOOL b2ndStep, BOOL bBlocked, BOOL bExample, CDatabaseTCFunctions &pFunctions, CDatabaseTCPackets &pPackets) CONST;
	BOOL InitializeTCPacket(CONST CDatabaseTCFunction *pFunction, CONST CDatabaseTCPacket *pPacket, CTCPacket *pTCPacket, CONST CTimeTag &tExecutionTime, BOOL bBlocked = FALSE, BOOL bExample = FALSE) CONST;
	BOOL InitializeTCPacket(CTCItem *pItem, CDatabaseTCPacket *pPacket) CONST;
	BOOL InitializeTCPacket(CONST CTCItem *pItem, CDatabaseTCFunction *pFunction, CDatabaseTCPacket *pPacket, INT nSubEntry) CONST;
	BOOL CollectTCPacket(CDatabaseTCFunction *pFunction, CTCPacket *pTCPacket, INT nBlockID) CONST;
	BOOL DecodeTCPacket(CONST CTCPacket *pTCPacket, CDatabaseTCFunction *pDatabaseTCFunction, CDatabaseTCFunctions &pDatabaseBlockedTCFunctions, CDatabaseTCPacket *pDatabaseTCPacket) CONST;
	BOOL CheckTCFunctionExecutionTime(CONST CDatabaseTCFunction *pDatabaseTCFunction, CONST CDatabaseTCPacket *pDatabaseTCPacket, CONST CTimeTag &tExecutionTime = 0) CONST;
	BOOL SetTCFunctionExecutionTimeOffsets(CONST CTimeSpan &tMin, CONST CTimeSpan &tMax);
	BOOL GetTCFunctionExecutionTimeOffsets(CTimeSpan &tMin, CTimeSpan &tMax) CONST;
	BOOL SetTCFunctionParameterTimeOffsets(CONST CTimeSpan &tMin, CONST CTimeSpan &tMax);
	BOOL GetTCFunctionParameterTimeOffsets(CTimeSpan &tMin, CTimeSpan &tMax) CONST;
	BOOL ConvertTCParameterValue(LPCTSTR pszTag, ULONGLONG nAttributes, LPCTSTR pszValue, ULONGLONG &nValue) CONST;
	BOOL ConvertTCParameterValue(CONST CDatabaseTCParameter *pDatabaseTCParameter, ULONGLONG &nValue) CONST;
	BOOL CheckTCParameterOolStatus(CONST CDatabaseTCParameter *pParameter, UINT &nOolStatus) CONST;
	BOOL CheckTCFunctionElementOolStatus(CONST CDatabaseTCFunctionElement *pFunctionElement, UINT &nOolStatus) CONST;
	BOOL CheckTCPacketParameterOolStatus(CONST CDatabaseTCPacketParameter *pPacketParameter, UINT &nOolStatus) CONST;
	BOOL CheckTCProcedureArgumentOolStatus(CONST CDatabaseTCProcedureArgument *pArgument, UINT &nOolStatus) CONST;
	BOOL CheckTCFunctionPreexecutionParameterGroup(INT nGroupID, CStringArray &szParameters) CONST;
	BOOL CheckTCFunctionExecutionParameterGroup(CONST CTCItem *pItem, INT nGroupID, INT nStageID, CONST CTimeTag &tStageStart, CONST CTimeSpan &tUncertainty, CStringArray &szParameters) CONST;

	BOOL SetTCInterlocks(CONST CTCInterlocks &pInterlocks);
	BOOL SetTCInterlocks(UINT nSourceType, CONST CTCInterlocks &pInterlocks);
	BOOL GetTCInterlocks(CTCInterlocks &pInterlocks) CONST;
	BOOL GetTCInterlocks(UINT nSourceType, CTCInterlocks &pInterlocks) CONST;
	BOOL UpdateTCInterlocks(CONST CTCInterlocks &pInterlocks, BOOL bAll = TRUE);
	VOID UpdateTCInterlocks(LPCTSTR pszOriginator, CONST CTCInterlocks &pInterlocks, BOOL bAll = TRUE);
	BOOL CheckTCInterlocks(UINT nSourceType, UINT nState) CONST;
	BOOL CheckTCInterlock(UINT nSourceType, LPCTSTR pszInterlock, UINT &nState) CONST;
	BOOL CheckTCInterlock(UINT nSourceType, LPCTSTR pszInterlock, UINT &nScope, UINT &nStage, UINT &nState) CONST;
	BOOL CheckTCInterlock(CONST CTCItem *pItem) CONST;

	INT EnumTCDiagnosticsOversamplingDumpRates(CStringArray &szRates) CONST;
	BOOL EncodeTCDiagnosticsOversamplingDump(CONST CTimeTag &tExecutionTime, CONST COversamplingParameters &pOversamplingParameters, CDatabaseTCFunction *pDatabaseTCFunction);
	BOOL DecodeTCDiagnosticsOversamplingDump(CONST CDatabaseTCFunction *pDatabaseTCFunction, COversamplingParameters &pOversamplingParameters);
	BOOL DecodeTCDiagnosticsOversamplingDump(CONST CTMEnvironment *pTMEnvironment, COversamplingParameters &pOversamplingParameters, BOOL bAutomatic);
	double CalculateTCDiagnosticsOversamplingBandwidth(COversamplingParameters &pOversamplingParameters) CONST;

	INT EnumTCOnBoardBufferTypes(CStringArray &szTypes) CONST;
	INT EnumTCOnBoardBufferQueues(CTCOnBoardBufferQueues &pQueues) CONST;
	INT EnumTCOnBoardBufferQueues(LPCTSTR pszType, CStringArray &szNames) CONST;
	INT EnumTCOnBoardBufferQueues(LPCTSTR pszType, CStringArray &szNames, CUIntArray &nAPIDs, CUIntArray &nSubScheduleIDs, CUIntArray &nLimits, CStringArray &szUnits, CUIntArray &tTimeouts) CONST;
	INT UpdateTCOnBoardBufferQueues(CONST CTMEnvironment *pTMEnvironment, CStringArray &szTypes, CStringArray &szNames, CUIntArray &nSubScheduleIDs, CUIntArray &nCounts, CTimeTagArray &tUpdateTimes, CUIntArray &nStatus);
	BOOL UpdateTCOnBoardBufferQueues(CONST CTCOnBoardBufferQueues &pQueues, BOOL bAll = TRUE);
	VOID UpdateTCOnBoardBufferQueues(LPCTSTR pszOriginator, CONST CTCOnBoardBufferQueues &pQueues, BOOL bAll = TRUE);
	BOOL CheckTCOnBoardBufferQueues(CONST CTCItems &pItems, INT nChecks = -1) CONST;
	BOOL UpdateTCOnBoardBufferQueue(LPCTSTR pszType, LPCTSTR pszName, UINT nSubScheduleID, CONST CTCItems &pItems);
	BOOL UpdateTCOnBoardBufferQueue(LPCTSTR pszType, LPCTSTR pszName, UINT nSubScheduleID, UINT nFlags, UINT nAPID = -1, UINT nPSC = -1, INT nLowEntry = -1, INT nHighEntry = -1, CONST CTimeKey &tStartTime = 0, CONST CTimeKey &tStopTime = 0);
	BOOL AcknowledgeTCOnBoardBufferQueue(LPCTSTR pszType, LPCTSTR pszName, UINT nSubScheduleID, UINT nFlags = TCONBOARDBUFFERQUEUE_ALERTTYPE_ANY);
	BOOL CheckTCOnBoardBufferQueue(LPCTSTR pszType, LPCTSTR pszName, BOOL &bStatus, BOOL &bDumpAllEntries, BOOL &bDumpByAPID, BOOL &bDumpByPSC, BOOL &bDumpByEntryRange, BOOL &bDumpByTimeRange, BOOL &bResetAllEntries, BOOL &bResetByAPID, BOOL &bResetByPSC, BOOL &bResetByEntryRange, BOOL &bResetByTimeRange) CONST;
	BOOL CheckTCOnBoardBufferQueue(CONST CTCItem *pItem) CONST;
	BOOL EncodeTCOnBoardBufferQueueStatus(LPCTSTR pszType, LPCTSTR pszName, CONST CTimeTag &tExecutionTime, BOOL bEnable, CDatabaseTCFunction *pDatabaseTCFunction) CONST;
	BOOL EncodeTCOnBoardBufferQueueDump(LPCTSTR pszType, LPCTSTR pszName, CONST CTimeTag &tExecutionTime, UINT nAPID, UINT nPSC, UINT nLowEntry, UINT nHighEntry, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, CDatabaseTCFunction *pDatabaseTCFunction) CONST;
	BOOL EncodeTCOnBoardBufferQueueReset(LPCTSTR pszType, LPCTSTR pszName, CONST CTimeTag &tExecutionTime, UINT nAPID, UINT nPSC, UINT nLowEntry, UINT nHighEntry, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, CONST CTCPacket *pTCPacket, CDatabaseTCFunction *pDatabaseTCFunction) CONST;
	BOOL FindTCOnBoardBufferQueue(CONST CTCPacket *pTCPacket, CString &szType, CString &szName, UINT &nSubScheduleID) CONST;
	BOOL ExpandTCOnBoardBufferQueueEntry(CONST CTCPacket *pTCPacket, UINT &nBlockOffset, UINT &nBlockBytes, CUIntArray &nBlockSizes, CTimeTagArray &tBlockTimes) CONST;
	UINT CalculateTCOnBoardBufferQueueEntry(CONST CTCPacket *pTCPacket) CONST;

	BOOL CheckTCOnBoardMemoryImageDumpCapabilities(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, BOOL &bStop) CONST;
	BOOL EncodeTCOnBoardMemoryImageDump(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, CONST CTimeKey &tExecutionTime, BOOL bStop, CDatabaseTCFunction *pDatabaseTCFunction);
	BOOL IsTCOnBoardMemoryImageDump(CONST CTMEnvironment *pTMEnvironment) CONST;
	BOOL CheckTCOnBoardMemoryImagePatchCapabilities(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage) CONST;
	BOOL EncodeTCOnBoardMemoryImagePatch(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, CONST CTimeKey &tExecutionTime, CDatabaseTCFunctions &pDatabaseTCFunctions, CDatabaseTCPackets &pDatabaseTCPackets);
	BOOL CalculateTCOnBoardMemoryImageCRC(CONST CDatabaseOBProcessor *pProcessor, CDatabaseOBProcessorMemoryImage *pImage, LPCTSTR pszImageVersion) CONST;
	BOOL IsTCOnBoardMemoryImagePatch(CONST CTCPacket *pTCPacket, CString &szProcessor) CONST;

	BOOL ConvertTimeToOBRT(CONST CTimeTag &tOBRT, UINT &nOBRT) CONST;
	BOOL ConvertOBRTToTime(UINT nOBRT, CTimeTag &tOBRT) CONST;

	BOOL CorrelateTCTransferFrameSequenceNumber();
	BOOL CanCorrelateTCTransferFrameSequenceNumber() CONST;

	BOOL EnableTestMode(BOOL bEnable = TRUE);
	BOOL IsTestModeEnabled() CONST;

private:
	BOOL Initialize();
	BOOL Uninitialize();

	BOOL Initialize(CTCItems &pItems) CONST;
	BOOL Initialize(LPCTSTR pszProcedure, INT nProcedureID, INT nProcessID, LPCTSTR pszThread, LPCTSTR pszStep, LPCTSTR pszSequence, LPCTSTR pszFunction, BOOL bProcedure, INT nEntry, INT nEntries, CONST CTimeTag &tScheduleTime, CONST CTimeTag &tReleaseTime, DWORD dwReleaseOffset, CONST CTimeTag &tExecutionTime, DWORD dwExecutionOffset, BOOL bEarlierExecution, INT nBlockID, BOOL bGrouped, BOOL bCritical, UINT nExecutionMode, ULONGLONG nAckFlags, HINSTANCE hModule, HANDLE hSuccess, HANDLE hFailure, CTCItem *pItem) CONST;
	BOOL Initialize(HINSTANCE hModule, LPCTSTR pszName, INT nID, CONST CPtrArray &hEvents, CONST CTMEnvironment *pTMEnvironment, CTCItem *pItem);
	BOOL Update(HINSTANCE hModule, INT nID, CONST CTMEnvironment *pTMEnvironment);

	BOOL SetDevice(CONST CTCUplinkDevice *pDevice);
	BOOL GetDevice(CTCUplinkDevice *pDevice) CONST;
	BOOL StartDevice(CTCUplinkDevice *pDevice);
	BOOL StartDevice();
	VOID StopDevice();

	BOOL StartDisplay(INT nType, BOOL bRestart = TRUE);
	BOOL StopDisplay(INT nType);

	BOOL InitializeData();
	BOOL SetContentsData(CONST CByteArray &nData);
	BOOL GetContentsData(CByteArray &nData) CONST;
	BOOL SetProcessData(CONST CByteArray &nData);
	BOOL GetProcessData(CByteArray &nData) CONST;
	BOOL UpdateProcessData(CONST BYTE *pData);

	VOID UpdateQueues();
	VOID UpdateQueues(CONST CPtrArray &pInfo);

	VOID UpdateArchives();
	VOID UpdateArchives(CONST CTCItems &pItems);

	BOOL UpdateCommandLinkControlWord(DWORD dwCLCW);

	BOOL DoBackup(CONST CHistoryStoreFile *pFile, BOOL bDelayed = TRUE);

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcessThread)
public:
	virtual int Run();
protected:
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcessThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCArchivesBackupThread thread

// Specify the telecommand archives backup delay interval
#define TELECOMMANDARCHIVESBACKUP_DELAY_INTERVAL   SECONDSPERMINUTE
// Specify the telecommand archives backup copy buffer size
#define TELECOMMANDARCHIVESBACKUP_COPY_BUFFER   4096

class CTCArchivesBackupThread : public CThread
{
	DECLARE_DYNCREATE(CTCArchivesBackupThread)

	// Construction
public:

	// Attributes
private:
	HANDLE  m_hSync;
	HANDLE  m_bQuit;
	CString  m_szFileName[3];
	CHistoryStoreFile  m_cFile;

	// Operations
public:
	BOOL Start(CONST CHistoryStoreFile *pFile, BOOL bDelayed, HANDLE hSync, HANDLE bQuit);
	BOOL Stop();

private:
	VOID Alert(CONST CHistoryStoreFile *pFile, BOOL bSuccess);

	BOOL TestDirectory(LPCTSTR pszFileName) CONST;

	BOOL DelayBackup();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCArchivesBackupThread)
public:
	virtual int Run();
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCArchivesBackupThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCService

// Specify the telecommand service interface related settings
#define TCSERVICE_COMMANDINTERFACE_FIRSTPORT   1024
#define TCSERVICE_COMMANDINTERFACE_LASTPORT   65535
#define TCSERVICE_COMMANDINTERFACE_DEFAULTPORT   50003
#define TCSERVICE_COMMANDINTERFACE_MINIMUMBUFFERSIZE   (16*1024)
#define TCSERVICE_COMMANDINTERFACE_MAXIMUMBUFFERSIZE   (1024*1024)
#define TCSERVICE_COMMANDINTERFACE_DEFAULTBUFFERSIZE   (64*1024)
#define TCSERVICE_COMMANDINTERFACE_MINIMUMTIMEOUT   1
#define TCSERVICE_COMMANDINTERFACE_MAXIMUMTIMEOUT   SECONDSPERMINUTE
#define TCSERVICE_COMMANDINTERFACE_DEFAULTTIMEOUT   5
// Specify the telecommand service interface related access codes
#define TCSERVICE_COMMANDINTERFACE_UNLIMITEDACCESS   (1<<0)
#define TCSERVICE_COMMANDINTERFACE_LIMITEDACCESS   (1<<1)
#define TCSERVICE_COMMANDINTERFACE_NOACCESS   (1<<2)
#define TCSERVICE_COMMANDINTERFACE_AUDITACCESS   (1<<3)
// Specify the telecommand service interface related update flags
#define TCSERVICE_COMMANDINTERFACE_NOUPDATE   0
#define TCSERVICE_COMMANDINTERFACE_CONFIGURATIONUPDATE   (1<<0)
#define TCSERVICE_COMMANDINTERFACE_TELECOMMANDSUPDATE   (1<<1)
#define TCSERVICE_COMMANDINTERFACE_INTERLOCKSUPDATE   (1<<2)
#define TCSERVICE_COMMANDINTERFACE_QUEUESUPDATE   (1<<3)
#define TCSERVICE_COMMANDINTERFACE_HOTLINKUPDATE   (1<<4)
// Specify the telecommand service related command source types
#define TCSERVICE_COMMANDSOURCETYPE_NONE   0
#define TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK   (1<<0)
#define TCSERVICE_COMMANDSOURCETYPE_AUTOMATICSTACK   (1<<1)
#define TCSERVICE_COMMANDSOURCETYPE_PROCEDURESMONITOR   (1<<2)
#ifndef RC_INVOKED
#define TCSERVICE_COMMANDSOURCETYPE_ALL   (TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK | TCSERVICE_COMMANDSOURCETYPE_AUTOMATICSTACK | TCSERVICE_COMMANDSOURCETYPE_PROCEDURESMONITOR)
#endif
// Specify the telecommand service related command source modes
#define TCSERVICE_COMMANDSOURCEMODE_DEFAULT   (1<<0)
#define TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL   (1<<1)
// Specify the telecommand service related command source flags
#define TCSERVICE_COMMANDSOURCEFLAGS_DEFAULT   0
#define TCSERVICE_COMMANDSOURCEFLAGS_PTV_OVERRIDE   (1<<0)
#define TCSERVICE_COMMANDSOURCEFLAGS_PEV_OVERRIDE   (1<<1)
#define TCSERVICE_COMMANDSOURCEFLAGS_CEV_OVERRIDE   (1<<2)
#define TCSERVICE_COMMANDSOURCEFLAGS_PTV_DISABLE   (1<<3)
#define TCSERVICE_COMMANDSOURCEFLAGS_PEV_DISABLE   (1<<4)
#define TCSERVICE_COMMANDSOURCEFLAGS_CEV_DISABLE   (1<<5)
#define TCSERVICE_COMMANDSOURCEFLAGS_PREAUTHORIZED   (1<<6)
#define TCSERVICE_COMMANDSOURCEFLAGS_AUTHORIZEABLE   (1<<7)
// Specify the telecommand service related command source states
#define TCSERVICE_COMMANDSOURCESTATE_DEFAULT   (1<<0)
#define TCSERVICE_COMMANDSOURCESTATE_SUSPENDED   (1<<1)
#define TCSERVICE_COMMANDSOURCESTATE_STOPPED   (1<<2)
#define TCSERVICE_COMMANDSOURCESTATE_DISABLED   (1<<3)
#define TCSERVICE_COMMANDSOURCESTATE_EMPTY   (1<<4)
// Specify the telecommand service related command options
#define TCSERVICE_COMMANDSOURCEOPTION_NONE   0
#define TCSERVICE_COMMANDSOURCEOPTION_ALWAYSALLOWEXIT   (1<<0)
#define TCSERVICE_COMMANDSOURCEOPTION_UNDISPATCHONEXIT   (1<<1)
// Specify the telecommand service command handler options
#define TCSERVICE_COMMANDHANDLEROPTION_NONE   0
#define TCSERVICE_COMMANDHANDLEROPTION_ALWAYSALLOWEXIT   (1<<0)
// Specify the telecommand service command handler default time windows
#define TCSERVICE_COMMANDHANDLERTIMEWINDOW_VERIFICATIONUNCERTAINTYINTERVAL   (SECONDSPERMINUTE/4)
#define TCSERVICE_COMMANDHANDLERTIMEWINDOW_DEFAULTRELEASEINTERVAL   (5*SECONDSPERMINUTE)
#define TCSERVICE_COMMANDHANDLERTIMEWINDOW_DISPATCHINTERVAL   (SECONDSPERMINUTE/4)
// Specify the telecommand service command handler state codes
#define TCSERVICE_COMMANDHANDLERSTATE_NONE   0
#define TCSERVICE_COMMANDHANDLERSTATE_RUNNING   (1<<0)
#define TCSERVICE_COMMANDHANDLERSTATE_STOPPED   (1<<1)
#define TCSERVICE_COMMANDHANDLERSTATE_ENABLED   (1<<2)
#define TCSERVICE_COMMANDHANDLERSTATE_DISABLED   (1<<3)
#define TCSERVICE_COMMANDHANDLERSTATE_EMPTY   (1<<4)
#define TCSERVICE_COMMANDHANDLERSTATE_LINK_GOOD   (1<<5)
#define TCSERVICE_COMMANDHANDLERSTATE_LINK_BAD   (1<<6)
#define TCSERVICE_COMMANDHANDLERSTATE_FRONTENDLINK_GOOD   (1<<7)
#define TCSERVICE_COMMANDHANDLERSTATE_FRONTENDLINK_BAD   (1<<8)
#define TCSERVICE_COMMANDHANDLERSTATE_FRONTEND_OK   (1<<9)
#define TCSERVICE_COMMANDHANDLERSTATE_FRONTEND_NOTOK   (1<<10)

class CTCService : public CObject
{
	// Construction
public:
	CTCService();

	// Attributes
private:
	typedef struct tagSERVICEINFO {
		INT  cbSize;
		INT  cbServiceInfo[2];
		INT  cbArchivesSettingsInfo;
	} SERVICEINFO, *PSERVICEINFO, *LPSERVICEINFO;
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbDevicesData;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szLoggingFileName[2];
	DWORDLONG  m_dwLoggingRetention;
	CTimeSpan  m_tLoggingRetention;
	UINT  m_nLoggingReloadCount;
	UINT  m_nLoggingPolicy;
	BOOL  m_bLoggingAsEvent;
private:
	CTCProcessThread  m_cTCProcessThread;
private:
	CHistoryStore  m_cTCHistoryStore;
private:
	CTimeKey  m_tLastTCRetrieveTime;

	// Operations
public:
	BOOL Start(LPCTSTR pszName);
	BOOL Suspend();
	BOOL IsSuspended() CONST;
	BOOL Resume();
	VOID Stop();

	BOOL Initialize(CTMEnvironment *pTMEnvironment);
	BOOL Initialize(CTCParameters &pTCParameters);
	BOOL Initialize(CONST CTCItem *pItem, CTCEnvironment *pTCEnvironment);
	BOOL Initialize(CONST CTCEnvironment *pTCEnvironment, CTCItem *pItem);

	VOID Update(CONST CTMProcessEngine *pTMProcessEngine, CONST CTMEnvironment *pTMEnvironment);
	VOID Update(INT nDataID, UINT nStatus, BOOL bSuccess);
	VOID Update(LPCTSTR pszEvent);
	BOOL Update();

public:
	INT EnumTCSubSystems(CStringArray &szSubSystems, BOOL bAll = TRUE) CONST;
	UINT TranslateTCSubSystemToID(LPCTSTR pszSubSystem) CONST;
	CString TranslateIDToTCSubSystem(UINT nSubSystemID) CONST;

	BOOL SetTCUplinkDevices(CONST CTCUplinkDevices &pDevices);
	INT GetTCUplinkDevices(CTCUplinkDevices &pDevices) CONST;
	BOOL HasTCUplinkDevices(BOOL bSupported = FALSE) CONST;
	BOOL SetActiveTCUplinkDevice(CONST CTCUplinkDevice *pDevice);
	BOOL GetActiveTCUplinkDevice(CTCUplinkDevice *pDevice) CONST;

	BOOL SetTCHistoryFiles(UINT nType, CONST CHistoryStoreFiles &pFiles);
	INT GetTCHistoryFiles(UINT nType, CHistoryStoreFiles &pFiles) CONST;
	INT UpdateTCHistoryFiles(CONST CTCEnvironment *pTCEnvironment, CHistoryStoreFiles &pFiles, CUIntArray &nErrors);
	INT UpdateTCHistoryFiles(CHistoryStoreFiles &pFiles, CUIntArray &nErrors);
	BOOL SetDefaultTCHistoryFile(UINT nType, CONST CHistoryStoreFile &cFile);
	BOOL GetDefaultTCHistoryFile(UINT nType, CHistoryStoreFile &cFile) CONST;

	BOOL SetRecentTCHistoryTimeKey(CONST CTimeKey &tTime);
	BOOL GetRecentTCHistoryTimeKey(CTimeKey &tTime) CONST;

	BOOL UpdateTCDisplays(BOOL bProcessData = TRUE);
	BOOL UpdateTCParameters(CONST CTCParameters &pTCParameters);
	BOOL ResetTCParameters();

public:
	BOOL SetCommandHandlerConfiguration(LPCTSTR pszPreferredCommandHandler, LPCTSTR pszBackupCommandHandler, BOOL bSelfCommandHandler, BOOL bAnyCommandHandler, BOOL bExclusiveCommandHandler, UINT nCommandHandlerOptions, UINT nCommandHandlerPort, UINT nCommandHandlerBufferSize, CONST CTimeSpan &tCommandHandlerTimeout, CONST CStringArray &szCommandHandlerClients, CONST CUIntArray &nCommandHandlerAccessCodes, CONST CTimeKeyArray &tCommandHandlerStartTimes, CONST CTimeKeyArray &tCommandHandlerStopTimes);
	BOOL SetCommandHandlerConfiguration(CONST CTCProcessCommandSources &pCommandSources, UINT nTelecommandingMode, UINT nTelecommandingState, UINT nTelecommandingFlags, BOOL bTelecommandingInterlockMode, BOOL bTelecommandingReleaseWaitMode, BOOL bTelecommandingAutoRejectionMode, CONST CTimeSpan &tVerificationUncertaintyTimeWindow, CONST CTimeSpan &tMaximumExecutionTimePeriod, CONST CTimeSpan &tMaximumTimeCheckPeriod, CONST CTimeSpan &tDefaultReleaseTimeWindow, CONST CHistoryStoreFiles &pHistoryArchivalFiles, CONST CHistoryStoreFiles &pHistoryRetrievalFiles, LPCTSTR pszDefaultHistoryFileName, BOOL bUpdate);
	BOOL GetCommandHandlerConfiguration(CString &szPreferredCommandHandler, CString &szBackupCommandHandler, BOOL &bSelfCommandHandler, BOOL &bAnyCommandHandler, BOOL &bExclusiveCommandHandler, UINT &nCommandHandlerOptions, UINT &nCommandHandlerPort, UINT &nCommandHandlerBufferSize, CTimeSpan &tCommandHandlerTimeout, CStringArray &szCommandHandlerClients, CUIntArray &nCommandHandlerAccessCodes, CTimeKeyArray &tCommandHandlerStartTimes, CTimeKeyArray &tCommandHandlerStopTimes) CONST;
	BOOL GetCommandHandlerConfiguration(CTCProcessCommandSources &pCommandSources, UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingFlags, BOOL &bTelecommandingInterlockMode, BOOL &bTelecommandingReleaseWaitMode, BOOL &bTelecommandingAutoRejectionMode, CTimeSpan &tVerificationUncertaintyTimeWindow, CTimeSpan &tMaximumExecutionTimePeriod, CTimeSpan &tMaximumTimeCheckPeriod, CTimeSpan &tDefaultReleaseTimeWindow, CTCItems &pItems, CTCInterlocks &pInterlocks, CHistoryStoreFiles &pHistoryArchivalFiles, CHistoryStoreFiles &pHistoryRetrievalFiles, CString &szDefaultHistoryFileName, HWND hUpdateWnd, UINT_PTR nUpdateTimerID, BOOL &bUpdate);
	BOOL SetCommandHandlerContents(CONST CTCItems &pItems, CONST CTCInterlocks &pInterlocks, CONST CTCOnBoardBufferQueues &pQueues);
	BOOL GetCommandHandlerContents(CTCItems &pItems, CTCInterlocks &pInterlocks, CTCOnBoardBufferQueues &pQueues) CONST;
	BOOL SetCommandHandlerVerificationUncertaintyTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL GetCommandHandlerVerificationUncertaintyTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL SetCommandHandlerDefaultReleaseTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL GetCommandHandlerDefaultReleaseTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL SetCommandHandlerOptions(UINT nOptions);
	UINT GetCommandHandlerOptions() CONST;
	BOOL SetCommandHandlerState(UINT nState);
	UINT GetCommandHandlerState() CONST;

	BOOL SetCommandSourceTelecommandingMode(UINT nSourceType, UINT nMode);
	UINT GetCommandSourceTelecommandingMode(UINT nSourceType) CONST;
	BOOL SetCommandSourceTelecommandingState(UINT nSourceType, UINT nState);
	UINT GetCommandSourceTelecommandingState(UINT nSourceType) CONST;
	BOOL SetCommandSourceTelecommandingChecks(UINT nSourceType, UINT nFlags);
	UINT GetCommandSourceTelecommandingChecks(UINT nSourceType) CONST;
	BOOL EnableCommandSourceTelecommandingInterlockMode(UINT nSourceType, BOOL bEnable = TRUE);
	BOOL IsCommandSourceTelecommandingInterlockModeEnabled(UINT nSourceType) CONST;
	BOOL EnableCommandSourceTelecommandingReleaseWaitMode(UINT nSourceType, BOOL bEnable = TRUE);
	BOOL IsCommandSourceTelecommandingReleaseWaitModeEnabled(UINT nSourceType) CONST;
	BOOL EnableCommandSourceTelecommandingAutoRejectionMode(UINT nSourceType, BOOL bEnable = TRUE);
	BOOL IsCommandSourceTelecommandingAutoRejectionModeEnabled(UINT nSourceType) CONST;
	BOOL SetCommandSourceSubSystemChecks(UINT nSourceType, CONST CUIntArray &nSubSystemIDs, CONST CStringArray &szEnablingEvents, CONST CStringArray &szDisablingEvents, CONST CUIntArray &nStatus);
	BOOL GetCommandSourceSubSystemChecks(UINT nSourceType, CUIntArray &nSubSystemIDs, CStringArray &szEnablingEvents, CStringArray &szDisablingEvents, CUIntArray &nStatus) CONST;
	BOOL IsCommandSourceSubSystemEnabled(UINT nSourceType, CONST CTCItem *pItem) CONST;
	BOOL SetDefaultReleaseTimeWindow(UINT nSourceType, CONST CTimeSpan &tTimeWindow);
	CTimeSpan GetDefaultReleaseTimeWindow(UINT nSourceType) CONST;
	BOOL SetDispatchTimeWindow(UINT nSourceType, CONST CTimeSpan &tTimeWindow);
	CTimeSpan GetDispatchTimeWindow(UINT nSourceType) CONST;

public:
	BOOL LoadTelecommands(CONST CTCItems &pItems);
	BOOL DispatchTelecommands(CONST CTCItems &pItems, BOOL bUndo = FALSE);
	BOOL AcknowledgeTelecommands(CONST CTCItems &pItems);

public:
	BOOL GenerateTCPackets(CONST CDatabaseTCFunction *pFunction, CONST CDatabaseTCPacket *pPacket, LPCTSTR pszMemoryPatch, BOOL bTimeTagged, BOOL b2ndStep, BOOL bBlocked, BOOL bExample, CDatabaseTCFunctions &pFunctions, CDatabaseTCPackets &pPackets);
	BOOL DecodeTCPacket(CONST CTCPacket *pTCPacket, CDatabaseTCFunction *pDatabaseTCFunction, CDatabaseTCFunctions &pDatabaseBlockedTCFunctions, CDatabaseTCPacket *pDatabaseTCPacket) CONST;
	BOOL CheckTCFunctionExecutionTime(CONST CDatabaseTCFunction *pDatabaseTCFunction, CONST CDatabaseTCPacket *pDatabaseTCPacket, CONST CTimeTag &tExecutionTime = 0) CONST;
	BOOL SetTCFunctionExecutionTimeOffsets(CONST CTimeSpan &tMin, CONST CTimeSpan &tMax);
	BOOL GetTCFunctionExecutionTimeOffsets(CTimeSpan &tMin, CTimeSpan &tMax) CONST;
	BOOL SetTCFunctionParameterTimeOffsets(CONST CTimeSpan &tMin, CONST CTimeSpan &tMax);
	BOOL GetTCFunctionParameterTimeOffsets(CTimeSpan &tMin, CTimeSpan &tMax) CONST;
	BOOL ConvertTCParameterValue(LPCTSTR pszTag, ULONGLONG nAttributes, LPCTSTR pszValue, ULONGLONG &nValue) CONST;
	BOOL ConvertTCParameterValue(CONST CDatabaseTCParameter *pDatabaseTCParameter, ULONGLONG &nValue) CONST;
	BOOL CheckTCParameterOolStatus(CONST CDatabaseTCParameter *pParameter, UINT &nOolStatus) CONST;
	BOOL CheckTCFunctionElementOolStatus(CONST CDatabaseTCFunctionElement *pFunctionElement, UINT &nOolStatus) CONST;
	BOOL CheckTCPacketParameterOolStatus(CONST CDatabaseTCPacketParameter *pPacketParameter, UINT &nOolStatus) CONST;
	BOOL CheckTCProcedureArgumentOolStatus(CONST CDatabaseTCProcedureArgument *pArgument, UINT &nOolStatus) CONST;
	BOOL CheckTCFunctionPreexecutionParameterGroup(INT nGroupID, CStringArray &szParameters) CONST;

	BOOL SetTCInterlocks(CONST CTCInterlocks &pInterlocks);
	BOOL SetTCInterlocks(UINT nSourceType, CONST CTCInterlocks &pInterlocks);
	BOOL GetTCInterlocks(CTCInterlocks &pInterlocks) CONST;
	BOOL GetTCInterlocks(UINT nSourceType, CTCInterlocks &pInterlocks) CONST;
	BOOL CheckTCInterlocks(UINT nSourceType, UINT nState) CONST;
	BOOL CheckTCInterlock(UINT nSourceType, LPCTSTR pszInterlock, UINT &nState) CONST;
	BOOL CheckTCInterlock(UINT nSourceType, LPCTSTR pszInterlock, UINT &nScope, UINT &nStage, UINT &nState) CONST;
	BOOL CheckTCInterlock(CONST CTCItem *pItem) CONST;

	INT EnumTCDiagnosticsOversamplingDumpRates(CStringArray &szRates) CONST;
	BOOL EncodeTCDiagnosticsOversamplingDump(CONST CTimeTag &tExecutionTime, CONST COversamplingParameters &pOversamplingParameters, CDatabaseTCFunction *pDatabaseTCFunction);
	BOOL DecodeTCDiagnosticsOversamplingDump(CONST CDatabaseTCFunction *pDatabaseTCFunction, COversamplingParameters &pOversamplingParameters);
	BOOL DecodeTCDiagnosticsOversamplingDump(CONST CTMEnvironment *pTMEnvironment, COversamplingParameters &pOversamplingParameters, BOOL bAutomatic);
	double CalculateTCDiagnosticsOversamplingBandwidth(COversamplingParameters &pOversamplingParameters) CONST;

	INT EnumTCOnBoardBufferTypes(CStringArray &szTypes) CONST;
	INT EnumTCOnBoardBufferQueues(CTCOnBoardBufferQueues &pQueues) CONST;
	INT EnumTCOnBoardBufferQueues(LPCTSTR pszType, CStringArray &szNames) CONST;
	INT EnumTCOnBoardBufferQueues(LPCTSTR pszType, CStringArray &szNames, CUIntArray &nAPIDs, CUIntArray &nSubScheduleIDs, CUIntArray &nLimits, CStringArray &szUnits, CUIntArray &tTimeouts) CONST;
	INT UpdateTCOnBoardBufferQueues(CONST CTMEnvironment *pTMEnvironment, CStringArray &szTypes, CStringArray &szNames, CUIntArray &nSubScheduleIDs, CUIntArray &nCounts, CTimeTagArray &tUpdateTimes, CUIntArray &nStatus);
	BOOL CheckTCOnBoardBufferQueues(CONST CTCItems &pItems, INT nChecks = -1) CONST;
	BOOL UpdateTCOnBoardBufferQueue(LPCTSTR pszType, LPCTSTR pszName, UINT nSubScheduleID, CONST CTCItems &pItems);
	BOOL UpdateTCOnBoardBufferQueue(LPCTSTR pszType, LPCTSTR pszName, UINT nSubScheduleID, UINT nFlags, UINT nAPID = -1, UINT nPSC = -1, INT nLowEntry = -1, INT nHighEntry = -1, CONST CTimeKey &tStartTime = 0, CONST CTimeKey &tStopTime = 0);
	BOOL AcknowledgeTCOnBoardBufferQueue(LPCTSTR pszType, LPCTSTR pszName, UINT nSubScheduleID, UINT nFlags = TCONBOARDBUFFERQUEUE_ALERTTYPE_ANY);
	BOOL CheckTCOnBoardBufferQueue(LPCTSTR pszType, LPCTSTR pszName, BOOL &bStatus, BOOL &bDumpAllEntries, BOOL &bDumpByAPID, BOOL &bDumpByPSC, BOOL &bDumpByEntryRange, BOOL &bDumpByTimeRange, BOOL &bResetAllEntries, BOOL &bResetByAPID, BOOL &bResetByPSC, BOOL &bResetByEntryRange, BOOL &bResetByTimeRange) CONST;
	BOOL CheckTCOnBoardBufferQueue(CONST CTCItem *pItem) CONST;
	BOOL EncodeTCOnBoardBufferQueueStatus(LPCTSTR pszType, LPCTSTR pszName, CONST CTimeTag &tExecutionTime, BOOL bEnable, CDatabaseTCFunction *pDatabaseTCFunction) CONST;
	BOOL EncodeTCOnBoardBufferQueueDump(LPCTSTR pszType, LPCTSTR pszName, CONST CTimeTag &tExecutionTime, UINT nAPID, UINT nPSC, UINT nLowEntry, UINT nHighEntry, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, CDatabaseTCFunction *pDatabaseTCFunction) CONST;
	BOOL EncodeTCOnBoardBufferQueueReset(LPCTSTR pszType, LPCTSTR pszName, CONST CTimeTag &tExecutionTime, UINT nAPID, UINT nPSC, UINT nLowEntry, UINT nHighEntry, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, CONST CTCPacket *pTCPacket, CDatabaseTCFunction *pDatabaseTCFunction) CONST;
	BOOL FindTCOnBoardBufferQueue(CONST CTCPacket *pTCPacket, CString &szType, CString &szName, UINT &nSubScheduleID) CONST;
	BOOL ExpandTCOnBoardBufferQueueEntry(CONST CTCPacket *pTCPacket, UINT &nBlockOffset, UINT &nBlockBytes, CUIntArray &nBlockSizes, CTimeTagArray &tBlockTimes) CONST;
	UINT CalculateTCOnBoardBufferQueueEntry(CONST CTCPacket *pTCPacket) CONST;

	BOOL CheckTCOnBoardMemoryImageDumpCapabilities(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, BOOL &bStop) CONST;
	BOOL EncodeTCOnBoardMemoryImageDump(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, CONST CTimeKey &tExecutionTime, BOOL bStop, CDatabaseTCFunction *pDatabaseTCFunction);
	BOOL IsTCOnBoardMemoryImageDump(CONST CTMEnvironment *pTMEnvironment) CONST;
	BOOL CheckTCOnBoardMemoryImagePatchCapabilities(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage) CONST;
	BOOL EncodeTCOnBoardMemoryImagePatch(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, CONST CTimeKey &tExecutionTime, CDatabaseTCFunctions &pDatabaseTCFunctions, CDatabaseTCPackets &pDatabaseTCPackets);
	BOOL CalculateTCOnBoardMemoryImageCRC(CONST CDatabaseOBProcessor *pProcessor, CDatabaseOBProcessorMemoryImage *pImage, LPCTSTR pszImageVersion) CONST;
	BOOL IsTCOnBoardMemoryImagePatch(CONST CTCPacket *pTCPacket, CString &szProcessor) CONST;

public:
	BOOL InitializeLoggingOptions();
	BOOL SetLoggingOptions(UINT nArchivalPolicy, LPCTSTR pszArchivalFileName, DWORDLONG dwArchivalRetention, CONST CTimeSpan &tArchivalRetention, LPCTSTR pszRetrievalFileName, UINT nRetrievalReloadCount, BOOL bShowAsEvent);
	BOOL GetLoggingOptions(UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST;

	BOOL ConvertTimeToOBRT(CONST CTimeTag &tOBRT, UINT &nOBRT) CONST;
	BOOL ConvertOBRTToTime(UINT nOBRT, CTimeTag &tOBRT) CONST;

	BOOL CorrelateTCTransferFrameSequenceNumber();
	BOOL CanCorrelateTCTransferFrameSequenceNumber() CONST;

	BOOL EnableTestMode(BOOL bEnable = TRUE);
	BOOL IsTestModeEnabled() CONST;

	BOOL IsHealthy() CONST;

public:
	BOOL SetServiceInfo(CONST CByteArray &nInfo);
	BOOL GetServiceInfo(CByteArray &nInfo) CONST;
	BOOL UpdateServiceInfo(BOOL bSave = TRUE);

	BOOL Lock();
	BOOL Unlock();

private:
	BOOL SaveServiceInfo();
	BOOL LoadServiceInfo();

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////


#endif // __TC_H__
