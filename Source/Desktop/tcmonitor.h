// TCMONITOR.H : Telecommand Procedures Monitor Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the telecommand procedures monitor
// related interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2007/04/03 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __TCMONITOR_H__
#define __TCMONITOR_H__

#include "displays.h"


/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItem

// Specify the telecommand procedures monitor item trigger types
#define TCPROCEDURESMONITORITEM_TRIGGERTYPE_NONE   0
#define TCPROCEDURESMONITORITEM_TRIGGERTYPE_MANUAL   1
#define TCPROCEDURESMONITORITEM_TRIGGERTYPE_AUTOMATIC   2
#define TCPROCEDURESMONITORITEM_TRIGGERTYPE_IMMEDIATELY   3
#define TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATSTARTUP   4
#define TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATTIME   5
#define TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATDAILYTIME   6
#define TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATINTERVAL   7
#define TCPROCEDURESMONITORITEM_TRIGGERTYPE_ATEVENT   8
// Specify the telecommand procedures monitor item flags
#define TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDEPTV   TCSERVICE_COMMANDSOURCEFLAGS_PTV_OVERRIDE
#define TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDEPEV   TCSERVICE_COMMANDSOURCEFLAGS_PEV_OVERRIDE
#define TCPROCEDURESMONITORITEM_CHECKFLAG_OVERRIDECEV   TCSERVICE_COMMANDSOURCEFLAGS_CEV_OVERRIDE
#define TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLEPTV   TCSERVICE_COMMANDSOURCEFLAGS_PTV_DISABLE
#define TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLEPEV   TCSERVICE_COMMANDSOURCEFLAGS_PEV_DISABLE
#define TCPROCEDURESMONITORITEM_CHECKFLAG_DISABLECEV   TCSERVICE_COMMANDSOURCEFLAGS_CEV_DISABLE
// Specify the telecommand procedures monitor item execution modes
#define TCPROCEDURESMONITORITEM_EXECUTIONMODE_NONE   0
#define TCPROCEDURESMONITORITEM_EXECUTIONMODE_AUTOMATIC   TCPROCEDURE_EXECUTIONMODE_AUTOMATIC
#define TCPROCEDURESMONITORITEM_EXECUTIONMODE_SINGLESTEP   TCPROCEDURE_EXECUTIONMODE_SINGLESTEP
#define TCPROCEDURESMONITORITEM_EXECUTIONMODE_EXTERNALACTIONS   TCPROCEDURE_EXECUTIONMODE_EXTERNALACTIONS
#define TCPROCEDURESMONITORITEM_EXECUTIONMODE_COMMANDS   TCPROCEDURE_EXECUTIONMODE_COMMANDS
// Specify the telecommand procedures monitor item running states
#define TCPROCEDURESMONITORITEM_RUNNINGSTATE_NONE   0
#define TCPROCEDURESMONITORITEM_RUNNINGSTATE_NOTRUNNING   TCPROCEDURE_RUNNINGSTATE_NOTRUNNING
#define TCPROCEDURESMONITORITEM_RUNNINGSTATE_RUNNING   TCPROCEDURE_RUNNINGSTATE_RUNNING
#define TCPROCEDURESMONITORITEM_RUNNINGSTATE_STOPPED   TCPROCEDURE_RUNNINGSTATE_STOPPED
// Specify the telecommand procedures monitor item alert types
#define TCPROCEDURESMONITORITEM_ALERTTYPE_INFORMATIONAL   0
#define TCPROCEDURESMONITORITEM_ALERTTYPE_WARNING   1
#define TCPROCEDURESMONITORITEM_ALERTTYPE_ERROR   2
#define TCPROCEDURESMONITORITEM_ALERTTYPE_ALERT   3
#define TCPROCEDURESMONITORITEM_ALERTTYPE_AUTHORIZATION   4
#define TCPROCEDURESMONITORITEM_ALERTTYPES   5

class CTCProceduresMonitorItem : public CDatabaseTCProcedure
{
	// Construction
public:
	CTCProceduresMonitorItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbArguments;
		INT  cbTriggerEvent;
		INT  cbReleaseItems;
		INT  cbAudition[TCPROCEDURESMONITORITEM_ALERTTYPES];
		INT  cbNotifications[TCPROCEDURESMONITORITEM_ALERTTYPES];
		UINT  nFlags;
		UINT  nTriggerType;
		UINT  nTriggerCount;
		UINT  nExecutionMode;
		UINT  nExecutionCount;
		BOOL  bManualExecution;
		BOOL  bExecutionBreaks;
		BOOL  bAuditionBlinkFlag[TCPROCEDURESMONITORITEM_ALERTTYPES];
		BOOL  bAcknowledgmentFlag[TCPROCEDURESMONITORITEM_ALERTTYPES];
		BOOL  bEnabled;
		TIMEKEY  tTriggerTime[3];
		TIMEKEY  tDailyTriggerTime;
		TIMEKEY  tTriggerInterval;
		TIMEKEY  tExecutionTime[2];
		COLORREF  nAuditionColor[TCPROCEDURESMONITORITEM_ALERTTYPES];
		COLORREF  nAcknowledgmentColor[TCPROCEDURESMONITORITEM_ALERTTYPES];
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szTriggerEvent;
	CTimeKey  m_tTriggerTime[3];
	CTimeKey  m_tExecutionTime[2];
	CTimeSpan  m_tDailyTriggerTime;
	CTimeSpan  m_tTriggerInterval;
	CStringArray  m_szReleaseItems;
	CDatabaseTCProcedureArguments  m_pArguments;
	INT  m_nID;
	UINT  m_nFlags;
	UINT  m_nTriggerType;
	UINT  m_nTriggerCount;
	UINT  m_nExecutionMode;
	UINT  m_nExecutionCount;
	UINT  m_nRunningState;
	BOOL  m_bTriggerEvent;
	BOOL  m_bManualExecution;
	BOOL  m_bExecutionBreaks;
	BOOL  m_bAlerted;
	BOOL  m_bEnabled;
private:
	CString  m_szAudition[TCPROCEDURESMONITORITEM_ALERTTYPES];
	CStringArray  m_szNotifications[TCPROCEDURESMONITORITEM_ALERTTYPES];
	COLORREF  m_nAcknowledgmentColor[TCPROCEDURESMONITORITEM_ALERTTYPES];
	COLORREF  m_nAuditionColor[TCPROCEDURESMONITORITEM_ALERTTYPES];
	BOOL  m_bAcknowledgmentFlag[TCPROCEDURESMONITORITEM_ALERTTYPES];
	BOOL  m_bAuditionBlinkFlag[TCPROCEDURESMONITORITEM_ALERTTYPES];
private:
	CTCItems  m_pAuthorizableTCItems;
private:
	CUIntArray  m_nAlertMessageTypes;
	CStringArray  m_szAlertMessages;
	CTimeTagArray  m_tAlertMessages;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetID(INT nID);
	INT GetID() CONST;
	VOID SetFlags(UINT nFlags);
	UINT GetFlags() CONST;
	VOID SetArguments(CONST CDatabaseTCProcedureArguments &pArguments);
	INT GetArguments(CDatabaseTCProcedureArguments &pArguments) CONST;
	VOID SetTriggerType(UINT nType);
	UINT GetTriggerType() CONST;
	VOID SetTriggerTime(CONST CTimeKey &tTime);
	CTimeKey GetTriggerTime() CONST;
	VOID SetDailyTriggerTime(CONST CTimeSpan &tTime);
	CTimeSpan GetDailyTriggerTime() CONST;
	VOID SetTriggerInterval(CONST CTimeKey &tStartTime, CONST CTimeSpan &tInterval);
	VOID SetTriggerInterval(CONST CTimeKey &tStartTime, CONST CTimeSpan &tInterval, UINT nCount);
	VOID SetTriggerInterval(CONST CTimeKey &tStartTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime);
	BOOL GetTriggerInterval(CTimeKey &tStartTime, CTimeSpan &tInterval) CONST;
	BOOL GetTriggerInterval(CTimeKey &tStartTime, CTimeSpan &tInterval, UINT &nCount) CONST;
	BOOL GetTriggerInterval(CTimeKey &tStartTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST;
	VOID SetTriggerEvent(LPCTSTR pszEvent);
	CString GetTriggerEvent() CONST;
	VOID EnableTriggerEvent(BOOL bEnable = TRUE);
	BOOL IsTriggerEventEnabled() CONST;
	VOID SetExecutionMode(UINT nMode);
	UINT GetExecutionMode() CONST;
	VOID SetExecutionStartTime(CONST CTimeKey &tTime);
	CTimeKey GetExecutionStartTime() CONST;
	VOID SetExecutionEndTime(CONST CTimeKey &tTime);
	CTimeKey GetExecutionEndTime() CONST;
	VOID SetExecutionCount(UINT nCount);
	UINT GetExecutionCount() CONST;
	VOID AllowManualExecution(BOOL bAllow = TRUE);
	BOOL IsManualExecutionAllowed() CONST;
	VOID AllowExecutionBreaks(BOOL bAllow = TRUE);
	BOOL AreExecutionBreaksAllowed() CONST;
	BOOL SetReleaseConstraints(CONST CStringArray &szItems);
	BOOL SetReleaseConstraints(LPCTSTR pszThread, LPCTSTR pszStep, LPCTSTR pszFunction, INT nEntry, LPCTSTR pszInterlock, CONST CTimeSpan &tTimeWindow);
	INT GetReleaseConstraints(CStringArray &szItems) CONST;
	BOOL GetReleaseConstraints(LPCTSTR pszThread, LPCTSTR pszStep, LPCTSTR pszFunction, INT nEntry, CString &szInterlock, CTimeSpan &tTimeWindow) CONST;
	VOID SetAudition(UINT nType, LPCTSTR pszAudition);
	CString GetAudition(UINT nType) CONST;
	VOID EnableAuditionBlinking(UINT nType, BOOL bEnable = TRUE);
	BOOL IsAuditionBlinkingEnabled(UINT nType) CONST;
	VOID SetAuditionColor(UINT nType, COLORREF nColor);
	COLORREF GetAuditionColor(UINT nType) CONST;
	VOID SetNotifications(UINT nType, CONST CStringArray &szNotifications);
	INT GetNotifications(UINT nType, CStringArray &szNotifications) CONST;
	VOID EnableAcknowledgment(UINT nType, BOOL bEnable = TRUE);
	BOOL IsAcknowledgmentEnabled(UINT nType) CONST;
	VOID SetAcknowledgmentColor(UINT nType, COLORREF nColor);
	COLORREF GetAcknowledgmentColor(UINT nType) CONST;

	BOOL AddAuthorizableTelecommand(CONST CTCItem *pTCItem);
	BOOL EnumAuthorizableTelecommands(CTCItems &pTCItems) CONST;
	BOOL HasAuthorizableTelecommands() CONST;
	BOOL AuthorizeTelecommands(CONST CTCItems &pTCItems);

	INT AddAlertMessage(LPCTSTR pszAlert);
	INT AddAlertMessage(UINT nType, LPCTSTR pszAlert);
	INT AddAlertMessage(UINT nType, LPCTSTR pszAlert, CONST CTimeTag &tAlert);
	CString GetAlertMessage() CONST;
	BOOL GetAlertMessage(UINT &nType, CString &szAlert) CONST;
	BOOL GetAlertMessage(UINT &nType, CString &szAlert, CTimeTag &tAlert) CONST;
	BOOL RemoveAlertMessage();
	VOID RemoveAllAlertMessages();
	VOID Alert(BOOL bEnable = TRUE);
	BOOL IsAlerted() CONST;
	VOID Enable(BOOL bEnable = TRUE);
	BOOL IsEnabled() CONST;

	VOID SetRunningState(UINT nState);
	UINT GetRunningState() CONST;

	BOOL Copy(CONST CTCProceduresMonitorItem *pItem, BOOL bAll = TRUE);
	BOOL Compare(CONST CTCProceduresMonitorItem *pItem, BOOL bAll = TRUE) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItems

class CTCProceduresMonitorItems : public CPtrArray
{
	// Construction
public:
	CTCProceduresMonitorItems();
	~CTCProceduresMonitorItems();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCProceduresMonitorItem *pItem);

	CTCProceduresMonitorItem *GetAt(INT nIndex) CONST;
	CTCProceduresMonitorItem *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCProceduresMonitorItems *pItems);
	BOOL Compare(CONST CTCProceduresMonitorItems *pItems) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemThread thread

// Specify the telecommand procedures monitor item thread related identifiers
#define TCPROCEDURESMONITORITEMTHREAD_EVENT_UPDATE   0
#define TCPROCEDURESMONITORITEMTHREAD_EVENT_EXIT   1
#define TCPROCEDURESMONITORITEMTHREAD_EVENTS   2

class CTCProceduresMonitorItemThread : public CThread, public CDisplayLockable
{
	DECLARE_DYNAMIC(CTCProceduresMonitorItemThread)

	// Construction
public:
	CTCProceduresMonitorItemThread(CONST CTCProceduresMonitorItem *pItem);
	~CTCProceduresMonitorItemThread();

	// Attributes
private:
	BOOL  m_bStartup;
	CEvent  m_bAbort;
	CEvent  m_bUpdate;
	CTCEnvironment  *m_pTCEnvironment;
	CTCProcessEngine  *m_pTCProcessEngine;
	CTCProceduresMonitorItem  m_cItem[3];
private:
	INT  m_nTCProcedureID;
	INT  m_nTCProcedureStepID;
	BOOL  m_bTCProcedureStepInto;
	BOOL  m_bTCProcedureStepOver;
	BOOL  m_bTCProcedureStepOut;
	BOOL  m_bTCProcedureStepBreak;
	BOOL  m_bTCProcedureLineBreak;
	BOOL  m_bTCProcedureBreak;
	BOOL  m_bTCProcedureDirty;
	BOOL  m_bTCProcedureExit;
	CString  m_szTCProcedureStep;
	HINSTANCE  m_hTCProcedureCode;
	CPtrArray  m_hTCProcedureEvents;
	CUIntArray  m_nTCProcedureLines;
private:
	class CTCProceduresMonitorWnd  *m_pTCProceduresMonitorWnd;

	// Operations
public:
	BOOL Start(class CTCProceduresMonitorWnd *pTCProceduresMonitorWnd, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, BOOL bStartup = TRUE);
	BOOL Stop(BOOL bWait = TRUE);

	BOOL Update(CONST CTCProceduresMonitorItem *pItem);
	BOOL Update(CONST CTMEnvironment *pTMEnvironment);

	BOOL Refresh();

	BOOL Suspend();
	BOOL Resume(BOOL bAuto = TRUE);
	BOOL Abort();

	BOOL Reset();
	BOOL CanReset() CONST;

public:
	BOOL CheckExecution(INT nProcedureID = -1) CONST;
	BOOL CheckExecution(INT nProcedureID, CString &szSubRoutine) CONST;

	BOOL StepIntoExecutionBlock(INT nThreadID);
	BOOL CanStepIntoExecutionBlock(INT nThreadID) CONST;
	BOOL StepOverExecutionBlock(INT nThreadID);
	BOOL CanStepOverExecutionBlock(INT nThreadID) CONST;
	BOOL StepOutExecutionBlock(INT nThreadID);
	BOOL CanStepOutExecutionBlock(INT nThreadID) CONST;

	BOOL IsRunning() CONST;
	BOOL IsSuspended() CONST;

private:
	BOOL SuspendProcedure(CONST CTCProceduresMonitorItem *pItem);
	BOOL UpdateProcedure(CONST CTCProceduresMonitorItem *pItem);
	BOOL ResumeProcedure(CONST CTCProceduresMonitorItem *pItem, BOOL bAuto = TRUE);
	BOOL TerminateProcedure(CONST CTCProceduresMonitorItem *pItem);
	BOOL AbortProcedure(CONST CTCProceduresMonitorItem *pItem);

	BOOL HasProcedureDialogs(CONST CTCProceduresMonitorItem *pItem) CONST;

	BOOL IsProcedureRunning() CONST;
	BOOL IsProcedureSuspended() CONST;
	BOOL IsProcedureStopping() CONST;

private:
	BOOL UpdateThreadBreakpoints(LPCTSTR pszThread, CONST CDatabaseTCProcedureThreadBreakpoints &pBreakpoints);

	BOOL CheckThreadState(LPCTSTR pszThread, UINT &nState, CStringArray &szSteps, CUIntArray &nStepStates, UINT &nLine) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorItemThread)
public:
	virtual int Run();
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProceduresMonitorItemThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorPrintJobInfo

class CTCProceduresMonitorPrintJobInfo : public CObject
{
	// Construction
public:
	CTCProceduresMonitorPrintJobInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbProfile;
		INT  cbComments;
		UINT  nPrintMode;
		UINT  nPrintScale;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szProfile;
	CString  m_szComments;
	UINT  m_nPrintMode;
	UINT  m_nPrintScale;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetProfile(LPCTSTR pszProfile);
	CString GetProfile() CONST;
	VOID SetComments(LPCTSTR pszComments);
	CString GetComments() CONST;

	BOOL SetPrintMode(UINT nMode);
	UINT GetPrintMode() CONST;
	BOOL SetPrintScale(UINT nScale);
	BOOL GetPrintScale(UINT &nScale) CONST;

	VOID Copy(CONST CTCProceduresMonitorPrintJobInfo *pJobInfo);
	BOOL Compare(CONST CTCProceduresMonitorPrintJobInfo *pJobInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorPrintJobs

class CTCProceduresMonitorPrintJobs : public CPtrArray
{
	// Construction
public:
	CTCProceduresMonitorPrintJobs();
	~CTCProceduresMonitorPrintJobs();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCProceduresMonitorPrintJobInfo *pJobInfo);

	INT Find(LPCTSTR pszName) CONST;

	CTCProceduresMonitorPrintJobInfo *GetAt(INT nIndex) CONST;
	CTCProceduresMonitorPrintJobInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCProceduresMonitorPrintJobs *pPrintJobs);
	BOOL Compare(CONST CTCProceduresMonitorPrintJobs *pPrintJobs) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorSettingsLayoutPage dialog

#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_DETAILS   1001
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT   1002
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_NAME_STATIC   1003
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_NAME   1004
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_VIEW   1005
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE   1006
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER   1007
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_REMOVE   1008
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_FLOWCHART_STATIC  1009
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_FLOWCHART_BACKGROUNDCOLOR   1010
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FORMAT_FLOWCHART_TOOLTIPS   1011
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS   1012
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC   1013
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE   1014
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS   1015
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_LOCATION_SOURCECODE   1016
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_STATIC   1017
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELS   1018
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_FLOWCHART_LABELSCOLOR   1019
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_CHARACTERISTICS   1020
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC   1021
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_NAMES   1022
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC   1023
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_STYLE   1024
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC   1025
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SIZE   1026
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SAMPLE   1027
#define IDC_TCPROCEDURESMONITORSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT   1028

class CTCProceduresMonitorSettingsLayoutPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCProceduresMonitorSettingsLayoutPage)

	// Construction
public:
	CTCProceduresMonitorSettingsLayoutPage();

	// Attributes
private:
	CUIntArray  m_nColumns[2];
	LOGFONT  m_fntListTitle[2];
	LOGFONT  m_fntListItems[2];
	LOGFONT  m_fntSourceCode[2];
	LOGFONT  m_fntFlowchartLabels[2];
	COLORREF  m_nFlowchartLabelsColor[2];
	COLORREF  m_nFlowchartBackgroundColor[2];
	BOOL  m_bToolTips[2];
private:
	CString  m_szFontSampleText;
	CStringArray  m_szColumns;
	INT  m_nColumnIndex;

	// Dialog Data
	//{{AFX_DATA(CTCProceduresMonitorSettingsLayoutPage)
	enum { IDD = IDD_TCPROCEDURESMONITOR_SETTINGS_LAYOUTPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetColumns(CUIntArray &nColumns) CONST;
	BOOL GetTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetItemsFont(LPLOGFONT pItemsFont) CONST;
	BOOL GetSourceCodeFont(LPLOGFONT pCodeFont) CONST;
	BOOL GetFlowchartLabelsFont(LPLOGFONT pLabelsFont) CONST;
	BOOL GetFlowchartLabelsColor(COLORREF &nColor) CONST;
	BOOL GetFlowchartBackgroundColor(COLORREF &nColor) CONST;
	BOOL GetToolTipMode(BOOL &bEnable) CONST;

	class CTCProceduresMonitorSettingsDialog *GetParentDialog() CONST;
	class CTCProceduresMonitorWnd *GetParentDisplay() CONST;

private:
	BOOL EnumLayoutColumns();

	BOOL ShowLayoutColumns();
	VOID ShowLayoutFontDetails();
	VOID ShowLayoutFontSample();

	BOOL InsertLayoutColumn(INT nIndex, LPCTSTR pszText);
	BOOL ModifyLayoutColumn(INT nIndex, LPCTSTR pszText);
	BOOL RemoveLayoutColumn(INT nIndex);
	BOOL SetCurLayoutColumn(INT nIndex = 0);
	INT GetCurLayoutColumn() CONST;
	BOOL CheckLayoutColumn() CONST;

	CString LookupColumnName(UINT nColumn) CONST;
	UINT LookupColumnName(LPCTSTR pszColumn) CONST;
	INT CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths);
	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnIndent() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorSettingsLayoutPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCProceduresMonitorSettingsLayoutPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnInsertColumnBefore();
	afx_msg void OnInsertColumnAfter();
	afx_msg void OnRemoveColumn();
	afx_msg void OnToolTips();
	afx_msg void OnTitleFont();
	afx_msg void OnItemsFont();
	afx_msg void OnSourceCodeFont();
	afx_msg void OnFlowchartLabelsFont();
	afx_msg void OnEditchangeFontName();
	afx_msg void OnSelchangeColumnName();
	afx_msg void OnSelchangeFontName();
	afx_msg void OnSelchangeFontStyle();
	afx_msg void OnSelchangeFontSize();
	afx_msg void OnSelchangeFontColor();
	afx_msg void OnSelchangeBackgroundColor();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorSettingsContentsPage dialog

#define IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_DETAILS   1001
#define IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_LIST_STATIC   1002
#define IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_LIST   1003
#define IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ADD   1004
#define IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_REMOVE   1005
#define IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_REMOVEALL   1006
#define IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_ACTIVELIST   1007
#define IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS   1008
#define IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_COMMANDSOURCE   1009
#define IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_OVERRIDEPEV   1010
#define IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLEPEV   1011
#define IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_OVERRIDECEV   1012
#define IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLECEV   1013
#define IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_RELEASEWAITMODE   1014
#define IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_DISABLED   1015
#define IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_ARGUMENTS   1016
#define IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_EXECUTION   1017
#define IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_COMMANDS   1018
#define IDC_TCPROCEDURESMONITORSETTINGS_CONTENTSPAGE_OPERATIONS_ALERTS   1019

class CTCProceduresMonitorSettingsContentsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCProceduresMonitorSettingsContentsPage)

	// Construction
public:
	CTCProceduresMonitorSettingsContentsPage();

	// Attributes
private:
	BOOL  m_bModes[2];
	BOOL  m_bStateFlags[2];
	UINT  m_nCheckFlags[2];
	CTCProceduresMonitorItems  m_pItems[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProceduresMonitorSettingsContentsPage)
	enum { IDD = IDD_TCPROCEDURESMONITOR_SETTINGS_CONTENTSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	INT GetContents(CTCProceduresMonitorItems &pItems) CONST;
	BOOL GetCheckOptions(UINT &nFlags) CONST;
	BOOL GetReleaseWaitModeFlag(BOOL &bEnabled) CONST;
	BOOL GetDisabledStateFlag(BOOL &bFlag) CONST;

	class CTCProceduresMonitorSettingsDialog *GetParentDialog() CONST;
	class CTCProceduresMonitorWnd *GetParentDisplay() CONST;

private:
	BOOL EnumProcedures();

	VOID ShowProperties();

	CTCProceduresMonitorItem *FindProcedure() CONST;

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorSettingsContentsPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCProceduresMonitorSettingsContentsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddProcedure();
	afx_msg void OnRemoveProcedure();
	afx_msg void OnRemoveAllProcedures();
	afx_msg void OnOperationsCommandSource();
	afx_msg void OnOperationsOverridePEV();
	afx_msg void OnOperationsDisablePEV();
	afx_msg void OnOperationsOverrideCEV();
	afx_msg void OnOperationsDisableCEV();
	afx_msg void OnOperationsReleaseWaitMode();
	afx_msg void OnOperationsDisabled();
	afx_msg void OnProcedureArguments();
	afx_msg void OnProcedureExecution();
	afx_msg void OnProcedureCommands();
	afx_msg void OnProcedureAlerts();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorSettingsLoggingPage dialog

#define IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_DETAILS   1001
#define IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_LIST   1002
#define IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_OPTIONS   1003
#define IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_MODE_STATIC   1004
#define IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_REALTIME   1005
#define IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD   1006
#define IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD_COUNT   1007
#define IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_RELOAD_COUNT_STATIC   1008
#define IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL   1009
#define IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STARTTIME_STATIC   1010
#define IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STARTTIME   1011
#define IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATTIME   1012
#define IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPTIME   1013
#define IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATLIMIT   1014
#define IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT   1015
#define IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT_STATIC   1016
#define IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_NOLIMIT   1017
#define IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_HISTORICAL_RETRIEVE   1018
#define IDC_TCPROCEDURESMONITORSETTINGS_LOGGINGPAGE_SHOWASEVENT   1019

// Specify the telecommand procedures monitor settings logging page related limits
#define TCPROCEDURESMONITORSETTINGSLOGGINGPAGE_MINIMUMRELOADCOUNT   1
#define TCPROCEDURESMONITORSETTINGSLOGGINGPAGE_MAXIMUMRELOADCOUNT   1000
#define TCPROCEDURESMONITORSETTINGSLOGGINGPAGE_DEFAULTRELOADCOUNT   25
#define TCPROCEDURESMONITORSETTINGSLOGGINGPAGE_MINIMUMRETRIEVALSTOPCOUNT   1
#define TCPROCEDURESMONITORSETTINGSLOGGINGPAGE_MAXIMUMRETRIEVALSTOPCOUNT   10000
#define TCPROCEDURESMONITORSETTINGSLOGGINGPAGE_DEFAULTRETRIEVALSTOPCOUNT   100
// Specify the telecommand procedures monitor settings logging page related timer identifiers
#define TCPROCEDURESMONITORSETTINGSLOGGINGPAGE_TIMERID   100
#define TCPROCEDURESMONITORSETTINGSLOGGINGPAGE_TIMEOUT   500

class CTCProceduresMonitorSettingsLoggingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCProceduresMonitorSettingsLoggingPage)

	// Construction
public:
	CTCProceduresMonitorSettingsLoggingPage();

	// Attributes
private:
	UINT  m_nArchivalPolicy[2];
	UINT  m_nRetrievalReloadCount[2];
	CString  m_szArchivalFileName[2];
	CString  m_szRetrievalFileName[2];
	DWORDLONG  m_dwArchivalRetention[2];
	CTimeSpan  m_tArchivalRetention[2];
	BOOL  m_bShowAsEvent[2];
private:
	CLogFile  m_cRetrievalFile;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProceduresMonitorSettingsLoggingPage)
	enum { IDD = IDD_TCPROCEDURESMONITOR_SETTINGS_LOGGINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetOptions(UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST;

	class CTCProceduresMonitorSettingsDialog *GetParentDialog() CONST;
	class CTCProceduresMonitorWnd *GetParentDisplay() CONST;

private:
	VOID ShowLoggingDetails();
	VOID ShowLogEntries(CONST CTCLogEntries &pEntries);
	VOID ShowLogEntry(CONST CTCLogEntry *pEntry, INT nIndex = -1);

	BOOL RetrieveLogEntries();
	BOOL RetrieveLogEntries(CTCLogEntries &pEntries);

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorSettingsLoggingPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCProceduresMonitorSettingsLoggingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnRealtime();
	afx_msg void OnHistorical();
	afx_msg void OnReloadCount();
	afx_msg void OnStopAtTime();
	afx_msg void OnStopAtLimit();
	afx_msg void OnStopAtEnd();
	afx_msg void OnOptions();
	afx_msg void OnRetrieve();
	afx_msg void OnShowAsEvent();
	afx_msg void OnSpinchangeReloadCount();
	afx_msg void OnSpinchangeStartTime();
	afx_msg void OnSpinchangeStopTime();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorSettingsPrintingComments window

class CTCProceduresMonitorSettingsPrintingComments : public CEdit
{
	DECLARE_DYNCREATE(CTCProceduresMonitorSettingsPrintingComments)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorSettingsPrintingComments)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProceduresMonitorSettingsPrintingComments)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorSettingsPrintingPage dialog

#define IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_DETAILS   1001
#define IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PROFILE_STATIC   1002
#define IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PROFILE   1003
#define IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_OPTIONS   1004
#define IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLIST   1005
#define IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTFLOWCHART   1006
#define IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTONEONLY   1007
#define IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT   1008
#define IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_AUTOSCALE   1009
#define IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE   1010
#define IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE_STATIC   1011
#define IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_PRINTLAYOUT_FIXEDSCALE_NUMBER   1012
#define IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_COMMENTS   1013
#define IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_COMMENTSTEXT_STATIC   1014
#define IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_COMMENTSTEXT   1015
#define IDC_TCPROCEDURESMONITORSETTINGS_PRINTINGPAGE_CLEARCOMMENTS   1016

// Specify the telecommand procedures monitor settings printing page related limits
#define TCPROCEDURESMONITORSETTINGSPRINTINGPAGE_MINIMUMSCALE   1
#define TCPROCEDURESMONITORSETTINGSPRINTINGPAGE_MAXIMUMSCALE   1000
#define TCPROCEDURESMONITORSETTINGSPRINTINGPAGE_DEFAULTSCALE   100

class CTCProceduresMonitorSettingsPrintingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCProceduresMonitorSettingsPrintingPage)

	// Construction
public:
	CTCProceduresMonitorSettingsPrintingPage();

	// Attributes
private:
	CTCProceduresMonitorPrintJobs  m_pJobs[2];
private:
	CTCProceduresMonitorSettingsPrintingComments  m_wndComments;

	// Dialog Data
	//{{AFX_DATA(CTCProceduresMonitorSettingsPrintingPage)
	enum { IDD = IDD_TCPROCEDURESMONITOR_SETTINGS_PRINTINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(CTCProceduresMonitorPrintJobs &pJobs) CONST;

	class CTCProceduresMonitorSettingsDialog *GetParentDialog() CONST;
	class CTCProceduresMonitorWnd *GetParentDisplay() CONST;

private:
	VOID ShowJobInfo();
	CTCProceduresMonitorPrintJobInfo *FindJobInfo() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorSettingsPrintingPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCProceduresMonitorSettingsPrintingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeProfile();
	afx_msg void OnPrintList();
	afx_msg void OnPrintFlowchart();
	afx_msg void OnPrintOneOnly();
	afx_msg void OnPrintAutomaticScale();
	afx_msg void OnPrintFixedScale();
	afx_msg void OnSpinchangePrintFixedScale();
	afx_msg void OnEditchangeComments();
	afx_msg void OnResetComments();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorSettingsTabCtrl window

class CTCProceduresMonitorSettingsTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCProceduresMonitorSettingsTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorSettingsTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProceduresMonitorSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorSettingsDialog

class CTCProceduresMonitorSettingsDialog : public CDisplayPropertySheetDialog
{
	DECLARE_DYNCREATE(CTCProceduresMonitorSettingsDialog)

	// Construction
public:
	CTCProceduresMonitorSettingsDialog();

	// Attributes
private:
	CTCProceduresMonitorSettingsTabCtrl  m_wndTabCtrl;
	CTCProceduresMonitorSettingsLayoutPage  m_pageLayout;
	CTCProceduresMonitorSettingsContentsPage  m_pageContents;
	CTCProceduresMonitorSettingsLoggingPage  m_pageLogging;
	CTCProceduresMonitorSettingsPrintingPage  m_pagePrinting;

	// Operations
public:
	BOOL GetColumns(CUIntArray &nColumns) CONST;
	BOOL GetTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetItemsFont(LPLOGFONT pItemsFont) CONST;
	BOOL GetSourceCodeFont(LPLOGFONT pCodeFont) CONST;
	BOOL GetFlowchartLabelsFont(LPLOGFONT pLabelsFont) CONST;
	BOOL GetFlowchartLabelsColor(COLORREF &nColor) CONST;
	BOOL GetFlowchartBackgroundColor(COLORREF &nColor) CONST;
	BOOL GetToolTipMode(BOOL &bEnable) CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetContents(CTCProceduresMonitorItems &pItems) CONST;
	BOOL GetCheckOptions(UINT &nFlags) CONST;
	BOOL GetReleaseWaitModeFlag(BOOL &bEnabled) CONST;
	BOOL GetDisabledStateFlag(BOOL &bFlag) CONST;
	BOOL IsContentsModified() CONST;

	BOOL GetLoggingOptions(UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST;
	BOOL IsLoggingModified() CONST;

	BOOL GetPrintJobs(CTCProceduresMonitorPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CTCProceduresMonitorWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorSettingsDialog)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProceduresMonitorSettingsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorArgumentParametersCalibrationPage dialog

#define IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_NAME_STATIC   1001
#define IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_NAME   1002
#define IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_ID_STATIC   1003
#define IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_ID   1004
#define IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC   1005
#define IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_TYPE   1006
#define IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS_STATIC  1007
#define IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CALIBRATIONPAGE_POINTS   1008

class CTCProceduresMonitorArgumentParametersCalibrationPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCProceduresMonitorArgumentParametersCalibrationPage)

	// Construction
public:
	CTCProceduresMonitorArgumentParametersCalibrationPage();

	// Attributes
private:
	UINT  m_nCalTableType;
	CUIntArray  m_nCalTableIDs;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProceduresMonitorArgumentParametersCalibrationPage)
	enum { IDD = IDD_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_CONTENTSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo(CONST CDatabaseTCParameter *pParameter);
	VOID ShowCalibrationInfo();

	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CTCProceduresMonitorArgumentParametersFolder *GetParent() CONST;

private:
	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorArgumentParametersCalibrationPage)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCProceduresMonitorArgumentParametersCalibrationPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorArgumentParametersFolderTabCtrl window

class CTCProceduresMonitorArgumentParametersFolderTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCProceduresMonitorArgumentParametersFolderTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CTCProceduresMonitorArgumentParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMinitorArgumentParametersFolderTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProceduresMonitorArgumentParametersFolderTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorArgumentParametersFolder

class CTCProceduresMonitorArgumentParametersFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CTCProceduresMonitorArgumentParametersFolder)

	// Construction
public:
	CTCProceduresMonitorArgumentParametersFolder();

	// Attributes
private:
	CTCProceduresMonitorArgumentParametersFolderTabCtrl  m_wndTabCtrl;
	CTCProceduresMonitorArgumentParametersCalibrationPage  m_pageCalibration;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID ShowParameterInfo(CONST CDatabaseTCParameter *pParameter = NULL);

	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CTCProceduresMonitorArgumentParametersDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorArgumentParametersFolder)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProceduresMonitorArgumentParametersFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorArgumentParametersDialog dialog

#define IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_DETAILS   1001
#define IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_ITEM_STATIC   1002
#define IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_ITEM   1003
#define IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_FOLDER   1004
#define IDC_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_HELP   1005

class CTCProceduresMonitorArgumentParametersDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProceduresMonitorArgumentParametersDialog)

	// Construction
public:
	CTCProceduresMonitorArgumentParametersDialog();   // standard constructor

	// Attributes
private:
	CString  m_szX;
	CString  m_szY;
	CString  m_szParameter;
private:
	CTCProceduresMonitorArgumentParametersFolder  m_wndFolderCtrl;

	// Dialog Data
	//{{AFX_DATA(CTCProceduresMonitorArgumentParametersDialog)
	enum { IDD = IDD_TCPROCEDURESMONITOR_ARGUMENTPARAMETERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, LPCTSTR pszParameter, CString &szValue);

	VOID SetSelectedCalibrationPoint(LPCTSTR pszX, LPCTSTR pszY);
	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CTCProceduresMonitorArgumentValuesDialog *GetParent() CONST;

private:
	BOOL EnumParameters();

	VOID ShowParameterInfo();

	CRect CalcFolderSize() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorArgumentParametersDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProceduresMonitorArgumentParametersDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeParameter();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorArgumentValuesDialog dialog

#define IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_DETAILS   1001
#define IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST_STATIC   1002
#define IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_LIST   1003
#define IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_REMARK   1004
#define IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE_STATIC   1005
#define IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE   1006
#define IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_VALUE_SET   1007
#define IDC_TCPROCEDURESMONITOR_ARGUMENTVALUES_HELP   1008

class CTCProceduresMonitorArgumentValuesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProceduresMonitorArgumentValuesDialog)

	// Construction
public:
	CTCProceduresMonitorArgumentValuesDialog();   // standard constructor

	// Attributes
private:
	CTCProceduresMonitorItem  m_cItem[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProceduresMonitorArgumentValuesDialog)
	enum { IDD = IDD_TCPROCEDURESMONITOR_ARGUMENTVALUES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProceduresMonitorItem *pItem);

	class CTCProceduresMonitorSettingsContentsPage *GetParentDialog() CONST;
	class CTCProceduresMonitorWnd *GetParentDisplay() CONST;

private:
	BOOL EnumArguments();

	VOID ShowArgumentValues();
	VOID ShowArgumentValues(CONST CDatabaseTCProcedureArgument *pArgument);

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorArgumentValuesDialog)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProceduresMonitorArgumentValuesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSetValue();
	afx_msg void OnEditchangeValue();
	afx_msg void OnSelchangeValue();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorExecutionOptionsDialog dialog

#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_DETAILS   1001
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_STATIC   1002
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_IMMEDIATELY   1003
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATSTARTUP   1004
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATDAILYTIME   1005
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATDAILYTIME_TIME   1006
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATTIME   1007
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATTIME_TIME   1008
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL   1009
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STARTTIME   1010
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STARTTIME_STATIC   1011
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_INTERVAL   1012
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_INTERVAL_STATIC   1013
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT   1014
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT_NUMBER   1015
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPCOUNT_NUMBER_STATIC   1016
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPTIME   1017
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATINTERVAL_STOPTIME_TIME   1018
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT   1019
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_ATEVENT_NAME   1020
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_DISABLED   1021
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_RUN_MANUAL   1022
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE   1023
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_AUTOMATIC   1024
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_STATIC   1025
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_SINGLESTEP   1026
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_EXTERNALACTIONS   1027
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_COMMANDS   1028
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_MODE_BREAKS   1029
#define IDC_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_HELP   1030

// Specify the telecommand procedures monitor execution options dialog related settings
#define TCPROCEDURESMONITOREXECUTIONOPTIONSDIALOG_MINIMUMTRIGGERINTERVAL   1
#define TCPROCEDURESMONITOREXECUTIONOPTIONSDIALOG_MAXIMUMTRIGGERINTERVAL   (SECONDSPERDAY*DAYSPERWEEK)
#define TCPROCEDURESMONITOREXECUTIONOPTIONSDIALOG_DEFAULTTRIGGERINTERVAL   SECONDSPERHOUR
#define TCPROCEDURESMONITOREXECUTIONOPTIONSDIALOG_MINIMUMTRIGGERCOUNT   1
#define TCPROCEDURESMONITOREXECUTIONOPTIONSDIALOG_MAXIMUMTRIGGERCOUNT   1000
#define TCPROCEDURESMONITOREXECUTIONOPTIONSDIALOG_DEFAULTTRIGGERCOUNT   5

class CTCProceduresMonitorExecutionOptionsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProceduresMonitorExecutionOptionsDialog)

	// Construction
public:
	CTCProceduresMonitorExecutionOptionsDialog();   // standard constructor

	// Attributes
private:
	CTCProceduresMonitorItem  m_cItem[2];

	// Dialog Data
	//{{AFX_DATA(CTCProceduresMonitorExecutionOptionsDialog)
	enum { IDD = IDD_TCPROCEDURESMONITOR_EXECUTIONOPTIONS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProceduresMonitorItem *pItem);

	class CTCProceduresMonitorSettingsContentsPage *GetParentDialog() CONST;
	class CTCProceduresMonitorWnd *GetParentDisplay() CONST;

private:
	BOOL EnumTriggerEvents();

	VOID ShowExecutionDetails();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorExecutionOptionsDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProceduresMonitorExecutionOptionsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnTriggerImmediately();
	afx_msg void OnTriggerAlwaysAfterStartup();
	afx_msg void OnTriggerAtDailyTime();
	afx_msg void OnTriggerAtTime();
	afx_msg void OnTriggerAtInterval();
	afx_msg void OnTriggerStopAtCount();
	afx_msg void OnTriggerStopAtTime();
	afx_msg void OnTriggerAtEvent();
	afx_msg void OnTriggerDisabled();
	afx_msg void OnAllowManualExecution();
	afx_msg void OnModeAutomatic();
	afx_msg void OnModeSingleStep();
	afx_msg void OnModeExternalActions();
	afx_msg void OnModeCommands();
	afx_msg void OnModeExecutionBreaks();
	afx_msg void OnSelchangeTriggerEvent();
	afx_msg void OnSpinchangeTriggerDailyTime();
	afx_msg void OnSpinchangeTriggerTime();
	afx_msg void OnSpinchangeTriggerIntervalStartTime();
	afx_msg void OnSpinchangeTriggerInterval();
	afx_msg void OnSpinchangeTriggerIntervalStopCount();
	afx_msg void OnSpinchangeTriggerIntervalStopTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorCommandOptionsDialog dialog

#define IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_DETAILS   1001
#define IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_THREAD_STATIC   1002
#define IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_THREAD   1003
#define IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS_STATIC   1004
#define IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_STEPS   1005
#define IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES   1006
#define IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK   1007
#define IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCK_NAME   1008
#define IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_INTERLOCKS   1009
#define IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW   1010
#define IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_DEFAULT   1011
#define IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_UNLIMITED   1012
#define IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED   1013
#define IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED_INTERVAL   1014
#define IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_PROPERTIES_TIMEWINDOW_LIMITED_INTERVAL_STATIC   1015
#define IDC_TCPROCEDURESMONITOR_COMMANDOPTIONS_HELP   1016

// Specify the telecommand procedures monitor command options related limits
#define TCPROCEDURESMONITORCOMMANDOPTIONSDIALOG_MINIMUMTIMEWINDOWINTERVAL   1
#define TCPROCEDURESMONITORCOMMANDOPTIONSDIALOG_MAXIMUMTIMEWINDOWINTERVAL   SECONDSPERDAY
#define TCPROCEDURESMONITORCOMMANDOPTIONSDIALOG_DEFAULTTIMEWINDOWINTERVAL   SECONDSPERMINUTE

class CTCProceduresMonitorCommandOptionsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProceduresMonitorCommandOptionsDialog)

	// Construction
public:
	CTCProceduresMonitorCommandOptionsDialog();   // standard constructor

	// Attributes
private:
	CTCProceduresMonitorItem  m_cItem[2];
private:
	CTCInterlocks  m_pInterlocks[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProceduresMonitorCommandOptionsDialog)
	enum { IDD = IDD_TCPROCEDURESMONITOR_COMMANDOPTIONS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProceduresMonitorItem *pItem);

private:
	BOOL EnumThreads();
	BOOL EnumThreadSteps();
	BOOL EnumInterlocks();

	VOID ShowThreadStepProperties();

	INT FindThreadStep(CString &szThread, CString &szStep, CString &szFunction) CONST;
	INT FindThreadStep(INT nIndex, CString &szThread, CString &szStep, CString &szFunction) CONST;

	BOOL CheckTCVerificationStage(LPCTSTR pszFunction, UINT nStage) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorCommandOptionsDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProceduresMonitorCommandOptionsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnInterlock();
	afx_msg void OnInterlocks();
	afx_msg void OnTimeWindowDefault();
	afx_msg void OnTimeWindowUnlimited();
	afx_msg void OnTimeWindowLimited();
	afx_msg void OnSelchangeThread();
	afx_msg void OnSelchangeInterlock();
	afx_msg void OnSpinchangeTimeWindow();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorCommandInterlocksDialog dialog

#define IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_DETAILS   1001
#define IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME_STATIC   1002
#define IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_NAME   1003
#define IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_ADD   1004
#define IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_REMOVE   1005
#define IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_REMOVEALL   1006
#define IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES   1007
#define IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_STATIC   1008
#define IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_GLOBAL   1009
#define IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_LOCAL   1010
#define IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM   1011
#define IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME   1012
#define IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_TELECOMMANDS   1013
#define IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_SCOPE_NOWAITSTATE   1014
#define IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_STATIC   1015
#define IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_RECEPTION   1016
#define IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_TRANSMISSION   1017
#define IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_ACCEPTANCE   1018
#define IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_START   1019
#define IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_PROGRESS   1020
#define IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_PROPERTIES_STAGE_COMPLETION   1021
#define IDC_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_HELP   1022

class CTCProceduresMonitorCommandInterlocksDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProceduresMonitorCommandInterlocksDialog)

	// Construction
public:
	CTCProceduresMonitorCommandInterlocksDialog();   // standard constructor

	// Attributes
private:
	CTCInterlocks  m_pInterlocks[2];

	// Dialog Data
	//{{AFX_DATA(CTCProceduresMonitorCommandInterlocksDialog)
	enum { IDD = IDD_TCPROCEDURESMONITOR_COMMANDINTERLOCKS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCInterlocks &pInterlocks);

private:
	BOOL EnumInterlocks();
	BOOL EnumSubSystems();

	VOID ShowProperties();

	CTCInterlock *FindInterlock() CONST;

	UINT TranslateToSubSystemID(LPCTSTR pszSubSystem) CONST;
	CString TranslateIDToSubSystem(UINT nSubSystemID) CONST;

	BOOL CanAddInterlock() CONST;
	BOOL CanRemoveInterlock() CONST;
	BOOL CanRemoveAllInterlocks() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorCommandInterlocksDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProceduresMonitorCommandInterlocksDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnRemoveAll();
	afx_msg void OnScopeGlobal();
	afx_msg void OnScopeLocal();
	afx_msg void OnScopeSubSystem();
	afx_msg void OnScopeTeleommands();
	afx_msg void OnScopeNoWaitState();
	afx_msg void OnStageReception();
	afx_msg void OnStageTransmission();
	afx_msg void OnStageAcceptance();
	afx_msg void OnStageStart();
	afx_msg void OnStageProgress();
	afx_msg void OnStageCompletion();
	afx_msg void OnEditchangeName();
	afx_msg void OnSelchangeName();
	afx_msg void OnSelchangeSubSystem();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorAlertOptionsDialog dialog

#define IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_DETAILS   1001
#define IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE_STATIC   1002
#define IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_TYPE   1003
#define IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION   1004
#define IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_STATIC   1005
#define IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION   1006
#define IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_BLINK   1007
#define IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_COLOR_STATIC   1008
#define IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_AUDITION_COLOR   1009
#define IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_STATIC   1010
#define IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS   1011
#define IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_ADD   1012
#define IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVE   1013
#define IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVEALL   1014
#define IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST   1015
#define IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_ACKNOWLEDGMENT   1016
#define IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_ACKNOWLEDGMENT_COLOR_STATIC   1017
#define IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_ACTION_ACKNOWLEDGMENT_COLOR   1018
#define IDC_TCPROCEDURESMONITOR_ALERTOPTIONS_HELP   1019

class CTCProceduresMonitorAlertOptionsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProceduresMonitorAlertOptionsDialog)

	// Construction
public:
	CTCProceduresMonitorAlertOptionsDialog();   // standard constructor

	// Attributes
private:
	CTCProceduresMonitorItem  m_cItem[2];

	// Dialog Data
	//{{AFX_DATA(CTCProceduresMonitorAlertOptionsDialog)
	enum { IDD = IDD_TCPROCEDURESMONITOR_ALERTOPTIONS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProceduresMonitorItem *pItem);

	class CTCProceduresMonitorSettingsContentsPage *GetParentDialog() CONST;
	class CTCProceduresMonitorWnd *GetParentDisplay() CONST;

private:
	BOOL EnumTypes();
	BOOL EnumAuditions();
	BOOL EnumNotifications();

	VOID ShowAlertDetails();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorAlertOptionsDialog)
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProceduresMonitorAlertOptionsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAuditionBlink();
	afx_msg void OnAcknowledgeAlert();
	afx_msg void OnAddNotification();
	afx_msg void OnRemoveNotification();
	afx_msg void OnRemoveAllNotifications();
	afx_msg void OnSelchangeType();
	afx_msg void OnSelchangeAudition();
	afx_msg void OnSelchangeAuditionColor();
	afx_msg void OnSelchangeNotification();
	afx_msg void OnSelchangeNotificationList();
	afx_msg void OnSelchangeAcknowledgeColor();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorLoggingOptionsDialog dialog

#define IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_DETAILS   1001
#define IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_FILENAME_STATIC   1002
#define IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_FILENAME   1003
#define IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_BROWSE   1004
#define IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_DISABLED   1005
#define IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_RETRIEVALS   1006
#define IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY   1007
#define IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_OVERWRITE   1008
#define IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_OLDOVERWRITE   1009
#define IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_DAYS_STATIC   1010
#define IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_DAYS   1011
#define IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_POLICY_NOOVERWRITE   1012
#define IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE   1013
#define IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_UNLIMITED   1014
#define IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_LIMITED   1015
#define IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_MAXIMUM_STATIC   1016
#define IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_MAXIMUM   1017
#define IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_SIZE_RESET   1018
#define IDC_TCPROCEDURESMONITOR_LOGGINGOPTIONS_HELP   1019

// Specify the telecommand procedures monitor logging options dialog related settings
#define TCPROCEDURESMONITORLOGGINGOPTIONS_MINIMUMDAYS   1
#define TCPROCEDURESMONITORLOGGINGOPTIONS_MAXIMUMDAYS   10000
#define TCPROCEDURESMONITORLOGGINGOPTIONS_DEFAULTDAYS   DAYSPERWEEK
#define TCPROCEDURESMONITORLOGGINGOPTIONS_MINIMUMSIZE   8
#define TCPROCEDURESMONITORLOGGINGOPTIONS_MAXIMUMSIZE   2147483647
#define TCPROCEDURESMONITORLOGGINGOPTIONS_DEFAULTSIZE   (LOGFILE_DEFAULT_SIZE/1024)

class CTCProceduresMonitorLoggingOptionsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProceduresMonitorLoggingOptionsDialog)

	// Construction
public:
	CTCProceduresMonitorLoggingOptionsDialog();   // standard constructor

	// Attributes
private:
	CString  m_szArchivalFileName[2];
	CString  m_szRetrievalFileName[2];
	DWORDLONG  m_dwArchivalRetention[2];
	CTimeSpan  m_tArchivalRetention[2];
	UINT  m_nArchivalPolicy[2];

	// Dialog Data
	//{{AFX_DATA(CTCProceduresMonitorLoggingOptionsDialog)
	enum { IDD = IDD_TCPROCEDURESMONITOR_LOGGINGOPTIONS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CString &szArchivalFileName, UINT &nArchivalPolicy, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName);

	class CTCProceduresMonitorLoggingPage *GetParentDialog() CONST;
	class CTCProceduresMonitorWnd *GetParentDisplay() CONST;

private:
	VOID ShowLoggingOptions();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorLoggingOptionsDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProceduresMonitorLoggingOptionsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRetrievals();
	afx_msg void OnBrowseFileName();
	afx_msg void OnOverwriteLogs();
	afx_msg void OnOverwriteOldLogs();
	afx_msg void OnOverwriteNoLogs();
	afx_msg void OnUnlimitedSize();
	afx_msg void OnLimitedSize();
	afx_msg void OnResetSize();
	afx_msg void OnDisabled();
	afx_msg void OnSpinchangeDays();
	afx_msg void OnSpinchangeSize();
	afx_msg void OnEditchangeFileName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorRetrievalOptionsDialog dialog

#define IDC_TCPROCEDURESMONITOR_RETRIEVALOPTIONS_DETAILS   1001
#define IDC_TCPROCEDURESMONITOR_RETRIEVALOPTIONS_FILENAME_STATIC   1002
#define IDC_TCPROCEDURESMONITOR_RETRIEVALOPTIONS_FILENAME   1003
#define IDC_TCPROCEDURESMONITOR_RETRIEVALOPTIONS_BROWSE   1004
#define IDC_TCPROCEDURESMONITOR_RETRIEVALOPTIONS_HELP   1005

class CTCProceduresMonitorRetrievalOptionsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProceduresMonitorRetrievalOptionsDialog)

	// Construction
public:
	CTCProceduresMonitorRetrievalOptionsDialog();   // standard constructor

	// Attributes
private:
	CString  m_szFileName[2];

	// Dialog Data
	//{{AFX_DATA(CTCProceduresMonitorRetrievalOptionsDialog)
	enum { IDD = IDD_TCPROCEDURESMONITOR_RETRIEVALOPTIONS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CString &szFileName);

	class CTCProceduresMonitorLoggingOptionsDialog *GetParentDialog() CONST;
	class CTCProceduresMonitorWnd *GetParentDisplay() CONST;

private:
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorRetrievalOptionsDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProceduresMonitorRetrievalOptionsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBrowseFileName();
	afx_msg void OnEditchangeFileName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorDetailsDialog dialog

#define IDC_TCPROCEDURESMONITOR_ITEM_DETAILS   1001
#define IDC_TCPROCEDURESMONITOR_ITEM_NAME_STATIC   1002
#define IDC_TCPROCEDURESMONITOR_ITEM_NAME   1003
#define IDC_TCPROCEDURESMONITOR_ITEM_DESCRIPTION_STATIC   1004
#define IDC_TCPROCEDURESMONITOR_ITEM_DESCRIPTION   1005
#define IDC_TCPROCEDURESMONITOR_ITEM_ARGUMENTS_STATIC   1006
#define IDC_TCPROCEDURESMONITOR_ITEM_ARGUMENTS   1007
#define IDC_TCPROCEDURESMONITOR_ITEM_RUNNINGSTATE_STATIC   1008
#define IDC_TCPROCEDURESMONITOR_ITEM_RUNNINGSTATE_NOTRUNNING   1009
#define IDC_TCPROCEDURESMONITOR_ITEM_RUNNINGSTATE_RUNNING   1010
#define IDC_TCPROCEDURESMONITOR_ITEM_RUNNINGSTATE_STOPPED   1011
#define IDC_TCPROCEDURESMONITOR_ITEM_EXECUTIONMODE_STATIC   1012
#define IDC_TCPROCEDURESMONITOR_ITEM_EXECUTIONMODE_AUTOMATIC   1013
#define IDC_TCPROCEDURESMONITOR_ITEM_EXECUTIONMODE_SINGLESTEP   1014
#define IDC_TCPROCEDURESMONITOR_ITEM_EXECUTIONMODE_EXTERNALACTIONS   1015
#define IDC_TCPROCEDURESMONITOR_ITEM_EXECUTIONMODE_COMMANDS   1016
#define IDC_TCPROCEDURESMONITOR_ITEM_ACKNOWLEDGEREQUEST_STATIC   1017
#define IDC_TCPROCEDURESMONITOR_ITEM_ACKNOWLEDGEREQUEST   1018
#define IDC_TCPROCEDURESMONITOR_ITEM_ACKNOWLEDGE   1019
#define IDC_TCPROCEDURESMONITOR_ITEM_HELP   1020

class CTCProceduresMonitorDetailsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProceduresMonitorDetailsDialog)

	// Construction
public:
	CTCProceduresMonitorDetailsDialog();   // standard constructor

	// Attributes
private:
	CString  m_szAlert;
	CTCProceduresMonitorItem  m_cItem;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProceduresMonitorDetailsDialog)
	enum { IDD = IDD_TCPROCEDURESMONITOR_DETAILS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CTCProceduresMonitorWnd *GetParentDisplay() CONST;

private:
	BOOL EnumProcedureArguments();

	VOID ShowProcedureState();
	BOOL ShowProcedureAlert();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorDetailsDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProceduresMonitorDetailsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAcknowledge();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorAcknowledgmentsDialog dialog

#define IDC_TCPROCEDURESMONITOR_ACKNOWLEDGMENTS_DETAILS   1001
#define IDC_TCPROCEDURESMONITOR_ACKNOWLEDGMENTS_REQUEST_STATIC   1002
#define IDC_TCPROCEDURESMONITOR_ACKNOWLEDGMENTS_REQUEST   1003
#define IDC_TCPROCEDURESMONITOR_ACKNOWLEDGMENTS_CONFIRM   1004
#define IDC_TCPROCEDURESMONITOR_ACKNOWLEDGMENTS_HELP   1005

class CTCProceduresMonitorAcknowledgmentsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProceduresMonitorAcknowledgmentsDialog)

	// Construction
public:
	CTCProceduresMonitorAcknowledgmentsDialog();   // standard constructor

	// Attributes
private:
	CString  m_szAlert;
	CTCProceduresMonitorItem  m_cItem;

	// Dialog Data
	//{{AFX_DATA(CTCProceduresMonitorAcknowledgmentsDialog)
	enum { IDD = IDD_TCPROCEDURESMONITOR_ACKNOWLEDGMENTS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CTCProceduresMonitorWnd *GetParentDisplay() CONST;

private:
	BOOL ShowProcedureAlert();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorAcknowledgmentsDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProceduresMonitorAcknowledgmentsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAcknowledge();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorAuthorizationsDialog dialog

#define IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_DETAILS   1001
#define IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_MESSAGE_STATIC   1002
#define IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_MESSAGE   1003
#define IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS_STATIC   1004
#define IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TELECOMMANDS   1005
#define IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TIME_STATIC   1006
#define IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_TIME   1007
#define IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE   1008
#define IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE_PROCEDURE_STATIC   1009
#define IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE_PROCEDURE   1010
#define IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE_THREAD_STATIC   1011
#define IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE_THREAD   1012
#define IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE_STEP_STATIC   1013
#define IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_SOURCE_STEP   1014
#define IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_GRANT   1015
#define IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_DENY   1016
#define IDC_TCPROCEDURESMONITOR_AUTHORIZATIONS_HELP   1017

class CTCProceduresMonitorAuthorizationsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProceduresMonitorAuthorizationsDialog)

	// Construction
public:
	CTCProceduresMonitorAuthorizationsDialog();   // standard constructor

	// Attributes
private:
	INT  m_nItemIndex;
	CString  m_szSource[3];
	CTCItems  m_pTCItems;
	CPtrArray  m_pListedTCItems;
	CTCProceduresMonitorItem  m_cItem;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProceduresMonitorAuthorizationsDialog)
	enum { IDD = IDD_TCPROCEDURESMONITOR_AUTHORIZATIONS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CTCProceduresMonitorWnd *GetParentDisplay() CONST;

private:
	VOID ShowTelecommandSource();
	BOOL ShowTelecommandAlerts();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorAuthorizationsDialog)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProceduresMonitorAuthorizationsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnGrantAuthorization();
	afx_msg void OnDenyAuthorization();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorInterlocksDialog dialog

#define IDC_TCPROCEDURESMONITOR_INTERLOCKS_DETAILS   1001
#define IDC_TCPROCEDURESMONITOR_INTERLOCKS_LIST   1002
#define IDC_TCPROCEDURESMONITOR_INTERLOCKS_RESET   1003
#define IDC_TCPROCEDURESMONITOR_INTERLOCKS_RESETALL   1004
#define IDC_TCPROCEDURESMONITOR_INTERLOCKS_HELP   1005

class CTCProceduresMonitorInterlocksDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProceduresMonitorInterlocksDialog)

	// Construction
public:
	CTCProceduresMonitorInterlocksDialog();   // standard constructor

	// Attributes
private:
	CTCInterlocks  m_pInterlocks[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProceduresMonitorInterlocksDialog)
	enum { IDD = IDD_TCPROCEDURESMONITOR_INTERLOCKS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCInterlocks &pInterlocks);

private:
	BOOL EnumInterlocks();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorInterlocksDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProceduresMonitorInterlocksDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnReset();
	afx_msg void OnResetAll();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorToolBar window

class CTCProceduresMonitorToolBar : public CDisplayToolBar
{
	DECLARE_DYNCREATE(CTCProceduresMonitorToolBar)

	// Construction
public:
	CTCProceduresMonitorToolBar();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorToolBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProceduresMonitorToolBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorStatusBar window

class CTCProceduresMonitorStatusBar : public CDisplayStatusBar
{
	DECLARE_DYNCREATE(CTCProceduresMonitorStatusBar)

	// Construction
public:
	CTCProceduresMonitorStatusBar();

	// Attributes
private:
	CToolTipCtrl  m_wndToolTip;

	// Operations
public:
	BOOL SetIndicators(CONST UINT *pPanesID, INT nCount);

	class CTCProceduresMonitorWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorStatusBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProceduresMonitorStatusBar)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorViewToolTip window

// Specify the telecommand procedures monitor view tooltip timer identifiers
#define TCPROCEDURESMONITORVIEW_TOOLTIP_TIMERID   100
#define TCPROCEDURESMONITORVIEW_TOOLTIP_TIMEOUT   5000

class CTCProceduresMonitorViewToolTip : public CDisplayToolTip
{
	DECLARE_DYNCREATE(CTCProceduresMonitorViewToolTip)

	// Construction
public:
	CTCProceduresMonitorViewToolTip();

	// Attributes
public:

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST POINT &point, LPCTSTR pszTitle, LPCTSTR pszText, BOOL bAutoDestroy = FALSE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorViewToolTip)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProceduresMonitorViewToolTip)
	afx_msg void OnTimer(UINT_PTR nEventID);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorDocument

class CTCProceduresMonitorDocument : public CDocument
{
	DECLARE_DYNAMIC(CTCProceduresMonitorDocument)

	// Construction
public:
	CTCProceduresMonitorDocument();
	virtual ~CTCProceduresMonitorDocument();

	// Attributes
private:

	// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorTextView window

// Specify the telecommand procedures monitor command check flag symbol identifiers
#define TCPROCEDURESMONITORTEXTVIEW_COMMANDCHECKFLAGSYMBOL_NONE   0
#define TCPROCEDURESMONITORTEXTVIEW_COMMANDCHECKFLAGSYMBOL_ON   1
#define TCPROCEDURESMONITORTEXTVIEW_COMMANDCHECKFLAGSYMBOL_OFF   2
#define TCPROCEDURESMONITORTEXTVIEW_COMMANDCHECKFLAGSYMBOL_DISABLED   3
#define TCPROCEDURESMONITORTEXTVIEW_COMMANDCHECKFLAGSYMBOLS   4
// Specify the telecommand procedures monitor command alert symbol identifiers
#define TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOL_INFORMATION   0
#define TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOL_WARNING   1
#define TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOL_ERROR   2
#define TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOL_ALERT   3
#define TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOL_AUTHORIZATION   4
#define TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOLS   5

class CTCProceduresMonitorTextView : public CTextView
{
	DECLARE_DYNCREATE(CTCProceduresMonitorTextView)

	// Construction
public:
	CTCProceduresMonitorTextView();

	// Attributes
private:
	CSize m_sizeAlertSymbols;
	CSize m_sizeCheckFlagSymbols;
	CImage  *m_pAlertSymbols[TCPROCEDURESMONITORTEXTVIEW_COMMANDALERTSYMBOLS];
	CImage  *m_pCheckFlagSymbols[TCPROCEDURESMONITORTEXTVIEW_COMMANDCHECKFLAGSYMBOLS];
	CTCProceduresMonitorViewToolTip  m_wndToolTip;
	HCURSOR  m_hToolTipCursor;
	BOOL  m_bToolTips;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle);

	BOOL SetLayout(CONST CUIntArray &nColumns);
	BOOL SetLayout(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayout(CUIntArray &nColumns) CONST;
	BOOL GetLayout(CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetTitleFont(CFont *pFont);
	BOOL SetTitleFont(CONST LOGFONT *plfFont);
	BOOL GetTitleFont(CFont *pFont) CONST;
	BOOL GetTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetItemsFont(CFont *pFont);
	BOOL SetItemsFont(CONST LOGFONT *plfFont);
	BOOL GetItemsFont(CFont *pFont) CONST;
	BOOL GetItemsFont(LOGFONT *plfFont) CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetText(INT nRow, LPCTSTR pszText, CONST CTextViewAttribute *pAttribute = NULL, BOOL bRedraw = TRUE);
	BOOL SetText(INT nRow, INT nColumn, LPCTSTR pszText, BOOL bRedraw = TRUE);
	BOOL GetText(INT nRow, INT nColumn, CString &szText) CONST;

	BOOL SetCurText(INT nItem);
	INT GetCurText() CONST;

	BOOL GetPrintProperties(CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	VOID UpdateContent(BOOL bRedraw = TRUE);

	class CTCProceduresMonitorListView *GetParent() CONST;
	class CTCProceduresMonitorWnd *GetParentDisplay() CONST;

private:
	CString LookupColumnName(UINT nColumn) CONST;
	UINT LookupColumnName(LPCTSTR pszColumn) CONST;
	INT LookupColumnsName(CONST CUIntArray &nColumns, CStringArray &szColumns) CONST;
	COLORREF LookupColumnColor(UINT nColumn) CONST;

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths);

	CRect CalcTelecommandSymbolPosition(INT nRow, INT nColumn, LPCTSTR pszText) CONST;
	CRect CalcTelecommandSymbolPosition(INT nRow, INT nColumn, INT nCount, INT nIndex) CONST;

	CString ConstructToolTipTitle(LPCTSTR pszTip, UINT nTip) CONST;
	CString ConstructToolTipText(INT nIndex, LPCTSTR pszTip, UINT nTip) CONST;

	BOOL LoadTelecommandSymbols();
	VOID FreeTelecommandSymbols();

	BOOL LoadToolTipCursor();
	HCURSOR GetToolTipCursor() CONST;
	BOOL FreeToolTipCursor();

public:
	static TCHAR GetSymbolDelimiter();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorTextView)
public:
	virtual BOOL SetLayoutInfo(INT nIndex, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	virtual BOOL GetLayoutInfo(INT &nIndex, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;
public:
	virtual VOID RefreshContent();
public:
	virtual VOID DrawContent();
	virtual VOID DrawContent(CDC *pDC);
	virtual VOID DrawText(INT nItem, LPCTSTR pszText);
	virtual VOID DrawText(CDC *pDC, INT nItem, LPCTSTR pszText);
	virtual VOID DrawText(INT nItem, INT nColumn, LPCTSTR pszText);
	virtual VOID DrawText(CDC *pDC, INT nItem, INT nColumn, LPCTSTR pszText);
	virtual BOOL DrawBackground(CDC *pDC, INT nItem, INT nColumn, CONST RECT &rItem);
public:
	virtual BOOL OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult);
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProceduresMonitorTextView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorListView window

// Specify the telecommand procedures monitor list view related identifiers
#define TCPROCEDURESMONITORLISTVIEW_STARTPROCEDURE_TIMERID   100
#define TCPROCEDURESMONITORLISTVIEW_STARTPROCEDURE_TIMEOUT   0
#define TCPROCEDURESMONITORLISTVIEW_STOPPROCEDURE_TIMERID   101
#define TCPROCEDURESMONITORLISTVIEW_STOPPROCEDURE_TIMEOUT   0

class CTCProceduresMonitorListView : public CView
{
	DECLARE_DYNCREATE(CTCProceduresMonitorListView)

	// Construction
public:
	CTCProceduresMonitorListView();
	~CTCProceduresMonitorListView();

	// Attributes
private:
	UINT  m_nTelecommandingMode;
	UINT  m_nTelecommandingState;
	UINT  m_nTelecommandingFlags;
	UINT  m_nTelecommandingUplinkState;
	BOOL  m_bTelecommandingReleaseWaitMode;
private:
	CTCItems  m_pTCItems;
	CTCProceduresMonitorItems  m_pItems;
	CPtrArray  m_pItemThreads;
private:
	CTCEnvironment  *m_pTCEnvironment;
	CTCProcessEngine  *m_pTCProcessEngine;
private:
	CTCProceduresMonitorTextView  *m_pwndList;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL SetLayout(CONST CUIntArray &nColumns);
	BOOL SetLayout(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayout(CUIntArray &nColumns) CONST;
	BOOL GetLayout(CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetListTitleFont(CFont *pFont);
	BOOL SetListTitleFont(CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(CFont *pFont) CONST;
	BOOL GetListTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(CFont *pFont);
	BOOL SetListItemsFont(CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(CFont *pFont) CONST;
	BOOL GetListItemsFont(LOGFONT *plfFont) CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetProcedures(CONST CTCProceduresMonitorItems &pItems);
	BOOL GetProcedures(CTCProceduresMonitorItems &pItems) CONST;
	BOOL UpdateProcedure(CONST CTCItem *pTCItem);

	BOOL StartProcedure(INT nIndex);
	BOOL CanStartProcedure(INT nIndex) CONST;
	BOOL IsProcedureRunning(INT nIndex) CONST;
	BOOL SuspendProcedure(INT nIndex);
	BOOL ResumeProcedure(INT nIndex);
	BOOL IsProcedureSuspended(INT nIndex) CONST;
	BOOL IsProcedureDisabled(INT nIndex) CONST;
	BOOL StepIntoProcedure(INT nIndex, INT nThreadID);
	BOOL CanStepIntoProcedure(INT nIndex, INT nThreadID) CONST;
	BOOL StepOverProcedure(INT nIndex, INT nThreadID);
	BOOL CanStepOverProcedure(INT nIndex, INT nThreadID) CONST;
	BOOL StepOutProcedure(INT nIndex, INT nThreadID);
	BOOL CanStepOutProcedure(INT nIndex, INT nThreadID) CONST;
	BOOL ResetProcedure(INT nIndex);
	BOOL CanResetProcedure(INT nIndex) CONST;
	BOOL CanBreakProcedure(INT nIndex) CONST;
	BOOL AbortProcedure(INT nIndex);

	BOOL UpdateProcedure(INT nIndex);
	BOOL UpdateProcedure(INT nIndex, UINT nTriggerType, UINT nRunningState, CONST CTimeKey &tExecutionStartTime = 0, CONST CTimeKey &tExecutionEndTime = 0, UINT nExecutionCount = 0);

	BOOL AlertProcedure(INT nIndex, UINT nType, LPCTSTR pszAlert);
	BOOL AlertProcedure(INT nIndex, UINT nType, LPCTSTR pszAlert, CONST CTimeTag &tAlertTime);
	BOOL AcknowledgeProcedure(INT nIndex, BOOL bAll = FALSE);
	BOOL CanAcknowledgeProcedure(INT nIndex) CONST;
	BOOL AcknowledgeAllProcedures();

	BOOL SetProcedureInfo(INT nIndex, CONST CTCProceduresMonitorItem *pItem, BOOL bAll = TRUE);
	BOOL GetProcedureInfo(INT nIndex, CTCProceduresMonitorItem *pItem, BOOL bAll = TRUE) CONST;
	BOOL GetProcedureInfo(INT nIndex, CDatabaseTCProcedure *pProcedure) CONST;
	BOOL GetProcedureInfo(INT nIndex, CString &szName, UINT &nMode, UINT &nState) CONST;

	BOOL SetCurProcedure(INT nIndex);
	INT GetCurProcedure() CONST;

	UINT GetProcedureCount() CONST;

	BOOL StartMonitoring(CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, BOOL bStartup = TRUE);
	BOOL UpdateMonitoring(CONST CTMEnvironment *pTMEnvironment);
	BOOL UpdateMonitoring(LPCTSTR pszEvent);
	BOOL IsMonitoring() CONST;
	BOOL StopMonitoring();

	BOOL SetTelecommandingMode(UINT nMode);
	UINT GetTelecommandingMode() CONST;
	BOOL SetTelecommandingChecks(UINT nFlags);
	UINT GetTelecommandingChecks() CONST;
	BOOL SetTelecommandingState(UINT nState);
	UINT GetTelecommandingState() CONST;
	BOOL SetTelecommandingUplinkState(UINT nState);
	UINT GetTelecommandingUplinkState() CONST;
	BOOL EnableTelecommandingReleaseWaitMode(BOOL bEnable);
	BOOL IsTelecommandingReleaseWaitModeEnabled() CONST;

	BOOL InitializeTelecommand(INT nProcedureID, LPCTSTR pszThread, LPCTSTR pszStep, LPCTSTR pszFunction, INT nEntry, CTCItem *pTCItem);
	BOOL EnumAuthorizableTelecommands(INT nIndex, CTCItems &pTCItems) CONST;
	BOOL AuthorizeTelecommands(INT nIndex, CONST CTCItems &pTCItems);
	BOOL AuthorizeTelecommands(CONST CTCItems &pTCItems);
	BOOL CanAuthorizeTelecommands(INT nIndex) CONST;

	BOOL GetPrintProperties(CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs, BOOL bAll) CONST;

	BOOL UpdateContent(BOOL bAll = FALSE);

	VOID SetTrackSize(CONST SIZE &size);
	CSize GetTrackSize() CONST;

	class CTCProceduresMonitorView *GetParent() CONST;
	class CTCProceduresMonitorWnd *GetParentDisplay() CONST;

private:
	VOID ShowContent(INT nIndex = -1);

	INT CreateItem(INT nID);
	INT FindItem(INT nID) CONST;
	BOOL DestroyItem(INT nID);

	INT GenerateItemID() CONST;

	BOOL TranslateAlertLoggingInfo(CEventObject *pEvent, LPCTSTR pszLog) CONST;
	CString ParseAlertLoggingOption(LPCTSTR pszLog, LPCTSTR pszOption, INT &nPos) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorListView)
public:
	virtual BOOL SetLayoutInfo(INT nIndex, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	virtual BOOL GetLayoutInfo(INT &nIndex, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;
protected:
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
	virtual void PostNcDestroy();
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProceduresMonitorListView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemFlowchartThreadViewStatePane window

class CTCProceduresMonitorItemFlowchartThreadViewStatePane : public CWnd
{
	DECLARE_DYNCREATE(CTCProceduresMonitorItemFlowchartThreadViewStatePane)

	// Construction
public:
	CTCProceduresMonitorItemFlowchartThreadViewStatePane();
	~CTCProceduresMonitorItemFlowchartThreadViewStatePane();

	// Attributes
private:
	BOOL  m_bBreaks;
	CStringArray  m_szBreakpoints;
	CDatabaseTCProcedureThreadBreakpoints  m_pBreakpoints;
private:
	UINT  m_nExecutionState;
	CString  m_szExecutionStep;
private:
	BOOL  m_bToolTips;
	CString  m_szToolTip;
	CTCProceduresMonitorViewToolTip  m_wndToolTip;
private:
	CCriticalSection  *m_pCriticalSection;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID SetBreakpoints(CONST CDatabaseTCProcedureThreadBreakpoints &pBreakpoints);
	INT GetBreakpoints(CDatabaseTCProcedureThreadBreakpoints &pBreakpoints) CONST;

	VOID AllowExecutionBreaks(BOOL bAllow = TRUE);
	BOOL AreExecutionBreaksAllowed() CONST;

	VOID EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	VOID UpdateExecutionpoint();
	VOID UpdateExecutionpoint(UINT nState);
	VOID UpdateExecutionpoint(LPCTSTR pszStep, UINT nState);

	class CTCProceduresMonitorItemFlowchartThreadView *GetParent() CONST;

private:
	VOID DrawContent();
	VOID DrawContent(CDC *pDC);
	VOID DrawBreakpoints(CDC *pDC);
	VOID DrawExecutionpoint(CDC *pDC);

	CTCProcedureDocumentItem *FindBreakpoint(CTCProcedureDocumentItem *pStep) CONST;
	CTCProcedureDocumentItem *FindBreakpoint(CTCProcedureDocument *pSubSteps, CTCProcedureDocumentItem *pStep) CONST;
	CTCProcedureDocumentItem *FindExecutionpoint(LPCTSTR pszStep) CONST;
	CTCProcedureDocumentItem *FindContainerStep(CONST CTCProcedureDocumentItem *pStep) CONST;

	CRect CalcBreakpointPosition(CTCProcedureDocumentItem *pStep) CONST;
	INT CalcBreakpointRadius() CONST;
	INT CalcBreakpointIndent() CONST;
	CRect CalcExecutionpointPosition(CTCProcedureDocumentItem *pStep) CONST;
	INT CalcExecutionpointExtent() CONST;
	INT CalcExecutionpointIndent() CONST;

	BOOL Lock();
	BOOL Unlock();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorItemFlowchartThreadViewStatePane)
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProceduresMonitorItemFlowchartThreadViewStatePane)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemFlowchartThreadView view

class CTCProceduresMonitorItemFlowchartThreadView : public CScrollView
{
	DECLARE_DYNCREATE(CTCProceduresMonitorItemFlowchartThreadView)

	// Construction
public:
	CTCProceduresMonitorItemFlowchartThreadView();

	// Attributes
private:
	BOOL  m_bBreaks;
	BOOL  m_bRunning;
	BOOL  m_bToolTips;
	CPoint  m_ptScroll;
	HCURSOR  m_hToolTipCursor;
	LOGFONT  m_lfStepsLabelFont;
	COLORREF  m_nStepsLabelColor;
	COLORREF  m_nBackgroundColor;
	CTCProcedureDocument  *m_pFlowchart;
private:
	CTCProceduresMonitorViewToolTip  m_wndToolTip;
	CTCProceduresMonitorItemFlowchartThreadViewStatePane  m_wndStatePane;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, UINT nID, BOOL bVisible = TRUE);

	VOID SetBreakpoints(CONST CDatabaseTCProcedureThreadBreakpoints &pBreakpoints);
	INT GetBreakpoints(CDatabaseTCProcedureThreadBreakpoints &pBreakpoints) CONST;

	BOOL SetSteps(CONST CTCProcedureDocument *pFlowchart);
	BOOL GetSteps(CTCProcedureDocument *pFlowchart) CONST;
	INT EnumSteps(INT nY, CPtrArray &pSteps, CStringArray &szSteps) CONST;
	BOOL SetActiveStep(CONST CTCProcedureDocumentItem *pStep = NULL);
	CTCProcedureDocumentItem *GetActiveStep(BOOL bAll = FALSE) CONST;
	CTCProcedureDocumentItem *FindStep(LPCTSTR pszName) CONST;
	INT GetTotalSteps() CONST;

	VOID SetStepsLabelFont(CONST LOGFONT *plfFont);
	BOOL GetStepsLabelFont(LOGFONT *plfFont) CONST;
	VOID SetStepsLabelColor(COLORREF nColor);
	COLORREF GetStepsLabelColor() CONST;
	VOID SetBackgroundColor(COLORREF nColor);
	COLORREF GetBackgroundColor() CONST;

	VOID AllowExecutionBreaks(BOOL bAllow = TRUE);
	BOOL AreExecutionBreaksAllowed() CONST;

	VOID EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	VOID UpdateAllSteps(CPtrArray &pSteps);
	VOID UpdateAllSteps(BOOL bRedraw = TRUE);
	VOID UpdateAllSteps(UINT nState, CONST CStringArray &szSteps, CONST CUIntArray &nStates);

	BOOL UpdateAllBreakpoints();

	BOOL HasImage() CONST;

	VOID GetPrintProperties(CMetaFileDC *pMetaDC) CONST;

	CTCProcedureDocument *GetDocument() CONST;

	class CTCProceduresMonitorItemFlowchartTabCtrl *GetParent() CONST;
	class CTCProceduresMonitorWnd *GetParentDisplay() CONST;

private:
	VOID DrawContent();
	VOID DrawContent(CDC *pDC);

	VOID AdjustSteps(CONST CTCProcedureDocumentItem *pStep, INT nOffset);
	VOID AdjustSteps(CONST CTCProcedureDocumentItem *pSteps, CONST CTCProcedureDocumentItem *pStep, INT nOffset);

	POSITION FindStep(CONST CTCProcedureDocumentItem *pStep, BOOL bAll = FALSE) CONST;
	POSITION FindStep(CONST CTCProcedureDocumentItem *pSteps, CONST CTCProcedureDocumentItem *pStep, BOOL bAll = FALSE) CONST;
	CTCProcedureDocumentItem *FindStep(CONST POINT &pt, BOOL bImage = TRUE, BOOL bTreeSymbol = TRUE, BOOL bAll = FALSE) CONST;
	CTCProcedureDocumentItem *FindStep(CONST CTCProcedureDocumentItem *pSteps, CONST POINT &pt, BOOL bImage = TRUE, BOOL bTreeSymbol = TRUE, BOOL bAll = FALSE) CONST;
	CTCProcedureDocumentItem *FindStep(POSITION &lPosition) CONST;
	CTCProcedureDocumentItem *FindStep(CONST CTCProcedureDocumentItem *pSteps, POSITION &lPosition) CONST;
	CTCProcedureDocumentItem *FindContainerStep(CONST CTCProcedureDocumentItem *pStep) CONST;

	CRect CalcStatePanePosition() CONST;
	CRect CalcStatePanePosition(INT cx, INT cy) CONST;
	INT CalcStatePaneMarginSize() CONST;

	CSize CalcScrollSizes() CONST;

	BOOL LoadToolTipCursor();
	HCURSOR GetToolTipCursor() CONST;
	BOOL FreeToolTipCursor();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorItemFlowchartThreadView)
protected:
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProceduresMonitorItemFlowchartThreadView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemFlowchartTabCtrl

class CTCProceduresMonitorItemFlowchartTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCProceduresMonitorItemFlowchartTabCtrl)

	// Construction
public:
	CTCProceduresMonitorItemFlowchartTabCtrl();

	// Attributes
private:
	INT  m_nIndex;
	CFont  m_cTabFont;
	CSize  m_sizeTabMargins;
	CStringArray  m_szViews;
	CPtrArray  m_pViews;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, CONST CStringArray &szTabs);

	BOOL SetFlowcharts(CONST CTCProceduresMonitorItem *pItem);
	BOOL GetFlowcharts(CTCProceduresMonitorItem *pItem) CONST;

	VOID SetBreakpoints(CONST CStringArray &szBreakpoints, CONST CDatabaseTCProcedureThreadBreakpoints &pBreakpoints);
	INT GetBreakpoints(CStringArray &szBreakpoints, CDatabaseTCProcedureThreadBreakpoints &pBreakpoints) CONST;

	BOOL SetActiveStep(CONST CTCProcedureDocumentItem *pStep = NULL);
	CTCProcedureDocumentItem *GetActiveStep(BOOL bAll = FALSE) CONST;
	INT GetTotalSteps() CONST;

	BOOL SetStepsTitleFont(CONST LOGFONT *plfFont);
	BOOL GetStepsTitleFont(LOGFONT *plfFont) CONST;
	VOID SetStepsLabelFont(CONST LOGFONT *plfFont);
	BOOL GetStepsLabelFont(LOGFONT *plfFont) CONST;
	VOID SetStepsLabelColor(COLORREF nColor);
	COLORREF GetStepsLabelColor() CONST;
	VOID SetBackgroundColor(COLORREF nColor);
	COLORREF GetBackgroundColor() CONST;

	VOID AllowExecutionBreaks(BOOL bAllow = TRUE);
	BOOL AreExecutionBreaksAllowed() CONST;

	VOID EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	VOID SetSelectedThreadID(INT nThreadID = 0);
	INT GetSelectedThreadID() CONST;

	INT SetCurTab(INT nIndex);
	INT GetCurTab() CONST;
	INT GetTabCount() CONST;

	BOOL HasImage() CONST;

	VOID UpdateSteps();
	BOOL UpdateSteps(INT nThreadID, UINT nState, CONST CStringArray &szSteps, CONST CUIntArray &nStates);

	BOOL GetPrintProperties(CStringArray &szThreads, CPtrArray &pThreadMetaDCs) CONST;

	CSize GetMargins() CONST;

	class CTCProceduresMonitorItemFlowchartView *GetParent() CONST;
	class CTCProceduresMonitorWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorItemFlowchartTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProceduresMonitorItemFlowchartTabCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSelchange(NMHDR *pNotifyStruct, LRESULT *pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemFlowchartView view

class CTCProceduresMonitorItemFlowchartView : public CView, public CDisplayLockable
{
	DECLARE_DYNCREATE(CTCProceduresMonitorItemFlowchartView)

	// Construction
public:
	CTCProceduresMonitorItemFlowchartView();

	// Attributes
private:
	BOOL  m_bBreaks;
	BOOL  m_bToolTips;
	CSize  m_sizeTrackLayout;
	LOGFONT  m_lfTitleFont;
	LOGFONT  m_lfLabelsFont;
	COLORREF  m_nLabelsColor;
	COLORREF  m_nBackgroundColor;
	CTCProceduresMonitorItemFlowchartTabCtrl  m_wndTabCtrl;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL SetFlowcharts(CONST CTCProceduresMonitorItem *pItem);
	BOOL GetFlowcharts(CTCProceduresMonitorItem *pItem) CONST;

	BOOL SetTitleFont(CFont *pFont);
	BOOL SetTitleFont(CONST LOGFONT *plfFont);
	BOOL GetTitleFont(CFont *pFont) CONST;
	BOOL GetTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetLabelsFont(CFont *pFont);
	BOOL SetLabelsFont(CONST LOGFONT *plfFont);
	BOOL GetLabelsFont(CFont *pFont) CONST;
	BOOL GetLabelsFont(LOGFONT *plfFont) CONST;
	BOOL SetLabelsColor(COLORREF nColor);
	BOOL GetLabelsColor(COLORREF &nColor) CONST;
	BOOL SetBackgroundColor(COLORREF nColor);
	BOOL GetBackgroundColor(COLORREF &nColor) CONST;

	BOOL AllowExecutionBreaks(BOOL bAllow = TRUE);
	BOOL AreExecutionBreaksAllowed() CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetSelectedThreadID(INT nThreadID = 0);
	INT GetSelectedThreadID() CONST;

	BOOL GetPrintProperties(CStringArray &szThreads, CPtrArray &pThreadMetaDCs) CONST;

	BOOL UpdateContents();
	BOOL UpdateContents(INT nThreadID, UINT nState, CONST CStringArray &szSteps, CONST CUIntArray &nStates);
	BOOL HasContents() CONST;

	VOID SetTrackSize(CONST SIZE &size);
	CSize GetTrackSize() CONST;

	class CTCProceduresMonitorItemContents *GetParent() CONST;
	class CTCProceduresMonitorWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorItemFlowchartView)
public:
	virtual BOOL SetLayoutInfo(INT nThreadID);
	virtual BOOL GetLayoutInfo(INT &nThreadID) CONST;
protected:
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProceduresMonitorItemFlowchartView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemCodeEdit window

class CTCProceduresMonitorItemCodeEdit : public CTPLCodeEdit, public CDisplayLockable
{
	DECLARE_DYNCREATE(CTCProceduresMonitorItemCodeEdit)

	// Construction
public:
	CTCProceduresMonitorItemCodeEdit();

	// Attributes
private:
	BOOL  m_bBreaks;
	CStringArray  m_szBreakpoints;
	CDatabaseTCProcedureThreadBreakpoints  m_pBreakpoints;
private:
	CUIntArray  m_nExecutionThreadIDs;
	CUIntArray  m_nExecutionStates;
	CUIntArray  m_nExecutionLines;
private:
	CFont  m_cCodeFont;
	CSize  m_sizeCodeFont;
private:
	BOOL  m_bToolTips;
	CString  m_szToolTip;
	CTCProceduresMonitorViewToolTip  m_wndToolTip;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID SetSourceCode(LPCTSTR pszCode);
	BOOL SetSourceCode(CONST CByteArray &nCode);
	CString GetSourceCode() CONST;
	BOOL GetSourceCode(CByteArray &nCode) CONST;
	VOID SetBreakpoints(CONST CStringArray &szBreakpoints, CONST CDatabaseTCProcedureThreadBreakpoints &pBreakpoints);
	INT GetBreakpoints(CStringArray &szBreakpoints, CDatabaseTCProcedureThreadBreakpoints &pBreakpoints) CONST;

	VOID AllowExecutionBreaks(BOOL bAllow = TRUE);
	BOOL AreExecutionBreaksAllowed() CONST;

	VOID EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetFont(CFont *pFont, BOOL bRedraw = TRUE);
	BOOL GetFont(CFont *pFont) CONST;

	VOID UpdateBreakpoints();
	VOID UpdateExecutionpoint(UINT nThreadID, UINT nState = TCPROCEDURETHREAD_RUNNINGSTATE_NOTRUNNING, UINT nLine = 0);

	class CTCProceduresMonitorItemCodeView *GetParent() CONST;
	class CTCProceduresMonitorWnd *GetParentDisplay() CONST;

private:
	VOID DrawMargin();
	VOID DrawMargin(CDC *pDC);
	VOID DrawBreakpoints(CDC *pDC);
	VOID DrawExecutionpoint(CDC *pDC);

	CString CheckLine(UINT nLine) CONST;

	INT FindKeyword(LPCTSTR pszSourceCode, LPCTSTR pszKeyword, INT nPos) CONST;
	LPCTSTR FindKeyword(LPCTSTR pszSourceCode, LPCTSTR pszKeyword) CONST;

	CRect CalcBreakpointPosition(INT nLine) CONST;
	INT CalcBreakpointRadius() CONST;
	INT CalcBreakpointIndent() CONST;
	CRect CalcExecutionpointPosition(INT nLine) CONST;
	INT CalcExecutionpointExtent() CONST;
	INT CalcExecutionpointIndent() CONST;

	CRect CalcMargin() CONST;

private:
	static DWORD CALLBACK SetCodeCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
	static DWORD CALLBACK GetCodeCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorItemCodeEdit)
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProceduresMonitorItemCodeEdit)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnPaint();
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnEditchangeCode();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemCodeView view

class CTCProceduresMonitorItemCodeView : public CView
{
	DECLARE_DYNCREATE(CTCProceduresMonitorItemCodeView)

	// Construction
public:
	CTCProceduresMonitorItemCodeView();
	~CTCProceduresMonitorItemCodeView();

	// Attributes
private:
	BOOL  m_bBreaks;
	BOOL  m_bToolTips;
	CSize  m_sizeTrackLayout;
	CTCProceduresMonitorItemCodeEdit  *m_pwndCode;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL SetFont(CFont *pFont);
	BOOL SetFont(CONST LOGFONT *plfFont);
	BOOL GetFont(CFont *pFont) CONST;
	BOOL GetFont(LOGFONT *plfFont) CONST;

	BOOL AllowExecutionBreaks(BOOL bAllow = TRUE);
	BOOL AreExecutionBreaksAllowed() CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL UpdateBreakpoints(LPCTSTR pszThread, CONST CDatabaseTCProcedureThreadBreakpoints &pBreakpoints);

	BOOL UpdateContent();
	BOOL UpdateContent(INT nThreadID, UINT nState, UINT nLine);

	VOID SetTrackSize(CONST SIZE &size);
	CSize GetTrackSize() CONST;

	class CTCProceduresMonitorItemContents *GetParent() CONST;
	class CTCProceduresMonitorWnd *GetParentDisplay() CONST;

private:
	CRect CalcCodePosition() CONST;
	CRect CalcCodePosition(INT cx, INT cy) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorItemCodeView)
protected:
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProceduresMonitorItemCodeView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemContents window

class CTCProceduresMonitorItemContents : public CSplitterWndEx
{
	DECLARE_DYNCREATE(CTCProceduresMonitorItemContents)

	// Construction
public:
	CTCProceduresMonitorItemContents();

	// Attributes
private:
	CTCProceduresMonitorItemFlowchartView  *m_pFlowchartView;
	CTCProceduresMonitorItemCodeView  *m_pCodeView;
private:
	CSize  m_sizeFlowchartPane;
	CSize  m_sizeCodePane;
	BOOL  m_bTracking;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	BOOL SetLayout(CONST SIZE &sizeFlowchartPane, CONST SIZE &sizeCodePane);
	BOOL GetLayout(CSize &sizeFlowchartPane, CSize &sizeCodePane) CONST;

	BOOL SetFlowcharts(CONST CTCProceduresMonitorItem *pItem);
	BOOL GetFlowcharts(CTCProceduresMonitorItem *pItem) CONST;
	BOOL SetFlowchartTitleFont(CFont *pFont);
	BOOL SetFlowchartTitleFont(CONST LOGFONT *plfFont);
	BOOL GetFlowchartTitleFont(CFont *pFont) CONST;
	BOOL GetFlowchartTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetFlowchartLabelsFont(CFont *pFont);
	BOOL SetFlowchartLabelsFont(CONST LOGFONT *plfFont);
	BOOL GetFlowchartLabelsFont(CFont *pFont) CONST;
	BOOL GetFlowchartLabelsFont(LOGFONT *plfFont) CONST;
	BOOL SetFlowchartLabelsColor(COLORREF nColor);
	BOOL GetFlowchartLabelsColor(COLORREF &nColor) CONST;
	BOOL SetFlowchartBackgroundColor(COLORREF nColor);
	BOOL GetFlowchartBackgroundColor(COLORREF &nColor) CONST;
	BOOL SetSourceCodeFont(CFont *pFont);
	BOOL SetSourceCodeFont(CONST LOGFONT *plfFont);
	BOOL GetSourceCodeFont(CFont *pFont) CONST;
	BOOL GetSourceCodeFont(LOGFONT *plfFont) CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetSelectedThreadID(INT nThreadID = 0);
	INT GetSelectedThreadID() CONST;

	BOOL GetPrintProperties(CStringArray &szThreads, CPtrArray &pThreadMetaDCs) CONST;

	BOOL UpdateContents();
	BOOL UpdateContents(INT nThreadID, UINT nState, CONST CStringArray &szSteps, CONST CUIntArray &nStates, UINT nLine);

	VOID SetTrackSize(CONST SIZE &size);
	CSize GetTrackSize() CONST;

	CTCProceduresMonitorItemFlowchartView *GetFlowchartView() CONST;
	CTCProceduresMonitorItemCodeView *GetCodeView() CONST;

	class CTCProceduresMonitorItemView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorItemContents)
public:
	virtual BOOL SetLayoutInfo(INT nThreadID);
	virtual BOOL GetLayoutInfo(INT &nThreadID) CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CTCProceduresMonitorItemContents)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorItemView view

class CTCProceduresMonitorItemView : public CView
{
	DECLARE_DYNCREATE(CTCProceduresMonitorItemView)

	// Construction
public:
	CTCProceduresMonitorItemView();

	// Attributes
private:
	CTCProceduresMonitorItemContents  m_wndContents;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL SetLayout(CONST SIZE &sizeFlowchartPane, CONST SIZE &sizeCodePane);
	BOOL GetLayout(CSize &sizeFlowchartPane, CSize &sizeCodePane) CONST;

	BOOL SetFlowcharts(CONST CTCProceduresMonitorItem *pItem);
	BOOL GetFlowcharts(CTCProceduresMonitorItem *pItem) CONST;
	BOOL SetFlowchartTitleFont(CFont *pFont);
	BOOL SetFlowchartTitleFont(CONST LOGFONT *plfFont);
	BOOL GetFlowchartTitleFont(CFont *pFont) CONST;
	BOOL GetFlowchartTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetFlowchartLabelsFont(CFont *pFont);
	BOOL SetFlowchartLabelsFont(CONST LOGFONT *plfFont);
	BOOL GetFlowchartLabelsFont(CFont *pFont) CONST;
	BOOL GetFlowchartLabelsFont(LOGFONT *plfFont) CONST;
	BOOL SetFlowchartLabelsColor(COLORREF nColor);
	BOOL GetFlowchartLabelsColor(COLORREF &nColor) CONST;
	BOOL SetFlowchartBackgroundColor(COLORREF nColor);
	BOOL GetFlowchartBackgroundColor(COLORREF &nColor) CONST;
	BOOL SetSourceCodeFont(CFont *pFont);
	BOOL SetSourceCodeFont(CONST LOGFONT *plfFont);
	BOOL GetSourceCodeFont(CFont *pFont) CONST;
	BOOL GetSourceCodeFont(LOGFONT *plfFont) CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetSelectedThreadID(INT nThreadID = 0);
	INT GetSelectedThreadID() CONST;

	BOOL GetPrintProperties(CStringArray &szThreads, CPtrArray &pThreadMetaDCs) CONST;

	BOOL UpdateContents();
	BOOL UpdateContents(INT nThreadID, UINT nState, CONST CStringArray &szSteps, CONST CUIntArray &nStates, UINT nLine);

	VOID SetTrackSize(CONST SIZE &size);
	CSize GetTrackSize() CONST;

	class CTCProceduresMonitorView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorItemView)
public:
	virtual BOOL SetLayoutInfo(INT nThreadID);
	virtual BOOL GetLayoutInfo(INT &nThreadID) CONST;
protected:
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProceduresMonitorItemView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorView window

class CTCProceduresMonitorView : public CSplitterWndEx
{
	DECLARE_DYNCREATE(CTCProceduresMonitorView)

	// Construction
public:
	CTCProceduresMonitorView();

	// Attributes
private:
	CSize  m_sizeListPane;
	CSize  m_sizeCodePane;
	CSize  m_sizeFlowchartPane;
	CUIntArray  m_nColumns;
	CUIntArray  m_nColumnWidths;
	LOGFONT  m_lfListTitleFont;
	LOGFONT  m_lfListItemsFont;
	LOGFONT  m_lfItemSourceCodeFont;
	LOGFONT  m_lfItemFlowchartTitleFont;
	LOGFONT  m_lfItemFlowchartLabelsFont;
	COLORREF  m_nItemFlowchartColor[2];
	BOOL  m_bTracking;
	BOOL  m_bToolTips;
private:
	UINT  m_nTelecommandingMode;
	UINT  m_nTelecommandingState;
	UINT  m_nTelecommandingFlags;
	UINT  m_nTelecommandingUplinkState;
	BOOL  m_bTelecommandingReleaseWaitMode;
private:
	CTCProceduresMonitorItems  m_pContents;
private:
	CTCProceduresMonitorListView  *m_pListView;
	CTCProceduresMonitorItemView  *m_pItemView;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	BOOL SetLayout(CONST CUIntArray &nColumns);
	BOOL SetLayout(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL SetLayout(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST SIZE &sizeListPane, CONST SIZE &sizeFlowchartPane, CONST SIZE &sizeCodePane);
	BOOL GetLayout(CUIntArray &nColumns) CONST;
	BOOL GetLayout(CUIntArray &nColumns, CUIntArray &nWidths) CONST;
	BOOL GetLayout(CUIntArray &nColumns, CUIntArray &nWidths, CSize &sizeListPane, CSize &sizeFlowchartPane, CSize &sizeCodePane) CONST;

	BOOL SetListTitleFont(CFont *pFont);
	BOOL SetListTitleFont(CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(CFont *pFont) CONST;
	BOOL GetListTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(CFont *pFont);
	BOOL SetListItemsFont(CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(CFont *pFont) CONST;
	BOOL GetListItemsFont(LOGFONT *plfFont) CONST;
	BOOL SetItemFlowcharts(CONST CTCProceduresMonitorItem *pItem);
	BOOL GetItemFlowcharts(CTCProceduresMonitorItem *pItem) CONST;
	BOOL SetItemFlowchartTitleFont(CFont *pFont);
	BOOL SetItemFlowchartTitleFont(CONST LOGFONT *plfFont);
	BOOL GetItemFlowchartTitleFont(CFont *pFont) CONST;
	BOOL GetItemFlowchartTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetItemFlowchartLabelsFont(CFont *pFont);
	BOOL SetItemFlowchartLabelsFont(CONST LOGFONT *plfFont);
	BOOL GetItemFlowchartLabelsFont(CFont *pFont) CONST;
	BOOL GetItemFlowchartLabelsFont(LOGFONT *plfFont) CONST;
	BOOL SetItemFlowchartLabelsColor(COLORREF nColor);
	BOOL GetItemFlowchartLabelsColor(COLORREF &nColor) CONST;
	BOOL SetItemFlowchartBackgroundColor(COLORREF nColor);
	BOOL GetItemFlowchartBackgroundColor(COLORREF &nColor) CONST;
	BOOL SetItemSourceCodeFont(CFont *pFont);
	BOOL SetItemSourceCodeFont(CONST LOGFONT *plfFont);
	BOOL GetItemSourceCodeFont(CFont *pFont) CONST;
	BOOL GetItemSourceCodeFont(LOGFONT *plfFont) CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetProcedures(CONST CTCProceduresMonitorItems &pItems);
	BOOL GetProcedures(CTCProceduresMonitorItems &pItems) CONST;
	BOOL UpdateProcedure(CONST CTCItem *pTCItem);

	BOOL StartProcedure(INT nIndex);
	BOOL CanStartProcedure(INT nIndex) CONST;
	BOOL IsProcedureRunning(INT nIndex) CONST;
	BOOL SuspendProcedure(INT nIndex);
	BOOL ResumeProcedure(INT nIndex);
	BOOL IsProcedureSuspended(INT nIndex) CONST;
	BOOL IsProcedureDisabled(INT nIndex) CONST;
	BOOL StepIntoProcedure(INT nIndex);
	BOOL CanStepIntoProcedure(INT nIndex) CONST;
	BOOL StepOverProcedure(INT nIndex);
	BOOL CanStepOverProcedure(INT nIndex) CONST;
	BOOL StepOutProcedure(INT nIndex);
	BOOL CanStepOutProcedure(INT nIndex) CONST;
	BOOL UpdateProcedure(INT nIndex);
	BOOL UpdateProcedure(INT nIndex, UINT nTriggerType, UINT nRunningState, CONST CTimeKey &tExecutionStartTime = 0, CONST CTimeKey &tExecutionEndTime = 0, UINT nExecutionCount = 0);
	BOOL UpdateProcedure(INT nIndex, UINT nTriggerType, UINT nRunningState, INT nThreadID, UINT nThreadState, CONST CStringArray &szThreadSteps, CONST CUIntArray &nThreadStates, UINT nThreadLine);
	BOOL UpdateProcedure(INT nIndex, INT nThreadID, UINT nThreadState, CONST CStringArray &szThreadSteps, CONST CUIntArray &nThreadStates, UINT nThreadLine);
	BOOL AlertProcedure(INT nIndex, UINT nType, LPCTSTR pszAlert);
	BOOL AcknowledgeProcedure(INT nIndex);
	BOOL CanAcknowledgeProcedure(INT nIndex) CONST;
	BOOL ResetProcedure(INT nIndex);
	BOOL CanResetProcedure(INT nIndex) CONST;
	BOOL CanBreakProcedure(INT nIndex) CONST;
	BOOL AbortProcedure(INT nIndex);

	BOOL SetProcedureInfo(INT nIndex, CONST CTCProceduresMonitorItem *pItem, BOOL bAll = TRUE);
	BOOL GetProcedureInfo(INT nIndex, CTCProceduresMonitorItem *pItem, BOOL bAll = TRUE) CONST;
	BOOL GetProcedureInfo(INT nIndex, CDatabaseTCProcedure *pProcedure) CONST;
	BOOL GetProcedureInfo(INT nIndex, CString &szName, UINT &nMode, UINT &nState) CONST;

	BOOL SetCurProcedure(INT nIndex);
	INT GetCurProcedure() CONST;

	BOOL AcknowledgeAllProcedures();

	UINT GetProcedureCount() CONST;

	BOOL StartMonitoring(CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, BOOL bStartup = TRUE);
	BOOL UpdateMonitoring(CONST CTMEnvironment *pTMEnvironment);
	BOOL UpdateMonitoring(LPCTSTR pszEvent);
	BOOL IsMonitoring() CONST;
	BOOL StopMonitoring();

	BOOL SetTelecommandingMode(UINT nMode);
	UINT GetTelecommandingMode() CONST;
	BOOL SetTelecommandingChecks(UINT nFlags);
	UINT GetTelecommandingChecks() CONST;
	BOOL SetTelecommandingState(UINT nState);
	UINT GetTelecommandingState() CONST;
	BOOL SetTelecommandingUplinkState(UINT nState);
	UINT GetTelecommandingUplinkState() CONST;
	BOOL EnableTelecommandingReleaseWaitMode(BOOL bEnable);
	BOOL IsTelecommandingReleaseWaitModeEnabled() CONST;

	BOOL InitializeTelecommand(INT nProcedureID, LPCTSTR pszThread, LPCTSTR pszStep, LPCTSTR pszFunction, INT nEntry, CTCItem *pTCItem);
	BOOL EnumAuthorizableTelecommands(INT nIndex, CTCItems &pTCItems) CONST;
	BOOL AuthorizeTelecommands(INT nIndex, CONST CTCItems &pTCItems);
	BOOL AuthorizeTelecommands(CONST CTCItems &pTCItems);
	BOOL CanAuthorizeTelecommands(INT nIndex) CONST;

	VOID UpdateContents(BOOL bAll = TRUE);

	VOID ResizeToContents(BOOL bAll = TRUE);
	VOID AdjustToParentSize(CONST RECT &rect);

	BOOL GetPrintProperties(CONST CTCProceduresMonitorPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, CStringArray &szThreads, CPtrArray &pThreadMetaDCs, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	CTCProceduresMonitorListView *GetListView() CONST;
	CTCProceduresMonitorItemView *GetItemView() CONST;

	class CTCProceduresMonitorWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorView)
public:
	virtual BOOL SetLayoutInfo(INT nIndex, INT nThreadID, CONST SCROLLINFO *pListPaneHorzScrollInfo, CONST SCROLLINFO *pListPaneVertScrollInfo);
	virtual BOOL GetLayoutInfo(INT &nIndex, INT &nThreadID, SCROLLINFO *pListPaneHorzScrollInfo, SCROLLINFO *pListPaneVertScrollInfo) CONST;
public:
	virtual VOID RecalcLayout();
	virtual VOID RecalcLayout(BOOL bRecalc);
protected:
	virtual void StartTracking(int ht);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CTCProceduresMonitorView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProceduresMonitorWnd frame with splitter

// Specify the telecommand procedures monitor title items
#define TCPROCEDURESMONITOR_TITLEITEM_NAME   (1<<0)
#define TCPROCEDURESMONITOR_TITLEITEM_DESCRIPTION   (1<<1)
#define TCPROCEDURESMONITOR_TITLEITEM_COMMENTS   (1<<2)
#define TCPROCEDURESMONITOR_TITLEITEM_AUTHOR   (1<<3)
#define TCPROCEDURESMONITOR_TITLEITEM_CREATIONTIME   (1<<4)
#define TCPROCEDURESMONITOR_TITLEITEM_MODIFICATIONTIME   (1<<5)
#define TCPROCEDURESMONITOR_TITLEITEM_VERIFICATIONSTATUS   (1<<6)
#define TCPROCEDURESMONITOR_TITLEITEM_NUMBEROFTHREADS   (1<<7)
#define TCPROCEDURESMONITOR_TITLEITEM_ARGUMENTS   (1<<8)
#define TCPROCEDURESMONITOR_TITLEITEM_TRIGGERTYPE   (1<<9)
#define TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONMODE   (1<<10)
#define TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONCOUNT   (1<<11)
#define TCPROCEDURESMONITOR_TITLEITEM_RUNNINGSTATE   (1<<12)
#define TCPROCEDURESMONITOR_TITLEITEM_ACKNOWLEDGEREQUEST   (1<<13)
#define TCPROCEDURESMONITOR_TITLEITEM_ACKREQUESTTIME   (1<<14)
#define TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS   (1<<15)
#define TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS   (1<<16)
#define TCPROCEDURESMONITOR_TITLEITEM_STARTTIME   (1<<17)
#define TCPROCEDURESMONITOR_TITLEITEM_ENDTIME   (1<<18)
#ifndef RC_INVOKED
#define TCPROCEDURESMONITOR_TITLEITEMS_DEFAULT   (TCPROCEDURESMONITOR_TITLEITEM_NAME | TCPROCEDURESMONITOR_TITLEITEM_DESCRIPTION | TCPROCEDURESMONITOR_TITLEITEM_ARGUMENTS | TCPROCEDURESMONITOR_TITLEITEM_TRIGGERTYPE | TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONMODE | TCPROCEDURESMONITOR_TITLEITEM_RUNNINGSTATE | TCPROCEDURESMONITOR_TITLEITEM_ACKNOWLEDGEREQUEST | TCPROCEDURESMONITOR_TITLEITEM_ACKREQUESTTIME | TCPROCEDURESMONITOR_TITLEITEM_STARTTIME | TCPROCEDURESMONITOR_TITLEITEM_ENDTIME)
#define TCPROCEDURESMONITOR_TITLEITEMS_ALL   (TCPROCEDURESMONITOR_TITLEITEMS_DEFAULT | TCPROCEDURESMONITOR_TITLEITEM_COMMENTS | TCPROCEDURESMONITOR_TITLEITEM_AUTHOR | TCPROCEDURESMONITOR_TITLEITEM_CREATIONTIME | TCPROCEDURESMONITOR_TITLEITEM_MODIFICATIONTIME | TCPROCEDURESMONITOR_TITLEITEM_VERIFICATIONSTATUS | TCPROCEDURESMONITOR_TITLEITEM_NUMBEROFTHREADS | TCPROCEDURESMONITOR_TITLEITEM_EXECUTIONCOUNT | TCPROCEDURESMONITOR_TITLEITEM_PEVCHECKS | TCPROCEDURESMONITOR_TITLEITEM_CEVCHECKS)
#endif
// Specify the telecommand procedures monitor command source modes
#define TCPROCEDURESMONITOR_MODE_DEFAULT   TCSERVICE_COMMANDSOURCEMODE_DEFAULT
// Specify the telecommand procedures monitor command source checks
#define TCPROCEDURESMONITOR_CHECKS_DEFAULT   TCSERVICE_COMMANDSOURCEFLAGS_DEFAULT
#define TCPROCEDURESMONITOR_CHECKS_PEV_OVERRIDE   TCSERVICE_COMMANDSOURCEFLAGS_PEV_OVERRIDE
#define TCPROCEDURESMONITOR_CHECKS_CEV_OVERRIDE   TCSERVICE_COMMANDSOURCEFLAGS_CEV_OVERRIDE
#define TCPROCEDURESMONITOR_CHECKS_PEV_DISABLE   TCSERVICE_COMMANDSOURCEFLAGS_PEV_DISABLE
#define TCPROCEDURESMONITOR_CHECKS_CEV_DISABLE   TCSERVICE_COMMANDSOURCEFLAGS_CEV_DISABLE
// Specify the telecommand procedures monitor command source states
#define TCPROCEDURESMONITOR_STATE_DEFAULT   TCSERVICE_COMMANDSOURCESTATE_DEFAULT
#define TCPROCEDURESMONITOR_STATE_DISABLED   TCSERVICE_COMMANDSOURCESTATE_DISABLED
#define TCPROCEDURESMONITOR_STATE_IDLE   TCSERVICE_COMMANDSOURCESTATE_EMPTY
// Specify the telecommand procedures monitor print modes
#define TCPROCEDURESMONITOR_PRINT_LIST   (1<<0)
#define TCPROCEDURESMONITOR_PRINT_FLOWCHART   (1<<1)
#define TCPROCEDURESMONITOR_PRINT_ONEONLY   (1<<2)
#define TCPROCEDURESMONITOR_PRINT_AUTOSCALE   (1<<3)
#define TCPROCEDURESMONITOR_PRINT_FIXEDSCALE   (1<<4)
#define TCPROCEDURESMONITOR_PRINT_CLEARCOMMENTS   (1<<5)
// Specify the telecommand procedures monitor print fonts
#define TCPROCEDURESMONITOR_PRINTFONT_TITLE   0
#define TCPROCEDURESMONITOR_PRINTFONT_SUBTITLE   1
#define TCPROCEDURESMONITOR_PRINTFONT_OPERATINGDETAILS   2
#define TCPROCEDURESMONITOR_PRINTFONT_LISTITEMSTITLE   3
#define TCPROCEDURESMONITOR_PRINTFONT_LISTITEMS   4
#define TCPROCEDURESMONITOR_PRINTFONT_FOOTER   5
#define TCPROCEDURESMONITOR_PRINTFONT_NOTICE   6
#define TCPROCEDURESMONITOR_PRINTFONT_LOGO   7
#define TCPROCEDURESMONITOR_PRINTFONTS   8
// Specify the telecommand procedures monitor statusbar pane identifiers
#define ID_TCPROCEDURESMONITOR_STATUSBAR_MESSAGEPANE   ID_SEPARATOR
#define ID_TCPROCEDURESMONITOR_STATUSBAR_UPLINKPANE   ID_STATUSBAR_PANE1
#define ID_TCPROCEDURESMONITOR_STATUSBAR_PEVPANE   ID_STATUSBAR_PANE2
#define ID_TCPROCEDURESMONITOR_STATUSBAR_CEVPANE   ID_STATUSBAR_PANE3
#define ID_TCPROCEDURESMONITOR_STATUSBAR_STATEPANE   ID_STATUSBAR_PANE4

class CTCProceduresMonitorWnd : public CDisplayWnd
{
	DECLARE_DYNAMIC(CTCProceduresMonitorWnd)

	// Construction
public:
	CTCProceduresMonitorWnd();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  nIndex;
		INT  nThreadID;
		INT  cbColumns[2];
		SIZE  sizePanes[3];
		LOGFONT  sFont[4];
		COLORREF  nColor[2];
		SCROLLINFO  sScrollInfo[2];
	} DATA, *PDATA, *LPDATA;
private:
	CTCProceduresMonitorToolBar  m_wndToolBar;
	CTCProceduresMonitorStatusBar  m_wndStatusBar;
	CTCProceduresMonitorView  m_wndView;
private:
	CTCProceduresMonitorSettingsDialog  m_dlgSettings;
	CTCProceduresMonitorDetailsDialog  m_dlgDetails;
	CTCProceduresMonitorAcknowledgmentsDialog  m_dlgAcknowledgments;
	CTCProceduresMonitorAuthorizationsDialog  m_dlgAuthorizations;
	CTCProceduresMonitorInterlocksDialog  m_dlgInterlocks;
private:
	CTCProceduresMonitorPrintJobs  m_pPrintJobs;
private:
	UINT  m_nLoggingPolicy;
	UINT  m_nLoggingReloadCount;
	CString  m_szLoggingFileName[2];
	CTimeSpan  m_tLoggingRetention;
	DWORDLONG  m_dwLoggingRetention;
	BOOL  m_bLoggingAsEvent;

	// Operations
public:
	BOOL SetLayout(CONST CUIntArray &nColumns);
	BOOL SetLayout(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL SetLayout(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST SIZE &sizeListPane, CONST SIZE &sizeFlowchartPane, CONST SIZE &sizeCodePane);
	BOOL GetLayout(CUIntArray &nColumns) CONST;
	BOOL GetLayout(CUIntArray &nColumns, CUIntArray &nWidths) CONST;
	BOOL GetLayout(CUIntArray &nColumns, CUIntArray &nWidths, CSize &sizeListPane, CSize &sizeFlowchartPane, CSize &sizeCodePane) CONST;

	BOOL SetListTitleFont(CFont *pFont);
	BOOL SetListTitleFont(CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(CFont *pFont) CONST;
	BOOL GetListTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(CFont *pFont);
	BOOL SetListItemsFont(CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(CFont *pFont) CONST;
	BOOL GetListItemsFont(LOGFONT *plfFont) CONST;
	BOOL SetItemFlowcharts(CONST CTCProceduresMonitorItem *pItem);
	BOOL GetItemFlowcharts(CTCProceduresMonitorItem *pItem) CONST;
	BOOL SetItemFlowchartTitleFont(CFont *pFont);
	BOOL SetItemFlowchartTitleFont(CONST LOGFONT *plfFont);
	BOOL GetItemFlowchartTitleFont(CFont *pFont) CONST;
	BOOL GetItemFlowchartTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetItemFlowchartLabelsFont(CFont *pFont);
	BOOL SetItemFlowchartLabelsFont(CONST LOGFONT *plfFont);
	BOOL GetItemFlowchartLabelsFont(CFont *pFont) CONST;
	BOOL GetItemFlowchartLabelsFont(LOGFONT *plfFont) CONST;
	BOOL SetItemFlowchartLabelsColor(COLORREF nColor);
	BOOL GetItemFlowchartLabelsColor(COLORREF &nColor) CONST;
	BOOL SetItemFlowchartBackgroundColor(COLORREF nColor);
	BOOL GetItemFlowchartBackgroundColor(COLORREF &nColor) CONST;
	BOOL SetItemSourceCodeFont(CFont *pFont);
	BOOL SetItemSourceCodeFont(CONST LOGFONT *plfFont);
	BOOL GetItemSourceCodeFont(CFont *pFont) CONST;
	BOOL GetItemSourceCodeFont(LOGFONT *plfFont) CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetProcedures(CONST CTCProceduresMonitorItems &pItems);
	BOOL GetProcedures(CTCProceduresMonitorItems &pItems) CONST;
	BOOL UpdateProcedure(CONST CTCItem *pTCItem);

	BOOL StartProcedure(INT nIndex);
	BOOL CanStartProcedure(INT nIndex) CONST;
	BOOL IsProcedureRunning(INT nIndex) CONST;
	BOOL SuspendProcedure(INT nIndex);
	BOOL ResumeProcedure(INT nIndex);
	BOOL IsProcedureSuspended(INT nIndex) CONST;
	BOOL IsProcedureDisabled(INT nIndex) CONST;
	BOOL StepIntoProcedure(INT nIndex);
	BOOL CanStepIntoProcedure(INT nIndex) CONST;
	BOOL StepOverProcedure(INT nIndex);
	BOOL CanStepOverProcedure(INT nIndex) CONST;
	BOOL StepOutProcedure(INT nIndex);
	BOOL CanStepOutProcedure(INT nIndex) CONST;
	BOOL UpdateProcedure(INT nIndex);
	BOOL UpdateProcedure(INT nIndex, UINT nTriggerType, UINT nRunningState, CONST CTimeKey &tExecutionStartTime = 0, CONST CTimeKey &tExecutionEndTime = 0, UINT nExecutionCount = 0);
	BOOL UpdateProcedure(INT nIndex, UINT nTriggerType, UINT nRunningState, INT nThreadID, UINT nThreadState, CONST CStringArray &szThreadSteps, CONST CUIntArray &nThreadStates, UINT nThreadLine);
	BOOL UpdateProcedure(INT nIndex, INT nThreadID, UINT nThreadState, CONST CStringArray &szThreadSteps, CONST CUIntArray &nThreadStates, UINT nThreadLine);
	BOOL AlertProcedure(INT nIndex, UINT nType, LPCTSTR pszAlert);
	BOOL AcknowledgeProcedure(INT nIndex);
	BOOL CanAcknowledgeProcedure(INT nIndex) CONST;
	BOOL ResetProcedure(INT nIndex);
	BOOL CanResetProcedure(INT nIndex) CONST;
	BOOL CanBreakProcedure(INT nIndex) CONST;
	BOOL AbortProcedure(INT nIndex);

	VOID ShowProcedureDetails(INT nIndex);

	BOOL SetProcedureInfo(INT nIndex, CONST CTCProceduresMonitorItem *pItem, BOOL bAll = TRUE);
	BOOL GetProcedureInfo(INT nIndex, CTCProceduresMonitorItem *pItem, BOOL bAll = TRUE) CONST;
	BOOL GetProcedureInfo(INT nIndex, CDatabaseTCProcedure *pProcedure) CONST;
	BOOL GetProcedureInfo(INT nIndex, CString &szName, UINT &nMode, UINT &nState) CONST;

	BOOL SetCurProcedure(INT nIndex);
	INT GetCurProcedure() CONST;

	BOOL AcknowledgeAllProcedures();

	UINT GetProcedureCount() CONST;

	BOOL StartMonitoring(CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, BOOL bStartup = TRUE);
	BOOL UpdateMonitoring(LPCTSTR pszOriginator, CONST CTCProcessCommandSourceInfo *pCommandSourceInfo);
	BOOL UpdateMonitoring(CONST CTMEnvironment *pTMEnvironment);
	BOOL UpdateMonitoring(LPCTSTR pszEvent);
	BOOL IsMonitoring() CONST;
	BOOL StopMonitoring();

	BOOL SetTelecommandingMode(UINT nMode, BOOL bUser = TRUE);
	BOOL SetTelecommandingMode(LPCTSTR pszOriginator, UINT nMode, BOOL bUser = TRUE);
	UINT GetTelecommandingMode() CONST;
	BOOL SetTelecommandingChecks(UINT nFlags, BOOL bUser = TRUE);
	BOOL SetTelecommandingChecks(LPCTSTR pszOriginator, UINT nFlags, BOOL bUser = TRUE);
	UINT GetTelecommandingChecks() CONST;
	BOOL SetTelecommandingState(UINT nState, BOOL bUser = TRUE);
	BOOL SetTelecommandingState(LPCTSTR pszOriginator, UINT nState, BOOL bUser = TRUE);
	UINT GetTelecommandingState() CONST;
	BOOL SetTelecommandingUplinkState(UINT nState);
	UINT GetTelecommandingUplinkState() CONST;
	BOOL EnableTelecommandingReleaseWaitMode(BOOL bEnable, BOOL bUser = TRUE);
	BOOL EnableTelecommandingReleaseWaitMode(LPCTSTR pszOriginator, BOOL bEnable, BOOL bUser = TRUE);
	BOOL IsTelecommandingReleaseWaitModeEnabled() CONST;

	BOOL InitializeTelecommand(INT nProcedureID, LPCTSTR pszThread, LPCTSTR pszStep, LPCTSTR pszFunction, INT nEntry, CTCItem *pTCItem);
	BOOL EnumAuthorizableTelecommands(INT nIndex, CTCItems &pTCItems) CONST;
	BOOL AuthorizeTelecommands(INT nIndex, CONST CTCItems &pTCItems);
	BOOL AuthorizeTelecommands(CONST CTCItems &pTCItems);
	BOOL CanAuthorizeTelecommands(INT nIndex) CONST;

	BOOL DoResetInterlocks();
	BOOL CanResetInterlocks() CONST;

	BOOL SetLoggingOptions();
	BOOL SetLoggingOptions(UINT nArchivalPolicy, LPCTSTR pszArchivalFileName, DWORDLONG dwArchivalRetention, CONST CTimeSpan &tArchivalRetention, LPCTSTR pszRetrievalFileName, UINT nRetrievalReloadCount, BOOL bShowAsEvent);
	BOOL GetLoggingOptions(UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST;

	BOOL LogActivity(CONST CTCLogEntry *pEntry);

	BOOL SetPrintJobs(CONST CTCProceduresMonitorPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(CTCProceduresMonitorPrintJobs &pPrintJobs) CONST;

	BOOL Print(CONST CTCProceduresMonitorPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo = NULL);

	CTCProceduresMonitorListView *GetListView() CONST;
	CTCProceduresMonitorItemView *GetItemView() CONST;

private:
	BOOL CreateToolBar();
	BOOL CreateStatusBar();
	BOOL CreateView();

	BOOL Customize(BOOL bDefault);

	VOID UpdateToolBar();

	BOOL UpdateAllPanes();
	VOID UpdateMessagePane();
	VOID UpdateUplinkPane();
	VOID UpdatePreexecutionVerificationPane();
	VOID UpdateExecutionVerificationPane();
	VOID UpdateStatePane();

	VOID UpdateContents(BOOL bAll = TRUE);

	BOOL LogProcedures(CONST CTCProceduresMonitorItems &pItems, CONST CTCProceduresMonitorItems &pProcedures);
	BOOL LogTelecommandingMode(LPCTSTR pszOriginator, UINT nMode, BOOL bUser);
	BOOL LogTelecommandingState(LPCTSTR pszOriginator, UINT nState, BOOL bUser);
	BOOL LogTelecommandingChecks(LPCTSTR pszOriginator, UINT nFlags, BOOL bUser);
	BOOL LogTelecommandingReleaseWaitMode(LPCTSTR pszOriginator, BOOL bEnabled, BOOL bUser);
	BOOL LogResetInterlocks(CONST CTCInterlocks &pInterlocks);

	BOOL SetContents(CONST CByteArray &nContentsInfo);
	BOOL GetContents(CByteArray &nContentsInfo) CONST;

	BOOL SetPrintJobs(CONST CByteArray &nPrintInfo);
	BOOL GetPrintJobs(CByteArray &nPrintInfo) CONST;

	BOOL GetPrintProperties(CONST CTCProceduresMonitorPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, CStringArray &szThreads, CPtrArray &pThreadMetaDCs, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

private:
	BOOL StartPrintJob(CDC &cDC);
	BOOL PrintJob(CDC &cDC, CONST CTCProceduresMonitorPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST CTextViewAttributes &pAttributes, CONST CStringArray &szThreads, CONST CPtrArray &pThreadMetaDCs, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CONST CPtrArray &pSymbols, CONST CUIntArray &nSymbolIDs);
	BOOL EndPrintJob(CDC &cDC);

	BOOL DrawPrintDocPage(CDC &cDC, CONST CTCProceduresMonitorPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, LPCTSTR pszName, LPCTSTR pszDescription, LPCTSTR pszDetails, CONST CStringArray &szColumns, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nPages, INT nPage, LPRECT prClip);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocOperatingDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszDetails, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocListItemsTitle(CDC &cDC, LPRECT prClip, CONST CStringArray &szColumns, CFont *pFont, CONST CUIntArray &nTabs, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSymbol(CDC &cDC, LPRECT prClip, UINT nSymbolID, CONST CPtrArray &pSymbols, CONST CUIntArray &nSymbolIDs);
	BOOL DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc = FALSE);

	CString GetPrintDocTitle() CONST;
	CString GetPrintDocSubTitle(CONST CTCProceduresMonitorPrintJobInfo *pJobInfo, LPCTSTR pszName, LPCTSTR pszDescription) CONST;
	CString GetPrintDocOperatingDetails(CONST CTCProceduresMonitorPrintJobInfo *pJobInfo, LPCTSTR pszDetails) CONST;
	CString GetPrintDocListItemsTitle(CONST CStringArray &szColumns) CONST;
	CString GetPrintDocNotice() CONST;
	CString GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST;

	INT ExtractPrintDocText(LPCTSTR pszText, CStringArray &szColumnsText) CONST;

	BOOL CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocOperatingDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocListItemsFonts(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CFont &cTitleFont, CFont &cItemsFont) CONST;
	BOOL CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST;
	BOOL CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;

	INT CalcPrintDocTitleWidth(CDC &cDC, LPCTSTR pszColumn, CFont *pTitleFont) CONST;
	INT CalcPrintDocTitleWidth(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CFont *pTitleFont, CFont *pItemsFont, CUIntArray &nTabs) CONST;
	INT CalcPrintDocColumnWidth(CDC &cDC, CONST RECT &rArea, LPCTSTR pszColumn, CStringArray &szContents, CFont *pItemsFont) CONST;

	BOOL CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST;

private:
	BOOL SetLayoutInfo(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST SIZE &sizeListPane, CONST SIZE &sizeFlowchartPane, CONST SIZE &sizeCodePane, CONST LOGFONT *pListPaneTitleFont, CONST LOGFONT *pListPaneItemsFont, CONST LOGFONT *pCodePaneFont, CONST LOGFONT *pFlowchartPaneLabelFont, COLORREF nFlowchartPaneBackgroundColor, COLORREF nFlowchartPaneLabelColor, INT nIndex, INT nThreadID, CONST SCROLLINFO *pListPaneHorzScrollInfo, CONST SCROLLINFO *pListPaneVertScrollInfo);
	BOOL GetLayoutInfo(CUIntArray &nColumns, CUIntArray &nWidths, CSize &sizeListPane, CSize &sizeFlowchartPane, CSize &sizeCodePane, LOGFONT *pListPaneTitleFont, LOGFONT *pListPaneItemsFont, LOGFONT *pCodePaneFont, LOGFONT *pFlowchartPaneLabelFont, COLORREF &nFlowchartPaneBackgroundColor, COLORREF &nFlowchartPaneLabelColor, INT &nIndex, INT &nThreadID, SCROLLINFO *pListPaneHorzScrollInfo, SCROLLINFO *pListPaneVertScrollInfo) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProceduresMonitorWnd)
public:
	virtual BOOL Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault = TRUE);
public:
	virtual BOOL Start();
	virtual BOOL Prepare(BOOL bDialog);
	virtual BOOL Check() CONST;
	virtual VOID Update();
	virtual BOOL Stop();
public:
	virtual BOOL SaveInfo(INT nPage, INT nDisplay, LPCTSTR pszTitle, CONST PDISPLAYINFO pDisplayInfo);
	virtual BOOL LoadInfo(INT nPage, INT nDisplay, CString &szTitle, PDISPLAYINFO pDisplayInfo);
	virtual BOOL SetLayoutInfo(LPCVOID pData);
	virtual INT GetLayoutInfo(LPVOID *pData = NULL) CONST;
	virtual BOOL QueryDefaultInfo(PDISPLAYINFO pDefaultInfo) CONST;
	virtual BOOL QueryDefaultMenu(CLocaleMenu &cMenu, CImageList &cImages, CUIntArray &nImageIDs) CONST;
	virtual VOID UpdateBars();
public:
	virtual BOOL Print(PRINTDLG *pPrintInfo = NULL);
	virtual BOOL CanPrint() CONST;
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
public:
	BOOL OnCloseSettingsDialog(UINT nCode);

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProceduresMonitorWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO *lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnSettings();
	afx_msg void OnDetails();
	afx_msg void OnAuthorizations();
	afx_msg void OnStart();
	afx_msg void OnSuspend();
	afx_msg void OnStepInto();
	afx_msg void OnStepOver();
	afx_msg void OnStepOut();
	afx_msg void OnAbort();
	afx_msg void OnReset();
	afx_msg void OnResetInterlocks();
	afx_msg void OnReleaseWaitMode();
	afx_msg void OnPrint();
	afx_msg void OnUpdateSettings(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDetails(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAuthorizations(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStart(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSuspend(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStepInto(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStepOver(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStepOut(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAbort(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReset(CCmdUI *pCmdUI);
	afx_msg void OnUpdateResetInterlocks(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReleaseWaitMode(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBreakAlways(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBreakAtFailedTrigger(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBreakAtFailedBody(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBreakAtFailedConfirmation(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDisableBreakpoint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarMessagePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarUplinkPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarPEVPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarCEVPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarStatePane(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __TCMONITOR_H__
