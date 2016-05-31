// TCHISTORY.H : Telecommand History Display Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the telecommand history display related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2007/04/04 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __TCHISTORY_H__
#define __TCHISTORY_H__

#include "displays.h"


/////////////////////////////////////////////////////////////////////////////
// CTCHistoryItem

// Specify the telecommand history display item types
#define TCHISTORYITEM_TYPE_NONE   TCITEM_TYPE_NONE
#define TCHISTORYITEM_TYPE_FUNCTION   TCITEM_TYPE_FUNCTION
#define TCHISTORYITEM_TYPE_SEQUENCE   TCITEM_TYPE_SEQUENCE
#define TCHISTORYITEM_TYPE_PROCEDURE   TCITEM_TYPE_PROCEDURE
// Specify the telecommand history display item flags
#define TCHISTORYITEM_CHECKFLAG_OVERRIDEPTV   TCITEM_CHECKFLAG_OVERRIDEPTV
#define TCHISTORYITEM_CHECKFLAG_OVERRIDEPEV   TCITEM_CHECKFLAG_OVERRIDEPEV
#define TCHISTORYITEM_CHECKFLAG_OVERRIDECEV   TCITEM_CHECKFLAG_OVERRIDECEV
#define TCHISTORYITEM_CHECKFLAG_DISABLEPTV   TCITEM_CHECKFLAG_DISABLEPTV
#define TCHISTORYITEM_CHECKFLAG_DISABLEPEV   TCITEM_CHECKFLAG_DISABLEPEV
#define TCHISTORYITEM_CHECKFLAG_DISABLECEV   TCITEM_CHECKFLAG_DISABLECEV
#define TCHISTORYITEM_CHECKFLAG_PREAUTHORIZED   TCITEM_CHECKFLAG_PREAUTHORIZED
#define TCHISTORYITEM_LINKAGEFLAG_GROUPED   TCITEM_LINKAGEFLAG_GROUPED
#define TCHISTORYITEM_LINKAGEFLAG_BLOCKED   TCITEM_LINKAGEFLAG_BLOCKED
#define TCHISTORYITEM_RELEASEFLAG_AFTERBEGIN   TCITEM_RELEASEFLAG_AFTERBEGIN
#define TCHISTORYITEM_RELEASEFLAG_AFTERPREVIOUS   TCITEM_RELEASEFLAG_AFTERPREVIOUS
#define TCHISTORYITEM_EXECUTIONFLAG_AFTERBEGIN   TCITEM_EXECUTIONFLAG_AFTERBEGIN
#define TCHISTORYITEM_EXECUTIONFLAG_AFTERPREVIOUS   TCITEM_EXECUTIONFLAG_AFTERPREVIOUS
#define TCHISTORYITEM_EXECUTIONFLAG_IMMEDIATE   TCITEM_EXECUTIONFLAG_IMMEDIATE
#define TCHISTORYITEM_EXECUTIONFLAG_TIMETAGGED   TCITEM_EXECUTIONFLAG_TIMETAGGED
#define TCHISTORYITEM_EXECUTIONFLAG_1STSTEP   TCITEM_EXECUTIONFLAG_1STSTEP
#define TCHISTORYITEM_EXECUTIONFLAG_2NDSTEP   TCITEM_EXECUTIONFLAG_2NDSTEP
#define TCHISTORYITEM_DUMPFLAG_SYNCHRONIZED   TCITEM_DUMPFLAG_SYNCHRONIZED
#define TCHISTORYITEM_DUMPFLAG_NOTSYNCHRONIZED   TCITEM_DUMPFLAG_NOTSYNCHRONIZED
#define TCHISTORYITEM_ACKNOWLEDGEFLAG_ACCEPTANCE   TCITEM_ACKNOWLEDGEFLAG_ACCEPTANCE
#define TCHISTORYITEM_ACKNOWLEDGEFLAG_START   TCITEM_ACKNOWLEDGEFLAG_START
#define TCHISTORYITEM_ACKNOWLEDGEFLAG_PROGRESS   TCITEM_ACKNOWLEDGEFLAG_PROGRESS
#define TCHISTORYITEM_ACKNOWLEDGEFLAG_COMPLETION   TCITEM_ACKNOWLEDGEFLAG_COMPLETION
#define TCHISTORYITEM_ACKNOWLEDGEFLAG_ALL   TCITEM_ACKNOWLEDGEFLAG_ALL
// Specify the telecommand history display item authorization status
#define TCHISTORYITEM_AUTHORIZATIONSTATUS_NONE   TCITEM_AUTHORIZATIONSTATUS_NONE
#define TCHISTORYITEM_AUTHORIZATIONSTATUS_GRANTED   TCITEM_AUTHORIZATIONSTATUS_GRANTED
#define TCHISTORYITEM_AUTHORIZATIONSTATUS_DENIED   TCITEM_AUTHORIZATIONSTATUS_DENIED
// Specify the telecommand history display item check results
#define TCHISTORYITEM_RESULT_NONE   TCITEM_RESULT_NONE
#define TCHISTORYITEM_RESULT_PTV_GO   TCITEM_RESULT_PTV_GO
#define TCHISTORYITEM_RESULT_PTV_WAIT   TCITEM_RESULT_PTV_WAIT
#define TCHISTORYITEM_RESULT_PTV_FAIL   TCITEM_RESULT_PTV_FAIL
#define TCHISTORYITEM_RESULT_PEV_GO   TCITEM_RESULT_PEV_GO
#define TCHISTORYITEM_RESULT_PEV_NOGO   TCITEM_RESULT_PEV_NOGO
#define TCHISTORYITEM_RESULT_CEV_IDLE   TCITEM_RESULT_CEV_IDLE
#define TCHISTORYITEM_RESULT_CEV_PENDING   TCITEM_RESULT_CEV_PENDING
#define TCHISTORYITEM_RESULT_CEV_PASSED   TCITEM_RESULT_CEV_PASSED
#define TCHISTORYITEM_RESULT_CEV_FAILED   TCITEM_RESULT_CEV_FAILED
#define TCHISTORYITEM_RESULT_CEV_UNKNOWN   TCITEM_RESULT_CEV_UNKNOWN
#define TCHISTORYITEM_RESULT_CEV_UNVERIFIED   TCITEM_RESULT_CEV_UNVERIFIED
#define TCHISTORYITEM_FAILURE_PTV_UPLINK   TCITEM_FAILURE_PTV_UPLINK
#define TCHISTORYITEM_FAILURE_PTV_RELEASETIMEWINDOW   TCITEM_FAILURE_PTV_RELEASETIMEWINDOW
#define TCHISTORYITEM_FAILURE_PTV_EXECUTIONTIME   TCITEM_FAILURE_PTV_EXECUTIONTIME
#define TCHISTORYITEM_FAILURE_PTV_INTERLOCK   TCITEM_FAILURE_PTV_INTERLOCK
#define TCHISTORYITEM_FAILURE_PTV_SUBSYSTEM   TCITEM_FAILURE_PTV_SUBSYSTEM
#define TCHISTORYITEM_FAILURE_PTV_ONBOARDBUFFER   TCITEM_FAILURE_PTV_ONBOARDBUFFER
#define TCHISTORYITEM_FAILURE_PTV_ENCODING   TCITEM_FAILURE_PTV_ENCODING
#define TCHISTORYITEM_FAILURE_PEV_TELEMETRY   TCITEM_FAILURE_PEV_TELEMETRY
#define TCHISTORYITEM_FAILURE_PEV_CORRELATION   TCITEM_FAILURE_PEV_CORRELATION
#define TCHISTORYITEM_FAILURE_PEV_2NDSTEP   TCITEM_FAILURE_PEV_2NDSTEP
#define TCHISTORYITEM_FAILURE_PEV_PARAMETERS   TCITEM_FAILURE_PEV_PARAMETERS
#define TCHISTORYITEM_FAILURE_CEV_PARAMETERS   TCITEM_FAILURE_CEV_PARAMETERS
// Specify the telecommand history display item status flags
#define TCHISTORYITEM_STATUS_NONE   TCITEM_STATUS_NONE
#define TCHISTORYITEM_STATUS_RELEASED   TCITEM_STATUS_RELEASED
#define TCHISTORYITEM_STATUS_NOTRELEASED   TCITEM_STATUS_NOTRELEASED
#define TCHISTORYITEM_STATUS_FAILEDRELEASE   TCITEM_STATUS_FAILEDRELEASE
#define TCHISTORYITEM_STATUS_SENT   TCITEM_STATUS_SENT
#define TCHISTORYITEM_STATUS_FAILEDSEND   TCITEM_STATUS_FAILEDSEND
#define TCHISTORYITEM_STATUS_UPLINKED   TCITEM_STATUS_UPLINKED
#define TCHISTORYITEM_STATUS_FAILEDUPLINK   TCITEM_STATUS_FAILEDUPLINK
#define TCHISTORYITEM_STATUS_EXECUTED   TCITEM_STATUS_EXECUTED
#define TCHISTORYITEM_STATUS_NOTEXECUTED   TCITEM_STATUS_NOTEXECUTED
#define TCHISTORYITEM_STATUS_FAILEDEXECUTION   TCITEM_STATUS_FAILEDEXECUTION
// Specify the telecommand history display item status colors
#define TCHISTORYITEM_STATUSCOLOR_NONE   0
#define TCHISTORYITEM_STATUSCOLOR_IDLE   1
#define TCHISTORYITEM_STATUSCOLOR_PENDING   2
#define TCHISTORYITEM_STATUSCOLOR_PASSED   3
#define TCHISTORYITEM_STATUSCOLOR_NOTPASSED   4
// Specify the telecommand history display item alert types
#define TCHISTORYITEM_ALERTTYPE_NONE   0
#define TCHISTORYITEM_ALERTTYPE_INFORMATION   1
#define TCHISTORYITEM_ALERTTYPE_WARNING   2
#define TCHISTORYITEM_ALERTTYPE_ERROR   3
#define TCHISTORYITEM_ALERTTYPE_ANY   (-1)

class CTCHistoryItem : public CTCItem
{
	// Construction
public:
	CTCHistoryItem();

	// Attributes
private:
	typedef struct tagPROPERTIESDATA {
		INT  cbSize;
		INT  cbAlertTypes;
		INT  cbAlertMessages[2];
	} PROPERTIESDATA, *PPROPERTIESDATA, *LPPROPERTIESDATA;
private:
	CUIntArray  m_nAlertTypes;
	CUIntArray  m_nAlertMessages;
	CStringArray  m_szAlertMessages;
private:
	BOOL  m_bSelected;

	// Operations
public:
	BOOL SetAlerts(CONST CByteArray &nAlertsInfo);
	BOOL GetAlerts(CByteArray &nAlertsInfo) CONST;

	BOOL Alert(UINT nType, UINT nMessage, LPCTSTR pszMessage, BOOL bOverwrite = TRUE);
	BOOL Alert(UINT nType, UINT nMessage = -1, BOOL bEnable = FALSE);
	UINT IsAlerted(UINT nMessage, CString &szMessage) CONST;
	UINT IsAlerted(UINT nMessage = -1) CONST;

	INT GetAlertCount(UINT nType) CONST;

	VOID Select(BOOL bSelect = TRUE);
	BOOL IsSelected() CONST;

	BOOL Copy(CONST CTCHistoryItem *pItem);
	BOOL Compare(CONST CTCHistoryItem *pItem) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryItems

class CTCHistoryItems : public CTCItems
{
	// Construction
public:
	CTCHistoryItems();
	~CTCHistoryItems();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCHistoryItem *pItem);

	INT Collect(INT nIndex, CTCHistoryItems &pItems) CONST;
	INT Collect(INT nIndex, CUIntArray &nItemIDs) CONST;
	INT Collect(INT nIndex, CPtrArray &pItems) CONST;

	CTCHistoryItem *GetAt(INT nIndex) CONST;
	CTCHistoryItem *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCHistoryItems *pItems);
	BOOL Compare(CONST CTCHistoryItems *pItems) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryPrintJobInfo

class CTCHistoryPrintJobInfo : public CObject
{
	// Construction
public:
	CTCHistoryPrintJobInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbProfile;
		INT  cbComments;
		UINT  nPrintMode;
		UINT  nPrintRange[2];
		TIMEKEY  tPrintRange[2][2];
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szProfile;
	CString  m_szComments;
	CTimeKey  m_tPrintRange[2][2];
	UINT  m_nPrintRange[2];
	UINT  m_nPrintMode;

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
	BOOL SetPrintRange(UINT nMin, UINT nMax);
	BOOL SetPrintRange(CONST CTimeKey &tMin, CONST CTimeKey &tMax, BOOL bReleaseTime = TRUE);
	BOOL GetPrintRange(UINT &nMin, UINT &nMax) CONST;
	BOOL GetPrintRange(CTimeKey &tMin, CTimeKey &tMax, BOOL bReleaseTime = TRUE) CONST;

	VOID Copy(CONST CTCHistoryPrintJobInfo *pJobInfo);
	BOOL Compare(CONST CTCHistoryPrintJobInfo *pJobInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryPrintJobs

class CTCHistoryPrintJobs : public CPtrArray
{
	// Construction
public:
	CTCHistoryPrintJobs();
	~CTCHistoryPrintJobs();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCHistoryPrintJobInfo *pJobInfo);

	INT Find(LPCTSTR pszName) CONST;

	CTCHistoryPrintJobInfo *GetAt(INT nIndex) CONST;
	CTCHistoryPrintJobInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCHistoryPrintJobs *pPrintJobs);
	BOOL Compare(CONST CTCHistoryPrintJobs *pPrintJobs) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySettingsLayoutPage dialog

#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_DETAILS   1001
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT   1002
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_NAME_STATIC   1003
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_NAME   1004
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_VIEW   1005
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE   1006
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER   1007
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_REMOVE   1008
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_GRID   1009
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_GRIDCOLOR   1010
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS   1011
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS   1012
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC   1013
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE   1014
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS   1015
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_CHARACTERISTICS   1016
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC   1017
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_NAMES   1018
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC   1019
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_STYLE   1020
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC   1021
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SIZE   1022
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SAMPLE   1023
#define IDC_TCHISTORYSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT   1024

class CTCHistorySettingsLayoutPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCHistorySettingsLayoutPage)

	// Construction
public:
	CTCHistorySettingsLayoutPage();

	// Attributes
private:
	CUIntArray  m_nColumns[2];
	LOGFONT  m_fntTitle[2];
	LOGFONT  m_fntItems[2];
	COLORREF  m_nGridBackgroundColor[2];
	BOOL  m_bToolTips[2];
private:
	CString  m_szFontSampleText;
	CStringArray  m_szColumns;
	INT  m_nColumnIndex;

	// Dialog Data
	//{{AFX_DATA(CTCHistorySettingsLayoutPage)
	enum { IDD = IDD_TCHISTORY_SETTINGS_LAYOUTPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetColumns(CUIntArray &nColumns) CONST;
	BOOL GetTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetItemsFont(LPLOGFONT pItemsFont) CONST;
	BOOL GetGridBackgroundColor(COLORREF &nColor) CONST;
	BOOL GetToolTipMode(BOOL &bEnable) CONST;

	class CTCHistorySettingsDialog *GetParentDialog() CONST;
	class CTCHistoryWnd *GetParentDisplay() CONST;

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
	//{{AFX_VIRTUAL(CTCHistorySettingsLayoutPage)
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
	//{{AFX_MSG(CTCHistorySettingsLayoutPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnInsertColumnBefore();
	afx_msg void OnInsertColumnAfter();
	afx_msg void OnRemoveColumn();
	afx_msg void OnGridBackground();
	afx_msg void OnToolTips();
	afx_msg void OnTitleFont();
	afx_msg void OnItemsFont();
	afx_msg void OnEditchangeFontName();
	afx_msg void OnSelchangeColumnName();
	afx_msg void OnSelchangeFontName();
	afx_msg void OnSelchangeFontStyle();
	afx_msg void OnSelchangeFontSize();
	afx_msg void OnSelchangeGridBackgroundColor();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySettingsFilteringPage dialog

#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_DETAILS   1001
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER   1002
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMPUTER_NAME   1003
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE   1004
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_MANUALSTACK   1005
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_AUTOMATICSTACK   1006
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_COMMANDSOURCE_PROCEDURESMONITOR   1007
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND   1008
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM   1009
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM_NAME   1010
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE    1011
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE_NAME   1012
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE   1013
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_IMMEDIATE   1014
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_TIMETAGGED   1015
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_1STSTEP   1016
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_2NDSTEP   1017
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION   1018
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE_STATIC   1019
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE   1020
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE   1021
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME   1022
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES   1023
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES_COUNT   1024
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES_STATIC   1025
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES   1026
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES_COUNT   1027
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_AUTOLOAD_ENTRIES_STATIC   1028
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_ALERTS   1029
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING   1030
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_STATIC   1031
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_BYRELEASETIME   1032
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_BYEXECUTIONTIME   1033
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_ORDER_STATIC   1034
#define IDC_TCHISTORYSETTINGS_FILTERINGPAGE_SORTING_ORDER_LATESTFIRST   1035

// Specify the telecommand history display settings filtering page related limits
#define TCHISTORYSETTINGSFILTERINGPAGE_MINIMUMENTRYLIMITATION   1
#define TCHISTORYSETTINGSFILTERINGPAGE_MAXIMUMENTRYLIMITATION   10000
#define TCHISTORYSETTINGSFILTERINGPAGE_DEFAULTENTRYLIMITATION   1000
#define TCHISTORYSETTINGSFILTERINGPAGE_MINIMUMAUTOLOADENTRIES   1
#define TCHISTORYSETTINGSFILTERINGPAGE_MAXIMUMAUTOLOADENTRIES   100
#define TCHISTORYSETTINGSFILTERINGPAGE_DEFAULTAUTOLOADENTRIES   10

class CTCHistorySettingsFilteringPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCHistorySettingsFilteringPage)

	// Construction
public:
	CTCHistorySettingsFilteringPage();

	// Attributes
private:
	CString  m_szComputer[2];
	CString  m_szTelecommand[2][2];
	UINT  m_nLimitation[2];
	UINT  m_nAutoload[2];
	UINT  m_nMode[2][2];
	BOOL  m_bAlerts[2];

	// Dialog Data
	//{{AFX_DATA(CTCHistorySettingsFilteringPage)
	enum { IDD = IDD_TCHISTORY_SETTINGS_FILTERINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetMode(UINT &nMode) CONST;
	BOOL GetComputer(CString &szComputer) CONST;
	BOOL GetTelecommandName(CString &szName) CONST;
	BOOL GetTelecommandSequence(CString &szSequence) CONST;
	BOOL GetLimitation(UINT &nCount) CONST;
	BOOL GetAutoload(UINT &nCount) CONST;
	BOOL GetSortMode(UINT &nMode) CONST;

	class CTCHistorySettingsDialog *GetParentDialog() CONST;
	class CTCHistoryWnd *GetParentDisplay() CONST;

private:
	BOOL EnumComputers();
	BOOL EnumVerificationStages();
	BOOL EnumVerificationStates();

	VOID ShowFilterInfo();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySettingsFilteringPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCHistorySettingsFilteringPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnComputer();
	afx_msg void OnCommandSource();
	afx_msg void OnCommandSourceManualStack();
	afx_msg void OnCommandSourceAutomaticStack();
	afx_msg void OnCommandSourceProceduresMonitor();
	afx_msg void OnTelecommand();
	afx_msg void OnTelecommandName();
	afx_msg void OnTelecommandSequence();
	afx_msg void OnTelecommandType();
	afx_msg void OnTelecommandTypeImmediate();
	afx_msg void OnTelecommandTypeTimeTagged();
	afx_msg void OnTelecommandType1stStep();
	afx_msg void OnTelecommandType2ndStep();
	afx_msg void OnVerificationStatus();
	afx_msg void OnVerificationState();
	afx_msg void OnLimitEntries();
	afx_msg void OnAutoloadEntries();
	afx_msg void OnAlerts();
	afx_msg void OnSortByReleaseTime();
	afx_msg void OnSortByExecutionTime();
	afx_msg void OnSortOrderLatestFirst();
	afx_msg void OnSelchangeComputer();
	afx_msg void OnSelchangeVerificationStage();
	afx_msg void OnSelchangeVerificationState();
	afx_msg void OnSpinchangeLimitationCount();
	afx_msg void OnSpinchangeAutoloadCount();
	afx_msg void OnEditchangeComputer();
	afx_msg void OnEditchangeTelecommandTypeName();
	afx_msg void OnEditchangeTelecommandTypeSequence();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySettingsRetrievingPage dialog

#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_DETAILS   1001
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_KEY_STATIC   1002
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_KEY_RELEASETIME   1003
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_KEY_EXECUTIONTIME   1004
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_DATASOURCE_STATIC   1005
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_DATASOURCE   1006
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_INSPECT   1007
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO   1008
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS   1009
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC   1010
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT   1011
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC   1012
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY   1013
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC   1014
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT   1015
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC   1016
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE   1017
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC   1018
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME   1019
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO   1020
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME   1021
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC   1022
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME   1023
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC   1024
#define IDC_TCHISTORYSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE   1025

class CTCHistorySettingsRetrievingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCHistorySettingsRetrievingPage)

	// Construction
public:
	CTCHistorySettingsRetrievingPage();

	// Attributes
private:
	UINT  m_nMode[2];
	CString  m_szFileName[2];

	// Dialog Data
	//{{AFX_DATA(CTCHistorySettingsRetrievingPage)
	enum { IDD = IDD_TCHISTORY_SETTINGS_RETRIEVINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetMode(UINT &nMode) CONST;
	BOOL GetDataSourceFileName(CString &szFileName) CONST;

	class CTCHistorySettingsDialog *GetParentDialog() CONST;
	class CTCHistoryWnd *GetParentDisplay() CONST;

private:
	VOID EnumDataSources();
	VOID ShowDataSourceInfo();

	BOOL CheckDataSource(LPCTSTR pszFileName) CONST;
	BOOL CheckDataSource(LPCTSTR pszFileName, CString &szProduct, CString &szCompany, CString &szTrademark, CString &szSpacecraft, CString &szDataSourceType, CString &szStartTime, CString &szStopTime, CString &szCreationTime, CString &szDataSourceSize) CONST;

	CString FormatDataSourceSize(LPCTSTR pszDataSourceSize) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySettingsRetrievingPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCHistorySettingsRetrievingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnRetrieveByReleaseTime();
	afx_msg void OnRetrieveByExecutionTime();
	afx_msg void OnInspect();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnSelchangeFileName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySettingsPrintingComments window

class CTCHistorySettingsPrintingComments : public CEdit
{
	DECLARE_DYNCREATE(CTCHistorySettingsPrintingComments)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySettingsPrintingComments)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCHistorySettingsPrintingComments)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySettingsPrintingPage dialog

#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_DETAILS   1001
#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_PROFILE_STATIC   1002
#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_PROFILE   1003
#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS   1004
#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER   1005
#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW   1006
#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_TO_STATIC   1007
#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH   1008
#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME   1009
#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_START   1010
#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_TO_STATIC   1011
#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_STOP   1012
#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME   1013
#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_START   1014
#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_TO_STATIC   1015
#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_EXECUTIONTIME_STOP   1016
#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION   1017
#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION_SUCCESS   1018
#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_OPTIONS_VERIFICATION_FAILURE   1019
#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_COMMENTS   1020
#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_COMMENTSTEXT_STATIC   1021
#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_COMMENTSTEXT   1022
#define IDC_TCHISTORYSETTINGS_PRINTINGPAGE_CLEARCOMMENTS   1023

// Specify the telecommand history display settings printing page related limits
#define TCHISTORYSETTINGSPRINTINGPAGE_MINIMUMITEMRANGE   1
#define TCHISTORYSETTINGSPRINTINGPAGE_MAXIMUMITEMRANGE   10000
#define TCHISTORYSETTINGSPRINTINGPAGE_DEFAULTITEMRANGE   100

class CTCHistorySettingsPrintingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCHistorySettingsPrintingPage)

	// Construction
public:
	CTCHistorySettingsPrintingPage();

	// Attributes
private:
	CTCHistoryPrintJobs  m_pJobs[2];
private:
	CTCHistorySettingsPrintingComments  m_wndComments;

	// Dialog Data
	//{{AFX_DATA(CTCHistorySettingsPrintingPage)
	enum { IDD = IDD_TCHISTORY_SETTINGS_PRINTINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(CTCHistoryPrintJobs &pJobs) CONST;

	class CTCHistorySettingsDialog *GetParentDialog() CONST;
	class CTCHistoryWnd *GetParentDisplay() CONST;

private:
	VOID ShowJobInfo();
	CTCHistoryPrintJobInfo *FindJobInfo() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySettingsPrintingPage)
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
	//{{AFX_MSG(CTCHistorySettingsPrintingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPrintItemRange();
	afx_msg void OnPrintReleaseTimeRange();
	afx_msg void OnPrintExecutionTimeRange();
	afx_msg void OnVerificationStatus();
	afx_msg void OnVerificationSuccess();
	afx_msg void OnVerificationFailure();
	afx_msg void OnSelchangeProfile();
	afx_msg void OnSpinchangeLowItemRange();
	afx_msg void OnSpinchangeHighItemRange();
	afx_msg void OnSpinchangeReleaseStartTimeRange();
	afx_msg void OnSpinchangeReleaseStopTimeRange();
	afx_msg void OnSpinchangeExecutionStartTimeRange();
	afx_msg void OnSpinchangeExecutionStopTimeRange();
	afx_msg void OnEditchangeComments();
	afx_msg void OnResetComments();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySettingsTabCtrl window

class CTCHistorySettingsTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCHistorySettingsTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySettingsTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCHistorySettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySettingsDialog

class CTCHistorySettingsDialog : public CDisplayPropertySheetDialog
{
	DECLARE_DYNCREATE(CTCHistorySettingsDialog)

	// Construction
public:
	CTCHistorySettingsDialog();

	// Attributes
private:
	CTCHistorySettingsTabCtrl  m_wndTabCtrl;
	CTCHistorySettingsLayoutPage  m_pageLayout;
	CTCHistorySettingsFilteringPage  m_pageFiltering;
	CTCHistorySettingsRetrievingPage  m_pageRetrieving;
	CTCHistorySettingsPrintingPage  m_pagePrinting;

	// Operations
public:
	BOOL GetLayoutColumns(CUIntArray &nColumns) CONST;
	BOOL GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetLayoutItemsFont(LPLOGFONT pItemsFont) CONST;
	BOOL GetLayoutGridBackgroundColor(COLORREF &nColor) CONST;
	BOOL GetLayoutToolTipMode(BOOL &bEnable) CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetFilterMode(UINT &nMode) CONST;
	BOOL GetFilterComputer(CString &szComputer) CONST;
	BOOL GetFilterTelecommandName(CString &szName) CONST;
	BOOL GetFilterTelecommandSequence(CString &szSequence) CONST;
	BOOL GetFilterLimitation(UINT &nCount) CONST;
	BOOL GetFilterAutoload(UINT &nCount) CONST;
	BOOL GetFilterSortMode(UINT &nMode) CONST;
	BOOL IsFilteringModified() CONST;

	BOOL GetRetrieveMode(UINT &nMode) CONST;
	BOOL GetRetrieveFileName(CString &szFileName) CONST;
	BOOL IsRetrievingModified() CONST;

	BOOL GetPrintJobs(CTCHistoryPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CTCHistoryOpenDialog *GetParentDialog() CONST;
	class CTCHistoryWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySettingsDialog)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCHistorySettingsDialog)
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
// CTCHistoryAlertOptionsDialog dialog

#define IDC_TCHISTORY_ALERTOPTIONS_DETAILS   1001
#define IDC_TCHISTORY_ALERTOPTIONS_TYPE_STATIC   1002
#define IDC_TCHISTORY_ALERTOPTIONS_TYPE   1003
#define IDC_TCHISTORY_ALERTOPTIONS_ACTION   1004
#define IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_STATIC   1005
#define IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION   1006
#define IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_BLINK   1007
#define IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_COLOR_STATIC   1008
#define IDC_TCHISTORY_ALERTOPTIONS_ACTION_AUDITION_COLOR   1009
#define IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_STATIC   1010
#define IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS   1011
#define IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_ADD   1012
#define IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVE   1013
#define IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVEALL   1014
#define IDC_TCHISTORY_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST   1015
#define IDC_TCHISTORY_ALERTOPTIONS_HELP   1016

class CTCHistoryAlertOptionsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistoryAlertOptionsDialog)

	// Construction
public:
	CTCHistoryAlertOptionsDialog();   // standard constructor

	// Attributes
private:
	CUIntArray  m_nTypes[2];
	CStringArray  m_szAuditions[2];
	CStringArray  m_szNotifications[2];
	CDWordArray  m_nAcknowledgeColors[2];
	CByteArray  m_bAcknowledgments[2];

	// Dialog Data
	//{{AFX_DATA(CTCHistoryAlertOptionsDialog)
	enum { IDD = IDD_TCHISTORY_ALERTOPTIONS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CTCHistoryFilteringPage *GetParentDialog() CONST;
	class CTCHistoryWnd *GetParentDisplay() CONST;

private:
	BOOL EnumTypes();
	BOOL EnumAuditions();
	BOOL EnumNotifications();

	VOID ShowAlertDetails();

	INT FindAlertType() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistoryAlertOptionsDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistoryAlertsOptionsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAuditionBlink();
	afx_msg void OnAddNotification();
	afx_msg void OnRemoveNotification();
	afx_msg void OnRemoveAllNotifications();
	afx_msg void OnSelchangeType();
	afx_msg void OnSelchangeAudition();
	afx_msg void OnSelchangeAuditionColor();
	afx_msg void OnSelchangeNotification();
	afx_msg void OnSelchangeNotificationList();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryItemPropertiesParametersCalibrationPage dialog

#define IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_NAME_STATIC   1001
#define IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_NAME   1002
#define IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_ID_STATIC   1003
#define IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_ID   1004
#define IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC   1005
#define IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TYPE   1006
#define IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS_STATIC  1007
#define IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS   1008

class CTCHistoryItemPropertiesParametersCalibrationPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCHistoryItemPropertiesParametersCalibrationPage)

	// Construction
public:
	CTCHistoryItemPropertiesParametersCalibrationPage();

	// Attributes
private:
	UINT  m_nCalTableType;
	CUIntArray  m_nCalTableIDs;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCHistoryItemPropertiesParametersCalibrationPage)
	enum { IDD = IDD_TCHISTORY_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo(CONST CDatabaseTCParameter *pDatabaseTCParameter);
	VOID ShowCalibrationInfo();

	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CTCHistoryItemPropertiesParametersFolder *GetParent() CONST;

private:
	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCHistoryItemPropertiesParametersCalibrationPage)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCHistoryItemPropertiesParametersCalibrationPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryItemPropertiesParametersFolderTabCtrl window

class CTCHistoryItemPropertiesParametersFolderTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCHistoryItemPropertiesParametersFolderTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CTCHistoryItemPropertiesParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistoryItemPropertiesParametersFolderTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCHistoryItemPropertiesParametersFolderTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryItemPropertiesParametersFolder

class CTCHistoryItemPropertiesParametersFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CTCHistoryItemPropertiesParametersFolder)

	// Construction
public:
	CTCHistoryItemPropertiesParametersFolder();

	// Attributes
private:
	CTCHistoryItemPropertiesParametersFolderTabCtrl  m_wndTabCtrl;
	CTCHistoryItemPropertiesParametersCalibrationPage  m_pageCalibration;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID ShowParameterInfo(CONST CDatabaseTCParameter *pDatabaseTCParameter = NULL);

	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CTCHistoryItemPropertiesParametersDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistoryItemPropertiesParametersFolder)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCHistoryItemPropertiesParametersFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryItemPropertiesParametersDialog dialog

#define IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_DETAILS   1001
#define IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_ITEM_STATIC   1002
#define IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_ITEM   1003
#define IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_FOLDER   1004
#define IDC_TCHISTORY_ITEMPROPERTIESPARAMETERS_HELP   1005

class CTCHistoryItemPropertiesParametersDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistoryItemPropertiesParametersDialog)

	// Construction
public:
	CTCHistoryItemPropertiesParametersDialog();   // standard constructor

	// Attributes
private:
	CString  m_szX;
	CString  m_szY;
	CString  m_szParameter;
private:
	CTCHistoryItemPropertiesParametersFolder  m_wndFolderCtrl;

	// Dialog Data
	//{{AFX_DATA(CTCHistoryItemPropertiesParametersDialog)
	enum { IDD = IDD_TCHISTORY_ITEMPROPERTIESPARAMETERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, LPCTSTR pszParameter);

	VOID SetSelectedCalibrationPoint(LPCTSTR pszX, LPCTSTR pszY);
	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CDisplayDialog *GetParent() CONST;

private:
	BOOL EnumParameters();

	VOID ShowParameterInfo();

	CRect CalcFolderSize() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistoryItemPropertiesParametersDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistoryItemPropertiesParametersDialog)
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
// CTCHistoryItemPropertiesDialog dialog

#define IDC_TCHISTORY_ITEMPROPERTIES_DETAILS   1001
#define IDC_TCHISTORY_ITEMPROPERTIES_NAME_STATIC   1002
#define IDC_TCHISTORY_ITEMPROPERTIES_NAME   1003
#define IDC_TCHISTORY_ITEMPROPERTIES_DESCRIPTION_STATIC   1004
#define IDC_TCHISTORY_ITEMPROPERTIES_DESCRIPTION   1005
#define IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS   1006
#define IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_OVERRIDEPTV   1007
#define IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_OVERRIDEPEV   1008
#define IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_OVERRIDECEV   1009
#define IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_DISABLEPTV   1010
#define IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_DISABLEPEV   1011
#define IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_DISABLECEV   1012
#define IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_PREAUTHORIZED   1013
#define IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW   1014
#define IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME_STATIC   1015
#define IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME   1016
#define IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME_STATIC   1017
#define IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME   1018
#define IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_UNLIMITED   1019
#define IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME_STATIC   1020
#define IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME   1021
#define IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_DELAY_STATIC   1022
#define IDC_TCHISTORY_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_DELAY   1023
#define IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION   1024
#define IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION_IMMEDIATELY   1025
#define IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION_TIMETAG   1026
#define IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION_TIMETAG_TIME   1027
#define IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION_FIRSTSTEP   1028
#define IDC_TCHISTORY_ITEMPROPERTIES_ONBOARDEXECUTION_SECONDSTEP   1029
#define IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS   1030
#define IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_LIST   1031
#define IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_REMARK   1032
#define IDC_TCHISTORY_ITEMPROPERTIES_PARAMETERS_SHOWALL   1033
#define IDC_TCHISTORY_ITEMPROPERTIES_RAWDATA   1034
#define IDC_TCHISTORY_ITEMPROPERTIES_RAWDATA_AREA   1035
#define IDC_TCHISTORY_ITEMPROPERTIES_HELP   1036

class CTCHistoryItemPropertiesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistoryItemPropertiesDialog)

	// Construction
public:
	CTCHistoryItemPropertiesDialog();   // standard constructor

	// Attributes
private:
	CTCHistoryItem  m_cItem;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCHistoryItemPropertiesDialog)
	enum { IDD = IDD_TCHISTORY_ITEMPROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CONST CTCHistoryItem *pItem);

	CTCHistoryWnd *GetParentDisplay() CONST;

private:
	VOID ShowProperties();
	VOID ShowParameters();
	VOID ShowRawData();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistoryItemPropertiesDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistoryItemPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnShowAllParameters();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryComposedItemPropertiesDialog dialog

#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_DETAILS   1001
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_NAME_STATIC   1002
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_NAME   1003
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_DESCRIPTION_STATIC   1004
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_DESCRIPTION   1005
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_STATIC   1006
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY   1007
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PROPERTIES   1008
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS   1009
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDEPTV   1010
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDEPEV   1011
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDECEV   1012
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLEPTV   1013
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLEPEV   1014
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLECEV   1015
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_PREAUTHORIZED   1016
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW   1017
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME_STATIC   1018
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME   1019
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME_NONE   1020
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME_STATIC   1021
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME   1022
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME_NONE   1023
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_UNLIMITED   1024
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME_STATIC   1025
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME   1026
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME_NONE   1027
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_EXECUTIONTIME_STATIC   1028
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY_STATIC   1029
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY   1030
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY_NONE   1031
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION   1032
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_IMMEDIATELY   1033
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_TIMETAG   1034
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_TIMETAG_TIME   1035
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_FIRSTSTEP   1036
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_SECONDSTEP   1037
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS   1038
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST   1039
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_REMARK   1040
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SHOWFORMALLIST   1041
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SHOWALL   1042
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_RAWDATA   1043
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_ENTRY_RAWDATA_AREA   1044
#define IDC_TCHISTORY_COMPOSEDITEMPROPERTIES_HELP   1045

class CTCHistoryComposedItemPropertiesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistoryComposedItemPropertiesDialog)

	// Construction
public:
	CTCHistoryComposedItemPropertiesDialog();   // standard constructor

	// Attributes
private:
	CString  m_szName;
	CString  m_szDescription;
	CString  m_szRawData[2];
	CTCHistoryItems  m_pItems;
	CDatabaseTCParameters  m_pParameters;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCHistoryComposedItemPropertiesDialog)
	enum { IDD = IDD_TCHISTORY_COMPOSEDITEMPROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CONST CTCHistoryItems &pItems);

	CTCHistoryWnd *GetParentDisplay() CONST;

private:
	BOOL EnumEntries();

	VOID ShowProperties();
	VOID ShowParameters();
	VOID ShowRawData();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistoryComposedItemPropertiesDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistoryComposedItemPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeEntry();
	afx_msg void OnShowAllParameters();
	afx_msg void OnShowFormalParameters();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryRetrieveDialog dialog

#define IDC_TCHISTORY_RETRIEVE_DETAILS   1001
#define IDC_TCHISTORY_RETRIEVE_TITLE_STATIC   1002
#define IDC_TCHISTORY_RETRIEVE_TITLE   1003
#define IDC_TCHISTORY_RETRIEVE_TYPE_STATIC   1004
#define IDC_TCHISTORY_RETRIEVE_TYPE   1005
#define IDC_TCHISTORY_RETRIEVE_HISTORY   1006
#define IDC_TCHISTORY_RETRIEVE_HISTORY_START_STATIC   1007
#define IDC_TCHISTORY_RETRIEVE_HISTORY_STARTTIME   1008
#define IDC_TCHISTORY_RETRIEVE_HISTORY_STOP_STATIC   1009
#define IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYTIME   1010
#define IDC_TCHISTORY_RETRIEVE_HISTORY_STOPTIME   1011
#define IDC_TCHISTORY_RETRIEVE_HISTORY_STOPBYEND   1012
#define IDC_TCHISTORY_RETRIEVE_HISTORY_PLAYBACKMODE   1013
#define IDC_TCHISTORY_RETRIEVE_HISTORY_AUTOMATIC   1014
#define IDC_TCHISTORY_RETRIEVE_HISTORY_PSEUDOREALTIME   1015
#define IDC_TCHISTORY_RETRIEVE_HISTORY_MANUAL   1016
#define IDC_TCHISTORY_RETRIEVE_HISTORY_SPEED_STATIC   1017
#define IDC_TCHISTORY_RETRIEVE_HISTORY_SPEED   1018
#define IDC_TCHISTORY_RETRIEVE_HISTORY_SLOW   1019
#define IDC_TCHISTORY_RETRIEVE_HISTORY_FAST   1020
#define IDC_TCHISTORY_RETRIEVE_HELP   1021

class CTCHistoryRetrieveDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistoryRetrieveDialog)

	// Construction
public:
	CTCHistoryRetrieveDialog();   // standard constructor

	// Attributes
private:
	CString  m_szTitle;

	// Dialog Data
	//{{AFX_DATA(CTCHistoryRetrieveDialog)
	enum { IDD = IDD_TCHISTORY_RETRIEVE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);
	INT Create(CWnd *pParentWnd, LPCTSTR pszTitle);

	BOOL GetMode(UINT &nMode) CONST;
	BOOL GetSpeed(UINT &nSpeed) CONST;
	BOOL GetStartTime(CTimeKey &tTimeKey) CONST;
	BOOL GetStopTime(CTimeKey &tTimeKey) CONST;

	class CTCHistoryOpenDialog *GetParentDialog() CONST;
	class CTCHistoryWnd *GetParentDisplay() CONST;

private:
	BOOL SetRetrieveInfo();
	BOOL GetRetrieveInfo(UINT &nMode) CONST;
	BOOL GetRetrieveInfo(UINT &nMode, UINT &nSpeed, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistoryRetrieveDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistoryRetrieveDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnRetrieveByTime();
	afx_msg void OnRetrieveByEnd();
	afx_msg void OnRetrieveAutomatic();
	afx_msg void OnRetrievePseudoRealtime();
	afx_msg void OnRetrieveManual();
	afx_msg void OnSpinchangeRetrieveStartTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchNumberDialog dialog

#define IDC_TCHISTORY_SEARCHNUMBER_NUMBER_STATIC   1001
#define IDC_TCHISTORY_SEARCHNUMBER_NUMBER   1002
#define IDC_TCHISTORY_SEARCHNUMBER_GOTO   1003
#define IDC_TCHISTORY_SEARCHNUMBER_COMMENT_STATIC   1004
#define IDC_TCHISTORY_SEARCHNUMBER_COMMENT   1005
#define IDC_TCHISTORY_SEARCHNUMBER_CLOSE   1006
#define IDC_TCHISTORY_SEARCHNUMBER_HELP   1007

class CTCHistorySearchNumberDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchNumberDialog)

	// Construction
public:
	CTCHistorySearchNumberDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchNumberDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHNUMBER_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchNumberDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchNumberDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnGotoNumber();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchNameDialog dialog

#define IDC_TCHISTORY_SEARCHNAME_NAME_STATIC   1001
#define IDC_TCHISTORY_SEARCHNAME_NAME   1002
#define IDC_TCHISTORY_SEARCHNAME_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHNAME_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHNAME_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHNAME_ALL   1006
#define IDC_TCHISTORY_SEARCHNAME_FIND   1007
#define IDC_TCHISTORY_SEARCHNAME_HELP   1008

class CTCHistorySearchNameDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchNameDialog)

	// Construction
public:
	CTCHistorySearchNameDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szNames;

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchNameDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHNAME_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchNameDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchNameDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeName();
	afx_msg void OnEditchangeName();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchComputerDialog dialog

#define IDC_TCHISTORY_SEARCHCOMPUTER_NAME_STATIC   1001
#define IDC_TCHISTORY_SEARCHCOMPUTER_NAME   1002
#define IDC_TCHISTORY_SEARCHCOMPUTER_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHCOMPUTER_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHCOMPUTER_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHCOMPUTER_ALL   1006
#define IDC_TCHISTORY_SEARCHCOMPUTER_FIND   1007
#define IDC_TCHISTORY_SEARCHCOMPUTER_HELP   1008

class CTCHistorySearchComputerDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchComputerDialog)

	// Construction
public:
	CTCHistorySearchComputerDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szComputers;

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchComputerDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHCOMPUTER_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchComputerDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchComputerDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComputer();
	afx_msg void OnEditchangeComputer();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchCommandSourceDialog dialog

#define IDC_TCHISTORY_SEARCHCOMMANDSOURCE_TYPE_STATIC   1001
#define IDC_TCHISTORY_SEARCHCOMMANDSOURCE_TYPE   1002
#define IDC_TCHISTORY_SEARCHCOMMANDSOURCE_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHCOMMANDSOURCE_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHCOMMANDSOURCE_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHCOMMANDSOURCE_ALL   1006
#define IDC_TCHISTORY_SEARCHCOMMANDSOURCE_FIND   1007
#define IDC_TCHISTORY_SEARCHCOMMANDSOURCE_HELP   1008

class CTCHistorySearchCommandSourceDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchCommandSourceDialog)

	// Construction
public:
	CTCHistorySearchCommandSourceDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchCommandSourceDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHCOMMANDSOURCE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

private:
	VOID EnumCommandSources();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchCommandSourceDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchCommandSourceDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchDescriptionDialog dialog

#define IDC_TCHISTORY_SEARCHDESCRIPTION_TEXT_STATIC   1001
#define IDC_TCHISTORY_SEARCHDESCRIPTION_TEXT   1002
#define IDC_TCHISTORY_SEARCHDESCRIPTION_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHDESCRIPTION_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHDESCRIPTION_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHDESCRIPTION_ALL   1006
#define IDC_TCHISTORY_SEARCHDESCRIPTION_CASE   1007
#define IDC_TCHISTORY_SEARCHDESCRIPTION_WORD   1008
#define IDC_TCHISTORY_SEARCHDESCRIPTION_FIND   1009
#define IDC_TCHISTORY_SEARCHDESCRIPTION_HELP   1010

class CTCHistorySearchDescriptionDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchDescriptionDialog)

	// Construction
public:
	CTCHistorySearchDescriptionDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szDescriptions;

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchDescriptionDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHDESCRIPTION_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchDescriptionDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchDescriptionDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeDescription();
	afx_msg void OnEditchangeDescription();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchCategoryDialog dialog

#define IDC_TCHISTORY_SEARCHCATEGORY_CATEGORY_STATIC   1001
#define IDC_TCHISTORY_SEARCHCATEGORY_CATEGORY   1002
#define IDC_TCHISTORY_SEARCHCATEGORY_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHCATEGORY_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHCATEGORY_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHCATEGORY_ALL   1006
#define IDC_TCHISTORY_SEARCHCATEGORY_FIND   1007
#define IDC_TCHISTORY_SEARCHCATEGORY_HELP   1008

class CTCHistorySearchCategoryDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchCategoryDialog)

	// Construction
public:
	CTCHistorySearchCategoryDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchCategoryDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHCATEGORY_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

private:
	VOID EnumCategories();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchCategoryDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchCategoryDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchSubSystemDialog dialog

#define IDC_TCHISTORY_SEARCHSUBSYSTEM_NAME_STATIC   1001
#define IDC_TCHISTORY_SEARCHSUBSYSTEM_NAME   1002
#define IDC_TCHISTORY_SEARCHSUBSYSTEM_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHSUBSYSTEM_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHSUBSYSTEM_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHSUBSYSTEM_ALL   1006
#define IDC_TCHISTORY_SEARCHSUBSYSTEM_CASE   1007
#define IDC_TCHISTORY_SEARCHSUBSYSTEM_FIND   1008
#define IDC_TCHISTORY_SEARCHSUBSYSTEM_HELP   1009

class CTCHistorySearchSubSystemDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchSubSystemDialog)

	// Construction
public:
	CTCHistorySearchSubSystemDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szSubSystems;

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchSubSystemDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHSUBSYSTEM_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchSubSystemDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchSubSystemDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeSubSystem();
	afx_msg void OnEditchangeSubSystem();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchArgumentsDialog dialog

#define IDC_TCHISTORY_SEARCHARGUMENTS_ARGUMENT_STATIC   1001
#define IDC_TCHISTORY_SEARCHARGUMENTS_ARGUMENT   1002
#define IDC_TCHISTORY_SEARCHARGUMENTS_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHARGUMENTS_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHARGUMENTS_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHARGUMENTS_ALL   1006
#define IDC_TCHISTORY_SEARCHARGUMENTS_FIND   1007
#define IDC_TCHISTORY_SEARCHARGUMENTS_HELP   1008

class CTCHistorySearchArgumentsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchArgumentsDialog)

	// Construction
public:
	CTCHistorySearchArgumentsDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szArguments;

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchArgumentsDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHARGUMENTS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchArgumentsDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchArgumentsDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeArgument();
	afx_msg void OnEditchangeArgument();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchFlagsDialog dialog

#define IDC_TCHISTORY_SEARCHFLAGS_FLAG_STATIC   1001
#define IDC_TCHISTORY_SEARCHFLAGS_FLAG_INTERLOCKING   1002
#define IDC_TCHISTORY_SEARCHFLAGS_FLAG_INTERLOCKED   1003
#define IDC_TCHISTORY_SEARCHFLAGS_FLAG_GROUPED   1004
#define IDC_TCHISTORY_SEARCHFLAGS_FLAG_BLOCKED   1005
#define IDC_TCHISTORY_SEARCHFLAGS_DIRECTION   1006
#define IDC_TCHISTORY_SEARCHFLAGS_DIRECTION_UP   1007
#define IDC_TCHISTORY_SEARCHFLAGS_DIRECTION_DOWN   1008
#define IDC_TCHISTORY_SEARCHFLAGS_ALL   1009
#define IDC_TCHISTORY_SEARCHFLAGS_FIND   1010
#define IDC_TCHISTORY_SEARCHFLAGS_HELP   1011

class CTCHistorySearchFlagsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchFlagsDialog)

	// Construction
public:
	CTCHistorySearchFlagsDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchFlagsDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHFLAGS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchFlagsDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchFlagsDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnInterlockingFlag();
	afx_msg void OnInterlockedFlag();
	afx_msg void OnGroupedFlag();
	afx_msg void OnBlockedFlag();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchTCPacketDialog dialog

#define IDC_TCHISTORY_SEARCHTCPACKET_TAG_STATIC   1001
#define IDC_TCHISTORY_SEARCHTCPACKET_TAG   1002
#define IDC_TCHISTORY_SEARCHTCPACKET_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHTCPACKET_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHTCPACKET_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHTCPACKET_ALL   1006
#define IDC_TCHISTORY_SEARCHTCPACKET_FIND   1007
#define IDC_TCHISTORY_SEARCHTCPACKET_HELP   1008

class CTCHistorySearchTCPacketDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchTCPacketDialog)

	// Construction
public:
	CTCHistorySearchTCPacketDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchTCPacketDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHTCPACKET_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

private:
	VOID EnumTCPackets();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchTCPacketDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchTCPacketDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchDispatchTimeDialog dialog

#define IDC_TCHISTORY_SEARCHDISPATCHTIME_TIME_STATIC   1001
#define IDC_TCHISTORY_SEARCHDISPATCHTIME_TIME   1002
#define IDC_TCHISTORY_SEARCHDISPATCHTIME_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHDISPATCHTIME_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHDISPATCHTIME_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHDISPATCHTIME_ALL   1006
#define IDC_TCHISTORY_SEARCHDISPATCHTIME_MATCH   1007
#define IDC_TCHISTORY_SEARCHDISPATCHTIME_INTERVAL   1008
#define IDC_TCHISTORY_SEARCHDISPATCHTIME_INTERVAL_TIME   1009
#define IDC_TCHISTORY_SEARCHDISPATCHTIME_INTERVAL_STATIC   1010
#define IDC_TCHISTORY_SEARCHDISPATCHTIME_FIND   1011
#define IDC_TCHISTORY_SEARCHDISPATCHTIME_HELP   1012

// Specify the telecommand history display search dispatch time dialog related identifiers
#define TCHISTORYSEARCHDISPATCHTIME_MINIMUMINTERVAL   1
#define TCHISTORYSEARCHDISPATCHTIME_MAXIMUMINTERVAL   SECONDSPERDAY
#define TCHISTORYSEARCHDISPATCHTIME_DEFAULTINTERVAL   SECONDSPERHOUR

class CTCHistorySearchDispatchTimeDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchDispatchTimeDialog)

	// Construction
public:
	CTCHistorySearchDispatchTimeDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchDispatchTimeDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHDISPATCHTIME_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchDispatchTimeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchDispatchTimeDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDirectionUp();
	afx_msg void OnDirectionDown();
	afx_msg void OnMatchTime();
	afx_msg void OnIntervalTime();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchReleaseTimeDialog dialog

#define IDC_TCHISTORY_SEARCHRELEASETIME_TIME_STATIC   1001
#define IDC_TCHISTORY_SEARCHRELEASETIME_TIME   1002
#define IDC_TCHISTORY_SEARCHRELEASETIME_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHRELEASETIME_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHRELEASETIME_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHRELEASETIME_ALL   1006
#define IDC_TCHISTORY_SEARCHRELEASETIME_MATCH   1007
#define IDC_TCHISTORY_SEARCHRELEASETIME_INTERVAL   1008
#define IDC_TCHISTORY_SEARCHRELEASETIME_INTERVAL_TIME   1009
#define IDC_TCHISTORY_SEARCHRELEASETIME_INTERVAL_STATIC   1010
#define IDC_TCHISTORY_SEARCHRELEASETIME_FIND   1011
#define IDC_TCHISTORY_SEARCHRELEASETIME_HELP   1012

// Specify the telecommand history display search release time dialog related identifiers
#define TCHISTORYSEARCHRELEASETIME_MINIMUMINTERVAL   1
#define TCHISTORYSEARCHRELEASETIME_MAXIMUMINTERVAL   SECONDSPERDAY
#define TCHISTORYSEARCHRELEASETIME_DEFAULTINTERVAL   SECONDSPERHOUR

class CTCHistorySearchReleaseTimeDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchReleaseTimeDialog)

	// Construction
public:
	CTCHistorySearchReleaseTimeDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchReleaseTimeDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHRELEASETIME_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchReleaseTimeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchReleaseTimeDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDirectionUp();
	afx_msg void OnDirectionDown();
	afx_msg void OnMatchTime();
	afx_msg void OnIntervalTime();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchReleaseTimeOffsetDialog dialog

#define IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_OFFSET_STATIC   1001
#define IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_OFFSET   1002
#define IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_ALL   1006
#define IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_MATCH   1007
#define IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_INTERVAL   1008
#define IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_INTERVAL_TIME   1009
#define IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_INTERVAL_STATIC   1010
#define IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_FIND   1011
#define IDC_TCHISTORY_SEARCHRELEASETIMEOFFSET_HELP   1012

// Specify the telecommand history display search release time offset dialog related identifiers
#define TCHISTORYSEARCHRELEASETIMEOFFSET_MINIMUMINTERVAL   1
#define TCHISTORYSEARCHRELEASETIMEOFFSET_MAXIMUMINTERVAL   SECONDSPERDAY
#define TCHISTORYSEARCHRELEASETIMEOFFSET_DEFAULTINTERVAL   SECONDSPERMINUTE

class CTCHistorySearchReleaseTimeOffsetDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchReleaseTimeOffsetDialog)

	// Construction
public:
	CTCHistorySearchReleaseTimeOffsetDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchReleaseTimeOffsetDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHRELEASETIMEOFFSET_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchReleaseTimeOffsetDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchReleaseTimeOffsetDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDirectionUp();
	afx_msg void OnDirectionDown();
	afx_msg void OnMatchTimeOffset();
	afx_msg void OnIntervalTimeOffset();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchTransmissionTimeDialog dialog

#define IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_TIME_STATIC   1001
#define IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_TIME   1002
#define IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_ALL   1006
#define IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_MATCH   1007
#define IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_INTERVAL   1008
#define IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_INTERVAL_TIME   1009
#define IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_INTERVAL_STATIC   1010
#define IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_FIND   1011
#define IDC_TCHISTORY_SEARCHTRANSMISSIONTIME_HELP   1012

// Specify the telecommand history display search transmission time dialog related identifiers
#define TCHISTORYSEARCHTRANSMISSIONTIME_MINIMUMINTERVAL   1
#define TCHISTORYSEARCHTRANSMISSIONTIME_MAXIMUMINTERVAL   SECONDSPERDAY
#define TCHISTORYSEARCHTRANSMISSIONTIME_DEFAULTINTERVAL   SECONDSPERHOUR

class CTCHistorySearchTransmissionTimeDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchTransmissionTimeDialog)

	// Construction
public:
	CTCHistorySearchTransmissionTimeDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchTransmissionTimeDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHTRANSMISSIONTIME_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchTransmissionTimeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchTransmissionTimeDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDirectionUp();
	afx_msg void OnDirectionDown();
	afx_msg void OnMatchTime();
	afx_msg void OnIntervalTime();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchExecutionTimeDialog dialog

#define IDC_TCHISTORY_SEARCHEXECUTIONTIME_TIME_STATIC   1001
#define IDC_TCHISTORY_SEARCHEXECUTIONTIME_TIME   1002
#define IDC_TCHISTORY_SEARCHEXECUTIONTIME_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHEXECUTIONTIME_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHEXECUTIONTIME_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHEXECUTIONTIME_ALL   1006
#define IDC_TCHISTORY_SEARCHEXECUTIONTIME_MATCH   1007
#define IDC_TCHISTORY_SEARCHEXECUTIONTIME_INTERVAL   1008
#define IDC_TCHISTORY_SEARCHEXECUTIONTIME_INTERVAL_TIME   1009
#define IDC_TCHISTORY_SEARCHEXECUTIONTIME_INTERVAL_STATIC   1010
#define IDC_TCHISTORY_SEARCHEXECUTIONTIME_FIND   1011
#define IDC_TCHISTORY_SEARCHEXECUTIONTIME_HELP   1012

// Specify the telecommand history display search execution time dialog related identifiers
#define TCHISTORYSEARCHEXECUTIONTIME_MINIMUMINTERVAL   1
#define TCHISTORYSEARCHEXECUTIONTIME_MAXIMUMINTERVAL   SECONDSPERDAY
#define TCHISTORYSEARCHEXECUTIONTIME_DEFAULTINTERVAL   SECONDSPERHOUR

class CTCHistorySearchExecutionTimeDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchExecutionTimeDialog)

	// Construction
public:
	CTCHistorySearchExecutionTimeDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchExecutionTimeDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHEXECUTIONTIME_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchExecutionTimeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchExecutionTimeDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDirectionUp();
	afx_msg void OnDirectionDown();
	afx_msg void OnMatchTime();
	afx_msg void OnIntervalTime();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchExecutionTimeOffsetDialog dialog

#define IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_OFFSET_STATIC   1001
#define IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_OFFSET   1002
#define IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_ALL   1006
#define IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_MATCH   1007
#define IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_INTERVAL   1008
#define IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_INTERVAL_TIME   1009
#define IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_INTERVAL_STATIC   1010
#define IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_FIND   1011
#define IDC_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_HELP   1012

// Specify the telecommand history display search execution time offset dialog related identifiers
#define TCHISTORYSEARCHEXECUTIONTIMEOFFSET_MINIMUMOFFSET   -(365*SECONDSPERDAY)
#define TCHISTORYSEARCHEXECUTIONTIMEOFFSET_MAXIMUMOFFSET   (365*SECONDSPERDAY)
#define TCHISTORYSEARCHEXECUTIONTIMEOFFSET_DEFAULTOFFSET   0
#define TCHISTORYSEARCHEXECUTIONTIMEOFFSET_MINIMUMINTERVAL   1
#define TCHISTORYSEARCHEXECUTIONTIMEOFFSET_MAXIMUMINTERVAL   SECONDSPERDAY
#define TCHISTORYSEARCHEXECUTIONTIMEOFFSET_DEFAULTINTERVAL   SECONDSPERMINUTE

class CTCHistorySearchExecutionTimeOffsetDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchExecutionTimeOffsetDialog)

	// Construction
public:
	CTCHistorySearchExecutionTimeOffsetDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchExecutionTimeOffsetDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHEXECUTIONTIMEOFFSET_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchExecutionTimeOffsetDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchExecutionTimeOffsetDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDirectionUp();
	afx_msg void OnDirectionDown();
	afx_msg void OnMatchTimeOffset();
	afx_msg void OnIntervalTimeOffset();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchAuthorizationDialog dialog

#define IDC_TCHISTORY_SEARCHAUTHORIZATION_TYPE_STATIC   1001
#define IDC_TCHISTORY_SEARCHAUTHORIZATION_TYPE   1002
#define IDC_TCHISTORY_SEARCHAUTHORIZATION_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHAUTHORIZATION_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHAUTHORIZATION_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHAUTHORIZATION_ALL   1006
#define IDC_TCHISTORY_SEARCHAUTHORIZATION_FIND   1007
#define IDC_TCHISTORY_SEARCHAUTHORIZATION_HELP   1008

class CTCHistorySearchAuthorizationDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchAuthorizationDialog)

	// Construction
public:
	CTCHistorySearchAuthorizationDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchAuthorizationDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHAUTHORIZATION_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

private:
	VOID EnumAuthorizations();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchAuthorizationDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchAuthorizationDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchPTVTimeWindowDialog dialog

#define IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_TIME_STATIC   1001
#define IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_TIME   1002
#define IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_ALL   1006
#define IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_FIND   1007
#define IDC_TCHISTORY_SEARCHPTVTIMEWINDOW_HELP   1008

class CTCHistorySearchPTVTimeWindowDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchPTVTimeWindowDialog)

	// Construction
public:
	CTCHistorySearchPTVTimeWindowDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchPTVTimeWindowDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHPTVTIMEWINDOW_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchPTVTimeWindowDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchPTVTimeWindowDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchPTVCheckDialog dialog

#define IDC_TCHISTORY_SEARCHPTVCHECK_CHECK_STATIC   1001
#define IDC_TCHISTORY_SEARCHPTVCHECK_CHECK   1002
#define IDC_TCHISTORY_SEARCHPTVCHECK_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHPTVCHECK_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHPTVCHECK_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHPTVCHECK_ALL   1006
#define IDC_TCHISTORY_SEARCHPTVCHECK_FIND   1007
#define IDC_TCHISTORY_SEARCHPTVCHECK_HELP   1008

class CTCHistorySearchPTVCheckDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchPTVCheckDialog)

	// Construction
public:
	CTCHistorySearchPTVCheckDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchPTVCheckDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHPTVCHECK_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

private:
	VOID EnumCheckFlags();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchPTVCheckDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchPTVCheckDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchPTVResultDialog dialog

#define IDC_TCHISTORY_SEARCHPTVRESULT_RESULT_STATIC   1001
#define IDC_TCHISTORY_SEARCHPTVRESULT_RESULT   1002
#define IDC_TCHISTORY_SEARCHPTVRESULT_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHPTVRESULT_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHPTVRESULT_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHPTVRESULT_ALL   1006
#define IDC_TCHISTORY_SEARCHPTVRESULT_FIND   1007
#define IDC_TCHISTORY_SEARCHPTVRESULT_HELP   1008

class CTCHistorySearchPTVResultDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchPTVResultDialog)

	// Construction
public:
	CTCHistorySearchPTVResultDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchPTVResultDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHPTVRESULT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

private:
	VOID EnumCheckResults();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchPTVResultDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchPTVResultDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchPEVCheckDialog dialog

#define IDC_TCHISTORY_SEARCHPEVCHECK_CHECK_STATIC   1001
#define IDC_TCHISTORY_SEARCHPEVCHECK_CHECK   1002
#define IDC_TCHISTORY_SEARCHPEVCHECK_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHPEVCHECK_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHPEVCHECK_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHPEVCHECK_ALL   1006
#define IDC_TCHISTORY_SEARCHPEVCHECK_FIND   1007
#define IDC_TCHISTORY_SEARCHPEVCHECK_HELP   1008

class CTCHistorySearchPEVCheckDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchPEVCheckDialog)

	// Construction
public:
	CTCHistorySearchPEVCheckDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchPEVCheckDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHPEVCHECK_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

private:
	VOID EnumCheckFlags();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchPEVCheckDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchPEVCheckDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchPEVResultDialog dialog

#define IDC_TCHISTORY_SEARCHPEVRESULT_RESULT_STATIC   1001
#define IDC_TCHISTORY_SEARCHPEVRESULT_RESULT   1002
#define IDC_TCHISTORY_SEARCHPEVRESULT_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHPEVRESULT_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHPEVRESULT_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHPEVRESULT_ALL   1006
#define IDC_TCHISTORY_SEARCHPEVRESULT_FIND   1007
#define IDC_TCHISTORY_SEARCHPEVRESULT_HELP   1008

class CTCHistorySearchPEVResultDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchPEVResultDialog)

	// Construction
public:
	CTCHistorySearchPEVResultDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchPEVResultDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHPEVRESULT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

private:
	VOID EnumCheckResults();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchPEVResultDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchPEVResultDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchCEVTimeWindowDialog dialog

#define IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_TIME_STATIC   1001
#define IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_TIME   1002
#define IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_ALL   1006
#define IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_FIND   1007
#define IDC_TCHISTORY_SEARCHCEVTIMEWINDOW_HELP   1008

class CTCHistorySearchCEVTimeWindowDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchCEVTimeWindowDialog)

	// Construction
public:
	CTCHistorySearchCEVTimeWindowDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchCEVTimeWindowDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHCEVTIMEWINDOW_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchCEVTimeWindowDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchCEVTimeWindowDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchCEVCheckDialog dialog

#define IDC_TCHISTORY_SEARCHCEVCHECK_CHECK_STATIC   1001
#define IDC_TCHISTORY_SEARCHCEVCHECK_CHECK   1002
#define IDC_TCHISTORY_SEARCHCEVCHECK_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHCEVCHECK_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHCEVCHECK_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHCEVCHECK_ALL   1006
#define IDC_TCHISTORY_SEARCHCEVCHECK_FIND   1007
#define IDC_TCHISTORY_SEARCHCEVCHECK_HELP   1008

class CTCHistorySearchCEVCheckDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchCEVCheckDialog)

	// Construction
public:
	CTCHistorySearchCEVCheckDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchCEVCheckDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHCEVCHECK_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

private:
	VOID EnumCheckFlags();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchCEVCheckDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchCEVCheckDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchCEVResultDialog dialog

#define IDC_TCHISTORY_SEARCHCEVRESULT_RESULT_STATIC   1001
#define IDC_TCHISTORY_SEARCHCEVRESULT_RESULT   1002
#define IDC_TCHISTORY_SEARCHCEVRESULT_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHCEVRESULT_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHCEVRESULT_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHCEVRESULT_ALL   1006
#define IDC_TCHISTORY_SEARCHCEVRESULT_FIND   1007
#define IDC_TCHISTORY_SEARCHCEVRESULT_HELP   1008

class CTCHistorySearchCEVResultDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchCEVResultDialog)

	// Construction
public:
	CTCHistorySearchCEVResultDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchCEVResultDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHCEVRESULT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

private:
	VOID EnumCheckResults();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchCEVResultDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchCEVResultDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistorySearchStatusDialog dialog

#define IDC_TCHISTORY_SEARCHSTATUS_STATUS_STATIC   1001
#define IDC_TCHISTORY_SEARCHSTATUS_STATUS   1002
#define IDC_TCHISTORY_SEARCHSTATUS_DIRECTION   1003
#define IDC_TCHISTORY_SEARCHSTATUS_DIRECTION_UP   1004
#define IDC_TCHISTORY_SEARCHSTATUS_DIRECTION_DOWN   1005
#define IDC_TCHISTORY_SEARCHSTATUS_ALL   1006
#define IDC_TCHISTORY_SEARCHSTATUS_FIND   1007
#define IDC_TCHISTORY_SEARCHSTATUS_HELP   1008

class CTCHistorySearchStatusDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistorySearchStatusDialog)

	// Construction
public:
	CTCHistorySearchStatusDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCHistorySearchStatusDialog)
	enum { IDD = IDD_TCHISTORY_SEARCHSTATUS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCHistoryView *GetParent() CONST;

private:
	VOID EnumStatus();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistorySearchStatusDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistorySearchStatusDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryOpenDialog dialog

#define IDC_TCHISTORY_OPEN_DETAILS   1001
#define IDC_TCHISTORY_OPEN_DISPLAY_STATIC   1002
#define IDC_TCHISTORY_OPEN_DISPLAY   1003
#define IDC_TCHISTORY_OPEN_SETTINGS   1004
#define IDC_TCHISTORY_OPEN_TYPE   1005
#define IDC_TCHISTORY_OPEN_TYPE_NORMAL   1006
#define IDC_TCHISTORY_OPEN_MODE   1007
#define IDC_TCHISTORY_OPEN_MODE_REALTIME   1008
#define IDC_TCHISTORY_OPEN_MODE_HISTORY   1009
#define IDC_TCHISTORY_OPEN_HELP   1010

class CTCHistoryOpenDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCHistoryOpenDialog)

	// Construction
public:
	CTCHistoryOpenDialog();   // standard constructor

	// Attributes
private:
	UINT  m_nFilterMode[2];
	UINT  m_nRetrieveMode;
	UINT  m_nRetrieveSpeed;
	UINT  m_nFilterAutoload;
	UINT  m_nFilterLimitation;
	BOOL  m_bLayoutToolTips;
	LOGFONT  m_fntLayoutTitle;
	LOGFONT  m_fntLayoutItems;
	CString  m_szFilterComputer;
	CString  m_szRetrieveFileName;
	CString  m_szFilterTelecommand[2];
	COLORREF  m_nLayoutGridBackgroundColor;
	CTimeKey  m_tRetrieveStartTime;
	CTimeKey  m_tRetrieveStopTime;
	CTimeSpan  m_tRetrieveInterval;
	CUIntArray  m_nLayoutColumns;
	CTCHistoryPrintJobs  m_pPrintJobs;
private:
	CTCHistorySettingsDialog  m_dlgSettings;
	CTCHistoryRetrieveDialog  m_dlgRetrievals;

	// Dialog Data
	//{{AFX_DATA(CTCHistoryOpenDialog)
	enum { IDD = IDD_TCHISTORY_OPEN_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	CString GetTitle() CONST;
	UINT GetType() CONST;
	UINT GetMode() CONST;

	BOOL GetLayout(CString &szLayout) CONST;
	BOOL GetLayout(CString &szLayout, CUIntArray &nColumns) CONST;
	BOOL GetLayoutListTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetLayoutListItemsFont(LPLOGFONT pItemsFont) CONST;
	BOOL GetLayoutGridBackgroundColor(COLORREF &nColor) CONST;
	BOOL GetLayoutToolTipMode(BOOL &bEnable) CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetFilterMode(UINT &nMode) CONST;
	BOOL GetFilterComputer(CString &szComputer) CONST;
	BOOL GetFilterTelecommandName(CString &szName) CONST;
	BOOL GetFilterTelecommandSequence(CString &szSequence) CONST;
	BOOL GetFilterLimitation(UINT &nCount) CONST;
	BOOL GetFilterAutoload(UINT &nCount) CONST;
	BOOL GetFilterSortMode(UINT &nMode) CONST;
	BOOL IsFilteringModified() CONST;

	BOOL GetRetrieveMode(UINT &nMode) CONST;
	BOOL GetRetrieveSpeed(UINT &nSpeed) CONST;
	BOOL GetRetrieveInterval(CTimeSpan &tInterval) CONST;
	BOOL GetRetrieveStartTime(CTimeKey &tTimeKey) CONST;
	BOOL GetRetrieveStopTime(CTimeKey &tTimeKey) CONST;
	BOOL GetRetrieveFileName(CString &szFileName) CONST;
	BOOL IsRetrievingModified() CONST;

	BOOL GetPrintJobs(CTCHistoryPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CTCHistoryWnd *GetParent() CONST;

private:
	VOID EnumLayouts();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistoryOpenDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
public:
	BOOL OnCloseSettingsDialog(UINT nCode);
	BOOL OnCloseRetrieveDialog(UINT nCode);

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCHistoryOpenDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSettings();
	afx_msg void OnEditchangeTitle();
	afx_msg void OnSelchangeTitle();
	afx_msg void OnTypeNormal();
	afx_msg void OnRealtimeMode();
	afx_msg void OnHistoryMode();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryRetrieveThread thread

// Specify the telecommand history display retrieve thread action codes
#define TCHISTORYRETRIEVETHREAD_ACTION_STOP   0
#define TCHISTORYRETRIEVETHREAD_ACTION_AUTOFORWARD   1
#define TCHISTORYRETRIEVETHREAD_ACTION_MANUALFORWARD   2
#define TCHISTORYRETRIEVETHREAD_ACTION_PSEUDOREALTIME   3
#define TCHISTORYRETRIEVETHREAD_ACTION_TYPES   4

class CTCHistoryRetrieveThread : public CThread
{
	DECLARE_DYNCREATE(CTCHistoryRetrieveThread)

	// Construction
public:
	CTCHistoryRetrieveThread();

	// Attributes
private:
	UINT  m_nMode;
	UINT  m_nSpeed;
	CTimeKey  m_tStartTime;
	CTimeKey  m_tStopTime;
	CString  m_szFileName;
private:
	LONG  *m_pbFlag;
	HANDLE  m_bInit[2];
	HANDLE  m_hAction[TCHISTORYRETRIEVETHREAD_ACTION_TYPES];
private:
	CHistoryTCProcessEngine  m_cTCProcessEngine;
	CTCEnvironment  m_cTCEnvironment;

	// Operations
public:
	BOOL Start(class CTCHistoryWnd *pParentWnd, HANDLE bInit, HANDLE bContinue, LPCTSTR pszFileName, UINT nMode, UINT nSpeed, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, LONG *pbFlag, HANDLE bRetrieveStop, HANDLE bRetrieveAutoForward, HANDLE bRetrieveManualForward, HANDLE bRetrievePseudoRealtime);
	BOOL Stop();

private:
	VOID StartRetrieving();
	VOID StopRetrieving();

	UINT GetRetrieveMode() CONST;
	UINT GetRetrieveSpeed() CONST;
	CTimeKey GetRetrieveStartTime() CONST;
	CTimeKey GetRetrieveStopTime() CONST;
	CString GetRetrieveFileName() CONST;

	VOID BeginWaitCursor(BOOL bForced = FALSE);
	VOID EndWaitCursor();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistoryRetrieveThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCHistoryRetrieveThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryToolBar window

class CTCHistoryToolBar : public CDisplayToolBar
{
	DECLARE_DYNCREATE(CTCHistoryToolBar)

	// Construction
public:
	CTCHistoryToolBar();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistoryToolBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCHistoryToolBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryStatusBar window

class CTCHistoryStatusBar : public CDisplayStatusBar
{
	DECLARE_DYNCREATE(CTCHistoryStatusBar)

	// Construction
public:
	CTCHistoryStatusBar();

	// Attributes
private:
	CToolTipCtrl  m_wndToolTip;

	// Operations
public:
	BOOL SetIndicators(CONST UINT *pPanesID, INT nCount);

	class CTCHistoryWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistoryStatusBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCHistoryStatusBar)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryToolTip window

class CTCHistoryToolTip : public CDisplayToolTip
{
	DECLARE_DYNCREATE(CTCHistoryToolTip)

	// Construction
public:
	CTCHistoryToolTip();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistoryToolTip)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCHistoryToolTip)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryView window

// Specify the telecommand history display command flag symbol identifiers
#define TCHISTORYVIEW_COMMANDFLAGSYMBOL_INTERLOCK   0
#define TCHISTORYVIEW_COMMANDFLAGSYMBOL_INTERLOCKIDLE   1
#define TCHISTORYVIEW_COMMANDFLAGSYMBOL_INTERLOCKPENDING   2
#define TCHISTORYVIEW_COMMANDFLAGSYMBOL_INTERLOCKSUCCESS   3
#define TCHISTORYVIEW_COMMANDFLAGSYMBOL_INTERLOCKFAILURE   4
#define TCHISTORYVIEW_COMMANDFLAGSYMBOL_GROUPED   5
#define TCHISTORYVIEW_COMMANDFLAGSYMBOL_BLOCKED   6
#define TCHISTORYVIEW_COMMANDFLAGSYMBOLS   7
// Specify the telecommand history display command check flag symbol identifiers
#define TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOL_NONE   0
#define TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOL_ON   1
#define TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOL_OFF   2
#define TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOL_DISABLED   3
#define TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOLS   4
// Specify the telecommand history display command result symbol identifiers
#define TCHISTORYVIEW_COMMANDRESULTSYMBOL_PTV_GO   0
#define TCHISTORYVIEW_COMMANDRESULTSYMBOL_PTV_WAIT   1
#define TCHISTORYVIEW_COMMANDRESULTSYMBOL_PTV_FAIL   2
#define TCHISTORYVIEW_COMMANDRESULTSYMBOL_PEV_GO   3
#define TCHISTORYVIEW_COMMANDRESULTSYMBOL_PEV_NOGO   4
#define TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_IDLE   5
#define TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_PENDING   6
#define TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_PASSED   7
#define TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_FAILED   8
#define TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_UNKNOWN   9
#define TCHISTORYVIEW_COMMANDRESULTSYMBOL_CEV_UNVERIFIED   10
#define TCHISTORYVIEW_COMMANDRESULTSYMBOLS   11
// Specify the telecommand history display command alert symbol identifiers
#define TCHISTORYVIEW_COMMANDALERTSYMBOL_INFORMATION   0
#define TCHISTORYVIEW_COMMANDALERTSYMBOL_WARNING   1
#define TCHISTORYVIEW_COMMANDALERTSYMBOL_ERROR   2
#define TCHISTORYVIEW_COMMANDALERTSYMBOLS   3
// Specify the telecommand history display command update timer identifiers
#define TCHISTORYVIEW_COMMANDUPDATE_TIMERID   100
#define TCHISTORYVIEW_COMMANDUPDATE_TIMEOUT   1000
// Specify the telecommand history display visual aspect related identifiers
#define TCHISTORYVIEW_COLUMNTRANSPARENCY   0x30

class CTCHistoryView : public CTextView
{
	DECLARE_DYNCREATE(CTCHistoryView)

	// Construction
public:
	CTCHistoryView();

	// Attributes
private:
	CString  m_szLayout;
private:
	INT  m_nSearchIndex;
	BOOL  m_bProperties;
	BOOL  m_bFullViewMode;
	UINT  m_nFilterMode[2];
	UINT  m_nFilterAutoload;
	UINT  m_nFilterLimitation;
	CString  m_szFilterComputer;
	CString  m_szFilterTelecommand[2];
private:
	CSize  m_sizeFlagSymbols;
	CSize  m_sizeAlertSymbols;
	CSize  m_sizeResultSymbols;
	CSize  m_sizeCheckFlagSymbols;
	CImage  *m_pFlagSymbols[TCHISTORYVIEW_COMMANDFLAGSYMBOLS];
	CImage  *m_pCheckFlagSymbols[TCHISTORYVIEW_COMMANDCHECKFLAGSYMBOLS];
	CImage  *m_pResultSymbols[TCHISTORYVIEW_COMMANDRESULTSYMBOLS];
	CImage  *m_pAlertSymbols[TCHISTORYVIEW_COMMANDALERTSYMBOLS];
	COLORREF  m_nBackgroundColor[2];
	CUIntArray  m_nStatusColors;
	HCURSOR  m_hToolTipCursor;
	UINT  m_nClipboardFormat;
	BOOL  m_bToolTips;
private:
	CTCHistoryItems  m_pItems[2];
private:
	CTCHistorySearchNameDialog  m_dlgSearchName;
	CTCHistorySearchFlagsDialog  m_dlgSearchFlags;
	CTCHistorySearchNumberDialog  m_dlgSearchNumber;
	CTCHistorySearchStatusDialog  m_dlgSearchStatus;
	CTCHistorySearchComputerDialog  m_dlgSearchComputer;
	CTCHistorySearchCategoryDialog  m_dlgSearchCategory;
	CTCHistorySearchTCPacketDialog  m_dlgSearchTCPacket;
	CTCHistorySearchPTVCheckDialog  m_dlgSearchPTVCheck;
	CTCHistorySearchPEVCheckDialog  m_dlgSearchPEVCheck;
	CTCHistorySearchCEVCheckDialog  m_dlgSearchCEVCheck;
	CTCHistorySearchSubSystemDialog  m_dlgSearchSubSystem;
	CTCHistorySearchArgumentsDialog  m_dlgSearchArguments;
	CTCHistorySearchPTVResultDialog  m_dlgSearchPTVResult;
	CTCHistorySearchPEVResultDialog  m_dlgSearchPEVResult;
	CTCHistorySearchCEVResultDialog  m_dlgSearchCEVResult;
	CTCHistorySearchDescriptionDialog  m_dlgSearchDescription;
	CTCHistorySearchReleaseTimeDialog  m_dlgSearchReleaseTime;
	CTCHistorySearchDispatchTimeDialog  m_dlgSearchDispatchTime;
	CTCHistorySearchExecutionTimeDialog  m_dlgSearchExecutionTime;
	CTCHistorySearchPTVTimeWindowDialog  m_dlgSearchPTVTimeWindow;
	CTCHistorySearchCEVTimeWindowDialog  m_dlgSearchCEVTimeWindow;
	CTCHistorySearchCommandSourceDialog  m_dlgSearchCommandSource;
	CTCHistorySearchAuthorizationDialog  m_dlgSearchAuthorization;
	CTCHistorySearchTransmissionTimeDialog  m_dlgSearchTransmissionTime;
	CTCHistorySearchReleaseTimeOffsetDialog  m_dlgSearchReleaseTimeOffset;
	CTCHistorySearchExecutionTimeOffsetDialog  m_dlgSearchExecutionTimeOffset;
private:
	CTCHistoryToolTip  m_wndToolTip;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, DWORD dwStyle);

	BOOL SetLayout(LPCTSTR pszLayout);
	BOOL SetLayout(LPCTSTR pszLayout, UINT nColumns);
	BOOL SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns);
	BOOL SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayout(CString &szLayout) CONST;
	BOOL GetLayout(CString &szLayout, CUIntArray &nColumns) CONST;
	BOOL GetLayout(CString &szLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetListTitleFont(CFont *pFont);
	BOOL SetListTitleFont(CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(CFont *pFont) CONST;
	BOOL GetListTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(CFont *pFont);
	BOOL SetListItemsFont(CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(CFont *pFont) CONST;
	BOOL GetListItemsFont(LOGFONT *plfFont) CONST;
	BOOL SetGridBackgroundColor(COLORREF nColor);
	BOOL GetGridBackgroundColor(COLORREF &nColor) CONST;

	BOOL EnableFullViewMode(BOOL bEnable = TRUE);
	BOOL IsFullViewModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetFilterMode(UINT nMode);
	BOOL GetFilterMode(UINT &nMode) CONST;
	BOOL SetFilterComputer(LPCTSTR pszComputer);
	BOOL GetFilterComputer(CString &szComputer) CONST;
	BOOL SetFilterTelecommandName(LPCTSTR pszName);
	BOOL GetFilterTelecommandName(CString &szName) CONST;
	BOOL SetFilterTelecommandSequence(LPCTSTR pszSequence);
	BOOL GetFilterTelecommandSequence(CString &szSequence) CONST;
	BOOL SetFilterLimitation(UINT nCount);
	BOOL GetFilterLimitation(UINT &nCount) CONST;
	BOOL SetFilterAutoload(UINT nCount);
	BOOL GetFilterAutoload(UINT &nCount) CONST;
	BOOL SetFilterSortMode(UINT nMode);
	BOOL GetFilterSortMode(UINT &nMode) CONST;

	BOOL StartMonitoring();
	BOOL ResetMonitoring(CTCEnvironment *pTCEnvironment = NULL);
	BOOL StopMonitoring();

	BOOL SetTelecommands(CONST CTCItems &pItems);
	BOOL GetTelecommands(CTCItems &pItems) CONST;
	BOOL UpdateTelecommands(CONST CTCItems &pItems);

	BOOL SetCurTelecommand(INT nIndex);
	INT GetCurTelecommand() CONST;

	BOOL FindTelecommand(CONST CTCItem *pItem) CONST;

	BOOL SelectTelecommand(INT nIndex);
	BOOL HasSelectedTelecommands() CONST;

	UINT GetTelecommandCount() CONST;

	BOOL ShowTelecommandProperties();
	BOOL CanShowTelecommandProperties() CONST;
	BOOL IsShowingTelecommandProperties() CONST;

	BOOL DoAcknowledgeTelecommand();
	BOOL CanAcknowledgeTelecommand() CONST;
	BOOL DoCopyTelecommand();
	BOOL CanCopyTelecommand() CONST;

	BOOL SearchTelecommandByNumber(INT nNumber);
	BOOL SearchTelecommandByName(LPCTSTR pszName, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByComputer(LPCTSTR pszComputer, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByCommandSource(UINT nSourceType, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByDescription(LPCTSTR pszDescription, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL SearchTelecommandByCategory(LPCTSTR pszCategory, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandBySubSystem(LPCTSTR pszSubSystem, BOOL bDown, BOOL bAll, BOOL bCase);
	BOOL SearchTelecommandByArgument(LPCTSTR pszArgument, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByFlags(BOOL bDown, BOOL bAll, BOOL bInterlocking, BOOL bInterlocked, BOOL bGrouped, BOOL bBlocked);
	BOOL SearchTelecommandByTCPacket(LPCTSTR pszPacket, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByDispatchTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByReleaseTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByReleaseTimeOffset(DWORD dwOffset, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByTransmissionTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByExecutionTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByExecutionTimeOffset(CONST CTimeSpan &tOffset, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByAuthorization(UINT nAuthorization, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByPTVTimeWindow(CONST CTimeKey &tTime, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByPTVCheck(UINT nCheck, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByPTVResult(UINT nResult, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByPEVCheck(UINT nCheck, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByPEVResult(UINT nResult, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByCEVTimeWindow(CONST CTimeKey &tTime, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByCEVCheck(UINT nCheck, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByCEVResult(UINT nResult, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByStatus(LPCTSTR pszStatus, BOOL bDown, BOOL bAll);

	BOOL GetPrintProperties(CONST CTCHistoryPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	VOID UpdateContent(BOOL bFilter = FALSE, BOOL bRedraw = TRUE);

	class CTCHistoryWnd *GetParent() CONST;

private:
	BOOL ShowTelecommandProperties(INT nIndex);

	BOOL ActivateTelecommand(INT nIndex, BOOL bActivate = TRUE, BOOL bRedraw = TRUE);
	BOOL IsActivatedTelecommand(INT nIndex) CONST;

	BOOL UpdateTelecommand(CTCHistoryItem *pItem);

	CString TranslateTelecommand(CONST CTCHistoryItem *pItem) CONST;
	BOOL TranslateTelecommand(CONST CTCHistoryItem *pItem, CTextViewAttribute *pAttribute) CONST;

	BOOL AdjustTelecommandAlerts(CONST CTCItem *pAlertItem, CTCHistoryItem *pItem, BOOL bAlert = TRUE) CONST;

	BOOL CheckTelecommandFilter(CONST CTCItem *pItem) CONST;

private:
	CString LookupColumnName(UINT nColumn) CONST;
	UINT LookupColumnName(LPCTSTR pszColumn) CONST;
	INT LookupColumnsName(CONST CUIntArray &nColumns, CStringArray &szColumns) CONST;
	COLORREF LookupColumnColor(UINT nColumn) CONST;
	COLORREF LookupStatusColor(UINT nResult, UINT nStatus) CONST;

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths);

	CRect CalcTelecommandSymbolPosition(INT nRow, INT nColumn, LPCTSTR pszText) CONST;
	CRect CalcTelecommandSymbolPosition(INT nRow, INT nColumn, INT nCount, INT nIndex) CONST;

	CString ConstructToolTipTitle(CONST POINT &ptTip, LPCTSTR pszTip, UINT nTip) CONST;
	CString ConstructToolTipText(CONST CTCHistoryItem *pItem, CONST POINT &ptTip, LPCTSTR pszTip, UINT nTip) CONST;

	BOOL SetClipboardFormat(UINT nFormat);
	UINT GetClipboardFormat() CONST;
	BOOL CopyToClipboard();

	BOOL LoadTelecommandSymbols();
	VOID FreeTelecommandSymbols();

	BOOL LoadToolTipCursor();
	HCURSOR GetToolTipCursor() CONST;
	BOOL FreeToolTipCursor();

public:
	static TCHAR GetSymbolDelimiter();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistoryView)
public:
	virtual BOOL SetLayoutInfo(CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	virtual BOOL GetLayoutInfo(SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;
public:
	virtual VOID RecalcLayout();
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
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCHistoryView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCHistoryWnd frame

// Specify the telecommand history display types
#define TCHISTORY_TYPE_GLOBAL   1
#define TCHISTORY_TYPE_NORMAL   2
// Specify the telecommand history display title items
#define TCHISTORY_TITLEITEM_NUMBER   (1<<0)
#define TCHISTORY_TITLEITEM_NAME   (1<<1)
#define TCHISTORY_TITLEITEM_COMPUTER   (1<<2)
#define TCHISTORY_TITLEITEM_COMMANDSOURCE   (1<<3)
#define TCHISTORY_TITLEITEM_DESCRIPTION   (1<<4)
#define TCHISTORY_TITLEITEM_CATEGORY   (1<<5)
#define TCHISTORY_TITLEITEM_SUBSYSTEM   (1<<6)
#define TCHISTORY_TITLEITEM_ARGUMENTS   (1<<7)
#define TCHISTORY_TITLEITEM_FLAGS   (1<<8)
#define TCHISTORY_TITLEITEM_TCPACKET   (1<<9)
#define TCHISTORY_TITLEITEM_DISPATCHTIME   (1<<10)
#define TCHISTORY_TITLEITEM_RELEASETIME   (1<<11)
#define TCHISTORY_TITLEITEM_RELEASETIMEOFFSET   (1<<12)
#define TCHISTORY_TITLEITEM_TRANSMISSIONTIME   (1<<13)
#define TCHISTORY_TITLEITEM_EXECUTIONTIME   (1<<14)
#define TCHISTORY_TITLEITEM_EXECUTIONTIMEOFFSET   (1<<15)
#define TCHISTORY_TITLEITEM_AUTHORIZATION   (1<<16)
#define TCHISTORY_TITLEITEM_PTVTIMEWINDOW   (1<<17)
#define TCHISTORY_TITLEITEM_PTVCHECKS   (1<<18)
#define TCHISTORY_TITLEITEM_PTVRESULT   (1<<19)
#define TCHISTORY_TITLEITEM_PEVCHECKS   (1<<20)
#define TCHISTORY_TITLEITEM_PEVRESULT   (1<<21)
#define TCHISTORY_TITLEITEM_CEVTIMEWINDOW   (1<<22)
#define TCHISTORY_TITLEITEM_CEVCHECKS   (1<<23)
#define TCHISTORY_TITLEITEM_CEVRESULT   (1<<24)
#define TCHISTORY_TITLEITEM_STATUS   (1<<25)
#ifndef RC_INVOKED
#define TCHISTORY_TITLEITEMS_DEFAULT   (TCHISTORY_TITLEITEM_NUMBER | TCHISTORY_TITLEITEM_NAME | TCHISTORY_TITLEITEM_DESCRIPTION | TCHISTORY_TITLEITEM_ARGUMENTS | TCHISTORY_TITLEITEM_FLAGS | TCHISTORY_TITLEITEM_RELEASETIME | TCHISTORY_TITLEITEM_RELEASETIMEOFFSET | TCHISTORY_TITLEITEM_CEVCHECKS | TCHISTORY_TITLEITEM_CEVRESULT | TCHISTORY_TITLEITEM_STATUS)
#define TCHISTORY_TITLEITEMS_ALL   (TCHISTORY_TITLEITEMS_DEFAULT | TCHISTORY_TITLEITEM_COMPUTER | TCHISTORY_TITLEITEM_COMMANDSOURCE | TCHISTORY_TITLEITEM_CATEGORY | TCHISTORY_TITLEITEM_SUBSYSTEM | TCHISTORY_TITLEITEM_TCPACKET | TCHISTORY_TITLEITEM_DISPATCHTIME | TCHISTORY_TITLEITEM_TRANSMISSIONTIME | TCHISTORY_TITLEITEM_EXECUTIONTIME | TCHISTORY_TITLEITEM_EXECUTIONTIMEOFFSET | TCHISTORY_TITLEITEM_PTVTIMEWINDOW | TCHISTORY_TITLEITEM_PTVCHECKS | TCHISTORY_TITLEITEM_PTVRESULT | TCHISTORY_TITLEITEM_PEVCHECKS | TCHISTORY_TITLEITEM_PEVRESULT | TCHISTORY_TITLEITEM_CEVTIMEWINDOW)
#endif
// Specify the telecommand history display filter modes
#define TCHISTORY_FILTERMODE_NONE   0
#define TCHISTORY_FILTERMODE_BYCOMPUTER   (1<<0)
#define TCHISTORY_FILTERMODE_BYMANUALSTACK   (1<<1)
#define TCHISTORY_FILTERMODE_BYAUTOMATICSTACK   (1<<2)
#define TCHISTORY_FILTERMODE_BYPROCEDURESMONITOR   (1<<3)
#define TCHISTORY_FILTERMODE_BYTELECOMMAND   (1<<4)
#define TCHISTORY_FILTERMODE_BYTELECOMMANDITEM   (1<<5)
#define TCHISTORY_FILTERMODE_BYTELECOMMANDSEQUENCE   (1<<6)
#define TCHISTORY_FILTERMODE_BYTELECOMMANDTYPEIMMEDIATE   (1<<7)
#define TCHISTORY_FILTERMODE_BYTELECOMMANDTYPETIMETAGGED   (1<<8)
#define TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE1STSTEP   (1<<9)
#define TCHISTORY_FILTERMODE_BYTELECOMMANDTYPE2NDSTEP   (1<<10)
#define TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONPASSED   (1<<11)
#define TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONFAILED   (1<<12)
#define TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEPASSED   (1<<13)
#define TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEFAILED   (1<<14)
#define TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNKNOWN   (1<<15)
#define TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNVERIFIED   (1<<16)
#define TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTPASSED   (1<<17)
#define TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTFAILED   (1<<18)
#define TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNKNOWN   (1<<19)
#define TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGESTARTUNVERIFIED   (1<<20)
#define TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSPASSED   (1<<21)
#define TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSFAILED   (1<<22)
#define TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNKNOWN   (1<<23)
#define TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNVERIFIED   (1<<24)
#define TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONPASSED   (1<<25)
#define TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONFAILED   (1<<26)
#define TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNKNOWN   (1<<27)
#define TCHISTORY_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNVERIFIED   (1<<28)
#define TCHISTORY_FILTERMODE_BYLIMITENTRIES  (1<<29)
#define TCHISTORY_FILTERMODE_BYAUTOLOADENTRIES   (1<<30)
// Specify the telecommand history display sort modes
#define TCHISTORY_SORTMODE_NONE   0
#define TCHISTORY_SORTMODE_BYRELEASETIME   (1<<0)
#define TCHISTORY_SORTMODE_BYEXECUTIONTIME   (1<<1)
#define TCHISTORY_SORTMODE_BYLATESTFIRST   (1<<2)
// Specify the telecommand history display alert types
#define TCHISTORY_ALERTTYPE_TELECOMMANDACCEPTANCESUCCESS   0
#define TCHISTORY_ALERTTYPE_TELECOMMANDSTARTSUCCESS   1
#define TCHISTORY_ALERTTYPE_TELECOMMANDPROGRESSSUCCESS   2
#define TCHISTORY_ALERTTYPE_TELECOMMANDCOMPLETIONSUCCESS   3
#define TCHISTORY_ALERTTYPE_TELECOMMANDACCEPTANCEFAILURE   4
#define TCHISTORY_ALERTTYPE_TELECOMMANDSTARTFAILURE   5
#define TCHISTORY_ALERTTYPE_TELECOMMANDPROGRESSFAILURE   6
#define TCHISTORY_ALERTTYPE_TELECOMMANDCOMPLETIONFAILURE   7
#define TCHISTORY_ALERTTYPE_TELECOMMANDVERIFICATIONFAILURE   8
// Specify the telecommand history display retrieval modes
#define TCHISTORY_RETRIEVE_BYRELEASETIME   (1<<0)
#define TCHISTORY_RETRIEVE_BYEXECUTIONTIME   (1<<1)
#define TCHISTORY_RETRIEVE_EXACTTIME   (1<<2)
#define TCHISTORY_RETRIEVE_STOPBYTIME   (1<<3)
#define TCHISTORY_RETRIEVE_STOPBYEND   (1<<4)
#define TCHISTORY_RETRIEVE_STOPPED   (1<<5)
#define TCHISTORY_RETRIEVE_RELATIVE   (1<<6)
#define TCHISTORY_RETRIEVE_AUTOFORWARD   (1<<7)
#define TCHISTORY_RETRIEVE_MANUALFORWARD   (1<<8)
#define TCHISTORY_RETRIEVE_PSEUDOREALTIME   (1<<9)
// Specify the telecommand history display print modes
#define TCHISTORY_PRINT_ITEMRANGE   (1<<0)
#define TCHISTORY_PRINT_RELEASETIMERANGE   (1<<1)
#define TCHISTORY_PRINT_EXECUTIONTIMERANGE   (1<<2)
#define TCHISTORY_PRINT_VERIFICATIONSUCCESS   (1<<3)
#define TCHISTORY_PRINT_VERIFICATIONFAILURE   (1<<4)
#define TCHISTORY_PRINT_CLEARCOMMENTS   (1<<5)
// Specify the telecommand history display print fonts
#define TCHISTORY_PRINTFONT_TITLE   0
#define TCHISTORY_PRINTFONT_SUBTITLE   1
#define TCHISTORY_PRINTFONT_DETAILS   2
#define TCHISTORY_PRINTFONT_COMMENTS   3
#define TCHISTORY_PRINTFONT_LISTITEMSTITLE   4
#define TCHISTORY_PRINTFONT_LISTITEMS   5
#define TCHISTORY_PRINTFONT_FOOTER   6
#define TCHISTORY_PRINTFONT_NOTICE   7
#define TCHISTORY_PRINTFONT_LOGO   8
#define TCHISTORY_PRINTFONTS   9
// Specify the telecommand history display statusbar pane identifiers
#define ID_TCHISTORY_STATUSBAR_MESSAGEPANE   ID_SEPARATOR
#define ID_TCHISTORY_STATUSBAR_MODEPANE   ID_STATUSBAR_PANE1
#define ID_TCHISTORY_STATUSBAR_TYPEPANE   ID_STATUSBAR_PANE2

class CTCHistoryWnd : public CDisplayWnd
{
	DECLARE_DYNAMIC(CTCHistoryWnd)

	// Construction
public:
	CTCHistoryWnd();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbColumns[2];
		LOGFONT  sFont[2];
		SCROLLINFO  sScrollInfo[2];
	} DATA, *PDATA, *LPDATA;
private:
	CTCHistoryToolBar  m_wndToolBar;
	CTCHistoryStatusBar  m_wndStatusBar;
	CTCHistoryView  m_wndView;
private:
	CTCHistoryOpenDialog  m_dlgOpen;
	CTCHistorySettingsDialog  m_dlgSettings;
	CTCHistoryRetrieveDialog  m_dlgRetrievals;
private:
	CTCHistoryRetrieveThread  m_cRetrieveThread;
private:
	CTCHistoryPrintJobs  m_pPrintJobs;
private:
	LONG  m_bRetrieveFlag;
	UINT  m_nRetrieveMode;
	UINT  m_nRetrieveSpeed;
	CEvent  m_cRetrieveStop;
	CEvent  m_cRetrieveAutoForward;
	CEvent  m_cRetrieveManualForward;
	CEvent  m_cRetrievePseudoRealtime;
	CTimeKey  m_tRetrieveStartTime;
	CTimeKey  m_tRetrieveStopTime;
	CString  m_szRetrieveFileName;
private:
	CUIntArray  m_nAlertTypes;
	CStringArray  m_szAlertAuditions;
	CStringArray  m_szAlertNotifications;
	CDWordArray  m_nAlertAcknowledgeColors;
	CByteArray  m_bAlertAcknowledgments;
private:
	CString  m_szTCUnit;
	CTimeTag  m_tTCUnit;

	// Operations
public:
	BOOL SetLayout(LPCTSTR pszLayout);
	BOOL SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns);
	BOOL SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayout(CString &szLayout) CONST;
	BOOL GetLayout(CString &szLayout, CUIntArray &nColumns) CONST;
	BOOL GetLayout(CString &szLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetListTitleFont(CFont *pFont);
	BOOL SetListTitleFont(CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(CFont *pFont) CONST;
	BOOL GetListTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(CFont *pFont);
	BOOL SetListItemsFont(CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(CFont *pFont) CONST;
	BOOL GetListItemsFont(LOGFONT *plfFont) CONST;
	BOOL SetGridBackgroundColor(COLORREF nColor);
	BOOL GetGridBackgroundColor(COLORREF &nColor) CONST;

	BOOL EnableFullViewMode(BOOL bEnable = TRUE);
	BOOL IsFullViewModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetFilterMode(UINT nMode = 0);
	BOOL GetFilterMode(UINT &nMode) CONST;
	BOOL SetFilterComputer(LPCTSTR pszComputer);
	BOOL GetFilterComputer(CString &szComputer) CONST;
	BOOL SetFilterTelecommandName(LPCTSTR pszName);
	BOOL GetFilterTelecommandName(CString &szName) CONST;
	BOOL SetFilterTelecommandSequence(LPCTSTR pszSequence);
	BOOL GetFilterTelecommandSequence(CString &szSequence) CONST;
	BOOL SetFilterLimitation(UINT nCount);
	BOOL GetFilterLimitation(UINT &nCount) CONST;
	BOOL SetFilterAutoload(UINT nCount);
	BOOL GetFilterAutoload(UINT &nCount) CONST;
	BOOL SetFilterSortMode(UINT nMode = 0);
	BOOL GetFilterSortMode(UINT &nMode) CONST;

	BOOL StartMonitoring();
	BOOL StopMonitoring();

	BOOL SetTelecommands(CONST CTCItems &pItems);
	BOOL GetTelecommands(CTCItems &pItems) CONST;
	BOOL UpdateTelecommands(CONST CTCItems &pItems);

	BOOL SetCurTelecommand(INT nIndex);
	INT GetCurTelecommand() CONST;

	BOOL FindTelecommand(CONST CTCItem *pItem) CONST;

	BOOL SelectTelecommand(INT nIndex);
	BOOL HasSelectedTelecommands() CONST;

	UINT GetTelecommandCount() CONST;

	BOOL ShowTelecommandProperties();
	BOOL CanShowTelecommandProperties() CONST;
	BOOL IsShowingTelecommandProperties() CONST;

	BOOL ProcessRealtimeData();

	BOOL StartRetrieveData(UINT nMode, UINT nSpeed, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime);
	BOOL StartRetrieveData();
	LONG IsRetrievingData() CONST;
	BOOL RetrieveMoreData(UINT nAction);
	BOOL RetrieveAutoData();
	BOOL StopRetrieveData();
	BOOL SetRetrieveMode(UINT nMode = 0);
	BOOL GetRetrieveMode(UINT &nMode) CONST;
	UINT GetRetrieveMode() CONST;
	BOOL SetRetrieveSpeed(UINT nSpeed = 0);
	BOOL GetRetrieveSpeed(UINT &nSpeed) CONST;
	UINT GetRetrieveSpeed() CONST;
	BOOL SetRetrieveStartTime(CONST CTimeKey &tStartTime = 0);
	BOOL GetRetrieveStartTime(CTimeKey &tStartTime) CONST;
	CTimeKey GetRetrieveStartTime() CONST;
	BOOL SetRetrieveStopTime(CONST CTimeKey &tStopTime = 0);
	BOOL GetRetrieveStopTime(CTimeKey &tStopTime) CONST;
	CTimeKey GetRetrieveStopTime() CONST;
	BOOL SetRetrieveFileName(LPCTSTR pszFileName);
	BOOL GetRetrieveFileName(CString &szFileName) CONST;
	CString GetRetrieveFileName() CONST;

	BOOL DoAcknowledgeTelecommand();
	BOOL CanAcknowledgeTelecommand() CONST;
	BOOL DoCopyTelecommand();
	BOOL CanCopyTelecommand() CONST;

	BOOL SetAlertOptions(CONST CUIntArray &nTypes, CONST CStringArray &szAuditions, CONST CStringArray &szNotifications, CONST CDWordArray &nAcknowledgeColors, CONST CByteArray &bAcknowledgments);
	BOOL GetAlertOptions(CUIntArray &nTypes, CStringArray &szAuditions, CStringArray &szNotifications, CDWordArray &nAcknowledgeColors, CByteArray &bAcknowledgments) CONST;

	BOOL Alert(CONST CTCHistoryItem *pItem, UINT nStage = 0);

	BOOL SetPrintJobs(CONST CTCHistoryPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(CTCHistoryPrintJobs &pPrintJobs) CONST;

	BOOL Print(CONST CTCHistoryPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo = NULL);

	CTCHistoryWnd *Find(INT nType, UINT nMode, LPCTSTR pszName) CONST;

	VOID SetUpdateInfo();
	VOID SetUpdateInfo(LPCTSTR pszTag, CONST CTimeTag &tTag);
	BOOL GetUpdateInfo(CString &szTag, CTimeTag &tTag) CONST;

private:
	BOOL CreateToolBar();
	BOOL CreateStatusBar();
	BOOL CreateView();

	BOOL Customize(BOOL bDefault);

	BOOL UpdateAllPanes();
	VOID UpdateMessagePane();
	VOID UpdateModePane();
	VOID UpdateTypePane();

	VOID UpdateContents(BOOL bFilter = FALSE);

	BOOL SetPrintJobs(CONST CByteArray &nPrintInfo);
	BOOL GetPrintJobs(CByteArray &nPrintInfo) CONST;

	BOOL GetPrintProperties(CONST CTCHistoryPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

private:
	BOOL StartPrintJob(CDC &cDC);
	BOOL PrintJob(CDC &cDC, CONST CTCHistoryPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, LPCTSTR pszLayout, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST CTextViewAttributes &pAttributes, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CONST CPtrArray &pSymbols, CONST CUIntArray &nSymbolIDs);
	BOOL EndPrintJob(CDC &cDC);

	BOOL DrawPrintDocPage(CDC &cDC, CONST CTCHistoryPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, LPCTSTR pszLayout, CONST CStringArray &szColumns, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nPages, INT nPage, LPRECT prClip);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszLayout, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocComments(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocListItemsTitle(CDC &cDC, LPRECT prClip, CONST CStringArray &szColumns, CFont *pFont, CONST CUIntArray &nTabs, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSymbol(CDC &cDC, LPRECT prClip, UINT nSymbolID, CONST CPtrArray &pSymbols, CONST CUIntArray &nSymbolIDs);
	BOOL DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc = FALSE);

	CString GetPrintDocTitle() CONST;
	CString GetPrintDocSubTitle(LPCTSTR pszLayout) CONST;
	CString GetPrintDocDetails(CONST CTCHistoryPrintJobInfo *pJobInfo) CONST;
	CString GetPrintDocComments(CONST CTCHistoryPrintJobInfo *pJobInfo) CONST;
	CString GetPrintDocListItemsTitle(CONST CStringArray &szColumns) CONST;
	CString GetPrintDocNotice() CONST;
	CString GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST;

	INT ExtractPrintDocText(LPCTSTR pszText, CStringArray &szColumnsText) CONST;

	BOOL CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocCommentsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocListItemsFonts(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CFont &cTitleFont, CFont &cItemsFont) CONST;
	BOOL CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST;
	BOOL CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;

	INT CalcPrintDocTitleWidth(CDC &cDC, LPCTSTR pszColumn, CFont *pTitleFont) CONST;
	INT CalcPrintDocTitleWidth(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CFont *pTitleFont, CFont *pItemsFont, CUIntArray &nTabs) CONST;
	INT CalcPrintDocColumnWidth(CDC &cDC, CONST RECT &rArea, LPCTSTR pszColumn, CStringArray &szContents, CFont *pItemsFont) CONST;

	BOOL CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST;

private:
	BOOL SetLayoutInfo(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	BOOL GetLayoutInfo(CUIntArray &nColumns, CUIntArray &nWidths, LOGFONT *pTitleFont, LOGFONT *pItemsFont, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCHistoryWnd)
public:
	virtual BOOL Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault = TRUE);
public:
	virtual BOOL Start();
	virtual BOOL Prepare(BOOL bDialog);
	virtual BOOL Check() CONST;
	virtual VOID Update();
	virtual BOOL Update(CONST CTimeKey &tTimeKey, CTCEnvironment *pTCEnvironment, UINT nFlags = 0);
	virtual VOID Reset(CTCEnvironment *pTCEnvironment = NULL);
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
	BOOL OnCloseOpenDialog(UINT nCode);
	BOOL OnCloseSettingsDialog(UINT nCode);
	BOOL OnCloseRetrieveDialog(UINT nCode);

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCHistoryWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO *lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnSettings();
	afx_msg void OnDetails();
	afx_msg void OnAcknowledge();
	afx_msg void OnCopy();
	afx_msg void OnRetrievals();
	afx_msg void OnRetrieveStop();
	afx_msg void OnRetrieveAutoForward();
	afx_msg void OnRetrieveManualForward();
	afx_msg void OnRetrievePseudoRealtime();
	afx_msg void OnFullViewMode();
	afx_msg void OnPrint();
	afx_msg void OnDestroy();
	afx_msg void OnUpdateSettings(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDetails(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAcknowledge(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCopy(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrievals(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrieveStop(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrieveAutoForward(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrieveManualForward(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrievePseudoRealtime(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFullViewMode(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarMessagePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarModePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarTypePane(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __TCHISTORY_H__
